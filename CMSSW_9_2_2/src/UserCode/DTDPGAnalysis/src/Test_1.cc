// system include files
#include <memory>
#include <fstream>
#include <string>
#include <vector>

// user include files
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"

#include "DataFormats/Common/interface/SortedCollection.h"
#include "DataFormats/HcalRecHit/interface/HORecHit.h"
#include "DataFormats/HcalDigi/interface/HOTriggerPrimitiveDigi.h"

#include "DataFormats/L1TMuon/interface/RegionalMuonCandFwd.h"
#include "DataFormats/L1TMuon/interface/RegionalMuonCand.h"
#include "DataFormats/L1Trigger/interface/Muon.h"

#include "Geometry/DTGeometry/interface/DTGeometry.h"
#include "Geometry/Records/interface/MuonGeometryRecord.h"    // New trying to avoid crashes in the topology functions
#include "Geometry/DTGeometry/interface/DTLayer.h" // New trying to avoid crashes in the topology functions
#include "Geometry/DTGeometry/interface/DTTopology.h" // New trying to avoid crashes in the topology functions
#include "DataFormats/MuonDetId/interface/DTLayerId.h" // New trying to avoid crashes in the topology functions

#include "DataFormats/DTRecHit/interface/DTRecSegment4DCollection.h"
#include "DataFormats/L1DTTrackFinder/interface/L1MuDTChambPhContainer.h"
#include "DataFormats/L1DTTrackFinder/interface/L1MuDTChambThContainer.h"

#include "TH1F.h"
#include "TH2F.h"
#include "TTree.h"
#include "TFile.h"
//
// class declaration
//

// If the analyzer does not use TFileService, please remove
// the template argument to the base class so the class inherits
// from  edm::one::EDAnalyzer<> and also remove the line from
// constructor "usesResource("TFileService");"
// This will improve performance in multithreaded jobs.


class Test_1: public edm::one::EDAnalyzer<edm::one::SharedResources> {
    public:
    
    explicit Test_1(const edm::ParameterSet&);
    ~Test_1();
    
    static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


    private:
    
    virtual void beginJob() override;
    virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
    virtual void endJob() override;
    
    virtual void clear();
    
    //virtual void fill_dtsegments_variables(edm::Handle <DTRecSegment4DCollection> dtsegments4DHandle, const DTGeometry* dtGeom);
    virtual void fill_twinmuxout_variables(edm::Handle <L1MuDTChambPhContainer> localTriggerTwinMuxOut);
    virtual void fill_twinmuxin_variables(edm::Handle <L1MuDTChambPhContainer> localTriggerTwinMuxIn);
    virtual void fill_twinmuxth_variables(edm::Handle <L1MuDTChambThContainer> localTriggerTwinMux_Th);
    
    virtual void fill_hoTP_variables(edm::Handle <edm::SortedCollection <HOTriggerPrimitiveDigi> > hotpHandle);
    
    virtual int getIetaFromSegment(L1MuDTChambThDigi digi_L1MuDTChambTh);
    virtual int getIphiFromPhDigi(L1MuDTChambPhDigi digi_L1MuDTChambPh);
    
    // ----------member data ---------------------------
    
    // HO variables
    int hoTPdigi_n;
    std::vector<double> hoTPdigi_bits;
    std::vector<double> hoTPdigi_iEta;
    std::vector<double> hoTPdigi_iPhi;
    std::vector<double> hoTPdigi_nSamples;
    std::vector<double> hoTPdigi_raw;
    std::vector<double> hoTPdigi_whichSampleTriggered;
    
    //DT segment variables
    int segm4D_n;
    std::vector<double> segm4D_wheel;
    std::vector<double> segm4D_sector;
    std::vector<double> segm4D_station;
    std::vector<double> segm4D_hasPhi;
    std::vector<double> segm4D_hasZed;
    std::vector<double> segm4D_x_pos_loc;
    std::vector<double> segm4D_y_pos_loc;
    std::vector<double> segm4D_z_pos_loc;
    std::vector<double> segm4D_x_dir_loc;
    std::vector<double> segm4D_y_dir_loc;
    std::vector<double> segm4D_z_dir_loc;
    std::vector<double> segm4D_cosx;
    std::vector<double> segm4D_cosy;
    std::vector<double> segm4D_cosz;
    std::vector<double> segm4D_phi;
    std::vector<double> segm4D_theta;
    std::vector<double> segm4D_eta;
    std::vector<double> segm4D_t0;
    std::vector<double> segm4D_vdrift;
    std::vector<double> segm4D_phinormchi2;
    std::vector<double> segm4D_phinhits;
    std::vector<double> segm4D_znormchi2;
    std::vector<double> segm4D_znhits;
    
