# include <iostream>
# include <iterator>
# include <fstream>
# include <map>
# include <sstream> 
# include <string>
# include <utility>
# include <vector>

# include <CLHEP/Vector/ThreeVector.h>
# include <CLHEP/Vector/LorentzVector.h>

# include <TFile.h>
# include <TH1F.h>
# include <TH2F.h>
# include <TTree.h>

# include "InputData_DTNtuple.h"
# include "Common.h"


int str_len = 500;

int nWheel = 5;
int nStation = 4;
int nSector = 12;

std::string muonWP = "medium";
//std::string muonWP = "tight";

double mu_pTcut = 0; // GeV
double mu_pTcutUpr = 0; // GeV
double mu_etaCut = 0.83;

double BMTF_pTcut = 0; // GeV
double BMTF_etaCut = 0.83;

double MB1_pTcut = mu_pTcut; // GeV

double DTTP_BMTF_deltaPhiCut = 0.4;

int isoMB1HO_3x3_cut = 1;
bool isoMB1HO_3x3_placeCut = false;

int DTsegment_nHit_phiLocal_min = 4;
int DTsegment_phiLocal_max = 45; // degree

int HOTP_bits_SOI = 4;

int MB1_HO_deltaIphiCut = 1;
int MB2_HO_deltaIphiCut = 2;

double muBMTF_deltaRcut = 0.4;
double muMB1_deltaRcut = 0.4;
double muMB1_deltaEtaCut = 1.5 * 2.0*M_PI/72.0;
double muMB1_deltaPhiCut = 1.5 * 2.0*M_PI/72.0;

double MB34onlyBMTF_HO_deltaRcut = 0.4;

std::vector <int> v_phiB_MB1;
std::vector <double> v_pT_MB1;

std::vector <int> v_phiB_MB2;
std::vector <double> v_pT_MB2;

//std::vector <int> v_BMTF_stationMask(15, 0.0);
//std::vector <TH1F*> v_h1_BMTF_pT;
//std::vector <TH1F*> v_h1_BMTF_eta;


class MBTP_info
{
    public:
    
    int index = -1;
    int station = -1;
    int wheel = 9999;
    
    double deltaPhi = 9999;
    double phiB = 9999;
    double phiLocal = 9999;
};


class OutputData
{
    public:
    
    //
    TH1F *h1_mu_n;
    TH1F *h1_mu_pT;
    TH1F *h1_mu_eta;
    TH1F *h1_mu_phi;
    
    TH2F *h2_mu_eta_vs_phi;
    TH2F *h2_mu_pT_vs_eta;
    TH2F *h2_mu_pT_vs_phi;
    TH2F *h2_mu_pT_vs_MB1extDeltaPhi;
    TH2F *h2_mu_pT_vs_MB1extDeltaEta;
    
    TH1F *h1_usedMu_pT;
    TH1F *h1_usedMu_eta;
    TH1F *h1_usedMu_phi;
    
    TH2F *h2_usedMu_pT_vs_eta;
    TH2F *h2_usedMu_pT_vs_stationMask;
    TH2F *h2_usedMu_eta_vs_stationMask;
    TH2F *h2_usedMu_DTTP_pT_vs_deltaPhi;
    
    TH2F *h2_usedMB12mu_MB2phiB_vs_MB1phiB;
    TH2F *h2_usedMB12mu_wh0_MB2phiB_vs_MB1phiB;
    TH2F *h2_usedMB12mu_wh1_MB2phiB_vs_MB1phiB;
    
    TH2F *h2_usedMB12mu_wh0_pT_vs_MB1phiB;
    TH2F *h2_usedMB12mu_wh1_pT_vs_MB1phiB;
    
    //
    TH1F *h1_unusedMu_pT;
    TH1F *h1_unusedMu_eta;
    TH1F *h1_unusedMu_phi;
    TH1F *h1_unusedMu_nearestDTTP_station;
    TH1F *h1_unusedMu_nDTTP;
    
    TH1F *h1_unusedMu_stationMask;
    
    TH2F *h2_nUnusedMu_vs_nDTTP;
    TH2F *h2_unusedMu_pT_vs_eta;
    TH2F *h2_unusedMu_eta_vs_phi;
    TH2F *h2_unusedMu_pT_vs_stationMask;
    TH2F *h2_unusedMu_eta_vs_stationMask;
    TH2F *h2_unusedMu_phi_vs_stationMask;
    TH2F *h2_unusedMu_DTTP_pT_vs_deltaPhi;
    
    TH2F *h2_unusedMuHO_pT_vs_eta;
    TH2F *h2_unusedMuHO_eta_vs_phi;
    TH2F *h2_unusedMuHO_pT_vs_stationMask;
    TH2F *h2_unusedMuHO_eta_vs_stationMask;
    TH2F *h2_unusedMuHO_phi_vs_stationMask;
    
    TH1F *h1_unusedMB1mu_wh0_phiB;
    TH1F *h1_unusedMB1mu_wh1_phiB;
    
    TH1F *h1_unusedMB2mu_wh0_phiB;
    TH1F *h1_unusedMB2mu_wh1_phiB;
    
    TH2F *h2_unusedMB12mu_MB2phiB_vs_MB1phiB;
    TH2F *h2_unusedMB12mu_wh0_MB2phiB_vs_MB1phiB;
    TH2F *h2_unusedMB12mu_wh1_MB2phiB_vs_MB1phiB;
    
    TH1F *h1_unusedMB1mu_wh0_psi;
    TH1F *h1_unusedMB1mu_wh1_psi;
    
    TH1F *h1_unusedMB2mu_wh0_psi;
    TH1F *h1_unusedMB2mu_wh1_psi;
    
    TH2F *h2_unusedMB12mu_MB2psi_vs_MB1psi;
    TH2F *h2_unusedMB12mu_wh0_MB2psi_vs_MB1psi;
    TH2F *h2_unusedMB12mu_wh1_MB2psi_vs_MB1psi;
    
    TH2F *h2_unusedMB2mu_pT_vs_eta;
    TH2F *h2_unusedMB2mu_eta_vs_phi;
    
    TH2F *h2_unusedMB1muHO_pT_vs_deltaR;
    TH2F *h2_unusedMB1muHO_pT_vs_deltaIphi;
    
    TH2F *h2_unusedMB2muHO_pT_vs_deltaR;
    TH2F *h2_unusedMB2muHO_pT_vs_deltaIphi;
    
    //
    TH1F *h1_BMTF_MB1_deltaPhi;
    TH1F *h1_BMTF_MB2_deltaPhi;
    TH1F *h1_BMTF_MB3_deltaPhi;
    TH1F *h1_BMTF_MB4_deltaPhi;
    
    TH2F *h2_BMTF_MB1_deltaPhi_vs_trackType;
    TH2F *h2_BMTF_MB2_deltaPhi_vs_trackType;
    TH2F *h2_BMTF_MB3_deltaPhi_vs_trackType;
    TH2F *h2_BMTF_MB4_deltaPhi_vs_trackType;
    
    TH1F *h1_BMTF_mu_deltaPt;
    
    TH1F *h1_BMTF_mu_deltaEta;
    TH1F *h1_BMTF_mu_deltaPhi;
    TH1F *h1_BMTF_mu_deltaR;
    
    TH2F *h2_BMTF_mu_pT_vs_deltaR;
    
    TH1F *h1_BMTF_muMatched_pT;
    TH1F *h1_BMTF_muMatched_eta;
    TH1F *h1_BMTF_muMatched_phi;
    
    TH1F *h1_BMTF_muMatched_deltaEta;
    TH1F *h1_BMTF_muMatched_deltaPhi;
    
    TH1F *h1_BMTF_trackType;
    TH1F *h1_BMTF_muMatched_trackType;
    
    TH2F *h2_BMTF_muMatched_eta_vs_phi;
    TH2F *h2_BMTF_muMatched_pT_vs_eta;
    TH2F *h2_BMTF_muMatched_pT_vs_phi;
    TH2F *h2_BMTF_muMatched_pT_vs_trackType;
    
    TH2F *h2_BMTF_pT_resolution_vs_trackType;
    
    TH1F *h1_BMTF_muMatched_MB34onlyMB3HO_pT;
    TH1F *h1_BMTF_muMatched_MB34onlyMB3HO_eta;
    
    TH2F *h2_BMTF_muMatched_MB34onlyMB3HO_pT_vs_eta;
    
    
    //
    TH1F *h1_BMTF_muNotMatched_pT;
    TH1F *h1_BMTF_muNotMatched_eta;
    TH1F *h1_BMTF_muNotMatched_phi;
    
    TH2F *h2_BMTF_muNotMatched_eta_vs_phi;
    TH2F *h2_BMTF_muNotMatched_pT_vs_eta;
    TH2F *h2_BMTF_muNotMatched_pT_vs_phi;
    
    
    //
    TH1F *h1_MB1_BMTF_deltaPhi;
    
    
    //
    TH1F *h1_MB1_isoType;
    
    
    //
    TH2F *h2_MB_station_vs_wheel;
    TH2F *h2_usedMB_station_vs_wheel;
    TH2F *h2_unusedMB_station_vs_wheel;
    
    
    //
    TH1F *h1_isoMB1HO_deltaIphi;
    
    TH1F *h1_isoMB1HO_mu_deltaPt;
    TH2F *h2_isoMB1HO_mu_pT_vs_deltaR;
    
    TH1F *h1_isoMB1HO_muMatched_pT;
    TH1F *h1_isoMB1HO_muMatched_eta;
    TH1F *h1_isoMB1HO_muMatched_phi;
    
    TH1F *h1_isoMB1HO_muMatched_3x3;
    
    TH2F *h2_isoMB1HO_muMatched_eta_vs_phi;
    TH2F *h2_isoMB1HO_muMatched_pT_vs_eta;
    TH2F *h2_isoMB1HO_muMatched_pT_vs_phi;
    
    TH2F *h2_isoMB1HO_muMatched_pT_vs_deltaIphi;
    
    
    //
    TH1F *h1_isoMB1HO_muNotMatched_pT;
    TH1F *h1_isoMB1HO_muNotMatched_eta;
    TH1F *h1_isoMB1HO_muNotMatched_phi;
    
    TH1F *h1_isoMB1HO_muNotMatched_3x3;
    
    TH2F *h2_isoMB1HO_muNotMatched_eta_vs_phi;
    TH2F *h2_isoMB1HO_muNotMatched_pT_vs_eta;
    TH2F *h2_isoMB1HO_muNotMatched_pT_vs_phi;
    
    TH2F *h2_isoMB1HO_nNotMuMatched_vs_nUnusedMu;
    
    
    //
    TH1F *h1_MB34onlyBMTF_pT;
    TH1F *h1_MB34onlyBMTF_eta;
    TH1F *h1_MB34onlyBMTF_nearestHO_iEta;
    TH1F *h1_MB34onlyBMTF_nearestHO_deltaR;
    TH1F *h1_MB34onlyBMTFHO_pT;
    TH1F *h1_MB34onlyBMTFHO_eta;
    
    TH2F *h2_MB34onlyBMTF_nearestMB3_wh_vs_nearestHO_iEta;
    TH2F *h2_MB34onlyBMTF_nearestMB4_wh_vs_nearestHO_iEta;
    
    TH2F *h2_MB34onlyBMTF_matchedMu_pT_vs_nearestMB3nearestHO_deltaIphi;
    TH2F *h2_MB34onlyBMTF_matchedMu_pT_vs_nearestMB4nearestHO_deltaIphi;
    
    TH2F *h2_MB34onlyBMTF_matchedMu_ch_vs_nearestMB3nearestHO_deltaIphi;
    TH2F *h2_MB34onlyBMTF_matchedMu_ch_vs_nearestMB4nearestHO_deltaIphi;
    
    
    //
    TH1F *h1_test1;
    TH1F *h1_test1a;
    
    TH1F *h1_test2;
    TH1F *h1_test2a;
    
