import os


crabRun_fileName = "crabRun.sh"
crabRun_mod_fileName = "crabRun_mod.sh"

dictionary = {}


crabConfig_fileName = "crabConfig.py"
crabConfig_mod_fileName = "crabConfig_mod.py"

cmsRunFileName = "EDAnalyzers/miniaod2custom/python/ConfFile_cfg_data.py"


dictionary["ZeroBiasBunchTrains"] = [ \
    "/ZeroBiasBunchTrains0/Run2016H-v1/RAW",
    "/ZeroBiasBunchTrains1/Run2016H-v1/RAW",
    "/ZeroBiasBunchTrains2/Run2016H-v1/RAW",
    "/ZeroBiasBunchTrains3/Run2016H-v1/RAW",
    "/ZeroBiasBunchTrains4/Run2016H-v1/RAW",
    "/ZeroBiasBunchTrains5/Run2016H-v1/RAW"
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
        
        keyName = inputDataset[inputDataset.find("/", 0)+1: inputDataset.find("/", 1)]
        
        print "\n\n\n\n"
        print "********** Running", keyName, "**********"
        print ""
        
        
        # Read the files
        with open(crabConfig_fileName, "r") as f :
            
            crabConfig_fileContent = f.read()
        
        with open(crabRun_fileName, "r") as f :
            
            crabRun_fileContent = f.read()
        
        
        # Edit the files
        crabConfig_fileContent = crabConfig_fileContent.replace("@1@", inputDataset)
        #crabConfig_fileContent = crabConfig_fileContent.replace("@2@", cmsRunFileName)
        
        crabRun_fileContent = crabRun_fileContent.replace("@1@", keyName)
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
        
