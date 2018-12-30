import matplotlib.pyplot
import numpy
import os

matplotlib.pyplot.rc("text", usetex = True)


pTcuts = [0, 5, 10, 14, 18, 22, 25, 30]


fileNames_iEta3 = [
    "output/ZeroBias1_BMTF0_iEta3/isolatedMB1_HQ_pT0.txt",
    "output/ZeroBias1_BMTF0_iEta3/isolatedMB1_HQ_pT5.txt",
    "output/ZeroBias1_BMTF0_iEta3/isolatedMB1_HQ_pT10.txt",
    "output/ZeroBias1_BMTF0_iEta3/isolatedMB1_HQ_pT14.txt",
    "output/ZeroBias1_BMTF0_iEta3/isolatedMB1_HQ_pT18.txt",
    "output/ZeroBias1_BMTF0_iEta3/isolatedMB1_HQ_pT22.txt",
    "output/ZeroBias1_BMTF0_iEta3/isolatedMB1_HQ_pT25.txt",
    "output/ZeroBias1_BMTF0_iEta3/isolatedMB1_HQ_pT30.txt",
]


fileNames_iEta3_isoMB1HO3x3 = [
    "output/ZeroBias1_BMTF0_iEta3_isoMB1HO3x3/isolatedMB1_HQ_pT0.txt",
    "output/ZeroBias1_BMTF0_iEta3_isoMB1HO3x3/isolatedMB1_HQ_pT5.txt",
    "output/ZeroBias1_BMTF0_iEta3_isoMB1HO3x3/isolatedMB1_HQ_pT10.txt",
    "output/ZeroBias1_BMTF0_iEta3_isoMB1HO3x3/isolatedMB1_HQ_pT14.txt",
    "output/ZeroBias1_BMTF0_iEta3_isoMB1HO3x3/isolatedMB1_HQ_pT18.txt",
    "output/ZeroBias1_BMTF0_iEta3_isoMB1HO3x3/isolatedMB1_HQ_pT22.txt",
    "output/ZeroBias1_BMTF0_iEta3_isoMB1HO3x3/isolatedMB1_HQ_pT25.txt",
    "output/ZeroBias1_BMTF0_iEta3_isoMB1HO3x3/isolatedMB1_HQ_pT30.txt",
]


fileNames_iEtaAll = [
    "output/ZeroBias1_BMTF0_iEtaAll/isolatedMB1_HQ_pT0.txt",
    "output/ZeroBias1_BMTF0_iEtaAll/isolatedMB1_HQ_pT5.txt",
    "output/ZeroBias1_BMTF0_iEtaAll/isolatedMB1_HQ_pT10.txt",
    "output/ZeroBias1_BMTF0_iEtaAll/isolatedMB1_HQ_pT14.txt",
    "output/ZeroBias1_BMTF0_iEtaAll/isolatedMB1_HQ_pT18.txt",
    "output/ZeroBias1_BMTF0_iEtaAll/isolatedMB1_HQ_pT22.txt",
    "output/ZeroBias1_BMTF0_iEtaAll/isolatedMB1_HQ_pT25.txt",
    "output/ZeroBias1_BMTF0_iEtaAll/isolatedMB1_HQ_pT30.txt",
]


fileNames_iEtaAll_isoMB1HO3x3 = [
    "output/ZeroBias1_BMTF0_iEtaAll_isoMB1HO3x3/isolatedMB1_HQ_pT0.txt",
    "output/ZeroBias1_BMTF0_iEtaAll_isoMB1HO3x3/isolatedMB1_HQ_pT5.txt",
    "output/ZeroBias1_BMTF0_iEtaAll_isoMB1HO3x3/isolatedMB1_HQ_pT10.txt",
    "output/ZeroBias1_BMTF0_iEtaAll_isoMB1HO3x3/isolatedMB1_HQ_pT14.txt",
    "output/ZeroBias1_BMTF0_iEtaAll_isoMB1HO3x3/isolatedMB1_HQ_pT18.txt",
    "output/ZeroBias1_BMTF0_iEtaAll_isoMB1HO3x3/isolatedMB1_HQ_pT22.txt",
    "output/ZeroBias1_BMTF0_iEtaAll_isoMB1HO3x3/isolatedMB1_HQ_pT25.txt",
    "output/ZeroBias1_BMTF0_iEtaAll_isoMB1HO3x3/isolatedMB1_HQ_pT30.txt",
]


