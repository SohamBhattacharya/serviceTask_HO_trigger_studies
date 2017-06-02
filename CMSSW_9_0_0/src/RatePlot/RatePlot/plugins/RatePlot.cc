// -*- C++ -*-
//
// Package:    RatePlot/RatePlot
// Class:      RatePlot
// 
/**\class RatePlot RatePlot.cc RatePlot/RatePlot/plugins/RatePlot.cc

 Description: [one line class summary]

 Implementation:
 [Notes on implementation]
 */
//
// Original Author:  Florian Scheuch
//         Created:  Thu, 08 Dec 2016 11:51:02 GMT
//
//
/*
 ++Event    21 contains 178 products with friendlyClassName, moduleLabel, productInstanceName and processName:
 ++BeamSpotOnlines "scalersRawToDigi" "" "RECO" (productId = 2:1)
 ++CSCDetIdCSCALCTDigiMuonDigiCollection "muonCSCDigis" "MuonCSCALCTDigi" "RECO" (productId = 2:2)
 ++CSCDetIdCSCCLCTDigiMuonDigiCollection "muonCSCDigis" "MuonCSCCLCTDigi" "RECO" (productId = 2:3)
 ++CSCDetIdCSCComparatorDigiMuonDigiCollection "muonCSCDigis" "MuonCSCComparatorDigi" "RECO" (productId = 2:4)
 ++CSCDetIdCSCCorrelatedLCTDigiMuonDigiCollection "csctfDigis" "" "RECO" (productId = 2:5)
 ++CSCDetIdCSCCorrelatedLCTDigiMuonDigiCollection "muonCSCDigis" "MuonCSCCorrelatedLCTDigi" "RECO" (productId = 2:6)
 ++CSCDetIdCSCDCCFormatStatusDigiMuonDigiCollection "muonCSCDigis" "MuonCSCDCCFormatStatusDigi" "RECO" (productId = 2:7)
 ++CSCDetIdCSCRPCDigiMuonDigiCollection "muonCSCDigis" "MuonCSCRPCDigi" "RECO" (productId = 2:8)
 ++CSCDetIdCSCStripDigiMuonDigiCollection "muonCSCDigis" "MuonCSCStripDigi" "RECO" (productId = 2:9)
 ++CSCDetIdCSCWireDigiMuonDigiCollection "muonCSCDigis" "MuonCSCWireDigi" "RECO" (productId = 2:10)
 ++CastorDataFramesSorted "castorDigis" "" "RECO" (productId = 2:11)
 ++CastorTriggerPrimitiveDigisSorted "castorDigis" "" "RECO" (productId = 2:12)
 ++DTChamberIdDTLocalTriggerMuonDigiCollection "muonDTDigis" "" "RECO" (productId = 2:13)
 ++DTLayerIdDTDigiMuonDigiCollection "muonDTDigis" "" "RECO" (productId = 2:14)
 ++DcsStatuss "scalersRawToDigi" "" "RECO" (productId = 2:15)
 ++DetIdedmEDCollection "siPixelDigis" "" "RECO" (productId = 2:16)
 ++DetIdedmEDCollection "siPixelDigis" "UserErrorModules" "RECO" (productId = 2:17)
 ++DetIdedmEDCollection "siStripDigis" "" "RECO" (productId = 2:18)
 ++EBDetIdedmEDCollection "ecalDigis" "EcalIntegrityChIdErrors" "RECO" (productId = 2:19)
 ++EBDetIdedmEDCollection "ecalDigis" "EcalIntegrityGainErrors" "RECO" (productId = 2:20)
 ++EBDetIdedmEDCollection "ecalDigis" "EcalIntegrityGainSwitchErrors" "RECO" (productId = 2:21)
 ++EBDigiCollection "ecalDigis" "ebDigis" "RECO" (productId = 2:22)
 ++EBSrFlagsSorted "ecalDigis" "" "RECO" (productId = 2:23)
 ++EEDetIdedmEDCollection "ecalDigis" "EcalIntegrityChIdErrors" "RECO" (productId = 2:24)
 ++EEDetIdedmEDCollection "ecalDigis" "EcalIntegrityGainErrors" "RECO" (productId = 2:25)
 ++EEDetIdedmEDCollection "ecalDigis" "EcalIntegrityGainSwitchErrors" "RECO" (productId = 2:26)
 ++EEDigiCollection "ecalDigis" "eeDigis" "RECO" (productId = 2:27)
 ++EESrFlagsSorted "ecalDigis" "" "RECO" (productId = 2:28)
 ++ESDCCHeaderBlocksSorted "ecalPreshowerDigis" "" "RECO" (productId = 2:29)
 ++ESDigiCollection "ecalPreshowerDigis" "" "RECO" (productId = 2:30)
 ++ESKCHIPBlocksSorted "ecalPreshowerDigis" "" "RECO" (productId = 2:31)
 ++EcalDCCHeaderBlocksSorted "ecalDigis" "" "RECO" (productId = 2:32)
 ++EcalElectronicsIdedmEDCollection "ecalDigis" "EcalIntegrityBlockSizeErrors" "RECO" (productId = 2:33)
 ++EcalElectronicsIdedmEDCollection "ecalDigis" "EcalIntegrityMemBlockSizeErrors" "RECO" (productId = 2:34)
 ++EcalElectronicsIdedmEDCollection "ecalDigis" "EcalIntegrityMemChIdErrors" "RECO" (productId = 2:35)
 ++EcalElectronicsIdedmEDCollection "ecalDigis" "EcalIntegrityMemGainErrors" "RECO" (productId = 2:36)
 ++EcalElectronicsIdedmEDCollection "ecalDigis" "EcalIntegrityMemTtIdErrors" "RECO" (productId = 2:37)
 ++EcalElectronicsIdedmEDCollection "ecalDigis" "EcalIntegrityTTIdErrors" "RECO" (productId = 2:38)
 ++EcalElectronicsIdedmEDCollection "ecalDigis" "EcalIntegrityZSXtalIdErrors" "RECO" (productId = 2:39)
 ++EcalPnDiodeDigisSorted "ecalDigis" "" "RECO" (productId = 2:40)
 ++EcalPseudoStripInputDigisSorted "ecalDigis" "EcalPseudoStripInputs" "RECO" (productId = 2:41)
 ++EcalTriggerPrimitiveDigisSorted "ecalDigis" "EcalTriggerPrimitives" "RECO" (productId = 2:42)
 ++FEDRawDataCollection "rawDataCollector" "" "LHC" (productId = 0:0)
 ++GlobalAlgBlkBXVector "gtStage2Digis" "" "RECO" (productId = 2:43)
 ++GlobalExtBlkBXVector "gtStage2Digis" "" "RECO" (productId = 2:44)
 ++GlobalObjectMapRecord "hltGtStage2ObjectMap" "" "HLT" (productId = 1:79)
 ++HBHEDataFramesSorted "hcalDigis" "" "RECO" (productId = 2:45)
 ++HFDataFramesSorted "hcalDigis" "" "RECO" (productId = 2:46)
 ++HODataFramesSorted "hcalDigis" "" "RECO" (productId = 2:47)
 ++HOTriggerPrimitiveDigisSorted "hcalDigis" "" "RECO" (productId = 2:48)
 ++HcalCalibDataFramesSorted "hcalDigis" "" "RECO" (productId = 2:49)
 ++HcalTTPDigisSorted "castorDigis" "" "RECO" (productId = 2:50)
 ++HcalTTPDigisSorted "hcalDigis" "" "RECO" (productId = 2:51)
 ++HcalTriggerPrimitiveDigisSorted "hcalDigis" "" "RECO" (productId = 2:52)
 ++HcalUnpackerReport "castorDigis" "" "RECO" (productId = 2:53)
 ++HcalUnpackerReport "hcalDigis" "" "RECO" (productId = 2:54)
 ++L1AcceptBunchCrossings "scalersRawToDigi" "" "RECO" (productId = 2:55)
 ++L1CaloEmCands "caloStage1Digis" "" "RECO" (productId = 2:56)
 ++L1CaloEmCands "gctDigis" "" "RECO" (productId = 2:57)
 ++L1CaloRegions "caloStage1Digis" "" "RECO" (productId = 2:58)
 ++L1CaloRegions "gctDigis" "" "RECO" (productId = 2:59)
 ++L1GctEmCands "caloStage1LegacyFormatDigis" "isoEm" "RECO" (productId = 2:60)
 ++L1GctEmCands "caloStage1LegacyFormatDigis" "nonIsoEm" "RECO" (productId = 2:61)
 ++L1GctEmCands "gctDigis" "isoEm" "RECO" (productId = 2:62)
 ++L1GctEmCands "gctDigis" "nonIsoEm" "RECO" (productId = 2:63)
 ++L1GctEtHads "caloStage1LegacyFormatDigis" "" "RECO" (productId = 2:64)
 ++L1GctEtHads "gctDigis" "" "RECO" (productId = 2:65)
 ++L1GctEtMisss "caloStage1LegacyFormatDigis" "" "RECO" (productId = 2:66)
 ++L1GctEtMisss "gctDigis" "" "RECO" (productId = 2:67)
 ++L1GctEtTotals "caloStage1LegacyFormatDigis" "" "RECO" (productId = 2:68)
 ++L1GctEtTotals "gctDigis" "" "RECO" (productId = 2:69)
 ++L1GctFibreWords "gctDigis" "" "RECO" (productId = 2:70)
 ++L1GctHFBitCountss "caloStage1LegacyFormatDigis" "" "RECO" (productId = 2:71)
 ++L1GctHFBitCountss "gctDigis" "" "RECO" (productId = 2:72)
 ++L1GctHFRingEtSumss "caloStage1LegacyFormatDigis" "" "RECO" (productId = 2:73)
 ++L1GctHFRingEtSumss "gctDigis" "" "RECO" (productId = 2:74)
 ++L1GctHtMisss "caloStage1LegacyFormatDigis" "" "RECO" (productId = 2:75)
 ++L1GctHtMisss "gctDigis" "" "RECO" (productId = 2:76)
 ++L1GctInternEmCands "gctDigis" "" "RECO" (productId = 2:77)
 ++L1GctInternEtSums "caloStage1LegacyFormatDigis" "" "RECO" (productId = 2:78)
 ++L1GctInternEtSums "gctDigis" "" "RECO" (productId = 2:79)
 ++L1GctInternHFDatas "gctDigis" "" "RECO" (productId = 2:80)
 ++L1GctInternHtMisss "caloStage1LegacyFormatDigis" "" "RECO" (productId = 2:81)
 ++L1GctInternHtMisss "gctDigis" "" "RECO" (productId = 2:82)
 ++L1GctInternJetDatas "caloStage1LegacyFormatDigis" "" "RECO" (productId = 2:83)
 ++L1GctInternJetDatas "gctDigis" "" "RECO" (productId = 2:84)
 ++L1GctJetCands "caloStage1LegacyFormatDigis" "cenJets" "RECO" (productId = 2:85)
 ++L1GctJetCands "caloStage1LegacyFormatDigis" "forJets" "RECO" (productId = 2:86)
 ++L1GctJetCands "caloStage1LegacyFormatDigis" "isoTauJets" "RECO" (productId = 2:87)
 ++L1GctJetCands "caloStage1LegacyFormatDigis" "tauJets" "RECO" (productId = 2:88)
 ++L1GctJetCands "gctDigis" "cenJets" "RECO" (productId = 2:89)
 ++L1GctJetCands "gctDigis" "forJets" "RECO" (productId = 2:90)
 ++L1GctJetCands "gctDigis" "tauJets" "RECO" (productId = 2:91)
 ++L1GctJetCountss "gctDigis" "" "RECO" (productId = 2:92)
 ++L1GlobalTriggerReadoutRecord "gtDigis" "" "RECO" (productId = 2:93)
 ++L1MuDTChambPhContainer "bmtfDigis" "" "RECO" (productId = 2:94)
 ++L1MuDTChambPhContainer "dttfDigis" "" "RECO" (productId = 2:95)
 ++L1MuDTChambThContainer "bmtfDigis" "" "RECO" (productId = 2:96)
 ++L1MuDTChambThContainer "dttfDigis" "" "RECO" (productId = 2:97)
 ++L1MuDTTrackContainer "dttfDigis" "DATA" "RECO" (productId = 2:98)
 ++L1MuGMTCands "gtDigis" "" "RECO" (productId = 2:99)
 ++L1MuGMTReadoutCollection "gtDigis" "" "RECO" (productId = 2:100)
 ++L1MuRegionalCands "gtDigis" "CSC" "RECO" (productId = 2:101)
 ++L1MuRegionalCands "gtDigis" "DT" "RECO" (productId = 2:102)
 ++L1MuRegionalCands "gtDigis" "RPCb" "RECO" (productId = 2:103)
 ++L1MuRegionalCands "gtDigis" "RPCf" "RECO" (productId = 2:104)
 ++L1TriggerErrors "gctDigis" "" "RECO" (productId = 2:105)
 ++L1TriggerScalerss "scalersRawToDigi" "" "RECO" (productId = 2:106)
 ++Level1TriggerScalerss "scalersRawToDigi" "" "RECO" (productId = 2:107)
 ++LinkBoardElectronicIndexintstdpairs "muonRPCDigis" "" "RECO" (productId = 2:108)
 ++LumiScalerss "scalersRawToDigi" "" "RECO" (productId = 2:109)
 ++PixelDigiedmDetSetVector "siPixelDigis" "" "RECO" (productId = 2:110)
 ++QIE10DataFrameHcalDataFrameContainer "hcalDigis" "" "RECO" (productId = 2:111)
 ++QIE11DataFrameHcalDataFrameContainer "hcalDigis" "" "RECO" (productId = 2:112)
 ++RPCDetIdRPCDigiMuonDigiCollection "muonRPCDigis" "" "RECO" (productId = 2:113)
 ++RPCRawDataCounts "muonRPCDigis" "" "RECO" (productId = 2:114)
 ++SiPixelRawDataErroredmDetSetVector "siPixelDigis" "" "RECO" (productId = 2:115)
 ++SiStripDigiedmDetSetVector "siStripDigis" "ZeroSuppressed" "RECO" (productId = 2:116)
 ++SiStripEventSummary "siStripDigis" "" "RECO" (productId = 2:117)
 ++SiStripRawDigiedmDetSetVector "siStripDigis" "ProcessedRaw" "RECO" (productId = 2:118)
 ++SiStripRawDigiedmDetSetVector "siStripDigis" "ScopeMode" "RECO" (productId = 2:119)
 ++SiStripRawDigiedmDetSetVector "siStripDigis" "VirginRaw" "RECO" (productId = 2:120)
 ++TotemFEDInfos "totemRPRawToDigi" "RP" "RECO" (productId = 2:121)
 ++TotemRPDigiedmDetSetVector "totemRPRawToDigi" "RP" "RECO" (productId = 2:122)
 ++TotemTriggerCounters "totemTriggerRawToDigi" "" "RECO" (productId = 2:123)
 ++TotemVFATStatusedmDetSetVector "totemRPRawToDigi" "RP" "RECO" (productId = 2:124)
 ++ZDCDataFramesSorted "hcalDigis" "" "RECO" (productId = 2:125)
 ++cscL1TrackCSCDetIdCSCCorrelatedLCTDigiMuonDigiCollectionstdpairs "csctfDigis" "" "RECO" (productId = 2:126)
 ++csctfTrackStubCSCTriggerContainer "csctfDigis" "DT" "RECO" (productId = 2:127)
 ++edmTriggerResults "TriggerResults" "" "HLT" (productId = 1:190)
 ++int "tcdsDigis" "nibble" "RECO" (productId = 2:129)
 ++intL1CSCSPStatusDigisstdpair "csctfDigis" "" "RECO" (productId = 2:130)
 ++l1extraL1EmParticles "l1extraParticles" "Isolated" "RECO" (productId = 2:131)
 ++l1extraL1EmParticles "l1extraParticles" "NonIsolated" "RECO" (productId = 2:132)
 ++l1extraL1EtMissParticles "l1extraParticles" "MET" "RECO" (productId = 2:133)
 ++l1extraL1EtMissParticles "l1extraParticles" "MHT" "RECO" (productId = 2:134)
 ++l1extraL1HFRingss "l1extraParticles" "" "RECO" (productId = 2:135)
 ++l1extraL1JetParticles "l1extraParticles" "Central" "RECO" (productId = 2:136)
 ++l1extraL1JetParticles "l1extraParticles" "Forward" "RECO" (productId = 2:137)
 ++l1extraL1JetParticles "l1extraParticles" "IsoTau" "RECO" (productId = 2:138)
 ++l1extraL1JetParticles "l1extraParticles" "Tau" "RECO" (productId = 2:139)
 ++l1extraL1MuonParticles "l1extraParticles" "" "RECO" (productId = 2:140)
 ++l1tCaloSpareBXVector "caloStage1Digis" "HFBitCounts" "RECO" (productId = 2:141)
 ++l1tCaloSpareBXVector "caloStage1Digis" "HFRingSums" "RECO" (productId = 2:142)
 ++l1tCaloSpareBXVector "caloStage1FinalDigis" "HFBitCounts" "RECO" (productId = 2:143)
 ++l1tCaloSpareBXVector "caloStage1FinalDigis" "HFRingSums" "RECO" (productId = 2:144)
 ++l1tCaloTowerBXVector "caloStage1Digis" "" "RECO" (productId = 2:145)
 ++l1tCaloTowerBXVector "caloStage2Digis" "CaloTower" "RECO" (productId = 2:146)
 ++l1tEGammaBXVector "caloStage1Digis" "" "RECO" (productId = 2:147)
 ++l1tEGammaBXVector "caloStage1FinalDigis" "" "RECO" (productId = 2:148)
 ++l1tEGammaBXVector "caloStage2Digis" "EGamma" "RECO" (productId = 2:149)
 ++l1tEGammaBXVector "caloStage2Digis" "MP" "RECO" (productId = 2:150)
 ++l1tEGammaBXVector "gtStage2Digis" "EGamma" "RECO" (productId = 2:151)
 ++l1tEtSumBXVector "caloStage1Digis" "" "RECO" (productId = 2:152)
 ++l1tEtSumBXVector "caloStage1FinalDigis" "" "RECO" (productId = 2:153)
 ++l1tEtSumBXVector "caloStage2Digis" "EtSum" "RECO" (productId = 2:154)
 ++l1tEtSumBXVector "caloStage2Digis" "MP" "RECO" (productId = 2:155)
 ++l1tEtSumBXVector "gtStage2Digis" "EtSum" "RECO" (productId = 2:156)
 ++l1tJetBXVector "caloStage1Digis" "" "RECO" (productId = 2:157)
 ++l1tJetBXVector "caloStage1FinalDigis" "" "RECO" (productId = 2:158)
 ++l1tJetBXVector "caloStage1FinalDigis" "preGtJets" "RECO" (productId = 2:159)
 ++l1tJetBXVector "caloStage2Digis" "Jet" "RECO" (productId = 2:160)
 ++l1tJetBXVector "caloStage2Digis" "MP" "RECO" (productId = 2:161)
 ++l1tJetBXVector "gtStage2Digis" "Jet" "RECO" (productId = 2:162)
 ++l1tMuonBXVector "gmtStage2Digis" "Muon" "RECO" (productId = 2:163)
 ++l1tMuonBXVector "gtStage2Digis" "Muon" "RECO" (productId = 2:164)
 ++l1tRegionalMuonCandBXVector "bmtfDigis" "BMTF" "RECO" (productId = 2:165)
 ++l1tRegionalMuonCandBXVector "gmtStage2Digis" "BMTF" "RECO" (productId = 2:166)
 ++l1tRegionalMuonCandBXVector "gmtStage2Digis" "EMTF" "RECO" (productId = 2:167)
 ++l1tRegionalMuonCandBXVector "gmtStage2Digis" "OMTF" "RECO" (productId = 2:168)
 ++l1tTauBXVector "caloStage1Digis" "isoTaus" "RECO" (productId = 2:169)
 ++l1tTauBXVector "caloStage1Digis" "rlxTaus" "RECO" (productId = 2:170)
 ++l1tTauBXVector "caloStage1FinalDigis" "isoTaus" "RECO" (productId = 2:171)
 ++l1tTauBXVector "caloStage1FinalDigis" "rlxTaus" "RECO" (productId = 2:172)
 ++l1tTauBXVector "caloStage2Digis" "MP" "RECO" (productId = 2:173)
 ++l1tTauBXVector "caloStage2Digis" "Tau" "RECO" (productId = 2:174)
 ++l1tTauBXVector "gtStage2Digis" "Tau" "RECO" (productId = 2:175)
 ++triggerTriggerEvent "hltTriggerSummaryAOD" "" "HLT" (productId = 1:293)

 */

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

