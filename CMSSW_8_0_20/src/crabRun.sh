#!/bin/bash

OPT="$1"

#crabDir="crabJobs/crab_ZeroBiasBunchTrains0" #_withCode7"
crabDir="crabJobs/crab_@1@" #_withCode7"
#crabConfigFile="crabConfig.py"
crabConfigFile="crabConfig_mod.py"

# cmsenv
eval `scramv1 runtime -sh`

#source /etc/bashrc
# Not needed anymore: source /afs/cern.ch/cms/LCG/LCG-2/UI/cms_ui_env.sh
export VO_CMS_SW_DIR=/cvmfs/cms.cern.ch
source $VO_CMS_SW_DIR/cmsset_default.sh
export SCRAM_ARCH=slc6_amd64_gcc530
source /cvmfs/cms.cern.ch/crab3/crab.sh

which crab

# Create proxy with specified duration (in hours)
#voms-proxy-init -voms cms -valid 192:00 # Maximum: 192 hours (8 days)
#~/.local/bin/vomsproxy.exp

# For normal run
if [ "$OPT" = "NORMAL" ]; then
    echo "Normal run..."
    rm -rf $crabDir
    crab submit -c $crabConfigFile #--wait
# For dry run
elif [ "$OPT" = "DRY" ]; then
    echo "Dry run..."
    rm -rf $crabDir
	crab submit -c $crabConfigFile --dryrun
# For resubmission (submit failed jobs only)
elif [ "$OPT" = "RESUBMIT" ]; then
    echo "Resubmitting failed jobs..."
    crab resubmit -d $crabDir
# Kill jobs
elif [ "$OPT" = "KILL" ]; then
    echo "Killing jobs..."
    crab kill -d $crabDir
    
else
    echo "Enter a valid option. Syntax: crabRun.sh <option>"
    echo "Options:"
    echo "NORMAL --> Dry run"
    echo "DRY --> Normal run"
    echo "RESUBMIT --> Resubmit failed jobs"
    echo "KILL --> Kill jobs"
fi
