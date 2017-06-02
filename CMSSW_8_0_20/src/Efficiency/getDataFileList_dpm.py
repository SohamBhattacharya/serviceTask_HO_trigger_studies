import os


dictionary = [ \
    "SingleMuon", 
]


#scriptName = "getDataFileList_dpm.sh"
#scriptName_mod = "getDataFileList_dpm_mod.sh"


for iEntry in range(0, len(dictionary)) :
    
    print "Getting file list:", dictionary[iEntry]
    
    crabDir = "/home/sobhatta/t3store/serviceTask_HO_trigger_studies/CMSSW_9_0_1/src/crabJobs/crab_" + dictionary[iEntry]
    
    outDir = "sourceFiles/" + dictionary[iEntry]
    outFile = "sourceFiles/" + dictionary[iEntry] + "/" + dictionary[iEntry] + "_custom.txt"
    print "Output file:", outFile
    
    command = "mkdir -p " + outDir
    print command
    os.system(command)
    
    command = "crab getoutputold --xrootd " + crabDir + " | sort -V > " + outFile
    print command
    os.system(command)
    
    print "\n"