#include "Geometry/DTGeometry/interface/DTGeometry.h"
#include "Geometry/CaloGeometry/interface/CaloGeometry.h"
#include "Geometry/Records/interface/MuonGeometryRecord.h"
#include "Geometry/Records/interface/CaloGeometryRecord.h"

#include "TH1D.h"
#include "TH2D.h"
//
// class declaration
//

// If the analyzer does not use TFileService, please remove
// the template argument to the base class so the class inherits
// from  edm::one::EDAnalyzer<> and also remove the line from
// constructor "usesResource("TFileService");"
// This will improve performance in multithreaded jobs.

class RatePlot: public edm::one::EDAnalyzer<edm::one::SharedResources> {
public:
	explicit RatePlot(const edm::ParameterSet&);
	~RatePlot();

	static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

private:
	virtual void beginJob() override;
	virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
	virtual void endJob() override;
	virtual int getIEta(double eta);
	virtual int getIPhi(double phi);
	virtual double getPt(L1MuDTChambPhDigi kDigi);
	virtual double getEtaFromSegment(L1MuDTChambThDigi kDigi);
	virtual bool isInWheel(int ieta, int wheel);
	virtual double getPUFromLumiSection(int lumiSec);
	virtual void parseCSV();
	edm::EDGetTokenT<L1MuDTChambPhContainer> chambPhi_token;
	edm::EDGetTokenT<L1MuDTChambThContainer> chambThe_token;
	edm::EDGetTokenT<L1MuDTTrackContainer> dttfTrack_token;
	edm::EDGetTokenT<
			edm::SortedCollection<HOTriggerPrimitiveDigi,
					edm::StrictWeakOrdering<HOTriggerPrimitiveDigi>> > ho_token;
	edm::EDGetTokenT<l1t::RegionalMuonCandBxCollection> bmtfToken;