    TH1F *h1_test3;
    TH1F *h1_test3a;
    
    
    OutputData()
    {
        char histName[str_len];
        char histTitle[str_len];
        
        double pT_min = 0;
        double pT_max = 1000;
        int nBin_pT = 2000;
        
        double eta_min = -3;
        double eta_max = 3;
        int nBin_eta = 68;
        //int nBin_eta = 136;
        
        double phi_min = -M_PI;
        double phi_max = M_PI;
        int nBin_phi = 72;
        
        double deltaR_min = 0;
        double deltaR_max = 3;
        int nBin_deltaR = 120;
        
        //
        h1_mu_n = new TH1F("mu_n", "mu_n", 10, 0, 10);
        h1_mu_pT = new TH1F("mu_pT", "mu_pT", nBin_pT, pT_min, pT_max);
        h1_mu_eta = new TH1F("mu_eta", "mu_eta", nBin_eta, eta_min, eta_max);
        h1_mu_phi = new TH1F("mu_phi", "mu_phi", nBin_phi, phi_min, phi_max);
        
        h2_mu_eta_vs_phi = new TH2F("mu_eta_vs_phi", "mu_eta_vs_phi", nBin_phi, phi_min, phi_max, nBin_eta, eta_min, eta_max);
        h2_mu_pT_vs_eta = new TH2F("mu_pT_vs_eta", "mu_pT_vs_eta", nBin_eta, eta_min, eta_max, nBin_pT, pT_min, pT_max);
        h2_mu_pT_vs_phi = new TH2F("mu_pT_vs_phi", "mu_pT_vs_phi", nBin_phi, phi_min, phi_max, nBin_pT, pT_min, pT_max);
        
        h2_mu_pT_vs_MB1extDeltaEta = new TH2F("mu_pT_vs_MB1extDeltaEta", "mu_pT_vs_MB1extDeltaEta", 2*nBin_eta, eta_min, eta_max, nBin_pT, pT_min, pT_max);
        h2_mu_pT_vs_MB1extDeltaPhi = new TH2F("mu_pT_vs_MB1extDeltaPhi", "mu_pT_vs_MB1extDeltaPhi", 2*nBin_phi, phi_min, phi_max, nBin_pT, pT_min, pT_max);
        
        h1_usedMu_pT = new TH1F("usedMu_pT", "usedMu_pT", nBin_pT, pT_min, pT_max);
        h1_usedMu_eta = new TH1F("usedMu_eta", "usedMu_eta", nBin_eta, eta_min, eta_max);
        h1_usedMu_phi = new TH1F("usedMu_phi", "usedMu_phi", nBin_phi, phi_min, phi_max);
        
        h2_usedMu_pT_vs_eta = new TH2F("usedMu_pT_vs_eta", "usedMu_pT_vs_eta", nBin_eta, eta_min, eta_max, nBin_pT, pT_min, pT_max);
        h2_usedMu_pT_vs_stationMask = new TH2F("usedMu_pT_vs_stationMask", "usedMu_pT_vs_stationMask", 25, 0, 25, nBin_pT, pT_min, pT_max);
        h2_usedMu_eta_vs_stationMask = new TH2F("usedMu_eta_vs_stationMask", "usedMu_eta_vs_stationMask", 25, 0, 25, nBin_eta, eta_min, eta_max);
        h2_usedMu_DTTP_pT_vs_deltaPhi = new TH2F("usedMu_DTTP_pT_vs_deltaPhi", "usedMu_DTTP_pT_vs_deltaPhi", 2*nBin_phi, phi_min, phi_max, 200, 0, 1000);
        
        h2_usedMB12mu_MB2phiB_vs_MB1phiB = new TH2F("usedMB12mu_MB2phiB_vs_MB1phiB", "usedMB12mu_MB2phiB_vs_MB1phiB", nBin_phi, phi_min, phi_max, nBin_phi, phi_min, phi_max);
        h2_usedMB12mu_wh0_MB2phiB_vs_MB1phiB = new TH2F("usedMB12mu_wh0_MB2phiB_vs_MB1phiB", "usedMB12mu_wh0_MB2phiB_vs_MB1phiB", nBin_phi, phi_min, phi_max, nBin_phi, phi_min, phi_max);
        h2_usedMB12mu_wh1_MB2phiB_vs_MB1phiB = new TH2F("usedMB12mu_wh1_MB2phiB_vs_MB1phiB", "usedMB12mu_wh1_MB2phiB_vs_MB1phiB", nBin_phi, phi_min, phi_max, nBin_phi, phi_min, phi_max);
        
        h2_usedMB12mu_wh0_pT_vs_MB1phiB = new TH2F("usedMB12mu_wh0_pT_vs_MB1phiB", "usedMB12mu_wh0_pT_vs_MB1phiB", nBin_phi, phi_min, phi_max, nBin_pT, pT_min, pT_max);
        h2_usedMB12mu_wh1_pT_vs_MB1phiB = new TH2F("usedMB12mu_wh1_pT_vs_MB1phiB", "usedMB12mu_wh1_pT_vs_MB1phiB", nBin_phi, phi_min, phi_max, nBin_pT, pT_min, pT_max);
        
        
        //
        h1_unusedMu_pT = new TH1F("unusedMu_pT", "unusedMu_pT", nBin_pT, pT_min, pT_max);
        h1_unusedMu_eta = new TH1F("unusedMu_eta", "unusedMu_eta", nBin_eta, eta_min, eta_max);
        h1_unusedMu_phi = new TH1F("unusedMu_phi", "unusedMu_phi", nBin_phi, phi_min, phi_max);
        
        h1_unusedMu_nearestDTTP_station = new TH1F("unusedMu_nearestDTTP_station", "unusedMu_nearestDTTP_station", 10, 0, 10);
        h1_unusedMu_nDTTP = new TH1F("unusedMu_nDTTP", "unusedMu_nDTTP", 50, 0, 50);
        
        h1_unusedMu_stationMask = new TH1F("unusedMu_stationMask", "unusedMu_stationMask", 25, 0, 25);
        
        h2_nUnusedMu_vs_nDTTP = new TH2F("nUnusedMu_vs_nDTTP", "nUnusedMu_vs_nDTTP", 50, 0, 50, 10, 0, 10);
        h2_unusedMu_pT_vs_eta = new TH2F("unusedMu_pT_vs_eta", "unusedMu_pT_vs_eta", nBin_eta, eta_min, eta_max, nBin_pT, pT_min, pT_max);
        h2_unusedMu_eta_vs_phi = new TH2F("unusedMu_eta_vs_phi", "unusedMu_eta_vs_phi", nBin_phi, phi_min, phi_max, nBin_eta, eta_min, eta_max);
        h2_unusedMu_pT_vs_stationMask = new TH2F("unusedMu_pT_vs_stationMask", "unusedMu_pT_vs_stationMask", 25, 0, 25, nBin_pT, pT_min, pT_max);
        h2_unusedMu_eta_vs_stationMask = new TH2F("unusedMu_eta_vs_stationMask", "unusedMu_eta_vs_stationMask", 25, 0, 25, nBin_eta, eta_min, eta_max);
        h2_unusedMu_phi_vs_stationMask = new TH2F("unusedMu_phi_vs_stationMask", "unusedMu_phi_vs_stationMask", 25, 0, 25, nBin_phi, phi_min, phi_max);
        h2_unusedMu_DTTP_pT_vs_deltaPhi = new TH2F("unusedMu_DTTP_pT_vs_deltaPhi", "unusedMu_DTTP_pT_vs_deltaPhi", 2*nBin_phi, phi_min, phi_max, 200, 0, 1000);
        
        h2_unusedMuHO_pT_vs_eta = new TH2F("unusedMuHO_pT_vs_eta", "unusedMuHO_pT_vs_eta", nBin_eta, eta_min, eta_max, nBin_pT, pT_min, pT_max);
        h2_unusedMuHO_eta_vs_phi = new TH2F("unusedMuHO_eta_vs_phi", "unusedMuHO_eta_vs_phi", nBin_phi, phi_min, phi_max, nBin_eta, eta_min, eta_max);
        h2_unusedMuHO_pT_vs_stationMask = new TH2F("unusedMuHO_pT_vs_stationMask", "unusedMuHO_pT_vs_stationMask", 25, 0, 25, nBin_pT, pT_min, pT_max);
        h2_unusedMuHO_eta_vs_stationMask = new TH2F("unusedMuHO_eta_vs_stationMask", "unusedMuHO_eta_vs_stationMask", 25, 0, 25, nBin_eta, eta_min, eta_max);
        h2_unusedMuHO_phi_vs_stationMask = new TH2F("unusedMuHO_phi_vs_stationMask", "unusedMuHO_phi_vs_stationMask", 25, 0, 25, nBin_phi, phi_min, phi_max);\
        
        h1_unusedMB1mu_wh0_phiB = new TH1F("unusedMB1mu_wh0_phiB", "unusedMB1mu_wh0_phiB", nBin_phi, phi_min, phi_max);
        h1_unusedMB1mu_wh1_phiB = new TH1F("unusedMB1mu_wh1_phiB", "unusedMB1mu_wh1_phiB", nBin_phi, phi_min, phi_max);
        
        h1_unusedMB2mu_wh0_phiB = new TH1F("unusedMB2mu_wh0_phiB", "unusedMB2mu_wh0_phiB", nBin_phi, phi_min, phi_max);
        h1_unusedMB2mu_wh1_phiB = new TH1F("unusedMB2mu_wh1_phiB", "unusedMB2mu_wh1_phiB", nBin_phi, phi_min, phi_max);
        
        h2_unusedMB12mu_MB2phiB_vs_MB1phiB = new TH2F("unusedMB12mu_MB2phiB_vs_MB1phiB", "unusedMB12mu_MB2phiB_vs_MB1phiB", nBin_phi, phi_min, phi_max, nBin_phi, phi_min, phi_max);
        h2_unusedMB12mu_wh0_MB2phiB_vs_MB1phiB = new TH2F("unusedMB12mu_wh0_MB2phiB_vs_MB1phiB", "unusedMB12mu_wh0_MB2phiB_vs_MB1phiB", nBin_phi, phi_min, phi_max, nBin_phi, phi_min, phi_max);
        h2_unusedMB12mu_wh1_MB2phiB_vs_MB1phiB = new TH2F("unusedMB12mu_wh1_MB2phiB_vs_MB1phiB", "unusedMB12mu_wh1_MB2phiB_vs_MB1phiB", nBin_phi, phi_min, phi_max, nBin_phi, phi_min, phi_max);
        
        h1_unusedMB1mu_wh0_psi = new TH1F("unusedMB1mu_wh0_psi", "unusedMB1mu_wh0_psi", nBin_phi, phi_min, phi_max);
        h1_unusedMB1mu_wh1_psi = new TH1F("unusedMB1mu_wh1_psi", "unusedMB1mu_wh1_psi", nBin_phi, phi_min, phi_max);
        
        h1_unusedMB2mu_wh0_psi = new TH1F("unusedMB2mu_wh0_psi", "unusedMB2mu_wh0_psi", nBin_phi, phi_min, phi_max);
        h1_unusedMB2mu_wh1_psi = new TH1F("unusedMB2mu_wh1_psi", "unusedMB2mu_wh1_psi", nBin_phi, phi_min, phi_max);
        
        h2_unusedMB12mu_MB2psi_vs_MB1psi = new TH2F("unusedMB12mu_MB2psi_vs_MB1psi", "unusedMB12mu_MB2psi_vs_MB1psi", nBin_phi, phi_min, phi_max, nBin_phi, phi_min, phi_max);
        h2_unusedMB12mu_wh0_MB2psi_vs_MB1psi = new TH2F("unusedMB12mu_wh0_MB2psi_vs_MB1psi", "unusedMB12mu_wh0_MB2psi_vs_MB1psi", nBin_phi, phi_min, phi_max, nBin_phi, phi_min, phi_max);
        h2_unusedMB12mu_wh1_MB2psi_vs_MB1psi = new TH2F("unusedMB12mu_wh1_MB2psi_vs_MB1psi", "unusedMB12mu_wh1_MB2psi_vs_MB1psi", nBin_phi, phi_min, phi_max, nBin_phi, phi_min, phi_max);
        
        h2_unusedMB2mu_pT_vs_eta = new TH2F("unusedMB2mu_pT_vs_eta", "unusedMB2mu_pT_vs_eta", nBin_eta, eta_min, eta_max, nBin_pT, pT_min, pT_max);
        h2_unusedMB2mu_eta_vs_phi = new TH2F("unusedMB2mu_eta_vs_phi", "unusedMB2mu_eta_vs_phi", nBin_phi, phi_min, phi_max, nBin_eta, eta_min, eta_max);
        
        h2_unusedMB1muHO_pT_vs_deltaR = new TH2F("unusedMB1muHO_pT_vs_deltaR", "unusedMB1muHO_pT_vs_deltaR", nBin_deltaR, deltaR_min, deltaR_max, nBin_pT, pT_min, pT_max);
        h2_unusedMB1muHO_pT_vs_deltaIphi = new TH2F("unusedMB1muHO_pT_vs_deltaIphi", "unusedMB1muHO_pT_vs_deltaIphi", 20, -10, 10, nBin_pT, pT_min, pT_max);
        
        h2_unusedMB2muHO_pT_vs_deltaR = new TH2F("unusedMB2muHO_pT_vs_deltaR", "unusedMB2muHO_pT_vs_deltaR", nBin_deltaR, deltaR_min, deltaR_max, nBin_pT, pT_min, pT_max);
        h2_unusedMB2muHO_pT_vs_deltaIphi = new TH2F("unusedMB2muHO_pT_vs_deltaIphi", "unusedMB2muHO_pT_vs_deltaIphi", 20, -10, 10, nBin_pT, pT_min, pT_max);
        
        
        //
        h1_BMTF_MB1_deltaPhi = new TH1F("BMTF_MB1_deltaPhi", "BMTF_MB1_deltaPhi", nBin_phi, phi_min, phi_max);
        h1_BMTF_MB2_deltaPhi = new TH1F("BMTF_MB2_deltaPhi", "BMTF_MB2_deltaPhi", nBin_phi, phi_min, phi_max);
        h1_BMTF_MB3_deltaPhi = new TH1F("BMTF_MB3_deltaPhi", "BMTF_MB3_deltaPhi", nBin_phi, phi_min, phi_max);
        h1_BMTF_MB4_deltaPhi = new TH1F("BMTF_MB4_deltaPhi", "BMTF_MB4_deltaPhi", nBin_phi, phi_min, phi_max);
        
        h2_BMTF_MB1_deltaPhi_vs_trackType = new TH2F("BMTF_MB1_deltaPhi_vs_trackType", "BMTF_MB1_deltaPhi_vs_trackType", 25, 0, 25, nBin_phi, phi_min, phi_max);
        h2_BMTF_MB2_deltaPhi_vs_trackType = new TH2F("BMTF_MB2_deltaPhi_vs_trackType", "BMTF_MB2_deltaPhi_vs_trackType", 25, 0, 25, nBin_phi, phi_min, phi_max);
        h2_BMTF_MB3_deltaPhi_vs_trackType = new TH2F("BMTF_MB3_deltaPhi_vs_trackType", "BMTF_MB3_deltaPhi_vs_trackType", 25, 0, 25, nBin_phi, phi_min, phi_max);
        h2_BMTF_MB4_deltaPhi_vs_trackType = new TH2F("BMTF_MB4_deltaPhi_vs_trackType", "BMTF_MB4_deltaPhi_vs_trackType", 25, 0, 25, nBin_phi, phi_min, phi_max);
        
        h1_BMTF_mu_deltaPt = new TH1F("BMTF_mu_deltaPt", "BMTF_mu_deltaPt", 200, -100, 100);
        
        h1_BMTF_mu_deltaEta = new TH1F("BMTF_mu_deltaEta", "BMTF_mu_deltaEta", 2*nBin_eta, eta_min, eta_max);
        h1_BMTF_mu_deltaPhi = new TH1F("BMTF_mu_deltaPhi", "BMTF_mu_deltaPhi", 2*nBin_phi, phi_min, phi_max);
        h1_BMTF_mu_deltaR = new TH1F("BMTF_mu_deltaR", "BMTF_mu_deltaR", nBin_deltaR, deltaR_min, deltaR_max);
        
        h2_BMTF_mu_pT_vs_deltaR = new TH2F("BMTF_mu_pT_vs_deltaR", "BMTF_mu_pT_vs_deltaR", nBin_deltaR, deltaR_min, deltaR_max, nBin_pT, pT_min, pT_max);
        
        h1_BMTF_muMatched_pT = new TH1F("BMTF_muMatched_pT", "BMTF_muMatched_pT", nBin_pT, pT_min, pT_max);
        h1_BMTF_muMatched_eta = new TH1F("BMTF_muMatched_eta", "BMTF_muMatched_eta", nBin_eta, eta_min, eta_max);
        h1_BMTF_muMatched_phi = new TH1F("BMTF_muMatched_phi", "BMTF_muMatched_phi", nBin_phi, phi_min, phi_max);
        
        h1_BMTF_muMatched_deltaEta = new TH1F("BMTF_muMatched_deltaEta", "BMTF_muMatched_deltaEta", 2*nBin_eta, eta_min, eta_max);
        h1_BMTF_muMatched_deltaPhi = new TH1F("BMTF_muMatched_deltaPhi", "BMTF_muMatched_deltaPhi", 2*nBin_phi, phi_min, phi_max);
        
        h1_BMTF_trackType = new TH1F("BMTF_trackType", "BMTF_trackType", 25, 0, 25);
        h1_BMTF_muMatched_trackType = new TH1F("BMTF_muMatched_trackType", "BMTF_muMatched_trackType", 25, 0, 25);
        
        h2_BMTF_muMatched_eta_vs_phi = new TH2F("BMTF_muMatched_eta_vs_phi", "BMTF_muMatched_eta_vs_phi", nBin_phi, phi_min, phi_max, nBin_eta, eta_min, eta_max);
        h2_BMTF_muMatched_pT_vs_eta = new TH2F("BMTF_muMatched_pT_vs_eta", "BMTF_muMatched_pT_vs_eta", nBin_eta, eta_min, eta_max, nBin_pT, pT_min, pT_max);
        h2_BMTF_muMatched_pT_vs_phi = new TH2F("BMTF_muMatched_pT_vs_phi", "BMTF_muMatched_pT_vs_phi", nBin_phi, phi_min, phi_max, nBin_pT, pT_min, pT_max);
        h2_BMTF_muMatched_pT_vs_trackType = new TH2F("BMTF_muMatched_pT_vs_trackType", "BMTF_muMatched_pT_vs_trackType", 25, 0, 25, nBin_pT, pT_min, pT_max);
        
        h2_BMTF_pT_resolution_vs_trackType = new TH2F("BMTF_pT_resolution_vs_trackType", "BMTF_pT_resolution_vs_trackType", 25, 0, 25, 50, 0, 5);
        
        h1_BMTF_muMatched_MB34onlyMB3HO_pT = new TH1F("BMTF_muMatched_MB34onlyMB3HO_pT", "BMTF_muMatched_MB34onlyMB3HO_pT", nBin_pT, pT_min, pT_max);
        h1_BMTF_muMatched_MB34onlyMB3HO_eta = new TH1F("BMTF_muMatched_MB34onlyMB3HO_eta", "BMTF_muMatched_MB34onlyMB3HO_eta", nBin_eta, eta_min, eta_max);
        
        h2_BMTF_muMatched_MB34onlyMB3HO_pT_vs_eta = new TH2F("BMTF_muMatched_MB34onlyMB3HO_pT_vs_eta", "BMTF_muMatched_MB34onlyMB3HO_pT_vs_eta", nBin_eta, eta_min, eta_max, nBin_pT, pT_min, pT_max);
        
        
        //
        h1_BMTF_muNotMatched_pT = new TH1F("BMTF_muNotMatched_pT", "BMTF_muNotMatched_pT", nBin_pT, pT_min, pT_max);
        h1_BMTF_muNotMatched_eta = new TH1F("BMTF_muNotMatched_eta", "BMTF_muNotMatched_eta", nBin_eta, eta_min, eta_max);
        h1_BMTF_muNotMatched_phi = new TH1F("BMTF_muNotMatched_phi", "BMTF_muNotMatched_phi", nBin_phi, phi_min, phi_max);
        
        h2_BMTF_muNotMatched_eta_vs_phi = new TH2F("BMTF_muNotMatched_eta_vs_phi", "BMTF_muNotMatched_eta_vs_phi", nBin_phi, phi_min, phi_max, nBin_eta, eta_min, eta_max);
        h2_BMTF_muNotMatched_pT_vs_eta = new TH2F("BMTF_muNotMatched_pT_vs_eta", "BMTF_muNotMatched_pT_vs_eta", nBin_eta, eta_min, eta_max, nBin_pT, pT_min, pT_max);
        h2_BMTF_muNotMatched_pT_vs_phi = new TH2F("BMTF_muNotMatched_pT_vs_phi", "BMTF_muNotMatched_pT_vs_phi", nBin_phi, phi_min, phi_max, nBin_pT, pT_min, pT_max);
        
        
        //
        h1_MB1_BMTF_deltaPhi = new TH1F("MB1_BMTF_deltaPhi", "MB1_BMTF_deltaPhi", 2*nBin_phi, phi_min, phi_max);
        
        
        //
        h1_MB1_isoType = new TH1F("MB1_isoType", "MB1_isoType", 5, -2, 3);
        
        
        //
        h2_MB_station_vs_wheel = new TH2F("MB_station_vs_wheel", "MB_station_vs_wheel", 7, -3, 4, 5, 0, 5);
        h2_usedMB_station_vs_wheel = new TH2F("usedMB_station_vs_wheel", "usedMB_station_vs_wheel", 7, -3, 4, 5, 0, 5);
        h2_unusedMB_station_vs_wheel = new TH2F("unusedMB_station_vs_wheel", "unusedMB_station_vs_wheel", 7, -3, 4, 5, 0, 5);
        
        
        //
        h1_isoMB1HO_deltaIphi = new TH1F("isoMB1HO_deltaIphi", "isoMB1HO_deltaIphi", 20, -10, 10);
        
        h1_isoMB1HO_mu_deltaPt = new TH1F("isoMB1HO_mu_deltaPt", "isoMB1HO_mu_deltaPt", 200, -100, 100);
        h2_isoMB1HO_mu_pT_vs_deltaR = new TH2F("isoMB1HO_mu_pT_vs_deltaR", "isoMB1HO_mu_pT_vs_deltaR", nBin_deltaR, deltaR_min, deltaR_max, nBin_pT, pT_min, pT_max);
        
        h1_isoMB1HO_muMatched_pT = new TH1F("isoMB1HO_muMatched_pT", "isoMB1HO_muMatched_pT", nBin_pT, pT_min, pT_max);
        h1_isoMB1HO_muMatched_eta = new TH1F("isoMB1HO_muMatched_eta", "isoMB1HO_muMatched_eta", nBin_eta, eta_min, eta_max);
        h1_isoMB1HO_muMatched_phi = new TH1F("isoMB1HO_muMatched_phi", "isoMB1HO_muMatched_phi", nBin_phi, phi_min, phi_max);
        
        h1_isoMB1HO_muMatched_3x3 = new TH1F("isoMB1HO_muMatched_3x3", "isoMB1HO_muMatched_3x3", 10, 0, 10);
        
        h2_isoMB1HO_muMatched_eta_vs_phi = new TH2F("isoMB1HO_muMatched_eta_vs_phi", "isoMB1HO_muMatched_eta_vs_phi", nBin_phi, phi_min, phi_max, nBin_eta, eta_min, eta_max);
        h2_isoMB1HO_muMatched_pT_vs_eta = new TH2F("isoMB1HO_muMatched_pT_vs_eta", "isoMB1HO_muMatched_pT_vs_eta", nBin_eta, eta_min, eta_max, nBin_pT, pT_min, pT_max);
        h2_isoMB1HO_muMatched_pT_vs_phi = new TH2F("isoMB1HO_muMatched_pT_vs_phi", "isoMB1HO_muMatched_pT_vs_phi", nBin_phi, phi_min, phi_max, nBin_pT, pT_min, pT_max);
        
        h2_isoMB1HO_muMatched_pT_vs_deltaIphi = new TH2F("isoMB1HO_muMatched_pT_vs_deltaIphi", "isoMB1HO_muMatched_pT_vs_deltaIphi", 20, -10, 10, nBin_pT, pT_min, pT_max);
        
        
        //
        h1_isoMB1HO_muNotMatched_pT = new TH1F("isoMB1HO_muNotMatched_pT", "isoMB1HO_muNotMatched_pT", nBin_pT, pT_min, pT_max);
        h1_isoMB1HO_muNotMatched_eta = new TH1F("isoMB1HO_muNotMatched_eta", "isoMB1HO_muNotMatched_eta", nBin_eta, eta_min, eta_max);
        h1_isoMB1HO_muNotMatched_phi = new TH1F("isoMB1HO_muNotMatched_phi", "isoMB1HO_muNotMatched_phi", nBin_phi, phi_min, phi_max);
        
        h1_isoMB1HO_muNotMatched_3x3 = new TH1F("isoMB1HO_muNotMatched_3x3", "isoMB1HO_muNotMatched_3x3", 10, 0, 10);
        
        h2_isoMB1HO_muNotMatched_eta_vs_phi = new TH2F("isoMB1HO_muNotMatched_eta_vs_phi", "isoMB1HO_muNotMatched_eta_vs_phi", nBin_phi, phi_min, phi_max, nBin_eta, eta_min, eta_max);
        h2_isoMB1HO_muNotMatched_pT_vs_eta = new TH2F("isoMB1HO_muNotMatched_pT_vs_eta", "isoMB1HO_muNotMatched_pT_vs_eta", nBin_eta, eta_min, eta_max, nBin_pT, pT_min, pT_max);
        h2_isoMB1HO_muNotMatched_pT_vs_phi = new TH2F("isoMB1HO_muNotMatched_pT_vs_phi", "isoMB1HO_muNotMatched_pT_vs_phi", nBin_phi, phi_min, phi_max, nBin_pT, pT_min, pT_max);
        
        h2_isoMB1HO_nNotMuMatched_vs_nUnusedMu = new TH2F("isoMB1HO_nNotMuMatched_vs_nUnusedMu", "isoMB1HO_nNotMuMatched_vs_nUnusedMu", 50, 0, 50, 50, 0, 50);
        
        
        //
        h1_MB34onlyBMTF_pT = new TH1F("MB34onlyBMTF_pT", "MB34onlyBMTF_pT", nBin_pT, pT_min, pT_max);
        h1_MB34onlyBMTF_eta = new TH1F("MB34onlyBMTF_eta", "MB34onlyBMTF_eta", nBin_eta, eta_min, eta_max);
        h1_MB34onlyBMTF_nearestHO_iEta = new TH1F("MB34onlyBMTF_nearestHO_iEta", "MB34onlyBMTF_nearestHO_iEta", 40, -20, 20);
        h1_MB34onlyBMTF_nearestHO_deltaR = new TH1F("MB34onlyBMTF_nearestHO_deltaR", "MB34onlyBMTF_nearestHO_deltaR", nBin_deltaR, deltaR_min, deltaR_max);
        
        h1_MB34onlyBMTFHO_pT = new TH1F("MB34onlyBMTFHO_pT", "MB34onlyBMTFHO_pT", nBin_pT, pT_min, pT_max);
        h1_MB34onlyBMTFHO_eta = new TH1F("MB34onlyBMTFHO_eta", "MB34onlyBMTFHO_eta", nBin_eta, eta_min, eta_max);
        
        h2_MB34onlyBMTF_nearestMB3_wh_vs_nearestHO_iEta = new TH2F("MB34onlyBMTF_nearestMB3_wh_vs_nearestHO_iEta", "MB34onlyBMTF_nearestMB3_wh_vs_nearestHO_iEta", 40, -20, 20, 7, -3, 4);
        h2_MB34onlyBMTF_nearestMB4_wh_vs_nearestHO_iEta = new TH2F("MB34onlyBMTF_nearestMB4_wh_vs_nearestHO_iEta", "MB34onlyBMTF_nearestMB4_wh_vs_nearestHO_iEta", 40, -20, 20, 7, -3, 4);
        
        h2_MB34onlyBMTF_matchedMu_pT_vs_nearestMB3nearestHO_deltaIphi = new TH2F("MB34onlyBMTF_matchedMu_pT_vs_nearestMB3nearestHO_deltaIphi", "MB34onlyBMTF_matchedMu_pT_vs_nearestMB3nearestHO_deltaIphi", 20, -10, 10, nBin_pT, pT_min, pT_max);
        h2_MB34onlyBMTF_matchedMu_pT_vs_nearestMB4nearestHO_deltaIphi = new TH2F("MB34onlyBMTF_matchedMu_pT_vs_nearestMB4nearestHO_deltaIphi", "MB34onlyBMTF_matchedMu_pT_vs_nearestMB4nearestHO_deltaIphi", 20, -10, 10, nBin_pT, pT_min, pT_max);
        
        h2_MB34onlyBMTF_matchedMu_ch_vs_nearestMB3nearestHO_deltaIphi = new TH2F("MB34onlyBMTF_matchedMu_ch_vs_nearestMB3nearestHO_deltaIphi", "MB34onlyBMTF_matchedMu_pT_vs_nearestMB3nearestHO_deltaIphi", 20, -10, 10, 5, -2, 3);
        h2_MB34onlyBMTF_matchedMu_ch_vs_nearestMB4nearestHO_deltaIphi = new TH2F("MB34onlyBMTF_matchedMu_ch_vs_nearestMB4nearestHO_deltaIphi", "MB34onlyBMTF_matchedMu_pT_vs_nearestMB4nearestHO_deltaIphi", 20, -10, 10, 5, -2, 3);
        
        
        //
        h1_test1 = new TH1F("test1", "test1", 60+10, 0, 60+10);
        h1_test1->SetLabelSize(0.025, "x");
        
        h1_test1a = new TH1F("test1a", "test1a", 120+10, 0, 120+10);
        h1_test1a->SetLabelSize(0.02, "x");
        
        //
        h1_test2 = new TH1F("test2", "test2", 200+10, 0, 200+10);
        h1_test2->SetLabelSize(0.01, "x");
        
        h1_test2a = new TH1F("test2a", "test2a", 400+10, 0, 400+10);
        h1_test2a->SetLabelSize(0.005, "x");
        
        for(int iEta = 0; iEta < 10; iEta++)
        {
            for(int iMask = 1; iMask < 16; iMask++)
            {
                char temp_str[100];
                
                sprintf(temp_str, "i#eta%d, MB ", iEta+1);
                std::string binLabel = std::string(temp_str);
                
                sprintf(temp_str, "i#eta%d/1, MB ", iEta+1);
                std::string binLabel_1 = std::string(temp_str);
                
                sprintf(temp_str, "i#eta%d/2, MB ", iEta+1);
                std::string binLabel_2 = std::string(temp_str);
                
                for(int iStation = 0; iStation < 4; iStation++)
                {
                    if(iMask & (1<<(iStation)))
                    {
                        binLabel += std::to_string(iStation+1);
                        binLabel_1 += std::to_string(iStation+1);
                        binLabel_2 += std::to_string(iStation+1);
                    }
                }
                
                h1_test2->GetXaxis()->SetBinLabel(iEta*20 + iMask+1, binLabel.c_str());
                h1_test2->GetXaxis()->SetBinLabel(iEta*20 + 1, "none");
                
                h1_test2a->GetXaxis()->SetBinLabel(iEta*2*20 + 0*20 + iMask+1, binLabel_1.c_str());
                h1_test2a->GetXaxis()->SetBinLabel(iEta*2*20 + 0*20 + 1, "none");
                
                h1_test2a->GetXaxis()->SetBinLabel(iEta*2*20 + 1*20 + iMask+1, binLabel_2.c_str());
                h1_test2a->GetXaxis()->SetBinLabel(iEta*2*20 + 1*20 + 1, "none");
            }
        }
        
        //
        h1_test3 = new TH1F("test3", "test3", 60+10, 0, 60+10);
        h1_test3->SetLabelSize(0.025, "x");
        
        h1_test3a = new TH1F("test3a", "test3a", 100+10, 0, 100+10);
        h1_test3a->SetLabelSize(0.02, "x");
        
        for(int iStation = 0; iStation < 4; iStation++)
        {
            for(int iEta = 1; iEta <= 10; iEta++)
            {
                char binLabel[100];
                
                sprintf(binLabel, "i#eta%d, MB %d", iEta, iStation+1);
                h1_test1->GetXaxis()->SetBinLabel((iEta-1)*6 + iStation+1+1, binLabel);
                
                sprintf(binLabel, "i#eta%d/1, MB %d", iEta, iStation+1);
                h1_test1a->GetXaxis()->SetBinLabel((iEta-1)*2*6 + 0*6 + iStation+1+1, binLabel);
                
                sprintf(binLabel, "i#eta%d/2, MB %d", iEta, iStation+1);
                h1_test1a->GetXaxis()->SetBinLabel((iEta-1)*2*6 + 1*6 + iStation+1+1, binLabel);
                
                
                sprintf(binLabel, "MB %d, i#eta%d", iStation+1, iEta);
                h1_test3->GetXaxis()->SetBinLabel(iStation*15 + iEta+1, binLabel);
                
                sprintf(binLabel, "MB %d, i#eta%d/1", iStation+1, iEta);
                h1_test3a->GetXaxis()->SetBinLabel(iStation*25 + iEta*2-1+1, binLabel);
                
                sprintf(binLabel, "MB %d, i#eta%d/2", iStation+1, iEta);
                h1_test3a->GetXaxis()->SetBinLabel(iStation*25 + iEta*2-0+1, binLabel);
            }
        }
        
        
        h1_test1->LabelsOption("v", "x");
        h1_test1a->LabelsOption("v", "x");
        
        h1_test2->LabelsOption("v", "x");
        h1_test2a->LabelsOption("v", "x");
        
        h1_test3->LabelsOption("v", "x");
        h1_test3a->LabelsOption("v", "x");
        
        
        h1_BMTF_trackType->SetLabelSize(0.025, "x");
        h1_BMTF_muMatched_trackType->SetLabelSize(0.025, "x");
        h2_BMTF_muMatched_pT_vs_trackType->SetLabelSize(0.025, "x");
        h2_BMTF_pT_resolution_vs_trackType->SetLabelSize(0.025, "x");
        
        h2_BMTF_MB1_deltaPhi_vs_trackType->SetLabelSize(0.025, "x");
        h2_BMTF_MB2_deltaPhi_vs_trackType->SetLabelSize(0.025, "x");
        h2_BMTF_MB3_deltaPhi_vs_trackType->SetLabelSize(0.025, "x");
        h2_BMTF_MB4_deltaPhi_vs_trackType->SetLabelSize(0.025, "x");
        
        for(int iMask = 1; iMask < 16; iMask++)
        {
            char temp_str[100];
            
            std::string binLabel = "MB ";
            
            for(int iStation = 0; iStation < 4; iStation++)
            {
                if(iMask & (1<<(iStation)))
                {
                    binLabel += std::to_string(iStation+1);
                }
            }
            
            h2_usedMu_pT_vs_stationMask->GetXaxis()->SetBinLabel(iMask+1, binLabel.c_str());
            h2_usedMu_eta_vs_stationMask->GetXaxis()->SetBinLabel(iMask+1, binLabel.c_str());
            
            h1_unusedMu_stationMask->GetXaxis()->SetBinLabel(iMask+1, binLabel.c_str());
            h2_unusedMu_pT_vs_stationMask->GetXaxis()->SetBinLabel(iMask+1, binLabel.c_str());
            h2_unusedMu_eta_vs_stationMask->GetXaxis()->SetBinLabel(iMask+1, binLabel.c_str());
            h2_unusedMu_phi_vs_stationMask->GetXaxis()->SetBinLabel(iMask+1, binLabel.c_str());
            
            h2_unusedMuHO_pT_vs_stationMask->GetXaxis()->SetBinLabel(iMask+1, binLabel.c_str());
            h2_unusedMuHO_eta_vs_stationMask->GetXaxis()->SetBinLabel(iMask+1, binLabel.c_str());
            h2_unusedMuHO_phi_vs_stationMask->GetXaxis()->SetBinLabel(iMask+1, binLabel.c_str());
            
            h1_BMTF_trackType->GetXaxis()->SetBinLabel(iMask+1, binLabel.c_str());
            h1_BMTF_muMatched_trackType->GetXaxis()->SetBinLabel(iMask+1, binLabel.c_str());
            h2_BMTF_muMatched_pT_vs_trackType->GetXaxis()->SetBinLabel(iMask+1, binLabel.c_str());
            h2_BMTF_pT_resolution_vs_trackType->GetXaxis()->SetBinLabel(iMask+1, binLabel.c_str());
            
            h2_BMTF_MB1_deltaPhi_vs_trackType->GetXaxis()->SetBinLabel(iMask+1, binLabel.c_str());
            h2_BMTF_MB2_deltaPhi_vs_trackType->GetXaxis()->SetBinLabel(iMask+1, binLabel.c_str());
            h2_BMTF_MB3_deltaPhi_vs_trackType->GetXaxis()->SetBinLabel(iMask+1, binLabel.c_str());
            h2_BMTF_MB4_deltaPhi_vs_trackType->GetXaxis()->SetBinLabel(iMask+1, binLabel.c_str());
        }
        
        //
        h2_usedMu_pT_vs_stationMask->GetXaxis()->SetBinLabel(1, "none");
        h2_usedMu_pT_vs_stationMask->LabelsOption("v", "x");
        
        h2_usedMu_eta_vs_stationMask->GetXaxis()->SetBinLabel(1, "none");
        h2_usedMu_eta_vs_stationMask->LabelsOption("v", "x");
        
        h1_unusedMu_stationMask->GetXaxis()->SetBinLabel(1, "none");
        h1_unusedMu_stationMask->LabelsOption("v", "x");
        
        h2_unusedMu_pT_vs_stationMask->GetXaxis()->SetBinLabel(1, "none");
        h2_unusedMu_pT_vs_stationMask->LabelsOption("v", "x");
        
        h2_unusedMu_eta_vs_stationMask->GetXaxis()->SetBinLabel(1, "none");
        h2_unusedMu_eta_vs_stationMask->LabelsOption("v", "x");
        
        h2_unusedMu_phi_vs_stationMask->GetXaxis()->SetBinLabel(1, "none");
        h2_unusedMu_phi_vs_stationMask->LabelsOption("v", "x");
        
        //
        h2_unusedMuHO_pT_vs_stationMask->GetXaxis()->SetBinLabel(1, "none");
        h2_unusedMuHO_pT_vs_stationMask->LabelsOption("v", "x");
        
        h2_unusedMuHO_eta_vs_stationMask->GetXaxis()->SetBinLabel(1, "none");
        h2_unusedMuHO_eta_vs_stationMask->LabelsOption("v", "x");
        
        h2_unusedMuHO_phi_vs_stationMask->GetXaxis()->SetBinLabel(1, "none");
        h2_unusedMuHO_phi_vs_stationMask->LabelsOption("v", "x");
        
        //
        h1_BMTF_trackType->GetXaxis()->SetBinLabel(1, "all BMTF");
        h1_BMTF_muMatched_trackType->GetXaxis()->SetBinLabel(1, "all BMTF");
        h2_BMTF_muMatched_pT_vs_trackType->GetXaxis()->SetBinLabel(1, "all BMTF");
        h2_BMTF_pT_resolution_vs_trackType->GetXaxis()->SetBinLabel(1, "all BMTF");
        
        h1_BMTF_muMatched_trackType->GetXaxis()->SetBinLabel(20, "#splitline{MB 34}{MB3+HO}");
        h1_BMTF_muMatched_trackType->GetXaxis()->SetBinLabel(21, "#splitline{MB 34}{MB4+HO}");
        h1_BMTF_muMatched_trackType->GetXaxis()->SetBinLabel(22, "#splitline{MB 34}{MB34+HO}");
        h1_BMTF_muMatched_trackType->GetXaxis()->SetBinLabel(23, "#splitline{MB 34}{no HO}");
        
        h2_BMTF_muMatched_pT_vs_trackType->GetXaxis()->SetBinLabel(20, "#splitline{MB 34}{MB3+HO}");
        h2_BMTF_muMatched_pT_vs_trackType->GetXaxis()->SetBinLabel(21, "#splitline{MB 34}{MB4+HO}");
        h2_BMTF_muMatched_pT_vs_trackType->GetXaxis()->SetBinLabel(22, "#splitline{MB 34}{MB34+HO}");
        h2_BMTF_muMatched_pT_vs_trackType->GetXaxis()->SetBinLabel(23, "#splitline{MB 34}{no HO}");
        
        h2_BMTF_pT_resolution_vs_trackType->GetXaxis()->SetBinLabel(20, "#splitline{MB 34}{MB3+HO}");
        h2_BMTF_pT_resolution_vs_trackType->GetXaxis()->SetBinLabel(21, "#splitline{MB 34}{MB4+HO}");
        h2_BMTF_pT_resolution_vs_trackType->GetXaxis()->SetBinLabel(22, "#splitline{MB 34}{MB34+HO}");
        h2_BMTF_pT_resolution_vs_trackType->GetXaxis()->SetBinLabel(23, "#splitline{MB 34}{no HO}");
        
        h1_BMTF_trackType->LabelsOption("v", "x");
        h1_BMTF_muMatched_trackType->LabelsOption("v", "x");
        h2_BMTF_muMatched_pT_vs_trackType->LabelsOption("v", "x");
        h2_BMTF_pT_resolution_vs_trackType->LabelsOption("v", "x");
        
        
        h2_BMTF_MB1_deltaPhi_vs_trackType->GetXaxis()->SetBinLabel(1, "all BMTF");
        h2_BMTF_MB2_deltaPhi_vs_trackType->GetXaxis()->SetBinLabel(1, "all BMTF");
        h2_BMTF_MB3_deltaPhi_vs_trackType->GetXaxis()->SetBinLabel(1, "all BMTF");
        h2_BMTF_MB4_deltaPhi_vs_trackType->GetXaxis()->SetBinLabel(1, "all BMTF");
        
        h2_BMTF_MB1_deltaPhi_vs_trackType->LabelsOption("v", "x");
        h2_BMTF_MB2_deltaPhi_vs_trackType->LabelsOption("v", "x");
        h2_BMTF_MB3_deltaPhi_vs_trackType->LabelsOption("v", "x");
        h2_BMTF_MB4_deltaPhi_vs_trackType->LabelsOption("v", "x");
    }
    
    
    void writeData()
    {
        //
        h1_mu_n->Write();
        h1_mu_pT->Write();
        h1_mu_eta->Write();
        h1_mu_phi->Write();
        
        h2_mu_eta_vs_phi->Write();
        h2_mu_pT_vs_eta->Write();
        h2_mu_pT_vs_phi->Write();
        h2_mu_pT_vs_MB1extDeltaEta->Write();
        h2_mu_pT_vs_MB1extDeltaPhi->Write();
        
        h1_usedMu_pT->Write();
        h1_usedMu_eta->Write();
        h1_usedMu_phi->Write();
        
        h2_usedMu_pT_vs_eta->Write();
        h2_usedMu_pT_vs_stationMask->Write();
        h2_usedMu_eta_vs_stationMask->Write();
        h2_usedMu_DTTP_pT_vs_deltaPhi->Write();
        
        h2_usedMB12mu_MB2phiB_vs_MB1phiB->Write();
        h2_usedMB12mu_wh0_MB2phiB_vs_MB1phiB->Write();
        h2_usedMB12mu_wh1_MB2phiB_vs_MB1phiB->Write();
        
        h2_usedMB12mu_wh0_pT_vs_MB1phiB->Write();
        h2_usedMB12mu_wh1_pT_vs_MB1phiB->Write();
        
        
        //
        h1_unusedMu_pT->Write();
        h1_unusedMu_eta->Write();
        h1_unusedMu_phi->Write();
        
        h1_unusedMu_nearestDTTP_station->Write();
        h1_unusedMu_nDTTP->Write();
        
        h1_unusedMu_stationMask->Write();
        
        h2_nUnusedMu_vs_nDTTP->Write();
        h2_unusedMu_pT_vs_eta->Write();
        h2_unusedMu_eta_vs_phi->Write();
        h2_unusedMu_pT_vs_stationMask->Write();
        h2_unusedMu_eta_vs_stationMask->Write();
        h2_unusedMu_phi_vs_stationMask->Write();
        h2_unusedMu_DTTP_pT_vs_deltaPhi->Write();
        
        h2_unusedMuHO_pT_vs_eta->Write();
        h2_unusedMuHO_eta_vs_phi->Write();
        h2_unusedMuHO_pT_vs_stationMask->Write();
        h2_unusedMuHO_eta_vs_stationMask->Write();
        h2_unusedMuHO_phi_vs_stationMask->Write();
        
        h1_unusedMB1mu_wh0_phiB->Write();
        h1_unusedMB1mu_wh1_phiB->Write();
        
        h1_unusedMB2mu_wh0_phiB->Write();
        h1_unusedMB2mu_wh1_phiB->Write();
        
        h2_unusedMB12mu_MB2phiB_vs_MB1phiB->Write();
        h2_unusedMB12mu_wh0_MB2phiB_vs_MB1phiB->Write();
        h2_unusedMB12mu_wh1_MB2phiB_vs_MB1phiB->Write();
        
        h1_unusedMB1mu_wh0_psi->Write();
        h1_unusedMB1mu_wh1_psi->Write();
        
        h1_unusedMB2mu_wh0_psi->Write();
        h1_unusedMB2mu_wh1_psi->Write();
        
        h2_unusedMB12mu_MB2psi_vs_MB1psi->Write();
        h2_unusedMB12mu_wh0_MB2psi_vs_MB1psi->Write();
        h2_unusedMB12mu_wh1_MB2psi_vs_MB1psi->Write();
        
        h2_unusedMB2mu_pT_vs_eta->Write();
        h2_unusedMB2mu_eta_vs_phi->Write();
        
        h2_unusedMB1muHO_pT_vs_deltaR->Write();
        h2_unusedMB1muHO_pT_vs_deltaIphi->Write();
        
        h2_unusedMB2muHO_pT_vs_deltaR->Write();
        h2_unusedMB2muHO_pT_vs_deltaIphi->Write();
        
        
        //
        h1_BMTF_MB1_deltaPhi->Write();
        h1_BMTF_MB2_deltaPhi->Write();
        h1_BMTF_MB3_deltaPhi->Write();
        h1_BMTF_MB4_deltaPhi->Write();
        
        h2_BMTF_MB1_deltaPhi_vs_trackType->Write();
        h2_BMTF_MB2_deltaPhi_vs_trackType->Write();
        h2_BMTF_MB3_deltaPhi_vs_trackType->Write();
        h2_BMTF_MB4_deltaPhi_vs_trackType->Write();
        
        h1_BMTF_mu_deltaPt->Write();
        
        h1_BMTF_mu_deltaEta->Write();
        h1_BMTF_mu_deltaPhi->Write();
        h1_BMTF_mu_deltaR->Write();
        
        h2_BMTF_mu_pT_vs_deltaR->Write();
        
        h1_BMTF_muMatched_pT->Write();
        h1_BMTF_muMatched_eta->Write();
        h1_BMTF_muMatched_phi->Write();
        
        h1_BMTF_muMatched_deltaEta->Write();
        h1_BMTF_muMatched_deltaPhi->Write();
        
        h1_BMTF_trackType->Write();
        h1_BMTF_muMatched_trackType->Write();
        
        h2_BMTF_muMatched_eta_vs_phi->Write();
        h2_BMTF_muMatched_pT_vs_eta->Write();
        h2_BMTF_muMatched_pT_vs_phi->Write();
        h2_BMTF_muMatched_pT_vs_trackType->Write();
        
        h2_BMTF_pT_resolution_vs_trackType->Write();
        
        h1_BMTF_muMatched_MB34onlyMB3HO_pT->Write();
        h1_BMTF_muMatched_MB34onlyMB3HO_eta->Write();
        
        h2_BMTF_muMatched_MB34onlyMB3HO_pT_vs_eta->Write();
        
        //
        h1_BMTF_muNotMatched_pT->Write();
        h1_BMTF_muNotMatched_eta->Write();
        h1_BMTF_muNotMatched_phi->Write();
        
        h2_BMTF_muNotMatched_eta_vs_phi->Write();
        h2_BMTF_muNotMatched_pT_vs_eta->Write();
        h2_BMTF_muNotMatched_pT_vs_phi->Write();
        
        
        //
        h1_MB1_BMTF_deltaPhi->Write();
        
        
        //
        h1_MB1_isoType->Write();
        
        
        //
        h2_MB_station_vs_wheel->Write();
        h2_usedMB_station_vs_wheel->Write();
        h2_unusedMB_station_vs_wheel->Write();
        
        
        //
        h1_isoMB1HO_deltaIphi->Write();
        
        h1_isoMB1HO_mu_deltaPt->Write();
        h2_isoMB1HO_mu_pT_vs_deltaR->Write();
        
        h1_isoMB1HO_muMatched_pT->Write();
        h1_isoMB1HO_muMatched_eta->Write();
        h1_isoMB1HO_muMatched_phi->Write();
        
        h1_isoMB1HO_muMatched_3x3->Write();
        
        h2_isoMB1HO_muMatched_eta_vs_phi->Write();
        h2_isoMB1HO_muMatched_pT_vs_eta->Write();
        h2_isoMB1HO_muMatched_pT_vs_phi->Write();
        
        h2_isoMB1HO_muMatched_pT_vs_deltaIphi->Write();
        
        
        //
        h1_isoMB1HO_muNotMatched_pT->Write();
        h1_isoMB1HO_muNotMatched_eta->Write();
        h1_isoMB1HO_muNotMatched_phi->Write();
        
        h1_isoMB1HO_muNotMatched_3x3->Write();
        
        h2_isoMB1HO_muNotMatched_eta_vs_phi->Write();
        h2_isoMB1HO_muNotMatched_pT_vs_eta->Write();
        h2_isoMB1HO_muNotMatched_pT_vs_phi->Write();
        
        h2_isoMB1HO_nNotMuMatched_vs_nUnusedMu->Write();
        
        
        //
        h1_MB34onlyBMTF_pT->Write();
        h1_MB34onlyBMTF_eta->Write();
        h1_MB34onlyBMTF_nearestHO_iEta->Write();
        h1_MB34onlyBMTF_nearestHO_deltaR->Write();
        h1_MB34onlyBMTFHO_pT->Write();
        h1_MB34onlyBMTFHO_eta->Write();
        
        h2_MB34onlyBMTF_nearestMB3_wh_vs_nearestHO_iEta->Write();
        h2_MB34onlyBMTF_nearestMB4_wh_vs_nearestHO_iEta->Write();
        
        h2_MB34onlyBMTF_matchedMu_pT_vs_nearestMB3nearestHO_deltaIphi->Write();
        h2_MB34onlyBMTF_matchedMu_pT_vs_nearestMB4nearestHO_deltaIphi->Write();
        
        h2_MB34onlyBMTF_matchedMu_ch_vs_nearestMB3nearestHO_deltaIphi->Write();
        h2_MB34onlyBMTF_matchedMu_ch_vs_nearestMB4nearestHO_deltaIphi->Write();
        
        
        //
        h1_test1->Write();
        h1_test1a->Write();
        
        h1_test2->Write();
        h1_test2a->Write();
        
        h1_test3->Write();
        h1_test3a->Write();
    }
    
    
    void freeMemory()
    {
        //
        delete h1_mu_n;
        delete h1_mu_pT;
        delete h1_mu_eta;
        delete h1_mu_phi;
        
        delete h2_mu_eta_vs_phi;
        delete h2_mu_pT_vs_eta;
        delete h2_mu_pT_vs_phi;
        delete h2_mu_pT_vs_MB1extDeltaEta;
        delete h2_mu_pT_vs_MB1extDeltaPhi;
        
        delete h1_usedMu_pT;
        delete h1_usedMu_eta;
        delete h1_usedMu_phi;
        
        delete h2_usedMu_pT_vs_eta;
        delete h2_usedMu_pT_vs_stationMask;
        delete h2_usedMu_eta_vs_stationMask;
        delete h2_usedMu_DTTP_pT_vs_deltaPhi;
        
        delete h2_usedMB12mu_MB2phiB_vs_MB1phiB;
        delete h2_usedMB12mu_wh0_MB2phiB_vs_MB1phiB;
        delete h2_usedMB12mu_wh1_MB2phiB_vs_MB1phiB;
        
        delete h2_usedMB12mu_wh0_pT_vs_MB1phiB;
        delete h2_usedMB12mu_wh1_pT_vs_MB1phiB;
        
        
        //
        delete h1_unusedMu_pT;
        delete h1_unusedMu_eta;
        delete h1_unusedMu_phi;
        
        delete h1_unusedMu_nearestDTTP_station;
        delete h1_unusedMu_nDTTP;
        
        delete h1_unusedMu_stationMask;
        
        delete h2_nUnusedMu_vs_nDTTP;
        delete h2_unusedMu_pT_vs_eta;
        delete h2_unusedMu_eta_vs_phi;
        delete h2_unusedMu_pT_vs_stationMask;
        delete h2_unusedMu_eta_vs_stationMask;
        delete h2_unusedMu_phi_vs_stationMask;
        delete h2_unusedMu_DTTP_pT_vs_deltaPhi;
        
        delete h2_unusedMuHO_pT_vs_eta;
        delete h2_unusedMuHO_eta_vs_phi;
        delete h2_unusedMuHO_pT_vs_stationMask;
        delete h2_unusedMuHO_eta_vs_stationMask;
        delete h2_unusedMuHO_phi_vs_stationMask;
        
        delete h1_unusedMB1mu_wh0_phiB;
        delete h1_unusedMB1mu_wh1_phiB;
        
        delete h1_unusedMB2mu_wh0_phiB;
        delete h1_unusedMB2mu_wh1_phiB;
        
        delete h2_unusedMB12mu_MB2phiB_vs_MB1phiB;
        delete h2_unusedMB12mu_wh0_MB2phiB_vs_MB1phiB;
        delete h2_unusedMB12mu_wh1_MB2phiB_vs_MB1phiB;
        
        delete h1_unusedMB1mu_wh0_psi;
        delete h1_unusedMB1mu_wh1_psi;
        
        delete h1_unusedMB2mu_wh0_psi;
        delete h1_unusedMB2mu_wh1_psi;
        
        delete h2_unusedMB12mu_MB2psi_vs_MB1psi;
        delete h2_unusedMB12mu_wh0_MB2psi_vs_MB1psi;
        delete h2_unusedMB12mu_wh1_MB2psi_vs_MB1psi;
        
        delete h2_unusedMB2mu_pT_vs_eta;
        delete h2_unusedMB2mu_eta_vs_phi;
        
        delete h2_unusedMB1muHO_pT_vs_deltaR;
        delete h2_unusedMB1muHO_pT_vs_deltaIphi;
        
        delete h2_unusedMB2muHO_pT_vs_deltaR;
        delete h2_unusedMB2muHO_pT_vs_deltaIphi;
        
        //
        delete h1_BMTF_MB1_deltaPhi;
        delete h1_BMTF_MB2_deltaPhi;
        delete h1_BMTF_MB3_deltaPhi;
        delete h1_BMTF_MB4_deltaPhi;
        
        delete h2_BMTF_MB1_deltaPhi_vs_trackType;
        delete h2_BMTF_MB2_deltaPhi_vs_trackType;
        delete h2_BMTF_MB3_deltaPhi_vs_trackType;
        delete h2_BMTF_MB4_deltaPhi_vs_trackType;
        
        delete h1_BMTF_mu_deltaPt;
        
        delete h1_BMTF_mu_deltaEta;
        delete h1_BMTF_mu_deltaPhi;
        delete h1_BMTF_mu_deltaR;
        
        delete h2_BMTF_mu_pT_vs_deltaR;
        
        delete h1_BMTF_muMatched_pT;
        delete h1_BMTF_muMatched_eta;
        delete h1_BMTF_muMatched_phi;
        
        delete h1_BMTF_muMatched_deltaEta;
        delete h1_BMTF_muMatched_deltaPhi;
        
        delete h1_BMTF_trackType;
        delete h1_BMTF_muMatched_trackType;
        
        delete h2_BMTF_muMatched_eta_vs_phi;
        delete h2_BMTF_muMatched_pT_vs_eta;
        delete h2_BMTF_muMatched_pT_vs_phi;
        delete h2_BMTF_muMatched_pT_vs_trackType;
        
        delete h2_BMTF_pT_resolution_vs_trackType;
        
        delete h1_BMTF_muMatched_MB34onlyMB3HO_pT;
        delete h1_BMTF_muMatched_MB34onlyMB3HO_eta;
        
        delete h2_BMTF_muMatched_MB34onlyMB3HO_pT_vs_eta;
        
        
        //
        delete h1_BMTF_muNotMatched_pT;
        delete h1_BMTF_muNotMatched_eta;
        delete h1_BMTF_muNotMatched_phi;
        
        delete h2_BMTF_muNotMatched_eta_vs_phi;
        delete h2_BMTF_muNotMatched_pT_vs_eta;
        delete h2_BMTF_muNotMatched_pT_vs_phi;
        
        
        //
        delete h1_MB1_BMTF_deltaPhi;
        
        
        //
        delete h1_MB1_isoType;
        
        
        //
        delete h2_MB_station_vs_wheel;
        delete h2_usedMB_station_vs_wheel;
        delete h2_unusedMB_station_vs_wheel;
        
        
        //
        delete h1_isoMB1HO_deltaIphi;
        
        delete h1_isoMB1HO_mu_deltaPt;
        delete h2_isoMB1HO_mu_pT_vs_deltaR;
        
        delete h1_isoMB1HO_muMatched_pT;
        delete h1_isoMB1HO_muMatched_eta;
        delete h1_isoMB1HO_muMatched_phi;
        
        delete h1_isoMB1HO_muNotMatched_3x3;
        
        delete h2_isoMB1HO_muMatched_eta_vs_phi;
        delete h2_isoMB1HO_muMatched_pT_vs_eta;
        delete h2_isoMB1HO_muMatched_pT_vs_phi;
        
        delete h2_isoMB1HO_muMatched_pT_vs_deltaIphi;
        
        
        //
        delete h1_isoMB1HO_muNotMatched_pT;
        delete h1_isoMB1HO_muNotMatched_eta;
        delete h1_isoMB1HO_muNotMatched_phi;
        
        delete h2_isoMB1HO_muNotMatched_eta_vs_phi;
        delete h2_isoMB1HO_muNotMatched_pT_vs_eta;
        delete h2_isoMB1HO_muNotMatched_pT_vs_phi;
        
        delete h2_isoMB1HO_nNotMuMatched_vs_nUnusedMu;
        
        
        //
        delete h1_MB34onlyBMTF_pT;
        delete h1_MB34onlyBMTF_eta;
        delete h1_MB34onlyBMTF_nearestHO_iEta;
        delete h1_MB34onlyBMTF_nearestHO_deltaR;
        delete h1_MB34onlyBMTFHO_pT;
        delete h1_MB34onlyBMTFHO_eta;
        
        delete h2_MB34onlyBMTF_nearestMB3_wh_vs_nearestHO_iEta;
        delete h2_MB34onlyBMTF_nearestMB4_wh_vs_nearestHO_iEta;
        
        delete h2_MB34onlyBMTF_matchedMu_pT_vs_nearestMB3nearestHO_deltaIphi;
        delete h2_MB34onlyBMTF_matchedMu_pT_vs_nearestMB4nearestHO_deltaIphi;
        
        delete h2_MB34onlyBMTF_matchedMu_ch_vs_nearestMB3nearestHO_deltaIphi;
        delete h2_MB34onlyBMTF_matchedMu_ch_vs_nearestMB4nearestHO_deltaIphi;
        
        
        //
        delete h1_test1;
        delete h1_test1a;
        
        delete h1_test2;
        delete h1_test2a;
        
        delete h1_test3;
        delete h1_test3a;
    }
};


