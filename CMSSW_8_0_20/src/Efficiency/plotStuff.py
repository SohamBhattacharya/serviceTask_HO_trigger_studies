import numpy

import ROOT
from ROOT import TAxis
from ROOT import TCanvas
from ROOT import TFile
from ROOT import TH1F
from ROOT import TH2F
from ROOT import THStack
from ROOT import TLegend
from ROOT import TStyle


initVal = -9999

numberFormat_int = ".0f"
numberFormat_float = ".3f"


ROOT.gStyle.SetPalette(ROOT.kPastel)
ROOT.gStyle.SetOptStat(0)
ROOT.gStyle.SetPaintTextFormat(numberFormat_float)
ROOT.gStyle.SetTitleH(0.035)


lineColor = {}

lineColor["BMTF"] = 1
lineColor["MB1"] = 6
lineColor["MB2"] = 4
lineColor["MB12"] = 2
lineColor["MB34"] = 3
lineColor["MB1234"] = 4
lineColor["MB34_MB3HO"] = 6
lineColor["isoMB1HO"] = 2
lineColor["isoMB12HO"] = 4


class HistogramDetails :
    
    rootFileName = ""
    rootFile = 0
    
    histName = ""
    histTitle = ""
    histLabel = ""
    
    lineColor = 4
    lineStyle = 1
    lineWidth = 1
    
    hist = 0
    
    xTitle = ""
    yTitle = ""
    
    xMin = initVal
    xMax = initVal
    
    yMin = initVal
    yMax = initVal
    
    zMin = initVal
    zMax = initVal
    
    logX = False
    logY = False
    logZ = False
    
    gridX = False
    gridY = False
    
    drawOption = "hist"
    
    outFileName = ""
    outFileName_suffix = ""
    
    
    def getHist(self, projection = "", startBin = 0, endBin = -1, findStartBin = False, findEndBin = False, suffix = "") :
        
        print "File:", self.rootFileName
        print "Name:", self.histName
        
        self.rootFile = TFile(self.rootFileName)
        
        axis = 0
        
        if (projection == "X") :
            
            hist_temp = self.rootFile.Get(self.histName).Clone()
            axis = hist_temp.GetYaxis()
        
        elif (projection == "Y") :
            
            hist_temp = self.rootFile.Get(self.histName).Clone()
            axis = hist_temp.GetXaxis()
        
        if (projection != "" and findStartBin) :
            
            startBin = axis.FindBin(startBin)
        
        if (projection != "" and findEndBin) :
            
            endBin = axis.FindBin(endBin)
        
        # Get histogram
        if (projection == "") :
            
            self.hist = self.rootFile.Get(self.histName).Clone()
            self.hist.Sumw2()
        
        elif (projection == "X") :
            
            print "Projection X"
            self.hist = self.rootFile.Get(self.histName).Clone().ProjectionX(self.histName + "_px" + suffix, startBin, endBin)
            self.hist.Sumw2()
        
        elif (projection == "Y") :
            
            print "Projection Y"
            self.hist = self.rootFile.Get(self.histName).Clone().ProjectionY(self.histName + "_py" + suffix, startBin, endBin)
            self.hist.Sumw2()
        
        else :
            
            print "Wrong projection option to HistogramDetails.getHist(...)"
            exit(1)


def plot1D(list_histDetails,
    stackDrawOption = "nostack",
    title = "",
    xTitle = "", yTitle = "",
    xMin = initVal, xMax = initVal,
    yMin = initVal, yMax = initVal,
    logX = False, logY = False,
    gridX = False, gridY = False,
    drawLegend = True,
    legendTextSize = -1,
    legendPos = "UR",
    fixAlphanumericBinLabels = False,
    outFileName = "outFile",
    outFileName_suffix = "",
    ) :
    
    canvas = TCanvas("canvas", "canvas")
    canvas.SetCanvasSize(800, 600)
    
    legend = 0
    
    if(legendPos == "UR") :
        
        legend = TLegend(0.6, 0.6, 0.895, 0.895)
    
    elif(legendPos == "LR") :
        
        legend = TLegend(0.5, 0.105, 0.895, 0.40)
    
    else :
        
        print "Wrong legend position option:", legendPos
        exit(1)
    
    if (legendTextSize > 0) :
        
        legend.SetTextSize(legendTextSize)
    
    stack = THStack()
    
    if (fixAlphanumericBinLabels) :
        
        h1_temp = TH1F("temp", "temp", list_histDetails[0].hist.GetXaxis().GetNbins(), list_histDetails[0].hist.GetXaxis().GetXmin(), list_histDetails[0].hist.GetXaxis().GetXmax())
        stack.Add(h1_temp)
    
    for iHist in range(0, len(list_histDetails)) :
        
        list_histDetails[iHist].hist.SetLineColor(list_histDetails[iHist].lineColor)
        list_histDetails[iHist].hist.SetLineStyle(list_histDetails[iHist].lineStyle)
        list_histDetails[iHist].hist.SetLineWidth(list_histDetails[iHist].lineWidth)
        
        stack.Add(list_histDetails[iHist].hist, list_histDetails[iHist].drawOption)
        legend.AddEntry(list_histDetails[iHist].hist, list_histDetails[iHist].histLabel)
    
    stack.Draw(stackDrawOption)
    
    if (drawLegend) :
        
        legend.Draw()
    
    if (fixAlphanumericBinLabels) :
        
        for iBin in range(0, stack.GetXaxis().GetNbins()) :
            
            stack.GetXaxis().SetBinLabel(iBin, list_histDetails[0].hist.GetXaxis().GetBinLabel(iBin))
        
        stack.GetXaxis().SetLabelSize(0.025)
        stack.GetXaxis().LabelsOption("v")
    
    stack.GetXaxis().SetTitle(xTitle)
    
    stack.GetYaxis().SetTitle(yTitle)
    stack.GetYaxis().SetTitleOffset(1.15)
    
    stack.SetTitle(title)
    
    # X range
    if (xMin != initVal and xMax != initVal) :
        
        stack.GetXaxis().SetRangeUser(
            xMin,
            xMax
        )
    
    elif (xMin != initVal) :
        
        stack.GetXaxis().SetRangeUser(
            xMin,
            stack.GetXaxis().GetXmax()
        )
    
    elif (xMax != initVal) :
        
        stack.GetXaxis().SetRangeUser(
            stack.GetXaxis().GetXmin(),
            xMax
        )
    
    # Y range
    if (yMin != initVal) :
        
        stack.SetMinimum(yMin)
    
    if (yMax != initVal) :
        
        stack.SetMaximum(yMax)
    
    stack.GetXaxis().CenterTitle(True)
    stack.GetYaxis().CenterTitle(True)
    
    ROOT.TGaxis.SetMaxDigits(3)
    
    canvas.SetLogx(logX)
    canvas.SetLogy(logY)
    
    canvas.SetGridx(gridX)
    canvas.SetGridy(gridY)
    
    #canvas.SetRightMargin(0.13)
    
    outFileName = outFileName + ("_"*(outFileName_suffix != "")) + outFileName_suffix + ".pdf"
    print "Output:", outFileName
    
    canvas.SaveAs(outFileName)
    
    print "\n"


def plot2D(histDetails) :
    
    canvas = TCanvas("canvas", "canvas")
    canvas.SetCanvasSize(800, 800)
    
    # X range
    if (histDetails.xMin != initVal and histDetails.xMax != initVal) :
        
        histDetails.hist.GetXaxis().SetRangeUser(
            histDetails.xMin,
            histDetails.xMax
        )
    
    elif (histDetails.xMin != initVal) :
        
        histDetails.hist.GetXaxis().SetRangeUser(
            histDetails.xMin,
            histDetails.hist.GetXaxis().GetXmax()
        )
    
    elif (histDetails.xMax != initVal) :
        
        histDetails.hist.GetXaxis().SetRangeUser(
            histDetails.hist.GetXaxis().GetXmin(),
            histDetails.xMax
        )
    
    # Y range
    if (histDetails.yMin != initVal and histDetails.yMax != initVal) :
        
        histDetails.hist.GetYaxis().SetRangeUser(
            histDetails.yMin,
            histDetails.yMax
        )
    
    elif (histDetails.yMin != initVal) :
        
        histDetails.hist.GetYaxis().SetRangeUser(
            histDetails.yMin,
            histDetails.hist.GetYaxis().GetXmax()
        )
    
    elif (histDetails.yMax != initVal) :
        
        histDetails.hist.GetYaxis().SetRangeUser(
            histDetails.hist.GetYaxis().GetXmin(),
            histDetails.yMax
        )
    
    # Z range
    if (histDetails.zMin != initVal) :
        
        histDetails.hist.SetMinimum(histDetails.zMin)
    
    if (histDetails.zMax != initVal) :
        
        histDetails.hist.SetMaximum(histDetails.zMax)
    
    histDetails.hist.GetXaxis().SetTitle(histDetails.xTitle)
    
    histDetails.hist.GetYaxis().SetTitle(histDetails.yTitle)
    histDetails.hist.GetYaxis().SetTitleOffset(1.15)
    
    histDetails.hist.GetXaxis().CenterTitle(True)
    histDetails.hist.GetYaxis().CenterTitle(True)
    
    #histDetails.hist.SetStats(0)
    histDetails.hist.SetTitle(histDetails.histTitle)
    
    ROOT.TGaxis.SetMaxDigits(3)
    
    canvas.SetLogx(histDetails.logX)
    canvas.SetLogy(histDetails.logY)
    canvas.SetLogz(histDetails.logZ)
    
    canvas.SetGridx(histDetails.gridX)
    canvas.SetGridy(histDetails.gridY)
    
    canvas.SetRightMargin(0.13)
    
    histDetails.hist.Draw(histDetails.drawOption)
    
    outFileName = histDetails.outFileName + ("_"*(histDetails.outFileName_suffix != "")) + histDetails.outFileName_suffix + ".pdf"
    print "Output:", outFileName
    
    canvas.SaveAs(outFileName)
    
    print "\n"


####################################################################################################
h2_usedMu_pT_vs_eta = HistogramDetails()
h2_usedMu_pT_vs_eta.rootFileName = "output/MET_Run2017C-v1_RAW/DTNtuple_all_efficiency.root"
h2_usedMu_pT_vs_eta.histName = "usedMu_pT_vs_eta"
h2_usedMu_pT_vs_eta.histTitle = "#mu^{reco, used} p_{T} vs. #eta"
h2_usedMu_pT_vs_eta.outFileName = "plots/lowPt/usedMu_pT_vs_eta"
h2_usedMu_pT_vs_eta.outFileName_suffix = "MET"
h2_usedMu_pT_vs_eta.drawOption = "colz"
h2_usedMu_pT_vs_eta.xMin = -1
h2_usedMu_pT_vs_eta.xMax = 1
h2_usedMu_pT_vs_eta.yMax = 20
h2_usedMu_pT_vs_eta.yTitle = "p_{T} [GeV]"
h2_usedMu_pT_vs_eta.xTitle = "#eta"
h2_usedMu_pT_vs_eta.getHist()
plot2D(h2_usedMu_pT_vs_eta)


####################################################################################################
h2_usedMu_pT_vs_stationMask = HistogramDetails()
h2_usedMu_pT_vs_stationMask.rootFileName = "output/MET_Run2017C-v1_RAW/DTNtuple_all_efficiency.root"
h2_usedMu_pT_vs_stationMask.histName = "usedMu_pT_vs_stationMask"
h2_usedMu_pT_vs_stationMask.histTitle = "#mu^{reco, used} p_{T} vs. stations hit [LQ+HQ DTTP]"
h2_usedMu_pT_vs_stationMask.outFileName = "plots/lowPt/usedMu_pT_vs_stationMask_LQHQ"
h2_usedMu_pT_vs_stationMask.outFileName_suffix = "MET"
h2_usedMu_pT_vs_stationMask.drawOption = "colz text"
h2_usedMu_pT_vs_stationMask.xMax = 17
h2_usedMu_pT_vs_stationMask.yMax = 10
h2_usedMu_pT_vs_stationMask.yTitle = "p_{T} [GeV]"
h2_usedMu_pT_vs_stationMask.getHist()
ROOT.gStyle.SetPaintTextFormat(numberFormat_int)
plot2D(h2_usedMu_pT_vs_stationMask)
ROOT.gStyle.SetPaintTextFormat(numberFormat_float)


####################################################################################################
h2_usedMu_pT_vs_stationMask = HistogramDetails()
h2_usedMu_pT_vs_stationMask.rootFileName = "output/MET_Run2017C-v1_RAW/DTNtuple_all_efficiency.root"
h2_usedMu_pT_vs_stationMask.histName = "HQ/usedMu_pT_vs_stationMask"
h2_usedMu_pT_vs_stationMask.histTitle = "#mu^{reco, used} p_{T} vs. stations hit [HQ DTTP]"
h2_usedMu_pT_vs_stationMask.outFileName = "plots/lowPt/usedMu_pT_vs_stationMask_HQ"
h2_usedMu_pT_vs_stationMask.outFileName_suffix = "MET"
h2_usedMu_pT_vs_stationMask.drawOption = "colz text"
h2_usedMu_pT_vs_stationMask.xMax = 17
h2_usedMu_pT_vs_stationMask.yMax = 10
h2_usedMu_pT_vs_stationMask.yTitle = "p_{T} [GeV]"
h2_usedMu_pT_vs_stationMask.getHist()
ROOT.gStyle.SetPaintTextFormat(numberFormat_int)
plot2D(h2_usedMu_pT_vs_stationMask)
ROOT.gStyle.SetPaintTextFormat(numberFormat_float)


####################################################################################################
h2_usedMu_eta_vs_stationMask = HistogramDetails()
h2_usedMu_eta_vs_stationMask.rootFileName = "output/MET_Run2017C-v1_RAW/DTNtuple_all_efficiency.root"
h2_usedMu_eta_vs_stationMask.histName = "usedMu_eta_vs_stationMask"
h2_usedMu_eta_vs_stationMask.histTitle = "#mu^{reco, used} #eta vs. stations hit [LQ+HQ DTTP]"
h2_usedMu_eta_vs_stationMask.outFileName = "plots/lowPt/usedMu_eta_vs_stationMask_LQHQ"
h2_usedMu_eta_vs_stationMask.outFileName_suffix = "MET"
h2_usedMu_eta_vs_stationMask.drawOption = "colz text"
h2_usedMu_eta_vs_stationMask.xMax = 17
h2_usedMu_eta_vs_stationMask.yMin = -1
h2_usedMu_eta_vs_stationMask.yMax = 1
h2_usedMu_eta_vs_stationMask.yTitle = "#eta"
h2_usedMu_eta_vs_stationMask.getHist()
ROOT.gStyle.SetPaintTextFormat(numberFormat_int)
plot2D(h2_usedMu_eta_vs_stationMask)
ROOT.gStyle.SetPaintTextFormat(numberFormat_float)