	TH1D* eventsPerPileUp;
	TH1D* phiOfDigis;
	TH1D* phiBOfDigis;
	TH1D* codeDigis;
	TH1D* addTracks;
	TH1D* bmtfTracks;
	TH1D* addTrackssecond;
	TH1D* bmtfTrackssecond;

	TH2D* addTracks2d;
	TH2D* bmtfTracks2d;
	TH2D* addTracks2dsecond;
	TH2D* bmtfTracks2dsecond;
	TH2D* phiOfDigisVSphiBOfDigis;

	vector<int> lumiSection;
	vector<double> pileUp;

	// ----------member data ---------------------------
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
RatePlot::RatePlot(const edm::ParameterSet& iConfig)

{
	//now do what ever initialization is needed
	usesResource("TFileService");
	std::string labelchambPhi_("bmtfDigis");
	std::string labelchambThe_("bmtfDigis");
	std::string labelHOdigi_("hcalDigis");
	chambPhi_token = consumes < L1MuDTChambPhContainer
			> (edm::InputTag(labelchambPhi_));
	chambThe_token = consumes < L1MuDTChambThContainer
			> (edm::InputTag(labelchambThe_));
	ho_token = consumes
			< edm::SortedCollection<HOTriggerPrimitiveDigi,
					edm::StrictWeakOrdering<HOTriggerPrimitiveDigi>>
			> (edm::InputTag(labelHOdigi_));

	dttfTrack_token = consumes < L1MuDTTrackContainer
			> (edm::InputTag("dttfDigis", "DATA"));
	bmtfToken = consumes < l1t::RegionalMuonCandBxCollection
			> (edm::InputTag("gmtStage2Digis", "BMTF"));
}

RatePlot::~RatePlot() {

	// do anything here that needs to be done at desctruction time
	// (e.g. close files, deallocate resources etc.)

}
//++HODataFramesSorted "hcalDigis" "" "RECO" (productId = 2:99)
//++HORecHitsSorted "horeco" "" "RECO" (productId = 2:100)
//++HORecHitsSorted "reducedHcalRecHits" "horeco" "RECO" (productId = 2:101)
//++HOTriggerPrimitiveDigisSorted "hcalDigis" "" "RECO" (productId = 2:102)
//++L1MuDTChambPhContainer "bmtfDigis" "" "RECO" (productId = 2:94)
//++L1MuDTChambPhContainer "dttfDigis" "" "RECO" (productId = 2:95)
//++L1MuDTChambThContainer "bmtfDigis" "" "RECO" (productId = 2:96)
//++L1MuDTChambThContainer "dttfDigis" "" "RECO" (productId = 2:97)
//++L1MuDTTrackContainer "dttfDigis" "DATA" "RECO" (productId = 2:98)
//++l1extraL1MuonParticles "l1extraParticles" "" "RECO" (productId = 2:140)

//
// member functions
//

// ------------ method called for each event  ------------
void RatePlot::analyze(const edm::Event& iEvent,
		const edm::EventSetup& iSetup) {
	using namespace edm;
	edm::ESHandle < DTGeometry > dtGeometry;
	iSetup.get<MuonGeometryRecord>().get(dtGeometry);

	edm::ESHandle < CaloGeometry > caloGeometry;
	iSetup.get<CaloGeometryRecord>().get(caloGeometry);

	edm::Handle < edm::SortedCollection
			< HOTriggerPrimitiveDigi >> hoPrimitivesHandle;
	iEvent.getByToken(ho_token, hoPrimitivesHandle);

	edm::Handle < l1t::RegionalMuonCandBxCollection > bmtfHandle;
	iEvent.getByToken(bmtfToken, bmtfHandle);

	edm::Handle < L1MuDTChambPhContainer > phiPrimitivesHandle;
	iEvent.getByToken(chambPhi_token, phiPrimitivesHandle);

	edm::Handle < L1MuDTChambThContainer > thePrimitivesHandle;
	iEvent.getByToken(chambThe_token, thePrimitivesHandle);
//   	
	edm::Handle < L1MuDTTrackContainer > dttfTrackHandle;
	iEvent.getByToken(dttfTrack_token, dttfTrackHandle);

	/*
	 edm::Handle
	 < edm::SortedCollection<HORecHit, edm::StrictWeakOrdering<HORecHit>>
	 > hoCollection;
	 iEvent.getByLabel("horeco", hoCollection);
	 
	 
	 iEvent.getByLabel("dttfunpacker", "DATA", dttfTrackHandle);
	 */

	const L1MuDTChambPhContainer::Phi_Container* digis =
			phiPrimitivesHandle->getContainer();

//	const L1MuDTChambThContainer::The_Container* thDigis =
//			thePrimitivesHandle->getContainer();

	double PU =
			getPUFromLumiSection(
					iEvent.getLuminosityBlock().luminosityBlockAuxiliary().luminosityBlock());
	eventsPerPileUp->Fill(PU);

	double highestPtHO = -1;
	double highestPtBMTF = -1;

	double secondHighestPtHO = -1;
	double secondHighestPtBMTF = -1;

	for (unsigned int k = 0; k < digis->size(); k++) {
		L1MuDTChambPhDigi kDigi = digis->at(k);

		if (kDigi.code() < 7 && kDigi.code() > 0) {
			if (kDigi.stNum() != 1)
				continue;
//			std::cout << "Wheel: " << kDigi.whNum() << std::endl;
//			std::cout << "Sector: " << kDigi.scNum() << std::endl;
//			std::cout << "Station: " << kDigi.stNum() << std::endl;
//			std::cout << "Phi: " << kDigi.phi() << std::endl;
//			std::cout << "PhiB: " << kDigi.phiB() << std::endl;
//			std::cout << "Code: " << kDigi.code() << std::endl;
//			std::cout << "---------------" << std::endl;
			phiOfDigis->Fill(kDigi.phi());
			phiBOfDigis->Fill(kDigi.phiB());
			phiOfDigisVSphiBOfDigis->Fill(kDigi.phi(), kDigi.phiB());
			codeDigis->Fill(kDigi.code());

			double globalPhi = kDigi.phi() / 4096.;
			globalPhi += 3.141 / 6 * (kDigi.scNum() - 1);
			if (globalPhi > 3.141)
				globalPhi -= 3.141 * 2;

			int iphi = getIPhi(globalPhi);
//			std::cout << "iPhi: " << iphi << " pT:" << getPt(kDigi) << std::endl;
//			int ieta = -99;
//			for (unsigned int j = 0; j < thDigis->size(); j++) {
//				L1MuDTChambThDigi tDigi = thDigis->at(j);
//				if (tDigi.whNum() == kDigi.whNum()
//						&& tDigi.stNum() == kDigi.stNum()
//						&& tDigi.scNum() == kDigi.scNum()) {
//					ieta = getEtaFromSegment(tDigi);
//				}
//			}
//			if (ieta == -99)
//				continue;

			for (edm::SortedCollection<HOTriggerPrimitiveDigi,
					edm::StrictWeakOrdering<HOTriggerPrimitiveDigi>>::const_iterator it =
					hoPrimitivesHandle->begin();
					it != hoPrimitivesHandle->end(); ++it) {
				const HOTriggerPrimitiveDigi rh = *it;
				if (abs(rh.iphi() - iphi) > 1)
					continue;
				if (!isInWheel(rh.ieta(), kDigi.whNum()))
					continue;

				bool isPresent = false;

				for (l1t::RegionalMuonCandBxCollection::const_iterator it =
						bmtfHandle->begin(); it != bmtfHandle->end(); ++it) {
					const l1t::RegionalMuonCand mc = *it;
					double phiTrack = mc.hwPhi() * 2. * 3.141 / 576.;
					double etaTrack = mc.hwEta();
					int iphiTrack = getIPhi(phiTrack);
					int ietaTrack = getIEta(etaTrack);

					if ((abs(rh.iphi() - iphiTrack) < 2)
							&& ((rh.ieta() - ietaTrack) < 2))
						isPresent = true;
					//		std::cout << "BMTF: " << mc.hwPt() * 0.5 << " GeV; "
					//				<<  << " rad; "
					//				<< mc.hwEta() * 0.010875 << std::endl;
				}

				if (!isPresent) {
					if (highestPtHO < getPt(kDigi)) {
						secondHighestPtHO = highestPtHO;
						highestPtHO = getPt(kDigi);
					}
                    
                    std::cout << k << " " << highestPtHO << " " << secondHighestPtHO << "\n";
                }

				//std::cout << "New matching muon: " << getPt(kDigi) << " GeV..." << std::endl;
			}
		}
	}

	for (l1t::RegionalMuonCandBxCollection::const_iterator it =
			bmtfHandle->begin(); it != bmtfHandle->end(); ++it) {
		const l1t::RegionalMuonCand mc = *it;
		if (highestPtBMTF < mc.hwPt() * 0.5) {
			secondHighestPtBMTF = highestPtBMTF;
			highestPtBMTF = mc.hwPt() * 0.5;
		}

//		std::cout << "BMTF: " << mc.hwPt() * 0.5 << " GeV; "
//				<< mc.hwPhi() * 2. * 3.141 / 576. << " rad; "
//				<< mc.hwEta() * 0.010875 << std::endl;
	}

	if (highestPtHO > 0) {
		addTracks->Fill(highestPtHO); std::cout << "highestPtHO " << highestPtHO << "\n";
		addTracks2d->Fill(highestPtHO, PU);
	}
    if (secondHighestPtHO > 0) {
		addTrackssecond->Fill(secondHighestPtHO); std::cout << "secondHighestPtHO " << secondHighestPtHO << "\n";
		addTracks2dsecond->Fill(secondHighestPtHO, PU);
	}
    if (highestPtBMTF > 0) {
		bmtfTracks->Fill(highestPtBMTF); std::cout << "highestPtBMTF " << highestPtBMTF << "\n";
		bmtfTracks2d->Fill(highestPtBMTF, PU);
	}
	if (secondHighestPtBMTF > 0) {
		bmtfTrackssecond->Fill(secondHighestPtBMTF); std::cout << "secondHighestPtBMTF " << secondHighestPtBMTF << "\n";
		bmtfTracks2dsecond->Fill(secondHighestPtBMTF, PU);
	}
//	const L1MuDTTrackContainer::TrackContainer* tc =
//			dttfTrackHandle->getContainer();

//	std::cout << "DTTF Size: " << tc->size() << std::endl;

#ifdef THIS_IS_AN_EVENT_EXAMPLE
	Handle<ExampleData> pIn;
	iEvent.getByLabel("example",pIn);
#endif

#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
	ESHandle<SetupData> pSetup;
	iSetup.get<SetupRecord>().get(pSetup);
#endif
}

// ------------ method called once each job just before starting event loop  ------------
void RatePlot::beginJob() {
	parseCSV();

	edm::Service < TFileService > fs;
	phiOfDigis = fs->make < TH1D
			> ("Phi of DT Digis", "Phi of DT Digis", 4096, -2048, 2047);

	eventsPerPileUp = fs->make < TH1D > ("eventsPerPileUp", "eventsPerPileUp", 3000, 30, 60);
	
	addTracks = fs->make < TH1D > ("AddTracks", "AddTracks", 40, 0, 40);

	bmtfTracks = fs->make < TH1D > ("BmtfTracks", "BmtfTracks", 40, 0, 40);

	addTracks2d = fs->make < TH2D
			> ("AddTracks 2d", "AddTracks 2d", 40, 0, 40, 3000, 30, 60);

	bmtfTracks2d = fs->make < TH2D
			> ("BmtfTracks 2d", "BmtfTracks 2d", 40, 0, 40, 3000, 30, 60);

	addTrackssecond = fs->make < TH1D
			> ("AddTracks 2nd", "AddTracks 2nd", 40, 0, 40);

	bmtfTrackssecond = fs->make < TH1D
			> ("BmtfTracks 2nd", "BmtfTracks 2nd", 40, 0, 40);

	addTracks2dsecond = fs->make < TH2D
			> ("AddTracks 2d 2nd", "AddTracks 2d 2nd", 40, 0, 40, 3000, 30, 60);

	bmtfTracks2dsecond =
			fs->make < TH2D
					> ("BmtfTracks 2d 2nd", "BmtfTracks 2d 2nd", 40, 0, 40, 3000, 30, 60);

	codeDigis = fs->make < TH1D
			> ("Code of DT Digis", "Code of DT Digis", 4096, -2048, 2047);

	phiBOfDigis = fs->make < TH1D
			> ("Phi B of DT Digis", "Phi B of DT Digis", 512, -256, 255);

	phiOfDigisVSphiBOfDigis =
			fs->make < TH2D
					> ("Phi of DT Digis vs. Phi B of DT Digis", "Phi of DT Digis vs. Phi B of DT Digis", 4096, -2048, 2047, 512, -256, 255);
}

// ------------ method called once each job just after ending the event loop  ------------
void RatePlot::endJob() {
}

int RatePlot::getIPhi(double phi) {
	double val = 0;
	if (phi < 0) {
		val = 2 * 3.141 + phi;
	} else {
		val = phi;
	}
	val = val / 2. / 3.141 * 72.;
	int valInt = (int) val;
	valInt = valInt + 1;
	return valInt;
}

int RatePlot::getIEta(double eta) {
	double b = (2. * 3.141 / 72.);
	double a = eta + 15 * b;
	double c = a / b;
	int e = (int) c;
	int d = e - 15;
	if (d >= 0) {
		return d + 1;
	}
	return d;
}

bool RatePlot::isInWheel(int ieta, int wheel) {
	if (ieta < -10 && wheel == -2)
		return true;
	if ((ieta < -4 && ieta > -11) && wheel == -1)
		return true;
	if ((ieta < 5 && ieta > -5) && wheel == 0)
		return true;
	if ((ieta > 4 && ieta < 11) && wheel == 1)
		return true;
	if (ieta > 10 && wheel == 2)
		return true;
	return false;
}

double RatePlot::getEtaFromSegment(L1MuDTChambThDigi kDigi) {
	int pos = -1;
	for (int i = 0; i < 7; i++) {
//		std::cout << kDigi.code(i) << std::endl;
		if (kDigi.code(i) == 2)
			pos = i;
	}
	if (kDigi.whNum() == -2 || kDigi.whNum() == -1
			|| (kDigi.whNum() == 0
					&& (kDigi.scNum() == 0 || kDigi.scNum() == 3
							|| kDigi.scNum() == 4 || kDigi.scNum() == 7
							|| kDigi.scNum() == 8 || kDigi.scNum() == 11)))
		pos = 6 - pos;
	if (kDigi.whNum() == -2) {
		return ((int) (round((-5. / 7.) * (pos + 1) - 10)));
	}
	if (kDigi.whNum() == -1) {
		return ((int) (round((-6. / 7.) * (pos + 1) - 4)));
	}
	if (kDigi.whNum() == 0) {
		return ((int) (round((-8. / 7.) * (pos + 1) + 5)));
	}
	if (kDigi.whNum() == 1) {
		return ((int) (round((-6. / 7.) * (pos + 1) + 11)));
	}
	if (kDigi.whNum() == 2) {
		return ((int) (round((-5. / 7.) * (pos + 1) + 16)));
	}
	return -99;
}

double RatePlot::getPt(L1MuDTChambPhDigi kDigi) {
	double p0 = 1.10456;
	double p1 = 2.27101;
	double p2 = 1.57637e-2;
	double n0 = -1.07813;
	double n1 = 2.34187;
	double n2 = -2.00791e-2;
	double phiB = kDigi.phiB() / 512.;
	if (phiB < 0)
		return abs(n0 / (phiB - n2) + n1);
	else
		return abs(p0 / (phiB - p2) + p1);
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void RatePlot::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
	//The following says we do not know what parameters are allowed so do no validation
	// Please change this to state exactly what you do use, even if it is no parameters
	edm::ParameterSetDescription desc;
	desc.setUnknown();
	descriptions.addDefault(desc);
}

void RatePlot::parseCSV() {
	std::ifstream data("LS.csv");
	std::string line;
	std::vector < vector<string> > parsedCsv;
	while (std::getline(data, line)) {
		std::stringstream lineStream(line);
		std::string cell;
		std::vector < string > parsedRow;
		while (std::getline(lineStream, cell, ',')) {

			parsedRow.push_back(cell);

		}

		parsedCsv.push_back(parsedRow);

	}
	for (unsigned int i = 0; i < parsedCsv.size(); i++) {
		lumiSection.push_back(std::stoi(parsedCsv[i][2]));
		pileUp.push_back(std::stod(parsedCsv[i][3]));
//		std::cout << "LumiSection: " << std::stoi(parsedCsv[i][2])
//				<< " PileUp: " << std::stod(parsedCsv[i][3]) << std::endl;
	}
}

double RatePlot::getPUFromLumiSection(int lumiSec) {
	unsigned int i = 0;
	while (i < lumiSection.size()) {
		if (lumiSection[i] == lumiSec) {
//			std::cout << "Check LS: " << lumiSec << " PileUp: " << pileUp.at(i)
//					<< std::endl;
			return pileUp.at(i);
		}
		i++;
	}
	return -1;

}

//define this as a plug-in
DEFINE_FWK_MODULE (RatePlot);