void analyze(InputData_DTNtuple::InputData *input, OutputData *output, OutputData *output_LQ, OutputData *output_HQ);


int main()
{
    std::string process;
    char sourceFileList[500];
    
    process = "@process@";
    sprintf(sourceFileList, "@source@");
    
    //process = "SingleMuon_Run2017C-ZMu-PromptReco-v3_RAW-RECO";
    //process = "MET_Run2017C-v1_RAW";
    
    //sprintf(sourceFileList, "sourceFiles/%s/%s.txt", process.c_str(), process.c_str());
    
    printf("Source file list: %s \n", sourceFileList);
    
    // Read phiB vs. pT
    Common::parseCSV_pTlut("ptb12h_Feb2016.lut", &v_phiB_MB1, &v_pT_MB1);
    Common::parseCSV_pTlut("ptb21h_Feb2016.lut", &v_phiB_MB2, &v_pT_MB2);
    
    std::vector <std::string> v_sourceFileName = {};
    
    // Read source file list
    std::ifstream fileData(sourceFileList);
    std::string line;
    
    while(std::getline(fileData, line))
    {
        v_sourceFileName.push_back(line);
    }
    
    fileData.close();
    
    char outputDir[500];
    sprintf(outputDir, "output/%s", process.c_str());
    
    // Make output directory
    char command[500];
    sprintf(command, "mkdir -p %s", outputDir);
    system(command);
    
    int n = 0;
    // Analyze input files
    for(int iFile = 0; iFile < v_sourceFileName.size(); iFile++)
    {
        //n++; if(n > 500) break; 
        std::string inputFileName = v_sourceFileName.at(iFile);
        
        printf("Input file: %s \n", inputFileName.c_str());
        InputData_DTNtuple::InputData *input = new InputData_DTNtuple::InputData(inputFileName.c_str());
        
        char fileNameStripped[500];
        sprintf(fileNameStripped, "%s", \
            (inputFileName.substr(inputFileName.rfind("/")+1, inputFileName.rfind(".root")-inputFileName.rfind("/")-1)).c_str());
        
        char outputFileName[500];
        sprintf(outputFileName, "%s/%s_efficiency.root", outputDir, fileNameStripped);
        
        printf("Output file: %s \n", outputFileName);
        TFile *outputFile = TFile::Open(outputFileName, "RECREATE");
        
        OutputData *output = new OutputData();
        OutputData *output_LQ = new OutputData();
        OutputData *output_HQ = new OutputData();
        
        analyze(input, output, output_LQ, output_HQ);
        
        outputFile->cd();
        output->writeData();
        output->freeMemory();
        
        outputFile->mkdir("LQ");
        outputFile->cd("LQ");
        output_LQ->writeData();
        output_LQ->freeMemory();
        
        outputFile->mkdir("HQ");
        outputFile->cd("HQ");
        output_HQ->writeData();
        output_HQ->freeMemory();
        
        outputFile->Close();
        delete outputFile;
        
        delete output;
        delete output_LQ;
        delete output_HQ;
        
        input->freeMemory();
        delete input;
        
        printf("\n");
    }
    
    
    printf("***** Run complete ***** \n");
    
    return 0;
}