####################################################################################################
h2_usedMu_eta_vs_stationMask = HistogramDetails()
h2_usedMu_eta_vs_stationMask.rootFileName = "output/MET_Run2017C-v1_RAW/DTNtuple_all_efficiency.root"
h2_usedMu_eta_vs_stationMask.histName = "HQ/usedMu_eta_vs_stationMask"
h2_usedMu_eta_vs_stationMask.histTitle = "#mu^{reco, used} #eta vs. stations hit [HQ DTTP]"
h2_usedMu_eta_vs_stationMask.outFileName = "plots/lowPt/usedMu_eta_vs_stationMask_HQ"
h2_usedMu_eta_vs_stationMask.outFileName_suffix = "MET"
h2_usedMu_eta_vs_stationMask.drawOption = "colz text"
h2_usedMu_eta_vs_stationMask.xMax = 17
h2_usedMu_eta_vs_stationMask.yMin = -1
h2_usedMu_eta_vs_stationMask.yMax = 1
h2_usedMu_eta_vs_stationMask.yTitle = "#eta"
h2_usedMu_eta_vs_stationMask.getHist()
ROOT.gStyle.SetPaintTextFormat(numberFormat_int)
plot2D(h2_usedMu_eta_vs_stationMask)
ROOT.gStyle.SetPaintTextFormat(numberFormat_float)


####################################################################################################
h2_unusedMu_pT_vs_eta = HistogramDetails()
h2_unusedMu_pT_vs_eta.rootFileName = "output/MET_Run2017C-v1_RAW/DTNtuple_all_efficiency.root"
h2_unusedMu_pT_vs_eta.histName = "unusedMu_pT_vs_eta"
h2_unusedMu_pT_vs_eta.histTitle = "#mu^{reco, unused} p_{T} vs. #eta"
h2_unusedMu_pT_vs_eta.outFileName = "plots/lowPt/unusedMu_pT_vs_eta"
h2_unusedMu_pT_vs_eta.outFileName_suffix = "MET"
h2_unusedMu_pT_vs_eta.drawOption = "colz"
h2_unusedMu_pT_vs_eta.xMin = -1
h2_unusedMu_pT_vs_eta.xMax = 1
h2_unusedMu_pT_vs_eta.yMax = 20
h2_unusedMu_pT_vs_eta.yTitle = "p_{T} [GeV]"
h2_unusedMu_pT_vs_eta.xTitle = "#eta"
h2_unusedMu_pT_vs_eta.getHist()
plot2D(h2_unusedMu_pT_vs_eta)


####################################################################################################
h2_unusedMu_pT_vs_stationMask = HistogramDetails()
h2_unusedMu_pT_vs_stationMask.rootFileName = "output/MET_Run2017C-v1_RAW/DTNtuple_all_efficiency.root"
h2_unusedMu_pT_vs_stationMask.histName = "unusedMu_pT_vs_stationMask"
h2_unusedMu_pT_vs_stationMask.histTitle = "#mu^{reco, unused} p_{T} vs. stations hit [LQ+HQ DTTP]"
h2_unusedMu_pT_vs_stationMask.outFileName = "plots/lowPt/unusedMu_pT_vs_stationMask_LQHQ"
h2_unusedMu_pT_vs_stationMask.outFileName_suffix = "MET"
h2_unusedMu_pT_vs_stationMask.drawOption = "colz text"
h2_unusedMu_pT_vs_stationMask.xMax = 17
h2_unusedMu_pT_vs_stationMask.yMax = 10
h2_unusedMu_pT_vs_stationMask.yTitle = "p_{T} [GeV]"
h2_unusedMu_pT_vs_stationMask.getHist()
ROOT.gStyle.SetPaintTextFormat(numberFormat_int)
plot2D(h2_unusedMu_pT_vs_stationMask)
ROOT.gStyle.SetPaintTextFormat(numberFormat_float)


####################################################################################################
h2_unusedMu_pT_vs_stationMask = HistogramDetails()
h2_unusedMu_pT_vs_stationMask.rootFileName = "output/MET_Run2017C-v1_RAW/DTNtuple_all_efficiency.root"
h2_unusedMu_pT_vs_stationMask.histName = "HQ/unusedMu_pT_vs_stationMask"
h2_unusedMu_pT_vs_stationMask.histTitle = "#mu^{reco, unused} p_{T} vs. stations hit [HQ DTTP]"
h2_unusedMu_pT_vs_stationMask.outFileName = "plots/lowPt/unusedMu_pT_vs_stationMask_HQ"
h2_unusedMu_pT_vs_stationMask.outFileName_suffix = "MET"
h2_unusedMu_pT_vs_stationMask.drawOption = "colz text"
h2_unusedMu_pT_vs_stationMask.xMax = 17
h2_unusedMu_pT_vs_stationMask.yMax = 10
h2_unusedMu_pT_vs_stationMask.yTitle = "p_{T} [GeV]"
h2_unusedMu_pT_vs_stationMask.getHist()
ROOT.gStyle.SetPaintTextFormat(numberFormat_int)
plot2D(h2_unusedMu_pT_vs_stationMask)
ROOT.gStyle.SetPaintTextFormat(numberFormat_float)


####################################################################################################
h2_unusedMu_eta_vs_stationMask = HistogramDetails()
h2_unusedMu_eta_vs_stationMask.rootFileName = "output/MET_Run2017C-v1_RAW/DTNtuple_all_efficiency.root"
h2_unusedMu_eta_vs_stationMask.histName = "unusedMu_eta_vs_stationMask"
h2_unusedMu_eta_vs_stationMask.histTitle = "#mu^{reco, unused} #eta vs. stations hit [LQ+HQ DTTP]"
h2_unusedMu_eta_vs_stationMask.outFileName = "plots/lowPt/unusedMu_eta_vs_stationMask_LQHQ"
h2_unusedMu_eta_vs_stationMask.outFileName_suffix = "MET"
h2_unusedMu_eta_vs_stationMask.drawOption = "colz text"
h2_unusedMu_eta_vs_stationMask.xMax = 17
h2_unusedMu_eta_vs_stationMask.yMin = -1
h2_unusedMu_eta_vs_stationMask.yMax = 1
h2_unusedMu_eta_vs_stationMask.yTitle = "#eta"
h2_unusedMu_eta_vs_stationMask.getHist()
ROOT.gStyle.SetPaintTextFormat(numberFormat_int)
plot2D(h2_unusedMu_eta_vs_stationMask)
ROOT.gStyle.SetPaintTextFormat(numberFormat_float)


####################################################################################################
h2_unusedMu_eta_vs_stationMask = HistogramDetails()
h2_unusedMu_eta_vs_stationMask.rootFileName = "output/MET_Run2017C-v1_RAW/DTNtuple_all_efficiency.root"
h2_unusedMu_eta_vs_stationMask.histName = "HQ/unusedMu_eta_vs_stationMask"
h2_unusedMu_eta_vs_stationMask.histTitle = "#mu^{reco, unused} #eta vs. stations hit [HQ DTTP]"
h2_unusedMu_eta_vs_stationMask.outFileName = "plots/lowPt/unusedMu_eta_vs_stationMask_HQ"
h2_unusedMu_eta_vs_stationMask.outFileName_suffix = "MET"
h2_unusedMu_eta_vs_stationMask.drawOption = "colz text"
h2_unusedMu_eta_vs_stationMask.xMax = 17
h2_unusedMu_eta_vs_stationMask.yMin = -1
h2_unusedMu_eta_vs_stationMask.yMax = 1
h2_unusedMu_eta_vs_stationMask.yTitle = "#eta"
h2_unusedMu_eta_vs_stationMask.getHist()
ROOT.gStyle.SetPaintTextFormat(numberFormat_int)
plot2D(h2_unusedMu_eta_vs_stationMask)
ROOT.gStyle.SetPaintTextFormat(numberFormat_float)


####################################################################################################
h1_unusedMu_eta_num = HistogramDetails()
h1_unusedMu_eta_num.rootFileName = "output/MET_Run2017C-v1_RAW/DTNtuple_all_efficiency.root"
h1_unusedMu_eta_num.histName = "HQ/unusedMu_eta_vs_stationMask"
h1_unusedMu_eta_num.drawOption = "hist E"
h1_unusedMu_eta_num.lineWidth = 2
h1_unusedMu_eta_num.lineColor = 4
h1_unusedMu_eta_num.getHist(projection = "Y", startBin = 3, endBin = 3, suffix = "MB2")

h1_unusedMu_eta_den = HistogramDetails()
h1_unusedMu_eta_den.rootFileName = "output/MET_Run2017C-v1_RAW/DTNtuple_all_efficiency.root"
h1_unusedMu_eta_den.histName = "HQ/unusedMu_eta_vs_stationMask"
h1_unusedMu_eta_den.getHist(projection = "Y", startBin = 2, endBin = 2, suffix = "MB1")

h1_unusedMu_eta_num.hist.Divide(h1_unusedMu_eta_den.hist)

plot1D(
    [h1_unusedMu_eta_num],
    title = "unused-#mu^{reco}_{MB2} / unused-#mu^{reco}_{MB1} [HQ DTTP]",
    xTitle = "#eta_{reco-#mu}", yTitle = "ratio",
    xMin = -1,
    xMax = 1,
    yMax = 4,
    gridX = True,
    gridY = True,
    drawLegend = False,
    outFileName = "plots/lowPt/unusedMu_eta_ratio_HQ",
    outFileName_suffix = "MET",
)


####################################################################################################
h2_unusedMu_pT_vs_stationMask = HistogramDetails()
h2_unusedMu_pT_vs_stationMask.rootFileName = "output/MET_Run2017C-v1_RAW/DTNtuple_all_efficiency.root"
h2_unusedMu_pT_vs_stationMask.histName = "unusedMu_pT_vs_stationMask"
h2_unusedMu_pT_vs_stationMask.histTitle = "#mu^{reco, unused} p_{T} vs. stations hit [LQ+HQ DTTP]"
h2_unusedMu_pT_vs_stationMask.outFileName = "plots/lowPt/unusedMu_pT_vs_stationMask_LQHQ"
h2_unusedMu_pT_vs_stationMask.outFileName_suffix = "MET"
h2_unusedMu_pT_vs_stationMask.drawOption = "colz text"
h2_unusedMu_pT_vs_stationMask.xMax = 17
h2_unusedMu_pT_vs_stationMask.yMax = 10
h2_unusedMu_pT_vs_stationMask.yTitle = "p_{T} [GeV]"
h2_unusedMu_pT_vs_stationMask.getHist()
ROOT.gStyle.SetPaintTextFormat(numberFormat_int)
plot2D(h2_unusedMu_pT_vs_stationMask)
ROOT.gStyle.SetPaintTextFormat(numberFormat_float)


####################################################################################################
h2_unusedMu_eta_vs_stationMask = HistogramDetails()
h2_unusedMu_eta_vs_stationMask.rootFileName = "output/MET_Run2017C-v1_RAW/DTNtuple_all_efficiency.root"
h2_unusedMu_eta_vs_stationMask.histName = "unusedMu_eta_vs_stationMask"
h2_unusedMu_eta_vs_stationMask.histTitle = "#mu^{reco, unused} #eta vs. stations hit [LQ+HQ DTTP]"
h2_unusedMu_eta_vs_stationMask.outFileName = "plots/lowPt/unusedMu_eta_vs_stationMask_LQHQ"
h2_unusedMu_eta_vs_stationMask.outFileName_suffix = "MET"
h2_unusedMu_eta_vs_stationMask.drawOption = "colz text"
h2_unusedMu_eta_vs_stationMask.xMax = 17
h2_unusedMu_eta_vs_stationMask.yMin = -1
h2_unusedMu_eta_vs_stationMask.yMax = 1
h2_unusedMu_eta_vs_stationMask.yTitle = "#eta"
h2_unusedMu_eta_vs_stationMask.getHist()
ROOT.gStyle.SetPaintTextFormat(numberFormat_int)
plot2D(h2_unusedMu_eta_vs_stationMask)
ROOT.gStyle.SetPaintTextFormat(numberFormat_float)


####################################################################################################
h1_unusedMu_eta_num = HistogramDetails()
h1_unusedMu_eta_num.rootFileName = "output/MET_Run2017C-v1_RAW/DTNtuple_all_efficiency.root"
h1_unusedMu_eta_num.histName = "unusedMu_eta_vs_stationMask"
h1_unusedMu_eta_num.drawOption = "hist E"
h1_unusedMu_eta_num.lineWidth = 2
h1_unusedMu_eta_num.lineColor = 4
h1_unusedMu_eta_num.getHist(projection = "Y", startBin = 3, endBin = 3, suffix = "MB2")

h1_unusedMu_eta_den = HistogramDetails()
h1_unusedMu_eta_den.rootFileName = "output/MET_Run2017C-v1_RAW/DTNtuple_all_efficiency.root"
h1_unusedMu_eta_den.histName = "unusedMu_eta_vs_stationMask"
h1_unusedMu_eta_den.getHist(projection = "Y", startBin = 2, endBin = 2, suffix = "MB1")

h1_unusedMu_eta_num.hist.Divide(h1_unusedMu_eta_den.hist)

plot1D(
    [h1_unusedMu_eta_num],
    title = "unused-#mu^{reco}_{MB2} / unused-#mu^{reco}_{MB1} [LQ+HQ DTTP]",
    xTitle = "#eta_{reco-#mu}", yTitle = "ratio",
    xMin = -1,
    xMax = 1,
    yMax = 4,
    gridX = True,
    gridY = True,
    drawLegend = False,
    outFileName = "plots/lowPt/unusedMu_eta_ratio_LQHQ",
    outFileName_suffix = "MET",
)


