void plot_DTTPefficiency()
{
    gStyle->SetOptStat(0);
    
    TCanvas *canvas = new TCanvas("canvas", "canvas", 800, 600);
    TLegend *legend = new TLegend(0.63, 0.105, 0.895, 0.37);
    
    TFile *_file0 = TFile::Open("output/MET_Run2017C-v1_RAW_DTTPefficiency/DTNtuple_all_efficiency.root");
    
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    TH1F *eff_eta_MB1 = (TH1F*) ((TH2F*) _file0->Get("dtsegm4D_withDTTP_mu_pT_vs_eta_station1"))->ProjectionX("_px", 0, 20);
    eff_eta_MB1->Divide((TH1F*) ((TH2F*) _file0->Get("dtsegm4D_mu_pT_vs_eta_station1"))->ProjectionX("_px", 0, 20));
    eff_eta_MB1->SetLineColor(1);
    eff_eta_MB1->SetLineWidth(2);
    eff_eta_MB1->Draw();
    legend->AddEntry(eff_eta_MB1, "MB1");
    
    eff_eta_MB1->SetMinimum(0);
    eff_eta_MB1->SetMaximum(1);
    eff_eta_MB1->GetXaxis()->SetRangeUser(-1, 1);
    eff_eta_MB1->GetXaxis()->SetTitle("#eta^{reco-#mu}");
    eff_eta_MB1->GetYaxis()->SetTitle("efficiency");
    eff_eta_MB1->SetTitle("DTTP efficiency vs. #eta^{reco-#mu} [0 < p^{reco-#mu}_{T} < 10 GeV]");

    TH1F *eff_eta_MB2 = (TH1F*) ((TH2F*) _file0->Get("dtsegm4D_withDTTP_mu_pT_vs_eta_station2"))->ProjectionX("_px", 0, 20);
    eff_eta_MB2->Divide((TH1F*) ((TH2F*) _file0->Get("dtsegm4D_mu_pT_vs_eta_station2"))->ProjectionX("_px", 0, 20));
    eff_eta_MB2->SetLineColor(2);
    eff_eta_MB2->SetLineWidth(2);
    eff_eta_MB2->Draw("sames");
    legend->AddEntry(eff_eta_MB2, "MB2");
    
    canvas->SetGridx(true);
    canvas->SetGridy(true);
    legend->Draw();
    
    canvas->SaveAs("plots/DTTPefficiency/DTTPefficiency_eta_mu0to10.pdf");
    canvas->Clear();
    legend->Clear();
    
    
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    eff_eta_MB1 = (TH1F*) ((TH2F*) _file0->Get("dtsegm4D_withDTTP_mu_pT_vs_eta_station1"))->ProjectionX("_px", 22, -1);
    eff_eta_MB1->Divide((TH1F*) ((TH2F*) _file0->Get("dtsegm4D_mu_pT_vs_eta_station1"))->ProjectionX("_px", 22, -1));
    eff_eta_MB1->SetLineColor(1);
    eff_eta_MB1->SetLineWidth(2);
    eff_eta_MB1->Draw();
    legend->AddEntry(eff_eta_MB1, "MB1");
    
    eff_eta_MB1->SetMinimum(0);
    eff_eta_MB1->SetMaximum(1);
    eff_eta_MB1->GetXaxis()->SetRangeUser(-1, 1);
    eff_eta_MB1->GetXaxis()->SetTitle("#eta^{reco-#mu}");
    eff_eta_MB1->GetYaxis()->SetTitle("efficiency");
    eff_eta_MB1->SetTitle("DTTP efficiency vs. #eta^{reco-#mu} [p^{reco-#mu}_{T} > 14 GeV]");

    eff_eta_MB2 = (TH1F*) ((TH2F*) _file0->Get("dtsegm4D_withDTTP_mu_pT_vs_eta_station2"))->ProjectionX("_px", 22, -1);
    eff_eta_MB2->Divide((TH1F*) ((TH2F*) _file0->Get("dtsegm4D_mu_pT_vs_eta_station2"))->ProjectionX("_px", 22, -1));
    eff_eta_MB2->SetLineColor(2);
    eff_eta_MB2->SetLineWidth(2);
    eff_eta_MB2->Draw("sames");
    legend->AddEntry(eff_eta_MB2, "MB2");
    
    canvas->SetGridx(true);
    canvas->SetGridy(true);
    legend->Draw();
    
    canvas->SaveAs("plots/DTTPefficiency/DTTPefficiency_eta_mu14.pdf");
    canvas->Clear();
    legend->Clear();
    
    
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    TH1F *eff_pT_MB1 = (TH1F*) _file0->Get("dtsegm4D_withDTTP_mu_pT_station1");
    eff_pT_MB1->Divide((TH1F*) _file0->Get("dtsegm4D_mu_pT_station1"));
    eff_pT_MB1->SetLineColor(1);
    eff_pT_MB1->SetLineWidth(2);
    eff_pT_MB1->Draw();
    legend->AddEntry(eff_pT_MB1, "MB1");
    
    eff_pT_MB1->SetMinimum(0);
    eff_pT_MB1->SetMaximum(1);
    eff_pT_MB1->GetXaxis()->SetRangeUser(0, 50);
    eff_pT_MB1->GetXaxis()->SetTitle("p^{reco-#mu}_{T}");
    eff_pT_MB1->GetYaxis()->SetTitle("efficiency");
    eff_pT_MB1->SetTitle("DTTP efficiency vs. p^{reco-#mu}_{T}");

    TH1F *eff_pT_MB2 = (TH1F*) _file0->Get("dtsegm4D_withDTTP_mu_pT_station2");
    eff_pT_MB2->Divide((TH1F*) _file0->Get("dtsegm4D_mu_pT_station2"));
    eff_pT_MB2->SetLineColor(2);
    eff_pT_MB2->SetLineWidth(2);
    eff_pT_MB2->Draw("sames");
    legend->AddEntry(eff_pT_MB2, "MB2");
    
    canvas->SetGridx(true);
    canvas->SetGridy(true);
    legend->Draw();
    
    canvas->SaveAs("plots/DTTPefficiency/DTTPefficiency_pT.pdf");
    canvas->Clear();
    legend->Clear();
    
    
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    for(int iSt = 0; iSt < 4; iSt++)
    {
        TH2F *eff_pT_vs_eta = (TH2F*) _file0->Get(("dtsegm4D_withDTTP_mu_pT_vs_eta_station" + std::to_string(iSt+1)).c_str());
        eff_pT_vs_eta->Divide((TH2F*) _file0->Get(("dtsegm4D_mu_pT_vs_eta_station" + std::to_string(iSt+1)).c_str()));
        eff_pT_vs_eta->SetLineColor(1);
        eff_pT_vs_eta->SetLineWidth(2);
        eff_pT_vs_eta->Draw();
        
        eff_pT_vs_eta->SetMinimum(0);
        eff_pT_vs_eta->SetMaximum(1);
        eff_pT_vs_eta->GetXaxis()->SetRangeUser(-1, 1);
        eff_pT_vs_eta->GetYaxis()->SetRangeUser(0, 50);
        eff_pT_vs_eta->GetXaxis()->SetTitle("#eta^{reco-#mu}");
        eff_pT_vs_eta->GetYaxis()->SetTitle("p^{reco-#mu}_{T}");
        
        eff_pT_vs_eta->Draw("colz");
        
        canvas->SaveAs(("plots/DTTPefficiency/DTTPefficiency_pT_vs_eta_MB" + std::to_string(iSt+1) + ".pdf").c_str());
        canvas->Clear();
        legend->Clear();
    }
    
    
    canvas->Close();
}
