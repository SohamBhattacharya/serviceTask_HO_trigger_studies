import matplotlib.pyplot
import numpy
import os

matplotlib.pyplot.rc("text", usetex = True)


pTcuts = [0, 5, 10, 14, 18, 22, 25, 30]


fileNames_HQ = [
"output/ZeroBias9/isolatedMB1_HQ_pT0.txt",
"output/ZeroBias9/isolatedMB1_HQ_pT5.txt",
"output/ZeroBias9/isolatedMB1_HQ_pT10.txt",
"output/ZeroBias9/isolatedMB1_HQ_pT14.txt",
"output/ZeroBias9/isolatedMB1_HQ_pT18.txt",
"output/ZeroBias9/isolatedMB1_HQ_pT22.txt",
"output/ZeroBias9/isolatedMB1_HQ_pT25.txt",
"output/ZeroBias9/isolatedMB1_HQ_pT30.txt",
]

fileNames_LQ = [
"output/ZeroBias9/isolatedMB1_LQ_pT0.txt",
"output/ZeroBias9/isolatedMB1_LQ_pT5.txt",
"output/ZeroBias9/isolatedMB1_LQ_pT10.txt",
"output/ZeroBias9/isolatedMB1_LQ_pT14.txt",
"output/ZeroBias9/isolatedMB1_LQ_pT18.txt",
"output/ZeroBias9/isolatedMB1_LQ_pT22.txt",
"output/ZeroBias9/isolatedMB1_LQ_pT25.txt",
"output/ZeroBias9/isolatedMB1_LQ_pT30.txt",
]


colors = ["b", "g", "r", "c", "m", "y", "k"]


fileContent_HQ = [numpy.loadtxt(fName, delimiter = ",") for fName in fileNames_HQ]
fileContent_LQ = [numpy.loadtxt(fName, delimiter = ",") for fName in fileNames_LQ]

fileContent = fileContent_HQ
#fileContent = fileContent_LQ

fig = matplotlib.pyplot.figure(figsize = [10, 10])

rates_HO_SOI = []
rates_MB1 = []

rates_isoMB1 = []
rates_isoMB1_HO = []

rates_unisoMB1 = []
rates_unisoMB1_HO = []

for iPt in range(0, len(pTcuts)) :
    
    #col = colors[iPt]
    
    # rate_avg = Weighted average of Rate with Lumi/LS as weights
    
    #
    rate_avg = numpy.average(fileContent[iPt][:, 5], weights = fileContent[iPt][:, 1])
    rates_HO_SOI.append(rate_avg)
    
    rate_avg = numpy.average(fileContent[iPt][:, 7], weights = fileContent[iPt][:, 1])
    rates_MB1.append(rate_avg)
    
    #
    rate_avg = numpy.average(fileContent[iPt][:, 9], weights = fileContent[iPt][:, 1])
    rates_isoMB1.append(rate_avg)
    
    rate_avg = numpy.average(fileContent[iPt][:, 11], weights = fileContent[iPt][:, 1])
    rates_isoMB1_HO.append(rate_avg)
    print rates_isoMB1_HO
    print numpy.average(fileContent[iPt][:, 11])
    
    #
    rate_avg = numpy.average(fileContent[iPt][:, 13], weights = fileContent[iPt][:, 1])
    rates_unisoMB1.append(rate_avg)
    
    rate_avg = numpy.average(fileContent[iPt][:, 15], weights = fileContent[iPt][:, 1])
    rates_unisoMB1_HO.append(rate_avg)
    
    #matplotlib.pyplot.plot(fileContent[iPt][:, 0], fileContent[iPt][:, 11], col+".-")


#print rates_isoMB1_HO
#print rates_unisoMB1_HO

MB1_labelSuffix = "\_HQ"

matplotlib.pyplot.semilogy(pTcuts, rates_HO_SOI, "g.-", label = "HO", markersize = 10, linewidth = 2)
#matplotlib.pyplot.semilogy(pTcuts, rates_MB1, "k.-", label = "MB1"+MB1_labelSuffix, markersize = 10, linewidth = 2)
matplotlib.pyplot.semilogy(pTcuts, rates_MB1, "k.-", label = "MB1"+MB1_labelSuffix+"(wh0)", markersize = 10, linewidth = 2)

#matplotlib.pyplot.semilogy(pTcuts, rates_isoMB1, "r.-", label = "isoMB1"+MB1_labelSuffix, markersize = 10, linewidth = 2)
matplotlib.pyplot.semilogy(pTcuts, rates_isoMB1, "r.-", label = "isoMB1"+MB1_labelSuffix+"(wh0)", markersize = 10, linewidth = 2)
#matplotlib.pyplot.semilogy(pTcuts, rates_isoMB1_HO, "r.--", label = "isoMB1"+MB1_labelSuffix+"+HO", markersize = 10, linewidth = 2)
matplotlib.pyplot.semilogy(pTcuts, rates_isoMB1_HO, "r.--", label = r"isoMB1"+MB1_labelSuffix+"(wh0)+HO($ i\\eta\\pm4 $)", markersize = 10, linewidth = 2)
#ratio = numpy.divide(rates_isoMB1_HO, rates_isoMB1)
#matplotlib.pyplot.semilogy(pTcuts, 100*ratio, "r.:", label = "ratio x 100 [mean = " + ("%0.3f"%numpy.average(ratio)) + "]", markersize = 10, linewidth = 2)
#print ratio, numpy.average(ratio)

#matplotlib.pyplot.semilogy(pTcuts, rates_unisoMB1, "b.-", label = "unisoMB1"+MB1_labelSuffix, markersize = 10, linewidth = 2)
matplotlib.pyplot.semilogy(pTcuts, rates_unisoMB1, "b.-", label = "unisoMB1"+MB1_labelSuffix+"(wh0)", markersize = 10, linewidth = 2)
#matplotlib.pyplot.semilogy(pTcuts, rates_unisoMB1_HO, "b.--", label = "unisoMB1"+MB1_labelSuffix+"+HO", markersize = 10, linewidth = 2)
matplotlib.pyplot.semilogy(pTcuts, rates_unisoMB1_HO, "b.--", label = "unisoMB1"+MB1_labelSuffix+"(wh0)+HO($ i\\eta\\pm4 $)", markersize = 10, linewidth = 2)
#ratio = numpy.divide(rates_unisoMB1_HO, rates_unisoMB1)
#matplotlib.pyplot.semilogy(pTcuts, 100*ratio, "b.:", label = "ratio x 100 [mean = " + ("%0.3f"%numpy.average(ratio)) + "]", markersize = 10, linewidth = 2)
#print ratio, numpy.average(ratio)

matplotlib.pyplot.legend(
    loc = 1,
    numpoints = 1,
    fontsize = 20)

matplotlib.pyplot.xticks(pTcuts, fontsize = 25)
matplotlib.pyplot.yticks(fontsize = 25)

matplotlib.pyplot.xlabel(r"$ p_{T} $ cut [GeV]", fontsize = 30)
matplotlib.pyplot.ylabel("Rate [kHz]", fontsize = 30)

matplotlib.pyplot.grid(True)
matplotlib.pyplot.tight_layout()

#matplotlib.pyplot.show()

matplotlib.pyplot.savefig("plots/MB_HO/rate.pdf")
matplotlib.pyplot.close(fig)
