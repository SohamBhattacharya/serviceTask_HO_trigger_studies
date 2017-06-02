# include "DataFormats/HcalDigi/interface/HOTriggerPrimitiveDigi.h"
# include "DataFormats/L1DTTrackFinder/interface/L1MuDTChambPhContainer.h"
# include "DataFormats/L1DTTrackFinder/interface/L1MuDTChambPhDigi.h"
# include "DataFormats/L1DTTrackFinder/interface/L1MuDTChambThContainer.h"
# include "DataFormats/L1DTTrackFinder/interface/L1MuDTChambThDigi.h"
# include "DataFormats/L1DTTrackFinder/interface/L1MuDTTrackContainer.h"
# include "DataFormats/L1DTTrackFinder/interface/L1MuDTTrackCand.h"
# include "DataFormats/L1TMuon/interface/RegionalMuonCand.h"

# include "L1Trigger/L1TwinMux/interface/HOtoDTTranslator.h"
# include "L1Trigger/L1TwinMux/interface/HOTwinMuxAlgorithm.h"


namespace HOTwinMuxAlgorithm
{
    void addHOinfo(edm::Handle <L1MuDTChambPhContainer> phiPrimitivesHandle, \
        edm::Handle <L1MuDTChambThContainer> thePrimitivesHandle, \
        edm::Handle <edm::SortedCollection <HOTriggerPrimitiveDigi> > hotpHandle)
    {
        double pileUp = getPUFromLumiSection(iEvent.getLuminosityBlock().luminosityBlockAuxiliary().luminosityBlock());
        h_eventsPerPileUp->Fill(pileUp);
        //std::cout << iEvent.id().luminosityBlock() << " " << iEvent.getLuminosityBlock().luminosityBlockAuxiliary().luminosityBlock() << " " << pileUp << "\n";
        double addTrack1_pT = 0;
        double addTrack2_pT = 0;
        
        double bmtfTrack1_pT = 0;
        double bmtfTrack2_pT = 0;
        
        Output *currentOutput = 0;
        
        // Remember the quality of the leading/sub-leading tracks
        bool isAddTrack1HQ = false;
        bool isAddTrack2HQ = false;
        
        
        for(unsigned int iDigiPh = 0; iDigiPh < digis_L1MuDTChambPh->size(); iDigiPh++)
        {
            L1MuDTChambPhDigi digi_L1MuDTChambPh = digis_L1MuDTChambPh->at(iDigiPh);
            
            bool is_LQ = digi_L1MuDTChambPh.code() > 0 && digi_L1MuDTChambPh.code() < 4;
            bool is_HQ = digi_L1MuDTChambPh.code() > 3 && digi_L1MuDTChambPh.code() < 7;
            
            // Check track quality
            if(!is_LQ && !is_HQ)
            {
                continue;
            }
            
            // Select the histograms to write to (LQ or HQ)
            if(is_LQ)
            {
                currentOutput = output_LQ;
            }
            
            else if(is_HQ)
            {
                currentOutput = output_HQ;
            }
            
            // Hit in 1st muon station
            if(digi_L1MuDTChambPh.stNum() != 1)
            {
                continue;
            }
            
            currentOutput->h_phiOfDigis->Fill(digi_L1MuDTChambPh.phi());
            currentOutput->h_phiBOfDigis->Fill(digi_L1MuDTChambPh.phiB());
            currentOutput->h_phiOfDigis_vs_phiBOfDigis->Fill(digi_L1MuDTChambPh.phi(), digi_L1MuDTChambPh.phiB());
            currentOutput->h_codeDigis->Fill(digi_L1MuDTChambPh.code());
            
            double globalPhi = digi_L1MuDTChambPh.phi() / 4096.0;
            globalPhi += 3.141 / 6 * (digi_L1MuDTChambPh.scNum() - 1);
            
            if(globalPhi > 3.141)
            {
                globalPhi -= 3.141 * 2;
            }
            
            int iPhi = getIPhi(globalPhi);
            
            int iEta = -99;
                
            if(is_HQ)
            {
                for(unsigned int iDigiTh = 0; iDigiTh < digis_L1MuDTChambTh->size(); iDigiTh++)
                {
                    L1MuDTChambThDigi digi_L1MuDTChambTh = digis_L1MuDTChambTh->at(iDigiTh);
                    
                    if(digi_L1MuDTChambTh.whNum() == digi_L1MuDTChambPh.whNum() &&
                        digi_L1MuDTChambTh.stNum() == digi_L1MuDTChambPh.stNum() &&
                        digi_L1MuDTChambTh.scNum() == digi_L1MuDTChambPh.scNum())
                    {
                        iEta = getEtaFromSegment(digi_L1MuDTChambTh);
                    }
                }
                
                if(iEta == -99)
                {
                    continue;
                }
            }
            
            
            for(edm::SortedCollection <HOTriggerPrimitiveDigi,
                edm::StrictWeakOrdering <HOTriggerPrimitiveDigi> >::const_iterator hoTP = hotpHandle->begin();
                hoTP != hotpHandle->end(); ++hoTP)
            {
                int isMip = hoTP->bits()&(1<<hoTP->whichSampleTriggered());
                //std::cout << "isMip = " << isMip << "\n";
                //std::cout << hoTP->bits() << " " << hoTP->whichSampleTriggered() << "\n";
                
                // Check if HO-TP is mip-like
                if(!isMip)
                {
                    continue;
                }
                
                // Check for matching HO-TP in phi direction
                if(fabs(hoTP->iphi() - iPhi) > 1)
                {
                    continue;
                }
                
                // For LQ, check for matching HO-TP in the same wheel
                if(is_LQ)
                {
                    if(!isInWheel(hoTP->ieta(), digi_L1MuDTChambPh.whNum()))
                    {
                        continue;
                    }
                }
                
                // For HQ, check for matching HO-TP in eta direction
                else if(is_HQ)
                {
                    if(fabs(hoTP->ieta() - iEta) > 1)
                    {
                        continue;
                    }
                }
                
                
                bool isPresent = false;
                
                // Check for matching BMTF track to HO-TP
                for(l1t::RegionalMuonCandBxCollection::const_iterator muonCand = bmtfHandle->begin(); muonCand != bmtfHandle->end(); ++muonCand)
                {
                    double phiTrack = muonCand->hwPhi() * 2.0 * 3.141 / 576.0;
                    double etaTrack = muonCand->hwEta();
                    
                    int iPhiTrack = getIPhi(phiTrack);
                    int iEtaTrack = getIEta(etaTrack);
                    
                    if(fabs(hoTP->iphi() - iPhiTrack) < 2 && fabs(hoTP->ieta() - iEtaTrack) < 2)
                    {
                        isPresent = true;
                    }
                }
                
                
                // If no matching BMTF track is found, 
                // get pT of leading/sub-leading muon chamber TP
                if(!isPresent)
                {
                    double muDT_pT = getPt(digi_L1MuDTChambPh);
                    
                    //std::cout << "addTrackAll_pT " << muDT_pT << "\n";
                    currentOutput->h_PU_vs_addTrackAll_pT->Fill(muDT_pT, pileUp);
                    
                    if(muDT_pT > addTrack1_pT)
                    {
                        addTrack2_pT = addTrack1_pT;
                        addTrack1_pT = muDT_pT;
                        
                        isAddTrack2HQ = isAddTrack1HQ;
                        isAddTrack1HQ = is_HQ;
                    }
                    
                    else if(muDT_pT > addTrack2_pT)
                    {
                        addTrack2_pT = muDT_pT;
                        
                        isAddTrack2HQ = is_HQ;
                    }
                    
                    //std::cout << is_LQ << " " << is_HQ << " " << iDigiPh << " " << addTrack1_pT << " " << addTrack2_pT << "\n";
                    break;
                }
            }
        }
    }
}