####################################################################################################
h2_BMTF_muMatched_pT_vs_trackType = HistogramDetails()
h2_BMTF_muMatched_pT_vs_trackType.rootFileName = "output/MET_Run2017C-v1_RAW/DTNtuple_all_efficiency.root"
h2_BMTF_muMatched_pT_vs_trackType.histName = "BMTF_muMatched_pT_vs_trackType"
h2_BMTF_muMatched_pT_vs_trackType.histTitle = "BMTF^{#mu-matched} p_{T} vs. track type"
h2_BMTF_muMatched_pT_vs_trackType.outFileName = "plots/lowPt/BMTF_muMatched_pT_vs_trackType"
h2_BMTF_muMatched_pT_vs_trackType.outFileName_suffix = "MET"
h2_BMTF_muMatched_pT_vs_trackType.drawOption = "colz"
h2_BMTF_muMatched_pT_vs_trackType.xMax = 17
h2_BMTF_muMatched_pT_vs_trackType.yMax = 20
h2_BMTF_muMatched_pT_vs_trackType.yTitle = "p_{T} [GeV]"
h2_BMTF_muMatched_pT_vs_trackType.getHist()
plot2D(h2_BMTF_muMatched_pT_vs_trackType)


####################################################################################################
h2_isoMB1HO_nNotMuMatched_vs_nUnusedMu = HistogramDetails()
h2_isoMB1HO_nNotMuMatched_vs_nUnusedMu.rootFileName = "output/MET_Run2017C-v1_RAW/DTNtuple_all_efficiency.root"
h2_isoMB1HO_nNotMuMatched_vs_nUnusedMu.histName = "isoMB1HO_nNotMuMatched_vs_nUnusedMu"
h2_isoMB1HO_nNotMuMatched_vs_nUnusedMu.histTitle = "n^{not #mu-matched}_{isoMB1+HO} vs. n^{unused}_{reco-#mu}"
h2_isoMB1HO_nNotMuMatched_vs_nUnusedMu.outFileName = "plots/lowPt/isoMB1HO_nNotMuMatched_vs_nUnusedMu"
h2_isoMB1HO_nNotMuMatched_vs_nUnusedMu.outFileName_suffix = "MET"
h2_isoMB1HO_nNotMuMatched_vs_nUnusedMu.drawOption = "colz text45"
h2_isoMB1HO_nNotMuMatched_vs_nUnusedMu.xMax = 4
h2_isoMB1HO_nNotMuMatched_vs_nUnusedMu.yMax = 4
h2_isoMB1HO_nNotMuMatched_vs_nUnusedMu.xTitle = "n^{unused}_{reco-#mu}"
h2_isoMB1HO_nNotMuMatched_vs_nUnusedMu.yTitle = "n^{not #mu-matched}_{isoMB1+HO}"
h2_isoMB1HO_nNotMuMatched_vs_nUnusedMu.getHist()
h2_isoMB1HO_nNotMuMatched_vs_nUnusedMu.hist.GetXaxis().SetNdivisions(-104)
h2_isoMB1HO_nNotMuMatched_vs_nUnusedMu.hist.GetYaxis().SetNdivisions(-104)
h2_isoMB1HO_nNotMuMatched_vs_nUnusedMu.hist.Scale(1.0 / h2_isoMB1HO_nNotMuMatched_vs_nUnusedMu.hist.Integral())
h2_isoMB1HO_nNotMuMatched_vs_nUnusedMu.hist.SetMarkerSize(2.5)
plot2D(h2_isoMB1HO_nNotMuMatched_vs_nUnusedMu)


####################################################################################################
h1_unusedMB1mu_wh0_phiB = HistogramDetails()
h1_unusedMB1mu_wh0_phiB.rootFileName = "output/MET_Run2017C-v1_RAW/DTNtuple_all_efficiency.root"
h1_unusedMB1mu_wh0_phiB.histName = "HQ/unusedMB1mu_wh0_phiB"
h1_unusedMB1mu_wh0_phiB.lineColor = lineColor["MB1"]
h1_unusedMB1mu_wh0_phiB.lineWidth = 2
h1_unusedMB1mu_wh0_phiB.lineStyle = 1
h1_unusedMB1mu_wh0_phiB.getHist()
#h1_unusedMB1mu_wh0_phiB.hist.Rebin(5)
h1_unusedMB1mu_wh0_phiB.histLabel = "#mu^{reco, unused}_{MB1, wh0} [#sigma = %0.2f]" %(h1_unusedMB1mu_wh0_phiB.hist.GetStdDev())
h1_unusedMB1mu_wh0_phiB.hist.Scale(1.0/h1_unusedMB1mu_wh0_phiB.hist.Integral())

h1_unusedMB1mu_wh1_phiB = HistogramDetails()
h1_unusedMB1mu_wh1_phiB.rootFileName = "output/MET_Run2017C-v1_RAW/DTNtuple_all_efficiency.root"
h1_unusedMB1mu_wh1_phiB.histName = "HQ/unusedMB1mu_wh1_phiB"
h1_unusedMB1mu_wh1_phiB.lineColor = lineColor["MB1"]
h1_unusedMB1mu_wh1_phiB.lineWidth = 2
h1_unusedMB1mu_wh1_phiB.lineStyle = 2
h1_unusedMB1mu_wh1_phiB.getHist()
#h1_unusedMB1mu_wh1_phiB.hist.Rebin(5)
h1_unusedMB1mu_wh1_phiB.histLabel = "#mu^{reco, unused}_{MB1, wh1} [#sigma = %0.2f]" %(h1_unusedMB1mu_wh1_phiB.hist.GetStdDev())
h1_unusedMB1mu_wh1_phiB.hist.Scale(1.0/h1_unusedMB1mu_wh1_phiB.hist.Integral())

h1_unusedMB2mu_wh0_phiB = HistogramDetails()
h1_unusedMB2mu_wh0_phiB.rootFileName = "output/MET_Run2017C-v1_RAW/DTNtuple_all_efficiency.root"
h1_unusedMB2mu_wh0_phiB.histName = "HQ/unusedMB2mu_wh0_phiB"
h1_unusedMB2mu_wh0_phiB.lineColor = lineColor["MB2"]
h1_unusedMB2mu_wh0_phiB.lineWidth = 2
h1_unusedMB2mu_wh0_phiB.lineStyle = 1
h1_unusedMB2mu_wh0_phiB.getHist()
#h1_unusedMB2mu_wh0_phiB.hist.Rebin(5)
h1_unusedMB2mu_wh0_phiB.histLabel = "#mu^{reco, unused}_{MB2, wh0} [#sigma = %0.2f]" %(h1_unusedMB2mu_wh0_phiB.hist.GetStdDev())
h1_unusedMB2mu_wh0_phiB.hist.Scale(1.0/h1_unusedMB2mu_wh0_phiB.hist.Integral())

h1_unusedMB2mu_wh1_phiB = HistogramDetails()
h1_unusedMB2mu_wh1_phiB.rootFileName = "output/MET_Run2017C-v1_RAW/DTNtuple_all_efficiency.root"
h1_unusedMB2mu_wh1_phiB.histName = "HQ/unusedMB2mu_wh1_phiB"
h1_unusedMB2mu_wh1_phiB.lineColor = lineColor["MB2"]
h1_unusedMB2mu_wh1_phiB.lineWidth = 2
h1_unusedMB2mu_wh1_phiB.lineStyle = 2
h1_unusedMB2mu_wh1_phiB.getHist()
#h1_unusedMB2mu_wh1_phiB.hist.Rebin(5)
h1_unusedMB2mu_wh1_phiB.histLabel = "#mu^{reco, unused}_{MB2, wh1} [#sigma = %0.2f]" %(h1_unusedMB2mu_wh1_phiB.hist.GetStdDev())
h1_unusedMB2mu_wh1_phiB.hist.Scale(1.0/h1_unusedMB2mu_wh1_phiB.hist.Integral())

plot1D(
    [h1_unusedMB1mu_wh0_phiB, h1_unusedMB1mu_wh1_phiB,
        h1_unusedMB2mu_wh0_phiB, h1_unusedMB2mu_wh1_phiB,
    ],
    title = "#phi_{B} of #mu^{reco, unused} [HQ DTTP]",
    xTitle = "#phi^{DTTP}_{B}", yTitle = "fraction",
    legendTextSize = 0.035,
    gridX = True,
    gridY = True,
    xMin = -1.5,
    xMax = 1.5,
    yMax = 0.2,
    outFileName = "plots/lowPt/unusedMu_phiB_HQ",
    outFileName_suffix = "MET",
)

####################################################################################################
h1_unusedMB1mu_wh0_phiB = HistogramDetails()
h1_unusedMB1mu_wh0_phiB.rootFileName = "output/MET_Run2017C-v1_RAW/DTNtuple_all_efficiency.root"
h1_unusedMB1mu_wh0_phiB.histName = "unusedMB1mu_wh0_phiB"
h1_unusedMB1mu_wh0_phiB.lineColor = lineColor["MB1"]
h1_unusedMB1mu_wh0_phiB.lineWidth = 2
h1_unusedMB1mu_wh0_phiB.lineStyle = 1
h1_unusedMB1mu_wh0_phiB.getHist()
#h1_unusedMB1mu_wh0_phiB.hist.Rebin(5)
h1_unusedMB1mu_wh0_phiB.histLabel = "#mu^{reco, unused}_{MB1, wh0} [#sigma = %0.2f]" %(h1_unusedMB1mu_wh0_phiB.hist.GetStdDev())
h1_unusedMB1mu_wh0_phiB.hist.Scale(1.0/h1_unusedMB1mu_wh0_phiB.hist.Integral())

h1_unusedMB1mu_wh1_phiB = HistogramDetails()
h1_unusedMB1mu_wh1_phiB.rootFileName = "output/MET_Run2017C-v1_RAW/DTNtuple_all_efficiency.root"
h1_unusedMB1mu_wh1_phiB.histName = "unusedMB1mu_wh1_phiB"
h1_unusedMB1mu_wh1_phiB.lineColor = lineColor["MB1"]
h1_unusedMB1mu_wh1_phiB.lineWidth = 2
h1_unusedMB1mu_wh1_phiB.lineStyle = 2
h1_unusedMB1mu_wh1_phiB.getHist()
#h1_unusedMB1mu_wh1_phiB.hist.Rebin(5)
h1_unusedMB1mu_wh1_phiB.histLabel = "#mu^{reco, unused}_{MB1, wh1} [#sigma = %0.2f]" %(h1_unusedMB1mu_wh1_phiB.hist.GetStdDev())
h1_unusedMB1mu_wh1_phiB.hist.Scale(1.0/h1_unusedMB1mu_wh1_phiB.hist.Integral())

h1_unusedMB2mu_wh0_phiB = HistogramDetails()
h1_unusedMB2mu_wh0_phiB.rootFileName = "output/MET_Run2017C-v1_RAW/DTNtuple_all_efficiency.root"
h1_unusedMB2mu_wh0_phiB.histName = "unusedMB2mu_wh0_phiB"
h1_unusedMB2mu_wh0_phiB.lineColor = lineColor["MB2"]
h1_unusedMB2mu_wh0_phiB.lineWidth = 2
h1_unusedMB2mu_wh0_phiB.lineStyle = 1
h1_unusedMB2mu_wh0_phiB.getHist()
#h1_unusedMB2mu_wh0_phiB.hist.Rebin(5)
h1_unusedMB2mu_wh0_phiB.histLabel = "#mu^{reco, unused}_{MB2, wh0} [#sigma = %0.2f]" %(h1_unusedMB2mu_wh0_phiB.hist.GetStdDev())
h1_unusedMB2mu_wh0_phiB.hist.Scale(1.0/h1_unusedMB2mu_wh0_phiB.hist.Integral())

h1_unusedMB2mu_wh1_phiB = HistogramDetails()
h1_unusedMB2mu_wh1_phiB.rootFileName = "output/MET_Run2017C-v1_RAW/DTNtuple_all_efficiency.root"
h1_unusedMB2mu_wh1_phiB.histName = "unusedMB2mu_wh1_phiB"
h1_unusedMB2mu_wh1_phiB.lineColor = lineColor["MB2"]
h1_unusedMB2mu_wh1_phiB.lineWidth = 2
h1_unusedMB2mu_wh1_phiB.lineStyle = 2
h1_unusedMB2mu_wh1_phiB.getHist()
#h1_unusedMB2mu_wh1_phiB.hist.Rebin(5)
h1_unusedMB2mu_wh1_phiB.histLabel = "#mu^{reco, unused}_{MB2, wh1} [#sigma = %0.2f]" %(h1_unusedMB2mu_wh1_phiB.hist.GetStdDev())
h1_unusedMB2mu_wh1_phiB.hist.Scale(1.0/h1_unusedMB2mu_wh1_phiB.hist.Integral())

plot1D(
    [h1_unusedMB1mu_wh0_phiB, h1_unusedMB1mu_wh1_phiB,
        h1_unusedMB2mu_wh0_phiB, h1_unusedMB2mu_wh1_phiB,
    ],
    title = "#phi_{B} of #mu^{reco, unused} [LQ+HQ DTTP]",
    xTitle = "#phi^{DTTP}_{B}", yTitle = "fraction",
    legendTextSize = 0.035,
    gridX = True,
    gridY = True,
    xMin = -1.5,
    xMax = 1.5,
    yMax = 0.2,
    outFileName = "plots/lowPt/unusedMu_phiB_LQHQ",
    outFileName_suffix = "MET",
)


####################################################################################################
h2_unusedMB12mu_wh0_MB2phiB_vs_MB1phiB = HistogramDetails()
h2_unusedMB12mu_wh0_MB2phiB_vs_MB1phiB.rootFileName = "output/MET_Run2017C-v1_RAW/DTNtuple_all_efficiency.root"
h2_unusedMB12mu_wh0_MB2phiB_vs_MB1phiB.histName = "unusedMB12mu_wh0_MB2phiB_vs_MB1phiB"
h2_unusedMB12mu_wh0_MB2phiB_vs_MB1phiB.outFileName = "plots/lowPt/unusedMB12mu_wh0_MB2phiB_vs_MB1phiB_LQHQ"
h2_unusedMB12mu_wh0_MB2phiB_vs_MB1phiB.outFileName_suffix = "MET"
h2_unusedMB12mu_wh0_MB2phiB_vs_MB1phiB.drawOption = "colz"
h2_unusedMB12mu_wh0_MB2phiB_vs_MB1phiB.xTitle = "#phi^{MB1TP}_{B}"
h2_unusedMB12mu_wh0_MB2phiB_vs_MB1phiB.yTitle = "#phi^{MB2TP}_{B}"
h2_unusedMB12mu_wh0_MB2phiB_vs_MB1phiB.gridX = True
h2_unusedMB12mu_wh0_MB2phiB_vs_MB1phiB.gridY = True
h2_unusedMB12mu_wh0_MB2phiB_vs_MB1phiB.getHist()
h2_unusedMB12mu_wh0_MB2phiB_vs_MB1phiB.histTitle = \
    "#splitline{#phi^{MB2TP}_{B} vs. #phi^{MB1TP}_{B} of #mu^{reco, unused}_{MB12} in Wheel 0 }{[#sigma_{x} = %0.2f, #sigma_{y} = %0.2f] [LQ+HQ DTTP]}" \
    %(h2_unusedMB12mu_wh0_MB2phiB_vs_MB1phiB.hist.GetStdDev(1), h2_unusedMB12mu_wh0_MB2phiB_vs_MB1phiB.hist.GetStdDev(2))
