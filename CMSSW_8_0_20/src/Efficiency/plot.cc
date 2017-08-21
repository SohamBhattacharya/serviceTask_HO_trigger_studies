# include <algorithm>
# include <iostream>
# include <string>
# include <vector>

# include <TCanvas.h>
# include <TFile.h>
# include <TGaxis.h>
# include <TH1F.h>
# include <TH2F.h>
# include <THStack.h>
# include <TStyle.h>
# include <TLegend.h>


void plot(std::vector <TH1F*> *v_hist, \
    std::vector <std::string> *v_label, \
    double xMin, double xMax, \
    double yMin, double yMax, \
    const char *title, \
    const char *outFileName);


TH1F* getHistogramRatio(TFile *inputFile, \
    const char *histNumName, \
    const char *histDenName);


int nStation = 4;
std::vector <std::string> v_quality = {"LQ", "HQ"};


void plot_efficiency(TFile *inputFile);
void plot_MB_HO(TFile *inputFile);


int main()
{
    TFile *inputFile;
    
    //inputFile = TFile::Open("output/efficiency.root");
    //inputFile = TFile::Open("output/SingleMuon/DTNtuple_all_efficiency.root");
    inputFile = TFile::Open("output/ZeroBias9/DTNtuple_all_efficiency.root");
    
    
    //plot_efficiency(inputFile);
    plot_MB_HO(inputFile);
    
    
    delete inputFile;
    
    return 0;
}


