#!/bin/bash


outputFile="output/plots.root"

rm $outputFile

hadd -f0 $outputFile `cat \
    sourceFiles/ZeroBiasBunchTrains0/ZeroBiasBunchTrains0_custom.txt \
    sourceFiles/ZeroBiasBunchTrains1/ZeroBiasBunchTrains1_custom.txt \
    sourceFiles/ZeroBiasBunchTrains2/ZeroBiasBunchTrains2_custom.txt \
    sourceFiles/ZeroBiasBunchTrains3/ZeroBiasBunchTrains3_custom.txt \
    sourceFiles/ZeroBiasBunchTrains4/ZeroBiasBunchTrains4_custom.txt \
    sourceFiles/ZeroBiasBunchTrains5/ZeroBiasBunchTrains5_custom.txt`