#h2_unusedMB12mu_wh0_MB2phiB_vs_MB1phiB.hist.RebinX(5)
#h2_unusedMB12mu_wh0_MB2phiB_vs_MB1phiB.hist.RebinY(5)
h2_unusedMB12mu_wh0_MB2phiB_vs_MB1phiB.hist.Scale(1.0 / h2_unusedMB12mu_wh0_MB2phiB_vs_MB1phiB.hist.Integral())
h2_unusedMB12mu_wh0_MB2phiB_vs_MB1phiB.xMin = -1.5
h2_unusedMB12mu_wh0_MB2phiB_vs_MB1phiB.xMax = 1.5
h2_unusedMB12mu_wh0_MB2phiB_vs_MB1phiB.yMin = -1.5
h2_unusedMB12mu_wh0_MB2phiB_vs_MB1phiB.yMax = 1.5
plot2D(h2_unusedMB12mu_wh0_MB2phiB_vs_MB1phiB)


####################################################################################################
h2_unusedMB12mu_wh1_MB2phiB_vs_MB1phiB = HistogramDetails()
h2_unusedMB12mu_wh1_MB2phiB_vs_MB1phiB.rootFileName = "output/MET_Run2017C-v1_RAW/DTNtuple_all_efficiency.root"
h2_unusedMB12mu_wh1_MB2phiB_vs_MB1phiB.histName = "unusedMB12mu_wh1_MB2phiB_vs_MB1phiB"
h2_unusedMB12mu_wh1_MB2phiB_vs_MB1phiB.outFileName = "plots/lowPt/unusedMB12mu_wh1_MB2phiB_vs_MB1phiB_LQHQ"
h2_unusedMB12mu_wh1_MB2phiB_vs_MB1phiB.outFileName_suffix = "MET"
h2_unusedMB12mu_wh1_MB2phiB_vs_MB1phiB.drawOption = "colz"
h2_unusedMB12mu_wh1_MB2phiB_vs_MB1phiB.xTitle = "#phi^{MB1TP}_{B}"
h2_unusedMB12mu_wh1_MB2phiB_vs_MB1phiB.yTitle = "#phi^{MB2TP}_{B}"
h2_unusedMB12mu_wh1_MB2phiB_vs_MB1phiB.gridX = True
h2_unusedMB12mu_wh1_MB2phiB_vs_MB1phiB.gridY = True
h2_unusedMB12mu_wh1_MB2phiB_vs_MB1phiB.getHist()
h2_unusedMB12mu_wh1_MB2phiB_vs_MB1phiB.histTitle = \
    "#splitline{#phi^{MB2TP}_{B} vs. #phi^{MB1TP}_{B} of #mu^{reco, unused}_{MB12} in Wheel 1}{[#sigma_{x} = %0.2f, #sigma_{y} = %0.2f] [LQ+HQ DTTP]}" \
    %(h2_unusedMB12mu_wh1_MB2phiB_vs_MB1phiB.hist.GetStdDev(1), h2_unusedMB12mu_wh1_MB2phiB_vs_MB1phiB.hist.GetStdDev(2))
#h2_unusedMB12mu_wh1_MB2phiB_vs_MB1phiB.hist.RebinX(5)
#h2_unusedMB12mu_wh1_MB2phiB_vs_MB1phiB.hist.RebinY(5)
h2_unusedMB12mu_wh1_MB2phiB_vs_MB1phiB.hist.Scale(1.0 / h2_unusedMB12mu_wh1_MB2phiB_vs_MB1phiB.hist.Integral())
h2_unusedMB12mu_wh1_MB2phiB_vs_MB1phiB.xMin = -1.5
h2_unusedMB12mu_wh1_MB2phiB_vs_MB1phiB.xMax = 1.5
h2_unusedMB12mu_wh1_MB2phiB_vs_MB1phiB.yMin = -1.5
h2_unusedMB12mu_wh1_MB2phiB_vs_MB1phiB.yMax = 1.5
plot2D(h2_unusedMB12mu_wh1_MB2phiB_vs_MB1phiB)


####################################################################################################
h2_usedMB12mu_wh0_MB2phiB_vs_MB1phiB = HistogramDetails()
h2_usedMB12mu_wh0_MB2phiB_vs_MB1phiB.rootFileName = "output/MET_Run2017C-v1_RAW/DTNtuple_all_efficiency.root"
h2_usedMB12mu_wh0_MB2phiB_vs_MB1phiB.histName = "usedMB12mu_wh0_MB2phiB_vs_MB1phiB"
h2_usedMB12mu_wh0_MB2phiB_vs_MB1phiB.outFileName = "plots/lowPt/usedMB12mu_wh0_MB2phiB_vs_MB1phiB_LQHQ"
h2_usedMB12mu_wh0_MB2phiB_vs_MB1phiB.outFileName_suffix = "MET"
h2_usedMB12mu_wh0_MB2phiB_vs_MB1phiB.drawOption = "colz"
h2_usedMB12mu_wh0_MB2phiB_vs_MB1phiB.xTitle = "#phi^{MB1TP}_{B}"
h2_usedMB12mu_wh0_MB2phiB_vs_MB1phiB.yTitle = "#phi^{MB2TP}_{B}"
h2_usedMB12mu_wh0_MB2phiB_vs_MB1phiB.gridX = True
h2_usedMB12mu_wh0_MB2phiB_vs_MB1phiB.gridY = True
h2_usedMB12mu_wh0_MB2phiB_vs_MB1phiB.getHist()
h2_usedMB12mu_wh0_MB2phiB_vs_MB1phiB.histTitle = \
    "#splitline{#phi^{MB2TP}_{B} vs. #phi^{MB1TP}_{B} of #mu^{reco, used}_{MB12} in Wheel 0}{[#sigma_{x} = %0.2f, #sigma_{y} = %0.2f] [LQ+HQ DTTP]}" \
    %(h2_usedMB12mu_wh0_MB2phiB_vs_MB1phiB.hist.GetStdDev(1), h2_usedMB12mu_wh0_MB2phiB_vs_MB1phiB.hist.GetStdDev(2))
#h2_usedMB12mu_wh0_MB2phiB_vs_MB1phiB.hist.RebinX(5)
#h2_usedMB12mu_wh0_MB2phiB_vs_MB1phiB.hist.RebinY(5)
h2_usedMB12mu_wh0_MB2phiB_vs_MB1phiB.hist.Scale(1.0 / h2_usedMB12mu_wh0_MB2phiB_vs_MB1phiB.hist.Integral())
h2_usedMB12mu_wh0_MB2phiB_vs_MB1phiB.xMin = -1.5
h2_usedMB12mu_wh0_MB2phiB_vs_MB1phiB.xMax = 1.5
h2_usedMB12mu_wh0_MB2phiB_vs_MB1phiB.yMin = -1.5
h2_usedMB12mu_wh0_MB2phiB_vs_MB1phiB.yMax = 1.5
plot2D(h2_usedMB12mu_wh0_MB2phiB_vs_MB1phiB)


####################################################################################################
h2_usedMB12mu_wh1_MB2phiB_vs_MB1phiB = HistogramDetails()
h2_usedMB12mu_wh1_MB2phiB_vs_MB1phiB.rootFileName = "output/MET_Run2017C-v1_RAW/DTNtuple_all_efficiency.root"
h2_usedMB12mu_wh1_MB2phiB_vs_MB1phiB.histName = "usedMB12mu_wh1_MB2phiB_vs_MB1phiB"
h2_usedMB12mu_wh1_MB2phiB_vs_MB1phiB.outFileName = "plots/lowPt/usedMB12mu_wh1_MB2phiB_vs_MB1phiB_LQHQ"
h2_usedMB12mu_wh1_MB2phiB_vs_MB1phiB.outFileName_suffix = "MET"
h2_usedMB12mu_wh1_MB2phiB_vs_MB1phiB.drawOption = "colz"
h2_usedMB12mu_wh1_MB2phiB_vs_MB1phiB.xTitle = "#phi^{MB1TP}_{B}"
h2_usedMB12mu_wh1_MB2phiB_vs_MB1phiB.yTitle = "#phi^{MB2TP}_{B}"
h2_usedMB12mu_wh1_MB2phiB_vs_MB1phiB.gridX = True
h2_usedMB12mu_wh1_MB2phiB_vs_MB1phiB.gridY = True
h2_usedMB12mu_wh1_MB2phiB_vs_MB1phiB.getHist()
h2_usedMB12mu_wh1_MB2phiB_vs_MB1phiB.histTitle = \
    "#splitline{#phi^{MB2TP}_{B} vs. #phi^{MB1TP}_{B} of #mu^{reco, used}_{MB12} in Wheel 1}{[#sigma_{x} = %0.2f, #sigma_{y} = %0.2f] [LQ+HQ DTTP]}" \
    %(h2_usedMB12mu_wh1_MB2phiB_vs_MB1phiB.hist.GetStdDev(1), h2_usedMB12mu_wh1_MB2phiB_vs_MB1phiB.hist.GetStdDev(2))
#h2_usedMB12mu_wh1_MB2phiB_vs_MB1phiB.hist.RebinX(5)
#h2_usedMB12mu_wh1_MB2phiB_vs_MB1phiB.hist.RebinY(5)
h2_usedMB12mu_wh1_MB2phiB_vs_MB1phiB.hist.Scale(1.0 / h2_usedMB12mu_wh1_MB2phiB_vs_MB1phiB.hist.Integral())
h2_usedMB12mu_wh1_MB2phiB_vs_MB1phiB.xMin = -1.5
h2_usedMB12mu_wh1_MB2phiB_vs_MB1phiB.xMax = 1.5
h2_usedMB12mu_wh1_MB2phiB_vs_MB1phiB.yMin = -1.5
h2_usedMB12mu_wh1_MB2phiB_vs_MB1phiB.yMax = 1.5
plot2D(h2_usedMB12mu_wh1_MB2phiB_vs_MB1phiB)


####################################################################################################
h2_usedMB12mu_wh0_pT_vs_MB1phiB = HistogramDetails()
h2_usedMB12mu_wh0_pT_vs_MB1phiB.rootFileName = "output/MET_Run2017C-v1_RAW_isoMB12/DTNtuple_all_efficiency.root"
h2_usedMB12mu_wh0_pT_vs_MB1phiB.histName = "usedMB12mu_wh0_pT_vs_MB1phiB"
h2_usedMB12mu_wh0_pT_vs_MB1phiB.outFileName = "plots/lowPt/usedMB12mu_wh0_pT_vs_MB1phiB_LQHQ"
h2_usedMB12mu_wh0_pT_vs_MB1phiB.outFileName_suffix = "MET"
h2_usedMB12mu_wh0_pT_vs_MB1phiB.drawOption = "colz"
h2_usedMB12mu_wh0_pT_vs_MB1phiB.xTitle = "#phi^{MB1TP}_{B}"
h2_usedMB12mu_wh0_pT_vs_MB1phiB.yTitle = "p_{T} [GeV]"
h2_usedMB12mu_wh0_pT_vs_MB1phiB.gridX = True
h2_usedMB12mu_wh0_pT_vs_MB1phiB.gridY = True
h2_usedMB12mu_wh0_pT_vs_MB1phiB.getHist()
h2_usedMB12mu_wh0_pT_vs_MB1phiB.histTitle = "#splitline{p_{T} of MB12 reco-#mu (in wheel 0) vs.}{#phi_{B} of the MB1TP (LQ+HQ) matched to it}"
h2_usedMB12mu_wh0_pT_vs_MB1phiB.hist.Scale(1.0 / h2_usedMB12mu_wh0_pT_vs_MB1phiB.hist.Integral())
h2_usedMB12mu_wh0_pT_vs_MB1phiB.xMin = -1.5
h2_usedMB12mu_wh0_pT_vs_MB1phiB.xMax = 1.5
h2_usedMB12mu_wh0_pT_vs_MB1phiB.yMin = 0
h2_usedMB12mu_wh0_pT_vs_MB1phiB.yMax = 20
plot2D(h2_usedMB12mu_wh0_pT_vs_MB1phiB)


####################################################################################################
h2_usedMB12mu_wh1_pT_vs_MB1phiB = HistogramDetails()
h2_usedMB12mu_wh1_pT_vs_MB1phiB.rootFileName = "output/MET_Run2017C-v1_RAW_isoMB12/DTNtuple_all_efficiency.root"
h2_usedMB12mu_wh1_pT_vs_MB1phiB.histName = "usedMB12mu_wh1_pT_vs_MB1phiB"
h2_usedMB12mu_wh1_pT_vs_MB1phiB.outFileName = "plots/lowPt/usedMB12mu_wh1_pT_vs_MB1phiB_LQHQ"
h2_usedMB12mu_wh1_pT_vs_MB1phiB.outFileName_suffix = "MET"
h2_usedMB12mu_wh1_pT_vs_MB1phiB.drawOption = "colz"
h2_usedMB12mu_wh1_pT_vs_MB1phiB.xTitle = "#phi^{MB1TP}_{B}"
h2_usedMB12mu_wh1_pT_vs_MB1phiB.yTitle = "p_{T} [GeV]"
h2_usedMB12mu_wh1_pT_vs_MB1phiB.gridX = True
h2_usedMB12mu_wh1_pT_vs_MB1phiB.gridY = True
h2_usedMB12mu_wh1_pT_vs_MB1phiB.getHist()
h2_usedMB12mu_wh1_pT_vs_MB1phiB.histTitle = "#splitline{p_{T} of MB12 reco-#mu (in wheels #pm1) vs.}{#phi_{B} of the MB1TP (LQ+HQ) matched to it}"
h2_usedMB12mu_wh1_pT_vs_MB1phiB.hist.Scale(1.0 / h2_usedMB12mu_wh1_pT_vs_MB1phiB.hist.Integral())
h2_usedMB12mu_wh1_pT_vs_MB1phiB.xMin = -1.5
h2_usedMB12mu_wh1_pT_vs_MB1phiB.xMax = 1.5
h2_usedMB12mu_wh1_pT_vs_MB1phiB.yMin = 0
h2_usedMB12mu_wh1_pT_vs_MB1phiB.yMax = 20
plot2D(h2_usedMB12mu_wh1_pT_vs_MB1phiB)


