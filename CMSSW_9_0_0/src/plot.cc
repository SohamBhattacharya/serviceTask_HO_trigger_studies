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


void plotRate(TFile *inFile, \
    const char *name_bmtfTrack, \
    const char *name_addTrack_LQ, \
    const char *name_addTrack_HQ, \
    double pT_cut, \
    const char *outFileName)
{
    TCanvas *canvas = new TCanvas("canvas", "canvas");
    canvas->SetCanvasSize(800, 800);
    
    TLegend *legend = new TLegend(0.65, 0.65, 0.88, 0.88);
    THStack *stack = new THStack();
    
    int axis_pT = 1;
    
    TH2F *h2_bmtfTrack = (TH2F*) inFile->Get(name_bmtfTrack)->Clone();
    applyCut(h2_bmtfTrack, pT_cut, axis_pT);
    TH1F *h1_bmtfTrack = (TH1F*) h2_bmtfTrack->ProjectionY()->Clone();
    h1_bmtfTrack->SetMarkerColor(1);
    h1_bmtfTrack->SetLineColor(1);
    h1_bmtfTrack->SetLineWidth(2);
    stack->Add(h1_bmtfTrack);
    legend->AddEntry(h1_bmtfTrack, "BMTF");
    
    TH2F *h2_addTrack_LQ = (TH2F*) inFile->Get(name_addTrack_LQ)->Clone();
    applyCut(h2_addTrack_LQ, pT_cut, axis_pT);
    TH1F *h1_addTrack_LQ = (TH1F*) h2_addTrack_LQ->ProjectionY()->Clone();
    h1_addTrack_LQ->SetMarkerColor(2);
    h1_addTrack_LQ->SetLineColor(2);
    h1_addTrack_LQ->SetLineWidth(2);
    stack->Add(h1_addTrack_LQ);
    legend->AddEntry(h1_addTrack_LQ, "BMTF + HO/DT (LQ)");
    
    TH2F *h2_addTrack_HQ = (TH2F*) inFile->Get(name_addTrack_HQ)->Clone();
    applyCut(h2_addTrack_HQ, pT_cut, axis_pT);
    TH1F *h1_addTrack_HQ = (TH1F*) h2_addTrack_HQ->ProjectionY()->Clone();
    h1_addTrack_HQ->SetMarkerColor(3);
    h1_addTrack_HQ->SetLineColor(3);
    h1_addTrack_HQ->SetLineWidth(2);
    stack->Add(h1_addTrack_HQ);
    legend->AddEntry(h1_addTrack_HQ, "BMTF + HO/DT (HQ)");
    
    stack->Draw();//"nostack");
    legend->Draw();
    
    canvas->SetLogy();
    
    canvas->SaveAs(outFileName);
    canvas->Close();
}


int main()
{
    TFile *inFile = TFile::Open("output/plots.root");
    
    plotRate( \
        inFile, \
        "demo/PU_vs_bmtfTrack1_pT", \
        "demo/LQ/PU_vs_addTrack1_pT", \
        "demo/HQ/PU_vs_addTrack1_pT", \
        3.0, \
        "plots/ratePlot.pdf");
        
    
    return 0;
}