colors = ["b", "g", "r", "c", "m", "y", "k"]


fileContent_iEta3 = [numpy.loadtxt(fName, delimiter = ",") for fName in fileNames_iEta3]
fileContent_iEta3_isoMB1HO3x3 = [numpy.loadtxt(fName, delimiter = ",") for fName in fileNames_iEta3_isoMB1HO3x3]

fileContent_iEtaAll = [numpy.loadtxt(fName, delimiter = ",") for fName in fileNames_iEtaAll]
fileContent_iEtaAll_isoMB1HO3x3 = [numpy.loadtxt(fName, delimiter = ",") for fName in fileNames_iEtaAll_isoMB1HO3x3]


rates_MB1 = []
rates_BMTF = []

rates_isoMB1 = []
rates_isoMB1HO_iEta3 = []
rates_isoMB1HO_iEta3_isoMB1HO3x3 = []
rates_isoMB1HO_iEtaAll = []
rates_isoMB1HO_iEtaAll_isoMB1HO3x3 = []

temp1 = []

for iPt  in range(0, len(pTcuts)) :
    
    #
    rate_MB1 = sum(fileContent_iEta3[iPt][:, 8])
    rates_MB1.append(rate_MB1)
    
    #
    rate_isoMB1 = sum(fileContent_iEta3[iPt][:, 10])
    rates_isoMB1.append(rate_isoMB1)
    
    #
    rate_isoMB1HO_iEta3 = sum(fileContent_iEta3[iPt][:, 12])
    rates_isoMB1HO_iEta3.append(rate_isoMB1HO_iEta3)
    
    rate_isoMB1HO_iEta3_isoMB1HO3x3 = sum(fileContent_iEta3_isoMB1HO3x3[iPt][:, 12])
    rates_isoMB1HO_iEta3_isoMB1HO3x3.append(rate_isoMB1HO_iEta3_isoMB1HO3x3)
    
    #
    rate_isoMB1HO_iEtaAll = sum(fileContent_iEtaAll[iPt][:, 12])
    rates_isoMB1HO_iEtaAll.append(rate_isoMB1HO_iEtaAll)
    
    rate_isoMB1HO_iEtaAll_isoMB1HO3x3 = sum(fileContent_iEtaAll_isoMB1HO3x3[iPt][:, 12])
    rates_isoMB1HO_iEtaAll_isoMB1HO3x3.append(rate_isoMB1HO_iEtaAll_isoMB1HO3x3)
    
    #
    rate_BMTF = sum(fileContent_iEta3[iPt][:, 6])
    rates_BMTF.append(rate_BMTF)
    
    print rate_isoMB1/rate_MB1, rate_isoMB1HO_iEta3/rate_MB1, rate_isoMB1HO_iEta3/rate_BMTF, rate_isoMB1HO_iEtaAll/rate_BMTF
    
    with numpy.errstate(divide = "ignore", invalid = "ignore") :
        
        temp = numpy.divide(fileContent_iEta3[iPt][:, 12], fileContent_iEta3[iPt][:, 6])
        
        #temp = temp[numpy.where(numpy.isnan(temp) == False)[0]]
        #temp = temp[numpy.where(numpy.isinf(temp) == False)[0]]
        
        temp[numpy.where(numpy.isnan(temp) == True)[0]] = 0
        temp[numpy.where(numpy.isinf(temp) == True)[0]] = 0
        
        temp1.append(numpy.average(temp))
    
print rates_MB1
print rates_isoMB1
print rates_isoMB1HO_iEta3
print rates_isoMB1HO_iEta3_isoMB1HO3x3
print rates_isoMB1HO_iEtaAll
print rates_isoMB1HO_iEtaAll_isoMB1HO3x3
print rates_BMTF

print temp1


fig = matplotlib.pyplot.figure(figsize = [10, 10])

