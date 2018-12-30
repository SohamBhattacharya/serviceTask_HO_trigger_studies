import matplotlib.pyplot
import numpy
import os

import Array2LatexTable

matplotlib.pyplot.rc("text", usetex = True)


arr_pTcut = [0, 5, 10, 14, 18, 22, 25, 30]

arr_pTcut_index = range(0, len(arr_pTcut))
#arr_pTcut_index = [5]


fileNames_HQ = [
    "output/ZeroBias1/isolatedMB1_HQ_pT0.txt",
    "output/ZeroBias1/isolatedMB1_HQ_pT5.txt",
    "output/ZeroBias1/isolatedMB1_HQ_pT10.txt",
    "output/ZeroBias1/isolatedMB1_HQ_pT14.txt",
    "output/ZeroBias1/isolatedMB1_HQ_pT18.txt",
    "output/ZeroBias1/isolatedMB1_HQ_pT22.txt",
    "output/ZeroBias1/isolatedMB1_HQ_pT25.txt",
    "output/ZeroBias1/isolatedMB1_HQ_pT30.txt",
]

#fileNames_LQ = [
#    "output/ZeroBias1_BX0_wh0/isolatedMB1_LQ_pT0.txt",
#    "output/ZeroBias1_BX0_wh0/isolatedMB1_LQ_pT5.txt",
#    "output/ZeroBias1_BX0_wh0/isolatedMB1_LQ_pT10.txt",
#    "output/ZeroBias1_BX0_wh0/isolatedMB1_LQ_pT14.txt",
#    "output/ZeroBias1_BX0_wh0/isolatedMB1_LQ_pT18.txt",
#    "output/ZeroBias1_BX0_wh0/isolatedMB1_LQ_pT22.txt",
#    "output/ZeroBias1_BX0_wh0/isolatedMB1_LQ_pT25.txt",
#    "output/ZeroBias1_BX0_wh0/isolatedMB1_LQ_pT30.txt",
#]


fileNames = fileNames_HQ
#fileNames = fileNames_LQ

fileContent = [numpy.loadtxt(fName, delimiter = ",") for fName in fileNames]


dtype_str = "S100"

outputDir = "tables"

os.system("mkdir -p " + outputDir)


arr_avg = []

fig = matplotlib.pyplot.figure(figsize = [10, 10])

for iPt in arr_pTcut_index :
    
    table = []
    
    inFileName = fileNames[iPt]
    outFileName = "tables/table_" + inFileName[inFileName.rfind("/")+1:]
    
    print "Input:", inFileName
    print "Output:", outFileName
    
    ###
    arr_run = fileContent[iPt][:, 0]
    arr_run_str = arr_run.astype(int).astype(dtype = dtype_str)
    arr_run_str = numpy.insert(arr_run_str, 0, "$ run $")
    table.append(arr_run_str)
    
    ###
    arr_nEvent = fileContent[iPt][:, 2]
    arr_nEvent_str = arr_nEvent.astype(int).astype(dtype = dtype_str)
    arr_nEvent_str = numpy.insert(arr_nEvent_str, 0, "$ n_{event} $")
    table.append(arr_nEvent_str)
    
    ###
    arr_BMTF = fileContent[iPt][:, 6]
    arr_BMTF_str = arr_BMTF.astype(int).astype(dtype = dtype_str)
    arr_BMTF_str = numpy.insert(arr_BMTF_str, 0, "$ BMTF $")
    table.append(arr_BMTF_str)
    
    ###
    arr_isoMB1 = fileContent[iPt][:, 10]
    arr_isoMB1_str = arr_isoMB1.astype(int).astype(dtype = dtype_str)
    #arr_isoMB1_str = numpy.insert(arr_isoMB1_str, 0, "$ isoMB1(wh0) $")
    arr_isoMB1_str = numpy.insert(arr_isoMB1_str, 0, "$ isoMB1(wh0, 1) $")
    table.append(arr_isoMB1_str)
    
    ###
    arr_isoMB1HO = fileContent[iPt][:, 12]
    arr_isoMB1HO_str = arr_isoMB1HO.astype(int).astype(dtype = dtype_str)
    #arr_isoMB1HO_str = numpy.insert(arr_isoMB1HO_str, 0, "$ isoMB1(wh0)+HO(i\\eta 3) $")
    arr_isoMB1HO_str = numpy.insert(arr_isoMB1HO_str, 0, "$ isoMB1(wh0, 1)+HO $")
    table.append(arr_isoMB1HO_str)
    
    ###
    with numpy.errstate(divide = "ignore", invalid = "ignore") :
        
        arr_ratio = (arr_BMTF+arr_isoMB1HO) / arr_BMTF
        #arr_ratio_str = arr_ratio.astype(dtype = dtype_str)
        arr_ratio_str = numpy.array([("%0.2f" % val) for val in arr_ratio], dtype = dtype_str)
        arr_ratio_str[numpy.where(arr_ratio_str == "nan")] = "-"
        arr_ratio_str[numpy.where(arr_ratio_str == "inf")] = "-"
        #arr_ratio_str = numpy.insert(arr_ratio_str, 0, "$ \\frac{BMTF+[isoMB1(wh0)+HO(i\\eta 3)]}{BMTF} $")
        arr_ratio_str = numpy.insert(arr_ratio_str, 0, "$ \\frac{BMTF+[isoMB1(wh0, 1)+HO]}{BMTF} $")
        table.append(arr_ratio_str)
        
        avg = numpy.average(
            arr_ratio[numpy.where(
                numpy.isfinite(arr_ratio))[0]])
    
    table = numpy.transpose(table).tolist()
    
    arr_avg += [avg]
    
    #print table
    print "Average = ", avg
    
    latexTable = Array2LatexTable.array2LatexTable(table, isColumnTitled = True, table_width = "0.75")
    #print latexTable
    
    with open(outFileName, "w") as outFile :
        
        outFile.write(latexTable)
    
    
    print "\n"

#matplotlib.pyplot.plot(arr_pTcut, arr_avg, "b.-", label = "HO($ i\\eta\\pm3 $)", markersize = 10, linewidth = 2)
matplotlib.pyplot.plot(arr_pTcut, arr_avg, "b.-", label = "HO", markersize = 10, linewidth = 2)

matplotlib.pyplot.xticks(arr_pTcut, fontsize = 25)
matplotlib.pyplot.yticks(numpy.arange(1, 2, 0.1), fontsize = 25)
#matplotlib.pyplot.yticks(numpy.arange(1, 15, 1), fontsize = 25)

matplotlib.pyplot.xlabel(r"$ p_{T} $ cut [GeV]", fontsize = 30)
matplotlib.pyplot.ylabel(r"$ \frac{BMTF+[isoMB1(wh0)+HO(i\eta 3)]}{BMTF} $", fontsize = 30)
#matplotlib.pyplot.ylabel(r"$ \frac{BMTF+[isoMB1(wh0, 1)+HO]}{BMTF} $", fontsize = 30)

matplotlib.pyplot.xlim(xmin = 0, xmax = 30)
matplotlib.pyplot.ylim(ymin = 1, ymax = 2)
#matplotlib.pyplot.ylim(ymin = 1, ymax = 15)

matplotlib.pyplot.grid(True)
matplotlib.pyplot.tight_layout()

#matplotlib.pyplot.show()

os.system("mkdir -p plots/MB_HO")
matplotlib.pyplot.savefig("plots/MB_HO/rate_ratio.pdf")
matplotlib.pyplot.close(fig)
