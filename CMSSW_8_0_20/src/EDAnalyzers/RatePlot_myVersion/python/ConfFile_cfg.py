import FWCore.ParameterSet.Config as cms

from Configuration.StandardSequences.Eras import eras

process = cms.Process("RECO", eras.Run2_2016)

process.load("FWCore.MessageService.MessageLogger_cfi")
process.load("Configuration.StandardSequences.GeometryRecoDB_cff")
process.load("Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff")
process.load("Configuration.StandardSequences.RawToDigi_Data_cff")
#process.load("Configuration.StandardSequences.L1Reco_cff")
#process.load("Configuration.StandardSequences.Reconstruction_Data_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
#process.load("EventFilter.L1TRawToDigi.bmtfDigis_cfi")

from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, "80X_dataRun2_SPECIALHIGHPUFILL_v0", "")

#process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1000) )

readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
process.source = cms.Source("PoolSource", fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend([
#"root://eoscms.cern.ch//eos/cms/store/data/Run2016H/ZeroBiasBunchTrains0/RAW/v1/000/283/169/00000/ECA43E73-E891-E611-BEBA-02163E014624.root",
"root://eoscms.cern.ch//eos/cms/store/data/Run2016H/ZeroBiasBunchTrains0/RAW/v1/000/283/171/00000/0050F6E3-F191-E611-88C9-02163E013785.root",
#"root://eoscms.cern.ch//eos/cms/store/data/Run2016H/ZeroBiasBunchTrains0/RAW/v1/000/283/171/00000/00B47F48-3192-E611-A382-FA163E605F68.root",
#"root://eoscms.cern.ch//eos/cms/store/data/Run2016H/ZeroBiasBunchTrains0/RAW/v1/000/283/171/00000/00D3F05A-F391-E611-9C24-02163E01349D.root",
#"root://eoscms.cern.ch//eos/cms/store/data/Run2016H/ZeroBiasBunchTrains0/RAW/v1/000/283/171/00000/02081300-EB91-E611-AC59-02163E0135B9.root",
#"root://eoscms.cern.ch//eos/cms/store/data/Run2016H/ZeroBiasBunchTrains0/RAW/v1/000/283/171/00000/02281A91-EC91-E611-B29B-02163E0142BF.root",
#"root://eoscms.cern.ch//eos/cms/store/data/Run2016H/ZeroBiasBunchTrains0/RAW/v1/000/283/171/00000/0228F88B-EB91-E611-8C62-02163E01395E.root",
#"root://eoscms.cern.ch//eos/cms/store/data/Run2016H/ZeroBiasBunchTrains0/RAW/v1/000/283/171/00000/028D522F-FC91-E611-B945-02163E014439.root",
#"root://eoscms.cern.ch//eos/cms/store/data/Run2016H/ZeroBiasBunchTrains0/RAW/v1/000/283/171/00000/02EB2CAC-EC91-E611-AE38-02163E0141F9.root",
#"root://eoscms.cern.ch//eos/cms/store/data/Run2016H/ZeroBiasBunchTrains0/RAW/v1/000/283/171/00000/040B5C48-3192-E611-B2AC-02163E0135B9.root",
#"root://eoscms.cern.ch//eos/cms/store/data/Run2016H/ZeroBiasBunchTrains0/RAW/v1/000/283/171/00000/0456B3D2-F091-E611-8C7E-02163E013827.root",
#
#"root://eoscms.cern.ch//eos/cms/store/data/Run2016H/ZeroBiasBunchTrains0/RAW/v1/000/283/171/00000/A49DCF47-3192-E611-A75A-02163E011EE8.root",
#"root://eoscms.cern.ch//eos/cms/store/data/Run2016H/ZeroBiasBunchTrains0/RAW/v1/000/283/171/00000/A4BF2BE0-FC91-E611-AFEC-02163E0142E1.root",
#"root://eoscms.cern.ch//eos/cms/store/data/Run2016H/ZeroBiasBunchTrains0/RAW/v1/000/283/171/00000/A4C02885-EB91-E611-8455-02163E011CD4.root",
#"root://eoscms.cern.ch//eos/cms/store/data/Run2016H/ZeroBiasBunchTrains0/RAW/v1/000/283/171/00000/A4C3522D-F891-E611-B0A6-02163E01352D.root",
#"root://eoscms.cern.ch//eos/cms/store/data/Run2016H/ZeroBiasBunchTrains0/RAW/v1/000/283/171/00000/A4C47CF8-FC91-E611-BE53-02163E01217B.root",
#"root://eoscms.cern.ch//eos/cms/store/data/Run2016H/ZeroBiasBunchTrains0/RAW/v1/000/283/171/00000/A6152729-ED91-E611-ABC9-02163E011DD3.root",
#"root://eoscms.cern.ch//eos/cms/store/data/Run2016H/ZeroBiasBunchTrains0/RAW/v1/000/283/171/00000/A65FE4CD-F591-E611-BCD2-FA163EBE57A9.root"
])


process.TFileService = cms.Service("TFileService",
    fileName = cms.string("plots.root")
)

process.demo = cms.EDAnalyzer("RatePlot_myVersion"
)

process.content = cms.EDAnalyzer("EventContentAnalyzer")


#process.out = cms.OutputModule("PoolOutputModule", 
#    fileName = cms.untracked.string("debug.root")
#)


process.p = cms.Path(process.RawToDigi*process.demo) #process.content #process.reconstruction* #
#process.RawToDigi*process.L1Reco

#process.output_step = cms.EndPath(process.out)
#process.schedule = cms.Schedule(process.p)
#process.schedule.extend([process.output_step])
