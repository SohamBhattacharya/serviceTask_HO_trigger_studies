# include <iostream>
# include <vector>

# include <TCanvas.h>
# include <TFile.h>
# include <TH1F.h>
# include <THStack.h>
# include <TLegend.h>


void plot(std::vector <TH1F*> *v_hist, \
    std::vector <std::string> *v_label, \
    const char *title, \
    const char *outFileName);


TH1F* getHistogramRatio(TFile *inputFile, \
    const char *histNumName, \
    const char *histDenName);


int main()
{
    TFile *inputFile;
    
    //inputFile = TFile::Open("output/efficiency.root");
    inputFile = TFile::Open("output/SingleMuon/DTNtuple_all_efficiency.root");
    
    
    int nStation = 4;
    
    
    //for(int iStation = 0; iStation < nStation; iStation++)
    for(int iStation = 1; iStation < 2; iStation++)
    {
        char histNumName[500];
        char histDenName[500];
        char title[500];
        char outFileName[500];
        
        std::vector <TH1F*> v_hist;
        std::vector <std::string> v_histLabel;
        
        
        // DTTP efficiency
        sprintf(title, "TwinMux trigger efficiency vs. #eta_{#mu} in Station %d", iStation+1);
        sprintf(outFileName, "plots/DTTP_efficiency_mu_eta_station%d.pdf", iStation+1);
        
        sprintf(histNumName, "dtdegm4D_withDTTP_mu_eta_station%d", iStation+1);
        sprintf(histDenName, "dtdegm4D_mu_eta_station%d", iStation+1);
        v_histLabel.push_back("DTTP");
        v_hist.push_back(getHistogramRatio( \
            inputFile, \
            histNumName, \
            histDenName));
        
        sprintf(histNumName, "dtdegm4D_noDTTP_withMB1DTTP_withHOTP_mu_eta_station%d", iStation+1);
        //sprintf(histDenName, "dtdegm4D_noDTTP_mu_eta_station%d", iStation+1);
        v_histLabel.push_back("DT + HO");
        v_hist.push_back(getHistogramRatio( \
            inputFile, \
            histNumName, \
            histDenName));
        
        plot(&v_hist, \
            &v_histLabel, \
            title, \
            outFileName);
        
        v_hist.clear();
        v_histLabel.clear();
        
        
        // HO support for DTTP
        sprintf(title, "HO support for missing DTTP vs. #eta_{#mu} in Station %d", iStation+1);
        sprintf(outFileName, "plots/DTTP_HOsupport_mu_eta_station%d.pdf", iStation+1);
        
        sprintf(histNumName, "dtdegm4D_noDTTP_withMB1DTTP_withHOTP_mu_eta_station%d", iStation+1);
        sprintf(histDenName, "dtdegm4D_noDTTP_mu_eta_station%d", iStation+1);
        v_histLabel.push_back("HO");
        v_hist.push_back(getHistogramRatio( \
            inputFile, \
            histNumName, \
            histDenName));
        
        plot(&v_hist, \
            &v_histLabel, \
            title, \
            outFileName);
        
        v_hist.clear();
        v_histLabel.clear();
        
        
        // BMTF efficiency
        sprintf(title, "BMTF efficiency vs. #eta_{#mu} in Station %d", iStation+1);
        sprintf(outFileName, "plots/BMTF_efficiency_mu_eta_station%d.pdf", iStation+1);
        
        sprintf(histNumName, "dtdegm4D_withDTTP_withBMTF_mu_eta_station%d", iStation+1);
        sprintf(histDenName, "dtdegm4D_withDTTP_mu_eta_station%d", iStation+1);
        v_histLabel.push_back("BMTF");
        v_hist.push_back(getHistogramRatio( \
            inputFile, \
            histNumName, \
            histDenName));
        
        sprintf(histNumName, "dtdegm4D_noDTTP_noBMTF_withMB1DTTP_withHOTP_mu_eta_station%d", iStation+1);
        //sprintf(histDenName, "dtdegm4D_mu_eta_station%d", iStation+1);
        v_histLabel.push_back("BMTF + HO");
        v_hist.push_back(getHistogramRatio( \
            inputFile, \
            histNumName, \
            histDenName));
        
        /*TH1F *histTemp = (TH1F*) v_hist.at(0)->Clone();
        histTemp->Multiply(v_hist.at(1));
        histTemp->Scale(-1);
        histTemp->Add(v_hist.at(0));
        histTemp->Add(v_hist.at(1));
        v_hist.at(1) = histTemp;*/
        
        plot(&v_hist, \
            &v_histLabel, \
            title, \
            outFileName);
        
        v_hist.clear();
        v_histLabel.clear();
        
        
        // BMTF recovery potential
        sprintf(title, "BMTF recovery potential vs. #eta_{#mu} in Station %d", iStation+1);
        sprintf(outFileName, "plots/BMTF_recoveryPotential_mu_eta_station%d.pdf", iStation+1);
        
        sprintf(histNumName, "dtdegm4D_noDTTP_noBMTF_mu_eta_station%d", iStation+1);
        sprintf(histDenName, "dtdegm4D_mu_eta_station%d", iStation+1);
        v_histLabel.push_back("no DTTP, no BMTF");
        v_hist.push_back(getHistogramRatio( \
            inputFile, \
            histNumName, \
            histDenName));
        
        plot(&v_hist, \
            &v_histLabel, \
            title, \
            outFileName);
        
        v_hist.clear();
        v_histLabel.clear();
        
        
        // HO support for BMTF
        sprintf(title, "HO support for missing BMTF vs. #eta_{#mu} in Station %d", iStation+1);
        sprintf(outFileName, "plots/BMTF_HOsupport_mu_eta_station%d.pdf", iStation+1);
        
        sprintf(histNumName, "dtdegm4D_noDTTP_noBMTF_withMB1DTTP_withHOTP_mu_eta_station%d", iStation+1);
        sprintf(histDenName, "dtdegm4D_noDTTP_noBMTF_mu_eta_station%d", iStation+1);
        v_histLabel.push_back("#splitline{no DTTP, no BMTF}{with MB1, with HO}");
        v_hist.push_back(getHistogramRatio( \
            inputFile, \
            histNumName, \
            histDenName));
        
        plot(&v_hist, \
            &v_histLabel, \
            title, \
            outFileName);
        
        v_hist.clear();
        v_histLabel.clear();
    }
    
    
    delete inputFile;
    
    return 0;
}