void plot_MB_HO(TFile *inputFile)
{
    char histName[500];
    char histNumName[500];
    char histDenName[500];
    char histLabel[500];
    char title[500];
    char outFileName[500];
    
    std::vector <TH1F*> v_hist;
    std::vector <std::string> v_histLabel;
    
    std::vector <std::string> v_h1Name = {
        "MB1DTTP_deltaPhi",
        "unisolatedMB1DTTP_deltaBX",
        "unisolatedMB1DTTP_deltaPhi",
        "isolatedMB1DTTP_HOTP_deltaIphi",
        "isolatedMB1DTTP_HOTP_deltaWheel"
    };
    
    std::vector <std::string> v_h2Name = {
        "unisolatedMB1DTTP_deltaBX_vs_deltaPhi",
        "unisolatedMB1DTTP_HOTP_deltaIphi_vs_deltaWheel",
        "unisolatedMB1DTTP_HOTP_deltaIphi_vs_deltaIeta",
        "unisolatedMB1DTTP_HOTP_deltaSector_vs_deltaWheel",
        "unisolatedMB1DTTP_vs_HOTP_iEta",
        "unisolatedMB1DTTP_vs_HOTP_etaGlobal",
        "unisolatedPlusMB1DTTP_vs_HOTP_etaLocal",
        "unisolatedMinusMB1DTTP_vs_HOTP_etaLocal",
        "unisolatedMB1DTTP_vs_HOTP_iPhi",
        "unisolatedMB1DTTP_vs_HOTP_phiLocal",
        
        "isolatedMB1DTTP_vs_HOTP_iEta",
        "isolatedMB1DTTP_vs_HOTP_etaGlobal",
        "isolatedPlusMB1DTTP_vs_HOTP_etaLocal",
        "isolatedMinusMB1DTTP_vs_HOTP_etaLocal",
        "isolatedMB1DTTP_vs_HOTP_iPhi",
        "isolatedMB1DTTP_vs_HOTP_phiLocal",
        "isolatedMB1DTTP_iPhi_vs_wheel",
        "isolatedMB1DTTP_HOTP_deltaIphi_vs_deltaWheel",
        "isolatedMB1DTTP_HOTP_deltaIphi_vs_deltaIeta",
        "isolatedMB1DTTP_HOTP_deltaSector_vs_deltaWheel",
        "HOTP_iPhi_vs_wheel"
    };
    
    for(int iHist = 0; iHist < v_h1Name.size(); iHist++)
    {
        sprintf(outFileName, "plots/MB_HO/%s.pdf", v_h1Name.at(iHist).c_str());
        
        for(int iQual = 0; iQual < v_quality.size(); iQual++)
        {
            sprintf(histName, "%s/%s", v_quality.at(iQual).c_str(), v_h1Name.at(iHist).c_str());
            
            v_histLabel.push_back(v_quality.at(iQual).c_str());
            v_hist.push_back((TH1F*) inputFile->Get(histName)->Clone());
            v_hist.at(v_hist.size()-1)->Sumw2();
        }
        
        plot(&v_hist, \
            &v_histLabel, \
            0, 0, \
            0, 0, \
            v_h1Name.at(iHist).c_str(), \
            outFileName);
        
        v_hist.clear();
        v_histLabel.clear();
    }
    
    for(int iHist = 0; iHist < v_h2Name.size(); iHist++)
    {
        if(!(v_h2Name.at(iHist).compare("unisolatedMB1DTTP_vs_HOTP_phiLocal") == 0 \
            || v_h2Name.at(iHist).compare("isolatedMB1DTTP_vs_HOTP_phiLocal") == 0))
        {
            continue;
        }
        
        for(int iQual = 0; iQual < v_quality.size(); iQual++)
        {
            sprintf(histName, "%s/%s", v_quality.at(iQual).c_str(), v_h2Name.at(iHist).c_str());
            
            for(int iPhi = 0; iPhi < 6; iPhi++)
            {
                sprintf(title, "%s [%s, i#phi^{local}_{HO} %d]", v_h2Name.at(iHist).c_str(), v_quality.at(iQual).c_str(), iPhi);
                
                std::string title_mod = std::string(title);
                title_mod.replace(title_mod.find("_vs_HOTP"), strlen("_vs_HOTP"), "");
                
                system("mkdir -p plots/MB_HO/localPhiLUT");
                sprintf(outFileName, "plots/MB_HO/localPhiLUT/%s_%s_HOiPhi%d.pdf", v_h2Name.at(iHist).c_str(), v_quality.at(iQual).c_str(), iPhi);
                
                sprintf(histLabel, "HO %d", iPhi);
                
                TH2F *hist = (TH2F*) inputFile->Get(histName)->Clone();
                hist->SetDirectory(0);
                
                for(int iBinX = 1; iBinX < hist->GetNbinsX(); iBinX++)
                {
                    for(int iBinY = 1; iBinY < hist->GetNbinsY(); iBinY++)
                    {
                        if(iBinX != iPhi+1)
                        {
                            hist->SetBinContent(iBinX, iBinY, 0.0);
                        }
                    }
                }
                
                //v_histLabel.push_back(std::string(histLabel));
                
                v_hist.push_back((TH1F*) hist->ProjectionY()->Clone());
                v_hist.at(v_hist.size()-1)->Sumw2();
                //v_hist.at(v_hist.size()-1)->SetOption("hist");
                
                plot(&v_hist, \
                    &v_histLabel, \
                    -700, 1500, \
                    0, 0, \
                    title_mod.c_str(), \
                    outFileName);
                
                v_hist.clear();
                v_histLabel.clear();
            }
        }
    }
    
    for(int iHist = 0; iHist < v_h2Name.size(); iHist++)
    {
        // {iEta_start, iEta_end, wheel}
        std::vector <std::vector <int> > v_iEta_range_minus = {
            {-11, -15, -2},
            {-5, -10, -1},
            {4, -4, 0}
        };
        
        std::vector <std::vector <int> > v_iEta_range_plus = {
            {-4, 4, 0},
            {5, 10, 1},
            {11, 15, 2}
        };
        
        std::vector <std::vector <int> > v_iEta_range;
        
        std::string orientation;
        
        int sign = 1;
        
        if(v_h2Name.at(iHist).compare("isolatedPlusMB1DTTP_vs_HOTP_etaLocal") == 0)
        {
            sign = 1;
            orientation = "plus";
            
            v_iEta_range = v_iEta_range_plus;
        }
        
        else if(v_h2Name.at(iHist).compare("isolatedMinusMB1DTTP_vs_HOTP_etaLocal") == 0)
        {
            sign = -1;
            orientation = "minus";
            
            v_iEta_range = v_iEta_range_minus;
        }
        
        else
        {
            continue;
        }
        
        for(int iQual = 1; iQual < v_quality.size(); iQual++)
        {
            sprintf(histName, "%s/%s", v_quality.at(iQual).c_str(), v_h2Name.at(iHist).c_str());
            
            for(int iWh = 0; iWh < v_iEta_range.size(); iWh++)
            {
                int localiEta = 0;
                
                for(int iEta = v_iEta_range.at(iWh).at(0); sign*iEta <= sign*v_iEta_range.at(iWh).at(1); iEta += sign)
                {
                    if(iEta == 0)
                    {
                        continue;
                    }
                    printf("%d %d \n", v_iEta_range.at(iWh).at(2), iEta);
                    sprintf(title, "%s [%s, wh_{HO} %d, i#eta^{local}_{HO} %d]", v_h2Name.at(iHist).c_str(), v_quality.at(iQual).c_str(), v_iEta_range.at(iWh).at(2), localiEta);
                    
                    std::string title_mod = std::string(title);
                    title_mod.replace(title_mod.find("_vs_HOTP"), strlen("_vs_HOTP"), "");
                    
                    system("mkdir -p plots/MB_HO/localEtaLUT");
                    sprintf(outFileName, "plots/MB_HO/localEtaLUT/%s_%s_wh%d_iEtaLocal%d.pdf", v_h2Name.at(iHist).c_str(), v_quality.at(iQual).c_str(), v_iEta_range.at(iWh).at(2), localiEta);
                    
                    sprintf(histLabel, "wh %d", v_iEta_range.at(iWh).at(2));
                    
                    //printf("%s \n %s \n %s \n %s \n", histName, title, title_mod.c_str(), outFileName);
                    
                    TH2F *hist = (TH2F*) inputFile->Get(histName)->Clone();
                    hist->SetDirectory(0);
                    
                    for(int iBinX = 1; iBinX < hist->GetNbinsX(); iBinX++)
                    {
                        for(int iBinY = 1; iBinY < hist->GetNbinsY(); iBinY++)
                        {
                            if((int) hist->GetXaxis()->GetBinLowEdge(iBinX) != iEta)
                            {
                                hist->SetBinContent(iBinX, iBinY, 0.0);
                            }
                        }
                    }
                    
                    //v_histLabel.push_back(std::string(histLabel));
                    
                    v_hist.push_back((TH1F*) hist->ProjectionY()->Clone());
                    v_hist.at(v_hist.size()-1)->Sumw2();
                    //v_hist.at(v_hist.size()-1)->SetOption("hist");
                    
                    plot(&v_hist, \
                        &v_histLabel, \
                        0, 0, \
                        0, 0, \
                        title_mod.c_str(), \
                        outFileName);
                    
                    v_hist.clear();
                    v_histLabel.clear();
                    
                    localiEta++;
                }
            }
        }
        
        /*for(int iQual = 1; iQual < v_quality.size(); iQual++)
        {
            sprintf(histName, "%s/%s", v_quality.at(iQual).c_str(), v_h2Name.at(iHist).c_str());
            
            for(int iWh = 0; iWh < v_iEta_range.size(); iWh++)
            {
                sprintf(title, "%s [%s, wh %d]", v_h2Name.at(iHist).c_str(), v_quality.at(iQual).c_str(), v_iEta_range.at(2));
                
                os.system("mkdir -p plots/MB_HO/localEtaLUT");
                sprintf(outFileName, "plots/MB_HO/localEtaLUT/%s_%s_wh%d.pdf", v_h2Name.at(iHist).c_str(), v_quality.at(iQual).c_str(), v_iEta_range.at(2));
                
                sprintf(histLabel, "wh %d", v_iEta_range.at(2));
                
                std::string title_mod = std::string(title);
                title_mod.replace(title_mod.find("_vs_HOTP"), strlen("_vs_HOTP"), "");
                
                TH1F *histNew = new TH1F(v_h2Name.at(iHist).c_str(), title, 10, 0, 10);
                
                TH2F *hist = (TH2F*) inputFile->Get(histName)->Clone();
                hist->SetDirectory(0);
                
                TH1F *histProjX = (TH1F*) histProjX->ProjectionX()->Clone();
                
                for(int iBinX = 1; iBinX < hist->GetNbinsX(); iBinX++)
                {
                    if(iBinX != iPhi+1)
                    {
                        hist->SetBinContent(iBinX, iBinY, 0.0);
                    }
                }
            }
        }
            
            for(int iPhi = 0; iPhi < 6; iPhi++)
            {
                sprintf(title, "%s [%s, i#eta^{local}_{HO} %d]", v_h2Name.at(iHist).c_str(), v_quality.at(iQual).c_str(), iPhi);
                sprintf(outFileName, "plots/MB_HO/%s_%s_HOiPhi%d.pdf", v_h2Name.at(iHist).c_str(), v_quality.at(iQual).c_str(), iPhi);
                sprintf(histLabel, "HO %d", iPhi);
                
                TH2F *hist = (TH2F*) inputFile->Get(histName)->Clone();
                hist->SetDirectory(0);
                
                for(int iBinX = 1; iBinX < hist->GetNbinsX(); iBinX++)
                {
                    for(int iBinY = 1; iBinY < hist->GetNbinsY(); iBinY++)
                    {
                        if(iBinX != iPhi+1)
                        {
                            hist->SetBinContent(iBinX, iBinY, 0.0);
                        }
                    }
                }
                
                //v_histLabel.push_back(std::string(histLabel));
                
                v_hist.push_back((TH1F*) hist->ProjectionY()->Clone());
                v_hist.at(v_hist.size()-1)->Sumw2();
                //v_hist.at(v_hist.size()-1)->SetOption("hist");
                
                std::string title_mod = std::string(title);
                title_mod.replace(title_mod.find("_vs_HOTP"), strlen("_vs_HOTP"), "");
                
                plot(&v_hist, \
                    &v_histLabel, \
                    -700, 1500, \
                    0, 0, \
                    title_mod.c_str(), \
                    outFileName);
                
                v_hist.clear();
                v_histLabel.clear();
            }
        }*/
    }
    
    for(int iHist = 0; iHist < v_h2Name.size(); iHist++)
    {
        for(int iQual = 0; iQual < v_quality.size(); iQual++)
        {
            sprintf(histName, "%s/%s", v_quality.at(iQual).c_str(), v_h2Name.at(iHist).c_str());
            sprintf(title, "%s [%s]", v_h2Name.at(iHist).c_str(), v_quality.at(iQual).c_str());
            sprintf(outFileName, "plots/MB_HO/%s_%s.pdf", v_h2Name.at(iHist).c_str(), v_quality.at(iQual).c_str());
            
            TH2F *hist = (TH2F*) inputFile->Get(histName)->Clone();
            
            TCanvas *canvas = new TCanvas("canvas", "canvas");
            canvas->SetCanvasSize(800, 800);
            
            hist->SetTitle(title);
            hist->SetStats(0);
            
            // Size of text draw option is proportional to the marker size
            hist->SetMarkerSize(0.75);
            
            //hist->Draw("colz text");
            if(v_h2Name.at(iHist).compare("isolatedPlusMB1DTTP_vs_HOTP_etaLocal") >= 0 
                || v_h2Name.at(iHist).compare("isolatedMinusMB1DTTP_vs_HOTP_etaLocal") >= 0
                || v_h2Name.at(iHist).compare("isolatedMB1DTTP_HOTP_deltaSector_vs_deltaWheel") >= 0)
            {
                hist->Draw("colz text89");
            }
            
            else
            {
                hist->Draw("colz");
            }
            
            // Color axis number in scientific notation
            TGaxis::SetMaxDigits(4);
            
            //canvas->SetLogy();
            //if(iHist == 2)
            //{
            //    canvas->SetLogz();
            //}
            
            canvas->SetGridx();
            canvas->SetGridy();
            
            canvas->SetRightMargin(0.135);
            
            canvas->SaveAs(outFileName);
            canvas->Close();
            
            delete canvas;
            delete hist;
        }
    }
}