    // DTTP variables
    int ltTwinMuxIn_n;
    std::vector<double> ltTwinMuxIn_wheel;
    std::vector<double> ltTwinMuxIn_sector;
    std::vector<double> ltTwinMuxIn_station;
    std::vector<double> ltTwinMuxIn_quality;
    std::vector<double> ltTwinMuxIn_bx;
    std::vector<double> ltTwinMuxIn_phi;
    std::vector<double> ltTwinMuxIn_iPhi;
    std::vector<double> ltTwinMuxIn_phiB;
    std::vector<double> ltTwinMuxIn_is2nd;
    
    int ltTwinMuxOut_n;
    std::vector<double> ltTwinMuxOut_wheel;
    std::vector<double> ltTwinMuxOut_sector;
    std::vector<double> ltTwinMuxOut_station;
    std::vector<double> ltTwinMuxOut_quality;
    std::vector<double> ltTwinMuxOut_rpcbit;
    std::vector<double> ltTwinMuxOut_bx;
    std::vector<double> ltTwinMuxOut_phi;
    std::vector<double> ltTwinMuxOut_iPhi;
    std::vector<double> ltTwinMuxOut_phiB;
    std::vector<double> ltTwinMuxOut_is2nd;
    
    int ltTwinMux_thN;
    std::vector<double> ltTwinMux_thBx;
    std::vector<double> ltTwinMux_thWheel;
    std::vector<double> ltTwinMux_thSector;
    std::vector<double> ltTwinMux_thStation;
    std::vector<double> ltTwinMux_thHits;
    std::vector<double> ltTwinMux_thIeta;
    
    TTree *tree;
    
    edm::InputTag hoTPLabel;
    edm::EDGetTokenT <edm::SortedCollection <HOTriggerPrimitiveDigi, \
        edm::StrictWeakOrdering <HOTriggerPrimitiveDigi> > > tok_hoTP;
    
    edm::InputTag dtSegmentLabel;
    edm::EDGetTokenT<DTRecSegment4DCollection> tok_dtSegment;
    
    edm::InputTag twinmuxPhInLabel;
    edm::EDGetTokenT <L1MuDTChambPhContainer> tok_twinmuxPhIn;
    
    edm::InputTag twinmuxPhOutLabel;
    edm::EDGetTokenT <L1MuDTChambPhContainer> tok_twinmuxPhOut;
    