####################################################################################################
h1_BMTF_muMatched_trackType = HistogramDetails()
h1_BMTF_muMatched_trackType.rootFileName = "output/SingleMuon_Run2017C-ZMu-PromptReco-v3_RAW-RECO_tightMu25_BMTF22/DTNtuple_all_efficiency.root"
h1_BMTF_muMatched_trackType.histName = "BMTF_muMatched_trackType"
h1_BMTF_muMatched_trackType.drawOption = "hist text"
h1_BMTF_muMatched_trackType.lineWidth = 2
h1_BMTF_muMatched_trackType.getHist()
h1_BMTF_muMatched_trackType.hist.Scale(1.0/h1_BMTF_muMatched_trackType.hist.GetBinContent(1))
plot1D(
    [h1_BMTF_muMatched_trackType],
    title = "BMTF^{#mu-matched} track type",
    xTitle = "", yTitle = "fraction",
    xMax = 25,
    gridY = True,
    drawLegend = False,
    fixAlphanumericBinLabels = True,
    outFileName = "plots/MB34trackPt/BMTF_muMatched_trackType",
    outFileName_suffix = "SingleMuon",
)


####################################################################################################
h1_test2_LQHQ = HistogramDetails()
h1_test2_LQHQ.rootFileName = "output/SingleMuon_Run2017C-ZMu-PromptReco-v3_RAW-RECO_tightMu25_BMTF22/DTNtuple_all_efficiency.root"
h1_test2_LQHQ.histName = "test2"
h1_test2_LQHQ.histLabel = "LQ+HQ DTTP"
h1_test2_LQHQ.drawOption = "hist"
h1_test2_LQHQ.lineWidth = 2
h1_test2_LQHQ.lineColor = 2
h1_test2_LQHQ.getHist()

h1_test2_HQ = HistogramDetails()
h1_test2_HQ.rootFileName = "output/SingleMuon_Run2017C-ZMu-PromptReco-v3_RAW-RECO_tightMu25_BMTF22/DTNtuple_all_efficiency.root"
h1_test2_HQ.histName = "HQ/test2"
h1_test2_HQ.histLabel = "HQ DTTP"
h1_test2_HQ.drawOption = "hist"
h1_test2_HQ.lineWidth = 2
h1_test2_HQ.lineColor = 4
h1_test2_HQ.getHist()


plot1D(
    [h1_test2_LQHQ, h1_test2_HQ],
    title = "stations hit by #mu^{reco} in i#eta 1-4",
    xTitle = "", yTitle = "count",
    xMax = 80,
    gridY = True,
    drawLegend = True,
    fixAlphanumericBinLabels = True,
    outFileName = "plots/MBgap/test2",
    outFileName_suffix = "SingleMuon",
)


####################################################################################################
h1_test3_LQHQ = HistogramDetails()
h1_test3_LQHQ.rootFileName = "output/SingleMuon_Run2017C-ZMu-PromptReco-v3_RAW-RECO_tightMu25_BMTF22/DTNtuple_all_efficiency.root"
h1_test3_LQHQ.histName = "test3"
h1_test3_LQHQ.histLabel = "LQ+HQ DTTP"
h1_test3_LQHQ.drawOption = "hist"
h1_test3_LQHQ.lineWidth = 2
h1_test3_LQHQ.lineColor = 2
h1_test3_LQHQ.getHist()

h1_test3_HQ = HistogramDetails()
h1_test3_HQ.rootFileName = "output/SingleMuon_Run2017C-ZMu-PromptReco-v3_RAW-RECO_tightMu25_BMTF22/DTNtuple_all_efficiency.root"
h1_test3_HQ.histName = "HQ/test3"
h1_test3_HQ.histLabel = "HQ DTTP"
h1_test3_HQ.drawOption = "hist"
h1_test3_HQ.lineWidth = 2
h1_test3_HQ.lineColor = 4
h1_test3_HQ.getHist()


plot1D(
    [h1_test3_LQHQ, h1_test3_HQ],
    title = "i#eta distribution of #mu^{reco} missing MB 1-4",
    xTitle = "", yTitle = "count",
    xMax = 60,
    gridY = True,
    drawLegend = True,
    fixAlphanumericBinLabels = True,
    outFileName = "plots/MBgap/test3",
    outFileName_suffix = "SingleMuon",
)


####################################################################################################
h1_BMTF_trackType = HistogramDetails()
h1_BMTF_trackType.rootFileName = "output/ZeroBias1_BMTF22_iEta3/DTNtuple_all_efficiency.root"
h1_BMTF_trackType.histName = "BMTF_trackType"
h1_BMTF_trackType.drawOption = "hist text"
h1_BMTF_trackType.lineWidth = 2
h1_BMTF_trackType.getHist()
h1_BMTF_trackType.hist.Scale(1.0/h1_BMTF_trackType.hist.GetBinContent(1))
plot1D(
    [h1_BMTF_trackType],
    title = "BMTF track type",
    xTitle = "", yTitle = "fraction",
    xMax = 25,
    gridY = True,
    drawLegend = False,
    fixAlphanumericBinLabels = True,
    outFileName = "plots/MB34trackPt/BMTF_trackType",
    outFileName_suffix = "ZeroBias",
)


####################################################################################################
h1_pT_BMTF = HistogramDetails()
h1_pT_BMTF.rootFileName = "output/SingleMuon_Run2017C-ZMu-PromptReco-v3_RAW-RECO_tightMu0_BMTF0/DTNtuple_all_efficiency.root"
h1_pT_BMTF.histName = "BMTF_muMatched_pT_vs_trackType"
h1_pT_BMTF.histLabel = "BMTF"
h1_pT_BMTF.lineWidth = 2
h1_pT_BMTF.lineColor = lineColor["BMTF"]
h1_pT_BMTF.getHist("Y", 1, 1)
#h1_pT_BMTF.hist = h1_pT_BMTF.hist.GetCumulative(False)

h1_pT_BMTFMB12 = HistogramDetails()
h1_pT_BMTFMB12.rootFileName = "output/SingleMuon_Run2017C-ZMu-PromptReco-v3_RAW-RECO_tightMu0_BMTF0/DTNtuple_all_efficiency.root"
h1_pT_BMTFMB12.histName = "BMTF_muMatched_pT_vs_trackType"
h1_pT_BMTFMB12.histLabel = "BMTF MB12"
h1_pT_BMTFMB12.lineWidth = 2
h1_pT_BMTFMB12.lineColor = lineColor["MB12"]
h1_pT_BMTFMB12.getHist("Y", 4, 4)
#h1_pT_BMTFMB12.hist = h1_pT_BMTFMB12.hist.GetCumulative(False)

h1_pT_BMTFMB34 = HistogramDetails()
h1_pT_BMTFMB34.rootFileName = "output/SingleMuon_Run2017C-ZMu-PromptReco-v3_RAW-RECO_tightMu0_BMTF0/DTNtuple_all_efficiency.root"
h1_pT_BMTFMB34.histName = "BMTF_muMatched_pT_vs_trackType"
h1_pT_BMTFMB34.histLabel = "MB34 BMTF"
h1_pT_BMTFMB34.lineWidth = 2
h1_pT_BMTFMB34.lineColor = lineColor["MB34"]
h1_pT_BMTFMB34.getHist("Y", 13, 13)
#h1_pT_BMTFMB34.hist = h1_pT_BMTFMB34.hist.GetCumulative(False)

h1_pT_BMTFMB1234 = HistogramDetails()
h1_pT_BMTFMB1234.rootFileName = "output/SingleMuon_Run2017C-ZMu-PromptReco-v3_RAW-RECO_tightMu0_BMTF0/DTNtuple_all_efficiency.root"
h1_pT_BMTFMB1234.histName = "BMTF_muMatched_pT_vs_trackType"
h1_pT_BMTFMB1234.histLabel = "BMTF MB1234"
h1_pT_BMTFMB1234.lineWidth = 2
h1_pT_BMTFMB1234.lineColor = lineColor["MB1234"]
h1_pT_BMTFMB1234.getHist("Y", 16, 16)
#h1_pT_BMTFMB1234.hist = h1_pT_BMTFMB1234.hist.GetCumulative(False)

plot1D(
    [h1_pT_BMTF,
        h1_pT_BMTFMB12,
        h1_pT_BMTFMB34,
        h1_pT_BMTFMB1234,
    ],
    title = "BMTF^{#mu-matched} p_{T}",
    xTitle = "p_{T} [GeV]", yTitle = "",
    gridX = True,
    gridY = True,
    xMin = 25,
    xMax = 100,
    logY = True,
    outFileName = "plots/MB34trackPt/BMTF_muMatched_pT",
    outFileName_suffix = "SingleMuon",
)


####################################################################################################
h1_pT_BMTF = HistogramDetails()
h1_pT_BMTF.rootFileName = "output/ZeroBias1_BMTF0_iEta3//DTNtuple_all_efficiency.root"
h1_pT_BMTF.histName = "BMTF_pT_vs_trackType"
h1_pT_BMTF.histLabel = "BMTF"
h1_pT_BMTF.lineWidth = 2
h1_pT_BMTF.lineColor = lineColor["BMTF"]
h1_pT_BMTF.getHist("Y", 1, 1)
h1_pT_BMTF.hist = h1_pT_BMTF.hist.GetCumulative(False)
#h1_pT_BMTF.hist.Scale(1.0 / h1_pT_BMTF.hist.Integral())

h1_pT_BMTFMB12 = HistogramDetails()
h1_pT_BMTFMB12.rootFileName = "output/ZeroBias1_BMTF0_iEta3//DTNtuple_all_efficiency.root"
h1_pT_BMTFMB12.histName = "BMTF_pT_vs_trackType"
h1_pT_BMTFMB12.histLabel = "BMTF MB12"
h1_pT_BMTFMB12.lineWidth = 2
h1_pT_BMTFMB12.lineColor = lineColor["MB12"]
h1_pT_BMTFMB12.getHist("Y", 4, 4)
h1_pT_BMTFMB12.hist = h1_pT_BMTFMB12.hist.GetCumulative(False)
#h1_pT_BMTFMB12.hist.Scale(1.0 / h1_pT_BMTFMB12.hist.Integral())

h1_pT_BMTFMB34 = HistogramDetails()
h1_pT_BMTFMB34.rootFileName = "output/ZeroBias1_BMTF0_iEta3//DTNtuple_all_efficiency.root"
h1_pT_BMTFMB34.histName = "BMTF_pT_vs_trackType"
h1_pT_BMTFMB34.histLabel = "MB34 BMTF"
h1_pT_BMTFMB34.lineWidth = 2
h1_pT_BMTFMB34.lineColor = lineColor["MB34"]
h1_pT_BMTFMB34.getHist("Y", 13, 13)
h1_pT_BMTFMB34.hist = h1_pT_BMTFMB34.hist.GetCumulative(False)
#h1_pT_BMTFMB34.hist.Scale(1.0 / h1_pT_BMTFMB34.hist.Integral())

h1_pT_BMTFMB1234 = HistogramDetails()
h1_pT_BMTFMB1234.rootFileName = "output/ZeroBias1_BMTF0_iEta3//DTNtuple_all_efficiency.root"
h1_pT_BMTFMB1234.histName = "BMTF_pT_vs_trackType"
h1_pT_BMTFMB1234.histLabel = "BMTF MB1234"
h1_pT_BMTFMB1234.lineWidth = 2
h1_pT_BMTFMB1234.lineColor = lineColor["MB1234"]
h1_pT_BMTFMB1234.getHist("Y", 16, 16)
h1_pT_BMTFMB1234.hist = h1_pT_BMTFMB1234.hist.GetCumulative(False)
#h1_pT_BMTFMB1234.hist.Scale(1.0 / h1_pT_BMTFMB1234.hist.Integral())

plot1D(
    [h1_pT_BMTF,
        h1_pT_BMTFMB12,
        h1_pT_BMTFMB34,
        h1_pT_BMTFMB1234,
    ],
    title = "BMTF^{#mu-matched} p_{T}",
    xTitle = "p_{T} [GeV]", yTitle = "",
    gridX = True,
    gridY = True,
    #xMin = 25,
    xMax = 100,
    logY = True,
    outFileName = "plots/MB34trackPt/BMTF_pT_cumulative",
    outFileName_suffix = "ZeroBias",
)


####################################################################################################
h1_pT_resolution_BMTF = HistogramDetails()
h1_pT_resolution_BMTF.rootFileName = "output/SingleMuon_Run2017C-ZMu-PromptReco-v3_RAW-RECO_tightMu25_BMTF22/DTNtuple_all_efficiency.root"
h1_pT_resolution_BMTF.histName = "BMTF_pT_resolution_vs_trackType"
h1_pT_resolution_BMTF.histLabel = "BMTF"
h1_pT_resolution_BMTF.lineWidth = 2
h1_pT_resolution_BMTF.lineColor = lineColor["BMTF"]
h1_pT_resolution_BMTF.getHist("Y", 1, 1)
nBin = h1_pT_resolution_BMTF.hist.GetNbinsX()
h1_pT_resolution_BMTF.hist.AddBinContent(nBin, h1_pT_resolution_BMTF.hist.GetBinContent(nBin+1))
h1_pT_resolution_BMTF.hist.Scale(1.0 / h1_pT_resolution_BMTF.hist.GetEntries())

