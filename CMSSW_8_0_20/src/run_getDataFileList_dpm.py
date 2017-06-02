import os
import subprocess


dictionary = [ \
    ["", "Tau"], \
    \
    ["", "DY1JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"], \
    ["", "DY2JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"], \
    ["", "DY3JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"], \
    ["", "DY4JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"], \
    \
    ["", "W1JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"], \
    ["", "W2JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"], \
    ["", "W3JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"], \
    ["", "W4JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"], \
    \
    ["", "TT_TuneCUETP8M1_13TeV-powheg-pythia8"], \
    \
    ["", "QCD_Pt_15to30_TuneCUETP8M1_13TeV_pythia8"], \
    ["", "QCD_Pt_30to50_TuneCUETP8M1_13TeV_pythia8"], \
    ["", "QCD_Pt_50to80_TuneCUETP8M1_13TeV_pythia8"], \
    ["", "QCD_Pt_80to120_TuneCUETP8M1_13TeV_pythia8"], \
    ["", "QCD_Pt_120to170_TuneCUETP8M1_13TeV_pythia8"], \
    ["", "QCD_Pt_170to300_TuneCUETP8M1_13TeV_pythia8"], \
    ["", "QCD_Pt_300to470_TuneCUETP8M1_13TeV_pythia8"], \
    ["", "QCD_Pt_470to600_TuneCUETP8M1_13TeV_pythia8"], \
    ["", "QCD_Pt_600to800_TuneCUETP8M1_13TeV_pythia8"], \
    ["", "QCD_Pt_800to1000_TuneCUETP8M1_13TeV_pythia8"], \
    ["", "QCD_Pt_1000to1400_TuneCUETP8M1_13TeV_pythia8"], \
    ["", "QCD_Pt_1400to1800_TuneCUETP8M1_13TeV_pythia8"], \
    ["", "QCD_Pt_1800to2400_TuneCUETP8M1_13TeV_pythia8"], \
    ["", "QCD_Pt_2400to3200_TuneCUETP8M1_13TeV_pythia8"], \
    ["", "QCD_Pt_3200toInf_TuneCUETP8M1_13TeV_pythia8"] ]


scriptName = "getDataFileList_dpm.sh"
scriptName_mod = "getDataFileList_dpm_mod.sh"


for iEntry in range(0, len(dictionary)) :
    
    print "Getting file list:", dictionary[iEntry][1]
    
    crabDir = "/home/sobhatta/t3store/PhD/source2custom/CMSSW_8_0_20/src/crabJobs/crab_" + dictionary[iEntry][1]
    
    # For python >= 2.7
    #crabStatus = subprocess.check_output(["crab", "status", crabDir]).split("\n")
    
    # For python < 2.7
    crabStatus = subprocess.Popen(["crab", "status", crabDir], stdout=subprocess.PIPE).communicate()[0].split("\n")
    
    jobID = ""
    
    for line in crabStatus :
        
        if ("Task name" in line) :
            
            jobID = line
            break
    
    jobID = jobID[jobID.find(":") + 1 : jobID.rfind(":")].strip()
    print "Task ID:", jobID
    
    dictionary[iEntry][0] = jobID
    
    
    with open(scriptName, "r") as f :
        
        scriptName_fileContent = f.read()
    
    
    scriptName_fileContent = scriptName_fileContent.replace("@1@", dictionary[iEntry][0])
    scriptName_fileContent = scriptName_fileContent.replace("@2@", dictionary[iEntry][1])
    
    
    with open(scriptName_mod, "w") as f :
        
        f.write(scriptName_fileContent)
    
    
    command = "chmod +x " + scriptName_mod
    os.system(command)
    
    command = "echo ./" + scriptName_mod + " | env -i bash -i"
    os.system(command)
