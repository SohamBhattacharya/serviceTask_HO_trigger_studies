import os
import subprocess


dictionary = [ \
    #["", "SingleMuon", "SingleMuon_Run2017C-ZMu-PromptReco-v3_RAW-RECO"],
    #["", "ZeroBias9"],
    #["", "ZeroBias1"],
    ["", "MET", "MET_Run2017C-v1_RAW"]
]


scriptName = "getDataFileList_dpm.sh"
scriptName_mod = "getDataFileList_dpm_mod.sh"


for iEntry in range(0, len(dictionary)) :
    
    print "Getting file list:", dictionary[iEntry][2]
    
    #crabDir = "/home/sobhatta/t3store/serviceTask_HO_trigger_studies/CMSSW_9_0_1/src/crabJobs/crab_" + dictionary[iEntry][2]
    crabDir = "/home/sobhatta/t3store/serviceTask_HO_trigger_studies/CMSSW_9_2_11/src/crabJobs/crab_" + dictionary[iEntry][2]
    
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
    
    if (jobID == "") :
        
        print "Could not get job ID."
        exit()
    
    print "Task ID:", jobID
    
    dictionary[iEntry][0] = jobID
    
    
    with open(scriptName, "r") as f :
        
        scriptName_fileContent = f.read()
    
    
    scriptName_fileContent = scriptName_fileContent.replace("@1@", dictionary[iEntry][0])
    scriptName_fileContent = scriptName_fileContent.replace("@2@", dictionary[iEntry][1])
    scriptName_fileContent = scriptName_fileContent.replace("@3@", dictionary[iEntry][2])
    
    
    with open(scriptName_mod, "w") as f :
        
        f.write(scriptName_fileContent)
    
    
    command = "chmod +x " + scriptName_mod
    os.system(command)
    
    command = "echo ./" + scriptName_mod + " | env -i bash -i"
    os.system(command)