h1_pT_resolution_BMTFMB12 = HistogramDetails()
h1_pT_resolution_BMTFMB12.rootFileName = "output/SingleMuon_Run2017C-ZMu-PromptReco-v3_RAW-RECO_tightMu25_BMTF22/DTNtuple_all_efficiency.root"
h1_pT_resolution_BMTFMB12.histName = "BMTF_pT_resolution_vs_trackType"
h1_pT_resolution_BMTFMB12.histLabel = "BMTF MB12"
h1_pT_resolution_BMTFMB12.lineWidth = 2
h1_pT_resolution_BMTFMB12.lineColor = lineColor["MB12"]
h1_pT_resolution_BMTFMB12.getHist("Y", 4, 4)
nBin = h1_pT_resolution_BMTFMB12.hist.GetNbinsX()
h1_pT_resolution_BMTFMB12.hist.AddBinContent(nBin, h1_pT_resolution_BMTFMB12.hist.GetBinContent(nBin+1))
h1_pT_resolution_BMTFMB12.hist.Scale(1.0 / h1_pT_resolution_BMTFMB12.hist.GetEntries())

h1_pT_resolution_BMTFMB34 = HistogramDetails()
h1_pT_resolution_BMTFMB34.rootFileName = "output/SingleMuon_Run2017C-ZMu-PromptReco-v3_RAW-RECO_tightMu25_BMTF22/DTNtuple_all_efficiency.root"
h1_pT_resolution_BMTFMB34.histName = "BMTF_pT_resolution_vs_trackType"
h1_pT_resolution_BMTFMB34.histLabel = "MB34 BMTF"
h1_pT_resolution_BMTFMB34.lineWidth = 2
h1_pT_resolution_BMTFMB34.lineColor = lineColor["MB34"]
h1_pT_resolution_BMTFMB34.getHist("Y", 13, 13)
nBin = h1_pT_resolution_BMTFMB34.hist.GetNbinsX()
h1_pT_resolution_BMTFMB34.hist.AddBinContent(nBin, h1_pT_resolution_BMTFMB34.hist.GetBinContent(nBin+1))
h1_pT_resolution_BMTFMB34.hist.Scale(1.0 / h1_pT_resolution_BMTFMB34.hist.GetEntries())

h1_pT_resolution_BMTFMB1234 = HistogramDetails()
h1_pT_resolution_BMTFMB1234.rootFileName = "output/SingleMuon_Run2017C-ZMu-PromptReco-v3_RAW-RECO_tightMu25_BMTF22/DTNtuple_all_efficiency.root"
h1_pT_resolution_BMTFMB1234.histName = "BMTF_pT_resolution_vs_trackType"
h1_pT_resolution_BMTFMB1234.histLabel = "BMTF MB1234"
h1_pT_resolution_BMTFMB1234.lineWidth = 2
h1_pT_resolution_BMTFMB1234.lineColor = lineColor["MB1234"]
h1_pT_resolution_BMTFMB1234.getHist("Y", 16, 16)
nBin = h1_pT_resolution_BMTFMB1234.hist.GetNbinsX()
h1_pT_resolution_BMTFMB1234.hist.AddBinContent(nBin, h1_pT_resolution_BMTFMB1234.hist.GetBinContent(nBin+1))
h1_pT_resolution_BMTFMB1234.hist.Scale(1.0 / h1_pT_resolution_BMTFMB1234.hist.GetEntries())

plot1D(
    [h1_pT_resolution_BMTF,
        h1_pT_resolution_BMTFMB12,
        h1_pT_resolution_BMTFMB34,
        h1_pT_resolution_BMTFMB1234,
    ],
    title = "BMTF p_{T} resolution",
    xTitle = "p^{BMTF}_{T} / p^{#mu}_{T}", yTitle = "",
    gridX = True,
    gridY = True,
    yMax = 0.25,
    outFileName = "plots/MB34trackPt/BMTF_pT_resolution",
    outFileName_suffix = "SingleMuon",
)


####################################################################################################
h2_MB34onlyBMTF_matchedMu_pT_vs_nearestMB3nearestHO_deltaIphi = HistogramDetails()
h2_MB34onlyBMTF_matchedMu_pT_vs_nearestMB3nearestHO_deltaIphi.rootFileName = "output/MET_Run2017C-v1_RAW/DTNtuple_all_efficiency.root"
h2_MB34onlyBMTF_matchedMu_pT_vs_nearestMB3nearestHO_deltaIphi.histName = "MB34onlyBMTF_matchedMu_pT_vs_nearestMB3nearestHO_deltaIphi"
h2_MB34onlyBMTF_matchedMu_pT_vs_nearestMB3nearestHO_deltaIphi.histTitle = "p^{MB34 BMTF}_{T} vs. #Deltai#phi_{HO-MB3}"
h2_MB34onlyBMTF_matchedMu_pT_vs_nearestMB3nearestHO_deltaIphi.outFileName = "plots/MB34trackPt/MB34onlyBMTF_matchedMu_pT_vs_nearestMB3nearestHO_deltaIphi"
h2_MB34onlyBMTF_matchedMu_pT_vs_nearestMB3nearestHO_deltaIphi.outFileName_suffix = "SingleMuon"
h2_MB34onlyBMTF_matchedMu_pT_vs_nearestMB3nearestHO_deltaIphi.drawOption = "colz"
h2_MB34onlyBMTF_matchedMu_pT_vs_nearestMB3nearestHO_deltaIphi.yMax = 100
h2_MB34onlyBMTF_matchedMu_pT_vs_nearestMB3nearestHO_deltaIphi.xTitle = "#Deltai#phi_{HO-MB3}"
h2_MB34onlyBMTF_matchedMu_pT_vs_nearestMB3nearestHO_deltaIphi.yTitle = "p_{T} [GeV]"
h2_MB34onlyBMTF_matchedMu_pT_vs_nearestMB3nearestHO_deltaIphi.gridX = True
h2_MB34onlyBMTF_matchedMu_pT_vs_nearestMB3nearestHO_deltaIphi.gridY = True
h2_MB34onlyBMTF_matchedMu_pT_vs_nearestMB3nearestHO_deltaIphi.getHist()
plot2D(h2_MB34onlyBMTF_matchedMu_pT_vs_nearestMB3nearestHO_deltaIphi)


####################################################################################################
h1_ratio = HistogramDetails()
h1_ratio.rootFileName = "output/SingleMuon_Run2017C-ZMu-PromptReco-v3_RAW-RECO_tightMu0_BMTF0/DTNtuple_all_efficiency.root"
h1_ratio.histName = "MB34onlyBMTF_matchedMu_pT_vs_nearestMB3nearestHO_deltaIphi"
h1_ratio.lineWidth = 2
h1_ratio.getHist("Y", startBin = 0, endBin = 0, findStartBin = True, findEndBin = True)
h1_ratio.hist.Rebin(5)

h1_MB34onlyBMTF_pT = HistogramDetails()
h1_MB34onlyBMTF_pT.rootFileName = "output/SingleMuon_Run2017C-ZMu-PromptReco-v3_RAW-RECO_tightMu0_BMTF0/DTNtuple_all_efficiency.root"
h1_MB34onlyBMTF_pT.histName = "MB34onlyBMTF_pT"
h1_MB34onlyBMTF_pT.getHist()
h1_MB34onlyBMTF_pT.hist.Rebin(5)

h1_ratio.hist.Divide(h1_MB34onlyBMTF_pT.hist)

plot1D(
    [h1_ratio],
    title = "p^{#Deltai#phi_{HO-MB3} = 0}_{T, MB34 BMTF} / p_{T, MB34 BMTF}",
    xTitle = "p_{T} [GeV]", yTitle = "fraction",
    gridX = True,
    gridY = True,
    xMax = 100,
    yMax = 1,
    drawLegend = False,
    outFileName = "plots/MB34trackPt/MB34HOratio1",
    outFileName_suffix = "SingleMuon",
)


####################################################################################################
h1_ratio = HistogramDetails()
h1_ratio.rootFileName = "output/SingleMuon_Run2017C-ZMu-PromptReco-v3_RAW-RECO_tightMu0_BMTF0/DTNtuple_all_efficiency.root"
h1_ratio.histName = "MB34onlyBMTF_matchedMu_pT_vs_nearestMB3nearestHO_deltaIphi"
h1_ratio.lineWidth = 2
h1_ratio.getHist("Y", startBin = 0, endBin = 0, findStartBin = True, findEndBin = True)
h1_ratio.hist.Rebin(5)

h1_MB34onlyBMTF_pT = HistogramDetails()
h1_MB34onlyBMTF_pT.rootFileName = "output/SingleMuon_Run2017C-ZMu-PromptReco-v3_RAW-RECO_tightMu0_BMTF0/DTNtuple_all_efficiency.root"
h1_MB34onlyBMTF_pT.histName = "MB34onlyBMTF_matchedMu_pT_vs_nearestMB3nearestHO_deltaIphi"
h1_MB34onlyBMTF_pT.getHist("Y")
h1_MB34onlyBMTF_pT.hist.Rebin(5)

h1_ratio.hist.Divide(h1_MB34onlyBMTF_pT.hist)

plot1D(
    [h1_ratio],
    title = "p^{#Deltai#phi_{HO-MB3} = 0}_{T, MB34 BMTF} / p^{#Deltai#phi_{HO-MB3} #leq 10}_{T, MB34 BMTF}",
    xTitle = "p_{T} [GeV]", yTitle = "fraction",
    gridX = True,
    gridY = True,
    xMax = 100,
    yMax = 1,
    drawLegend = False,
    outFileName = "plots/MB34trackPt/MB34HOratio2",
    outFileName_suffix = "SingleMuon",
)


####################################################################################################
h1_mu_pT = HistogramDetails()
h1_mu_pT.rootFileName = "output/SingleMuon_Run2017C-ZMu-PromptReco-v3_RAW-RECO_tightMu0_BMTF22/DTNtuple_all_efficiency.root"
h1_mu_pT.histName = "mu_pT"
h1_mu_pT.getHist()
h1_mu_pT.hist.Rebin(5)

h1_BMTF_muMatched_pT = HistogramDetails()
h1_BMTF_muMatched_pT.rootFileName = "output/SingleMuon_Run2017C-ZMu-PromptReco-v3_RAW-RECO_tightMu0_BMTF22/DTNtuple_all_efficiency.root"
h1_BMTF_muMatched_pT.histName = "BMTF_muMatched_pT"
h1_BMTF_muMatched_pT.histLabel = "BMTF"
h1_BMTF_muMatched_pT.drawOption = "hist E"
h1_BMTF_muMatched_pT.lineWidth = 2
h1_BMTF_muMatched_pT.lineColor = lineColor["BMTF"]
h1_BMTF_muMatched_pT.getHist()
h1_BMTF_muMatched_pT.hist.Rebin(5)
h1_BMTF_muMatched_pT.hist.Divide(h1_mu_pT.hist)

h1_BMTF_muMatched_MB34onlyMB3HO_pT = HistogramDetails()
h1_BMTF_muMatched_MB34onlyMB3HO_pT.rootFileName = "output/SingleMuon_Run2017C-ZMu-PromptReco-v3_RAW-RECO_tightMu0_BMTF22/DTNtuple_all_efficiency.root"
h1_BMTF_muMatched_MB34onlyMB3HO_pT.histName = "BMTF_muMatched_MB34onlyMB3HO_pT"
h1_BMTF_muMatched_MB34onlyMB3HO_pT.histLabel = "MB34 BMTF+HO"
h1_BMTF_muMatched_MB34onlyMB3HO_pT.drawOption = "hist E"
h1_BMTF_muMatched_MB34onlyMB3HO_pT.lineWidth = 2
h1_BMTF_muMatched_MB34onlyMB3HO_pT.lineColor = lineColor["MB34_MB3HO"]
h1_BMTF_muMatched_MB34onlyMB3HO_pT.getHist()
h1_BMTF_muMatched_MB34onlyMB3HO_pT.hist.Rebin(5)
h1_BMTF_muMatched_MB34onlyMB3HO_pT.hist.Divide(h1_mu_pT.hist)

plot1D(
    [h1_BMTF_muMatched_pT, h1_BMTF_muMatched_MB34onlyMB3HO_pT],
    title = "BMTF efficiency",
    xTitle = "p^{reco-#mu}_{T}", yTitle = "efficiency",
    gridX = True,
    gridY = True,
    xMin = 0, xMax = 100,
    yMax = 1.1,
    legendPos = "LR",
    outFileName = "plots/MB34trackPt/MB34_efficiency_pT",
    outFileName_suffix = "SingleMuon",
)


####################################################################################################
h1_mu_eta = HistogramDetails()
h1_mu_eta.rootFileName = "output/SingleMuon_Run2017C-ZMu-PromptReco-v3_RAW-RECO_tightMu25_BMTF22/DTNtuple_all_efficiency.root"
h1_mu_eta.histName = "mu_eta"
h1_mu_eta.getHist()

h1_BMTF_muMatched_eta = HistogramDetails()
h1_BMTF_muMatched_eta.rootFileName = "output/SingleMuon_Run2017C-ZMu-PromptReco-v3_RAW-RECO_tightMu25_BMTF22/DTNtuple_all_efficiency.root"
h1_BMTF_muMatched_eta.histName = "BMTF_muMatched_eta"
h1_BMTF_muMatched_eta.histLabel = "BMTF"
h1_BMTF_muMatched_eta.drawOption = "E"
h1_BMTF_muMatched_eta.lineWidth = 2
h1_BMTF_muMatched_eta.lineColor = lineColor["BMTF"]
h1_BMTF_muMatched_eta.getHist()
h1_BMTF_muMatched_eta.hist.Divide(h1_mu_eta.hist)

h1_BMTF_muMatched_MB34onlyMB3HO_eta = HistogramDetails()
h1_BMTF_muMatched_MB34onlyMB3HO_eta.rootFileName = "output/SingleMuon_Run2017C-ZMu-PromptReco-v3_RAW-RECO_tightMu25_BMTF22/DTNtuple_all_efficiency.root"
h1_BMTF_muMatched_MB34onlyMB3HO_eta.histName = "BMTF_muMatched_MB34onlyMB3HO_eta"
h1_BMTF_muMatched_MB34onlyMB3HO_eta.histLabel = "MB34 BMTF+HO"
h1_BMTF_muMatched_MB34onlyMB3HO_eta.drawOption = "E"
h1_BMTF_muMatched_MB34onlyMB3HO_eta.lineWidth = 2
h1_BMTF_muMatched_MB34onlyMB3HO_eta.lineColor = lineColor["MB34_MB3HO"]
h1_BMTF_muMatched_MB34onlyMB3HO_eta.getHist()
h1_BMTF_muMatched_MB34onlyMB3HO_eta.hist.Divide(h1_mu_eta.hist)

