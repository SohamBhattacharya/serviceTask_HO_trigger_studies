// -*- C++ -*-
//
// Package:    Test/TwinMuxTest
// Class:      TwinMuxTest
// 
/**\class TwinMuxTest TwinMuxTest.cc Test/TwinMuxTest/plugins/TwinMuxTest.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  
//         Created:  Tue, 18 Apr 2017 14:19:50 GMT
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/L1TMuon/interface/RegionalMuonCand.h"

//
// class declaration
//

// If the analyzer does not use TFileService, please remove
// the template argument to the base class so the class inherits
// from  edm::one::EDAnalyzer<> and also remove the line from
// constructor "usesResource("TFileService");"
// This will improve performance in multithreaded jobs.

class TwinMuxTest : public edm::one::EDAnalyzer<edm::one::SharedResources>
{
    public:
    
    explicit TwinMuxTest(const edm::ParameterSet&);
    ~TwinMuxTest();
    
    static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
    
    
    private:
    
    virtual void beginJob() override;
    virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
    virtual void endJob() override;

    // ----------member data ---------------------------
    
    edm::EDGetTokenT <l1t::RegionalMuonCandBxCollection> tok_gmtStage2Digis;
    edm::EDGetTokenT <l1t::RegionalMuonCandBxCollection> tok_bmtfDigis;
    edm::EDGetTokenT <l1t::RegionalMuonCandBxCollection> tok_simBmtfDigis;
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
TwinMuxTest::TwinMuxTest(const edm::ParameterSet& iConfig)
{
    //now do what ever initialization is needed
    usesResource("TFileService");
    
    tok_gmtStage2Digis = consumes <l1t::RegionalMuonCandBxCollection> (edm::InputTag("gmtStage2Digis", "BMTF"));
    tok_bmtfDigis = consumes <l1t::RegionalMuonCandBxCollection> (edm::InputTag("bmtfDigis", "BMTF"));
    tok_simBmtfDigis = consumes <l1t::RegionalMuonCandBxCollection> (edm::InputTag("simBmtfDigis", "BMTF"));
    
}


TwinMuxTest::~TwinMuxTest()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void TwinMuxTest::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
    using namespace edm;
    
    edm::Handle <l1t::RegionalMuonCandBxCollection> handle_gmtStage2Digis;
    iEvent.getByToken(tok_gmtStage2Digis, handle_gmtStage2Digis);
    
    edm::Handle <l1t::RegionalMuonCandBxCollection> handle_bmtfDigis;
    iEvent.getByToken(tok_bmtfDigis, handle_bmtfDigis);
    
    edm::Handle <l1t::RegionalMuonCandBxCollection> handle_simBmtfDigis;
    iEvent.getByToken(tok_simBmtfDigis, handle_simBmtfDigis);
    
    int count;
    
    count = 0;
    
    for(l1t::RegionalMuonCandBxCollection::const_iterator muonCand = handle_gmtStage2Digis->begin(); \
        muonCand != handle_gmtStage2Digis->end(); ++muonCand)
    {
        double ptTrack = muonCand->hwPt() * 0.5;
        double etaTrack = muonCand->hwEta() * 0.010875;
        double phiTrack = muonCand->hwPhi() * 2.0 * M_PI / 576.0;
        
        count++;
        
        printf("gmtStage2Digis %d %f %f %f \n", count, ptTrack, etaTrack, phiTrack);
    }
    
    printf("\n");
    count = 0;
    
    for(l1t::RegionalMuonCandBxCollection::const_iterator muonCand = handle_bmtfDigis->begin(); \
        muonCand != handle_bmtfDigis->end(); ++muonCand)
    {
        double ptTrack = muonCand->hwPt() * 0.5;
        double etaTrack = muonCand->hwEta() * 0.010875;
        double phiTrack = muonCand->hwPhi() * 2.0 * M_PI / 576.0;
        
        count++;
        
        printf("bmtfDigis %d %f %f %f \n", count, ptTrack, etaTrack, phiTrack);
    }
    
    printf("\n");
    count = 0;
    
    for(l1t::RegionalMuonCandBxCollection::const_iterator muonCand = handle_simBmtfDigis->begin(); \
        muonCand != handle_simBmtfDigis->end(); ++muonCand)
    {
        double ptTrack = muonCand->hwPt() * 0.5;
        double etaTrack = muonCand->hwEta() * 0.010875;
        double phiTrack = muonCand->hwPhi() * 2.0 * M_PI / 576.0;
        
        count++;
        
        printf("simBmtfDigis %d %f %f %f \n", count, ptTrack, etaTrack, phiTrack);
    }
    
    printf("xxxxxxxxxx \n");
}


// ------------ method called once each job just before starting event loop  ------------
void 
TwinMuxTest::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
TwinMuxTest::endJob() 
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
TwinMuxTest::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(TwinMuxTest);
