import FWCore.ParameterSet.Config as cms


process = cms.Process("Test")


process.load("FWCore.MessageService.MessageLogger_cfi")
process.load("Configuration.EventContent.EventContent_cff")
process.load("Configuration.StandardSequences.GeometryRecoDB_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("Configuration.StandardSequences.Reconstruction_cff")
process.load("Configuration.StandardSequences.Services_cff")


process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff")
#process.GlobalTag.globaltag = "90X_dataRun2_Express_v1"
process.GlobalTag.globaltag = "92X_dataRun2_Prompt_v4"


# The DT unpacker
process.load("EventFilter.DTRawToDigi.dtunpackerDDUGlobal_cfi")
process.dtunpacker.readOutParameters.debug = False
process.dtunpacker.readOutParameters.rosParameters.debug = False

# For DT segments
process.load("RecoLocalMuon.Configuration.RecoLocalMuon_cff")
process.dt1DRecHits.dtDigiLabel = "dtunpacker"


process.load("EventFilter.DTRawToDigi.dtunpacker_cfi")
process.muonDTDigis.inputLabel = "rawDataCollector"

# For DTTP
process.load("EventFilter.L1TXRawToDigi.twinMuxStage2Digis_cfi")

# for the emulator
process.load("L1TriggerConfig.DTTPGConfigProducers.L1DTTPGConfigFromDB_cff")
process.load("L1Trigger.DTTrigger.dtTriggerPrimitiveDigis_cfi")
process.dtTriggerPrimitiveDigis.debug = False
process.L1DTConfigFromDB.debug = False

# For HOTP
process.load("EventFilter.HcalRawToDigi.HcalRawToDigi_cfi")


# for Pedestal, LED runs
#process.hcalDigis.InputLabel = cms.InputTag("source")
#processSource = "HcalTBSource"

# For normal runs
processSource = "PoolSource"


# The analyzer
process.test = cms.EDAnalyzer("Test_1",
    dtSegmentLabel = cms.InputTag("dt4DSegments"),
    twinmuxPhInLabel = cms.InputTag("twinMuxStage2Digis", "PhIn"),
    twinmuxPhOutLabel = cms.InputTag("twinMuxStage2Digis", "PhOut"),
    twinmuxThLabel = cms.InputTag("twinMuxStage2Digis", "ThIn"),
    hoTPLabel = cms.InputTag("hcalDigis"),
    hoLabel = cms.InputTag("hcalDigis")
)

maxEvents = -1
maxEvents = 10
maxEvents = 10 * pow(10, 3)

process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(maxEvents))

outFileName = "DTNtuple.root"
#outFileName = "test.root"
#outFileName = "test_pedestal.root"
#outFileName = "test_LED.root"

#sourceFileNames = cms.untracked.vstring(
#    # Pedestal run
#    "root://cms-xrd-global.cern.ch//store/group/dpg_hcal/comm_hcal/USC/run296181/USC_296181.root",
#    #"root://cms-xrd-global.cern.ch//store/group/dpg_hcal/comm_hcal/USC/run295673/USC_295673.root",
#    
#    # LED run
#    #"root://cms-xrd-global.cern.ch//store/group/dpg_hcal/comm_hcal/USC/run296182/USC_296182.root",
#    #"root://cms-xrd-global.cern.ch//store/group/dpg_hcal/comm_hcal/USC/run295675/USC_295675.root",
#    
#    # Das name: /SingleMuon/Run2016H-ZMu-PromptReco-v2/RAW-RECO
#    #"root://cms-xrd-global.cern.ch//store/data/Run2016H/SingleMuon/RAW-RECO/ZMu-PromptReco-v2/000/284/035/00000/DC000F0F-559F-E611-825A-02163E0143B9.root",
#    #"root://cms-xrd-global.cern.ch//store/data/Run2016H/SingleMuon/RAW-RECO/ZMu-PromptReco-v2/000/284/035/00000/E0908FC9-539F-E611-BCE9-02163E012634.root",
#    #"root://cms-xrd-global.cern.ch//store/data/Run2016H/SingleMuon/RAW-RECO/ZMu-PromptReco-v2/000/284/035/00000/E8BFA3F1-539F-E611-9F33-02163E0136CD.root",
#    #"root://cms-xrd-global.cern.ch//store/data/Run2016H/SingleMuon/RAW-RECO/ZMu-PromptReco-v2/000/284/035/00000/EE0E75B2-539F-E611-B967-02163E01349D.root",
#    #"root://cms-xrd-global.cern.ch//store/data/Run2016H/SingleMuon/RAW-RECO/ZMu-PromptReco-v2/000/284/035/00000/F055B7E5-539F-E611-8192-02163E0119A7.root",
#    #"root://cms-xrd-global.cern.ch//store/data/Run2016H/SingleMuon/RAW-RECO/ZMu-PromptReco-v2/000/284/035/00000/F20D63F7-549F-E611-B25B-FA163E8B6264.root",
#    #"root://cms-xrd-global.cern.ch//store/data/Run2016H/SingleMuon/RAW-RECO/ZMu-PromptReco-v2/000/284/035/00000/F4D3933A-559F-E611-9694-02163E014557.root",
#    #"root://cms-xrd-global.cern.ch//store/data/Run2016H/SingleMuon/RAW-RECO/ZMu-PromptReco-v2/000/284/035/00000/F6FCD1FE-549F-E611-8047-02163E0146C3.root",
#    #"root://cms-xrd-global.cern.ch//store/data/Run2016H/SingleMuon/RAW-RECO/ZMu-PromptReco-v2/000/284/035/00000/FA77BCF4-549F-E611-A9F2-FA163EBCA43B.root",
#    #"root://cms-xrd-global.cern.ch//store/data/Run2016H/SingleMuon/RAW-RECO/ZMu-PromptReco-v2/000/284/035/00000/FE558300-559F-E611-8C24-02163E012172.root",
#)

#Das name: /SingleMuon/Run2017A-ZMu-PromptReco-v2/RAW-RECO
#sourceFile = "sourceFiles/SingleMuon/SingleMuon-Run2017A-ZMu-PromptReco-v2-RAW-RECO.txt"
#sourceFile = "sourceFiles/SingleMuon/SingleMuon-Run2017B-ZMu-PromptReco-v1-RAW-RECO.txt"
#sourceFile = "sourceFiles/SingleMuon/SingleMuon-Run2017B-v1-RAW.txt"
sourceFile = "sourceFiles/ZeroBias/ZeroBias9-Run2017B-v1-RAW.txt"

fNames = ""
with open(sourceFile) as f:
    
    fNames = f.readlines()

sourceFileNames = cms.untracked.vstring(fNames)


process.source = cms.Source(processSource,
    fileNames = sourceFileNames,
    secondaryFileNames = cms.untracked.vstring()
)


# Output
process.TFileService = cms.Service("TFileService", fileName = cms.string(outFileName))
#process.dtunpacker * process.twinMuxStage2Digis * process.reco * process.globalreco + process.sources + process.MEtoEDMConverter
process.p = cms.Path(
    #process.dtunpacker
    #*process.twinMuxStage2Digis
    #*process.dt1DRecHits
    #*process.dt2DSegments
    #*process.dt4DSegments
    #*process.reco
    #*process.globalreco
    #*process.sources
    #*proces.MEtoEDMConverter
    process.hcalDigis
    *process.test
)

process.schedule = cms.Schedule(process.p)


# Debug
process.out = cms.OutputModule("PoolOutputModule", 
    fileName = cms.untracked.string("debug.root")
)

process.output_step = cms.EndPath(process.out)
process.schedule.extend([process.output_step])