plot1D(
    [h1_BMTF_muMatched_eta, h1_BMTF_muMatched_MB34onlyMB3HO_eta],
    title = "BMTF efficiency",
    xTitle = "#eta^{reco-#mu}", yTitle = "efficiency",
    gridX = True,
    gridY = True,
    xMin = -1, xMax = 1,
    yMax = 1.1,
    legendPos = "LR",
    outFileName = "plots/MB34trackPt/MB34_efficiency_eta",
    outFileName_suffix = "SingleMuon",
)


####################################################################################################
h1_mu_pT = HistogramDetails()
h1_mu_pT.rootFileName = "output/SingleMuon_Run2017C-ZMu-PromptReco-v3_RAW-RECO_mediumMu0_BMTF22/DTNtuple_all_efficiency.root"
h1_mu_pT.histName = "mu_pT"
h1_mu_pT.getHist()
h1_mu_pT.hist.Rebin(5)

h1_BMTF_muMatched_pT = HistogramDetails()
h1_BMTF_muMatched_pT.rootFileName = "output/SingleMuon_Run2017C-ZMu-PromptReco-v3_RAW-RECO_mediumMu0_BMTF22/DTNtuple_all_efficiency.root"
h1_BMTF_muMatched_pT.histName = "BMTF_muMatched_pT"
h1_BMTF_muMatched_pT.histLabel = "BMTF"
h1_BMTF_muMatched_pT.drawOption = "hist E"
h1_BMTF_muMatched_pT.lineWidth = 2
h1_BMTF_muMatched_pT.lineColor = lineColor["BMTF"]
h1_BMTF_muMatched_pT.getHist()
h1_BMTF_muMatched_pT.hist.Rebin(5)

h1_isoMB1HO_muMatched_pT = HistogramDetails()
h1_isoMB1HO_muMatched_pT.rootFileName = "output/SingleMuon_Run2017C-ZMu-PromptReco-v3_RAW-RECO_mediumMu0_BMTF22/DTNtuple_all_efficiency.root"
h1_isoMB1HO_muMatched_pT.histName = "HQ/isoMB1HO_muMatched_pT"
h1_isoMB1HO_muMatched_pT.histLabel = "MB34 BMTF+HO"
h1_isoMB1HO_muMatched_pT.drawOption = "hist E"
h1_isoMB1HO_muMatched_pT.lineWidth = 2
h1_isoMB1HO_muMatched_pT.lineColor = lineColor["isoMB1HO"]
h1_isoMB1HO_muMatched_pT.getHist()
h1_isoMB1HO_muMatched_pT.hist.Rebin(5)
h1_isoMB1HO_muMatched_pT.hist.Add(h1_BMTF_muMatched_pT.hist)

h1_BMTF_muMatched_pT.hist.Divide(h1_mu_pT.hist)
h1_isoMB1HO_muMatched_pT.hist.Divide(h1_mu_pT.hist)

plot1D(
    [h1_BMTF_muMatched_pT, h1_isoMB1HO_muMatched_pT],
    title = "isoMB1+HO efficiency",
    xTitle = "p^{reco-#mu}_{T}", yTitle = "efficiency",
    gridX = True,
    gridY = True,
    xMin = 0, xMax = 100,
    yMax = 1.1,
    legendPos = "LR",
    outFileName = "plots/MBgap/isoMB1HO_efficiency_pT",
    outFileName_suffix = "SingleMuon",
)


####################################################################################################
h1_mu_eta = HistogramDetails()
h1_mu_eta.rootFileName = "output/SingleMuon_Run2017C-ZMu-PromptReco-v3_RAW-RECO_mediumMu25_BMTF22/DTNtuple_all_efficiency.root"
h1_mu_eta.histName = "mu_eta"
h1_mu_eta.getHist()

h1_BMTF_muMatched_eta = HistogramDetails()
h1_BMTF_muMatched_eta.rootFileName = "output/SingleMuon_Run2017C-ZMu-PromptReco-v3_RAW-RECO_mediumMu25_BMTF22/DTNtuple_all_efficiency.root"
h1_BMTF_muMatched_eta.histName = "BMTF_muMatched_eta"
h1_BMTF_muMatched_eta.histLabel = "BMTF"
h1_BMTF_muMatched_eta.drawOption = "E"
h1_BMTF_muMatched_eta.lineWidth = 2
h1_BMTF_muMatched_eta.lineColor = lineColor["BMTF"]
h1_BMTF_muMatched_eta.getHist()

h1_isoMB1HO_muMatched_eta = HistogramDetails()
h1_isoMB1HO_muMatched_eta.rootFileName = "output/SingleMuon_Run2017C-ZMu-PromptReco-v3_RAW-RECO_mediumMu25_BMTF22/DTNtuple_all_efficiency.root"
h1_isoMB1HO_muMatched_eta.histName = "HQ/isoMB1HO_muMatched_eta"
h1_isoMB1HO_muMatched_eta.histLabel = "BMTF + (isoMB1+HO)"
h1_isoMB1HO_muMatched_eta.drawOption = "E"
h1_isoMB1HO_muMatched_eta.lineWidth = 2
h1_isoMB1HO_muMatched_eta.lineColor = lineColor["isoMB1HO"]
h1_isoMB1HO_muMatched_eta.getHist()
h1_isoMB1HO_muMatched_eta.hist.Add(h1_BMTF_muMatched_eta.hist)

h1_BMTF_muMatched_eta.hist.Divide(h1_mu_eta.hist)
h1_isoMB1HO_muMatched_eta.hist.Divide(h1_mu_eta.hist)

plot1D(
    [h1_BMTF_muMatched_eta, h1_isoMB1HO_muMatched_eta],
    title = "isoMB1+HO efficiency",
    xTitle = "#eta^{reco-#mu}", yTitle = "efficiency",
    gridX = True,
    gridY = True,
    xMin = -1, xMax = 1,
    yMax = 1.1,
    legendPos = "LR",
    outFileName = "plots/MBgap/isoMB1HO_efficiency_eta",
    outFileName_suffix = "SingleMuon",
)


####################################################################################################
h2_BMTF_muMatched_pT_vs_eta = HistogramDetails()
h2_BMTF_muMatched_pT_vs_eta.rootFileName = "output/SingleMuon_Run2017C-ZMu-PromptReco-v3_RAW-RECO_mediumMu25_BMTF22/DTNtuple_all_efficiency.root"
h2_BMTF_muMatched_pT_vs_eta.histName = "BMTF_muMatched_pT_vs_eta"
h2_BMTF_muMatched_pT_vs_eta.getHist()
h2_BMTF_muMatched_pT_vs_eta.hist.RebinY(5)

h2_isoMB1HO_muMatched_pT_vs_eta = HistogramDetails()
h2_isoMB1HO_muMatched_pT_vs_eta.rootFileName = "output/SingleMuon_Run2017C-ZMu-PromptReco-v3_RAW-RECO_mediumMu25_BMTF22/DTNtuple_all_efficiency.root"
h2_isoMB1HO_muMatched_pT_vs_eta.histName = "HQ/isoMB1HO_muMatched_pT_vs_eta"
h2_isoMB1HO_muMatched_pT_vs_eta.histTitle = "BMTF + (isoMB1+HO) efficiency / BMTF efficiency"
h2_isoMB1HO_muMatched_pT_vs_eta.outFileName = "plots/MBgap/isoMB1HO_efficiency_pT_vs_eta"
h2_isoMB1HO_muMatched_pT_vs_eta.outFileName_suffix = "SingleMuon"
h2_isoMB1HO_muMatched_pT_vs_eta.drawOption = "colz"
h2_isoMB1HO_muMatched_pT_vs_eta.yMax = 100
h2_isoMB1HO_muMatched_pT_vs_eta.xTitle = "#eta^{reco-#mu}"
h2_isoMB1HO_muMatched_pT_vs_eta.yTitle = "p^{reco-#mu}_{T} [GeV]"
h2_isoMB1HO_muMatched_pT_vs_eta.gridX = True
h2_isoMB1HO_muMatched_pT_vs_eta.gridY = True
h2_isoMB1HO_muMatched_pT_vs_eta.xMin = -1
h2_isoMB1HO_muMatched_pT_vs_eta.xMax = 1
h2_isoMB1HO_muMatched_pT_vs_eta.zMin = 1
h2_isoMB1HO_muMatched_pT_vs_eta.getHist()
h2_isoMB1HO_muMatched_pT_vs_eta.hist.RebinY(5)
h2_isoMB1HO_muMatched_pT_vs_eta.hist.Add(h2_BMTF_muMatched_pT_vs_eta.hist)
h2_isoMB1HO_muMatched_pT_vs_eta.hist.Divide(h2_BMTF_muMatched_pT_vs_eta.hist)

plot2D(h2_isoMB1HO_muMatched_pT_vs_eta)


####################################################################################################
h1_mu_pT = HistogramDetails()
h1_mu_pT.rootFileName = "output/SingleMuon_Run2017C-ZMu-PromptReco-v3_RAW-RECO_mediumMu0_BMTF22_isoMB1HO3x3/DTNtuple_all_efficiency.root"
h1_mu_pT.histName = "mu_pT"
h1_mu_pT.getHist()
h1_mu_pT.hist.Rebin(5)

h1_BMTF_muMatched_pT = HistogramDetails()
h1_BMTF_muMatched_pT.rootFileName = "output/SingleMuon_Run2017C-ZMu-PromptReco-v3_RAW-RECO_mediumMu0_BMTF22_isoMB1HO3x3/DTNtuple_all_efficiency.root"
h1_BMTF_muMatched_pT.histName = "BMTF_muMatched_pT"
h1_BMTF_muMatched_pT.histLabel = "BMTF"
h1_BMTF_muMatched_pT.drawOption = "hist E"
h1_BMTF_muMatched_pT.lineWidth = 2
h1_BMTF_muMatched_pT.lineColor = lineColor["BMTF"]
h1_BMTF_muMatched_pT.getHist()
h1_BMTF_muMatched_pT.hist.Rebin(5)

h1_isoMB1HO_muMatched_pT = HistogramDetails()
h1_isoMB1HO_muMatched_pT.rootFileName = "output/SingleMuon_Run2017C-ZMu-PromptReco-v3_RAW-RECO_mediumMu0_BMTF22_isoMB1HO3x3/DTNtuple_all_efficiency.root"
h1_isoMB1HO_muMatched_pT.histName = "HQ/isoMB1HO_muMatched_pT"
h1_isoMB1HO_muMatched_pT.histLabel = "MB34 BMTF+HO"
h1_isoMB1HO_muMatched_pT.drawOption = "hist E"
h1_isoMB1HO_muMatched_pT.lineWidth = 2
h1_isoMB1HO_muMatched_pT.lineColor = lineColor["isoMB1HO"]
h1_isoMB1HO_muMatched_pT.getHist()
h1_isoMB1HO_muMatched_pT.hist.Rebin(5)
h1_isoMB1HO_muMatched_pT.hist.Add(h1_BMTF_muMatched_pT.hist)

h1_BMTF_muMatched_pT.hist.Divide(h1_mu_pT.hist)
h1_isoMB1HO_muMatched_pT.hist.Divide(h1_mu_pT.hist)

plot1D(
    [h1_BMTF_muMatched_pT, h1_isoMB1HO_muMatched_pT],
    title = "isoMB1+HO efficiency",
    xTitle = "p^{reco-#mu}_{T}", yTitle = "efficiency",
    gridX = True,
    gridY = True,
    xMin = 0, xMax = 100,
    yMax = 1.1,
    legendPos = "LR",
    outFileName = "plots/MBgap/isoMB1HO_efficiency_pT_isoMB1HO3x3",
    outFileName_suffix = "SingleMuon",
)


####################################################################################################
h1_mu_eta = HistogramDetails()
h1_mu_eta.rootFileName = "output/SingleMuon_Run2017C-ZMu-PromptReco-v3_RAW-RECO_mediumMu25_BMTF22_isoMB1HO3x3/DTNtuple_all_efficiency.root"
h1_mu_eta.histName = "mu_eta"
h1_mu_eta.getHist()

h1_BMTF_muMatched_eta = HistogramDetails()
h1_BMTF_muMatched_eta.rootFileName = "output/SingleMuon_Run2017C-ZMu-PromptReco-v3_RAW-RECO_mediumMu25_BMTF22_isoMB1HO3x3/DTNtuple_all_efficiency.root"
h1_BMTF_muMatched_eta.histName = "BMTF_muMatched_eta"
h1_BMTF_muMatched_eta.histLabel = "BMTF"
h1_BMTF_muMatched_eta.drawOption = "E"
h1_BMTF_muMatched_eta.lineWidth = 2
h1_BMTF_muMatched_eta.lineColor = lineColor["BMTF"]
h1_BMTF_muMatched_eta.getHist()

h1_isoMB1HO_muMatched_eta = HistogramDetails()
h1_isoMB1HO_muMatched_eta.rootFileName = "output/SingleMuon_Run2017C-ZMu-PromptReco-v3_RAW-RECO_mediumMu25_BMTF22_isoMB1HO3x3/DTNtuple_all_efficiency.root"
h1_isoMB1HO_muMatched_eta.histName = "HQ/isoMB1HO_muMatched_eta"
h1_isoMB1HO_muMatched_eta.histLabel = "BMTF + (isoMB1+HO)"
h1_isoMB1HO_muMatched_eta.drawOption = "E"
h1_isoMB1HO_muMatched_eta.lineWidth = 2
h1_isoMB1HO_muMatched_eta.lineColor = lineColor["isoMB1HO"]
h1_isoMB1HO_muMatched_eta.getHist()
h1_isoMB1HO_muMatched_eta.hist.Add(h1_BMTF_muMatched_eta.hist)

h1_BMTF_muMatched_eta.hist.Divide(h1_mu_eta.hist)
h1_isoMB1HO_muMatched_eta.hist.Divide(h1_mu_eta.hist)

plot1D(
    [h1_BMTF_muMatched_eta, h1_isoMB1HO_muMatched_eta],
    title = "isoMB1+HO efficiency",
    xTitle = "#eta^{reco-#mu}", yTitle = "efficiency",
    gridX = True,
    gridY = True,
    xMin = -1, xMax = 1,
    yMax = 1.1,
    legendPos = "LR",
    outFileName = "plots/MBgap/isoMB1HO_efficiency_eta_isoMB1HO3x3",
    outFileName_suffix = "SingleMuon",
)


