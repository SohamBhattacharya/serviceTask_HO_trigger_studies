import numpy
import os
import pandas


#normTagFile = "/afs/cern.ch/user/l/lumipro/public/normtag_file/normtag_DATACERT.json"
normTagFile = "normtag_DATACERT.json"
beamEnergy = 6500
minBiasXsec = 69200
beamType = "'STABLE BEAMS'"
lumiType = "pltzero16v3"

outFileName = "LS_new.csv"
tempFileName = "LS_temp.csv"

runList = [
    #283169, 
    283171
]

data = pandas.read_json(normTagFile)
data_len = len(data[0])


#for iEntry in range(0, data_len) :
#    
#    if (str(data[0][iEntry]) == lumiType) :
#        
#        runNumber = int(list(pandas.DataFrame(data[1][iEntry]))[0])
#        
#        print "Adding:", data[0][iEntry], data[1][iEntry]
#        
#        runList.append(runNumber)
#        


#print runList

for iRun in range(0, len(runList)) :

    runNumber = runList[iRun]
    
    command = "brilcalc lumi --byls -u '1e30/cm2s' --output-style csv"
    command += " -o " + tempFileName
    command += " -b " + beamType
    command += " -r " + str(runNumber)
    command += " --normtag " + normTagFile
    command += " --beamenergy " + str(beamEnergy)
    command += " --minBiasXsec " + str(minBiasXsec)
    
    print command
    
    errCode = os.system(command)
    
    if(errCode) :
        
        print "Error running brilcalc"
        exit()
    
    data_temp = numpy.loadtxt(tempFileName, delimiter = ",", dtype = str)
    #print data_temp
    
    for iRow in range(0, data_temp.shape[0]) :
        
        data_row = data_temp[iRow]
        
        run = data_row[0].split(":")[0]
        fill = data_row[0].split(":")[1]
        
        lumiSection = data_row[1].split(":")[0]
        avgPU = data_row[-2]
        
        print fill, run, lumiSection, avgPU
