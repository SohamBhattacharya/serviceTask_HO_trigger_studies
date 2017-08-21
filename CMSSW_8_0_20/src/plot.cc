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
    const char *title, \
    const char *outFileName)
{
    TCanvas *canvas = new TCanvas("canvas", "canvas");
    canvas->SetCanvasSize(800, 800);
    
    TLegend *legend = new TLegend(0.5, 0.12, 0.88, 0.35);
    THStack *stack = new THStack();
    
    int axis_pT = 1;
    int rebin_nGroup = 150;
    
    int color;
    double alpha = 0.5;
    
    
    TH1F *h1_pileUp = (TH1F*) inFile->Get(name_pileUp)->Clone();
    h1_pileUp->Sumw2();
    h1_pileUp->Rebin(rebin_nGroup);
    
    
    color = 1;
    TH2F *h2_bmtfTrack = (TH2F*) inFile->Get(name_bmtfTrack)->Clone();
    h2_bmtfTrack->Sumw2();
    applyCut(h2_bmtfTrack, pT_cut, axis_pT);
    TH1F *h1_bmtfTrack = (TH1F*) h2_bmtfTrack->ProjectionY()->Clone();
    h1_bmtfTrack->Sumw2();
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
    h2_addTrack_LQ->Sumw2();
    applyCut(h2_addTrack_LQ, pT_cut, axis_pT);
    TH1F *h1_addTrack_LQ = (TH1F*) h2_addTrack_LQ->ProjectionY()->Clone();
    h1_addTrack_LQ->Sumw2();
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
    h2_addTrack_HQ->Sumw2();
    applyCut(h2_addTrack_HQ, pT_cut, axis_pT);
    TH1F *h1_addTrack_HQ = (TH1F*) h2_addTrack_HQ->ProjectionY()->Clone();
    h1_addTrack_HQ->Sumw2();
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
    
    stack->SetTitle(title);
    
    stack->GetXaxis()->SetTitle("PU");
    stack->GetXaxis()->CenterTitle();
    
    stack->GetYaxis()->SetTitle("Unprescaled rate [Hz]");
    stack->GetYaxis()->SetTitleOffset(1.4);
    stack->GetYaxis()->CenterTitle();
    
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
    
    
    std::vector <int> v_mu_pTcut = {3, 14, 22};
    
    
    for(int iCut = 0; iCut < v_mu_pTcut.size(); iCut++)
    {
        char fileName[500];
        char fileNameFull[500];
        char title[500];
        
        
        sprintf(fileName, "ratePlot_pT%d.pdf", v_mu_pTcut.at(iCut));
        sprintf(title, "p_{T, #mu} > %d GeV", v_mu_pTcut.at(iCut));
        
        
        /*inFile = TFile::Open("output/no_mipCheck/plots.root");
        sprintf(fileNameFull, "plots/no_mipCheck/%s", fileName);
        
        plotRate( \
            inFile, \
            "demo/PU_vs_bmtfTrack1_pT", \
            "demo/LQ/PU_vs_addTrack1_pT", \
            "demo/HQ/PU_vs_addTrack1_pT", \
            "demo/eventsPerPileUp", \
            (double) v_mu_pTcut.at(iCut), \
            scale, \
            title, \
            fileNameFull);
        
        delete inFile;*/
        
        
        /*inFile = TFile::Open("output/old/plots.root");
        sprintf(fileNameFull, "plots/old/%s", fileName);
        
        plotRate( \
            inFile, \
            "demo/PU_vs_bmtfTrack1_pT", \
            "demo/LQ/PU_vs_addTrack1_pT", \
            "demo/HQ/PU_vs_addTrack1_pT", \
            "demo/eventsPerPileUp", \
            (double) v_mu_pTcut.at(iCut), \
            scale, \
            title, \
            fileNameFull);
        
        delete inFile;*/
        
        
        inFile = TFile::Open("output/plots.root");
        sprintf(fileNameFull, "plots/%s", fileName);
        
        plotRate( \
            inFile, \
            "demo/PU_vs_bmtfTrack1_pT", \
            "demo/LQ/PU_vs_addTrack1_pT", \
            "demo/HQ/PU_vs_addTrack1_pT", \
            "demo/eventsPerPileUp", \
            (double) v_mu_pTcut.at(iCut), \
            scale, \
            title, \
            fileNameFull);
        
        delete inFile;
    }
    
    
    return 0;
}