####################################################################################################
h2_BMTF_muMatched_pT_vs_eta = HistogramDetails()
h2_BMTF_muMatched_pT_vs_eta.rootFileName = "output/SingleMuon_Run2017C-ZMu-PromptReco-v3_RAW-RECO_mediumMu25_BMTF22_isoMB1HO3x3/DTNtuple_all_efficiency.root"
h2_BMTF_muMatched_pT_vs_eta.histName = "BMTF_muMatched_pT_vs_eta"
h2_BMTF_muMatched_pT_vs_eta.getHist()
h2_BMTF_muMatched_pT_vs_eta.hist.RebinY(5)

h2_isoMB1HO_muMatched_pT_vs_eta = HistogramDetails()
h2_isoMB1HO_muMatched_pT_vs_eta.rootFileName = "output/SingleMuon_Run2017C-ZMu-PromptReco-v3_RAW-RECO_mediumMu25_BMTF22_isoMB1HO3x3/DTNtuple_all_efficiency.root"
h2_isoMB1HO_muMatched_pT_vs_eta.histName = "HQ/isoMB1HO_muMatched_pT_vs_eta"
h2_isoMB1HO_muMatched_pT_vs_eta.histTitle = "BMTF + (isoMB1+HO) efficiency / BMTF efficiency"
h2_isoMB1HO_muMatched_pT_vs_eta.outFileName = "plots/MBgap/isoMB1HO_efficiency_pT_vs_eta_isoMB1HO3x3"
h2_isoMB1HO_muMatched_pT_vs_eta.outFileName_suffix = "SingleMuon"
h2_isoMB1HO_muMatched_pT_vs_eta.drawOption = "colz"
h2_isoMB1HO_muMatched_pT_vs_eta.yMax = 100
h2_isoMB1HO_muMatched_pT_vs_eta.xTitle = "#eta^{reco-#mu}"
h2_isoMB1HO_muMatched_pT_vs_eta.yTitle = "p^{reco-#mu}_{T} [GeV]"
h2_isoMB1HO_muMatched_pT_vs_eta.gridX = True
h2_isoMB1HO_muMatched_pT_vs_eta.gridY = True
h2_isoMB1HO_muMatched_pT_vs_eta.xMin = -1
h2_isoMB1HO_muMatched_pT_vs_eta.xMax = 1
h2_isoMB1HO_muMatched_pT_vs_eta.zMin = 1
h2_isoMB1HO_muMatched_pT_vs_eta.getHist()
h2_isoMB1HO_muMatched_pT_vs_eta.hist.RebinY(5)
h2_isoMB1HO_muMatched_pT_vs_eta.hist.Add(h2_BMTF_muMatched_pT_vs_eta.hist)
h2_isoMB1HO_muMatched_pT_vs_eta.hist.Divide(h2_BMTF_muMatched_pT_vs_eta.hist)

plot2D(h2_isoMB1HO_muMatched_pT_vs_eta)


####################################################################################################
h1_mu_pT = HistogramDetails()
h1_mu_pT.rootFileName = "output/MET_Run2017C-v1_RAW/DTNtuple_all_efficiency.root"
h1_mu_pT.histName = "mu_pT"
h1_mu_pT.getHist()

h1_BMTF_muMatched_pT = HistogramDetails()
h1_BMTF_muMatched_pT.rootFileName = "output/MET_Run2017C-v1_RAW/DTNtuple_all_efficiency.root"
h1_BMTF_muMatched_pT.histName = "BMTF_muMatched_pT"
h1_BMTF_muMatched_pT.histLabel = "BMTF"
h1_BMTF_muMatched_pT.drawOption = "hist E"
h1_BMTF_muMatched_pT.lineWidth = 2
h1_BMTF_muMatched_pT.lineColor = lineColor["BMTF"]
h1_BMTF_muMatched_pT.getHist()

h1_isoMB1HO_muMatched_pT = HistogramDetails()
h1_isoMB1HO_muMatched_pT.rootFileName = "output/MET_Run2017C-v1_RAW/DTNtuple_all_efficiency.root"
h1_isoMB1HO_muMatched_pT.histName = "HQ/isoMB1HO_muMatched_pT"
h1_isoMB1HO_muMatched_pT.histLabel = "#splitline{BMTF+}{(isoMB1+HO)}"
h1_isoMB1HO_muMatched_pT.drawOption = "hist E"
h1_isoMB1HO_muMatched_pT.lineWidth = 2
h1_isoMB1HO_muMatched_pT.lineColor = lineColor["isoMB1HO"]
h1_isoMB1HO_muMatched_pT.getHist()
h1_isoMB1HO_muMatched_pT.hist.Add(h1_BMTF_muMatched_pT.hist)

h1_isoMB12HO_muMatched_pT = HistogramDetails()
h1_isoMB12HO_muMatched_pT.rootFileName = "output/MET_Run2017C-v1_RAW_isoMB12/DTNtuple_all_efficiency.root"
h1_isoMB12HO_muMatched_pT.histName = "HQ/isoMB1HO_muMatched_pT"
h1_isoMB12HO_muMatched_pT.histLabel = "#splitline{BMTF +}{(isoMB1/isoMB2+HO)}"
h1_isoMB12HO_muMatched_pT.drawOption = "hist E"
h1_isoMB12HO_muMatched_pT.lineWidth = 2
h1_isoMB12HO_muMatched_pT.lineColor = lineColor["isoMB12HO"]
h1_isoMB12HO_muMatched_pT.getHist()
h1_isoMB12HO_muMatched_pT.hist.Add(h1_BMTF_muMatched_pT.hist)

h1_BMTF_muMatched_pT.hist.Divide(h1_mu_pT.hist)
h1_isoMB1HO_muMatched_pT.hist.Divide(h1_mu_pT.hist)
h1_isoMB12HO_muMatched_pT.hist.Divide(h1_mu_pT.hist)

plot1D(
    [h1_BMTF_muMatched_pT, h1_isoMB1HO_muMatched_pT, h1_isoMB12HO_muMatched_pT],
    title = "isoMB1+HO efficiency",
    xTitle = "p^{reco-#mu}_{T}", yTitle = "efficiency",
    gridX = True,
    gridY = True,
    xMin = 0, xMax = 20,
    yMax = 1.1,
    legendPos = "LR",
    legendTextSize = 0.04,
    outFileName = "plots/lowPt/isoMB1HO_efficiency_pT",
    outFileName_suffix = "MET",
)


####################################################################################################
h1_mu_eta = HistogramDetails()
h1_mu_eta.rootFileName = "output/MET_Run2017C-v1_RAW/DTNtuple_all_efficiency.root"
h1_mu_eta.histName = "mu_eta"
h1_mu_eta.getHist()

h1_BMTF_muMatched_eta = HistogramDetails()
h1_BMTF_muMatched_eta.rootFileName = "output/MET_Run2017C-v1_RAW/DTNtuple_all_efficiency.root"
h1_BMTF_muMatched_eta.histName = "BMTF_muMatched_eta"
h1_BMTF_muMatched_eta.histLabel = "BMTF"
h1_BMTF_muMatched_eta.drawOption = "E"
h1_BMTF_muMatched_eta.lineWidth = 2
h1_BMTF_muMatched_eta.lineColor = lineColor["BMTF"]
h1_BMTF_muMatched_eta.getHist()

h1_isoMB1HO_muMatched_eta = HistogramDetails()
h1_isoMB1HO_muMatched_eta.rootFileName = "output/MET_Run2017C-v1_RAW/DTNtuple_all_efficiency.root"
h1_isoMB1HO_muMatched_eta.histName = "HQ/isoMB1HO_muMatched_eta"
h1_isoMB1HO_muMatched_eta.histLabel = "#splitline{BMTF +}{(isoMB1+HO)}"
h1_isoMB1HO_muMatched_eta.drawOption = "E"
h1_isoMB1HO_muMatched_eta.lineWidth = 2
h1_isoMB1HO_muMatched_eta.lineColor = lineColor["isoMB1HO"]
h1_isoMB1HO_muMatched_eta.getHist()
h1_isoMB1HO_muMatched_eta.hist.Add(h1_BMTF_muMatched_eta.hist)

h1_isoMB12HO_muMatched_eta = HistogramDetails()
h1_isoMB12HO_muMatched_eta.rootFileName = "output/MET_Run2017C-v1_RAW_isoMB12/DTNtuple_all_efficiency.root"
h1_isoMB12HO_muMatched_eta.histName = "HQ/isoMB1HO_muMatched_eta"
h1_isoMB12HO_muMatched_eta.histLabel = "#splitline{BMTF +}{(isoMB1/isoMB2+HO)}"
h1_isoMB12HO_muMatched_eta.drawOption = "E"
h1_isoMB12HO_muMatched_eta.lineWidth = 2
h1_isoMB12HO_muMatched_eta.lineColor = lineColor["isoMB12HO"]
h1_isoMB12HO_muMatched_eta.getHist()
h1_isoMB12HO_muMatched_eta.hist.Add(h1_BMTF_muMatched_eta.hist)


h1_BMTF_muMatched_eta.hist.Divide(h1_mu_eta.hist)
h1_isoMB1HO_muMatched_eta.hist.Divide(h1_mu_eta.hist)
h1_isoMB12HO_muMatched_eta.hist.Divide(h1_mu_eta.hist)

plot1D(
    [h1_BMTF_muMatched_eta, h1_isoMB1HO_muMatched_eta, h1_isoMB12HO_muMatched_eta],
    title = "isoMB1+HO efficiency",
    xTitle = "#eta^{reco-#mu}", yTitle = "efficiency",
    gridX = True,
    gridY = True,
    xMin = -1, xMax = 1,
    yMin = 0.65, yMax = 1.1,
    legendPos = "LR",
    legendTextSize = 0.04,
    outFileName = "plots/lowPt/isoMB1HO_efficiency_eta",
    outFileName_suffix = "MET",
)


####################################################################################################
h1_isoMB1HO_muMatched_3x3 = HistogramDetails()
h1_isoMB1HO_muMatched_3x3.rootFileName = "output/SingleMuon_Run2017C-ZMu-PromptReco-v3_RAW-RECO_mediumMu25_BMTF22/DTNtuple_all_efficiency.root"
h1_isoMB1HO_muMatched_3x3.histName = "HQ/isoMB1HO_muMatched_3x3"
h1_isoMB1HO_muMatched_3x3.histLabel = "#splitline{isoMB1+HO}{#mu^{reco} matched}"
h1_isoMB1HO_muMatched_3x3.drawOption = "hist"
h1_isoMB1HO_muMatched_3x3.lineWidth = 2
h1_isoMB1HO_muMatched_3x3.lineColor = 2
h1_isoMB1HO_muMatched_3x3.getHist()
h1_isoMB1HO_muMatched_3x3.hist.Scale(1.0 / h1_isoMB1HO_muMatched_3x3.hist.Integral())
print h1_isoMB1HO_muMatched_3x3.hist.GetBinContent(1), h1_isoMB1HO_muMatched_3x3.hist.GetBinContent(2)
print h1_isoMB1HO_muMatched_3x3.hist.GetCumulative(False).GetBinContent(3)

h1_isoMB1HO_muNotMatched_3x3 = HistogramDetails()
h1_isoMB1HO_muNotMatched_3x3.rootFileName = "output/SingleMuon_Run2017C-ZMu-PromptReco-v3_RAW-RECO_mediumMu25_BMTF22/DTNtuple_all_efficiency.root"
h1_isoMB1HO_muNotMatched_3x3.histName = "HQ/isoMB1HO_muNotMatched_3x3"
h1_isoMB1HO_muNotMatched_3x3.histLabel = "#splitline{isoMB1+HO}{#mu^{reco} not matched}"
h1_isoMB1HO_muNotMatched_3x3.drawOption = "hist"
h1_isoMB1HO_muNotMatched_3x3.lineWidth = 2
h1_isoMB1HO_muNotMatched_3x3.lineColor = 4
h1_isoMB1HO_muNotMatched_3x3.getHist()
h1_isoMB1HO_muNotMatched_3x3.hist.Scale(1.0 / h1_isoMB1HO_muNotMatched_3x3.hist.Integral())
print h1_isoMB1HO_muNotMatched_3x3.hist.GetBinContent(1), h1_isoMB1HO_muNotMatched_3x3.hist.GetBinContent(2)
print h1_isoMB1HO_muNotMatched_3x3.hist.GetCumulative(False).GetBinContent(3)
print h1_isoMB1HO_muNotMatched_3x3.hist.GetCumulative(False).GetBinContent(3)/h1_isoMB1HO_muMatched_3x3.hist.GetCumulative(False).GetBinContent(3)

plot1D(
    [h1_isoMB1HO_muMatched_3x3, h1_isoMB1HO_muNotMatched_3x3],
    title = "# HO hits in a 3x3 window",
    xTitle = "# HO hits", yTitle = "fraction",
    gridX = True,
    gridY = True,
    logY = True,
    yMax = 1.1,
    outFileName = "plots/MBgap/isoMB1HO_3x3",
    outFileName_suffix = "SingleMuon",
)


####################################################################################################
h1_MB34onlyBMTF_nearestHO_deltaR = HistogramDetails()
h1_MB34onlyBMTF_nearestHO_deltaR.rootFileName = "output/SingleMuon_Run2017C-ZMu-PromptReco-v3_RAW-RECO_tightMu25_BMTF22/DTNtuple_all_efficiency.root"
h1_MB34onlyBMTF_nearestHO_deltaR.histName = "MB34onlyBMTF_nearestHO_deltaR"
h1_MB34onlyBMTF_nearestHO_deltaR.drawOption = "hist"
h1_MB34onlyBMTF_nearestHO_deltaR.lineWidth = 2
h1_MB34onlyBMTF_nearestHO_deltaR.lineColor = 4
h1_MB34onlyBMTF_nearestHO_deltaR.getHist()

plot1D(
    [h1_MB34onlyBMTF_nearestHO_deltaR],
    title = "#DeltaR(HO, MB3)",
    xTitle = "#DeltaR(HO, MB3)", yTitle = "count",
    gridX = True,
    gridY = True,
    xMax = 1.0,
    logY = True,
    drawLegend = False,
    outFileName = "plots/MB34trackPt/MB34onlyBMTF_nearestHO_deltaR",
    outFileName_suffix = "SingleMuon",
)

