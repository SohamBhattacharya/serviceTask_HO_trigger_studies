import os


crabRun_fileName = "crabRun.sh"
crabRun_mod_fileName = "crabRun_mod.sh"

dictionary = {}


crabConfig_fileName = "crabConfig.py"
crabConfig_mod_fileName = "crabConfig_mod.py"

cmsRunFileName = "UserCode/DTDPGAnalysis/test/RunTree_collisions_cfg.py"


dictionary["ZeroBias"] = [
    #"/ZeroBias9/Run2017B-v1/RAW",
    
    #"/ZeroBias/Run2017F-v1/RAW",
    
    ##"/ZeroBias0/Run2017F-v1/RAW",
    #"/ZeroBias1/Run2017F-v1/RAW",
    #"/ZeroBias2/Run2017F-v1/RAW",
    #"/ZeroBias3/Run2017F-v1/RAW",
    #"/ZeroBias4/Run2017F-v1/RAW",
    #"/ZeroBias5/Run2017F-v1/RAW",
    ##"/ZeroBias6/Run2017F-v1/RAW",
    ##"/ZeroBias7/Run2017F-v1/RAW",
    ##"/ZeroBias8/Run2017F-v1/RAW",
    ##"/ZeroBias9/Run2017F-v1/RAW",
]

#dictionary["SingleMuon"] = [
#    "/SingleMuon/Run2017C-ZMu-PromptReco-v3/RAW-RECO",
#    #"/SingleMuon/Run2017F-ZMu-PromptReco-v1/RAW-RECO",
#]

#dictionary["MET"] = [
#    "/MET/Run2017C-v1/RAW",
#    #"/MET/Run2017F-v1/RAW",
#]


dictionary["Charmonium"] = [
    "/Charmonium/Run2017F-v1/RAW",
]


print "\n"
print "Crab options:"
print "DRY --> Dry run"
print "NORMAL --> Normal run"
print "RESUBMIT --> Resubmit"
print "KILL --> Kill jobs"
crabMode = str(raw_input("Choice: "))


crabMode_options = ["DRY", "NORMAL", "RESUBMIT", "KILL"]


if (not crabMode in crabMode_options) :
    
    print "Enter a valid option."
    
    exit()


for key in dictionary :
    
    for iInputDataset in range(0, len(dictionary[key])) :
        
        inputDataset = dictionary[key][iInputDataset]
        crabDirName = "_".join(inputDataset.split("/")[1:])
        
        keyName = inputDataset[inputDataset.find("/", 0)+1: inputDataset.find("/", 1)]
        
        print "\n\n\n\n"
        print "********** Running", keyName, "**********"
        print "Datset:", inputDataset
        print ""
        
        
        # Read the files
        with open(crabConfig_fileName, "r") as f :
            
            crabConfig_fileContent = f.read()
        
        with open(crabRun_fileName, "r") as f :
            
            crabRun_fileContent = f.read()
        
        
        # Edit the files
        crabConfig_fileContent = crabConfig_fileContent.replace("@1@", inputDataset)
        #crabConfig_fileContent = crabConfig_fileContent.replace("@2@", cmsRunFileName)
        crabConfig_fileContent = crabConfig_fileContent.replace("@3@", crabDirName)
        
        crabRun_fileContent = crabRun_fileContent.replace("@1@", crabDirName)
        #crabRun_fileContent = crabRun_fileContent.replace("@2@", crabConfig_mod_fileName)
        
        
        # Write the files
        with open(crabConfig_mod_fileName, "w") as f :
            
            f.write(crabConfig_fileContent)
        
        with open(crabRun_mod_fileName, "w") as f :
            
            f.write(crabRun_fileContent)
        
        os.system("chmod +x " + crabRun_mod_fileName)
        
        # Run crab
        command = "./" + crabRun_mod_fileName + " " + crabMode
        print command
        os.system(command)
        