matplotlib.pyplot.semilogy(pTcuts, numpy.divide(rates_isoMB1, rates_MB1), "r.-", label = "$ \\frac{isoMB1}{MB1} $", markersize = 10, linewidth = 2)
matplotlib.pyplot.semilogy(pTcuts, numpy.divide(rates_isoMB1HO_iEtaAll, rates_MB1), "g.-", label = "$ \\frac{isoMB1+HO_{wh0,1}}{MB1} $", markersize = 10, linewidth = 2)
matplotlib.pyplot.semilogy(pTcuts, numpy.divide(rates_isoMB1HO_iEtaAll_isoMB1HO3x3, rates_MB1), "g--", label = "$ \\frac{isoMB1+HO_{wh0,1}}{MB1} (n^{HO}_{3 \\times 3} \\leq 1) $", markersize = 10, linewidth = 2)
matplotlib.pyplot.semilogy(pTcuts, numpy.divide(rates_isoMB1HO_iEta3, rates_MB1), "b.-", label = "$ \\frac{isoMB1+HO_{i\\eta3}}{MB1} $", markersize = 10, linewidth = 2)
matplotlib.pyplot.semilogy(pTcuts, numpy.divide(rates_isoMB1HO_iEta3_isoMB1HO3x3, rates_MB1), "b--", label = "$ \\frac{isoMB1+HO_{i\\eta3}}{MB1} (n^{HO}_{3 \\times 3} \\leq 1) $", markersize = 10, linewidth = 2)

matplotlib.pyplot.legend(
    loc = 4,
    numpoints = 1,
    fontsize = 20
)

matplotlib.pyplot.xticks(pTcuts, fontsize = 25)
matplotlib.pyplot.yticks(fontsize = 25)

matplotlib.pyplot.xlabel(r"$ p_{T} $ cut [GeV]", fontsize = 30)
matplotlib.pyplot.ylabel("Relative rate", fontsize = 30)

matplotlib.pyplot.xlim(xmin = 0, xmax = 30)
matplotlib.pyplot.ylim(ymin = 1e-2, ymax = 2)

matplotlib.pyplot.grid(True)
matplotlib.pyplot.tight_layout()


matplotlib.pyplot.savefig("plots/MBgap/MB1rate.pdf")
matplotlib.pyplot.close(fig)



fig = matplotlib.pyplot.figure(figsize = [10, 10])

matplotlib.pyplot.semilogy(pTcuts, numpy.divide(rates_isoMB1HO_iEtaAll, rates_BMTF), "g.-", label = "$ \\frac{isoMB1+HO_{wh0,1}}{BMTF} $", markersize = 10, linewidth = 2)
matplotlib.pyplot.semilogy(pTcuts, numpy.divide(rates_isoMB1HO_iEtaAll_isoMB1HO3x3, rates_BMTF), "g--", label = "$ \\frac{isoMB1+HO_{wh0,1}}{BMTF} (n^{HO}_{3 \\times 3} \\leq 1) $", markersize = 10, linewidth = 2)
matplotlib.pyplot.semilogy(pTcuts, numpy.divide(rates_isoMB1HO_iEta3, rates_BMTF), "b.-", label = "$ \\frac{isoMB1+HO_{i\\eta3}}{BMTF} $", markersize = 10, linewidth = 2)
matplotlib.pyplot.semilogy(pTcuts, numpy.divide(rates_isoMB1HO_iEta3_isoMB1HO3x3, rates_BMTF), "b--", label = "$ \\frac{isoMB1+HO_{i\\eta3}}{BMTF} (n^{HO}_{3 \\times 3} \\leq 1) $", markersize = 10, linewidth = 2)

matplotlib.pyplot.legend(
    loc = 4,
    numpoints = 1,
    fontsize = 20
)

matplotlib.pyplot.xticks(pTcuts, fontsize = 25)
matplotlib.pyplot.yticks(fontsize = 25)

matplotlib.pyplot.xlabel(r"$ p_{T} $ cut [GeV]", fontsize = 30)
matplotlib.pyplot.ylabel("Relative rate", fontsize = 30)

matplotlib.pyplot.xlim(xmin = 0, xmax = 30)
matplotlib.pyplot.ylim(ymin = 1e-2, ymax = 15)

matplotlib.pyplot.grid(True)
matplotlib.pyplot.tight_layout()


matplotlib.pyplot.savefig("plots/MBgap/BMTFrate.pdf")
matplotlib.pyplot.close(fig)