    edm::InputTag twinmuxThLabel;
    edm::EDGetTokenT<L1MuDTChambThContainer> tok_twinmuxTh;
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
Test_1::Test_1(const edm::ParameterSet& iConfig)
{
    //now do what ever initialization is needed
    
    usesResource("TFileService");
    
    edm::Service <TFileService> fs;
    tree = fs->make<TTree>("tree", "tree");
    
    
    tree->Branch("hoTPdigi_n", &hoTPdigi_n);
    tree->Branch("hoTPdigi_bits", &hoTPdigi_bits);
    tree->Branch("hoTPdigi_iEta", &hoTPdigi_iEta);
    tree->Branch("hoTPdigi_iPhi", &hoTPdigi_iPhi);
    tree->Branch("hoTPdigi_nSamples", &hoTPdigi_nSamples);
    tree->Branch("hoTPdigi_raw", &hoTPdigi_raw);
    tree->Branch("hoTPdigi_whichSampleTriggered", &hoTPdigi_whichSampleTriggered);
    
    tree->Branch("dtsegm4D_wheel",&segm4D_wheel);
    tree->Branch("dtsegm4D_sector",&segm4D_sector);
    tree->Branch("dtsegm4D_station",&segm4D_station);
    tree->Branch("dtsegm4D_hasPhi",&segm4D_hasPhi);
    tree->Branch("dtsegm4D_hasZed",&segm4D_hasZed);
    tree->Branch("dtsegm4D_x_pos_loc",&segm4D_x_pos_loc);
    tree->Branch("dtsegm4D_y_pos_loc",&segm4D_y_pos_loc);
    tree->Branch("dtsegm4D_z_pos_loc",&segm4D_z_pos_loc);
    tree->Branch("dtsegm4D_x_dir_loc",&segm4D_x_dir_loc);
    tree->Branch("dtsegm4D_y_dir_loc",&segm4D_y_dir_loc);
    tree->Branch("dtsegm4D_z_dir_loc",&segm4D_z_dir_loc);
    tree->Branch("dtsegm4D_cosx",&segm4D_cosx);
    tree->Branch("dtsegm4D_cosy",&segm4D_cosy);
    tree->Branch("dtsegm4D_cosz",&segm4D_cosz);
    tree->Branch("dtsegm4D_phi",&segm4D_phi);
    tree->Branch("dtsegm4D_theta",&segm4D_theta);
    tree->Branch("dtsegm4D_eta",&segm4D_eta);
    tree->Branch("dtsegm4D_t0",&segm4D_t0);
    tree->Branch("dtsegm4D_vdrift",&segm4D_vdrift);
    tree->Branch("dtsegm4D_phinormchisq",&segm4D_phinormchi2);
    tree->Branch("dtsegm4D_phinhits",&segm4D_phinhits);
    tree->Branch("dtsegm4D_znormchisq",&segm4D_znormchi2);
    tree->Branch("dtsegm4D_znhits",&segm4D_znhits);
    
    tree->Branch("ltTwinMuxIn_n", &ltTwinMuxIn_n);
    tree->Branch("ltTwinMuxIn_wheel", &ltTwinMuxIn_wheel);
    tree->Branch("ltTwinMuxIn_sector", &ltTwinMuxIn_sector);
    tree->Branch("ltTwinMuxIn_station", &ltTwinMuxIn_station);
    tree->Branch("ltTwinMuxIn_quality", &ltTwinMuxIn_quality);
    tree->Branch("ltTwinMuxIn_bx", &ltTwinMuxIn_bx);
    tree->Branch("ltTwinMuxIn_phi", &ltTwinMuxIn_phi);
    tree->Branch("ltTwinMuxIn_iPhi", &ltTwinMuxIn_iPhi);
    tree->Branch("ltTwinMuxIn_phiB", &ltTwinMuxIn_phiB);
    tree->Branch("ltTwinMuxIn_is2nd", &ltTwinMuxIn_is2nd);
    
    tree->Branch("ltTwinMuxOut_n", &ltTwinMuxOut_n);
    tree->Branch("ltTwinMuxOut_wheel", &ltTwinMuxOut_wheel);
    tree->Branch("ltTwinMuxOut_sector", &ltTwinMuxOut_sector);
    tree->Branch("ltTwinMuxOut_station", &ltTwinMuxOut_station);
    tree->Branch("ltTwinMuxOut_quality", &ltTwinMuxOut_quality);
    tree->Branch("ltTwinMuxOut_rpcbit", &ltTwinMuxOut_rpcbit);
    tree->Branch("ltTwinMuxOut_bx", &ltTwinMuxOut_bx);
    tree->Branch("ltTwinMuxOut_phi", &ltTwinMuxOut_phi);
    tree->Branch("ltTwinMuxOut_iPhi", &ltTwinMuxOut_iPhi);
    tree->Branch("ltTwinMuxOut_phiB", &ltTwinMuxOut_phiB);
    tree->Branch("ltTwinMuxOut_is2nd", &ltTwinMuxOut_is2nd);
    
    tree->Branch("ltTwinMux_thN", &ltTwinMux_thN);
    tree->Branch("ltTwinMux_thWheel", &ltTwinMux_thWheel);
    tree->Branch("ltTwinMux_thSector", &ltTwinMux_thSector);
    tree->Branch("ltTwinMux_thStation", &ltTwinMux_thStation);
    tree->Branch("ltTwinMux_thBx", &ltTwinMux_thBx);
    tree->Branch("ltTwinMux_thHits", &ltTwinMux_thHits);
    tree->Branch("ltTwinMux_thIeta", &ltTwinMux_thIeta);
    
    
    hoTPLabel = iConfig.getParameter<edm::InputTag>("hoTPLabel");
    tok_hoTP = consumes<edm::SortedCollection <HOTriggerPrimitiveDigi, \
             edm::StrictWeakOrdering <HOTriggerPrimitiveDigi> > > (edm::InputTag(hoTPLabel));
    
    /*dtSegmentLabel = iConfig.getParameter<edm::InputTag>("dtSegmentLabel");
    tok_dtSegment = consumes<DTRecSegment4DCollection>(edm::InputTag(dtSegmentLabel));
    
    twinmuxPhInLabel = iConfig.getParameter<edm::InputTag>("twinmuxPhInLabel");
    tok_twinmuxPhIn = consumes<L1MuDTChambPhContainer>(edm::InputTag(twinmuxPhInLabel));
    
    twinmuxPhOutLabel = iConfig.getParameter<edm::InputTag>("twinmuxPhOutLabel");
    tok_twinmuxPhOut = consumes<L1MuDTChambPhContainer>(edm::InputTag(twinmuxPhOutLabel));
    
    twinmuxThLabel = iConfig.getParameter<edm::InputTag>("twinmuxThLabel");
    tok_twinmuxTh = consumes<L1MuDTChambThContainer>(edm::InputTag(twinmuxThLabel))*/;
}


Test_1::~Test_1()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void Test_1::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
    clear();
    
