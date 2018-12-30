void testMacro()
{
    gStyle->SetOptStat(0);
    gStyle->SetPaintTextFormat(".3f");
    
    
    TFile *inputFile1a = TFile::Open("output/SingleMuon_Run2017C-ZMu-PromptReco-v3_RAW-RECO_mu0_BMTF0/DTNtuple_all_efficiency.root", "READ");
    TFile *inputFile1b = TFile::Open("output/SingleMuon_Run2017C-ZMu-PromptReco-v3_RAW-RECO_mu18to32_BMTF0/DTNtuple_all_efficiency.root", "READ");
    TFile *inputFile2 = TFile::Open("output/ZeroBias1/DTNtuple_all_efficiency.root", "READ");
    TFile *inputFile3 = TFile::Open("output/ZeroBias1_mu0_BMTF0/DTNtuple_all_efficiency.root", "READ");
    
    
    TCanvas *canvas = new TCanvas("canvas");
    canvas->SetGridx();
    canvas->SetGridy();
    
    
    
    //////////////////////////////////////////////////
    
    TH2F *h2_hist1 = (TH2F*) inputFile1a->Get("MB34onlyBMTF_matchedMu_pT_vs_nearestMB3nearestHO_deltaIphi")->Clone();
    //TH2F *h2_hist1 = (TH2F*) inputFile1a->Get("MB34onlyBMTF_matchedMu_pT_vs_nearestMB4nearestHO_deltaIphi")->Clone();
    
    TH1F *h1_ratio = new TH1F("ratio", "ratio", 20, 0, 100);
    
    for(int iBinY = 2; iBinY <= 20; iBinY++)
    {
        double num =
            h2_hist1->GetBinContent(h2_hist1->GetXaxis()->FindBin(0.0), iBinY);
        
        double den = 0;
        
        for(int deltaIeta = -9; deltaIeta <= 9; deltaIeta++)
        {
            den += h2_hist1->GetBinContent(h2_hist1->GetXaxis()->FindBin((float) deltaIeta), iBinY);
        }
        
        if(den == 0)
        {
            continue;
        }
        
        double ratio = num/den;
        
        //printf("%d, %f, %f, %f, %f \n", iBinY,
        //    h2_hist1->GetBinContent(h2_hist1->GetXaxis()->FindBin(-1.0), iBinY),
        //    h2_hist1->GetBinContent(h2_hist1->GetXaxis()->FindBin(0.0), iBinY),
        //    h2_hist1->GetBinContent(h2_hist1->GetXaxis()->FindBin(1.0), iBinY),
        //    ratio);
        
        h1_ratio->SetBinContent(iBinY, ratio);
    }
    
    h1_ratio->GetYaxis()->SetRangeUser(0, 1);
    h1_ratio->Draw();
    
    canvas->SaveAs("plots/MB34trackPt/ratio_MB3.pdf");
    //canvas->SaveAs("plots/MB34trackPt/ratio_MB4.pdf");
    
    delete h1_ratio;
    canvas->Clear();
    
    
    
    //////////////////////////////////////////////////
    
    TH1F *h1_hist1 = (TH1F*) inputFile1a->Get("MB34onlyBMTF_pT")->Clone();
    
    h1_ratio = new TH1F("ratio", "ratio", 20, 0, 100);
    
    for(int iBinY = 2; iBinY <= 20; iBinY++)
    {
        double den = h1_hist1->GetBinContent(iBinY);
        
        if(den == 0)
        {
            continue;
        }
        
        double num =
            h2_hist1->GetBinContent(h2_hist1->GetXaxis()->FindBin(0.0), iBinY);
        
        double ratio = num/den;
        
        h1_ratio->SetBinContent(iBinY, ratio);
    }
    
    h1_ratio->GetYaxis()->SetRangeUser(0, 1);
    h1_ratio->Draw();
    
    canvas->SaveAs("plots/MB34trackPt/ratio_mod1_MB3.pdf");
    //canvas->SaveAs("plots/MB34trackPt/ratio_mod1_MB4.pdf");
    
    delete h1_ratio;
    canvas->Clear();
    
    
    
    //////////////////////////////////////////////////
    
    TH1F *h1_BMTF_muMatched_trackType = (TH1F*) inputFile1a->Get("BMTF_muMatched_trackType")->Clone();
    h1_BMTF_muMatched_trackType->Scale(1.0 / h1_BMTF_muMatched_trackType->GetBinContent(1));
    
    h1_BMTF_muMatched_trackType->Draw("hist text");
    
    canvas->SaveAs("plots/MB34trackPt/BMTF_muMatched_trackType_SingleMuon.pdf");
    
    canvas->Clear();
    
    
    
    //////////////////////////////////////////////////
    
    TH1F *h1_BMTF_trackType = (TH1F*) inputFile2->Get("BMTF_trackType")->Clone();
    h1_BMTF_trackType->Scale(1.0 / h1_BMTF_trackType->GetBinContent(1));
    
    h1_BMTF_trackType->Draw("hist text");
    
    canvas->SaveAs("plots/MB34trackPt/BMTF_muMatched_trackType_ZeroBias.pdf");
    
    canvas->Clear();
    
    
    
    //////////////////////////////////////////////////
    
    TH1F *h1_hist3 = (TH1F*) inputFile1a->Get("mu_eta")->Clone();
    TH1F *h1_hist4 = (TH1F*) inputFile1a->Get("BMTF_muMatched_eta")->Clone();
    TH1F *h1_hist5 = (TH1F*) inputFile1a->Get("BMTF_muMatched_MB34onlyMB3HO_eta")->Clone();
    
    h1_hist4->Divide(h1_hist3);
    h1_hist5->Divide(h1_hist3);
    
    h1_hist4->SetLineColor(kRed);
    h1_hist5->SetLineColor(kBlue);
    
    h1_hist4->GetYaxis()->SetRangeUser(0.5, 1);
    h1_hist5->GetYaxis()->SetRangeUser(0.5, 1);
    
    h1_hist4->Draw();
    h1_hist5->Draw("sames");
    
    canvas->SaveAs("plots/MB34trackPt/BMTF_efficiency_eta.pdf");
    
    canvas->Clear();
    
    
    
    //////////////////////////////////////////////////
    gStyle->SetOptTitle(0);
    
    TH1F *h1_mu_pT = (TH1F*) inputFile1b->Get("mu_pT")->Clone();
    TH2F *h2_BMTF_muMatched_pT_vs_trackType = (TH2F*) inputFile1b->Get("BMTF_muMatched_pT_vs_trackType")->Clone();
    
    TH1F *h1_BMTF_muMatched_pT = (TH1F*) h2_BMTF_muMatched_pT_vs_trackType->ProjectionY("BMTF_muMatched_pT", 1, 2);
    h1_BMTF_muMatched_pT->SetTitle("BMTF_pT");
    
    TH1F *h1_BMTF_MB12_muMatched_pT = (TH1F*) h2_BMTF_muMatched_pT_vs_trackType->ProjectionY("BMTF_MB12_muMatched_pT", 4, 4);
    h1_BMTF_MB12_muMatched_pT->SetTitle("BMTF_MB12_pT");
    
    TH1F *h1_BMTF_MB34_muMatched_pT = (TH1F*) h2_BMTF_muMatched_pT_vs_trackType->ProjectionY("BMTF_MB34_muMatched_pT", 13, 13);
    h1_BMTF_MB34_muMatched_pT->SetTitle("BMTF_MB34_pT");
    
    TH1F *h1_BMTF_MB34_muMatched_MB3HO_pT = (TH1F*) h2_BMTF_muMatched_pT_vs_trackType->ProjectionY("BMTF_MB34_muMatched_MB3HO_pT", 20, 20);
    h1_BMTF_MB34_muMatched_MB3HO_pT->SetTitle("BMTF_MB34_MB3HO_pT");
    
    TH1F *h1_BMTF_MB34_muMatched_noHO_pT = (TH1F*) h2_BMTF_muMatched_pT_vs_trackType->ProjectionY("BMTF_MB34_muMatched_noHO_pT", 23, 23);
    h1_BMTF_MB34_muMatched_noHO_pT->SetTitle("BMTF_MB34_noHO_pT");
    
    TH1F *h1_BMTF_MB1234_muMatched_pT = (TH1F*) h2_BMTF_muMatched_pT_vs_trackType->ProjectionY("BMTF_MB1234_muMatched_pT", 16, 16);
    h1_BMTF_MB1234_muMatched_pT->SetTitle("BMTF_MB1234_pT");
    
    h1_BMTF_MB34_muMatched_MB3HO_pT->Add(h1_BMTF_MB34_muMatched_noHO_pT);
    
    h1_BMTF_muMatched_pT->Divide(h1_mu_pT);
    h1_BMTF_MB12_muMatched_pT->Divide(h1_mu_pT);
    h1_BMTF_MB34_muMatched_pT->Divide(h1_mu_pT);
    h1_BMTF_MB34_muMatched_MB3HO_pT->Divide(h1_mu_pT);
    h1_BMTF_MB1234_muMatched_pT->Divide(h1_mu_pT);
    
    h1_BMTF_muMatched_pT->SetLineColor(kBlack);
    h1_BMTF_MB12_muMatched_pT->SetLineColor(kRed);
    h1_BMTF_MB34_muMatched_pT->SetLineColor(kBlue);
    h1_BMTF_MB34_muMatched_MB3HO_pT->SetLineColor(kBlue);
    h1_BMTF_MB1234_muMatched_pT->SetLineColor(kGreen);
    
    h1_BMTF_MB34_muMatched_MB3HO_pT->SetLineStyle(2);
    
    h1_BMTF_muMatched_pT->GetYaxis()->SetRangeUser(0, 1);
    h1_BMTF_muMatched_pT->GetXaxis()->SetRangeUser(15, 40);
    
    h1_BMTF_muMatched_pT->Draw();
    h1_BMTF_MB12_muMatched_pT->Draw("sames");
    h1_BMTF_MB34_muMatched_pT->Draw("sames");
    h1_BMTF_MB34_muMatched_MB3HO_pT->Draw("sames");
    h1_BMTF_MB1234_muMatched_pT->Draw("sames");
    
    canvas->BuildLegend();
    
    canvas->SaveAs("plots/MB34trackPt/BMTF_trackType_efficiency_pT.pdf");
    
    canvas->Clear();
    
    //delete h1_mu_pT;
    //delete h2_BMTF_muMatched_pT_vs_trackType;
    //delete h1_BMTF_muMatched_pT;
    //delete h1_BMTF_MB12_muMatched_pT;
    //delete h1_BMTF_MB34_muMatched_pT;
    //delete h1_BMTF_MB1234_muMatched_pT;
    
    
    
    //////////////////////////////////////////////////
    gStyle->SetOptTitle(0);
    
    TH2F *h2_BMTF_pT_resolution_vs_trackType = (TH2F*) inputFile1b->Get("BMTF_pT_resolution_vs_trackType")->Clone();
    
    TH1F *h1_BMTF_pT_resolution = (TH1F*) h2_BMTF_pT_resolution_vs_trackType->ProjectionY("BMTF_pT_resolution", 1, 2);
    h1_BMTF_pT_resolution->SetTitle("BMTF");
    
    TH1F *h1_BMTF_MB12_pT_resolution = (TH1F*) h2_BMTF_pT_resolution_vs_trackType->ProjectionY("BMTF_MB12_pT_resolution", 4, 4);
    h1_BMTF_MB12_pT_resolution->SetTitle("BMTF_MB12");
    
    TH1F *h1_BMTF_MB34_pT_resolution = (TH1F*) h2_BMTF_pT_resolution_vs_trackType->ProjectionY("BMTF_MB34_pT_resolution", 13, 13);
    h1_BMTF_MB34_pT_resolution->SetTitle("BMTF_MB34");
    
    TH1F *h1_BMTF_MB34_MB3HO_pT_resolution = (TH1F*) h2_BMTF_pT_resolution_vs_trackType->ProjectionY("BMTF_MB34_MB3HO_pT_resolution", 20, 20);
    h1_BMTF_MB34_MB3HO_pT_resolution->SetTitle("BMTF_MB34_MB3HO");
    
    TH1F *h1_BMTF_MB34_noHO_pT_resolution = (TH1F*) h2_BMTF_pT_resolution_vs_trackType->ProjectionY("BMTF_MB34_noHO_pT_resolution", 23, 23);
    h1_BMTF_MB34_noHO_pT_resolution->SetTitle("BMTF_MB34_noHO");
    
    TH1F *h1_BMTF_MB1234_pT_resolution = (TH1F*) h2_BMTF_pT_resolution_vs_trackType->ProjectionY("BMTF_MB1234_pT_resolution", 16, 16);
    h1_BMTF_MB1234_pT_resolution->SetTitle("BMTF_MB1234");
    
    h1_BMTF_MB34_MB3HO_pT_resolution->Add(h1_BMTF_MB34_noHO_pT_resolution);
    
    int nBin = h1_BMTF_pT_resolution->GetNbinsX();
    
    h1_BMTF_pT_resolution->AddBinContent(nBin, h1_BMTF_pT_resolution->GetBinContent(nBin+1));
    h1_BMTF_MB12_pT_resolution->AddBinContent(nBin, h1_BMTF_MB12_pT_resolution->GetBinContent(nBin+1));
    h1_BMTF_MB34_pT_resolution->AddBinContent(nBin, h1_BMTF_MB34_pT_resolution->GetBinContent(nBin+1));
    h1_BMTF_MB34_MB3HO_pT_resolution->AddBinContent(nBin, h1_BMTF_MB34_MB3HO_pT_resolution->GetBinContent(nBin+1));
    h1_BMTF_MB1234_pT_resolution->AddBinContent(nBin, h1_BMTF_MB1234_pT_resolution->GetBinContent(nBin+1));
    
    h1_BMTF_pT_resolution->Scale(1.0 / h1_BMTF_pT_resolution->GetEntries());
    h1_BMTF_MB12_pT_resolution->Scale(1.0 / h1_BMTF_MB12_pT_resolution->GetEntries());
    h1_BMTF_MB34_pT_resolution->Scale(1.0 / h1_BMTF_MB34_pT_resolution->GetEntries());
    h1_BMTF_MB34_MB3HO_pT_resolution->Scale(1.0 / h1_BMTF_MB34_MB3HO_pT_resolution->GetEntries());
    h1_BMTF_MB1234_pT_resolution->Scale(1.0 / h1_BMTF_MB1234_pT_resolution->GetEntries());
    
    h1_BMTF_pT_resolution->SetLineColor(kBlack);
    h1_BMTF_MB12_pT_resolution->SetLineColor(kRed);
    h1_BMTF_MB34_pT_resolution->SetLineColor(kBlue);
    h1_BMTF_MB34_MB3HO_pT_resolution->SetLineColor(kBlue);
    h1_BMTF_MB1234_pT_resolution->SetLineColor(kGreen);
    
    h1_BMTF_MB34_MB3HO_pT_resolution->SetLineStyle(2);
    
    h1_BMTF_pT_resolution->GetYaxis()->SetRangeUser(0, 0.3);
    //h1_BMTF_pT_resolution->GetXaxis()->SetRangeUser(0, 5);
    
    h1_BMTF_pT_resolution->Draw();
    h1_BMTF_MB12_pT_resolution->Draw("sames");
    h1_BMTF_MB34_pT_resolution->Draw("sames");
    h1_BMTF_MB34_MB3HO_pT_resolution->Draw("sames");
    h1_BMTF_MB1234_pT_resolution->Draw("sames");
    
    canvas->BuildLegend();
    
    canvas->SaveAs("plots/MB34trackPt/BMTF_pT_resolution.pdf");
    
    canvas->Clear();
    
    //delete h2_BMTF_pT_resolution_vs_trackType;
    //delete h1_BMTF_pT_resolution;
    //delete h1_BMTF_MB12_pT_resolution;
    //delete h1_BMTF_MB34_pT_resolution;
    //delete h1_BMTF_MB1234_pT_resolution;
    
    
    
    //////////////////////////////////////////////////
    gStyle->SetOptTitle(0);
    
    h2_BMTF_muMatched_pT_vs_trackType = (TH2F*) inputFile1a->Get("BMTF_muMatched_pT_vs_trackType")->Clone();
    
    h1_BMTF_muMatched_pT = (TH1F*) h2_BMTF_muMatched_pT_vs_trackType->ProjectionY("BMTF_muMatched_pT", 1, 2);
    h1_BMTF_muMatched_pT->SetTitle("BMTF_muMatched_pT");
    
    h1_BMTF_MB12_muMatched_pT = (TH1F*) h2_BMTF_muMatched_pT_vs_trackType->ProjectionY("BMTF_MB12_muMatched_pT", 4, 4);
    h1_BMTF_MB12_muMatched_pT->SetTitle("BMTF_MB12_muMatched_pT");
    
    h1_BMTF_MB34_muMatched_pT = (TH1F*) h2_BMTF_muMatched_pT_vs_trackType->ProjectionY("BMTF_MB34_muMatched_pT", 13, 13);
    h1_BMTF_MB34_muMatched_pT->SetTitle("BMTF_MB34_muMatched_pT");
    
    h1_BMTF_MB1234_muMatched_pT = (TH1F*) h2_BMTF_muMatched_pT_vs_trackType->ProjectionY("BMTF_MB1234_muMatched_pT", 16, 16);
    h1_BMTF_MB1234_muMatched_pT->SetTitle("BMTF_MB1234_muMatched_pT");
    
    h1_BMTF_muMatched_pT = (TH1F*) h1_BMTF_muMatched_pT->GetCumulative(false);
    h1_BMTF_MB12_muMatched_pT = (TH1F*) h1_BMTF_MB12_muMatched_pT->GetCumulative(false);
    h1_BMTF_MB34_muMatched_pT = (TH1F*) h1_BMTF_MB34_muMatched_pT->GetCumulative(false);
    h1_BMTF_MB1234_muMatched_pT = (TH1F*) h1_BMTF_MB1234_muMatched_pT->GetCumulative(false);
    
    h1_BMTF_muMatched_pT->SetLineColor(kBlack);
    h1_BMTF_MB12_muMatched_pT->SetLineColor(kRed);
    h1_BMTF_MB34_muMatched_pT->SetLineColor(kBlue);
    h1_BMTF_MB1234_muMatched_pT->SetLineColor(kGreen);
    
    h1_BMTF_muMatched_pT->GetYaxis()->SetRangeUser(10, pow(10, 7));
    h1_BMTF_muMatched_pT->GetXaxis()->SetRangeUser(0, 500);
    
    h1_BMTF_muMatched_pT->Draw();
    h1_BMTF_MB12_muMatched_pT->Draw("sames");
    h1_BMTF_MB34_muMatched_pT->Draw("sames");
    h1_BMTF_MB1234_muMatched_pT->Draw("sames");
    
    canvas->BuildLegend();
    canvas->SetLogy();
    
    canvas->SaveAs("plots/MB34trackPt/BMTF_muMatched_pT_cumulative_SingleMuon.pdf");
    
    canvas->Clear();
    
    
    //////////////////////////////////////////////////
    gStyle->SetOptTitle(0);
    
    TH2F *h2_BMTF_pT_vs_trackType = (TH2F*) inputFile3->Get("BMTF_pT_vs_trackType")->Clone();
    
    TH1F *h1_BMTF_pT = (TH1F*) h2_BMTF_pT_vs_trackType->ProjectionY("BMTF_pT", 1, 2);
    h1_BMTF_pT->SetTitle("BMTF_pT");
    
    TH1F *h1_BMTF_MB12_pT = (TH1F*) h2_BMTF_pT_vs_trackType->ProjectionY("BMTF_MB12_pT", 4, 4);
    h1_BMTF_MB12_pT->SetTitle("BMTF_MB12_pT");
    
    TH1F *h1_BMTF_MB34_pT = (TH1F*) h2_BMTF_pT_vs_trackType->ProjectionY("BMTF_MB34_pT", 13, 13);
    h1_BMTF_MB34_pT->SetTitle("BMTF_MB34_pT");
    
    TH1F *h1_BMTF_MB34_MB3HO_pT = (TH1F*) h2_BMTF_pT_vs_trackType->ProjectionY("BMTF_MB34_MB3HO_pT", 20, 20);
    h1_BMTF_MB34_MB3HO_pT->SetTitle("BMTF_MB34_MB3HO_pT");
    
    TH1F *h1_BMTF_MB34_noHO_pT = (TH1F*) h2_BMTF_pT_vs_trackType->ProjectionY("BMTF_MB34_noHO_pT", 23, 23);
    h1_BMTF_MB34_noHO_pT->SetTitle("BMTF_MB34_noHO_pT");
    
    TH1F *h1_BMTF_MB1234_pT = (TH1F*) h2_BMTF_pT_vs_trackType->ProjectionY("BMTF_MB1234_pT", 16, 16);
    h1_BMTF_MB1234_pT->SetTitle("BMTF_MB1234_pT");
    
    h1_BMTF_MB34_MB3HO_pT->Add(h1_BMTF_MB34_noHO_pT);
    
    h1_BMTF_pT = (TH1F*) h1_BMTF_pT->GetCumulative(false);
    h1_BMTF_MB12_pT = (TH1F*) h1_BMTF_MB12_pT->GetCumulative(false);
    h1_BMTF_MB34_pT = (TH1F*) h1_BMTF_MB34_pT->GetCumulative(false);
    h1_BMTF_MB34_MB3HO_pT = (TH1F*) h1_BMTF_MB34_MB3HO_pT->GetCumulative(false);
    h1_BMTF_MB1234_pT = (TH1F*) h1_BMTF_MB1234_pT->GetCumulative(false);
    
    h1_BMTF_pT->SetLineColor(kBlack);
    h1_BMTF_MB12_pT->SetLineColor(kRed);
    h1_BMTF_MB34_pT->SetLineColor(kBlue);
    h1_BMTF_MB34_MB3HO_pT->SetLineColor(kBlue);
    h1_BMTF_MB1234_pT->SetLineColor(kGreen);
    
    h1_BMTF_MB34_MB3HO_pT->SetLineStyle(2);
    
    h1_BMTF_pT->GetYaxis()->SetRangeUser(10, pow(10, 5));
    h1_BMTF_pT->GetXaxis()->SetRangeUser(0, 50);
    
    h1_BMTF_pT->Draw();
    h1_BMTF_MB12_pT->Draw("sames");
    h1_BMTF_MB34_pT->Draw("sames");
    h1_BMTF_MB34_MB3HO_pT->Draw("sames");
    h1_BMTF_MB1234_pT->Draw("sames");
    
    canvas->BuildLegend();
    canvas->SetLogy();
    
    canvas->SaveAs("plots/MB34trackPt/BMTF_pT_cumulative_ZeroBias.pdf");
    
    canvas->Clear();
    
    
    
    gStyle->SetOptTitle(1);
    
    canvas->Close();
}
