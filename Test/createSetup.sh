#!/bin/bash

cmsrel CMSSW_8_0_24
cd CMSSW_8_0_24/src/
cmsenv
git cms-init

git cms-merge-topic jpazzini:TwinMux_unpacker_Output
git pull https://github.com/gflouris/cmssw.git twinmuxdevel_8_0_24
git cms-addpkg L1Trigger/L1TwinMux
git cms-addpkg L1Trigger/L1TMuonBarrel
git cms-addpkg CondFormats/DataRecord
git cms-addpkg CondFormats/L1TObjects
git cms-addpkg DataFormats/L1DTTrackFinder/
git clone https://github.com/gflouris/UIoannina
cd UIoannina/
git checkout twinmux    
cd ..
scram b -j8
#cd UIoannina/TrUpS/test/
#mkdir Ntuples/
#cmsRun runTM_Unpacker_Emulator_Ntuples.py