void analyze(InputData_DTNtuple::InputData *input, OutputData *output, OutputData *output_LQ, OutputData *output_HQ)
{
    int nEvent = input->tree->GetEntries();
    
    for(int iEvent = 0; iEvent < nEvent; iEvent++)
    {
        if((iEvent+1) % 1000 == 0 || iEvent+1 == nEvent)
        {
            printf("********** Event %d / %d ********** \n", iEvent+1, nEvent);
            
            fflush(stdout);
        }
        
        
        int entryStatus = input->tree->GetEntry(iEvent);
        
        OutputData *currentOutput = 0;
        
        int nDTseg = input->v_dtsegm4D_wheel->size();
        
        // Store best DT reco segment in each wh/st/sc
        /*std::vector <int> av_bestDTsegment_index[nWheel][nStation][nSector];
        //int a_bestDTsegment_nHit_phiLocal[nWheel][nStation][nSector];
        
        for(int iWheel = 0; iWheel < nWheel; iWheel++)
        {
            for(int iStation = 0; iStation < nStation; iStation++)
            {
                for(int iSector = 0; iSector < nSector; iSector++)
                {
                    av_bestDTsegment_index[iWheel][iStation][iSector] = {};
                    //a_bestDTsegment_nHit_phiLocal[iWheel][iStation][iSector] = 0;
                }
            }
        }
        
        OutputData *currentOutput = 0;
        
        
        
        for(int iDTsegment = 0; iDTsegment < nDTsegment; iDTsegment++)
        {
            int wheelNumber = input->v_dtsegm4D_wheel->at(iDTsegment);
            int stationNumber = input->v_dtsegm4D_station->at(iDTsegment);
            int sectorNumber = input->v_dtsegm4D_sector->at(iDTsegment);
            
            
            // MB4 sectors 4 (top) and 10 (bottom) are made up of two parts (divided vertically in the middle)
            // sector 4 is 4/1 and sector 13 is 4/2
            // sector 10 is 10/1 and sector 14 is 10/2
            sectorNumber = (sectorNumber > 12)? ((sectorNumber == 13)? 4: 10): sectorNumber;
            
            
            // Convert to array-index
            wheelNumber += 2;
            stationNumber--;
            sectorNumber--;
            
            int nHit_phiLocal = 0;
            int nHit_zLocal = 0;
            
            // Must have phi-projection, and if not MB4, then also z-projection
            if(input->v_dtsegm4D_hasPhi->at(iDTsegment) \
                && (input->v_dtsegm4D_hasZed->at(iDTsegment) || stationNumber+1 == 4))
            {
                nHit_phiLocal = input->v_dtsegm4D_phinhits->at(iDTsegment);
                
                double tan_phiLocal = input->v_dtsegm4D_x_dir_loc->at(iDTsegment) / input->v_dtsegm4D_z_dir_loc->at(iDTsegment);
                double phiLocal = atan(tan_phiLocal) * 180/M_PI;
                
                // Cut on the number of hits in an angular region
                if(nHit_phiLocal >= DTsegment_nHit_phiLocal_min && fabs(phiLocal) < DTsegment_phiLocal_max)
                {
                    av_bestDTsegment_index[wheelNumber][stationNumber][sectorNumber].push_back(iDTsegment);
                    
                    //if(nHit_phiLocal > a_bestDTsegment_nHit_phiLocal[wheelNumber][stationNumber][sectorNumber])
                    //{
                    //    a_bestDTsegment_index[wheelNumber][stationNumber][sectorNumber] = iDTsegment;
                    //    //a_bestDTsegment_nHit_phiLocal[wheelNumber][stationNumber][sectorNumber] = nHit_phiLocal;
                    //}
                }
            }
        }*/
        
        
        // select reco-muons
        std::vector <int> v_selectedMu_index_backup;
        std::vector <int> v_selectedMu_index;
        std::vector <double> v_selectedMu_pT;
        std::vector <double> v_selectedMu_eta;
        std::vector <double> v_selectedMu_phi;
        std::vector <double> v_selectedMu_etaMB1;
        std::vector <double> v_selectedMu_phiMB1;
        
        std::vector <bool> v_selectedMu_isMB1HOmatched;
        
        std::vector <bool> v_selectedMu_hasMB1;
        
        int nMuon = input->v_Mu_eta->size();
        
        for(int iMuon = 0; iMuon < nMuon; iMuon++)
        {
            // Muon must be Global and Tracker
            //if(!input->v_Mu_isMuGlobal->at(iMuon) || !input->v_Mu_isMuTracker->at(iMuon))
            //{
            //    continue;
            //}
            
            if(!muonWP.compare("loose"))
            {
                if(!input->v_Mu_isMuLoose->at(iMuon))
                {
                    continue;
                }
            }
            
            else if(!muonWP.compare("medium"))
            {
                if(!input->v_Mu_isMuMedium->at(iMuon))
                {
                    continue;
                }
            }
            
            else if(!muonWP.compare("tight"))
            {
                if(!input->v_Mu_isMuTight->at(iMuon))
                {
                    continue;
                }
            }
            
            else
            {
                printf("Wrong muon WP. \n");
                
                exit(EXIT_FAILURE);
            }
            
            double pT_iMuon = sqrt(pow(input->v_Mu_px->at(iMuon), 2) + pow(input->v_Mu_py->at(iMuon), 2));
            double eta_iMuon = input->v_Mu_eta->at(iMuon);
            double phi_iMuon = input->v_Mu_phi->at(iMuon);
            double etaMB1_iMuon = input->v_Mu_etaMB1->at(iMuon);
            double phiMB1_iMuon = input->v_Mu_phiMB1->at(iMuon);
            
            bool hasMB1_iMuon = false;
            
            // Check if extrapolations are valid
            if(fabs(etaMB1_iMuon) < 5 && fabs(phiMB1_iMuon) <= M_PI)
            {
                hasMB1_iMuon = true;
            }
            
            // An upper cut on pT (ONLY IF mu_pTcutUpr is +ve)
            if(mu_pTcutUpr > 0 && pT_iMuon > mu_pTcutUpr)
            {
                continue;
            }
            
            // Muon pT, eta cut
            if(hasMB1_iMuon)
            {
                if(pT_iMuon < mu_pTcut || fabs(etaMB1_iMuon) > mu_etaCut)
                {
                    continue;
                }
            }
            
            else
            {
                if(pT_iMuon < mu_pTcut || fabs(eta_iMuon) > mu_etaCut)
                {
                    continue;
                }
            }
            
            
            v_selectedMu_index.push_back(iMuon);
            v_selectedMu_index_backup.push_back(iMuon);
            
            v_selectedMu_pT.push_back(pT_iMuon);
            v_selectedMu_eta.push_back(eta_iMuon);
            v_selectedMu_phi.push_back(phi_iMuon);
            v_selectedMu_etaMB1.push_back(etaMB1_iMuon);
            v_selectedMu_phiMB1.push_back(phiMB1_iMuon);
            v_selectedMu_hasMB1.push_back(hasMB1_iMuon);
            
            v_selectedMu_isMB1HOmatched.push_back(false);
            
            // Fill reco-muon quantities
            output->h1_mu_pT->Fill(pT_iMuon);
            output->h1_mu_eta->Fill(eta_iMuon);
            output->h1_mu_phi->Fill(phi_iMuon);
            
            output->h2_mu_pT_vs_eta->Fill(eta_iMuon, pT_iMuon);
            output->h2_mu_pT_vs_phi->Fill(phi_iMuon, pT_iMuon);
            output->h2_mu_eta_vs_phi->Fill(phi_iMuon, eta_iMuon);
            
            int iEta_iMuon = Common::etaToIeta(eta_iMuon);
            int subIeta_iMuon = Common::etaToSubIeta(eta_iMuon, 2);
            
            if(abs(iEta_iMuon) <= 10)
            {
                // Run over LQ (0), HQ (1), LQ+HQ (2)
                for(int iQua = 0; iQua < 3; iQua++)
                {
                    if(iQua == 0)
                    {
                        currentOutput = output_LQ;
                    }
                    
                    else if(iQua == 1)
                    {
                        currentOutput = output_HQ;
                    }
                    
                    else
                    {
                        currentOutput = output;
                    }
                    
                    int stationMask_iMuon = 0;
                    
                    for(int iDTTP = 0; iDTTP < input->v_ltTwinMuxOut_bx->size(); iDTTP++)
                    {
                        int stNum_iDTTP = input->v_ltTwinMuxOut_station->at(iDTTP);
                        int whNum_iDTTP = input->v_ltTwinMuxOut_wheel->at(iDTTP);
                        int scNum_iDTTP = input->v_ltTwinMuxOut_sector->at(iDTTP);
                        
                        int bx_iDTTP = input->v_ltTwinMuxOut_bx->at(iDTTP);
                        
                        if(bx_iDTTP != 0)
                        {
                            continue;
                        }
                        
                        // Exclude wheels +-2 of MB1
                        // They are already supported by the CSC
                        //if(abs(whNum_iDTTP) == 2)
                        //{
                        //    continue;
                        //}
                        
                        //double pT_iDTTP = Common::getPtFromPhiB((int) input->v_ltTwinMuxOut_phiB->at(iDTTP), &v_phiB_MB1, &v_pT_MB1);
                        //
                        //if(pT_iDTTP < MB1_pTcut)
                        //{
                        //    continue;
                        //}
                        
                        double phi_iDTTP = Common::globalPhiFromDTphi(input->v_ltTwinMuxOut_phi->at(iDTTP), scNum_iDTTP);
                        
                        int quality = input->v_ltTwinMuxOut_quality->at(iDTTP);
                        
                        bool isLQ = quality > 0 && quality < 4;
                        bool isHQ = quality > 3 && quality < 7;
                        
                        // Check DTTP quality
                        if(!isLQ && !isHQ)
                        {
                            continue;
                        }
                        
                        //if(!isHQ)
                        //{
                        //    continue;
                        //}
                        
                        if(iQua == 0 && isHQ)
                        {
                            continue;
                        }
                        
                        else if(iQua == 1 && isLQ)
                        {
                            continue;
                        }
                        
                        
                        double deltaPhi = phi_iMuon - phi_iDTTP;
                        deltaPhi = (deltaPhi > M_PI)? (deltaPhi-2*M_PI): deltaPhi;
                        deltaPhi = (deltaPhi < -M_PI)? (deltaPhi+2*M_PI): deltaPhi;
                        
                        if(fabs(deltaPhi) < 0.1)
                        {
                            stationMask_iMuon |= (1<<(stNum_iDTTP-1));
                            
                            currentOutput->h1_test1->Fill((abs(iEta_iMuon)-1)*6 + stNum_iDTTP);
                            currentOutput->h1_test1a->Fill((abs(iEta_iMuon)-1)*2*6 + (subIeta_iMuon-1)*6 + stNum_iDTTP);
                        }
                    }
                    
                    currentOutput->h1_test2->Fill((abs(iEta_iMuon)-1)*20 + stationMask_iMuon);
                    currentOutput->h1_test2a->Fill((abs(iEta_iMuon)-1)*2*20 + (subIeta_iMuon-1)*20 + stationMask_iMuon);
                    
                    for(int iStation = 0; iStation < 4; iStation++)
                    {
                        if(!(stationMask_iMuon & (1<<iStation)))
                        {
                            currentOutput->h1_test3->Fill(iStation*15 + abs(iEta_iMuon));
                            currentOutput->h1_test3a->Fill(iStation*25 + abs(iEta_iMuon)*2 + subIeta_iMuon-2);
                        }
                    }
                }
            }
        }
        
        output->h1_mu_n->Fill(v_selectedMu_index.size());
        
        
        currentOutput = 0;
        
        // At least 1 reco-muon in the event
        // PROBABLY need to deactivate this for correct fake estimate
        if(!v_selectedMu_index.size())
        {
            printf("No reco-muon in the event. \n");
            continue;
        }
        
        
        int nDTTP = input->v_ltTwinMuxOut_bx->size();
        int nBMTF = input->v_bmtf_wheel->size();
        
        
        // Store the nearest DTTP for each BMTF
        std::vector <int> v_DTTP_BMTFindex(nDTTP, -1);
        std::vector <std::vector <int> > vv_BMTF_DTTPindex(nBMTF, {-1, -1, -1, -1});
        std::vector <std::vector <double> > vv_BMTF_DTTP_deltaPhi(nBMTF, {9999, 9999, 9999, 9999});
        
        for(int iBMTF = 0; iBMTF < nBMTF; iBMTF++)
        {
            int bx_iBMTF = input->v_bmtf_bx->at(iBMTF);
            
            if(bx_iBMTF != 0)
            {
                continue;
            }
            
            double phi_iBMTF = Common::bmtfGlobalPhiToCmsPhi(input->v_bmtf_globalPhi->at(iBMTF));
            
            int trAdd_iBMTF_MB1 = input->v_bmtf_trAddress->at(4*iBMTF + 0);
            int trAdd_iBMTF_MB2 = input->v_bmtf_trAddress->at(4*iBMTF + 1);
            int trAdd_iBMTF_MB3 = input->v_bmtf_trAddress->at(4*iBMTF + 2);
            int trAdd_iBMTF_MB4 = input->v_bmtf_trAddress->at(4*iBMTF + 3);
            
            // {index, deltaPhi}
            std::pair <int, double> p_nearestDTTP_info(-1, 9999);
            
            int trackType_BMTF = Common::getBMTFstationMask(trAdd_iBMTF_MB1, trAdd_iBMTF_MB2, trAdd_iBMTF_MB3, trAdd_iBMTF_MB4);
            
            for(int iSt = 1; iSt <= 4; iSt++)
            {
                if(iSt == 1 && trAdd_iBMTF_MB1 == 3)
                {
                    continue;
                }
                
                if(iSt == 2 && trAdd_iBMTF_MB2 == 15)
                {
                    continue;
                }
                
                if(iSt == 3 && trAdd_iBMTF_MB3 == 15)
                {
                    continue;
                }
                
                if(iSt == 4 && trAdd_iBMTF_MB4 == 15)
                {
                    continue;
                }
                
                p_nearestDTTP_info = Common::getNearestDTTPtoBMTF(
                    phi_iBMTF, iSt,
                    input->v_ltTwinMuxOut_bx,
                    input->v_ltTwinMuxOut_station,
                    input->v_ltTwinMuxOut_wheel,
                    input->v_ltTwinMuxOut_sector,
                    input->v_ltTwinMuxOut_phi,
                    &v_DTTP_BMTFindex
                );
                
                if(p_nearestDTTP_info.first >= 0)// && fabs(p_nearestDTTP_info.second) < 0.4)
                {
                    v_DTTP_BMTFindex.at(p_nearestDTTP_info.first) = iBMTF;
                    
                    vv_BMTF_DTTPindex.at(iBMTF).at(iSt-1) = p_nearestDTTP_info.first;
                    vv_BMTF_DTTP_deltaPhi.at(iBMTF).at(iSt-1) = p_nearestDTTP_info.second;
                }
            }
            
            printf("event %d: BMTF %d, trAdd %d %d %d %d, MB %d%d%d%d, DTTP %d %d %d %d, dPhi %0.2f %0.2f %0.2f %0.2f, nDTTP %d, nBMTF %d, pT %0.2f \n",
                iEvent, iBMTF,
                trAdd_iBMTF_MB1, trAdd_iBMTF_MB2, trAdd_iBMTF_MB3, trAdd_iBMTF_MB4,
                trAdd_iBMTF_MB1 != 3, trAdd_iBMTF_MB2 != 15, trAdd_iBMTF_MB3 != 15, trAdd_iBMTF_MB4 != 15,
                vv_BMTF_DTTPindex.at(iBMTF).at(0), vv_BMTF_DTTPindex.at(iBMTF).at(1), vv_BMTF_DTTPindex.at(iBMTF).at(2), vv_BMTF_DTTPindex.at(iBMTF).at(3),
                vv_BMTF_DTTP_deltaPhi.at(iBMTF).at(0), vv_BMTF_DTTP_deltaPhi.at(iBMTF).at(1), vv_BMTF_DTTP_deltaPhi.at(iBMTF).at(2), vv_BMTF_DTTP_deltaPhi.at(iBMTF).at(3),
                nDTTP, nBMTF, input->v_bmtf_pT->at(iBMTF)
            );
            
            if(trAdd_iBMTF_MB1 != 3)
            {
                output->h1_BMTF_MB1_deltaPhi->Fill(vv_BMTF_DTTP_deltaPhi.at(iBMTF).at(0));
                output->h2_BMTF_MB1_deltaPhi_vs_trackType->Fill(0.0, vv_BMTF_DTTP_deltaPhi.at(iBMTF).at(0));
                output->h2_BMTF_MB1_deltaPhi_vs_trackType->Fill(trackType_BMTF, vv_BMTF_DTTP_deltaPhi.at(iBMTF).at(0));
            }
            
            if(trAdd_iBMTF_MB2 != 15)
            {
                output->h1_BMTF_MB2_deltaPhi->Fill(vv_BMTF_DTTP_deltaPhi.at(iBMTF).at(1));
                output->h2_BMTF_MB2_deltaPhi_vs_trackType->Fill(0.0, vv_BMTF_DTTP_deltaPhi.at(iBMTF).at(1));
                output->h2_BMTF_MB2_deltaPhi_vs_trackType->Fill(trackType_BMTF, vv_BMTF_DTTP_deltaPhi.at(iBMTF).at(1));
            }
            
            if(trAdd_iBMTF_MB3 != 15)
            {
                output->h1_BMTF_MB3_deltaPhi->Fill(vv_BMTF_DTTP_deltaPhi.at(iBMTF).at(2));
                output->h2_BMTF_MB3_deltaPhi_vs_trackType->Fill(0.0, vv_BMTF_DTTP_deltaPhi.at(iBMTF).at(2));
                output->h2_BMTF_MB3_deltaPhi_vs_trackType->Fill(trackType_BMTF, vv_BMTF_DTTP_deltaPhi.at(iBMTF).at(2));
            }
            
            if(trAdd_iBMTF_MB4 != 15)
            {
                output->h1_BMTF_MB4_deltaPhi->Fill(vv_BMTF_DTTP_deltaPhi.at(iBMTF).at(3));
                output->h2_BMTF_MB4_deltaPhi_vs_trackType->Fill(0.0, vv_BMTF_DTTP_deltaPhi.at(iBMTF).at(3));
                output->h2_BMTF_MB4_deltaPhi_vs_trackType->Fill(trackType_BMTF, vv_BMTF_DTTP_deltaPhi.at(iBMTF).at(3));
            }
        }
        
        
        // used and unused DTTP
        currentOutput = 0;
        
        for(int iDTTP = 0; iDTTP < nDTTP; iDTTP++)
        {
            int stNum_iDTTP = input->v_ltTwinMuxOut_station->at(iDTTP);
            int whNum_iDTTP = input->v_ltTwinMuxOut_wheel->at(iDTTP);
            int scNum_iDTTP = input->v_ltTwinMuxOut_sector->at(iDTTP);
            
            int bx_iDTTP = input->v_ltTwinMuxOut_bx->at(iDTTP);
            
            if(bx_iDTTP != 0)
            {
                continue;
            }
            
            int quality = input->v_ltTwinMuxOut_quality->at(iDTTP);
            
            bool isLQ = quality > 0 && quality < 4;
            bool isHQ = quality > 3 && quality < 7;
            
            if(isHQ)
            {
                currentOutput = output_HQ;
            }
            
            else
            {
                currentOutput = output_LQ;
            }
            
            output->h2_MB_station_vs_wheel->Fill(whNum_iDTTP, stNum_iDTTP);
            currentOutput->h2_MB_station_vs_wheel->Fill(whNum_iDTTP, stNum_iDTTP);
            
            if(v_DTTP_BMTFindex.at(iDTTP) >= 0)
            {
                output->h2_usedMB_station_vs_wheel->Fill(whNum_iDTTP, stNum_iDTTP);
                currentOutput->h2_usedMB_station_vs_wheel->Fill(whNum_iDTTP, stNum_iDTTP);
            }
            
            else
            {
                output->h2_unusedMB_station_vs_wheel->Fill(whNum_iDTTP, stNum_iDTTP);
                currentOutput->h2_unusedMB_station_vs_wheel->Fill(whNum_iDTTP, stNum_iDTTP);
            }
        }
        
        
        // BMTF
        std::vector <bool> v_bmtf_isSelected(nBMTF, false);
        std::vector <bool> v_bmtf_isMuMatched(nBMTF, false);
        std::vector <bool> v_bmtf_isMB34only(nBMTF, false);
        
        int nHOTP = input->v_hoTPdigi_bits->size();
        
        std::vector <bool> v_HOTP_MB34onlyMatched(nHOTP, false);
        
        for(int iBMTF = 0; iBMTF < nBMTF; iBMTF++)
        {
            int selectedMu_BMTFmatched_index = -1;
            double deltaR_min = 9999;
            
            double pT_iBMTF = input->v_bmtf_pT->at(iBMTF);
            double eta_iBMTF = input->v_bmtf_eta->at(iBMTF);
            double phi_iBMTF = Common::bmtfGlobalPhiToCmsPhi(input->v_bmtf_globalPhi->at(iBMTF));
            
            int bx_iBMTF = input->v_bmtf_bx->at(iBMTF);
            
            if(bx_iBMTF != 0)
            {
                continue;
            }
            
            // BMTF pT, eta cut
            if(pT_iBMTF < BMTF_pTcut || fabs(eta_iBMTF) > BMTF_etaCut)
            {
                continue;
            }
            
            v_bmtf_isSelected.at(iBMTF) = true;
            
            // Get BMTF track type
            int trAdd_iBMTF_MB1 = input->v_bmtf_trAddress->at(4*iBMTF + 0);
            int trAdd_iBMTF_MB2 = input->v_bmtf_trAddress->at(4*iBMTF + 1);
            int trAdd_iBMTF_MB3 = input->v_bmtf_trAddress->at(4*iBMTF + 2);
            int trAdd_iBMTF_MB4 = input->v_bmtf_trAddress->at(4*iBMTF + 3);
            
            int stationMask_iBMTF = Common::getBMTFstationMask(trAdd_iBMTF_MB1, trAdd_iBMTF_MB2, trAdd_iBMTF_MB3, trAdd_iBMTF_MB4);
            output->h1_BMTF_trackType->Fill(stationMask_iBMTF);
            output->h1_BMTF_trackType->Fill(0);
            
            for(int iMuon = 0; iMuon < v_selectedMu_index.size(); iMuon++)
            {
                int muon_pos = v_selectedMu_index.at(iMuon);
                
                //if(!input->v_Mu_isMuTight->at(muon_pos))
                //{
                //    continue;
                //}
                
                if(muon_pos < 0)
                {
                    continue;
                }
                
                double eta_iMuon = v_selectedMu_eta.at(iMuon);//input->v_Mu_eta->at(muon_pos);
                double phi_iMuon = v_selectedMu_phi.at(iMuon);//input->v_Mu_phi->at(muon_pos);
                
                if(v_selectedMu_hasMB1.at(iMuon))
                {
                    eta_iMuon = v_selectedMu_etaMB1.at(iMuon);
                    phi_iMuon = v_selectedMu_phiMB1.at(iMuon);
                }
                
                double deltaEta = eta_iBMTF - eta_iMuon;
                
                double deltaPhi = phi_iBMTF - phi_iMuon;
                deltaPhi = (deltaPhi > M_PI)? (deltaPhi-2*M_PI): deltaPhi;
                deltaPhi = (deltaPhi < -M_PI)? (deltaPhi+2*M_PI): deltaPhi;
                
                double deltaR = sqrt(deltaEta*deltaEta + deltaPhi*deltaPhi);
                
                if(deltaR < deltaR_min)
                {
                    deltaR_min = deltaR;
                    selectedMu_BMTFmatched_index = iMuon;
                }
            }
            
            output->h1_BMTF_mu_deltaR->Fill(deltaR_min);
            
            if(selectedMu_BMTFmatched_index >= 0 && v_selectedMu_hasMB1.at(selectedMu_BMTFmatched_index))
            {
                double MB1extDeltaEta = input->v_Mu_eta->at(v_selectedMu_index.at(selectedMu_BMTFmatched_index)) - v_selectedMu_etaMB1.at(selectedMu_BMTFmatched_index);
                
                double MB1extDeltaPhi = input->v_Mu_phi->at(v_selectedMu_index.at(selectedMu_BMTFmatched_index)) - v_selectedMu_phiMB1.at(selectedMu_BMTFmatched_index);
                MB1extDeltaPhi = (MB1extDeltaPhi > M_PI)? (MB1extDeltaPhi-2*M_PI): MB1extDeltaPhi;
                MB1extDeltaPhi = (MB1extDeltaPhi < -M_PI)? (MB1extDeltaPhi+2*M_PI): MB1extDeltaPhi;
                
                output->h2_mu_pT_vs_MB1extDeltaEta->Fill(MB1extDeltaEta, v_selectedMu_pT.at(selectedMu_BMTFmatched_index));
                output->h2_mu_pT_vs_MB1extDeltaPhi->Fill(MB1extDeltaPhi, v_selectedMu_pT.at(selectedMu_BMTFmatched_index));
                
                output->h2_BMTF_mu_pT_vs_deltaR->Fill(deltaR_min, v_selectedMu_pT.at(selectedMu_BMTFmatched_index));
            }
            
            // Fill BMTF quantities if mu-matched
            if(deltaR_min < muBMTF_deltaRcut)
            {
                v_bmtf_isMuMatched.at(iBMTF) = true;
                
                double pT_resolution_iBMTF = pT_iBMTF / v_selectedMu_pT.at(selectedMu_BMTFmatched_index);
                
                output->h1_BMTF_mu_deltaPt->Fill(pT_iBMTF - v_selectedMu_pT.at(selectedMu_BMTFmatched_index));
                
                output->h1_BMTF_muMatched_pT->Fill(v_selectedMu_pT.at(selectedMu_BMTFmatched_index));//pT_iBMTF);
                output->h1_BMTF_muMatched_eta->Fill(v_selectedMu_eta.at(selectedMu_BMTFmatched_index));//eta_iBMTF);
                output->h1_BMTF_muMatched_phi->Fill(v_selectedMu_phi.at(selectedMu_BMTFmatched_index));//phi_iBMTF);
                
                output->h1_BMTF_muMatched_deltaEta->Fill(eta_iBMTF - v_selectedMu_eta.at(selectedMu_BMTFmatched_index));
                
                double deltaPhi = phi_iBMTF - v_selectedMu_phi.at(selectedMu_BMTFmatched_index);
                deltaPhi = (deltaPhi > M_PI)? (deltaPhi-2*M_PI): deltaPhi;
                deltaPhi = (deltaPhi < -M_PI)? (deltaPhi+2*M_PI): deltaPhi;
                output->h1_BMTF_muMatched_deltaPhi->Fill(deltaPhi);
                
                output->h2_BMTF_muMatched_pT_vs_eta->Fill(v_selectedMu_eta.at(selectedMu_BMTFmatched_index), v_selectedMu_pT.at(selectedMu_BMTFmatched_index));
                output->h2_BMTF_muMatched_pT_vs_phi->Fill(v_selectedMu_phi.at(selectedMu_BMTFmatched_index), v_selectedMu_pT.at(selectedMu_BMTFmatched_index));
                output->h2_BMTF_muMatched_eta_vs_phi->Fill(v_selectedMu_phi.at(selectedMu_BMTFmatched_index), v_selectedMu_eta.at(selectedMu_BMTFmatched_index));
                
                
                output->h1_BMTF_muMatched_trackType->Fill(stationMask_iBMTF);
                output->h1_BMTF_muMatched_trackType->Fill(0);
                
                output->h2_BMTF_muMatched_pT_vs_trackType->Fill(stationMask_iBMTF, v_selectedMu_pT.at(selectedMu_BMTFmatched_index));
                output->h2_BMTF_muMatched_pT_vs_trackType->Fill(0.0, v_selectedMu_pT.at(selectedMu_BMTFmatched_index));
                
                output->h2_BMTF_pT_resolution_vs_trackType->Fill(stationMask_iBMTF, pT_resolution_iBMTF);
                output->h2_BMTF_pT_resolution_vs_trackType->Fill(0.0, pT_resolution_iBMTF);
                
                // MB34 only BMTF tracks
                if(trAdd_iBMTF_MB1 == 3 && trAdd_iBMTF_MB2 == 15 && trAdd_iBMTF_MB3 != 15 && trAdd_iBMTF_MB4 != 15)
                {
                    v_bmtf_isMB34only.at(iBMTF) = true;
                    
                    output->h1_MB34onlyBMTF_pT->Fill(v_selectedMu_pT.at(selectedMu_BMTFmatched_index));
                    output->h1_MB34onlyBMTF_eta->Fill(v_selectedMu_eta.at(selectedMu_BMTFmatched_index));
                    
                    // Find nearest HO to MB34only BMTF
                    int MB34onlyBMTF_nearestHO_index = -1;
                    double MB34onlyBMTF_nearestHO_deltaR = 9999;
                    
                    for(int iHOTP = 0; iHOTP < nHOTP; iHOTP++)
                    {
                        // HOTP at SOI only
                        if(input->v_hoTPdigi_bits->at(iHOTP) != HOTP_bits_SOI)
                        {
                            continue;
                        }
                        
                        if(v_HOTP_MB34onlyMatched.at(iHOTP))
                        {
                            continue;
                        }
                        
                        double phi_iHOTP = Common::HOiPhiToPhi(input->v_hoTPdigi_iPhi->at(iHOTP));
                        double eta_iHOTP = Common::HOiEtaToEta(input->v_hoTPdigi_iEta->at(iHOTP));
                        
                        double deltaPhi = phi_iHOTP - phi_iBMTF;
                        deltaPhi = (deltaPhi > M_PI)? (deltaPhi-2*M_PI): deltaPhi;
                        deltaPhi = (deltaPhi < -M_PI)? (deltaPhi+2*M_PI): deltaPhi;
                        
                        double deltaEta = eta_iHOTP - eta_iBMTF;
                        
                        double deltaR = sqrt(deltaEta*deltaEta + deltaPhi*deltaPhi);
                        
                        if(deltaR < MB34onlyBMTF_nearestHO_deltaR)
                        {
                            MB34onlyBMTF_nearestHO_deltaR = deltaR;
                            MB34onlyBMTF_nearestHO_index = iHOTP;
                        }
                    }
                    
                    
                    // If an HOTP is found for MB34only BMTF track
                    if(MB34onlyBMTF_nearestHO_index >= 0)
                    {
                        int MB34onlyBMTF_nearestHO_iEta = input->v_hoTPdigi_iEta->at(MB34onlyBMTF_nearestHO_index);
                        int MB34onlyBMTF_nearestHO_iPhi = input->v_hoTPdigi_iPhi->at(MB34onlyBMTF_nearestHO_index);
                        
                        v_HOTP_MB34onlyMatched.at(MB34onlyBMTF_nearestHO_index) = true;
                        
                        output->h1_MB34onlyBMTF_nearestHO_iEta->Fill(MB34onlyBMTF_nearestHO_iEta);
                        output->h1_MB34onlyBMTF_nearestHO_deltaR->Fill(MB34onlyBMTF_nearestHO_deltaR);
                        
                        
                        // 
                        if(MB34onlyBMTF_nearestHO_deltaR < MB34onlyBMTF_HO_deltaRcut
                            && abs(MB34onlyBMTF_nearestHO_iEta) <= 10)
                        {
                            // Run over LQ (0), HQ (1), LQ+HQ (2)
                            for(int iQua = 0; iQua < 3; iQua++)
                            {
                                if(iQua == 0)
                                {
                                    currentOutput = output_LQ;
                                }
                                
                                else if(iQua == 1)
                                {
                                    currentOutput = output_HQ;
                                }
                                
                                else
                                {
                                    currentOutput = output;
                                }
                                
                                int MB34onlyBMTF_nearestMB3_index = -1;
                                double MB34onlyBMTF_nearestMB3_deltaPhi = 9999;
                                
                                int MB34onlyBMTF_nearestMB4_index = -1;
                                double MB34onlyBMTF_nearestMB4_deltaPhi = 9999;
                                
                                std::vector <bool> v_DTTP_MB34onlyMatched(nDTTP, false);
                                
                                for(int iDTTP = 0; iDTTP < nDTTP; iDTTP++)
                                {
                                    int stNum_iDTTP = input->v_ltTwinMuxOut_station->at(iDTTP);
                                    int whNum_iDTTP = input->v_ltTwinMuxOut_wheel->at(iDTTP);
                                    int scNum_iDTTP = input->v_ltTwinMuxOut_sector->at(iDTTP);
                                    
                                    int bx_iDTTP = input->v_ltTwinMuxOut_bx->at(iDTTP);
                                    
                                    if(bx_iDTTP != 0)
                                    {
                                        continue;
                                    }
                                    
                                    // MB3 and MB4 only
                                    if(stNum_iDTTP != 3 && stNum_iDTTP != 4)
                                    {
                                        continue;
                                    }
                                    
                                    // Some geometrical matchings
                                    if(!Common::isEtaMatched_MB34HO(MB34onlyBMTF_nearestHO_iEta, whNum_iDTTP, stNum_iDTTP))
                                    {
                                        continue;
                                    }
                                    
                                    double phi_iDTTP = Common::globalPhiFromDTphi(input->v_ltTwinMuxOut_phi->at(iDTTP), scNum_iDTTP);
                                    
                                    int quality = input->v_ltTwinMuxOut_quality->at(iDTTP);
                                    
                                    bool isLQ = quality > 0 && quality < 4;
                                    bool isHQ = quality > 3 && quality < 7;
                                    
                                    // Check DTTP quality
                                    if(!isLQ && !isHQ)
                                    {
                                        continue;
                                    }
                                    
                                    if(iQua == 0 && isHQ)
                                    {
                                        continue;
                                    }
                                    
                                    else if(iQua == 1 && isLQ)
                                    {
                                        continue;
                                    }
                                    
                                    
                                    double deltaPhi = phi_iDTTP - phi_iBMTF;
                                    
                                    if(stNum_iDTTP == 3 && fabs(deltaPhi) < fabs(MB34onlyBMTF_nearestMB3_deltaPhi))
                                    {
                                        MB34onlyBMTF_nearestMB3_index = iDTTP;
                                        MB34onlyBMTF_nearestMB3_deltaPhi = deltaPhi;
                                    }
                                    
                                    if(stNum_iDTTP == 4 && fabs(deltaPhi) < fabs(MB34onlyBMTF_nearestMB4_deltaPhi))
                                    {
                                        MB34onlyBMTF_nearestMB4_index = iDTTP;
                                        MB34onlyBMTF_nearestMB4_deltaPhi = deltaPhi;
                                    }
                                }
                                
                                int deltaIphi_MB3HO = 9999;
                                int deltaIphi_MB4HO = 9999;
                                
                                // If MB3TP is found
                                if(MB34onlyBMTF_nearestMB3_index >= 0)
                                {
                                    v_DTTP_MB34onlyMatched.at(MB34onlyBMTF_nearestMB3_index) = true;
                                    
                                    currentOutput->h2_MB34onlyBMTF_nearestMB3_wh_vs_nearestHO_iEta->Fill(
                                        MB34onlyBMTF_nearestHO_iEta,
                                        input->v_ltTwinMuxOut_wheel->at(MB34onlyBMTF_nearestMB3_index));
                                    
                                    deltaIphi_MB3HO = MB34onlyBMTF_nearestHO_iPhi - input->v_ltTwinMuxOut_iPhi->at(MB34onlyBMTF_nearestMB3_index);
                                    deltaIphi_MB3HO = (deltaIphi_MB3HO > 36)? (deltaIphi_MB3HO-72): deltaIphi_MB3HO;
                                    deltaIphi_MB3HO = (deltaIphi_MB3HO < -36)? (deltaIphi_MB3HO+72): deltaIphi_MB3HO;
                                    
                                    currentOutput->h2_MB34onlyBMTF_matchedMu_pT_vs_nearestMB3nearestHO_deltaIphi->Fill(
                                        deltaIphi_MB3HO, v_selectedMu_pT.at(selectedMu_BMTFmatched_index));
                                    
                                    currentOutput->h2_MB34onlyBMTF_matchedMu_ch_vs_nearestMB3nearestHO_deltaIphi->Fill(
                                        deltaIphi_MB3HO, input->v_Mu_charge->at(v_selectedMu_index.at(selectedMu_BMTFmatched_index)));
                                    
                                    if(deltaIphi_MB3HO == 0)
                                    {
                                        currentOutput->h1_MB34onlyBMTFHO_pT->Fill(v_selectedMu_pT.at(selectedMu_BMTFmatched_index));
                                        currentOutput->h1_MB34onlyBMTFHO_eta->Fill(v_selectedMu_eta.at(selectedMu_BMTFmatched_index));
                                        
                                        currentOutput->h1_BMTF_muMatched_trackType->AddBinContent(20);
                                        currentOutput->h2_BMTF_muMatched_pT_vs_trackType->Fill(20-1, v_selectedMu_pT.at(selectedMu_BMTFmatched_index));
                                        
                                        currentOutput->h2_BMTF_pT_resolution_vs_trackType->Fill(20-1, pT_resolution_iBMTF);
                                        
                                        currentOutput->h1_BMTF_muMatched_MB34onlyMB3HO_pT->Fill(v_selectedMu_pT.at(selectedMu_BMTFmatched_index));
                                        currentOutput->h1_BMTF_muMatched_MB34onlyMB3HO_eta->Fill(v_selectedMu_eta.at(selectedMu_BMTFmatched_index));
                                        currentOutput->h2_BMTF_muMatched_MB34onlyMB3HO_pT_vs_eta->Fill(
                                            v_selectedMu_eta.at(selectedMu_BMTFmatched_index), v_selectedMu_pT.at(selectedMu_BMTFmatched_index));
                                    }
                                }
                                
                                // If MB4TP is found
                                if(MB34onlyBMTF_nearestMB4_index >= 0)
                                {
                                    v_DTTP_MB34onlyMatched.at(MB34onlyBMTF_nearestMB4_index) = true;
                                    
                                    currentOutput->h2_MB34onlyBMTF_nearestMB4_wh_vs_nearestHO_iEta->Fill(
                                        MB34onlyBMTF_nearestHO_iEta,
                                        input->v_ltTwinMuxOut_wheel->at(MB34onlyBMTF_nearestMB4_index));
                                    
                                    deltaIphi_MB4HO = MB34onlyBMTF_nearestHO_iPhi - input->v_ltTwinMuxOut_iPhi->at(MB34onlyBMTF_nearestMB4_index);
                                    deltaIphi_MB4HO = (deltaIphi_MB4HO > 36)? (deltaIphi_MB4HO-72): deltaIphi_MB4HO;
                                    deltaIphi_MB4HO = (deltaIphi_MB4HO < -36)? (deltaIphi_MB4HO+72): deltaIphi_MB4HO;
                                    
                                    currentOutput->h2_MB34onlyBMTF_matchedMu_pT_vs_nearestMB4nearestHO_deltaIphi->Fill(
                                        deltaIphi_MB4HO, v_selectedMu_pT.at(selectedMu_BMTFmatched_index));
                                    
                                    currentOutput->h2_MB34onlyBMTF_matchedMu_ch_vs_nearestMB4nearestHO_deltaIphi->Fill(
                                        deltaIphi_MB4HO, input->v_Mu_charge->at(v_selectedMu_index.at(selectedMu_BMTFmatched_index)));
                                    
                                    if(deltaIphi_MB4HO == 0)
                                    {
                                        currentOutput->h1_BMTF_muMatched_trackType->AddBinContent(21);
                                        currentOutput->h2_BMTF_muMatched_pT_vs_trackType->Fill(21-1, v_selectedMu_pT.at(selectedMu_BMTFmatched_index));
                                        
                                        currentOutput->h2_BMTF_pT_resolution_vs_trackType->Fill(21-1, pT_resolution_iBMTF);
                                    }
                                }
                                
                                
                                if(deltaIphi_MB3HO == 0 && deltaIphi_MB4HO == 0)
                                {
                                    currentOutput->h1_BMTF_muMatched_trackType->AddBinContent(22);
                                    currentOutput->h2_BMTF_muMatched_pT_vs_trackType->Fill(22-1, v_selectedMu_pT.at(selectedMu_BMTFmatched_index));
                                    
                                    currentOutput->h2_BMTF_pT_resolution_vs_trackType->Fill(22-1, pT_resolution_iBMTF);
                                }
                            }
                        }
                        
                        else
                        {
                            output->h1_BMTF_muMatched_trackType->AddBinContent(23);
                            output->h2_BMTF_muMatched_pT_vs_trackType->Fill(23-1, v_selectedMu_pT.at(selectedMu_BMTFmatched_index));
                            
                            output->h2_BMTF_pT_resolution_vs_trackType->Fill(23-1, pT_resolution_iBMTF);
                            
                            output->h1_BMTF_muMatched_MB34onlyMB3HO_pT->Fill(v_selectedMu_pT.at(selectedMu_BMTFmatched_index));
                            output->h1_BMTF_muMatched_MB34onlyMB3HO_eta->Fill(v_selectedMu_eta.at(selectedMu_BMTFmatched_index));
                            output->h2_BMTF_muMatched_MB34onlyMB3HO_pT_vs_eta->Fill(
                                v_selectedMu_eta.at(selectedMu_BMTFmatched_index), v_selectedMu_pT.at(selectedMu_BMTFmatched_index));
                        }
                    }
                    
                    else
                    {
                        output->h1_BMTF_muMatched_trackType->AddBinContent(23);
                        output->h2_BMTF_muMatched_pT_vs_trackType->Fill(23-1, v_selectedMu_pT.at(selectedMu_BMTFmatched_index));
                        
                        output->h2_BMTF_pT_resolution_vs_trackType->Fill(23-1, pT_resolution_iBMTF);
                        
                        output->h1_BMTF_muMatched_MB34onlyMB3HO_pT->Fill(v_selectedMu_pT.at(selectedMu_BMTFmatched_index));
                        output->h1_BMTF_muMatched_MB34onlyMB3HO_eta->Fill(v_selectedMu_eta.at(selectedMu_BMTFmatched_index));
                        output->h2_BMTF_muMatched_MB34onlyMB3HO_pT_vs_eta->Fill(
                            v_selectedMu_eta.at(selectedMu_BMTFmatched_index), v_selectedMu_pT.at(selectedMu_BMTFmatched_index));
                    }
                }
                
                else
                {
                    output->h1_BMTF_muMatched_MB34onlyMB3HO_pT->Fill(v_selectedMu_pT.at(selectedMu_BMTFmatched_index));
                    output->h1_BMTF_muMatched_MB34onlyMB3HO_eta->Fill(v_selectedMu_eta.at(selectedMu_BMTFmatched_index));
                    output->h2_BMTF_muMatched_MB34onlyMB3HO_pT_vs_eta->Fill(
                        v_selectedMu_eta.at(selectedMu_BMTFmatched_index), v_selectedMu_pT.at(selectedMu_BMTFmatched_index));
                }
                
                
                // Block the matched muon
                if(selectedMu_BMTFmatched_index >= 0)
                {
                    v_selectedMu_index.at(selectedMu_BMTFmatched_index) = -1;
                }
            }
            
            // Fill BMTF quantities if not mu-matched
            else
            {
                output->h1_BMTF_muNotMatched_pT->Fill(pT_iBMTF);
                output->h1_BMTF_muNotMatched_eta->Fill(eta_iBMTF);
                output->h1_BMTF_muNotMatched_phi->Fill(phi_iBMTF);
                
                output->h2_BMTF_muNotMatched_pT_vs_eta->Fill(eta_iBMTF, pT_iBMTF);
                output->h2_BMTF_muNotMatched_pT_vs_phi->Fill(phi_iBMTF, pT_iBMTF);
                output->h2_BMTF_muNotMatched_eta_vs_phi->Fill(phi_iBMTF, eta_iBMTF);
            }
        }
        
        
        std::vector <int> v_HOTP_isUsed(input->v_hoTPdigi_bits->size(), 0);
        std::vector <int> v_DTTP_isUsed(input->v_ltTwinMuxOut_bx->size(), 0);
        std::vector <int> v_BMTF_isUsed(nBMTF, 0);
        
        int isoMB1HO_nNotMuMatched = 0;
        int isoMB1HO_HQ_nNotMuMatched = 0;
        int isoMB1HO_LQ_nNotMuMatched = 0;
        
        // MB1
        for(int iDTTP = 0; iDTTP < nDTTP; iDTTP++)
        {
            int stNum_iDTTP = input->v_ltTwinMuxOut_station->at(iDTTP);
            int whNum_iDTTP = input->v_ltTwinMuxOut_wheel->at(iDTTP);
            int scNum_iDTTP = input->v_ltTwinMuxOut_sector->at(iDTTP);
            
            int bx_iDTTP = input->v_ltTwinMuxOut_bx->at(iDTTP);
            
            if(bx_iDTTP != 0)
            {
                continue;
            }
            
            // MB1 only
            //if(stNum_iDTTP != 1)
            //if(stNum_iDTTP != 2)
            if(stNum_iDTTP > 2)
            {
                continue;
            }
            
            // Exclude wheels +-2 of MB1
            // They are already supported by the CSC
            if(abs(whNum_iDTTP) == 2)
            {
                continue;
            }
            
            double pT_iDTTP = 0;
            
            if(stNum_iDTTP == 1)
            {
                pT_iDTTP = Common::getPtFromPhiB((int) input->v_ltTwinMuxOut_phiB->at(iDTTP), &v_phiB_MB1, &v_pT_MB1);
            }
            
            else if(stNum_iDTTP == 2)
            {
                pT_iDTTP = Common::getPtFromPhiB((int) input->v_ltTwinMuxOut_phiB->at(iDTTP), &v_phiB_MB2, &v_pT_MB2);
            }
            
            if(pT_iDTTP < MB1_pTcut)
            {
                continue;
            }
            
            double phi_iDTTP = Common::globalPhiFromDTphi(input->v_ltTwinMuxOut_phi->at(iDTTP), scNum_iDTTP);
            int iPhi_iDTTP = input->v_ltTwinMuxOut_iPhi->at(iDTTP);
            
            std::string quality_str = "";
            
            int quality = input->v_ltTwinMuxOut_quality->at(iDTTP);
            
            bool isLQ = quality > 0 && quality < 4;
            bool isHQ = quality > 3 && quality < 7;
            
            // Check DTTP quality
            if(!isLQ && !isHQ)
            {
                continue;
            }
            
            if(!isHQ)
            {
                continue;
            }
            
            // Select the histograms to write to (LQ or HQ)
            if(isLQ)
            {
                quality_str = "LQ";
                currentOutput = output_LQ;
            }
            
            else if(isHQ)
            {
                quality_str = "HQ";
                currentOutput = output_HQ;
            }
            
            //std::vector <int> v_bestDTsegment_index = a_bestDTsegment_index[whNum+2][stNum-1][scNum-1];
            //
            //if(!v_bestDTsegment_index.size())
            //{
            //    continue;
            //}
            
            //double bestDTsegment_eta = input->v_dtsegm4D_eta->at(bestDTsegment_index);
            //double bestDTsegment_phi = input->v_dtsegm4D_phi->at(bestDTsegment_index);
            
            
            // Check if isolated (isolated = unused by BMTF)
            bool isIsolatedMB1 = true;
            double MB1BMTF_deltaPhi_min = 9999;
            int usedBMTF_index = -1;
            
            //for(int iBMTF = 0; iBMTF < nBMTF; iBMTF++)
            //{
            //    int bx_iBMTF = input->v_bmtf_bx->at(iBMTF);
            //    
            //    if(bx_iBMTF != 0)
            //    {
            //        continue;
            //    }
            //    
            //    //if(v_BMTF_isUsed.at(iBMTF))
            //    //{
            //    //    continue;
            //    //}
            //    
            //    // For each track, there are 4 entries (MB1/2/3/4)
            //    // To get whether the track used MB1, check entries at 0, 4, 8...
            //    // To get whether the track used MB2, check entries at 1, 5, 9...
            //    // To get whether the track used MB3, check entries at 2, 6, 10...
            //    // To get whether the track used MB4, check entries at 3, 7, 11...
            //    // For MB1, the entry is 1 for HQ, 2 for LQ, and 3 for unused
            //    int trAdd_iBMTF_MB1 = input->v_bmtf_trAddress->at(4*iBMTF + 0);
            //    int trAdd_iBMTF_MB2 = input->v_bmtf_trAddress->at(4*iBMTF + 1);
            //    
            //    double phi_iBMTF = Common::bmtfGlobalPhiToCmsPhi(input->v_bmtf_globalPhi->at(iBMTF));
            //    
            //    // Check if BMTF has used MB1 and match sector
            //    //if(//((isLQ && trAdd_iBMTF_MB1 == 2) || (isHQ && trAdd_iBMTF_MB1 == 1)) 
            //    //    //&& whNum_iDTTP == input->v_bmtf_wheel->at(iBMTF)
            //    //    (trAdd_iBMTF_MB1 == 1 || trAdd_iBMTF_MB1 == 2)
            //    //    && scNum_iDTTP-1 == input->v_bmtf_processor->at(iBMTF))
            //    if((stNum_iDTTP == 1 && trAdd_iBMTF_MB1 != 3
            //        && scNum_iDTTP-1 == input->v_bmtf_processor->at(iBMTF)) ||
            //        (stNum_iDTTP == 2 && trAdd_iBMTF_MB2 != 15
            //        && scNum_iDTTP-1 == input->v_bmtf_processor->at(iBMTF))
            //    )
            //    {
            //        //isIsolatedMB1 = false;
            //        
            //        double deltaPhi = phi_iBMTF - phi_iDTTP;
            //        deltaPhi = (deltaPhi > M_PI)? (deltaPhi-2*M_PI): deltaPhi;
            //        deltaPhi = (deltaPhi < -M_PI)? (deltaPhi+2*M_PI): deltaPhi;
            //        
            //        //currentOutput->h1_MB1_BMTF_deltaPhi->Fill(deltaPhi);
            //        //
            //        //break;
            //        
            //        if(fabs(deltaPhi) < fabs(MB1BMTF_deltaPhi_min))
            //        {
            //            MB1BMTF_deltaPhi_min = deltaPhi;
            //            usedBMTF_index = iBMTF;
            //        }
            //    }
            //}
            //
            //if(usedBMTF_index >= 0)
            //{
            //    v_BMTF_isUsed.at(usedBMTF_index) = 1;
            //    currentOutput->h1_MB1_BMTF_deltaPhi->Fill(MB1BMTF_deltaPhi_min);
            //}
            
            
            if(v_DTTP_BMTFindex.at(iDTTP) >= 0)
            {
                isIsolatedMB1 = false;
            }
            
            
            // Old iso-type
            //bool isIsolatedMB1_old = true;
            //double ijDTTP_deltaPhi_min = 9999;
            //int usedDTTP_index = -1;
            //for(int jDTTP = 0; jDTTP < nDTTP; jDTTP++)
            //{
            //    int stNum_jDTTP = input->v_ltTwinMuxOut_station->at(jDTTP);
            //    int whNum_jDTTP = input->v_ltTwinMuxOut_wheel->at(jDTTP);
            //    int scNum_jDTTP = input->v_ltTwinMuxOut_sector->at(jDTTP);
            //    
            //    // MB2/3/4
            //    if(stNum_jDTTP == 1)
            //    {
            //        continue;
            //    }
            //    
            //    if(v_DTTP_isUsed.at(jDTTP))
            //    {
            //        continue;
            //    }
            //    
            //    double phi_jDTTP = Common::globalPhiFromDTphi(input->v_ltTwinMuxOut_phi->at(jDTTP), scNum_jDTTP);
            //    
            //    double deltaPhi = phi_iDTTP - phi_jDTTP;
            //    deltaPhi = (deltaPhi > M_PI)? (deltaPhi-2*M_PI): deltaPhi;
            //    deltaPhi = (deltaPhi < -M_PI)? (deltaPhi+2*M_PI): deltaPhi;
            //    
            //    if(fabs(deltaPhi) < 0.4)// && scNum_jDTTP == scNum_iDTTP)// && whNum_jDTTP == whNum_iDTTP)
            //    {
            //        isIsolatedMB1_old = false;
            //        
            //        if(fabs(deltaPhi) < fabs(ijDTTP_deltaPhi_min))
            //        {
            //            ijDTTP_deltaPhi_min = deltaPhi;
            //            usedDTTP_index = jDTTP;
            //        }
            //    }
            //}
            //
            //if(usedDTTP_index >= 0)
            //{
            //    v_DTTP_isUsed.at(usedDTTP_index) = 1;
            //}
            //
            //if(isIsolatedMB1_old)
            //{
            //    currentOutput->h1_MB1_isoType->Fill(-2);
            //}
            //
            //if(isIsolatedMB1_old && !isIsolatedMB1)
            //{
            //    currentOutput->h1_MB1_isoType->Fill(-1);
            //}
            //
            //if(isIsolatedMB1_old && isIsolatedMB1)
            //{
            //    currentOutput->h1_MB1_isoType->Fill(0);
            //}
            //
            //if(!isIsolatedMB1_old && isIsolatedMB1)
            //{
            //    currentOutput->h1_MB1_isoType->Fill(1);
            //}
            //
            //if(isIsolatedMB1)
            //{
            //    currentOutput->h1_MB1_isoType->Fill(2);
            //}
            
            // Next portion only for isolated MB1
            if(!isIsolatedMB1)
            {
                continue;
            }
            
            
            printf("isoMB1 found: DT index %d, pT %f, phi %f \n", iDTTP, pT_iDTTP, phi_iDTTP);
            
            // HO support
            bool isHOTPmatched = false;
            
            int nearestHOTP_index = -1;
            int MB1HO_deltaIphi_min = 9999;
            
            for(int iHOTP = 0; iHOTP < nHOTP; iHOTP++)
            {
                // HOTP at SOI only
                if(input->v_hoTPdigi_bits->at(iHOTP) != HOTP_bits_SOI)
                {
                    continue;
                }
                
                if(v_HOTP_isUsed.at(iHOTP))
                {
                    continue;
                }
                
                int iPhi_iHOTP = input->v_hoTPdigi_iPhi->at(iHOTP);
                int iEta_iHOTP = input->v_hoTPdigi_iEta->at(iHOTP);
                
                //if(abs(input->v_hoTPdigi_iEta->at(iHOTP)) != 3)
                //{
                //    continue;
                //}
                
                //if((iPhi_iHOTP+1)%6 == 0 || (iPhi_iHOTP+2)%6 == 0)
                //{
                //    continue;
                //}
                
                int whNum_iHOTP = Common::getWheelFromIeta(input->v_hoTPdigi_iEta->at(iHOTP));
                int scNum_iHOTP = Common::getSectorFromIphi(input->v_hoTPdigi_iPhi->at(iHOTP));
                
                
                int deltaIphi = iPhi_iDTTP - iPhi_iHOTP;
                deltaIphi = (deltaIphi > 36)? (deltaIphi-72): deltaIphi;
                deltaIphi = (deltaIphi < -36)? (deltaIphi+72): deltaIphi;
                
                //int deltaIeta = etaToIeta(bestDTsegment_eta) - input->v_hoTPdigi_iEta->at(iHOTP);
                
                
                // Store nearest HOTP
                if(abs(deltaIphi) < abs(MB1HO_deltaIphi_min))
                {
                    MB1HO_deltaIphi_min = deltaIphi;
                    
                    nearestHOTP_index = iHOTP;
                    
                    // MB1-HO matching
                    if(((stNum_iDTTP == 1 && abs(deltaIphi) <= MB1_HO_deltaIphiCut) || (stNum_iDTTP == 2 && abs(deltaIphi) <= MB2_HO_deltaIphiCut))
                        && scNum_iDTTP == scNum_iHOTP
                        && whNum_iDTTP == whNum_iHOTP
                    )
                    {
                        isHOTPmatched = true;
                    }
                }
            }
            
            currentOutput->h1_isoMB1HO_deltaIphi->Fill(MB1HO_deltaIphi_min);
            
            bool MB1HO_isMuMatched = false;
            
            if(isHOTPmatched)
            {
                printf("isoMB1+HO found: HO index %d \n", nearestHOTP_index);
                
                v_HOTP_isUsed.at(nearestHOTP_index) = 1;
                
                int selectedMu_MB1HOmatched_index = -1;
                double deltaR_min = 9999;
                double nearestHOTP_eta = Common::HOiEtaToEta(input->v_hoTPdigi_iEta->at(nearestHOTP_index));
                double nearestHOTP_phi = Common::HOiPhiToPhi(input->v_hoTPdigi_iPhi->at(nearestHOTP_index));
                
                for(int iMuon = 0; iMuon < v_selectedMu_index.size(); iMuon++)
                {
                    int muon_pos = v_selectedMu_index.at(iMuon);
                    
                    if(muon_pos < 0)
                    {
                        continue;
                    }
                    
                    double eta_iMuon = v_selectedMu_eta.at(iMuon);//input->v_Mu_eta->at(muon_pos);
                    double phi_iMuon = v_selectedMu_phi.at(iMuon);//input->v_Mu_phi->at(muon_pos);
                    
                    if(v_selectedMu_hasMB1.at(iMuon))
                    {
                        eta_iMuon = v_selectedMu_etaMB1.at(iMuon);
                        phi_iMuon = v_selectedMu_phiMB1.at(iMuon);
                    }
                    
                    double deltaEta = nearestHOTP_eta - eta_iMuon;
                    double deltaPhi = phi_iDTTP - phi_iMuon;
                    deltaPhi = (deltaPhi > M_PI)? (deltaPhi-2*M_PI): deltaPhi;
                    deltaPhi = (deltaPhi < -M_PI)? (deltaPhi+2*M_PI): deltaPhi;
                    
                    double deltaR = sqrt(deltaEta*deltaEta + deltaPhi*deltaPhi);
                    
                    //if(fabs(deltaEta) < muMB1_deltaEtaCut && fabs(deltaPhi) < muMB1_deltaPhiCut)
                    
                    if(deltaR < deltaR_min)
                    {
                        deltaR_min = deltaR;
                        selectedMu_MB1HOmatched_index = iMuon;
                        
                    }
                }
                
                
                if(selectedMu_MB1HOmatched_index >= 0)// && v_selectedMu_hasMB1.at(selectedMu_MB1HOmatched_index))
                {
                    currentOutput->h2_isoMB1HO_mu_pT_vs_deltaR->Fill(deltaR_min, v_selectedMu_pT.at(selectedMu_MB1HOmatched_index));
                }
                
                
                int nHO3x3hit = Common::getHO3x3hits(input->v_hoTPdigi_iEta->at(nearestHOTP_index), input->v_hoTPdigi_iPhi->at(nearestHOTP_index),
                    input->v_hoTPdigi_iEta, input->v_hoTPdigi_iPhi,
                    input->v_hoTPdigi_bits, HOTP_bits_SOI
                );
                
                // Fill isoMB1+HO quantities if mu-matched
                if(deltaR_min < muMB1_deltaRcut)
                {
                    currentOutput->h1_isoMB1HO_muMatched_3x3->Fill(nHO3x3hit);
                    
                    if(!isoMB1HO_3x3_placeCut || nHO3x3hit <= isoMB1HO_3x3_cut)
                    {
                        printf("isoMB1+HO IS matched to muon. \n");
                        
                        MB1HO_isMuMatched = true;
                        
                        // Block the matched muon
                        if(selectedMu_MB1HOmatched_index >= 0)
                        {
                            v_selectedMu_index.at(selectedMu_MB1HOmatched_index) = -1;
                            v_selectedMu_isMB1HOmatched.at(selectedMu_MB1HOmatched_index) = true;
                        }
                        
                        currentOutput->h1_isoMB1HO_mu_deltaPt->Fill(pT_iDTTP - v_selectedMu_pT.at(selectedMu_MB1HOmatched_index));
                        
                        currentOutput->h1_isoMB1HO_muMatched_pT->Fill(v_selectedMu_pT.at(selectedMu_MB1HOmatched_index));//pT_iDTTP);
                        currentOutput->h1_isoMB1HO_muMatched_eta->Fill(v_selectedMu_eta.at(selectedMu_MB1HOmatched_index));//nearestHOTP_eta);
                        currentOutput->h1_isoMB1HO_muMatched_phi->Fill(v_selectedMu_phi.at(selectedMu_MB1HOmatched_index));//phi_iDTTP);
                        
                        currentOutput->h2_isoMB1HO_muMatched_pT_vs_eta->Fill(v_selectedMu_eta.at(selectedMu_MB1HOmatched_index), v_selectedMu_pT.at(selectedMu_MB1HOmatched_index));
                        currentOutput->h2_isoMB1HO_muMatched_pT_vs_phi->Fill(v_selectedMu_phi.at(selectedMu_MB1HOmatched_index), v_selectedMu_pT.at(selectedMu_MB1HOmatched_index));
                        currentOutput->h2_isoMB1HO_muMatched_eta_vs_phi->Fill(v_selectedMu_phi.at(selectedMu_MB1HOmatched_index), v_selectedMu_eta.at(selectedMu_MB1HOmatched_index));
                        
                        currentOutput->h2_isoMB1HO_muMatched_pT_vs_deltaIphi->Fill(MB1HO_deltaIphi_min, v_selectedMu_pT.at(selectedMu_MB1HOmatched_index));
                    }
                }
                
                // Fill isoMB1+HO quantities if not mu-matched
                else
                {
                    printf("isoMB1+HO is NOT matched to muon. \n");
                    
                    isoMB1HO_nNotMuMatched++;
                    
                    if(isHQ)
                    {
                        isoMB1HO_HQ_nNotMuMatched++;
                    }
                    
                    else
                    {
                        isoMB1HO_LQ_nNotMuMatched++;
                    }
                    
                    currentOutput->h1_isoMB1HO_muNotMatched_pT->Fill(pT_iDTTP);
                    currentOutput->h1_isoMB1HO_muNotMatched_eta->Fill(nearestHOTP_eta);
                    currentOutput->h1_isoMB1HO_muNotMatched_phi->Fill(phi_iDTTP);
                    
                    currentOutput->h1_isoMB1HO_muNotMatched_3x3->Fill(nHO3x3hit);
                    
                    currentOutput->h2_isoMB1HO_muNotMatched_pT_vs_eta->Fill(nearestHOTP_eta, pT_iDTTP);
                    currentOutput->h2_isoMB1HO_muNotMatched_pT_vs_phi->Fill(phi_iDTTP, pT_iDTTP);
                    currentOutput->h2_isoMB1HO_muNotMatched_eta_vs_phi->Fill(phi_iDTTP, nearestHOTP_eta);
                }
            }
        }
        
        
        // For the muons that are unused (not matched to anything)
        int nUnusedMu = 0;
        int nDTTP_BX0 = 0;
        
        for(int iMuon = 0; iMuon < v_selectedMu_index.size(); iMuon++)
        {
            currentOutput= 0;
            
            int muon_pos = v_selectedMu_index.at(iMuon);
            
            // Check if used
            bool isMuUsed = false;
            
            if(muon_pos < 0 && !v_selectedMu_isMB1HOmatched.at(iMuon))
            {
                //continue;
                isMuUsed = true;
                
                muon_pos = v_selectedMu_index_backup.at(iMuon);
            }
            
            double pT_iMuon = v_selectedMu_pT.at(iMuon);
            double eta_iMuon = v_selectedMu_eta.at(iMuon);
            double phi_iMuon = v_selectedMu_phi.at(iMuon);
            
            if(v_selectedMu_hasMB1.at(iMuon))
            {
                eta_iMuon = v_selectedMu_etaMB1.at(iMuon);
                phi_iMuon = v_selectedMu_phiMB1.at(iMuon);
            }
            
            // HO support
            double deltaR_min = 9999;
            bool isHOmatched = false;
            int nearestHO_iEta = 0;
            int nearestHO_iPhi = 0;
            
            for(int iHOTP = 0; iHOTP < nHOTP; iHOTP++)
            {
                // HOTP at SOI only
                if(input->v_hoTPdigi_bits->at(iHOTP) != HOTP_bits_SOI)
                {
                    continue;
                }
                
                //if(v_HOTP_isUsed.at(iHOTP))
                //{
                //    continue;
                //}
                
                int iPhi_iHOTP = input->v_hoTPdigi_iPhi->at(iHOTP);
                int iEta_iHOTP = input->v_hoTPdigi_iEta->at(iHOTP);
                
                //if(abs(input->v_hoTPdigi_iEta->at(iHOTP)) != 3)
                //{
                //    continue;
                //}
                
                //if((iPhi_iHOTP+1)%6 == 0 || (iPhi_iHOTP+2)%6 == 0)
                //{
                //    continue;
                //}
                
                int whNum_iHOTP = Common::getWheelFromIeta(input->v_hoTPdigi_iEta->at(iHOTP));
                int scNum_iHOTP = Common::getSectorFromIphi(input->v_hoTPdigi_iPhi->at(iHOTP));
                
                
                double deltaEta = Common::HOiEtaToEta(iEta_iHOTP) - eta_iMuon;
                double deltaPhi = Common::HOiPhiToPhi(iPhi_iHOTP) - phi_iMuon;
                deltaPhi = (deltaPhi > M_PI)? (deltaPhi-2*M_PI): deltaPhi;
                deltaPhi = (deltaPhi < -M_PI)? (deltaPhi+2*M_PI): deltaPhi;
                
                double deltaR = sqrt(deltaEta*deltaEta + deltaPhi*deltaPhi);
                
                //if(fabs(deltaEta) < muMB1_deltaEtaCut && fabs(deltaPhi) < muMB1_deltaPhiCut)
                
                if(deltaR < deltaR_min)
                {
                    deltaR_min = deltaR;
                    
                    nearestHO_iEta = iEta_iHOTP;
                    nearestHO_iPhi = iPhi_iHOTP;
                }
            }
            
            if(deltaR_min < muMB1_deltaRcut)
            {
                isHOmatched = true;
            }
            
            if(isMuUsed)
            {
                output->h1_usedMu_pT->Fill(pT_iMuon);
                output->h1_usedMu_eta->Fill(eta_iMuon);
                output->h1_usedMu_phi->Fill(phi_iMuon);
                
                output->h2_usedMu_pT_vs_eta->Fill(eta_iMuon, pT_iMuon);
            }
            
            else
            {
                nUnusedMu++;
                
                output->h1_unusedMu_pT->Fill(pT_iMuon);
                output->h1_unusedMu_eta->Fill(eta_iMuon);
                output->h1_unusedMu_phi->Fill(phi_iMuon);
                
                output->h1_unusedMu_nDTTP->Fill(nDTTP);
                
                output->h2_unusedMu_pT_vs_eta->Fill(eta_iMuon, pT_iMuon);
                output->h2_unusedMu_eta_vs_phi->Fill(phi_iMuon, eta_iMuon);
                
                if(isHOmatched)
                {
                    output->h2_unusedMuHO_pT_vs_eta->Fill(eta_iMuon, pT_iMuon);
                    output->h2_unusedMuHO_eta_vs_phi->Fill(phi_iMuon, eta_iMuon);
                }
            }
            
            
            // Run over LQ (0), HQ (1), LQ+HQ (2)
            for(int iQua = 0; iQua < 3; iQua++)
            {
                if(iQua == 0)
                {
                    currentOutput = output_LQ;
                }
                
                else if(iQua == 1)
                {
                    currentOutput = output_HQ;
                }
                
                else
                {
                    currentOutput = output;
                }
                
                double deltaPhi_min = 9999;
                
                int nearestDTTP_index = -1;
                bool nearestDTTP_isHQ = false;
                
                int stationMask_iMuon = 0;
                
                nDTTP_BX0 = 0;
                
                std::vector <MBTP_info> v_MBTP_info;
                
                for(int iSt = 0; iSt < 4; iSt++)
                {
                    MBTP_info temp;
                    
                    v_MBTP_info.push_back(temp);
                }
                
                //v_MBTP_info[0].index = 9;
                //v_MBTP_info[1].index = 5;
                //printf("xxxxx %d %d %d %d \n", v_MBTP_info[0].index, v_MBTP_info[1].index, v_MBTP_info[2].index, v_MBTP_info[3].index);
                
                for(int iDTTP = 0; iDTTP < nDTTP; iDTTP++)
                {
                    int stNum_iDTTP = input->v_ltTwinMuxOut_station->at(iDTTP);
                    int whNum_iDTTP = input->v_ltTwinMuxOut_wheel->at(iDTTP);
                    int scNum_iDTTP = input->v_ltTwinMuxOut_sector->at(iDTTP);
                    
                    int bx_iDTTP = input->v_ltTwinMuxOut_bx->at(iDTTP);
                    
                    if(bx_iDTTP != 0)
                    {
                        continue;
                    }
                    
                    nDTTP_BX0++;
                    
                    int quality = input->v_ltTwinMuxOut_quality->at(iDTTP);
                    
                    bool isLQ = quality > 0 && quality < 4;
                    bool isHQ = quality > 3 && quality < 7;
                    
                    // Check DTTP quality
                    if(!isLQ && !isHQ)
                    {
                        continue;
                    }
                    
                    if(iQua == 0 && isHQ)
                    {
                        continue;
                    }
                    
                    else if(iQua == 1 && isLQ)
                    {
                        continue;
                    }
                    
                    // Check if already associated to a BMTF
                    //if(v_DTTP_BMTFindex.at(iDTTP) >= 0)
                    //{
                    //    continue;
                    //}
                    
                    // Exclude wheels +-2 of MB1
                    // They are already supported by the CSC
                    //if(stNum_iDTTP == 1 && abs(whNum_iDTTP) == 2)
                    //{
                    //    continue;
                    //}
                    
                    //double pT_iDTTP = Common::getPtFromPhiB((int) input->v_ltTwinMuxOut_phiB->at(iDTTP), &v_phiB_MB1, &v_pT_MB1);
                    //
                    //if(pT_iDTTP < MB1_pTcut)
                    //{
                    //    continue;
                    //}
                    
                    double phi_iDTTP = Common::globalPhiFromDTphi(input->v_ltTwinMuxOut_phi->at(iDTTP), scNum_iDTTP);
                    
                    double deltaPhi = phi_iDTTP - phi_iMuon;
                    deltaPhi = (deltaPhi > M_PI)? (deltaPhi-2*M_PI): deltaPhi;
                    deltaPhi = (deltaPhi < -M_PI)? (deltaPhi+2*M_PI): deltaPhi;
                    
                    if(fabs(deltaPhi) < fabs(deltaPhi_min))
                    {
                        deltaPhi_min = deltaPhi;
                        nearestDTTP_index = iDTTP;
                        nearestDTTP_isHQ = isHQ;
                    }
                    
                    if(fabs(deltaPhi) < 0.4)
                    {
                        stationMask_iMuon |= (1<<(stNum_iDTTP-1));
                        
                        for(int iSt = 0; iSt < 4; iSt++)
                        {
                            if(iSt+1 == stNum_iDTTP && fabs(deltaPhi) < fabs(v_MBTP_info[iSt].deltaPhi))
                            {
                                v_MBTP_info[iSt].index = iDTTP;
                                v_MBTP_info[iSt].station = stNum_iDTTP;
                                v_MBTP_info[iSt].wheel = whNum_iDTTP;
                                
                                v_MBTP_info[iSt].deltaPhi = fabs(deltaPhi);
                                v_MBTP_info[iSt].phiB = input->v_ltTwinMuxOut_phiB->at(iDTTP) / 512.0;
                                v_MBTP_info[iSt].phiLocal = input->v_ltTwinMuxOut_phi->at(iDTTP) / 4096.0;
                            }
                        }
                    }
                }
                
                //for(int iDTseg = 0; iDTseg < nDTseg; iDTseg++)
                //{
                //    int whNum_iDTseg = input->v_dtsegm4D_wheel->at(iDTseg);
                //    int stNum_iDTseg = input->v_dtsegm4D_station->at(iDTseg);
                //    int scNum_iDTseg = input->v_dtsegm4D_sector->at(iDTseg);
                //    
                //    // MB4 sectors 4 (top) and 10 (bottom) are made up of two parts (divided vertically in the middle)
                //    // sector 4 is 4/1 and sector 13 is 4/2
                //    // sector 10 is 10/1 and sector 14 is 10/2
                //    scNum_iDTseg = (scNum_iDTseg > 12)? ((scNum_iDTseg == 13)? 4: 10): scNum_iDTseg;
                //    
                //    int nHit_phiLocal = 0;
                //    int nHit_zLocal = 0;
                //    
                //    bool isValid_iDTseg = false;
                //    
                //    // Must have phi-projection, and if not MB4, then also z-projection
                //    if(input->v_dtsegm4D_hasPhi->at(iDTseg)
                //        && (input->v_dtsegm4D_hasZed->at(iDTseg) || stNum_iDTseg == 4)
                //    )
                //    {
                //        nHit_phiLocal = input->v_dtsegm4D_phinhits->at(iDTseg);
                //        
                //        double tan_phiLocal = input->v_dtsegm4D_x_dir_loc->at(iDTseg) / input->v_dtsegm4D_z_dir_loc->at(iDTseg);
                //        double phiLocal = atan(tan_phiLocal) * 180/M_PI;
                //        
                //        // Cut on the number of hits in an angular region
                //        if(nHit_phiLocal >= DTsegment_nHit_phiLocal_min && fabs(phiLocal) < DTsegment_phiLocal_max)
                //        {
                //            isValid_iDTseg = true;
                //        }
                //    }
                //    
                //    if(!isValid_iDTseg)
                //    {
                //        continue;
                //    }
                //    
                //    nDTTP_BX0++;
                //    
                //    double phi_iDTseg = input->v_dtsegm4D_phi->at(iDTseg);
                //    
                //    double deltaPhi = phi_iDTseg - phi_iMuon;
                //    deltaPhi = (deltaPhi > M_PI)? (deltaPhi-2*M_PI): deltaPhi;
                //    deltaPhi = (deltaPhi < -M_PI)? (deltaPhi+2*M_PI): deltaPhi;
                //    
                //    if(fabs(deltaPhi) < fabs(deltaPhi_min))
                //    {
                //        deltaPhi_min = deltaPhi;
                //        nearestDTTP_index = iDTseg;
                //    }
                //    
                //    if(fabs(deltaPhi) < 0.8)
                //    {
                //        stationMask_iMuon |= (1<<(stNum_iDTseg-1));
                //    }
                //}
                
                int nearestHO_deltaIphi = 9999;
                
                if(isHOmatched)
                {
                    if(stationMask_iMuon == 1 || stationMask_iMuon == 2)
                    {
                        int iPhi_temp = input->v_ltTwinMuxOut_iPhi->at(v_MBTP_info[stationMask_iMuon-1].index);
                        
                        nearestHO_deltaIphi = iPhi_temp - nearestHO_iPhi;
                        nearestHO_deltaIphi = (nearestHO_deltaIphi > 36)? (nearestHO_deltaIphi-72): nearestHO_deltaIphi;
                        nearestHO_deltaIphi = (nearestHO_deltaIphi < -36)? (nearestHO_deltaIphi+72): nearestHO_deltaIphi;
                        
                        //if(abs(nearestHO_deltaIphi) > MB1_HO_deltaIphiCut)
                        //{
                        //    isHOmatched = false;
                        //}
                    }
                    
                    //else
                    //{
                    //    isHOmatched = false;
                    //}
                }
                
                if(isMuUsed)
                {
                    currentOutput->h2_usedMu_pT_vs_stationMask->Fill(stationMask_iMuon, pT_iMuon);
                    currentOutput->h2_usedMu_eta_vs_stationMask->Fill(stationMask_iMuon, eta_iMuon);
                    
                    // Used MB12 mu
                    if(stationMask_iMuon == 3)
                    {
                        int stNum = 0;
                        
                        currentOutput->h2_usedMB12mu_MB2phiB_vs_MB1phiB->Fill(
                            v_MBTP_info[0].phiB,
                            v_MBTP_info[1].phiB
                        );
                        
                        // MB1TP and MB2TP are in wh0
                        if(v_MBTP_info[0].wheel == 0 && v_MBTP_info[1].wheel == 0)
                        {
                            currentOutput->h2_usedMB12mu_wh0_MB2phiB_vs_MB1phiB->Fill(
                                v_MBTP_info[0].phiB,
                                v_MBTP_info[1].phiB
                            );
                            
                            currentOutput->h2_usedMB12mu_wh0_pT_vs_MB1phiB->Fill(
                                v_MBTP_info[0].phiB,
                                pT_iMuon
                            );
                        }
                        
                        // MB1TP and MB2TP are in wh1
                        else if(abs(v_MBTP_info[0].wheel) == 1 && abs(v_MBTP_info[1].wheel) == 1)
                        {
                            currentOutput->h2_usedMB12mu_wh1_MB2phiB_vs_MB1phiB->Fill(
                                v_MBTP_info[0].phiB,
                                v_MBTP_info[1].phiB
                            );
                            
                            currentOutput->h2_usedMB12mu_wh1_pT_vs_MB1phiB->Fill(
                                v_MBTP_info[0].phiB,
                                pT_iMuon
                            );
                        }
                    }
                }
                
                else
                {
                    currentOutput->h1_unusedMu_stationMask->Fill(stationMask_iMuon);
                    currentOutput->h2_unusedMu_pT_vs_stationMask->Fill(stationMask_iMuon, pT_iMuon);
                    currentOutput->h2_unusedMu_eta_vs_stationMask->Fill(stationMask_iMuon, eta_iMuon);
                    currentOutput->h2_unusedMu_phi_vs_stationMask->Fill(stationMask_iMuon, phi_iMuon);
                    
                    if(isHOmatched)
                    {
                        currentOutput->h2_unusedMuHO_pT_vs_stationMask->Fill(stationMask_iMuon, pT_iMuon);
                        currentOutput->h2_unusedMuHO_eta_vs_stationMask->Fill(stationMask_iMuon, eta_iMuon);
                        currentOutput->h2_unusedMuHO_phi_vs_stationMask->Fill(stationMask_iMuon, phi_iMuon);
                    }
                    
                    // Unused MB1 mu
                    if(stationMask_iMuon == 1)
                    {
                        int stNum = 0;
                        
                        if(v_MBTP_info[stNum].wheel == 0)
                        {
                            currentOutput->h1_unusedMB1mu_wh0_phiB->Fill(v_MBTP_info[stNum].phiB);
                            currentOutput->h1_unusedMB1mu_wh0_psi->Fill(v_MBTP_info[stNum].phiB + v_MBTP_info[stNum].phiLocal);
                        }
                        
                        else if(abs(v_MBTP_info[stNum].wheel) == 1)
                        {
                            currentOutput->h1_unusedMB1mu_wh1_phiB->Fill(v_MBTP_info[stNum].phiB);
                            currentOutput->h1_unusedMB1mu_wh1_psi->Fill(v_MBTP_info[stNum].phiB + v_MBTP_info[stNum].phiLocal);
                        }
                        
                        currentOutput->h2_unusedMB1muHO_pT_vs_deltaR->Fill(deltaR_min, pT_iMuon);
                        currentOutput->h2_unusedMB1muHO_pT_vs_deltaIphi->Fill(nearestHO_deltaIphi, pT_iMuon);
                    }
                    
                    // Unused MB2 mu
                    if(stationMask_iMuon == 2)
                    {
                        int stNum = 1;
                        
                        if(v_MBTP_info[stNum].wheel == 0)
                        {
                            currentOutput->h1_unusedMB2mu_wh0_phiB->Fill(v_MBTP_info[stNum].phiB);
                            currentOutput->h1_unusedMB2mu_wh0_psi->Fill(v_MBTP_info[stNum].phiB + v_MBTP_info[stNum].phiLocal);
                        }
                        
                        else if(abs(v_MBTP_info[stNum].wheel) == 1)
                        {
                            currentOutput->h1_unusedMB2mu_wh1_phiB->Fill(v_MBTP_info[stNum].phiB);
                            currentOutput->h1_unusedMB2mu_wh1_psi->Fill(v_MBTP_info[stNum].phiB + v_MBTP_info[stNum].phiLocal);
                        }
                        
                        currentOutput->h2_unusedMB2mu_pT_vs_eta->Fill(eta_iMuon, pT_iMuon);
                        currentOutput->h2_unusedMB2mu_eta_vs_phi->Fill(phi_iMuon, eta_iMuon);
                        
                        currentOutput->h2_unusedMB2muHO_pT_vs_deltaR->Fill(deltaR_min, pT_iMuon);
                        currentOutput->h2_unusedMB2muHO_pT_vs_deltaIphi->Fill(nearestHO_deltaIphi, pT_iMuon);
                    }
                    
                    // Unused MB12 mu
                    if(stationMask_iMuon == 3)
                    {
                        int stNum = 0;
                        
                        currentOutput->h2_unusedMB12mu_MB2phiB_vs_MB1phiB->Fill(
                            v_MBTP_info[0].phiB,
                            v_MBTP_info[1].phiB
                        );
                        
                        // MB1TP and MB2TP are in wh0
                        if(v_MBTP_info[0].wheel == 0 && v_MBTP_info[1].wheel == 0)
                        {
                            currentOutput->h2_unusedMB12mu_wh0_MB2phiB_vs_MB1phiB->Fill(
                                v_MBTP_info[0].phiB,
                                v_MBTP_info[1].phiB
                            );
                            
                            currentOutput->h2_unusedMB12mu_wh0_MB2psi_vs_MB1psi->Fill(
                                v_MBTP_info[0].phiB + v_MBTP_info[0].phiLocal,
                                v_MBTP_info[1].phiB + v_MBTP_info[1].phiLocal
                            );
                        }
                        
                        // MB1TP and MB2TP are in wh1
                        else if(abs(v_MBTP_info[0].wheel) == 1 && abs(v_MBTP_info[1].wheel) == 1)
                        {
                            currentOutput->h2_unusedMB12mu_wh1_MB2phiB_vs_MB1phiB->Fill(
                                v_MBTP_info[0].phiB,
                                v_MBTP_info[1].phiB
                            );
                            
                            currentOutput->h2_unusedMB12mu_wh1_MB2psi_vs_MB1psi->Fill(
                                v_MBTP_info[0].phiB + v_MBTP_info[0].phiLocal,
                                v_MBTP_info[1].phiB + v_MBTP_info[1].phiLocal
                            );
                        }
                    }
                }
                
                
                
                if(nearestDTTP_index >= 0)
                {
                    if(isMuUsed)
                    {
                        currentOutput->h2_usedMu_DTTP_pT_vs_deltaPhi->Fill(deltaPhi_min, pT_iMuon);
                    }
                    
                    else
                    {
                        currentOutput->h2_unusedMu_DTTP_pT_vs_deltaPhi->Fill(deltaPhi_min, pT_iMuon);
                    }
                }
            }
        }
        
        if(nUnusedMu)
        {
            output->h2_nUnusedMu_vs_nDTTP->Fill(nDTTP_BX0, nUnusedMu);
        }
        
        output->h2_isoMB1HO_nNotMuMatched_vs_nUnusedMu->Fill(nUnusedMu, isoMB1HO_nNotMuMatched);
        output_LQ->h2_isoMB1HO_nNotMuMatched_vs_nUnusedMu->Fill(nUnusedMu, isoMB1HO_LQ_nNotMuMatched);
        output_HQ->h2_isoMB1HO_nNotMuMatched_vs_nUnusedMu->Fill(nUnusedMu, isoMB1HO_HQ_nNotMuMatched);
    }
}
