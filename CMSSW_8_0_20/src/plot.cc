# include <iostream>
# include <vector>

# include "TFile.h"
# include "TH1F.h"
# include "TH2F.h"
# include "TCanvas.h"
# include "TLegend.h"
# include "THStack.h"


void applyCut(TH2F *hist, double cut, int axis)
{
    int cutBinX = hist->GetNbinsX();
    int cutBinY = hist->GetNbinsY();
    
    if(axis == 1)
    {
        cutBinX = hist->GetXaxis()->FindBin(cut);
    }
    
    else if(axis == 2)
    {
        cutBinY = hist->GetYaxis()->FindBin(cut);
    }
    
    for(int iBinX = 1; iBinX < cutBinX; iBinX++)
    {
        for(int iBinY = 1; iBinY < cutBinY; iBinY++)
        {
            hist->SetBinContent(iBinX, iBinY, 0.0);
        }
    }
}


void scaleHistBins(TH1F *hist)
{
    for(int iBin = 1; iBin < hist->GetNbinsX(); iBin++)
    {
        double binContent = hist->GetBinContent(iBin);
        double binCenter = hist->GetXaxis()->GetBinCenter(iBin);
        printf("(%f, %f) ", binCenter, binContent);
        binContent *= binCenter;
        
        hist->SetBinContent(iBin, binContent);
    }
    printf("\n\n");
}


void plotRate(TFile *inFile, \
    const char *name_bmtfTrack, \
    const char *name_addTrack_LQ, \
    const char *name_addTrack_HQ, \
    const char *name_pileUp, \
    double pT_cut, \
    double histScale, \
    const char *outFileName)
{
    TCanvas *canvas = new TCanvas("canvas", "canvas");
    canvas->SetCanvasSize(800, 800);
    
    TLegend *legend = new TLegend(0.65, 0.15, 0.88, 0.35);
    THStack *stack = new THStack();
    
    int axis_pT = 1;
    int rebin_nGroup = 150;
    
    int color;
    double alpha = 0.5;
    
    
    TH1F *h1_pileUp = (TH1F*) inFile->Get(name_pileUp)->Clone();
    h1_pileUp->Rebin(rebin_nGroup);
    
    
    color = 1;
    TH2F *h2_bmtfTrack = (TH2F*) inFile->Get(name_bmtfTrack)->Clone();
    applyCut(h2_bmtfTrack, pT_cut, axis_pT);
    TH1F *h1_bmtfTrack = (TH1F*) h2_bmtfTrack->ProjectionY()->Clone();
    h1_bmtfTrack->Rebin(rebin_nGroup);
    h1_bmtfTrack->Divide(h1_pileUp);
    h1_bmtfTrack->Scale(histScale);
    h1_bmtfTrack->SetMarkerColor(color);
    h1_bmtfTrack->SetLineColor(color);
    //h1_bmtfTrack->SetFillColorAlpha(color, alpha);
    h1_bmtfTrack->SetLineWidth(2);
    stack->Add(h1_bmtfTrack, "E");
    legend->AddEntry(h1_bmtfTrack, "BMTF");
    
    
    color = 2;
    TH2F *h2_addTrack_LQ = (TH2F*) inFile->Get(name_addTrack_LQ)->Clone();
    applyCut(h2_addTrack_LQ, pT_cut, axis_pT);
    TH1F *h1_addTrack_LQ = (TH1F*) h2_addTrack_LQ->ProjectionY()->Clone();
    h1_addTrack_LQ->Rebin(rebin_nGroup);
    h1_addTrack_LQ->Divide(h1_pileUp);
    h1_addTrack_LQ->Scale(histScale);
    h1_addTrack_LQ->Add(h1_bmtfTrack);
    h1_addTrack_LQ->SetMarkerColor(color);
    h1_addTrack_LQ->SetLineColor(color);
    //h1_addTrack_LQ->SetFillColorAlpha(color, alpha);
    h1_addTrack_LQ->SetLineWidth(2);
    stack->Add(h1_addTrack_LQ, "E");
    legend->AddEntry(h1_addTrack_LQ, "BMTF + HO/DT (LQ)");
    
    
    color = 4;
    TH2F *h2_addTrack_HQ = (TH2F*) inFile->Get(name_addTrack_HQ)->Clone();
    applyCut(h2_addTrack_HQ, pT_cut, axis_pT);
    TH1F *h1_addTrack_HQ = (TH1F*) h2_addTrack_HQ->ProjectionY()->Clone();
    h1_addTrack_HQ->Rebin(rebin_nGroup);
    h1_addTrack_HQ->Divide(h1_pileUp);
    h1_addTrack_HQ->Scale(histScale);
    h1_addTrack_HQ->Add(h1_bmtfTrack);
    h1_addTrack_HQ->SetMarkerColor(color);
    h1_addTrack_HQ->SetLineColor(color);
    //h1_addTrack_HQ->SetFillColorAlpha(color, alpha);
    h1_addTrack_HQ->SetLineWidth(2);
    stack->Add(h1_addTrack_HQ, "E");
    legend->AddEntry(h1_addTrack_HQ, "BMTF + HO/DT (HQ)");
    
    
    stack->Draw("nostack");
    
    stack->SetTitle("Unprescaled rate [Hz] vs. PU");
    
    //stack->GetXaxis()->SetTitle("PU");
    //stack->GetYaxis()->SetTitle("Unprescaled rate [Hz]");
    
    legend->Draw();
    
    canvas->SetGridx();
    canvas->SetGridy();
    
    //canvas->SetLogy();
    
    canvas->SaveAs(outFileName);
    canvas->Close();
}


int main()
{
    TFile *inFile;
    
    double scale = 11245.5; // Hz (Revolution frequency of bunches)
    
    
    inFile = TFile::Open("output/no_mipCheck/plots.root");
    
    plotRate( \
        inFile, \
        "demo/PU_vs_bmtfTrack1_pT", \
        "demo/LQ/PU_vs_addTrack1_pT", \
        "demo/HQ/PU_vs_addTrack1_pT", \
        "demo/eventsPerPileUp", \
        3.0, \
        scale, \
        "plots/no_mipCheck/ratePlot.pdf");
    
    delete inFile;
    
    
    inFile = TFile::Open("output/plots.root");
    
    plotRate( \
        inFile, \
        "demo/PU_vs_bmtfTrack1_pT", \
        "demo/LQ/PU_vs_addTrack1_pT", \
        "demo/HQ/PU_vs_addTrack1_pT", \
        "demo/eventsPerPileUp", \
        3.0, \
        scale, \
        "plots/ratePlot.pdf");
    
    delete inFile;
    
    return 0;
}