void plot_efficiency(TFile *inputFile)
{
    char histNumName[500];
    char histDenName[500];
    char histLabel[500];
    char title[500];
    char outFileName[500];
    
    std::vector <TH1F*> v_hist;
    std::vector <std::string> v_histLabel;
    
    
    double yMin = 0.6;
    double yMax = 1.0;
    
    for(int iStation = 0; iStation < nStation; iStation++)
    //for(int iStation = 1; iStation < 2; iStation++)
    {
        // DTTP efficiency vs. pT
        sprintf(title, "TwinMux trigger efficiency vs. p_{T, #mu} in Station %d", iStation+1);
        sprintf(outFileName, "plots/DTTP_efficiency_mu_pT_station%d.pdf", iStation+1);
        
        sprintf(histNumName, "dtdegm4D_withDTTP_mu_pT_station%d", iStation+1);
        sprintf(histDenName, "dtdegm4D_mu_pT_station%d", iStation+1);
        v_histLabel.push_back("DT");
        v_hist.push_back(getHistogramRatio( \
            inputFile, \
            histNumName, \
            histDenName));
        
        for(int iQual = 0; iQual < v_quality.size(); iQual++)
        {
            if(iStation == 1)
            {
                sprintf(histNumName, "%s/dtdegm4D_noDTTP_withMB1DTTP_withHOTP_mu_pT_station%d", v_quality.at(iQual).c_str(), iStation+1);
                //sprintf(histDenName, "dtdegm4D_noDTTP_mu_pT_station%d", iStation+1);
                sprintf(histLabel, "DT + HO (%s MB1)", v_quality.at(iQual).c_str());
                v_histLabel.push_back(histLabel);
                v_hist.push_back(getHistogramRatio( \
                    inputFile, \
                    histNumName, \
                    histDenName));
            }
        }
        
        plot(&v_hist, \
            &v_histLabel, \
            0, 200, \
            yMin, yMax, \
            title, \
            outFileName);
        
        
        v_hist.clear();
        v_histLabel.clear();
        
        
        // DTTP efficiency vs. eta
        sprintf(title, "TwinMux trigger efficiency vs. #eta_{#mu} in Station %d", iStation+1);
        sprintf(outFileName, "plots/DTTP_efficiency_mu_eta_station%d.pdf", iStation+1);
        
        sprintf(histNumName, "dtdegm4D_withDTTP_mu_eta_station%d", iStation+1);
        sprintf(histDenName, "dtdegm4D_mu_eta_station%d", iStation+1);
        v_histLabel.push_back("DT");
        v_hist.push_back(getHistogramRatio( \
            inputFile, \
            histNumName, \
            histDenName));
        
        for(int iQual = 0; iQual < v_quality.size(); iQual++)
        {
            if(iStation == 1)
            {
                sprintf(histNumName, "%s/dtdegm4D_noDTTP_withMB1DTTP_withHOTP_mu_eta_station%d", v_quality.at(iQual).c_str(), iStation+1);
                //sprintf(histDenName, "dtdegm4D_noDTTP_mu_eta_station%d", iStation+1);
                sprintf(histLabel, "DT + HO (%s MB1)", v_quality.at(iQual).c_str());
                v_histLabel.push_back(histLabel);
                v_hist.push_back(getHistogramRatio( \
                    inputFile, \
                    histNumName, \
                    histDenName));
            }
        }
        
        plot(&v_hist, \
            &v_histLabel, \
            -0.83, 0.83, \
            yMin, yMax, \
            title, \
            outFileName);
        
        
        v_hist.clear();
        v_histLabel.clear();
        
        
        // HO support for DTTP
        /*if(iStation == 1)
        {
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
                -0.83, 0.83, \
                title, \
                outFileName);
            
            v_hist.clear();
            v_histLabel.clear();
        }*/
        
        
        // BMTF efficiency vs. pT
        sprintf(title, "BMTF efficiency vs. p_{T, #mu} in Station %d", iStation+1);
        sprintf(outFileName, "plots/BMTF_efficiency_mu_pT_station%d.pdf", iStation+1);
        
        sprintf(histNumName, "dtdegm4D_withDTTP_withBMTF_mu_pT_station%d", iStation+1);
        sprintf(histDenName, "dtdegm4D_withDTTP_mu_pT_station%d", iStation+1);
        v_histLabel.push_back("BMTF");
        v_hist.push_back(getHistogramRatio( \
            inputFile, \
            histNumName, \
            histDenName));
        
        for(int iQual = 0; iQual < v_quality.size(); iQual++)
        {
            //if(iStation == 1)
            {
                sprintf(histNumName, "%s/dtdegm4D_noDTTP_noBMTF_withMB1DTTP_withHOTP_mu_pT_station%d", v_quality.at(iQual).c_str(), iStation+1);
                //sprintf(histDenName, "dtdegm4D_mu_pT_station%d", iStation+1);
                sprintf(histLabel, "BMTF + HO (%s MB1)", v_quality.at(iQual).c_str());
                v_histLabel.push_back(histLabel);
                v_hist.push_back(getHistogramRatio( \
                    inputFile, \
                    histNumName, \
                    histDenName));
            }
        }
        
        plot(&v_hist, \
            &v_histLabel, \
            0, 200, \
            yMin, yMax, \
            title, \
            outFileName);
        
        v_hist.clear();
        v_histLabel.clear();
        
        
        // BMTF efficiency vs. eta
        sprintf(title, "BMTF efficiency vs. #eta_{#mu} in Station %d", iStation+1);
        sprintf(outFileName, "plots/BMTF_efficiency_mu_eta_station%d.pdf", iStation+1);
        
        sprintf(histNumName, "dtdegm4D_withDTTP_withBMTF_mu_eta_station%d", iStation+1);
        sprintf(histDenName, "dtdegm4D_withDTTP_mu_eta_station%d", iStation+1);
        v_histLabel.push_back("BMTF");
        v_hist.push_back(getHistogramRatio( \
            inputFile, \
            histNumName, \
            histDenName));
        
        for(int iQual = 0; iQual < v_quality.size(); iQual++)
        {
            //if(iStation == 1)
            {
                sprintf(histNumName, "%s/dtdegm4D_noDTTP_noBMTF_withMB1DTTP_withHOTP_mu_eta_station%d", v_quality.at(iQual).c_str(), iStation+1);
                //sprintf(histDenName, "dtdegm4D_mu_eta_station%d", iStation+1);
                sprintf(histLabel, "BMTF + HO (%s MB1)", v_quality.at(iQual).c_str());
                v_histLabel.push_back(histLabel);
                v_hist.push_back(getHistogramRatio( \
                    inputFile, \
                    histNumName, \
                    histDenName));
            }
        }
        
        plot(&v_hist, \
            &v_histLabel, \
            -0.83, 0.83, \
            yMin, yMax, \
            title, \
            outFileName);
        
        v_hist.clear();
        v_histLabel.clear();
        
        
        // BMTF recovery potential
        /*sprintf(title, "BMTF recovery potential vs. #eta_{#mu} in Station %d", iStation+1);
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
            -0.83, 0.83, \
            yMin, yMax, \
            title, \
            outFileName);
        
        v_hist.clear();
        v_histLabel.clear();
        
        
        // HO support for BMTF
        if(iStation == 1)
        {
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
                -0.83, 0.83, \
                yMin, yMax, \
                title, \
                outFileName);
            
            v_hist.clear();
            v_histLabel.clear();
        }*/
    }
    
    
    //
    sprintf(title, "BMTF efficiency vs. #eta_{#mu}");
    sprintf(outFileName, "plots/BMTF_efficiency_mu_eta.pdf");
    
    sprintf(histNumName, "muon_withDTTP_withBMTF_mu_eta");
    sprintf(histDenName, "muon_withDTTP_mu_eta");
    v_histLabel.push_back("BMTF");
    v_hist.push_back(getHistogramRatio( \
        inputFile, \
        histNumName, \
        histDenName));
    
    for(int iQual = 0; iQual < v_quality.size(); iQual++)
    {
        sprintf(histNumName, "%s/muon_noBMTF_withMB1DTTP_withHOTP_mu_eta", v_quality.at(iQual).c_str());
        
        sprintf(histLabel, "BMTF + HO (%s MB1)", v_quality.at(iQual).c_str());
        v_histLabel.push_back(histLabel);
        v_hist.push_back(getHistogramRatio( \
            inputFile, \
            histNumName, \
            histDenName));
    }
    
    plot(&v_hist, \
        &v_histLabel, \
        -0.83, 0.83, \
        yMin, yMax, \
        title, \
        outFileName);
    
    v_hist.clear();
    v_histLabel.clear();
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
    double xMin, double xMax, \
    double yMin, double yMax, \
    const char *title, \
    const char *outFileName)
{
    TCanvas *canvas = new TCanvas("canvas", "canvas");
    canvas->SetCanvasSize(800, 800);
    
    //TLegend *legend = new TLegend(0.5, 0.12, 0.88, 0.35);
    TLegend *legend = new TLegend(0.65, 0.65, 0.88, 0.88);
    THStack *stack = new THStack();
    
    int nHist = v_hist->size();
    
    canvas->cd(1);
    
    for(int iHist = 0; iHist < nHist; iHist++)
    {
        int color = iHist+2;
        
        //v_hist->at(iHist)->SetLineWidth(2);
        v_hist->at(iHist)->SetLineWidth(0);
        v_hist->at(iHist)->SetLineColorAlpha(color, 0.5);
        v_hist->at(iHist)->SetFillColorAlpha(color, 0.5);
        
        if(v_label->size())
        {
            legend->AddEntry(v_hist->at(iHist), v_label->at(iHist).c_str());
        }
        
        stack->Add(v_hist->at(iHist), "hist");
        //stack->Add(v_hist->at(iHist), "E");
    }
    
    stack->SetTitle(title);
    
    //stack->Draw("nostack");
    stack->Draw();
    
    if(xMin < xMax)
    {
        stack->GetXaxis()->SetRangeUser(xMin, xMax);
    }
    
    if(yMin < yMax)
    {
        stack->SetMinimum(yMin);
        stack->SetMaximum(yMax);
    }
    
    if(v_label->size())
    {
        legend->Draw();
    }
    
    //canvas->SetLogy();
    
    canvas->SetGridx();
    canvas->SetGridy();
    
    canvas->SaveAs(outFileName);
    canvas->Close();
}
