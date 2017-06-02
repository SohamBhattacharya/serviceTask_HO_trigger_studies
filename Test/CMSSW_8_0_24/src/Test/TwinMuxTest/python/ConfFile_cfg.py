import FWCore.ParameterSet.Config as cms
from Configuration.StandardSequences.Eras import eras
from Configuration.AlCa.GlobalTag import GlobalTag

process = cms.Process("RECO", eras.Run2_2016)

process.load("FWCore.MessageService.MessageLogger_cfi")
process.load("Configuration.StandardSequences.GeometryRecoDB_cff")
process.load("Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff")
process.load("Configuration.StandardSequences.RawToDigi_Data_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")


process.GlobalTag = GlobalTag(process.GlobalTag, "80X_dataRun2_SPECIALHIGHPUFILL_v0", "")
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(1000))


inputFiles = [
    #"root://eoscms.cern.ch//eos/cms/store/data/Run2016H/ZeroBiasBunchTrains0/RAW/v1/000/283/169/00000/ECA43E73-E891-E611-BEBA-02163E014624.root",
    "root://eoscms.cern.ch//eos/cms/store/data/Run2016H/ZeroBiasBunchTrains0/RAW/v1/000/283/171/00000/0050F6E3-F191-E611-88C9-02163E013785.root",
    #"root://eoscms.cern.ch//eos/cms/store/data/Run2016H/ZeroBiasBunchTrains0/RAW/v1/000/283/171/00000/00B47F48-3192-E611-A382-FA163E605F68.root",
]

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(inputFiles)
)

process.TwinMuxTest = cms.EDAnalyzer("TwinMuxTest")

# TwinMux
process.load("L1Trigger.L1TwinMux.fakeTwinMuxParams_cff")
process.load("L1Trigger.L1TwinMux.simTwinMuxDigis_cfi")
process.simTwinMuxDigisEmu.DTDigi_Source = cms.InputTag("bmtfDigis")
process.simTwinMuxDigisEmu.DTThetaDigi_Source = cms.InputTag("bmtfDigis")
process.simTwinMuxDigisEmu.RPC_Source = cms.InputTag("muonRPCDigis")

# BMTF
process.load("L1Trigger.L1TMuonBarrel.fakeBmtfParams_cff")
process.load("L1Trigger.L1TMuonBarrel.simBmtfDigis_cfi")
process.simBmtfDigis.DTDigi_Source = cms.InputTag("simTwinMuxDigisEmu", "TwinMuxEmulator")
process.simBmtfDigis.DTDigi_Theta_Source = cms.InputTag("bmtfDigis")

process.p = cms.Path(
    process.RawToDigi
    *process.simTwinMuxDigisEmu
    *process.simBmtfDigis
    *process.TwinMuxTest
)

process.TFileService = cms.Service("TFileService", fileName = cms.string("output_TwinMuxTest.root"))
process.out = cms.OutputModule("PoolOutputModule", fileName = cms.untracked.string("debug.root"))
process.output_step = cms.EndPath(process.out)

processSchedule = [
    process.p, 
    process.output_step,
]

process.schedule = cms.Schedule(processSchedule)