    edm::Handle <edm::SortedCollection <HOTriggerPrimitiveDigi> > hotpHandle;
    iEvent.getByToken(tok_hoTP, hotpHandle);
    
    /*edm::Handle <DTRecSegment4DCollection> dtsegments4DHandle;
    iEvent.getByToken(tok_dtSegment, dtsegments4DHandle);
    
    edm::Handle <L1MuDTChambPhContainer> twinmuxPhInHandle;
    iEvent.getByToken(tok_twinmuxPhIn, twinmuxPhInHandle);
    
    edm::Handle <L1MuDTChambPhContainer> twinmuxPhOutHandle;
    iEvent.getByToken(tok_twinmuxPhOut, twinmuxPhOutHandle);
    
    edm::Handle <L1MuDTChambThContainer> twinmuxThHandle;
    iEvent.getByToken(tok_twinmuxTh, twinmuxThHandle);*/
    
    /*fill_twinmuxin_variables(twinmuxPhInHandle);
    fill_twinmuxout_variables(twinmuxPhOutHandle);
    fill_twinmuxth_variables(twinmuxThHandle);*/
    
    fill_hoTP_variables(hotpHandle);
    
    tree->Fill();
}
// ------------ method called once each job just before starting event loop  ------------
void 
Test_1::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
Test_1::endJob() 
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
Test_1::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}


void Test_1::fill_twinmuxout_variables(edm::Handle<L1MuDTChambPhContainer> localTriggerTwinMuxOut)
{
    const std::vector <L1MuDTChambPhDigi> *phTrigs = localTriggerTwinMuxOut->getContainer();
    
    for(unsigned int iDigi = 0; iDigi < phTrigs->size(); iDigi++)
    {
        L1MuDTChambPhDigi iph = phTrigs->at(iDigi);
        
        if(iph.code() != 7)
        {
            ltTwinMuxOut_wheel.push_back(iph.whNum());
            ltTwinMuxOut_sector.push_back(iph.scNum() + 1); // DTTF[0-11] -> DT[1-12] Sector Numbering
            ltTwinMuxOut_station.push_back(iph.stNum());
            ltTwinMuxOut_quality.push_back(iph.code());
            ltTwinMuxOut_rpcbit.push_back(iph.RpcBit());
            ltTwinMuxOut_bx.push_back(iph.bxNum());
            ltTwinMuxOut_phi.push_back(iph.phi());
            ltTwinMuxOut_iPhi.push_back(getIphiFromPhDigi(iph));
            ltTwinMuxOut_phiB.push_back(iph.phiB());
            ltTwinMuxOut_is2nd.push_back(iph.Ts2Tag());
            
            ltTwinMuxOut_n++;
        }
    }
    
    printf("Number of ltTwinMuxOut = %d / %d \n", ltTwinMuxOut_n, (int) phTrigs->size());
}