TH1F* getHistogramRatio(TFile *inputFile, \
    const char *histNumName, \
    const char *histDenName)
{
    TH1F *histRatio = (TH1F*) inputFile->Get(histNumName)->Clone();
    histRatio->Sumw2();
    
    histRatio->Divide((TH1F*) inputFile->Get(histDenName)->Clone());
    
    return histRatio;
}


void plot(std::vector <TH1F*> *v_hist, \
    std::vector <std::string> *v_label, \
    const char *title, \
    const char *outFileName)
{
    TCanvas *canvas = new TCanvas("canvas", "canvas");
    canvas->SetCanvasSize(800, 800);
    
    TLegend *legend = new TLegend(0.65, 0.15, 0.88, 0.25);
    THStack *stack = new THStack();
    
    int nHist = v_hist->size();
    
    canvas->cd(1);
    
    for(int iHist = 0; iHist < nHist; iHist++)
    {
        int color = iHist+1;
        
        v_hist->at(iHist)->SetLineWidth(2);
        v_hist->at(iHist)->SetLineColor(color);
        
        legend->AddEntry(v_hist->at(iHist), v_label->at(iHist).c_str());
        stack->Add(v_hist->at(iHist), "E");
    }
    
    stack->SetTitle(title);
    
    //stack->Draw("nostack");
    stack->Draw();
    
    stack->GetXaxis()->SetRangeUser(-1.5, 1.5);
    stack->SetMinimum(0.0);
    stack->SetMaximum(1.0);
    
    legend->Draw();
    
    canvas->SetGridx();
    canvas->SetGridy();
    
    canvas->SaveAs(outFileName);
    canvas->Close();
}
