// -*- C++ -*-
//
// Package:    EDAnalyzers/RatePlot_myVersion
// Class:      RatePlot_myVersion
// 
/**\class RatePlot_myVersion RatePlot_myVersion.cc EDAnalyzers/RatePlot_myVersion/plugins/RatePlot_myVersion.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  
//         Created:  Thu, 16 Mar 2017 05:18:37 GMT
//
//


// system include files
#include <memory>
#include <fstream>

// user include files
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"

#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/DTRecHit/interface/DTRecSegment4D.h"
#include "DataFormats/DTRecHit/interface/DTRecSegment2D.h"
#include "DataFormats/GeometrySurface/interface/Surface.h"
#include "DataFormats/MuonReco/interface/MuonFwd.h"
#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/L1DTTrackFinder/interface/L1MuDTChambPhContainer.h"
#include "DataFormats/L1DTTrackFinder/interface/L1MuDTChambPhDigi.h"
#include "DataFormats/L1DTTrackFinder/interface/L1MuDTChambThContainer.h"
#include "DataFormats/L1DTTrackFinder/interface/L1MuDTChambThDigi.h"
#include "DataFormats/L1DTTrackFinder/interface/L1MuDTTrackContainer.h"
#include "DataFormats/L1DTTrackFinder/interface/L1MuDTTrackCand.h"
#include "DataFormats/HcalRecHit/interface/HORecHit.h"
#include "DataFormats/L1Trigger/interface/L1MuonParticle.h"
#include "DataFormats/L1Trigger/interface/L1MuonParticleFwd.h"
#include "DataFormats/HcalDigi/interface/HOTriggerPrimitiveDigi.h"
#include "DataFormats/L1TMuon/interface/RegionalMuonCand.h"
#include "DataFormats/L1Trigger/interface/HOTPDigiTwinMux.h"

#include "Geometry/DTGeometry/interface/DTGeometry.h"
#include "Geometry/CaloGeometry/interface/CaloGeometry.h"
#include "Geometry/Records/interface/MuonGeometryRecord.h"
#include "Geometry/Records/interface/CaloGeometryRecord.h"

#include "TH1F.h"
#include "TH2F.h"
//
// class declaration
//

// If the analyzer does not use TFileService, please remove
// the template argument to the base class so the class inherits
// from  edm::one::EDAnalyzer<> and also remove the line from
// constructor "usesResource("TFileService");"
// This will improve performance in multithreaded jobs.


class Output
{
    public :
    
    TH1F *h_phiOfDigis;
    TH1F *h_phiBOfDigis;
    TH1F *h_codeDigis;
    
    TH1F *h_addTrack1_pT;
    TH1F *h_addTrack2_pT;

    TH2F *h_PU_vs_addTrack1_pT;
    TH2F *h_PU_vs_addTrack2_pT;
    TH2F *h_PU_vs_addTrackAll_pT;
    
    TH2F *h_phiOfDigis_vs_phiBOfDigis;
    
    
    Output(edm::Service <TFileService> fs, const char *dirName)
    {
        TFileDirectory dir = fs->mkdir(dirName);
        
        char name[500];
        char title[500];
        
        sprintf(name, "phiOfDigis");
        sprintf(title, "phiOfDigis");
        h_phiOfDigis = dir.make <TH1F> (name, title, 4096, -2048, 2047);
        
        sprintf(name, "codeDigis");
        sprintf(title, "codeDigis");
        h_codeDigis = dir.make <TH1F> (name, title, 4096, -2048, 2047);
        
        sprintf(name, "phiBOfDigis");
        sprintf(title, "phiBOfDigis");
        h_phiBOfDigis = dir.make <TH1F> (name, title, 512, -256, 255);
        
        sprintf(name, "addTrack1_pT");
        sprintf(title, "addTrack1_pT");
        h_addTrack1_pT = dir.make <TH1F> (name, title, 40, 0, 40);
        
        sprintf(name, "addTrack2_pT");
        sprintf(title, "addTrack2_pT");
        h_addTrack2_pT = dir.make <TH1F> (name, title, 40, 0, 40);
        
        sprintf(name, "PU_vs_addTrack1_pT");
        sprintf(title, "PU_vs_addTrack1_pT");
        h_PU_vs_addTrack1_pT = dir.make <TH2F> (name, title, 40, 0, 40, 3000, 30, 60);
        
        sprintf(name, "PU_vs_addTrack2_pT");
        sprintf(title, "PU_vs_addTrack2_pT");
        h_PU_vs_addTrack2_pT = dir.make <TH2F> (name, title, 40, 0, 40, 3000, 30, 60);
        
        sprintf(name, "PU_vs_addTrackAll_pT");
        sprintf(title, "PU_vs_addTrackAll_pT");
        h_PU_vs_addTrackAll_pT = dir.make <TH2F> (name, title, 40, 0, 40, 3000, 30, 60);
        
        sprintf(name, "phiOfDigis_vs_phiBOfDigis");
        sprintf(title, "phiOfDigis_vs_phiBOfDigis");
        h_phiOfDigis_vs_phiBOfDigis = dir.make <TH2F> (name, title, 4096, -2048, 2047, 512, -256, 255);
    }
};


class RatePlot_myVersion : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
    public:
    
    explicit RatePlot_myVersion(const edm::ParameterSet&);
    ~RatePlot_myVersion();
    
    static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


    private:
    
    virtual void beginJob() override;
    virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
    virtual void endJob() override;
    
    virtual int getIEta(double eta);
	virtual int getIPhi(double phi);
    
	virtual double getPt(L1MuDTChambPhDigi digi_L1MuDTChambPh);
    
	virtual double getEtaFromSegment(L1MuDTChambThDigi digi_L1MuDTChambTh);
    
	virtual bool isInWheel(int ieta, int wheel);
    
	virtual double getPUFromLumiSection(int lumiSec);
    
	virtual void parseCSV();
    
    // ----------member data ---------------------------
    
    edm::EDGetTokenT <L1MuDTChambPhContainer> tok_L1MuDTChambPh;
    edm::EDGetTokenT <L1MuDTChambThContainer> tok_L1MuDTChambTh;
    
    edm::EDGetTokenT <L1MuDTTrackContainer> tok_L1MuDTTrack;
    
    edm::EDGetTokenT <edm::SortedCollection <HOTriggerPrimitiveDigi, \
        edm::StrictWeakOrdering <HOTriggerPrimitiveDigi> > > tok_HOTriggerPrimitiveDigi;
    
    edm::EDGetTokenT <l1t::RegionalMuonCandBxCollection> tok_RegionalMuonCandBx;
    
    TH1F *h_eventsPerPileUp;
    
    TH1F *h_bmtfTrack1_pT;
    TH1F *h_bmtfTrack2_pT;
    
    TH2F *h_PU_vs_bmtfTrack1_pT;
    TH2F *h_PU_vs_bmtfTrack2_pT;
    TH2F *h_PU_vs_bmtfTrackAll_pT;

    vector <int> v_lumiSection;
    vector <double> v_pileUp;
    
    Output *output_LQ;
    Output *output_HQ;
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
RatePlot_myVersion::RatePlot_myVersion(const edm::ParameterSet& iConfig)
{
    //now do what ever initialization is needed
    usesResource("TFileService");
    
    parseCSV();
    
    edm::Service < TFileService > fs;
    
    output_LQ = new Output(fs, "LQ");
    output_HQ = new Output(fs, "HQ");
    
    h_eventsPerPileUp = fs->make <TH1F> ("eventsPerPileUp", "eventsPerPileUp", 3000, 30, 60);
    
    h_bmtfTrack1_pT = fs->make < TH1F > ("bmtfTrack1_pT", "bmtfTrack1_pT", 40, 0, 40);
    h_bmtfTrack2_pT = fs->make < TH1F > ("bmtfTrack2_pT", "bmtfTrack2_pT", 40, 0, 40);
    
    h_PU_vs_bmtfTrack1_pT = fs->make <TH2F> ("PU_vs_bmtfTrack1_pT", "PU_vs_bmtfTrack1_pT", 40, 0, 40, 3000, 30, 60);
    h_PU_vs_bmtfTrack2_pT = fs->make <TH2F> ("PU_vs_bmtfTrack2_pT", "PU_vs_bmtfTrack2_pT", 40, 0, 40, 3000, 30, 60);
    h_PU_vs_bmtfTrackAll_pT = fs->make <TH2F> ("PU_vs_bmtfTrackAll_pT", "PU_vs_bmtfTrackAll_pT", 40, 0, 40, 3000, 30, 60);
    
    tok_L1MuDTChambPh = consumes <L1MuDTChambPhContainer> (edm::InputTag("bmtfDigis"));
    tok_L1MuDTChambTh = consumes <L1MuDTChambThContainer> (edm::InputTag("bmtfDigis"));
    
    tok_L1MuDTTrack = consumes <L1MuDTTrackContainer> (edm::InputTag("dttfDigis", "DATA"));
    
    tok_HOTriggerPrimitiveDigi = consumes <edm::SortedCollection <HOTriggerPrimitiveDigi, \
        edm::StrictWeakOrdering <HOTriggerPrimitiveDigi> > > (edm::InputTag("hcalDigis"));
    
    tok_RegionalMuonCandBx = consumes <l1t::RegionalMuonCandBxCollection> (edm::InputTag("gmtStage2Digis", "BMTF"));
}


RatePlot_myVersion::~RatePlot_myVersion()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void RatePlot_myVersion::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
    using namespace edm;
    
    edm::ESHandle < DTGeometry > dtGeometry;
    iSetup.get<MuonGeometryRecord>().get(dtGeometry);
    
    edm::ESHandle < CaloGeometry > caloGeometry;
    iSetup.get<CaloGeometryRecord>().get(caloGeometry);
    
    edm::Handle < L1MuDTChambPhContainer > phiPrimitivesHandle;
    iEvent.getByToken(tok_L1MuDTChambPh, phiPrimitivesHandle);
    
    edm::Handle < L1MuDTChambThContainer > thePrimitivesHandle;
    iEvent.getByToken(tok_L1MuDTChambTh, thePrimitivesHandle);
    
    edm::Handle <L1MuDTTrackContainer> dttfTrackHandle;
    iEvent.getByToken(tok_L1MuDTTrack, dttfTrackHandle);
    
    edm::Handle < l1t::RegionalMuonCandBxCollection > bmtfHandle;
    iEvent.getByToken(tok_RegionalMuonCandBx, bmtfHandle);
    
    edm::Handle <edm::SortedCollection <HOTriggerPrimitiveDigi> > hoPrimitivesHandle;
    iEvent.getByToken(tok_HOTriggerPrimitiveDigi, hoPrimitivesHandle);
    
    
    const L1MuDTChambPhContainer::Phi_Container *digis_L1MuDTChambPh =
            phiPrimitivesHandle->getContainer();

    const L1MuDTChambThContainer::The_Container *digis_L1MuDTChambTh =
            thePrimitivesHandle->getContainer();

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
            edm::StrictWeakOrdering <HOTriggerPrimitiveDigi> >::const_iterator hoTP = hoPrimitivesHandle->begin();
            hoTP != hoPrimitivesHandle->end(); ++hoTP)
        {
            //HOTPDigiTwinMux hotptm(hoTP->raw());
            //std::cout << "mip = " << hotptm.mip() << " " << (hoTP->bits()&(1<<hoTP->whichSampleTriggered())) << "\n";
            //std::cout << "iPhi = " << hotptm.iphi() << " " << hoTP->iphi() << "\n";
            //std::cout << "iPhi = " << hotptm.ieta() << " " << hoTP->ieta() << "\n";
            
            int isMip = hoTP->bits()&(1<<hoTP->whichSampleTriggered());
            std::cout << "isMip = " << isMip << "\n";
            
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
                
                std::cout << "addTrackAll_pT " << muDT_pT << "\n";
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
                
                std::cout << is_LQ << " " << is_HQ << " " << iDigiPh << " " << addTrack1_pT << " " << addTrack2_pT << "\n";
                break;
            }
        }
    }
    
    
    // Get pT of leading/sub-leading BMTF track
    for(l1t::RegionalMuonCandBxCollection::const_iterator muonCand = bmtfHandle->begin(); muonCand != bmtfHandle->end(); ++muonCand)
    {
        double bmtf_pT = muonCand->hwPt() * 0.5;
        
        std::cout << "bmtfTrackAll_pT " << bmtf_pT << "\n";
        h_PU_vs_bmtfTrackAll_pT->Fill(bmtf_pT, pileUp);
        
        if(bmtf_pT > bmtfTrack1_pT)
        {
            bmtfTrack2_pT = bmtfTrack1_pT;
            bmtfTrack1_pT = bmtf_pT;
        }
        
        else if(bmtf_pT > bmtfTrack2_pT)
        {
            bmtfTrack2_pT = bmtf_pT;
        }
    }
    
    
    if(addTrack1_pT > 0)
    {
        std::cout << "addTrack1_pT " << addTrack1_pT << "\n";
        
        if(isAddTrack1HQ)
        {
            currentOutput = output_HQ;
        }
        
        else
        {
            currentOutput = output_LQ;
        }
        
        currentOutput->h_addTrack1_pT->Fill(addTrack1_pT);
        currentOutput->h_PU_vs_addTrack1_pT->Fill(addTrack1_pT, pileUp);
    }
    
    if(addTrack2_pT > 0)
    {
        std::cout << "addTrack2_pT " << addTrack2_pT << "\n";
        
        if(isAddTrack2HQ)
        {
            currentOutput = output_HQ;
        }
        
        else
        {
            currentOutput = output_LQ;
        }
        
        currentOutput->h_addTrack2_pT->Fill(addTrack2_pT);
        currentOutput->h_PU_vs_addTrack2_pT->Fill(addTrack2_pT, pileUp);
    }
    
    if(bmtfTrack1_pT > 0)
    {
        std::cout << "bmtfTrack1_pT " << bmtfTrack1_pT << "\n";
        
        h_bmtfTrack1_pT->Fill(bmtfTrack1_pT);
        h_PU_vs_bmtfTrack1_pT->Fill(bmtfTrack1_pT, pileUp);
    }
    
    if(bmtfTrack2_pT > 0)
    {
        std::cout << "bmtfTrack2_pT " << bmtfTrack2_pT << "\n";
        
        h_bmtfTrack2_pT->Fill(bmtfTrack2_pT);
        h_PU_vs_bmtfTrack2_pT->Fill(bmtfTrack2_pT, pileUp);
    }
}


// ------------ method called once each job just before starting event loop  ------------
void 
RatePlot_myVersion::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
RatePlot_myVersion::endJob() 
{
    delete output_LQ;
    delete output_HQ;
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
RatePlot_myVersion::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}


int RatePlot_myVersion::getIPhi(double phi)
{
    double val = 0;
    
    if(phi < 0)
    {
        val = 2 * 3.141 + phi;
    }
    
    else
    {
        val = phi;
    }
    
    val = val / 2. / 3.141 * 72.;
    
    int iPhi = (int) val + 1;
    
    return iPhi;
}


int RatePlot_myVersion::getIEta(double eta)
{
    double b = (2. * 3.141 / 72.);
    double a = eta + 15 * b;
    double c = a / b;
    
    int e = (int) c;
    int iEta = e - 15;
    
    if(iEta >= 0) {
        return iEta + 1;
    }
    
    return iEta;
}


bool RatePlot_myVersion::isInWheel(int iEta, int wheel)
{
    if(iEta < -10 && wheel == -2)
    {
        return true;
    }
    
    if((iEta < -4 && iEta > -11) && wheel == -1)
    {
        return true;
    }
    
    if((iEta < 5 && iEta > -5) && wheel == 0)
    {
        return true;
    }
    
    if((iEta > 4 && iEta < 11) && wheel == 1)
    {
        return true;
    }
    
    if(iEta > 10 && wheel == 2)
    {
        return true;
    }
    
    return false;
}


double RatePlot_myVersion::getEtaFromSegment(L1MuDTChambThDigi digi_L1MuDTChambTh)
{
    int pos = -1;
    
    for(unsigned int i = 0; i < 7; i++)
    {
        if(digi_L1MuDTChambTh.code(i) == 2)
        {
            pos = i;
        }
    }
    
    if(digi_L1MuDTChambTh.whNum() == -2 || digi_L1MuDTChambTh.whNum() == -1
            || (digi_L1MuDTChambTh.whNum() == 0
                    && (digi_L1MuDTChambTh.scNum() == 0 || digi_L1MuDTChambTh.scNum() == 3
                            || digi_L1MuDTChambTh.scNum() == 4 || digi_L1MuDTChambTh.scNum() == 7
                            || digi_L1MuDTChambTh.scNum() == 8 || digi_L1MuDTChambTh.scNum() == 11)))
    {
        pos = 6 - pos;
    }
    
    if(digi_L1MuDTChambTh.whNum() == -2)
    {
        return ((int) (round((-5. / 7.) * (pos + 1) - 10)));
    }
    
    if(digi_L1MuDTChambTh.whNum() == -1)
    {
        return ((int) (round((-6. / 7.) * (pos + 1) - 4)));
    }
    
    if(digi_L1MuDTChambTh.whNum() == 0)
    {
        return ((int) (round((-8. / 7.) * (pos + 1) + 5)));
    }
    
    if(digi_L1MuDTChambTh.whNum() == 1)
    {
        return ((int) (round((-6. / 7.) * (pos + 1) + 11)));
    }
    
    if(digi_L1MuDTChambTh.whNum() == 2){
        return ((int) (round((-5. / 7.) * (pos + 1) + 16)));
    }
    
    return -99;
}


double RatePlot_myVersion::getPt(L1MuDTChambPhDigi digi_L1MuDTChambPh)
{
    double p0 = 1.10456;
    double p1 = 2.27101;
    double p2 = 1.57637e-2;
    double n0 = -1.07813;
    double n1 = 2.34187;
    double n2 = -2.00791e-2;
    double phiB = digi_L1MuDTChambPh.phiB() / 512.;
    
    if(phiB < 0)
    {
        return fabs(n0 / (phiB - n2) + n1);
    }
    
    else
    {
        return fabs(p0 / (phiB - p2) + p1);
    }
}


void RatePlot_myVersion::parseCSV()
{
    std::ifstream data("LS.csv");
    std::string line;
    std::vector <vector <string> > parsedCsv;
    
    while(std::getline(data, line))
    {
        std::stringstream lineStream(line);
        std::string cell;
        std::vector <string> parsedRow;
        
        while(std::getline(lineStream, cell, ','))
        {
            parsedRow.push_back(cell);
        }
        
        parsedCsv.push_back(parsedRow);
    }
    
    for(unsigned int i = 0; i < parsedCsv.size(); i++)
    {
        v_lumiSection.push_back(std::stoi(parsedCsv[i][2]));
        v_pileUp.push_back(std::stod(parsedCsv[i][3]));
        
        //std::cout << "LumiSection: " << std::stoi(parsedCsv[i][2]) << " PileUp: " << std::stod(parsedCsv[i][3]) << std::endl;
    }
}


double RatePlot_myVersion::getPUFromLumiSection(int lumiSec)
{
    for(unsigned int iLumiSection = 0; iLumiSection < v_lumiSection.size(); iLumiSection++)
    {
        if(v_lumiSection[iLumiSection] == lumiSec)
        {
            //std::cout << "Check LS: " << lumiSec << " PileUp: " << pileUp.at(i) << std::endl;
            return v_pileUp.at(iLumiSection);
        }
    }
    
    return -1;
}

//define this as a plug-in
DEFINE_FWK_MODULE(RatePlot_myVersion);