void Test_1::fill_twinmuxin_variables(edm::Handle<L1MuDTChambPhContainer> localTriggerTwinMuxIn)
{
    const std::vector <L1MuDTChambPhDigi> *phTrigs = localTriggerTwinMuxIn->getContainer();
    
    for(unsigned int iDigi = 0; iDigi < phTrigs->size(); iDigi++)
    {
        L1MuDTChambPhDigi iph = phTrigs->at(iDigi);
        
        if(iph.code() != 7)
        {
            ltTwinMuxIn_wheel.push_back(iph.whNum());
            ltTwinMuxIn_sector.push_back(iph.scNum() + 1); // DTTF[0-11] -> DT[1-12] Sector Numbering
            ltTwinMuxIn_station.push_back(iph.stNum());
            ltTwinMuxIn_quality.push_back(iph.code());
            
            if(iph.Ts2Tag() == 1)
            {
                ltTwinMuxIn_bx.push_back(iph.bxNum()-1);
            }
            else
            {
                ltTwinMuxIn_bx.push_back(iph.bxNum());
            }
            
            ltTwinMuxIn_phi.push_back(iph.phi());
            ltTwinMuxIn_iPhi.push_back(getIphiFromPhDigi(iph));
            ltTwinMuxIn_phiB.push_back(iph.phiB());
            ltTwinMuxIn_is2nd.push_back(iph.Ts2Tag());
            
            ltTwinMuxIn_n++;
        }
    }
    
    printf("Number of ltTwinMuxIn = %d / %d \n", ltTwinMuxIn_n, (int) phTrigs->size());
}


int Test_1::getIphiFromPhDigi(L1MuDTChambPhDigi digi_L1MuDTChambPh)
{
    double phiGlobal = digi_L1MuDTChambPh.phi() / 4096.0;
    phiGlobal += 2.0*M_PI/12.0 * (digi_L1MuDTChambPh.scNum() - 1);
    
    if(phiGlobal > M_PI)
    {
        phiGlobal -= 2*M_PI;
    }
    
    // Segmentation is 0.087
    double dPhi = 2.0*M_PI / 72.0;
    
    if(phiGlobal < 0)
    {
        phiGlobal += 2*M_PI;
    }
    
    int iPhi = (int) (phiGlobal/dPhi + 1);
    
    return iPhi;
}


void Test_1::fill_twinmuxth_variables(edm::Handle<L1MuDTChambThContainer> localTriggerTwinMux_Th)
{
    const std::vector<L1MuDTChambThDigi> *thTrigs = localTriggerTwinMux_Th->getContainer();
    
    for(unsigned int iDigi = 0; iDigi < thTrigs->size(); iDigi++)
    {
        L1MuDTChambThDigi ith = thTrigs->at(iDigi);
        
        ltTwinMux_thWheel.push_back(ith.whNum());
        ltTwinMux_thSector.push_back(ith.scNum() + 1); // DTTF[0-11] -> DT[1-12] Sector Numbering
        ltTwinMux_thStation.push_back(ith.stNum());
        ltTwinMux_thBx.push_back(ith.bxNum());
        
        unsigned short int thcode = 0;
        for (int pos = 0; pos < 7; pos++)
        {    
            if(ith.code(pos))
            {
                thcode = thcode | (0x1<<pos);
            }
        }
        
        ltTwinMux_thHits.push_back(thcode);
        ltTwinMux_thIeta.push_back(getIetaFromSegment(ith));
        
        ltTwinMux_thN++;
    }
    
    printf("Number of ltTwinMux_th = %d / %d \n", ltTwinMux_thN, (int) thTrigs->size());
}


int Test_1::getIetaFromSegment(L1MuDTChambThDigi digi_L1MuDTChambTh)
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


