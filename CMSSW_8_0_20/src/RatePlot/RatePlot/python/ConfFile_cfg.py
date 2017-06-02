import FWCore.ParameterSet.Config as cms

from Configuration.StandardSequences.Eras import eras

process = cms.Process("RECO", eras.Run2_2016)

process.load("FWCore.MessageService.MessageLogger_cfi")
process.load("Configuration.StandardSequences.GeometryRecoDB_cff")
process.load("Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff")
process.load("Configuration.StandardSequences.RawToDigi_Data_cff")
process.load("Configuration.StandardSequences.L1Reco_cff")
process.load("Configuration.StandardSequences.Reconstruction_Data_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.load("EventFilter.L1TRawToDigi.bmtfDigis_cfi")

from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, "80X_dataRun2_SPECIALHIGHPUFILL_v0", "")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
process.source = cms.Source("PoolSource", fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend([
"root://eoscms.cern.ch//eos/cms/store/data/Run2016H/ZeroBiasBunchTrains0/RAW/v1/000/283/171/00000/A49DCF47-3192-E611-A75A-02163E011EE8.root"
])


process.TFileService = cms.Service("TFileService",
    fileName = cms.string("Plots.root")
)

process.demo = cms.EDAnalyzer("RatePlot"
)

process.content = cms.EDAnalyzer("EventContentAnalyzer")


process.p = cms.Path(process.RawToDigi*process.demo) #process.content #process.reconstruction* #

#process.RawToDigi*process.L1Reco
