import numpy
import os


condorConfig = "condor_config.sub"
condorScript = "condor_script.sh"

condorConfig_name = condorConfig[0: condorConfig.rfind(".")]
condorConfig_ext = condorConfig[condorConfig.rfind("."):]

condorScript_name = condorScript[0: condorScript.rfind(".")]
condorScript_ext = condorScript[condorScript.rfind("."):]

# Files to process per job
nUnitPerJob = 10

# Set to -1 for all files
nInputFileMax = -1


#processName = "SingleMuon_Run2017C-ZMu-PromptReco-v3_RAW-RECO"
#inputFileList = "sourceFiles/SingleMuon_Run2017C-ZMu-PromptReco-v3_RAW-RECO/SingleMuon_Run2017C-ZMu-PromptReco-v3_RAW-RECO.txt"

processName = "MET_Run2017C-v1_RAW"
inputFileList = "sourceFiles/MET_Run2017C-v1_RAW/MET_Run2017C-v1_RAW.txt"


codeFile = "realEfficiency.cc"
#codeFile = "DTTPefficiency.cc"

condorDirectory = "condorJobs/condor_" + processName

inputFiles = numpy.loadtxt(inputFileList, dtype = str)
nInputFile = inputFiles.shape[0]

if nInputFileMax > 0 and nInputFile > nInputFileMax :
    
    inputFiles = inputFiles[0: nInputFileMax]
    nInputFile = inputFiles.shape[0]

nJob = int(numpy.ceil(float(nInputFile)/nUnitPerJob))


print "Process:", processName
print "Input file:", inputFileList
print "Code file:", codeFile
print "# jobs:", nJob
print "# units:", inputFiles.shape[0]
print "# units per job:", nUnitPerJob
print ""


inputFileList = inputFileList[inputFileList.rfind("/")+1:]
inputFileList_name = inputFileList[0: inputFileList.rfind(".")]
inputFileList_ext = inputFileList[inputFileList.rfind("."):]

codeFile_name = codeFile[0: codeFile.rfind(".")]
codeFile_ext = codeFile[codeFile.rfind("."):]

codeFile_content = ""

with open(codeFile, "r") as f :
    
    codeFile_content = f.read()


condorConfig_content = ""

with open(condorConfig, "r") as f :
    
    condorConfig_content = f.read()


condorScript_content = ""

with open(condorScript, "r") as f :
    
    condorScript_content = f.read()


command = "mkdir -p " + condorDirectory
print "Command:", command
os.system(command)

print "\n"


for iJob in range(0, nJob) :
    
    codeFile_content_mod = codeFile_content
    condorConfig_content_mod = condorConfig_content
    condorScript_content_mod = condorScript_content
    
    inputFiles_mod = []
    
    if iJob < nJob-1 :
        
        inputFiles_mod = inputFiles[iJob*nUnitPerJob: (iJob+1)*nUnitPerJob]
        
    else :
        
        inputFiles_mod = inputFiles[iJob*nUnitPerJob:]
    
    condorConfig_mod = condorConfig_name + "_" + str(int(iJob+1)) + condorConfig_ext
    condorScript_mod = condorScript_name + "_" + str(int(iJob+1)) + condorScript_ext
    
    inputFileList_mod = inputFileList_name + "_" + str(int(iJob+1)) + inputFileList_ext
    codeFile_name_mod = codeFile_name + "_" + str(int(iJob+1))
    
    
    # Condor config
    condorConfig_content_mod = condorConfig_content_mod.replace("@exe@", condorDirectory + "/" + condorScript_mod)
    condorConfig_content_mod = condorConfig_content_mod.replace("@log@", condorDirectory + "/" + codeFile_name_mod + ".log")
    condorConfig_content_mod = condorConfig_content_mod.replace("@out@", condorDirectory + "/" + codeFile_name_mod + ".out")
    condorConfig_content_mod = condorConfig_content_mod.replace("@err@", condorDirectory + "/" + codeFile_name_mod + ".err")
    
    print "Writing:", (condorDirectory + "/" + condorConfig_mod)
    
    with open(condorDirectory + "/" + condorConfig_mod, "w") as f :
        
        f.write(condorConfig_content_mod)
    
    
    # Condor script
    condorScript_content_mod = condorScript_content_mod.replace("@exe@", condorDirectory + "/" + codeFile_name_mod)
    
    print "Writing:", (condorDirectory + "/" + condorScript_mod)
    
    with open(condorDirectory + "/" + condorScript_mod, "w") as f :
        
        f.write(condorScript_content_mod)
    
    command = "chmod +x " + condorDirectory + "/" + condorScript_mod
    print "Command:", command
    os.system(command)
    
    
    # Code file
    codeFile_content_mod = codeFile_content_mod.replace("@process@", processName)
    codeFile_content_mod = codeFile_content_mod.replace("@source@", condorDirectory + "/" + inputFileList_mod)
    
    print "Writing:", (condorDirectory + "/" + codeFile_name_mod + codeFile_ext)
    
    with open(condorDirectory + "/" + codeFile_name_mod + codeFile_ext, "w") as f :
        
        f.write(codeFile_content_mod)
    
    
    # Input file list
    print "Writing:", (condorDirectory + "/" + inputFileList_mod)
    
    with open(condorDirectory + "/" + inputFileList_mod, "w") as f :
        
        f.write("\n".join(inputFiles_mod) + "\n")
    
    
    command = "condor_submit " + condorDirectory + "/" + condorConfig_mod
    print "Command:", command
    os.system(command)
    
    
    print "\n"
    