void Test_1::fill_hoTP_variables(edm::Handle <edm::SortedCollection <HOTriggerPrimitiveDigi> > hotpHandle)
{
    for(edm::SortedCollection <HOTriggerPrimitiveDigi, \
        edm::StrictWeakOrdering <HOTriggerPrimitiveDigi> >::const_iterator hoTP = hotpHandle->begin();
        hoTP != hotpHandle->end(); ++hoTP)
    {
        if(!hoTP->bits())
        {
            continue;
        }
        
        hoTPdigi_n++;
        
        hoTPdigi_bits.push_back(hoTP->bits());
        hoTPdigi_iEta.push_back(hoTP->ieta());
        hoTPdigi_iPhi.push_back(hoTP->iphi());
        hoTPdigi_nSamples.push_back(hoTP->nsamples());
        hoTPdigi_raw.push_back(hoTP->raw());
        hoTPdigi_whichSampleTriggered.push_back(hoTP->whichSampleTriggered());
        
        //printf("hoTPdigi %d: bits %d, whSamp %d, data(whSamp) %d, mip %d \n", \
            hoTPdigi_n, \
            hoTP->bits(), \
            hoTP->whichSampleTriggered(), \
            hoTP->data(hoTP->whichSampleTriggered()), \
            (hoTP->bits()>>hoTP->whichSampleTriggered())&0x1);
    }
    
    printf("Number of HOTPs = %d \n", hoTPdigi_n);
}


void Test_1::clear()
{
    hoTPdigi_n = 0;
    hoTPdigi_bits.clear();
    hoTPdigi_iEta.clear();
    hoTPdigi_iPhi.clear();
    hoTPdigi_nSamples.clear();
    hoTPdigi_raw.clear();
    hoTPdigi_whichSampleTriggered.clear();
    
    segm4D_n = 0;
    segm4D_wheel.clear();
    segm4D_sector.clear();
    segm4D_station.clear();
    segm4D_hasPhi.clear();
    segm4D_hasZed.clear();
    segm4D_x_pos_loc.clear();
    segm4D_y_pos_loc.clear();
    segm4D_z_pos_loc.clear();
    segm4D_x_dir_loc.clear();
    segm4D_y_dir_loc.clear();
    segm4D_z_dir_loc.clear();
    segm4D_cosx.clear();
    segm4D_cosy.clear();
    segm4D_cosz.clear();
    segm4D_phi.clear();
    segm4D_theta.clear();
    segm4D_eta.clear();
    segm4D_t0.clear();
    segm4D_vdrift.clear();
    segm4D_phinormchi2.clear();
    segm4D_phinhits.clear();
    segm4D_znormchi2.clear();
    segm4D_znhits.clear();
    
    ltTwinMuxIn_n = 0;
    ltTwinMuxIn_wheel.clear();
    ltTwinMuxIn_sector.clear();
    ltTwinMuxIn_station.clear();
    ltTwinMuxIn_quality.clear();
    ltTwinMuxIn_bx.clear();
    ltTwinMuxIn_phi.clear();
    ltTwinMuxIn_iPhi.clear();
    ltTwinMuxIn_phiB.clear();
    ltTwinMuxIn_is2nd.clear();
    
    ltTwinMuxOut_n = 0;
    ltTwinMuxOut_wheel.clear();
    ltTwinMuxOut_sector.clear();
    ltTwinMuxOut_station.clear();
    ltTwinMuxOut_quality.clear();
    ltTwinMuxOut_rpcbit.clear();
    ltTwinMuxOut_bx.clear();
    ltTwinMuxOut_phi.clear();
    ltTwinMuxOut_iPhi.clear();
    ltTwinMuxOut_phiB.clear();
    ltTwinMuxOut_is2nd.clear();
    
    ltTwinMux_thN = 0;
    ltTwinMux_thWheel.clear();
    ltTwinMux_thSector.clear();
    ltTwinMux_thStation.clear();
    ltTwinMux_thBx.clear();
    ltTwinMux_thHits.clear();
    ltTwinMux_thIeta.clear();
}

//define this as a plug-in
DEFINE_FWK_MODULE(Test_1);
