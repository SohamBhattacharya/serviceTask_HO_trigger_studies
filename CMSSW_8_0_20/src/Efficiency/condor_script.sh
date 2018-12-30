#!/bin/sh

DIR="/home/sobhatta/t3store/serviceTask_HO_trigger_studies/CMSSW_8_0_20/src/Efficiency"

cd $DIR

export SCRAM_ARCH=slc6_amd64_gcc530
export CPATH=$CPATH:$DIR

source /cvmfs/cms.cern.ch/cmsset_default.sh

cmsenv

#g++mod h realEfficiency
#./realEfficiency

if g++mod h @exe@ ; then
    ./@exe@
else
    echo "Compilation failed."
fi
