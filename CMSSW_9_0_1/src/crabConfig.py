from CRABClient.UserUtilities import config, getUsernameFromSiteDB


config = config()


inputDataset = "@1@"
jobName = inputDataset[inputDataset.find("/", 0)+1: inputDataset.find("/", 1)]
cmsRunFileName = "UserCode/DTDPGAnalysis/test/RunTree_collisions_cfg.py"


# Will create crab directory <workArea>/crab_<requestName>
config.General.requestName = jobName
config.General.workArea = "crabJobs"


config.General.transferOutputs = True
config.General.transferLogs = True
config.JobType.pluginName = "Analysis"


# python file that for cmsRun
config.JobType.psetName = cmsRunFileName


#config.JobType.allowUndistributedCMSSW = True


# Other input files/directories (for example, the directory containing JEC .txt files)
#config.JobType.inputFiles = ["LS.csv"]


config.Data.inputDataset = inputDataset
config.Data.inputDBS = "global"


# Preferable for DATA
config.Data.splitting = "LumiBased"
config.Data.unitsPerJob = 10
config.Data.lumiMask = "luminosityLists/Cert_271036-284044_13TeV_PromptReco_Collisions16_JSON.txt"



# Preferable for MC
#config.Data.splitting = "FileBased"
#config.Data.unitsPerJob = 1
#config.Data.totalUnits = 200


config.Data.outLFNDirBase = "/store/user/%s/" % (getUsernameFromSiteDB())
config.Data.publication = False
#config.Data.publishDataName = "May2015_Data_analysis"


config.Site.storageSite = "T2_IN_TIFR"
#config.Site.whitelist = ["T2_IN_TIFR"]
