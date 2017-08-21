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


int nWheel = 5;
int nStation = 4;
int nSector = 12;

int str_len = 500;

double mu_pTcut = 14; // GeV
double mu_etaCut = 1.2;

double deltaRcut = 0.4;
double deltaPhiCut = 0.4;

double DT_deltaPhicut = 0.4;
int MB1_HO_deltaIphiCut = 1;
int MB1_HO_deltaSectorCut = 1;
int MB1_HO_deltaIetaCut = 1;
int MB1_HO_deltaWheelCut = 0;

int DTsegment_nHit_phiLocal_min = 4;
int DTsegment_phiLocal_max = 45; // degree

int nEvent_global = 0;
int nEvent_global_max = 0;

int MB1_n_LQ = 0;
int MB1_n_HQ = 0;
int isolatedMB1_n_LQ_inTimeMatching = 0;
int isolatedMB1_n_HQ_inTimeMatching = 0;
int isolatedMB1_n_LQ_deltaTimeMatching = 0;
int isolatedMB1_n_HQ_deltaTimeMatching = 0;
int isolatedMB1_n_LQ_noTimeMatching = 0;
int isolatedMB1_n_HQ_noTimeMatching = 0;

int HOTP_bits_SOI = 8;

std::vector <int> v_runNumber;
std::vector <double> v_recordedLumiPerLS;

std::vector <int> v_phiB;
std::vector <double> v_pT;

// <run, <pTcut, <event_n, MB1_n, isolatedMB1_n, unisolatedMB1_n, HOTP_n, HOTP_SOI_n, isolatedMB1_withHOTP_SOI_n, unisolatedMB1_withHOTP_SOI_n> > >
std::map <long, std::map <int, std::vector <int> > > m_MB1_LQ;
std::map <long, std::map <int, std::vector <int> > > m_MB1_HQ;

std::vector <int> v_pTcut = {0, 5, 10, 14, 18, 22};

int DT_phi_max = 0;
int DT_phi_min = 0;


class InputData
{
    public:
    
    TFile *inputFile;
    TTree *tree;
    
    Long64_t runNumber;
    Long64_t lumiBlock;
    Long64_t eventNumber;
    
    std::vector<int> *v_hoTPdigi_bits;
    std::vector<int> *v_hoTPdigi_iEta;
    std::vector<int> *v_hoTPdigi_iPhi;
    std::vector<int> *v_hoTPdigi_nSamples;
    std::vector<int> *v_hoTPdigi_raw;
    std::vector<int> *v_hoTPdigi_whichSampleTriggered;
    
    std::vector <double> *v_dtsegm4D_wheel;
    std::vector <double> *v_dtsegm4D_sector;
    std::vector <double> *v_dtsegm4D_station;
    std::vector <double> *v_dtsegm4D_hasPhi;
    std::vector <double> *v_dtsegm4D_hasZed;
    std::vector <double> *v_dtsegm4D_x_pos_loc;
    std::vector <double> *v_dtsegm4D_y_pos_loc;
    std::vector <double> *v_dtsegm4D_z_pos_loc;
    std::vector <double> *v_dtsegm4D_x_dir_loc;
    std::vector <double> *v_dtsegm4D_y_dir_loc;
    std::vector <double> *v_dtsegm4D_z_dir_loc;
    std::vector <double> *v_dtsegm4D_phi;
    std::vector <double> *v_dtsegm4D_theta;
    std::vector <double> *v_dtsegm4D_eta;
    std::vector <double> *v_dtsegm4D_phinhits;
    std::vector <double> *v_dtsegm4D_znhits;
    
    
    std::vector <double> *v_gmt_bx;
    std::vector <double> *v_gmt_pT;
    std::vector <double> *v_gmt_eta;
    std::vector <double> *v_gmt_phi;
    
    
    std::vector <int> *v_ltTwinMuxIn_wheel;
    std::vector <int> *v_ltTwinMuxIn_sector;
    std::vector <int> *v_ltTwinMuxIn_station;
    std::vector <int> *v_ltTwinMuxIn_quality;
    std::vector <int> *v_ltTwinMuxIn_bx;
    std::vector <int> *v_ltTwinMuxIn_phi;
    std::vector <int> *v_ltTwinMuxIn_iPhi;
    std::vector <int> *v_ltTwinMuxIn_phiB;
    
    std::vector <int> *v_ltTwinMuxOut_wheel;
    std::vector <int> *v_ltTwinMuxOut_sector;
    std::vector <int> *v_ltTwinMuxOut_station;
    std::vector <int> *v_ltTwinMuxOut_quality;
    std::vector <int> *v_ltTwinMuxOut_bx;
    std::vector <int> *v_ltTwinMuxOut_phi;
    std::vector <int> *v_ltTwinMuxOut_iPhi;
    std::vector <int> *v_ltTwinMuxOut_phiB;
    
    
    std::vector <int> *v_ltTwinMux_thBx;
    std::vector <int> *v_ltTwinMux_thWheel;
    std::vector <int> *v_ltTwinMux_thSector;
    std::vector <int> *v_ltTwinMux_thStation;
    std::vector <int> *v_ltTwinMux_thHits;
    std::vector <int> *v_ltTwinMux_thPosition;
    std::vector <int> *v_ltTwinMux_thQuality;
    std::vector <int> *v_ltTwinMux_thIeta;
    
    
    std::vector <double> *v_Mu_isMuGlobal;
    std::vector <double> *v_Mu_isMuTracker;
    std::vector <double> *v_Mu_isMuTight;
    std::vector <double> *v_Mu_px;
    std::vector <double> *v_Mu_py;
    std::vector <double> *v_Mu_pz;
    std::vector <double> *v_Mu_phi;
    std::vector <double> *v_Mu_eta;
    
    
    InputData(const char *inputFileName)
    {
        inputFile = TFile::Open(inputFileName, "READ");
        
        tree = (TTree*) inputFile->Get("myDTNtuple/DTTree");
        
        runNumber = 0;
        lumiBlock = 0;
        eventNumber = 0;
        
        v_hoTPdigi_bits = 0;
        v_hoTPdigi_iEta = 0;
        v_hoTPdigi_iPhi = 0;
        v_hoTPdigi_nSamples = 0;
        v_hoTPdigi_raw = 0;
        v_hoTPdigi_whichSampleTriggered = 0;
        
        v_dtsegm4D_wheel = 0;
        v_dtsegm4D_sector = 0;
        v_dtsegm4D_station = 0;
        v_dtsegm4D_hasPhi = 0;
        v_dtsegm4D_hasZed = 0;
        v_dtsegm4D_x_pos_loc = 0;
        v_dtsegm4D_y_pos_loc = 0;
        v_dtsegm4D_z_pos_loc = 0;
        v_dtsegm4D_x_dir_loc = 0;
        v_dtsegm4D_y_dir_loc = 0;
        v_dtsegm4D_z_dir_loc = 0;
        v_dtsegm4D_phi = 0;
        v_dtsegm4D_theta = 0;
        v_dtsegm4D_eta = 0;
        v_dtsegm4D_phinhits = 0;
        v_dtsegm4D_znhits = 0;
        
        
        v_gmt_bx = 0;
        v_gmt_pT = 0;
        v_gmt_eta = 0;
        v_gmt_phi = 0;
        
        
        v_ltTwinMuxIn_wheel = 0;
        v_ltTwinMuxIn_sector = 0;
        v_ltTwinMuxIn_station = 0;
        v_ltTwinMuxIn_quality = 0;
        v_ltTwinMuxIn_bx = 0;
        v_ltTwinMuxIn_phi = 0;
        v_ltTwinMuxIn_iPhi = 0;
        v_ltTwinMuxIn_phiB = 0;
        
        
        v_ltTwinMuxOut_wheel = 0;
        v_ltTwinMuxOut_sector = 0;
        v_ltTwinMuxOut_station = 0;
        v_ltTwinMuxOut_quality = 0;
        v_ltTwinMuxOut_bx = 0;
        v_ltTwinMuxOut_phi = 0;
        v_ltTwinMuxOut_iPhi = 0;
        v_ltTwinMuxOut_phiB = 0;
        
        
        v_ltTwinMux_thBx = 0;
        v_ltTwinMux_thWheel = 0;
        v_ltTwinMux_thSector = 0;
        v_ltTwinMux_thStation = 0;
        v_ltTwinMux_thHits = 0;
        v_ltTwinMux_thPosition = 0;
        v_ltTwinMux_thQuality = 0;
        v_ltTwinMux_thIeta = 0;
        
        
        v_Mu_isMuGlobal = 0;
        v_Mu_isMuTracker = 0;
        v_Mu_isMuTight = 0;
        v_Mu_px = 0;
        v_Mu_py = 0;
        v_Mu_pz = 0;
        v_Mu_phi = 0;
        v_Mu_eta = 0;
        
        
        linkBranch();
    }
    
    
    void linkBranch()
    {
        tree->SetBranchAddress("runnumber", &runNumber);
        tree->SetBranchAddress("lumiblock", &lumiBlock);
        tree->SetBranchAddress("eventNumber", &eventNumber);
        
        tree->SetBranchAddress("hoTPdigi_bits", &v_hoTPdigi_bits);
        tree->SetBranchAddress("hoTPdigi_iEta", &v_hoTPdigi_iEta);
        tree->SetBranchAddress("hoTPdigi_iPhi", &v_hoTPdigi_iPhi);
        tree->SetBranchAddress("hoTPdigi_nSamples", &v_hoTPdigi_nSamples);
        tree->SetBranchAddress("hoTPdigi_raw", &v_hoTPdigi_raw);
        tree->SetBranchAddress("hoTPdigi_whichSampleTriggered", &v_hoTPdigi_whichSampleTriggered);
        
        tree->SetBranchAddress("dtsegm4D_wheel", &v_dtsegm4D_wheel);
        tree->SetBranchAddress("dtsegm4D_sector", &v_dtsegm4D_sector);
        tree->SetBranchAddress("dtsegm4D_station", &v_dtsegm4D_station);
        tree->SetBranchAddress("dtsegm4D_hasPhi", &v_dtsegm4D_hasPhi);
        tree->SetBranchAddress("dtsegm4D_hasZed", &v_dtsegm4D_hasZed);
        tree->SetBranchAddress("dtsegm4D_x_pos_loc", &v_dtsegm4D_x_pos_loc);
        tree->SetBranchAddress("dtsegm4D_y_pos_loc", &v_dtsegm4D_y_pos_loc);
        tree->SetBranchAddress("dtsegm4D_z_pos_loc", &v_dtsegm4D_z_pos_loc);
        tree->SetBranchAddress("dtsegm4D_x_dir_loc", &v_dtsegm4D_x_dir_loc);
        tree->SetBranchAddress("dtsegm4D_y_dir_loc", &v_dtsegm4D_y_dir_loc);
        tree->SetBranchAddress("dtsegm4D_z_dir_loc", &v_dtsegm4D_z_dir_loc);
        tree->SetBranchAddress("dtsegm4D_phi", &v_dtsegm4D_phi);
        tree->SetBranchAddress("dtsegm4D_theta", &v_dtsegm4D_theta);
        tree->SetBranchAddress("dtsegm4D_eta", &v_dtsegm4D_eta);
        tree->SetBranchAddress("dtsegm4D_phinhits", &v_dtsegm4D_phinhits);
        tree->SetBranchAddress("dtsegm4D_znhits", &v_dtsegm4D_znhits);
        
        tree->SetBranchAddress("gmt_bx", &v_gmt_bx);
        tree->SetBranchAddress("gmt_pt", &v_gmt_pT);
        tree->SetBranchAddress("gmt_eta", &v_gmt_eta);
        tree->SetBranchAddress("gmt_phi", &v_gmt_phi);
        
        tree->SetBranchAddress("ltTwinMuxIn_wheel", &v_ltTwinMuxIn_wheel);
        tree->SetBranchAddress("ltTwinMuxIn_sector", &v_ltTwinMuxIn_sector);
        tree->SetBranchAddress("ltTwinMuxIn_station", &v_ltTwinMuxIn_station);
        tree->SetBranchAddress("ltTwinMuxIn_quality", &v_ltTwinMuxIn_quality);
        tree->SetBranchAddress("ltTwinMuxIn_bx", &v_ltTwinMuxIn_bx);
        tree->SetBranchAddress("ltTwinMuxIn_phi", &v_ltTwinMuxIn_phi);
        tree->SetBranchAddress("ltTwinMuxIn_iPhi", &v_ltTwinMuxIn_iPhi);
        tree->SetBranchAddress("ltTwinMuxIn_phiB", &v_ltTwinMuxIn_phiB);
        
        tree->SetBranchAddress("ltTwinMuxOut_wheel", &v_ltTwinMuxOut_wheel);
        tree->SetBranchAddress("ltTwinMuxOut_sector", &v_ltTwinMuxOut_sector);
        tree->SetBranchAddress("ltTwinMuxOut_station", &v_ltTwinMuxOut_station);
        tree->SetBranchAddress("ltTwinMuxOut_quality", &v_ltTwinMuxOut_quality);
        tree->SetBranchAddress("ltTwinMuxOut_bx", &v_ltTwinMuxOut_bx);
        tree->SetBranchAddress("ltTwinMuxOut_phi", &v_ltTwinMuxOut_phi);
        tree->SetBranchAddress("ltTwinMuxOut_iPhi", &v_ltTwinMuxOut_iPhi);
        tree->SetBranchAddress("ltTwinMuxOut_phiB", &v_ltTwinMuxOut_phiB);
        
        tree->SetBranchAddress("ltTwinMux_thBx", &v_ltTwinMux_thBx);
        tree->SetBranchAddress("ltTwinMux_thWheel", &v_ltTwinMux_thWheel);
        tree->SetBranchAddress("ltTwinMux_thSector", &v_ltTwinMux_thSector);
        tree->SetBranchAddress("ltTwinMux_thStation", &v_ltTwinMux_thStation);
        tree->SetBranchAddress("ltTwinMux_thHits", &v_ltTwinMux_thHits);
        tree->SetBranchAddress("ltTwinMux_thPosition", &v_ltTwinMux_thPosition);
        tree->SetBranchAddress("ltTwinMux_thQuality", &v_ltTwinMux_thQuality);
        tree->SetBranchAddress("ltTwinMux_thIeta", &v_ltTwinMux_thIeta);
        
        tree->SetBranchAddress("Mu_isMuGlobal", &v_Mu_isMuGlobal);
        tree->SetBranchAddress("Mu_isMuTracker", &v_Mu_isMuTracker);
        tree->SetBranchAddress("Mu_isMuTight", &v_Mu_isMuTight);
        tree->SetBranchAddress("Mu_px", &v_Mu_px);
        tree->SetBranchAddress("Mu_py", &v_Mu_py);
        tree->SetBranchAddress("Mu_pz", &v_Mu_pz);
        tree->SetBranchAddress("Mu_phi", &v_Mu_phi);
        tree->SetBranchAddress("Mu_eta", &v_Mu_eta);
    }
    
    
    void freeMemory()
    {
        delete tree;
        
        inputFile->Close();
        delete inputFile;
    }
};


class OutputData
{
    public:
    
    
    //FILE *eventInfoFile;
    
    //TFile *outputFile;
    
    std::vector <TH1F*> v_h1_dtdegm4D_mu_pT;
    std::vector <TH1F*> v_h1_dtdegm4D_mu_eta;
    
    std::vector <TH1F*> v_h1_dtdegm4D_withDTTP_mu_pT;
    std::vector <TH1F*> v_h1_dtdegm4D_withDTTP_mu_eta;
    
    std::vector <TH1F*> v_h1_dtdegm4D_noDTTP_mu_pT;
    std::vector <TH1F*> v_h1_dtdegm4D_noDTTP_mu_eta;
    
    // Don't care about BMTF
    std::vector <TH1F*> v_h1_dtdegm4D_noDTTP_withMB1DTTP_mu_pT;
    std::vector <TH1F*> v_h1_dtdegm4D_noDTTP_withMB1DTTP_mu_eta;
    
    std::vector <TH1F*> v_h1_dtdegm4D_noDTTP_withMB1DTTP_withHOTP_mu_pT;
    std::vector <TH1F*> v_h1_dtdegm4D_noDTTP_withMB1DTTP_withHOTP_mu_eta;
    
    std::vector <TH1F*> v_h1_dtdegm4D_noDTTP_withMB1DTTP_withMipHOTP_mu_pT;
    std::vector <TH1F*> v_h1_dtdegm4D_noDTTP_withMB1DTTP_withMipHOTP_mu_eta;
    
    // BMTF must be present
    std::vector <TH1F*> v_h1_dtdegm4D_withDTTP_withBMTF_mu_pT;
    std::vector <TH1F*> v_h1_dtdegm4D_withDTTP_withBMTF_mu_eta;
    
    std::vector <TH1F*> v_h1_dtdegm4D_noDTTP_withBMTF_mu_pT;
    std::vector <TH1F*> v_h1_dtdegm4D_noDTTP_withBMTF_mu_eta;
    
    // BMTF must not be present
    std::vector <TH1F*> v_h1_dtdegm4D_noDTTP_noBMTF_mu_pT;
    std::vector <TH1F*> v_h1_dtdegm4D_noDTTP_noBMTF_mu_eta;
    
    std::vector <TH1F*> v_h1_dtdegm4D_noDTTP_noBMTF_withMB1DTTP_mu_pT;
    std::vector <TH1F*> v_h1_dtdegm4D_noDTTP_noBMTF_withMB1DTTP_mu_eta;
    
    std::vector <TH1F*> v_h1_dtdegm4D_noDTTP_noBMTF_withMB1DTTP_withHOTP_mu_pT;
    std::vector <TH1F*> v_h1_dtdegm4D_noDTTP_noBMTF_withMB1DTTP_withHOTP_mu_eta;
    
    
    //
    TH1F *h1_muon_withDTTP_mu_pT;
    TH1F *h1_muon_withDTTP_mu_eta;
    
    TH1F *h1_muon_withDTTP_withBMTF_mu_pT;
    TH1F *h1_muon_withDTTP_withBMTF_mu_eta;
    
    TH1F *h1_muon_noBMTF_withMB1DTTP_withHOTP_mu_pT;
    TH1F *h1_muon_noBMTF_withMB1DTTP_withHOTP_mu_eta;
    
    TH1F *h1_BMTF_withMuon_withDTTP_pT;
    TH1F *h1_BMTF_withMuon_withDTTP_eta;
    
    
    //
    TH1F *h1_MB1DTTP_deltaPhi;
    TH1F *h1_MB1DTTP_pT;
    
    TH1F *h1_unisolatedMB1DTTP_deltaBX;
    TH1F *h1_unisolatedMB1DTTP_deltaPhi;
    
    TH1F *h1_unisolatedMB1DTTP_pT;
    TH1F *h1_unisolatedMB1DTTP_HOTP_pT;
    
    TH2F *h2_unisolatedMB1DTTP_deltaBX_vs_deltaPhi;
    TH2F *h2_unisolatedMB1DTTP_pT_vs_deltaPhi;
    TH2F *h2_unisolatedMB1DTTP_pT_vs_phiB;
    TH2F *h2_unisolatedMB1DTTP_HOTP_deltaIphi_vs_deltaWheel;
    TH2F *h2_unisolatedMB1DTTP_HOTP_deltaIphi_vs_deltaIeta;
    TH2F *h2_unisolatedMB1DTTP_HOTP_deltaSector_vs_deltaWheel;
    TH2F *h2_unisolatedMB1DTTP_vs_HOTP_iPhi;
    TH2F *h2_unisolatedMB1DTTP_vs_HOTP_phiLocal;
    TH2F *h2_unisolatedMB1DTTP_vs_HOTP_iEta;
    TH2F *h2_unisolatedPlusMB1DTTP_vs_HOTP_etaLocal;
    TH2F *h2_unisolatedMinusMB1DTTP_vs_HOTP_etaLocal;
    TH2F *h2_unisolatedMB1DTTP_vs_HOTP_etaGlobal;
    
    //
    TH1F *h1_isolatedMB1DTTP_HOTP_deltaIphi;
    TH1F *h1_isolatedMB1DTTP_HOTP_deltaWheel;
    
    TH1F *h1_isolatedMB1DTTP_pT;
    TH1F *h1_isolatedMB1DTTP_HOTP_pT;
    
    TH2F *h2_isolatedMB1DTTP_pT_vs_phiB;
    TH2F *h2_isolatedMB1DTTP_HOTP_deltaIphi_vs_deltaWheel;
    TH2F *h2_isolatedMB1DTTP_HOTP_deltaIphi_vs_deltaIeta;
    TH2F *h2_isolatedMB1DTTP_HOTP_deltaSector_vs_deltaWheel;
    TH2F *h2_isolatedMB1DTTP_iPhi_vs_wheel;
    TH2F *h2_isolatedMB1DTTP_vs_HOTP_iPhi;
    TH2F *h2_isolatedMB1DTTP_vs_HOTP_phiLocal;
    TH2F *h2_isolatedMB1DTTP_vs_HOTP_iEta;
    
    TH2F *h2_isolatedPlusMB1DTTP_vs_HOTP_etaLocal;
    std::vector <TH1F*> v_h1_isolatedPlusMB1DTTP_etaLocal;
    
    TH2F *h2_isolatedMinusMB1DTTP_vs_HOTP_etaLocal;
    std::vector <TH1F*> v_h1_isolatedMinusMB1DTTP_etaLocal;
    
    TH2F *h2_isolatedMB1DTTP_vs_HOTP_etaLocal;
    TH2F *h2_isolatedMB1DTTP_vs_HOTP_etaGlobal;
    
    TH2F *h2_HOTP_iPhi_vs_wheel;
    
    //
    TH1F *h1_MB1DTTP_noDTTP_eta;
    TH1F *h1_MB1DTTP_noDTTP_withHOTP_eta;
    
    std::vector <TH2F*> v_h2_dtSegmentIeta_vs_thDigiIeta;
    
    OutputData(/*const char *outputFileName*/)
    {
        //outputFile = TFile::Open(outputFileName, "RECREATE");
        
        char histName[str_len];
        char histTitle[str_len];
        
        for(int iStation = 0; iStation < nStation; iStation++)
        {
            //
            sprintf(histName, "dtdegm4D_mu_pT_station%d", iStation+1);
            sprintf(histTitle, "dtdegm4D_mu_pT_station%d", iStation+1);
            v_h1_dtdegm4D_mu_pT.push_back(new TH1F(histName, histTitle, 100, 0, 1000));
            
            sprintf(histName, "dtdegm4D_mu_eta_station%d", iStation+1);
            sprintf(histTitle, "dtdegm4D_mu_eta_station%d", iStation+1);
            v_h1_dtdegm4D_mu_eta.push_back(new TH1F(histName, histTitle, 125, -3, 3));
            
            //
            sprintf(histName, "dtdegm4D_withDTTP_mu_pT_station%d", iStation+1);
            sprintf(histTitle, "dtdegm4D_withDTTP_mu_pT_station%d", iStation+1);
            v_h1_dtdegm4D_withDTTP_mu_pT.push_back(new TH1F(histName, histTitle, 100, 0, 1000));
            
            sprintf(histName, "dtdegm4D_withDTTP_mu_eta_station%d", iStation+1);
            sprintf(histTitle, "dtdegm4D_withDTTP_mu_eta_station%d", iStation+1);
            v_h1_dtdegm4D_withDTTP_mu_eta.push_back(new TH1F(histName, histTitle, 125, -3, 3));
            
            //
            sprintf(histName, "dtdegm4D_withDTTP_withBMTF_mu_pT_station%d", iStation+1);
            sprintf(histTitle, "dtdegm4D_withDTTP_withBMTF_mu_pT_station%d", iStation+1);
            v_h1_dtdegm4D_withDTTP_withBMTF_mu_pT.push_back(new TH1F(histName, histTitle, 100, 0, 1000));
            
            sprintf(histName, "dtdegm4D_withDTTP_withBMTF_mu_eta_station%d", iStation+1);
            sprintf(histTitle, "dtdegm4D_withDTTP_withBMTF_mu_eta_station%d", iStation+1);
            v_h1_dtdegm4D_withDTTP_withBMTF_mu_eta.push_back(new TH1F(histName, histTitle, 125, -3, 3));
            
            //
            sprintf(histName, "dtdegm4D_noDTTP_mu_pT_station%d", iStation+1);
            sprintf(histTitle, "dtdegm4D_noDTTP_mu_pT_station%d", iStation+1);
            v_h1_dtdegm4D_noDTTP_mu_pT.push_back(new TH1F(histName, histTitle, 100, 0, 1000));
            
            sprintf(histName, "dtdegm4D_noDTTP_mu_eta_station%d", iStation+1);
            sprintf(histTitle, "dtdegm4D_noDTTP_mu_eta_station%d", iStation+1);
            v_h1_dtdegm4D_noDTTP_mu_eta.push_back(new TH1F(histName, histTitle, 125, -3, 3));
            
            
            // Don't care about BMTF
            sprintf(histName, "dtdegm4D_noDTTP_withMB1DTTP_mu_pT_station%d", iStation+1);
            sprintf(histTitle, "dtdegm4D_noDTTP_withMB1DTTP_mu_pT_station%d", iStation+1);
            v_h1_dtdegm4D_noDTTP_withMB1DTTP_mu_pT.push_back(new TH1F(histName, histTitle, 100, 0, 1000));
            
            sprintf(histName, "dtdegm4D_noDTTP_withMB1DTTP_mu_eta_station%d", iStation+1);
            sprintf(histTitle, "dtdegm4D_noDTTP_withMB1DTTP_mu_eta_station%d", iStation+1);
            v_h1_dtdegm4D_noDTTP_withMB1DTTP_mu_eta.push_back(new TH1F(histName, histTitle, 125, -3, 3));
            
            //
            sprintf(histName, "dtdegm4D_noDTTP_withMB1DTTP_withHOTP_mu_pT_station%d", iStation+1);
            sprintf(histTitle, "dtdegm4D_noDTTP_withMB1DTTP_withHOTP_mu_pT_station%d", iStation+1);
            v_h1_dtdegm4D_noDTTP_withMB1DTTP_withHOTP_mu_pT.push_back(new TH1F(histName, histTitle, 100, 0, 1000));
            
            sprintf(histName, "dtdegm4D_noDTTP_withMB1DTTP_withHOTP_mu_eta_station%d", iStation+1);
            sprintf(histTitle, "dtdegm4D_noDTTP_withMB1DTTP_withHOTP_mu_eta_station%d", iStation+1);
            v_h1_dtdegm4D_noDTTP_withMB1DTTP_withHOTP_mu_eta.push_back(new TH1F(histName, histTitle, 125, -3, 3));
            
            //
            sprintf(histName, "dtdegm4D_noDTTP_withMB1DTTP_withMipHOTP_mu_pT_station%d", iStation+1);
            sprintf(histTitle, "dtdegm4D_noDTTP_withMB1DTTP_withMipHOTP_mu_pT_station%d", iStation+1);
            v_h1_dtdegm4D_noDTTP_withMB1DTTP_withMipHOTP_mu_pT.push_back(new TH1F(histName, histTitle, 100, 0, 1000));
            
            sprintf(histName, "dtdegm4D_noDTTP_withMB1DTTP_withMipHOTP_mu_eta_station%d", iStation+1);
            sprintf(histTitle, "dtdegm4D_noDTTP_withMB1DTTP_withMipHOTP_mu_eta_station%d", iStation+1);
            v_h1_dtdegm4D_noDTTP_withMB1DTTP_withMipHOTP_mu_eta.push_back(new TH1F(histName, histTitle, 125, -3, 3));
            
            
            // BMTF must be present
            sprintf(histName, "dtdegm4D_noDTTP_withBMTF_mu_pT_station%d", iStation+1);
            sprintf(histTitle, "dtdegm4D_noDTTP_withBMTF_mu_pT_station%d", iStation+1);
            v_h1_dtdegm4D_noDTTP_withBMTF_mu_pT.push_back(new TH1F(histName, histTitle, 100, 0, 1000));
            
            sprintf(histName, "dtdegm4D_noDTTP_withBMTF_mu_eta_station%d", iStation+1);
            sprintf(histTitle, "dtdegm4D_noDTTP_withBMTF_mu_eta_station%d", iStation+1);
            v_h1_dtdegm4D_noDTTP_withBMTF_mu_eta.push_back(new TH1F(histName, histTitle, 125, -3, 3));
            
            
            // BMTF must not be present
            sprintf(histName, "dtdegm4D_noDTTP_noBMTF_mu_pT_station%d", iStation+1);
            sprintf(histTitle, "dtdegm4D_noDTTP_noBMTF_mu_pT_station%d", iStation+1);
            v_h1_dtdegm4D_noDTTP_noBMTF_mu_pT.push_back(new TH1F(histName, histTitle, 100, 0, 1000));
            
            sprintf(histName, "dtdegm4D_noDTTP_noBMTF_mu_eta_station%d", iStation+1);
            sprintf(histTitle, "dtdegm4D_noDTTP_noBMTF_mu_eta_station%d", iStation+1);
            v_h1_dtdegm4D_noDTTP_noBMTF_mu_eta.push_back(new TH1F(histName, histTitle, 125, -3, 3));
            
            //
            sprintf(histName, "dtdegm4D_noDTTP_noBMTF_withMB1DTTP_mu_pT_station%d", iStation+1);
            sprintf(histTitle, "dtdegm4D_noDTTP_noBMTF_withMB1DTTP_mu_pT_station%d", iStation+1);
            v_h1_dtdegm4D_noDTTP_noBMTF_withMB1DTTP_mu_pT.push_back(new TH1F(histName, histTitle, 100, 0, 1000));
            
            sprintf(histName, "dtdegm4D_noDTTP_noBMTF_withMB1DTTP_mu_eta_station%d", iStation+1);
            sprintf(histTitle, "dtdegm4D_noDTTP_noBMTF_withMB1DTTP_mu_eta_station%d", iStation+1);
            v_h1_dtdegm4D_noDTTP_noBMTF_withMB1DTTP_mu_eta.push_back(new TH1F(histName, histTitle, 125, -3, 3));
            
            //
            sprintf(histName, "dtdegm4D_noDTTP_noBMTF_withMB1DTTP_withHOTP_mu_pT_station%d", iStation+1);
            sprintf(histTitle, "dtdegm4D_noDTTP_noBMTF_withMB1DTTP_withHOTP_mu_pT_station%d", iStation+1);
            v_h1_dtdegm4D_noDTTP_noBMTF_withMB1DTTP_withHOTP_mu_pT.push_back(new TH1F(histName, histTitle, 100, 0, 1000));
            
            sprintf(histName, "dtdegm4D_noDTTP_noBMTF_withMB1DTTP_withHOTP_mu_eta_station%d", iStation+1);
            sprintf(histTitle, "dtdegm4D_noDTTP_noBMTF_withMB1DTTP_withHOTP_mu_eta_station%d", iStation+1);
            v_h1_dtdegm4D_noDTTP_noBMTF_withMB1DTTP_withHOTP_mu_eta.push_back(new TH1F(histName, histTitle, 125, -3, 3));
            
            //
            sprintf(histName, "dtSegmentIeta_vs_thDigiIeta_station%d", iStation+1);
            sprintf(histTitle, "dtSegmentIeta_vs_thDigiIeta_station%d", iStation+1);
            v_h2_dtSegmentIeta_vs_thDigiIeta.push_back(new TH2F(histName, histTitle, 40, -20, 20, 40, -20, 20));
        }
        
        //
        sprintf(histName, "muon_withDTTP_mu_pT");
        sprintf(histTitle, "muon_withDTTP_mu_pT");
        h1_muon_withDTTP_mu_pT = new TH1F(histName, histTitle, 100, 0, 1000);
        
        sprintf(histName, "muon_withDTTP_mu_eta");
        sprintf(histTitle, "muon_withDTTP_mu_eta");
        h1_muon_withDTTP_mu_eta = new TH1F(histName, histTitle, 125, -3, 3);
        
        //
        sprintf(histName, "muon_withDTTP_withBMTF_mu_pT");
        sprintf(histTitle, "muon_withDTTP_withBMTF_mu_pT");
        h1_muon_withDTTP_withBMTF_mu_pT = new TH1F(histName, histTitle, 100, 0, 1000);
        
        sprintf(histName, "muon_withDTTP_withBMTF_mu_eta");
        sprintf(histTitle, "muon_withDTTP_withBMTF_mu_eta");
        h1_muon_withDTTP_withBMTF_mu_eta = new TH1F(histName, histTitle, 125, -3, 3);
        
        //
        sprintf(histName, "muon_noBMTF_withMB1DTTP_withHOTP_mu_pT");
        sprintf(histTitle, "muon_noBMTF_withMB1DTTP_withHOTP_mu_pT");
        h1_muon_noBMTF_withMB1DTTP_withHOTP_mu_pT = new TH1F(histName, histTitle, 100, 0, 1000);
        
        sprintf(histName, "muon_noBMTF_withMB1DTTP_withHOTP_mu_eta");
        sprintf(histTitle, "muon_noBMTF_withMB1DTTP_withHOTP_mu_eta");
        h1_muon_noBMTF_withMB1DTTP_withHOTP_mu_eta = new TH1F(histName, histTitle, 125, -3, 3);
        
        //
        sprintf(histName, "BMTF_withMuon_withDTTP_pT");
        sprintf(histTitle, "BMTF_withMuon_withDTTP_pT");
        h1_BMTF_withMuon_withDTTP_pT = new TH1F(histName, histTitle, 100, 0, 1000);
        
        sprintf(histName, "BMTF_withMuon_withDTTP_eta");
        sprintf(histTitle, "BMTF_withMuon_withDTTP_eta");
        h1_BMTF_withMuon_withDTTP_eta = new TH1F(histName, histTitle, 125, -3, 3);
        
        
        //
        sprintf(histName, "MB1DTTP_noDTTP_eta");
        sprintf(histTitle, "MB1DTTP_noDTTP_eta");
        h1_MB1DTTP_noDTTP_eta = new TH1F(histName, histTitle, 125, -3, 3);
        
        sprintf(histName, "MB1DTTP_noDTTP_withHOTP_eta");
        sprintf(histTitle, "MB1DTTP_noDTTP_withHOTP_eta");
        h1_MB1DTTP_noDTTP_withHOTP_eta = new TH1F(histName, histTitle, 125, -3, 3);
        
        
        //
        double binWidth_phi = 0.025;
        
        sprintf(histName, "MB1DTTP_deltaPhi");
        sprintf(histTitle, "MB1DTTP_deltaPhi");
        h1_MB1DTTP_deltaPhi = new TH1F(histName, histTitle, (int) (2.0*5/binWidth_phi), -5, 5);
        
        sprintf(histName, "MB1DTTP_pT");
        sprintf(histTitle, "MB1DTTP_pT");
        h1_MB1DTTP_pT = new TH1F(histName, histTitle, 200, 0, 200);
        
        sprintf(histName, "unisolatedMB1DTTP_deltaBX");
        sprintf(histTitle, "unisolatedMB1DTTP_deltaBX");
        h1_unisolatedMB1DTTP_deltaBX = new TH1F(histName, histTitle, 10, 0, 10);
        
        sprintf(histName, "unisolatedMB1DTTP_deltaPhi");
        sprintf(histTitle, "unisolatedMB1DTTP_deltaPhi");
        h1_unisolatedMB1DTTP_deltaPhi = new TH1F(histName, histTitle, (int) (2*DT_deltaPhicut/binWidth_phi), -DT_deltaPhicut, DT_deltaPhicut);
        
        sprintf(histName, "unisolatedMB1DTTP_pT");
        sprintf(histTitle, "unisolatedMB1DTTP_pT");
        h1_unisolatedMB1DTTP_pT = new TH1F(histName, histTitle, 200, 0, 200);
        
        sprintf(histName, "unisolatedMB1DTTP_HOTP_pT");
        sprintf(histTitle, "unisolatedMB1DTTP_HOTP_pT");
        h1_unisolatedMB1DTTP_HOTP_pT = new TH1F(histName, histTitle, 200, 0, 200);
        
        sprintf(histName, "unisolatedMB1DTTP_deltaBX_vs_deltaPhi");
        sprintf(histTitle, "unisolatedMB1DTTP_deltaBX_vs_deltaPhi");
        h2_unisolatedMB1DTTP_deltaBX_vs_deltaPhi = new TH2F(histName, histTitle, (int) (2*DT_deltaPhicut/binWidth_phi), -DT_deltaPhicut, DT_deltaPhicut, 10, 0, 10);
        
        sprintf(histName, "unisolatedMB1DTTP_pT_vs_deltaPhi");
        sprintf(histTitle, "unisolatedMB1DTTP_pT_vs_deltaPhi");
        h2_unisolatedMB1DTTP_pT_vs_deltaPhi = new TH2F(histName, histTitle, (int) (2*DT_deltaPhicut/binWidth_phi), -DT_deltaPhicut, DT_deltaPhicut, 200, 0, 200);
        
        sprintf(histName, "unisolatedMB1DTTP_pT_vs_phiB");
        sprintf(histTitle, "unisolatedMB1DTTP_pT_vs_phiB");
        h2_unisolatedMB1DTTP_pT_vs_phiB = new TH2F(histName, histTitle, 1200, -600, 600, 200, 0, 200);
        
        sprintf(histName, "unisolatedMB1DTTP_HOTP_deltaIphi_vs_deltaWheel");
        sprintf(histTitle, "unisolatedMB1DTTP_HOTP_deltaIphi_vs_deltaWheel");
        h2_unisolatedMB1DTTP_HOTP_deltaIphi_vs_deltaWheel = new TH2F(histName, histTitle, 10, -5, 5, 20, -10, 10);
        
        sprintf(histName, "unisolatedMB1DTTP_HOTP_deltaIphi_vs_deltaIeta");
        sprintf(histTitle, "unisolatedMB1DTTP_HOTP_deltaIphi_vs_deltaIeta");
        h2_unisolatedMB1DTTP_HOTP_deltaIphi_vs_deltaIeta = new TH2F(histName, histTitle, 20, -10, 10, 20, -10, 10);
        
        sprintf(histName, "unisolatedMB1DTTP_HOTP_deltaSector_vs_deltaWheel");
        sprintf(histTitle, "unisolatedMB1DTTP_HOTP_deltaSector_vs_deltaWheel");
        h2_unisolatedMB1DTTP_HOTP_deltaSector_vs_deltaWheel = new TH2F(histName, histTitle, 10, -5, 5, 10, -5, 5);
        
        sprintf(histName, "unisolatedMB1DTTP_vs_HOTP_iPhi");
        sprintf(histTitle, "unisolatedMB1DTTP_vs_HOTP_iPhi");
        h2_unisolatedMB1DTTP_vs_HOTP_iPhi = new TH2F(histName, histTitle, 80, 0, 80, 80, 0, 80);
        
        sprintf(histName, "unisolatedMB1DTTP_vs_HOTP_phiLocal");
        sprintf(histTitle, "unisolatedMB1DTTP_vs_HOTP_phiLocal");
        h2_unisolatedMB1DTTP_vs_HOTP_phiLocal = new TH2F(histName, histTitle, 10, 0, 10, 5000, -2500, 2500);
        
        sprintf(histName, "unisolatedMB1DTTP_vs_HOTP_iEta");
        sprintf(histTitle, "unisolatedMB1DTTP_vs_HOTP_iEta");
        h2_unisolatedMB1DTTP_vs_HOTP_iEta = new TH2F(histName, histTitle, 40, -20, 20, 40, -20, 20);
        
        sprintf(histName, "unisolatedPlusMB1DTTP_vs_HOTP_etaLocal");
        sprintf(histTitle, "unisolatedPlusMB1DTTP_vs_HOTP_etaLocal");
        h2_unisolatedPlusMB1DTTP_vs_HOTP_etaLocal = new TH2F(histName, histTitle, 40, -20, 20, 10, 0, 10);
        
        sprintf(histName, "unisolatedMinusMB1DTTP_vs_HOTP_etaLocal");
        sprintf(histTitle, "unisolatedMinusMB1DTTP_vs_HOTP_etaLocal");
        h2_unisolatedMinusMB1DTTP_vs_HOTP_etaLocal = new TH2F(histName, histTitle, 40, -20, 20, 10, 0, 10);
        
        sprintf(histName, "unisolatedMB1DTTP_vs_HOTP_etaGlobal");
        sprintf(histTitle, "unisolatedMB1DTTP_vs_HOTP_etaGlobal");
        h2_unisolatedMB1DTTP_vs_HOTP_etaGlobal = new TH2F(histName, histTitle, 40, -20, 20, 50, 0, 50);
        
        
        //
        sprintf(histName, "isolatedMB1DTTP_HOTP_deltaIphi");
        sprintf(histTitle, "isolatedMB1DTTP_HOTP_deltaIphi");
        h1_isolatedMB1DTTP_HOTP_deltaIphi = new TH1F(histName, histTitle, 20, -10, 10);
        
        sprintf(histName, "isolatedMB1DTTP_HOTP_deltaWheel");
        sprintf(histTitle, "isolatedMB1DTTP_HOTP_deltaWheel");
        h1_isolatedMB1DTTP_HOTP_deltaWheel = new TH1F(histName, histTitle, 10, -5, 5);
        
        sprintf(histName, "isolatedMB1DTTP_pT");
        sprintf(histTitle, "isolatedMB1DTTP_pT");
        h1_isolatedMB1DTTP_pT = new TH1F(histName, histTitle, 200, 0, 200);
        
        sprintf(histName, "isolatedMB1DTTP_HOTP_pT");
        sprintf(histTitle, "isolatedMB1DTTP_HOTP_pT");
        h1_isolatedMB1DTTP_HOTP_pT = new TH1F(histName, histTitle, 200, 0, 200);
        
        sprintf(histName, "isolatedMB1DTTP_pT_vs_phiB");
        sprintf(histTitle, "isolatedMB1DTTP_pT_vs_phiB");
        h2_isolatedMB1DTTP_pT_vs_phiB = new TH2F(histName, histTitle, 1200, -600, 600, 200, 0, 200);
        
        sprintf(histName, "isolatedMB1DTTP_HOTP_deltaIphi_vs_deltaWheel");
        sprintf(histTitle, "isolatedMB1DTTP_HOTP_deltaIphi_vs_deltaWheel");
        h2_isolatedMB1DTTP_HOTP_deltaIphi_vs_deltaWheel = new TH2F(histName, histTitle, 10, -5, 5, 20, -10, 10);
        
        sprintf(histName, "isolatedMB1DTTP_HOTP_deltaIphi_vs_deltaIeta");
        sprintf(histTitle, "isolatedMB1DTTP_HOTP_deltaIphi_vs_deltaIeta");
        h2_isolatedMB1DTTP_HOTP_deltaIphi_vs_deltaIeta = new TH2F(histName, histTitle, 20, -10, 10, 20, -10, 10);
        
        sprintf(histName, "isolatedMB1DTTP_HOTP_deltaSector_vs_deltaWheel");
        sprintf(histTitle, "isolatedMB1DTTP_HOTP_deltaSector_vs_deltaWheel");
        h2_isolatedMB1DTTP_HOTP_deltaSector_vs_deltaWheel = new TH2F(histName, histTitle, 10, -5, 5, 10, -5, 5);
        
        sprintf(histName, "isolatedMB1DTTP_iPhi_vs_wheel");
        sprintf(histTitle, "isolatedMB1DTTP_iPhi_vs_wheel");
        h2_isolatedMB1DTTP_iPhi_vs_wheel = new TH2F(histName, histTitle, 6, -2, 4, 80, 0, 80);
        
        sprintf(histName, "isolatedMB1DTTP_vs_HOTP_iPhi");
        sprintf(histTitle, "isolatedMB1DTTP_vs_HOTP_iPhi");
        h2_isolatedMB1DTTP_vs_HOTP_iPhi = new TH2F(histName, histTitle, 80, 0, 80, 80, 0, 80);
        
        sprintf(histName, "isolatedMB1DTTP_vs_HOTP_phiLocal");
        sprintf(histTitle, "isolatedMB1DTTP_vs_HOTP_phiLocal");
        h2_isolatedMB1DTTP_vs_HOTP_phiLocal = new TH2F(histName, histTitle, 10, 0, 10, 5000, -2500, 2500);
        
        sprintf(histName, "isolatedMB1DTTP_vs_HOTP_iEta");
        sprintf(histTitle, "isolatedMB1DTTP_vs_HOTP_iEta");
        h2_isolatedMB1DTTP_vs_HOTP_iEta = new TH2F(histName, histTitle, 40, -20, 20, 40, -20, 20);
        
        sprintf(histName, "isolatedPlusMB1DTTP_vs_HOTP_etaLocal");
        sprintf(histTitle, "isolatedPlusMB1DTTP_vs_HOTP_etaLocal");
        h2_isolatedPlusMB1DTTP_vs_HOTP_etaLocal = new TH2F(histName, histTitle, 40, -20, 20, 10, 0, 10);
        
        sprintf(histName, "isolatedMinusMB1DTTP_vs_HOTP_etaLocal");
        sprintf(histTitle, "isolatedMinusMB1DTTP_vs_HOTP_etaLocal");
        h2_isolatedMinusMB1DTTP_vs_HOTP_etaLocal = new TH2F(histName, histTitle, 40, -20, 20, 10, 0, 10);
        
        sprintf(histName, "isolatedMB1DTTP_vs_HOTP_etaGlobal");
        sprintf(histTitle, "isolatedMB1DTTP_vs_HOTP_etaGlobal");
        h2_isolatedMB1DTTP_vs_HOTP_etaGlobal = new TH2F(histName, histTitle, 40, -20, 20, 50, 0, 50);
        
        
        sprintf(histName, "HOTP_iPhi_vs_wheel");
        sprintf(histTitle, "HOTP_iPhi_vs_wheel");
        h2_HOTP_iPhi_vs_wheel = new TH2F(histName, histTitle, 6, -2, 4, 80, 0, 80);
    }
    
    
    void writeData()
    {
        /*for(int iStation = 0; iStation < nStation; iStation++)
        {
            v_h1_dtdegm4D_mu_pT.at(iStation)->Write();
            v_h1_dtdegm4D_mu_eta.at(iStation)->Write();
            
            v_h1_dtdegm4D_withDTTP_mu_pT.at(iStation)->Write();
            v_h1_dtdegm4D_withDTTP_mu_eta.at(iStation)->Write();
            
            v_h1_dtdegm4D_withDTTP_withBMTF_mu_pT.at(iStation)->Write();
            v_h1_dtdegm4D_withDTTP_withBMTF_mu_eta.at(iStation)->Write();
            
            v_h1_dtdegm4D_noDTTP_mu_pT.at(iStation)->Write();
            v_h1_dtdegm4D_noDTTP_mu_eta.at(iStation)->Write();
            
            
            v_h1_dtdegm4D_noDTTP_withMB1DTTP_mu_pT.at(iStation)->Write();
            v_h1_dtdegm4D_noDTTP_withMB1DTTP_mu_eta.at(iStation)->Write();
            
            v_h1_dtdegm4D_noDTTP_withMB1DTTP_withHOTP_mu_pT.at(iStation)->Write();
            v_h1_dtdegm4D_noDTTP_withMB1DTTP_withHOTP_mu_eta.at(iStation)->Write();
            
            v_h1_dtdegm4D_noDTTP_withMB1DTTP_withMipHOTP_mu_pT.at(iStation)->Write();
            v_h1_dtdegm4D_noDTTP_withMB1DTTP_withMipHOTP_mu_eta.at(iStation)->Write();
            
            
            v_h1_dtdegm4D_noDTTP_withBMTF_mu_pT.at(iStation)->Write();
            v_h1_dtdegm4D_noDTTP_withBMTF_mu_eta.at(iStation)->Write();
            
            
            v_h1_dtdegm4D_noDTTP_noBMTF_mu_pT.at(iStation)->Write();
            v_h1_dtdegm4D_noDTTP_noBMTF_mu_eta.at(iStation)->Write();
            
            v_h1_dtdegm4D_noDTTP_noBMTF_withMB1DTTP_mu_pT.at(iStation)->Write();
            v_h1_dtdegm4D_noDTTP_noBMTF_withMB1DTTP_mu_eta.at(iStation)->Write();
            
            v_h1_dtdegm4D_noDTTP_noBMTF_withMB1DTTP_withHOTP_mu_pT.at(iStation)->Write();
            v_h1_dtdegm4D_noDTTP_noBMTF_withMB1DTTP_withHOTP_mu_eta.at(iStation)->Write();
            
            
            v_h2_dtSegmentIeta_vs_thDigiIeta.at(iStation)->Write();
        }
        
        h1_muon_withDTTP_mu_pT->Write();
        h1_muon_withDTTP_mu_eta->Write();
        
        h1_muon_withDTTP_withBMTF_mu_pT->Write();
        h1_muon_withDTTP_withBMTF_mu_eta->Write();
        
        h1_muon_noBMTF_withMB1DTTP_withHOTP_mu_pT->Write();
        h1_muon_noBMTF_withMB1DTTP_withHOTP_mu_eta->Write();
        
        h1_BMTF_withMuon_withDTTP_pT->Write();
        h1_BMTF_withMuon_withDTTP_eta->Write();*/
        
        h1_MB1DTTP_deltaPhi->Write();
        h1_MB1DTTP_pT->Write();
        
        h1_unisolatedMB1DTTP_deltaBX->Write();
        h1_unisolatedMB1DTTP_deltaPhi->Write();
        h1_unisolatedMB1DTTP_pT->Write();
        h1_unisolatedMB1DTTP_HOTP_pT->Write();
        
        h2_unisolatedMB1DTTP_deltaBX_vs_deltaPhi->Write();
        h2_unisolatedMB1DTTP_pT_vs_deltaPhi->Write();
        h2_unisolatedMB1DTTP_pT_vs_phiB->Write();
        h2_unisolatedMB1DTTP_HOTP_deltaIphi_vs_deltaWheel->Write();
        h2_unisolatedMB1DTTP_HOTP_deltaIphi_vs_deltaIeta->Write();
        h2_unisolatedMB1DTTP_HOTP_deltaSector_vs_deltaWheel->Write();
        h2_unisolatedMB1DTTP_vs_HOTP_iPhi->Write();
        h2_unisolatedMB1DTTP_vs_HOTP_phiLocal->Write();
        h2_unisolatedMB1DTTP_vs_HOTP_iEta->Write();
        h2_unisolatedPlusMB1DTTP_vs_HOTP_etaLocal->Write();
        h2_unisolatedMinusMB1DTTP_vs_HOTP_etaLocal->Write();
        h2_unisolatedMB1DTTP_vs_HOTP_etaGlobal->Write();
        
        h1_isolatedMB1DTTP_HOTP_deltaIphi->Write();
        h1_isolatedMB1DTTP_HOTP_deltaWheel->Write();
        h1_isolatedMB1DTTP_pT->Write();
        h1_isolatedMB1DTTP_HOTP_pT->Write();
        
        h2_isolatedMB1DTTP_pT_vs_phiB->Write();
        h2_isolatedMB1DTTP_HOTP_deltaIphi_vs_deltaWheel->Write();
        h2_isolatedMB1DTTP_HOTP_deltaIphi_vs_deltaIeta->Write();
        h2_isolatedMB1DTTP_HOTP_deltaSector_vs_deltaWheel->Write();
        h2_isolatedMB1DTTP_vs_HOTP_iPhi->Write();
        h2_isolatedMB1DTTP_vs_HOTP_phiLocal->Write();
        h2_isolatedMB1DTTP_vs_HOTP_iEta->Write();
        h2_isolatedPlusMB1DTTP_vs_HOTP_etaLocal->Write();
        h2_isolatedMinusMB1DTTP_vs_HOTP_etaLocal->Write();
        h2_isolatedMB1DTTP_vs_HOTP_etaGlobal->Write();
        
        h2_isolatedMB1DTTP_iPhi_vs_wheel->Write();
        
        h2_HOTP_iPhi_vs_wheel->Write();
    }
    
    
    void freeMemory()
    {
        for(int iStation = 0; iStation < nStation; iStation++)
        {
            delete v_h1_dtdegm4D_mu_pT.at(iStation);
            delete v_h1_dtdegm4D_mu_eta.at(iStation);
            
            delete v_h1_dtdegm4D_withDTTP_mu_pT.at(iStation);
            delete v_h1_dtdegm4D_withDTTP_mu_eta.at(iStation);
            
            delete v_h1_dtdegm4D_withDTTP_withBMTF_mu_pT.at(iStation);
            delete v_h1_dtdegm4D_withDTTP_withBMTF_mu_eta.at(iStation);
            
            delete v_h1_dtdegm4D_noDTTP_mu_pT.at(iStation);
            delete v_h1_dtdegm4D_noDTTP_mu_eta.at(iStation);
            
            
            delete v_h1_dtdegm4D_noDTTP_withMB1DTTP_mu_pT.at(iStation);
            delete v_h1_dtdegm4D_noDTTP_withMB1DTTP_mu_eta.at(iStation);
            
            delete v_h1_dtdegm4D_noDTTP_withMB1DTTP_withHOTP_mu_pT.at(iStation);
            delete v_h1_dtdegm4D_noDTTP_withMB1DTTP_withHOTP_mu_eta.at(iStation);
            
            delete v_h1_dtdegm4D_noDTTP_withMB1DTTP_withMipHOTP_mu_pT.at(iStation);
            delete v_h1_dtdegm4D_noDTTP_withMB1DTTP_withMipHOTP_mu_eta.at(iStation);
            
            
            delete v_h1_dtdegm4D_noDTTP_withBMTF_mu_pT.at(iStation);
            delete v_h1_dtdegm4D_noDTTP_withBMTF_mu_eta.at(iStation);
            
            
            delete v_h1_dtdegm4D_noDTTP_noBMTF_mu_pT.at(iStation);
            delete v_h1_dtdegm4D_noDTTP_noBMTF_mu_eta.at(iStation);
            
            delete v_h1_dtdegm4D_noDTTP_noBMTF_withMB1DTTP_mu_pT.at(iStation);
            delete v_h1_dtdegm4D_noDTTP_noBMTF_withMB1DTTP_mu_eta.at(iStation);
            
            delete v_h1_dtdegm4D_noDTTP_noBMTF_withMB1DTTP_withHOTP_mu_pT.at(iStation);
            delete v_h1_dtdegm4D_noDTTP_noBMTF_withMB1DTTP_withHOTP_mu_eta.at(iStation);
            
            
            delete v_h2_dtSegmentIeta_vs_thDigiIeta.at(iStation);
        }
        
        delete h1_muon_withDTTP_mu_pT;
        delete h1_muon_withDTTP_mu_eta;
        
        delete h1_muon_withDTTP_withBMTF_mu_pT;
        delete h1_muon_withDTTP_withBMTF_mu_eta;
        
        delete h1_muon_noBMTF_withMB1DTTP_withHOTP_mu_pT;
        delete h1_muon_noBMTF_withMB1DTTP_withHOTP_mu_eta;
        
        delete h1_BMTF_withMuon_withDTTP_pT;
        delete h1_BMTF_withMuon_withDTTP_eta;
        
        delete h1_MB1DTTP_deltaPhi;
        delete h1_MB1DTTP_pT;
        
        delete h1_unisolatedMB1DTTP_deltaBX;
        delete h1_unisolatedMB1DTTP_deltaPhi;
        delete h1_unisolatedMB1DTTP_pT;
        delete h1_unisolatedMB1DTTP_HOTP_pT;
        
        delete h2_unisolatedMB1DTTP_deltaBX_vs_deltaPhi;
        delete h2_unisolatedMB1DTTP_pT_vs_deltaPhi;
        delete h2_unisolatedMB1DTTP_pT_vs_phiB;
        delete h2_unisolatedMB1DTTP_HOTP_deltaIphi_vs_deltaWheel;
        delete h2_unisolatedMB1DTTP_HOTP_deltaIphi_vs_deltaIeta;
        delete h2_unisolatedMB1DTTP_HOTP_deltaSector_vs_deltaWheel;
        delete h2_unisolatedMB1DTTP_vs_HOTP_iPhi;
        delete h2_unisolatedMB1DTTP_vs_HOTP_phiLocal;
        delete h2_unisolatedMB1DTTP_vs_HOTP_iEta;
        delete h2_unisolatedPlusMB1DTTP_vs_HOTP_etaLocal;
        delete h2_unisolatedMinusMB1DTTP_vs_HOTP_etaLocal;
        delete h2_unisolatedMB1DTTP_vs_HOTP_etaGlobal;
        
        delete h1_isolatedMB1DTTP_HOTP_deltaIphi;
        delete h1_isolatedMB1DTTP_HOTP_deltaWheel;
        delete h1_isolatedMB1DTTP_pT;
        delete h1_isolatedMB1DTTP_HOTP_pT;
        
        delete h2_isolatedMB1DTTP_pT_vs_phiB;
        delete h2_isolatedMB1DTTP_HOTP_deltaIphi_vs_deltaWheel;
        delete h2_isolatedMB1DTTP_HOTP_deltaIphi_vs_deltaIeta;
        delete h2_isolatedMB1DTTP_HOTP_deltaSector_vs_deltaWheel;
        delete h2_isolatedMB1DTTP_iPhi_vs_wheel;
        delete h2_isolatedMB1DTTP_vs_HOTP_iPhi;
        delete h2_isolatedMB1DTTP_vs_HOTP_phiLocal;
        delete h2_isolatedMB1DTTP_vs_HOTP_iEta;
        delete h2_isolatedPlusMB1DTTP_vs_HOTP_etaLocal;
        delete h2_isolatedMinusMB1DTTP_vs_HOTP_etaLocal;
        delete h2_isolatedMB1DTTP_vs_HOTP_etaGlobal;
        
        
        delete h2_HOTP_iPhi_vs_wheel;
        
        //outputFile->Close();
        //delete outputFile;
    }
};


void analyze(InputData *input, OutputData *output, OutputData *output_LQ, OutputData *output_HQ);
double globalPhiFromDTphi(double phi, int secNum);
double HOiEtaToEta(int iEta);
double HOiPhiToPhi(int iEta);

int getIetaFromEta(double eta);
int getSectorFromIphi(int iPhi);
int getWheelFromIeta(int iEta);
bool isInSameWheel(double eta, int whNum);
bool isInSameWheel(int iEta, int whNum);

int getDTorientation(int whNum, int scNum);

void parseCSV_runInfo();
void parseCSV_pTlut();
double getLumi(long runNumber);
double getPtFromPhiB(int PhiB);

void updateCounterMap(std::map <long, std::map <int, std::vector <int> > > *myMap, long runNumber, int pos);
void updateCounterMap(std::map <long, std::map <int, std::vector <int> > > *myMap, long runNumber, int pos, double pT);


int main()
{
    std::string process;
    
    //process = "SingleMuon";
    process = "ZeroBias9";
    
    // Read run, lumi etc. info
    parseCSV_runInfo();
    
    // Read phiB vs. pT
    parseCSV_pTlut();
    
    char sourceFileList[500];
    sprintf(sourceFileList, "sourceFiles/%s/%s.txt", process.c_str(), process.c_str());
    printf("Source file list: %s \n", sourceFileList);
    
    std::vector <std::string> v_sourceFileName = {};
    
    //v_sourceFileName.push_back("root://eoscms.cern.ch//eos/cms/store/group/dpg_dt/comm_dt/dtRootple2016/Run2016HZMuPromptReco-v2.root");
    
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
    
    //nEvent_global_max = 2*pow(10, 6);
    //nEvent_global_max = 10000;
    
    int n = 0;
    // Analyze input files
    for(int iFile = 0; iFile < v_sourceFileName.size(); iFile++)
    {
        n++; if(n > 50) break; 
        std::string inputFileName = v_sourceFileName.at(iFile);
        
        printf("Input file: %s \n", inputFileName.c_str());
        InputData *input = new InputData(inputFileName.c_str());
        
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
        
        if(nEvent_global_max > 0 && nEvent_global > nEvent_global_max)
        {
            break;
        }
        
        printf("\n");
    }
    
    for(int iPtCut = 0; iPtCut < v_pTcut.size(); iPtCut++)
    {
        int pTcut = v_pTcut.at(iPtCut);
        
        char textFileName[500];
        sprintf(textFileName, "%s/isolatedMB1_pT%d.txt", outputDir, pTcut);
        FILE *textFile = fopen(textFileName, "w");
        
        std::map <long, std::map <int, std::vector <int> > >::iterator iEle_LQ = m_MB1_LQ.begin();
        std::map <long, std::map <int, std::vector <int> > >::iterator iEle_HQ = m_MB1_HQ.begin();
        
        fprintf(textFile, \
            "#runNumber,lumi per LS (/fb),"
            "nEvent,"
            
            "HOTP,HOTP_SOI,rate_HOTP_SOI [kHz],"
            
            //
            "MB1_LQ,rate_MB1_LQ [kHz],"
            
            "isolatedMB1_LQ,rate_isolatedMB1_LQ [kHz],"
            "isolatedMB1_LQ_withHOTP_SOI,rate_isolatedMB1_LQ_withHOTP_SOI [kHz],"
            
            "unisolatedMB1_LQ,rate_unisolatedMB1_LQ [kHz],"
            "unisolatedMB1_LQ_withHOTP_SOI,rate_unisolatedMB1_LQ_withHOTP_SOI [kHz],"
            
            //
            "MB1_HQ,rate_MB1_HQ [kHz],"
            
            "isolatedMB1_HQ,rate_isolatedMB1_HQ [kHz],"
            "isolatedMB1_HQ_withHOTP_SOI,rate_isolatedMB1_HQ_withHOTP_SOI [kHz],"
            
            "unisolatedMB1_HQ,rate_unisolatedMB1_HQ [kHz],"
            "unisolatedMB1_HQ_withHOTP_SOI,rate_unisolatedMB1_HQ_withHOTP_SOI [kHz]"
        );
        
        fprintf(textFile, "\n");
        
        for(;iEle_LQ != m_MB1_LQ.end(); iEle_LQ++, iEle_HQ++)
        {
            fprintf(textFile, \
                "%d,%f,"
                "%d,"
                
                "%d,%d,%f,"
                
                //
                "%d,%f,"
                
                "%d,%f,"
                "%d,%f,"
                
                "%d,%f,"
                "%d,%f,"
                
                //
                "%d,%f,"
                
                "%d,%f,"
                "%d,%f,"
                
                "%d,%f,"
                "%d,%f", \
                
                iEle_LQ->first, getLumi(iEle_LQ->first), \
                iEle_LQ->second[pTcut].at(0), \
                
                iEle_LQ->second[pTcut].at(4), iEle_LQ->second[pTcut].at(5), (double) iEle_LQ->second[pTcut].at(5) / iEle_LQ->second[pTcut].at(0) * 40.0*1000.0, \
                
                //
                iEle_LQ->second[pTcut].at(1), (double) iEle_LQ->second[pTcut].at(1) / iEle_LQ->second[pTcut].at(0) / 3.0 * 40.0*1000.0, \
                
                iEle_LQ->second[pTcut].at(2), (double) iEle_LQ->second[pTcut].at(2) / iEle_LQ->second[pTcut].at(0) / 3.0 * 40.0*1000.0, \
                iEle_LQ->second[pTcut].at(6), (double) iEle_LQ->second[pTcut].at(6) / iEle_LQ->second[pTcut].at(0) / 3.0 * 40.0*1000.0, \
                
                iEle_LQ->second[pTcut].at(3), (double) iEle_LQ->second[pTcut].at(3) / iEle_LQ->second[pTcut].at(0) / 3.0 * 40.0*1000.0, \
                iEle_LQ->second[pTcut].at(7), (double) iEle_LQ->second[pTcut].at(7) / iEle_LQ->second[pTcut].at(0) / 3.0 * 40.0*1000.0, \
                
                //
                iEle_HQ->second[pTcut].at(1), (double) iEle_HQ->second[pTcut].at(1) / iEle_HQ->second[pTcut].at(0) / 3.0 * 40.0*1000.0, \
                
                iEle_HQ->second[pTcut].at(2), (double) iEle_HQ->second[pTcut].at(2) / iEle_HQ->second[pTcut].at(0) / 3.0 * 40.0*1000.0, \
                iEle_HQ->second[pTcut].at(6), (double) iEle_HQ->second[pTcut].at(6) / iEle_HQ->second[pTcut].at(0) / 3.0 * 40.0*1000.0, \
                
                iEle_HQ->second[pTcut].at(3), (double) iEle_HQ->second[pTcut].at(3) / iEle_HQ->second[pTcut].at(0) / 3.0 * 40.0*1000.0, \
                iEle_HQ->second[pTcut].at(7), (double) iEle_HQ->second[pTcut].at(7) / iEle_HQ->second[pTcut].at(0) / 3.0 * 40.0*1000.0
            );
            
            fprintf(textFile, "\n");
        }
        
        fclose(textFile);
    }
    
    printf("\n\nDT_phi_min %d, DT_phi_max %d\n", DT_phi_min, DT_phi_max);
    
    return 0;
}


void analyze(InputData *input, OutputData *output, OutputData *output_LQ, OutputData *output_HQ)
{
    int nEvent = input->tree->GetEntries();
    
    //int nEvent_max = 2*pow(10, 6);
    //nEvent = (nEvent > nEvent_max)? nEvent_max: nEvent;
    
    for(int iEvent = 0; iEvent < nEvent; iEvent++)
    {
        if((iEvent+1) % 1000 == 0)
        {
            printf("********** Event %d / %d ********** \n", iEvent+1, nEvent);
            
            if(nEvent_global_max > 0)
            {
                printf("********** Total event %d/%d ********** \n", nEvent_global, nEvent_global_max);
            }
            
            fflush(stdout);
        }
        
        int entryStatus = input->tree->GetEntry(iEvent);
        
        // Check for corrupt entry
        if(entryStatus == -1)
        {
            printf("Corrupt entry.");
            
            continue;
        }
        
        // Skip runs with bad/zero lumi, or not appearing in runInfo
        if(getLumi(input->runNumber) <= 0)
        {
            //printf("%ld %f \n", (long) input->runNumber, getLumi(input->runNumber));
            continue;
        }
        
        if(m_MB1_LQ.find(input->runNumber) == m_MB1_LQ.end())
        {
            for(int iPtCut = 0; iPtCut < v_pTcut.size(); iPtCut++)
            {
                m_MB1_LQ[input->runNumber][v_pTcut.at(iPtCut)] = std::vector <int>(8, 0);
                m_MB1_HQ[input->runNumber][v_pTcut.at(iPtCut)] = std::vector <int>(8, 0);
            }
        }
        
        nEvent_global++;
        //m_MB1_LQ[input->runNumber].at(0)++;
        //m_MB1_HQ[input->runNumber].at(0)++;
        updateCounterMap(&m_MB1_LQ, input->runNumber, 0);
        updateCounterMap(&m_MB1_HQ, input->runNumber, 0);
        
        
        //printf("runNumber %ld, lumiBlock %ld, eventNumber %ld, iEvent %d \n", \
            input->runNumber, input->lumiBlock, input->eventNumber, iEvent);
        
        //fprintf(output->eventInfoFile, "%d,%d,%d,%d \n", \
            input->runNumber, input->lumiBlock, input->eventNumber, iEvent);
        
        // Fill number of HOTP at SOI
        int nHOTP = input->v_hoTPdigi_bits->size();
        
        for(int iHOTP = 0; iHOTP < nHOTP; iHOTP++)
        {
            //m_MB1_LQ[input->runNumber].at(3)++;
            //m_MB1_HQ[input->runNumber].at(3)++;
            updateCounterMap(&m_MB1_LQ, input->runNumber, 4);
            updateCounterMap(&m_MB1_HQ, input->runNumber, 4);
            
            if(input->v_hoTPdigi_bits->at(iHOTP) != HOTP_bits_SOI)
            {
                continue;
            }
            
            //m_MB1_LQ[input->runNumber].at(4)++;
            //m_MB1_HQ[input->runNumber].at(4)++;
            updateCounterMap(&m_MB1_LQ, input->runNumber, 5);
            updateCounterMap(&m_MB1_HQ, input->runNumber, 5);
            
            output->h2_HOTP_iPhi_vs_wheel->Fill(getWheelFromIeta(input->v_hoTPdigi_iEta->at(iHOTP)), input->v_hoTPdigi_iPhi->at(iHOTP));
        }
        
        // Store best DT reco segment in each wh/st/sc
        int a_bestDTsegment_index[nWheel][nStation][nSector];
        int a_bestDTsegment_nHit_phiLocal[nWheel][nStation][nSector];
        
        for(int iWheel = 0; iWheel < nWheel; iWheel++)
        {
            for(int iStation = 0; iStation < nStation; iStation++)
            {
                for(int iSector = 0; iSector < nSector; iSector++)
                {
                    a_bestDTsegment_index[iWheel][iStation][iSector] = -1;
                    a_bestDTsegment_nHit_phiLocal[iWheel][iStation][iSector] = 0;
                }
            }
        }
        
        OutputData *currentOutput = 0;
        
        int nDTsegment = input->v_dtsegm4D_wheel->size();
        
        for(int iDTsegment = 0; iDTsegment < nDTsegment; iDTsegment++)
        {
            int wheelNumber = (int) input->v_dtsegm4D_wheel->at(iDTsegment);
            int stationNumber = (int) input->v_dtsegm4D_station->at(iDTsegment);
            int sectorNumber = (int) input->v_dtsegm4D_sector->at(iDTsegment);
            
            
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
                    if(nHit_phiLocal > a_bestDTsegment_nHit_phiLocal[wheelNumber][stationNumber][sectorNumber])
                    {
                        a_bestDTsegment_index[wheelNumber][stationNumber][sectorNumber] = iDTsegment;
                        a_bestDTsegment_nHit_phiLocal[wheelNumber][stationNumber][sectorNumber] = nHit_phiLocal;
                    }
                }
            }
        }
        
        
        // Loop over stations
        /*for(int iStation = 0; iStation < nStation; iStation++)
        {
            // Loop over the best DT-segments in a station
            for(int iWheel = 0; iWheel < nWheel; iWheel++)
            {
                for(int iSector = 0; iSector < nSector; iSector++)
                {
                    int bestDTsegment_index = a_bestDTsegment_index[iWheel][iStation][iSector];
                    
                    if(bestDTsegment_index == -1)
                    {
                        continue;
                    }
                    
                    // Search for the muon which is closest to the DT-segment
                    bool isMuMatched = false;
                    int matchedMuon_index = -1;
                    double matchedMuon_pT = 0;
                    double matchedMuon_eta = 0;
                    double matchedMuon_phi = 0;
                    
                    double deltaPhi_min = 999;
                    double deltaR_min = 999;
                    
                    int nMuon = input->v_Mu_eta->size();
                    
                    for(int iMuon = 0; iMuon < nMuon; iMuon++)
                    {
                        // Muon must be Global and Tracker
                        if(!input->v_Mu_isMuGlobal->at(iMuon) || !input->v_Mu_isMuTracker->at(iMuon))
                        {
                            continue;
                        }
                        
                        if(!input->v_Mu_isMuTight->at(iMuon))
                        {
                            continue;
                        }
                        
                        double mu_pT = sqrt(pow(input->v_Mu_px->at(iMuon), 2) + pow(input->v_Mu_py->at(iMuon), 2));
                        double mu_eta = input->v_Mu_eta->at(iMuon);
                        double mu_phi = input->v_Mu_phi->at(iMuon);
                        
                        // Muon pT, eta cut
                        if(mu_pT < mu_pTcut || fabs(mu_eta) > mu_etaCut)
                        {
                            continue;
                        }
                        
                        double deltaEta = fabs(mu_eta - input->v_dtsegm4D_eta->at(bestDTsegment_index));
                        double deltaPhi = fabs(mu_phi - input->v_dtsegm4D_phi->at(bestDTsegment_index));
                        double deltaR = sqrt(pow(deltaEta, 2) + pow(deltaPhi, 2));
                        
                        // Check only deltaPhi for MB4
                        if(iStation+1 == 4)
                        {
                            if(deltaPhi < deltaPhiCut && deltaPhi < deltaPhi_min)
                            {
                                deltaPhi_min = deltaPhi;
                                
                                isMuMatched = true;
                                matchedMuon_index = iMuon;
                                matchedMuon_pT = mu_pT;
                                matchedMuon_eta = mu_eta;
                                matchedMuon_phi = mu_phi;
                            }
                        }
                        
                        // Check deltaR for other stations
                        else
                        {
                            deltaR = sqrt(pow(deltaEta, 2) + pow(deltaPhi, 2));
                            
                            if(deltaR < deltaRcut && deltaR < deltaR_min)
                            {
                                deltaR_min = deltaR;
                                
                                isMuMatched = true;
                                matchedMuon_index = iMuon;
                                matchedMuon_pT = mu_pT;
                                matchedMuon_eta = mu_eta;
                                matchedMuon_phi = mu_phi;
                            }
                        }
                    }
                    
                    if(!isMuMatched)
                    {
                        continue;
                    }
                    
                    
                    output->v_h1_dtdegm4D_mu_pT[iStation]->Fill(matchedMuon_pT);
                    output->v_h1_dtdegm4D_mu_eta[iStation]->Fill(matchedMuon_eta);
                    
                    printf("Matching muon found: index %d, st %d, wh %d, sc %d, " \
                        "pT %f, eta %f, phi %f \n", \
                        bestDTsegment_index, iStation+1, iWheel-2, iSector+1, \
                        matchedMuon_pT, matchedMuon_eta, matchedMuon_phi);
                    
                    
                    // Search for matching DTTP (at BX = 0) in the same wheel, station, and sector
                    bool foundDTTP = false;
                    
                    std::vector <int> v_matchedDTTP_index;
                    
                    int nDTTP = input->v_ltTwinMuxIn_wheel->size();
                    
                    for(int iDTTP = 0; iDTTP < nDTTP; iDTTP++)
                    {
                        //printf("    DTTP: index %d, bx %d, " \
                            "st %d, wh %d, sc %d \n", \
                            iDTTP, \
                            input->v_ltTwinMuxIn_bx->at(iDTTP), \
                            input->v_ltTwinMuxIn_station->at(iDTTP), \
                            input->v_ltTwinMuxIn_wheel->at(iDTTP), \
                            input->v_ltTwinMuxIn_sector->at(iDTTP));
                        
                        
                        if(input->v_ltTwinMuxIn_bx->at(iDTTP) == 0 && \
                            iWheel-2 == input->v_ltTwinMuxIn_wheel->at(iDTTP) && \
                            iStation+1 == input->v_ltTwinMuxIn_station->at(iDTTP) && \
                            iSector+1 == input->v_ltTwinMuxIn_sector->at(iDTTP))
                        {
                            foundDTTP = true;
                            
                            v_matchedDTTP_index.push_back(iDTTP);
                            
                            //break;
                        }
                    }
                    
                    //Check if a matching BMTF track is present
                    bool foundBMTF = false;
                    
                    int nBMTF = input->v_gmt_pT->size();
                    
                    for(int iBMTF = 0; iBMTF < nBMTF; iBMTF++)
                    {
                        int bx_BMTF = input->v_gmt_bx->at(iBMTF);
                        
                        if(bx_BMTF != 0)
                        {
                            continue;
                        }
                        
                        double pT_BMTF = input->v_gmt_pT->at(iBMTF);
                        double eta_BMTF = input->v_gmt_eta->at(iBMTF);
                        double phi_BMTF = input->v_gmt_phi->at(iBMTF);
                        
                        double eta_dtsegm4D = input->v_dtsegm4D_eta->at(bestDTsegment_index);
                        double phi_dtsegm4D = input->v_dtsegm4D_phi->at(bestDTsegment_index);
                        
                        //double deltaEta = fabs(eta_BMTF - eta_dtsegm4D);
                        //double deltaPhi = fabs(phi_BMTF - phi_DTTP);
                        //double deltaPhi = fabs(phi_BMTF - phi_dtsegm4D);
                        double deltaEta = fabs(eta_BMTF - matchedMuon_eta);
                        double deltaPhi = fabs(phi_BMTF - matchedMuon_phi);
                        
                        double deltaR = sqrt(pow(deltaEta, 2) + pow(deltaPhi, 2));
                        
                        //if(pT_BMTF > mu_pTcut && eta_BMTF < mu_etaCut && deltaPhi < 0.1 && isInSameWheel(eta_BMTF, iWheel-2))
                        if(pT_BMTF > mu_pTcut && eta_BMTF < mu_etaCut && deltaR < 0.15)
                        {
                            printf("Matching BMTF found: index %d, pT %f, eta %f, phi %f \n", \
                                iBMTF, pT_BMTF, eta_BMTF, phi_BMTF);
                            
                            foundBMTF = true;
                            break;
                        }
                    }
                    
                    if(foundDTTP)
                    {
                        printf("Matching MB%d DTTP found. \n", iStation+1);
                        
                        output->v_h1_dtdegm4D_withDTTP_mu_pT[iStation]->Fill(matchedMuon_pT);
                        output->v_h1_dtdegm4D_withDTTP_mu_eta[iStation]->Fill(matchedMuon_eta);
                        
                        if(foundBMTF)
                        {
                            printf("Matching DTTP and BMTF found. \n");
                            
                            output->v_h1_dtdegm4D_withDTTP_withBMTF_mu_pT[iStation]->Fill(matchedMuon_pT);
                            output->v_h1_dtdegm4D_withDTTP_withBMTF_mu_eta[iStation]->Fill(matchedMuon_eta);
                        }
                        
                        continue;
                    }
                    
                    
                    // If matching DTTP is not found, search for HOTP support
                    printf("Matching DTTP NOT found. \n");
                    
                    output->v_h1_dtdegm4D_noDTTP_mu_pT[iStation]->Fill(matchedMuon_pT);
                    output->v_h1_dtdegm4D_noDTTP_mu_eta[iStation]->Fill(matchedMuon_eta);
                    
                    if(foundBMTF)
                    {
                        output->v_h1_dtdegm4D_noDTTP_withBMTF_mu_pT[iStation]->Fill(matchedMuon_pT);
                        output->v_h1_dtdegm4D_noDTTP_withBMTF_mu_eta[iStation]->Fill(matchedMuon_eta);
                    }
                    
                    else
                    {
                        printf("Matching BMTF NOT found. \n");
                        
                        output->v_h1_dtdegm4D_noDTTP_noBMTF_mu_pT[iStation]->Fill(matchedMuon_pT);
                        output->v_h1_dtdegm4D_noDTTP_noBMTF_mu_eta[iStation]->Fill(matchedMuon_eta);
                    }
                    
                    // For now, provide support MB2 only
                    //if(iStation+1 != 2)
                    //{
                    //    continue;
                    //}
                    
                    printf("Searching for MB1 DTTP and HOTP. \n");
                    
                    // Search for matching DTTP in MB1
                    bool foundMB1DTTP = false;
                    bool foundHOTP = false;
                    bool foundMipHOTP = false;
                    
                    int matchedHOTP_index = -1;
                    
                    
                    for(int iDTTP = 0; iDTTP < nDTTP; iDTTP++)
                    {
                        // DTTP in MB1 at BX = 0
                        if(input->v_ltTwinMuxIn_bx->at(iDTTP) != 0 || \
                            input->v_ltTwinMuxIn_station->at(iDTTP) != 1)
                        {
                            continue;
                        }
                        
                        // Get the best DT-segment in the same wheel and sector of the MB1 DTTP
                        int bestDTsegment_index_MB1 = \
                            a_bestDTsegment_index[input->v_ltTwinMuxIn_wheel->at(iDTTP)+2][0][input->v_ltTwinMuxIn_sector->at(iDTTP)-1];
                        
                        if(bestDTsegment_index_MB1 == -1)
                        {
                            continue;
                        }
                        
                        double globalPhi = input->v_ltTwinMuxIn_phi->at(iDTTP) / 4096.0;
                        globalPhi += M_PI / 6 * (input->v_ltTwinMuxIn_sector->at(iDTTP) - 1);
                        
                        if(globalPhi > M_PI)
                        {
                            globalPhi -= M_PI * 2;
                        }
                        double dPhi = 2.0*M_PI / 72.0;
                        
                        if(globalPhi < 0)
                        {
                            globalPhi += 2*M_PI;
                        }
                        
                        int iPhi = (int) (globalPhi/dPhi + 1);
                        
                        
                        //double deltaEta = fabs(input->v_dtsegm4D_eta->at(bestDTsegment_index) - input->v_dtsegm4D_eta->at(bestDTsegment_index_MB1));
                        //double deltaPhi = fabs(input->v_dtsegm4D_phi->at(bestDTsegment_index) - input->v_dtsegm4D_phi->at(bestDTsegment_index_MB1));
                        
                        //double deltaEta = fabs(matchedMuon_eta - input->v_dtsegm4D_eta->at(bestDTsegment_index_MB1));
                        //double deltaPhi = fabs(matchedMuon_phi - input->v_dtsegm4D_phi->at(bestDTsegment_index_MB1));
                        
                        double deltaEta = fabs(matchedMuon_eta - input->v_dtsegm4D_eta->at(bestDTsegment_index_MB1));
                        double deltaPhi = fabs(matchedMuon_phi - globalPhi);
                        
                        double deltaR = sqrt(pow(deltaEta, 2) + pow(deltaPhi, 2));
                        
                        // Match the MB1 DTTP (using its best DT-segment) to the MB2 DT-segment
                        //if(deltaR > deltaRcut)
                        if(deltaPhi > 0.2 || deltaEta > 0.5)
                        {
                            continue;
                        }
                        
                        int quality = input->v_ltTwinMuxIn_quality->at(iDTTP);
                        
                        bool is_LQ = quality > 0 && quality < 4;
                        bool is_HQ = quality > 3 && quality < 7;
                        
                        // Check DTTP quality
                        if(!is_LQ && !is_HQ)
                        {
                            continue;
                        }
                        
                        // Select the histograms to write to (LQ or HQ)
                        if(is_LQ)
                        {
                            printf("Matching MB1 DTTP (LQ) found. \n");
                            currentOutput = output_LQ;
                        }
                        
                        else if(is_HQ)
                        {
                            printf("Matching MB1 DTTP (HQ) found. \n");
                            currentOutput = output_HQ;
                        }
                        
                        foundMB1DTTP = true;
                        
                        // Search for an HOTP matching the MB1 DTTP
                        int nHOTP = input->v_hoTPdigi_bits->size();
                        
                        for(int iHOTP = 0; iHOTP < nHOTP; iHOTP++)
                        {
                            int deltaIeta = (int) fabs(input->v_hoTPdigi_iEta->at(iHOTP) - getIetaFromEta(input->v_dtsegm4D_eta->at(bestDTsegment_index_MB1)));
                            int deltaIphi = (int) fabs(input->v_hoTPdigi_iPhi->at(iHOTP) - input->v_ltTwinMuxIn_iPhi->at(iDTTP));
                            
                            //deltaEta = fabs(HOiEtaToEta(input->v_hoTPdigi_iEta->at(iHOTP)) - input->v_dtsegm4D_eta->at(bestDTsegment_index_MB1));
                            //deltaPhi = fabs(HOiPhiToPhi(input->v_hoTPdigi_iPhi->at(iHOTP)) - input->v_dtsegm4D_phi->at(bestDTsegment_index_MB1));
                            
                            deltaEta = fabs(HOiEtaToEta(input->v_hoTPdigi_iEta->at(iHOTP)) - matchedMuon_eta);
                            deltaPhi = fabs(HOiPhiToPhi(input->v_hoTPdigi_iPhi->at(iHOTP)) - matchedMuon_phi);
                            
                            deltaR = sqrt(pow(deltaEta, 2) + pow(deltaPhi, 2));
                            
                            //if(foundMB1DTTP && !foundBMTF && deltaIeta < 2)
                            //{
                            //    printf("DTTP-HOTP %d \n", input->v_hoTPdigi_iEta->at(iHOTP));
                            //    printf("DTTP-HOTP %d \n", getIetaFromEta(input->v_dtsegm4D_eta->at(bestDTsegment_index_MB1)));
                            //    printf("DTTP-HOTP %d %d \n", input->v_hoTPdigi_iPhi->at(iHOTP), iPhi);
                            //    printf("DTTP-HOTP %d \n", input->v_ltTwinMuxIn_iPhi->at(iDTTP));
                            //    printf("DTTP-HOTP: dIeta %d, dIphi %d \n", \
                            //        deltaIeta, \
                            //        deltaIphi);
                            //}
                            
                            // Match the HO-TP to the muon that was matched to the MB2 DT-segment
                            //if(deltaEta < 0.087 && deltaPhi < 0.087)
                            if(deltaR < 0.2)
                            //if(deltaIeta < 2 && deltaIphi < 2)
                            {
                                foundHOTP = true;
                                
                                int bits = input->v_hoTPdigi_bits->at(iHOTP);
                                int whichSample = input->v_hoTPdigi_whichSampleTriggered->at(iHOTP);
                                
                                matchedHOTP_index = iHOTP;
                                
                                // Check mip bit
                                int isMip = (bits>>whichSample)&0x1;
                                
                                if(isMip)
                                {
                                    foundMipHOTP = true;
                                }
                                
                                break;
                            }
                        }
                        
                        if(foundHOTP)
                        {
                            break;
                        }
                    }
                    
                    if(foundMB1DTTP)
                    {
                        currentOutput->v_h1_dtdegm4D_noDTTP_withMB1DTTP_mu_pT[iStation]->Fill(matchedMuon_pT);
                        currentOutput->v_h1_dtdegm4D_noDTTP_withMB1DTTP_mu_eta[iStation]->Fill(matchedMuon_eta);
                        
                        if(!foundBMTF)
                        {
                            currentOutput->v_h1_dtdegm4D_noDTTP_noBMTF_withMB1DTTP_mu_pT[iStation]->Fill(matchedMuon_pT);
                            currentOutput->v_h1_dtdegm4D_noDTTP_noBMTF_withMB1DTTP_mu_eta[iStation]->Fill(matchedMuon_eta);
                        }
                    }
                    
                    if(!foundHOTP)
                    {
                        printf("Matching HOTP NOT found. \n");
                        
                        continue;
                    }
                    
                    printf("Matching HOTP found: index %d, eta %f, phi %f \n", \
                        HOiPhiToPhi(input->v_hoTPdigi_iPhi->at(matchedHOTP_index)), HOiPhiToPhi(input->v_hoTPdigi_iPhi->at(matchedHOTP_index)));
                    
                    currentOutput->v_h1_dtdegm4D_noDTTP_withMB1DTTP_withHOTP_mu_pT[iStation]->Fill(matchedMuon_pT);
                    currentOutput->v_h1_dtdegm4D_noDTTP_withMB1DTTP_withHOTP_mu_eta[iStation]->Fill(matchedMuon_eta);
                    
                    if(!foundBMTF)
                    {
                        printf("Matching HOTP found, BMTF not found. \n");
                        currentOutput->v_h1_dtdegm4D_noDTTP_noBMTF_withMB1DTTP_withHOTP_mu_pT[iStation]->Fill(matchedMuon_pT);
                        currentOutput->v_h1_dtdegm4D_noDTTP_noBMTF_withMB1DTTP_withHOTP_mu_eta[iStation]->Fill(matchedMuon_eta);
                    }
                    
                    if(foundMipHOTP)
                    {
                        printf("Matching mip-HOTP found. \n");
                        
                        currentOutput->v_h1_dtdegm4D_noDTTP_withMB1DTTP_withMipHOTP_mu_pT[iStation]->Fill(matchedMuon_pT);
                        currentOutput->v_h1_dtdegm4D_noDTTP_withMB1DTTP_withMipHOTP_mu_eta[iStation]->Fill(matchedMuon_eta);
                    }
                }
            }
        }*/
        
        
        // Loop over reco muons
        /*int nMuon = input->v_Mu_eta->size();
        std::vector <bool> v_Mu_matchedDTTP(nMuon, false);
        
        for(int iMuon = 0; iMuon < nMuon; iMuon++)
        {
            // Muon must be Global and Tracker
            if(!input->v_Mu_isMuGlobal->at(iMuon) || !input->v_Mu_isMuTracker->at(iMuon))
            {
                continue;
            }
            
            if(!input->v_Mu_isMuTight->at(iMuon))
            {
                continue;
            }
            
            double mu_pT = sqrt(pow(input->v_Mu_px->at(iMuon), 2) + pow(input->v_Mu_py->at(iMuon), 2));
            double mu_eta = input->v_Mu_eta->at(iMuon);
            double mu_phi = input->v_Mu_phi->at(iMuon);
            
            // Muon pT, eta cut
            if(mu_pT < mu_pTcut || fabs(mu_eta) > mu_etaCut)
            {
                continue;
            }
            
            // Search for 2 matching DTTPS in dfferent stations
            bool foundDTTP = false;
            bool foundMB1DTTP = false;
            
            int nDTTP = input->v_ltTwinMuxIn_bx->size();
            int nMatchedDTTP = 0;
            int matchedMB1DTTP_index = -1;
            
            for(int iDTTP = 0; iDTTP < nDTTP; iDTTP++)
            {
                int bestDTsegment_index = \
                    a_bestDTsegment_index[input->v_ltTwinMuxIn_wheel->at(iDTTP)+2][input->v_ltTwinMuxIn_station->at(iDTTP)-1][input->v_ltTwinMuxIn_sector->at(iDTTP)-1];
                
                if(bestDTsegment_index == -1)
                {
                    continue;
                }
                
                // DTTP must be at BX = 0
                if(input->v_ltTwinMuxIn_bx->at(iDTTP) != 0)
                {
                    continue;
                }
                
                int quality = input->v_ltTwinMuxIn_quality->at(iDTTP);
                
                bool is_LQ = quality > 0 && quality < 4;
                bool is_HQ = quality > 3 && quality < 7;
                
                // Check DTTP quality
                if(!is_LQ && !is_HQ)
                {
                    continue;
                }
                
                // Select the histograms to write to (LQ or HQ)
                if(is_LQ)
                {
                    //printf("Matching MB1 DTTP (LQ) found. \n");
                    currentOutput = output_LQ;
                }
                
                else if(is_HQ)
                {
                    //printf("Matching MB1 DTTP (HQ) found. \n");
                    currentOutput = output_HQ;
                }
                
                
                double globalPhi = input->v_ltTwinMuxIn_phi->at(iDTTP) / 4096.0;
                globalPhi += M_PI / 6 * (input->v_ltTwinMuxIn_sector->at(iDTTP) - 1);
                
                if(globalPhi > M_PI)
                {
                    globalPhi -= M_PI * 2;
                }
                
                double corrPhi = globalPhi - 2.0*input->v_ltTwinMuxIn_phiB->at(iDTTP)/512.0;
                printf("globalPhi %f, corrPhi %f, diff %f \n", globalPhi, corrPhi, globalPhi-corrPhi);
                double dPhi = 2.0*M_PI / 72.0;
                
                if(globalPhi < 0)
                {
                    globalPhi += 2*M_PI;
                }
                
                int iPhi = (int) (globalPhi/dPhi + 1);
                
                double deltaEta = fabs(mu_eta - input->v_dtsegm4D_eta->at(bestDTsegment_index));
                double deltaPhi = fabs(mu_phi - globalPhi);
                //double deltaPhi = fabs(mu_phi - corrPhi);
                
                //double deltaEta = fabs(mu_eta - input->v_dtsegm4D_eta->at(bestDTsegment_index));
                //double deltaPhi = fabs(mu_phi - input->v_dtsegm4D_phi->at(bestDTsegment_index));
                
                double deltaR = sqrt(pow(deltaEta, 2) + pow(deltaPhi, 2));
                
                int matchedDTTP_station = -1;
                
                // Check deltaR for MB1/2/3 and deltaPhi for MB4
                //if((input->v_ltTwinMuxIn_station->at(iDTTP) <= 3 && deltaR < deltaRcut) \
                    || (input->v_ltTwinMuxIn_station->at(iDTTP) == 4 && deltaPhi < deltaPhiCut))
                if(deltaPhi > 0.2 || deltaEta > 0.5)
                {
                    if(input->v_ltTwinMuxIn_station->at(iDTTP) == 1)
                    {
                        foundMB1DTTP = true;
                        matchedMB1DTTP_index = iDTTP;
                    }
                    
                    if(nMatchedDTTP == 0)
                    {
                        nMatchedDTTP++;
                        
                        matchedDTTP_station = input->v_ltTwinMuxIn_station->at(iDTTP);
                    }
                    
                    else if(nMatchedDTTP == 1 && matchedDTTP_station != input->v_ltTwinMuxIn_station->at(iDTTP))
                    {
                        nMatchedDTTP++;
                        
                        //break;
                    }
                }
            }
            
            if(nMatchedDTTP == 2)
            {
                foundDTTP = true;
                
                v_Mu_matchedDTTP.at(iMuon) = true;
            }
            
            
            // Search for a matching BMTF track
            bool foundBMTF = false;
            
            int nBMTF = input->v_gmt_pT->size();
            
            double pT_matchedBMTF = 0;
            double eta_matchedBMTF = 0;
            double phi_matchedBMTF = 0;
            double deltaR_min = 9999;
            
            for(int iBMTF = 0; iBMTF < nBMTF; iBMTF++)
            {
                int bx_BMTF = input->v_gmt_bx->at(iBMTF);
                
                if(bx_BMTF != 0)
                {
                    continue;
                }
                
                double pT_BMTF = input->v_gmt_pT->at(iBMTF);
                double eta_BMTF = input->v_gmt_eta->at(iBMTF);
                double phi_BMTF = input->v_gmt_phi->at(iBMTF);
                
                if(pT_BMTF < mu_pTcut || eta_BMTF > mu_etaCut)
                {
                    continue;
                }
                
                double deltaEta = fabs(eta_BMTF - mu_eta);
                double deltaPhi = fabs(phi_BMTF - mu_phi);
                double deltaR = sqrt(pow(deltaEta, 2) + pow(deltaPhi, 2));
                
                if(deltaR < 0.15)
                {
                    foundBMTF = true;
                    
                    //break;
                    
                    if(deltaR < deltaR_min)
                    {
                        deltaR_min = deltaR;
                        
                        pT_matchedBMTF = pT_BMTF;
                        eta_matchedBMTF = eta_BMTF;
                        phi_matchedBMTF = phi_BMTF;
                    }
                }
            }
            
            
            if(foundDTTP)
            {
                printf("Muon with 2 matching DTTPs found. \n");
                
                output->h1_muon_withDTTP_mu_pT->Fill(mu_pT);
                output->h1_muon_withDTTP_mu_eta->Fill(mu_eta);
                
                if(foundBMTF)
                {
                    printf("Muon with 2 matching DTTPs and a BMTF track found. \n");
                    
                    output->h1_muon_withDTTP_withBMTF_mu_pT->Fill(mu_pT);
                    output->h1_muon_withDTTP_withBMTF_mu_eta->Fill(mu_eta);
                    
                    //output->h1_muon_withDTTP_withBMTF_mu_pT->Fill(pT_matchedBMTF);
                    //output->h1_muon_withDTTP_withBMTF_mu_eta->Fill(eta_matchedBMTF);
                }
            }
            
            
            // If a matching BMTF track is not found, but an MB1 DTTP is found, search for a matching HOTP
            if(foundBMTF || !foundMB1DTTP)// || nMatchedDTTP != 1)
            {
                continue;
            }
            
            bool foundHOTP = false;
            
            int nHOTP = input->v_hoTPdigi_bits->size();
            
            for(int iHOTP = 0; iHOTP < nHOTP; iHOTP++)
            {
                int bestDTsegment_index = \
                    a_bestDTsegment_index[input->v_ltTwinMuxIn_wheel->at(matchedMB1DTTP_index)+2] \
                        [input->v_ltTwinMuxIn_station->at(matchedMB1DTTP_index)-1] \
                        [input->v_ltTwinMuxIn_sector->at(matchedMB1DTTP_index)-1];
                
                int deltaIeta = (int) fabs(input->v_hoTPdigi_iEta->at(iHOTP) - getIetaFromEta(input->v_dtsegm4D_eta->at(bestDTsegment_index)));
                int deltaIphi = (int) fabs(input->v_hoTPdigi_iPhi->at(iHOTP) - input->v_ltTwinMuxIn_iPhi->at(matchedMB1DTTP_index));
                
                double deltaEta = fabs(HOiEtaToEta(input->v_hoTPdigi_iEta->at(iHOTP)) - mu_eta);
                double deltaPhi = fabs(HOiPhiToPhi(input->v_hoTPdigi_iPhi->at(iHOTP)) - mu_phi);
                
                double deltaR = sqrt(pow(deltaEta, 2) + pow(deltaPhi, 2));
                
                //if(deltaR < 0.2)
                if(deltaIeta < 2 && deltaIphi < 2)
                {
                    foundHOTP = true;
                    
                    break;
                }
            }
            
            if(foundHOTP)
            {
                printf("Muon with no BMTF track, with MB1 DTTP and HOTP found. \n");
                
                currentOutput->h1_muon_noBMTF_withMB1DTTP_withHOTP_mu_pT->Fill(mu_pT);
                currentOutput->h1_muon_noBMTF_withMB1DTTP_withHOTP_mu_eta->Fill(mu_eta);
            }
        }*/
        
        
        // Loop over BMTF tracks
        /*int nBMTF = input->v_gmt_pT->size();
        
        for(int iBMTF = 0; iBMTF < nBMTF; iBMTF++)
        {
            int bx_BMTF = input->v_gmt_bx->at(iBMTF);
            
            if(bx_BMTF != 0)
            {
                continue;
            }
            
            double pT_BMTF = input->v_gmt_pT->at(iBMTF);
            double eta_BMTF = input->v_gmt_eta->at(iBMTF);
            double phi_BMTF = input->v_gmt_phi->at(iBMTF);
            
            if(pT_BMTF < mu_pTcut || eta_BMTF > mu_etaCut)
            {
                continue;
            }
            
            int nMuon = input->v_Mu_eta->size();
            
            for(int iMuon = 0; iMuon < nMuon; iMuon++)
            {
                // Muon must be Global and Tracker
                if(!input->v_Mu_isMuGlobal->at(iMuon) || !input->v_Mu_isMuTracker->at(iMuon))
                {
                    continue;
                }
                
                if(!input->v_Mu_isMuTight->at(iMuon) || !v_Mu_matchedDTTP.at(iMuon))
                {
                    continue;
                }
                
                double mu_pT = sqrt(pow(input->v_Mu_px->at(iMuon), 2) + pow(input->v_Mu_py->at(iMuon), 2));
                double mu_eta = input->v_Mu_eta->at(iMuon);
                double mu_phi = input->v_Mu_phi->at(iMuon);
                
                // Muon pT, eta cut
                if(mu_pT < mu_pTcut || fabs(mu_eta) > mu_etaCut)
                {
                    continue;
                }
            
                double deltaEta = fabs(eta_BMTF - mu_eta);
                double deltaPhi = fabs(phi_BMTF - mu_phi);
                double deltaR = sqrt(pow(deltaEta, 2) + pow(deltaPhi, 2));
                
                if(deltaR < 0.2)
                {
                    printf("Found BMTF with matching muon.");
                    
                    output->h1_BMTF_withMuon_withDTTP_pT->Fill(pT_BMTF);
                    output->h1_BMTF_withMuon_withDTTP_eta->Fill(eta_BMTF);
                    
                    break;
                }
            }
        }*/
        
        
        // loop over DTTPs
        /*int nDTTP = input->v_ltTwinMuxIn_bx->size();
        
        for(int iDTTP = 0; iDTTP < nDTTP; iDTTP++)
        {
            int stNum = input->v_ltTwinMuxIn_station->at(iDTTP)-1;
            int whNum = input->v_ltTwinMuxIn_wheel->at(iDTTP)+2;
            int scNum = input->v_ltTwinMuxIn_sector->at(iDTTP)-1;
            
            if(stNum == 3)
            {
                continue;
            }
            
            std::string quality_str = "";
            
            int quality = input->v_ltTwinMuxIn_quality->at(iDTTP);
            
            bool is_LQ = quality > 0 && quality < 4;
            bool is_HQ = quality > 3 && quality < 7;
            
            // Check DTTP quality
            if(!is_LQ && !is_HQ)
            {
                continue;
            }
            
            // Select the histograms to write to (LQ or HQ)
            if(is_LQ)
            {
                quality_str = "LQ";
                currentOutput = output_LQ;
            }
            
            else if(is_HQ)
            {
                quality_str = "HQ";
                currentOutput = output_HQ;
            }
            
            int bestDTsegment_index = \
                a_bestDTsegment_index[whNum][stNum][scNum];
            
            if(bestDTsegment_index == -1)
            {
                continue;
            }
            
            int dtSegment_iEta = getIetaFromEta(input->v_dtsegm4D_eta->at(bestDTsegment_index));
            int ltTwinMux_thIeta = -99;
            
            int nThDTTP = input->v_ltTwinMux_thBx->size();
            
            for(int iThDTTP = 0; iThDTTP < nThDTTP; iThDTTP++)
            {
                if(input->v_ltTwinMux_thWheel->at(iThDTTP)+2 == whNum && \
                    input->v_ltTwinMux_thStation->at(iThDTTP)-1 == stNum && \
                    input->v_ltTwinMux_thSector->at(iThDTTP)-1 == scNum)
                {
                    printf("xxx \n");
                    ltTwinMux_thIeta = input->v_ltTwinMux_thIeta->at(iThDTTP);
                }
                
                if(ltTwinMux_thIeta != -99)
                {
                    break;
                }
            }
            
            printf("%s st%d wh%d sc%d hasZed %d : ltTwinMux_thIeta %d, dtSegment_iEta %d, dtSegment_eta %f \n", \
                quality_str.c_str(), stNum+1, whNum-2, scNum+1, (int) input->v_dtsegm4D_hasZed->at(bestDTsegment_index), \
                ltTwinMux_thIeta, dtSegment_iEta, input->v_dtsegm4D_eta->at(bestDTsegment_index));
            
            currentOutput->v_h2_dtSegmentIeta_vs_thDigiIeta.at(stNum)->Fill(ltTwinMux_thIeta, dtSegment_iEta);
        }*/
        
        
        // get isolated MB1 DTTPs (MB1 DTTPs that are not matched to a DTTP from another station)
        int nDTTP = input->v_ltTwinMuxIn_bx->size();
        
        for(int iDTTP = 0; iDTTP < nDTTP; iDTTP++)
        {
            int stNum_iDTTP = input->v_ltTwinMuxIn_station->at(iDTTP)-1;
            int whNum_iDTTP = input->v_ltTwinMuxIn_wheel->at(iDTTP)+2;
            int scNum_iDTTP = input->v_ltTwinMuxIn_sector->at(iDTTP)-1;
            
            // MB1 only
            if(stNum_iDTTP != 0)
            {
                continue;
            }
            
            bool inAcceptance_iDTTP = true;
            
            // Exclude wheels +-2 of MB1
            // They are already supported by the CSC
            if(whNum_iDTTP == 0 || whNum_iDTTP == 4)
            {
                //inAcceptance_iDTTP = false;
                continue;
            }
            
            double pT_iDTTP = getPtFromPhiB((int) input->v_ltTwinMuxIn_phiB->at(iDTTP));
            
            if(whNum_iDTTP == 2)
            //if(whNum_iDTTP == 2 && scNum_iDTTP == 0)
            {
                if(input->v_ltTwinMuxIn_phi->at(iDTTP) > DT_phi_max)
                {
                    DT_phi_max = input->v_ltTwinMuxIn_phi->at(iDTTP);
                }
                
                else if(input->v_ltTwinMuxIn_phi->at(iDTTP) < DT_phi_min)
                {
                    DT_phi_min = input->v_ltTwinMuxIn_phi->at(iDTTP);
                }
                //printf("%d %d %d\n", DT_phi_min, input->v_ltTwinMuxIn_phi->at(iDTTP), DT_phi_max);
            }
            
            std::string quality_str = "";
            
            int quality = input->v_ltTwinMuxIn_quality->at(iDTTP);
            
            bool is_LQ = quality > 0 && quality < 4;
            bool is_HQ = quality > 3 && quality < 7;
            
            // Check DTTP quality
            if(!is_LQ && !is_HQ)
            {
                continue;
            }
            
            // Select the histograms to write to (LQ or HQ)
            if(is_LQ)
            {
                quality_str = "LQ";
                currentOutput = output_LQ;
                MB1_n_LQ++;
                
                //m_MB1_LQ[input->runNumber].at(1)++;
                updateCounterMap(&m_MB1_LQ, input->runNumber, 1, input->v_ltTwinMuxIn_phiB->at(iDTTP));
            }
            
            else if(is_HQ)
            {
                quality_str = "HQ";
                currentOutput = output_HQ;
                MB1_n_HQ++;
                
                //m_MB1_HQ[input->runNumber].at(1)++;
                updateCounterMap(&m_MB1_HQ, input->runNumber, 1);
            }
            
            currentOutput->h1_MB1DTTP_pT->Fill(pT_iDTTP);
            
            int bestDTsegment_index_iDTTP = \
                a_bestDTsegment_index[whNum_iDTTP][stNum_iDTTP][scNum_iDTTP];
            
            double globalPhi_iDTTP = globalPhiFromDTphi(input->v_ltTwinMuxIn_phi->at(iDTTP), input->v_ltTwinMuxIn_sector->at(iDTTP));
            
            bool isIsolated = true;
            bool isIsolated_inTimeMatching = true;
            bool isIsolated_deltaTimeMatching = true;
            
            bool isInTimeMatched = false;
            bool isDeltaTimeMatched = false;
            
            double deltaPhi_nearest = 100;
            double deltaPhiSign_nearest = 100;
            double deltaBX_nearest = 100;
            
            // Find matching DTTP from MB2/3/4
            for(int jDTTP = 0; jDTTP < nDTTP; jDTTP++)
            {
                if(jDTTP == iDTTP)
                {
                    continue;
                }
                
                int stNum_jDTTP = input->v_ltTwinMuxIn_station->at(jDTTP)-1;
                int whNum_jDTTP = input->v_ltTwinMuxIn_wheel->at(jDTTP)+2;
                int scNum_jDTTP = input->v_ltTwinMuxIn_sector->at(jDTTP)-1;
                
                // Skip MB1
                if(stNum_jDTTP == 0)
                {
                    continue;
                }
                
                int deltaBX = (int) fabs(input->v_ltTwinMuxIn_bx->at(iDTTP) - input->v_ltTwinMuxIn_bx->at(jDTTP));
                
                /*isIsolated = true;
                isIsolated_inTimeMatching = true;
                isIsolated_deltaTimeMatching = true;*/
                
                isInTimeMatched = false;
                isDeltaTimeMatched = false;
                
                // Check if the BX number is same
                if(deltaBX == 0)
                {
                    isInTimeMatched = true;
                }
                
                if(deltaBX <= 1)
                {
                    isDeltaTimeMatched = true;
                }
                
                /*if(deltaBX > 1)
                {
                    continue;
                }*/
                
                int bestDTsegment_index_jDTTP = \
                    a_bestDTsegment_index[whNum_jDTTP][stNum_jDTTP][scNum_jDTTP];
                
                double globalPhi_jDTTP = globalPhiFromDTphi(input->v_ltTwinMuxIn_phi->at(jDTTP), input->v_ltTwinMuxIn_sector->at(jDTTP));
                double deltaPhi = globalPhi_iDTTP - globalPhi_jDTTP;
                
                int deltaPhiSign = (deltaPhi < 0)? -1: 1;
                
                deltaPhi = fabs(deltaPhi);
                deltaPhi = (deltaPhi > M_PI)? (2*M_PI - deltaPhi): deltaPhi;
                
                
                //printf("deltaPhi %f \n", deltaPhi);
                
                // deltaPhi matching
                if(deltaPhi < 0.4)
                {
                    /*//printf("stNum_jDTTP %d \n", stNum_jDTTP);
                    
                    // Check deltaEta if jDTTP is not in MB4
                    if(stNum_jDTTP != 3)
                    {
                        // Check deltaEta if a DT segment exists in the same wh/st/sc
                        // Note: Zed projection of the DT segments has already been checked when filling a_bestDTsegment_index
                        if(bestDTsegment_index_iDTTP != -1 && bestDTsegment_index_jDTTP != -1)
                        {
                            double deltaEta = fabs(input->v_dtsegm4D_eta->at(bestDTsegment_index_iDTTP) - input->v_dtsegm4D_eta->at(bestDTsegment_index_jDTTP));
                            //printf("deltaEta %f \n", deltaEta);
                            
                            if(deltaEta < 0.4)
                            {
                                isIsolated = false;
                            }
                        }
                        
                        else
                        {
                            isIsolated = false;
                        }
                    }
                    
                    else
                    {
                        isIsolated = false;
                    }*/
                    
                    isIsolated = false;
                }
                
                if(deltaPhi < deltaPhi_nearest)
                {
                    deltaPhi_nearest = deltaPhi;
                    deltaPhiSign_nearest = deltaPhiSign;
                    deltaBX_nearest = deltaBX;
                }
                
                if(!isIsolated)
                {
                    if(isInTimeMatched)
                    {
                        isIsolated_inTimeMatching = false;
                    }
                    
                    if(isDeltaTimeMatched)
                    {
                        isIsolated_deltaTimeMatching = false;
                    }
                }
                
                // Break if match is found
                // Note: in-time matching is a subset of delta-time-matching
                //if(!isIsolated_deltaTimeMatching)
                //{
                //    break;
                //}
            }
            
            currentOutput->h1_MB1DTTP_deltaPhi->Fill(deltaPhi_nearest*deltaPhiSign_nearest);
            
            if(isIsolated_inTimeMatching)
            {
                if(is_LQ)
                {
                    isolatedMB1_n_LQ_inTimeMatching++;
                }
                
                else if(is_HQ)
                {
                    isolatedMB1_n_HQ_inTimeMatching++;
                }
            }
            
            if(isIsolated_deltaTimeMatching)
            {
                if(is_LQ)
                {
                    isolatedMB1_n_LQ_deltaTimeMatching++;
                }
                
                else if(is_HQ)
                {
                    isolatedMB1_n_HQ_deltaTimeMatching++;
                }
            }
            
            
            // Get list of th-DTTP in the same wh/st/sc as the current MB1TP
            std::vector <int> v_thDTTP_index = {};
            
            for(int iThDTTP = 0; iThDTTP < input->v_ltTwinMux_thBx->size(); iThDTTP++)
            {
                // Choose HQ th-DTTP
                if(!input->v_ltTwinMux_thQuality->at(iThDTTP))
                {
                    continue;
                }
                
                int iEta = input->v_ltTwinMux_thIeta->at(iThDTTP);
                
                // Reject junk
                if(abs(iEta) > 15)
                {
                    continue;
                }
                
                // Select from the same wh/st/sc
                if(input->v_ltTwinMux_thWheel->at(iThDTTP) == whNum_iDTTP-2 \
                    && input->v_ltTwinMux_thStation->at(iThDTTP) == stNum_iDTTP+1 \
                    && input->v_ltTwinMux_thSector->at(iThDTTP) == scNum_iDTTP+1)
                {
                    v_thDTTP_index.push_back(iThDTTP);
                }
            }
            
            
            int nHOTP = input->v_hoTPdigi_bits->size();
            bool isHOTPmatched = false;
            
            int deltaIphi_nearest = 100;
            int deltaIphiSign_nearest = 100;
            
            int deltaIeta_nearest = 100;
            int deltaIetaSign_nearest = 100;
            
            int deltaWheel_nearest = 100;
            int deltaWheelSign_nearest = 100;
            
            int deltaSector_nearest = 100;
            int deltaSectorSign_nearest = 100;
            
            int thDTTP_index_nearest = -1;
            int HOTP_index_nearest = -1;
            
            for(int iHOTP = 0; iHOTP < nHOTP; iHOTP++)
            {
                if(input->v_hoTPdigi_bits->at(iHOTP) != HOTP_bits_SOI)
                {
                    continue;
                }
                
                int deltaIphi =  input->v_ltTwinMuxIn_iPhi->at(iDTTP) - input->v_hoTPdigi_iPhi->at(iHOTP);
                int deltaIphiSign = (deltaIphi < 0)? -1: 1;
                deltaIphi = abs(deltaIphi);
                
                int deltaWheel = input->v_ltTwinMuxIn_wheel->at(iDTTP) - getWheelFromIeta(input->v_hoTPdigi_iEta->at(iHOTP));
                int deltaWheelSign = (deltaWheel < 0)? -1: 1;
                deltaWheel = abs(deltaWheel);
                
                int deltaSector = input->v_ltTwinMuxIn_sector->at(iDTTP) - getSectorFromIphi(input->v_hoTPdigi_iPhi->at(iHOTP));
                int deltaSectorSign = (deltaSector < 0)? -1: 1;
                deltaSector = abs(deltaSector);
                
                //if(deltaSector > 1)
                //{
                //    continue;
                //}
                
                // Get the min deltaIeta between the the current HOTP and the MB1TP
                int thDTTP_index_min = -1;
                int deltaIeta_min = 100;
                int deltaIetaSign_min = 100;
                int nThDTTP = v_thDTTP_index.size();
                
                for(int iThDTTP = 0; iThDTTP < nThDTTP; iThDTTP++)
                {
                    int deltaIeta =  input->v_ltTwinMux_thIeta->at(v_thDTTP_index.at(iThDTTP)) - input->v_hoTPdigi_iEta->at(iHOTP);
                    int deltaIetaSign = (deltaIeta < 0)? -1: 1;
                    deltaIeta = abs(deltaIeta);
                    
                    if(deltaIeta < deltaIeta_nearest)
                    {
                        thDTTP_index_min = v_thDTTP_index.at(iThDTTP);
                        deltaIeta_min = deltaIeta;
                        deltaIetaSign_min = deltaIetaSign;
                    }
                }
                
                // Check deltaIPhi
                if(deltaIphi <= MB1_HO_deltaIphiCut && deltaSector <= MB1_HO_deltaSectorCut )
                {
                    // Check wheels
                    if(deltaWheel <= MB1_HO_deltaWheelCut)
                    {
                        // Check iEta if available
                        if(!nThDTTP || (nThDTTP && deltaIeta_min <= MB1_HO_deltaIetaCut))
                        {
                            isHOTPmatched = true;
                            
                            if(deltaIphi_nearest > MB1_HO_deltaIphiCut \
                                || deltaWheel_nearest > MB1_HO_deltaWheelCut \
                                || deltaSector_nearest > MB1_HO_deltaSectorCut \
                                || (nThDTTP && deltaIeta_nearest > MB1_HO_deltaIetaCut))
                            {
                                deltaIphi_nearest = deltaIphi;
                                deltaIphiSign_nearest = deltaIphiSign;
                                
                                deltaIeta_nearest = deltaIeta_min;
                                deltaIetaSign_nearest = deltaIetaSign_min;
                                
                                deltaWheel_nearest = deltaWheel;
                                deltaWheelSign_nearest = deltaWheelSign;
                                
                                deltaSector_nearest = deltaSector;
                                deltaSectorSign_nearest = deltaSectorSign;
                                
                                thDTTP_index_nearest = thDTTP_index_min;
                                HOTP_index_nearest = iHOTP;
                            }
                        }
                    }
                }
                
                if(deltaIphi <= deltaIphi_nearest \
                    && deltaWheel <= deltaWheel_nearest \
                    && deltaSector <= deltaSector_nearest
                    && (nThDTTP && deltaIeta_min <= deltaIeta_nearest))
                {
                    deltaIphi_nearest = deltaIphi;
                    deltaIphiSign_nearest = deltaIphiSign;
                    
                    deltaIeta_nearest = deltaIeta_min;
                    deltaIetaSign_nearest = deltaIetaSign_min;
                    
                    deltaWheel_nearest = deltaWheel;
                    deltaWheelSign_nearest = deltaWheelSign;
                    
                    deltaSector_nearest = deltaSector;
                    deltaSectorSign_nearest = deltaSectorSign;
                    
                    thDTTP_index_nearest = thDTTP_index_min;
                    HOTP_index_nearest = iHOTP;
                }
            }
            
            
            /*if(deltaIphi_nearest <= MB1_HO_deltaIphiCut
                && getSectorFromIphi(input->v_hoTPdigi_iPhi->at(HOTP_index_nearest)) == input->v_ltTwinMuxIn_sector->at(iDTTP)
                && deltaWheel_nearest <= MB1_HO_deltaWheelCut
                && (!v_thDTTP_index.size() || (v_thDTTP_index.size() && deltaIeta_nearest <= MB1_HO_deltaIetaCut)))
            {
                isHOTPmatched = true;
            }*/
            
            
            int iDTTP_etaGlobal = -1;
            int iDTTP_orientation = 0;
            
            if(thDTTP_index_nearest >= 0)
            {
                int thWhNum = input->v_ltTwinMux_thWheel->at(thDTTP_index_nearest);
                int thScNum = input->v_ltTwinMux_thSector->at(thDTTP_index_nearest)-1;
                int thEtaLocal = input->v_ltTwinMux_thPosition->at(thDTTP_index_nearest);
                
                iDTTP_orientation = getDTorientation(thWhNum, thScNum);
                
                if(iDTTP_orientation < 0)
                {
                    thEtaLocal = thEtaLocal;
                }
                
                else
                {
                    thEtaLocal = 6 - thEtaLocal;
                }
                
                iDTTP_etaGlobal = (thWhNum+2)*7 + thEtaLocal;
            }
            
            if(isIsolated)
            {
                currentOutput->h1_isolatedMB1DTTP_pT->Fill(pT_iDTTP);
                
                if(is_LQ)
                {
                    isolatedMB1_n_LQ_noTimeMatching++;
                    //m_MB1_LQ[input->runNumber].at(2)++;
                    updateCounterMap(&m_MB1_LQ, input->runNumber, 2, pT_iDTTP);
                    
                    if(isHOTPmatched)
                    {
                        //m_MB1_LQ[input->runNumber].at(5)++;
                        updateCounterMap(&m_MB1_LQ, input->runNumber, 6, pT_iDTTP);
                        
                        currentOutput->h1_isolatedMB1DTTP_HOTP_pT->Fill(pT_iDTTP);
                    }
                }
                
                else if(is_HQ)
                {
                    isolatedMB1_n_HQ_noTimeMatching++;
                    //m_MB1_HQ[input->runNumber].at(2)++;
                    updateCounterMap(&m_MB1_HQ, input->runNumber, 2, pT_iDTTP);
                    
                    if(isHOTPmatched)
                    {
                        //m_MB1_HQ[input->runNumber].at(5)++;
                        updateCounterMap(&m_MB1_HQ, input->runNumber, 6, pT_iDTTP);
                        
                        currentOutput->h1_isolatedMB1DTTP_HOTP_pT->Fill(pT_iDTTP);
                    }
                }
                
                //if(isHOTPmatched)
                {
                    currentOutput->h2_isolatedMB1DTTP_iPhi_vs_wheel->Fill(input->v_ltTwinMuxIn_wheel->at(iDTTP), input->v_ltTwinMuxIn_iPhi->at(iDTTP));
                    currentOutput->h2_isolatedMB1DTTP_pT_vs_phiB->Fill(input->v_ltTwinMuxIn_phiB->at(iDTTP), pT_iDTTP);
                    
                    if(HOTP_index_nearest >= 0)
                    {
                        currentOutput->h1_isolatedMB1DTTP_HOTP_deltaIphi->Fill(deltaIphi_nearest*deltaIphiSign_nearest);
                        currentOutput->h1_isolatedMB1DTTP_HOTP_deltaWheel->Fill(deltaWheel_nearest*deltaWheelSign_nearest);
                        currentOutput->h2_isolatedMB1DTTP_HOTP_deltaIphi_vs_deltaWheel->Fill(deltaWheel_nearest*deltaWheelSign_nearest, deltaIphi_nearest*deltaIphiSign_nearest);
                        currentOutput->h2_isolatedMB1DTTP_HOTP_deltaIphi_vs_deltaIeta->Fill(deltaIeta_nearest*deltaIetaSign_nearest, deltaIphi_nearest*deltaIphiSign_nearest);
                        currentOutput->h2_isolatedMB1DTTP_HOTP_deltaSector_vs_deltaWheel->Fill(deltaWheel_nearest*deltaWheelSign_nearest, deltaSector_nearest*deltaSectorSign_nearest);
                        
                        currentOutput->h2_isolatedMB1DTTP_vs_HOTP_iPhi->Fill(input->v_hoTPdigi_iPhi->at(HOTP_index_nearest), input->v_ltTwinMuxIn_iPhi->at(iDTTP));
                        
                        int HOTP_phiLocal = (input->v_hoTPdigi_iPhi->at(HOTP_index_nearest) - 1 + 2) % 6;
                        currentOutput->h2_isolatedMB1DTTP_vs_HOTP_phiLocal->Fill(HOTP_phiLocal, input->v_ltTwinMuxIn_phi->at(iDTTP));
                        
                        if(thDTTP_index_nearest >= 0)
                        {
                            currentOutput->h2_isolatedMB1DTTP_vs_HOTP_iEta->Fill(input->v_hoTPdigi_iEta->at(HOTP_index_nearest), input->v_ltTwinMux_thIeta->at(thDTTP_index_nearest));
                            
                            if(iDTTP_orientation > 0)
                            {
                                currentOutput->h2_isolatedPlusMB1DTTP_vs_HOTP_etaLocal->Fill(input->v_hoTPdigi_iEta->at(HOTP_index_nearest), input->v_ltTwinMux_thPosition->at(thDTTP_index_nearest));
                            }
                            
                            if(iDTTP_orientation < 0)
                            {
                                currentOutput->h2_isolatedMinusMB1DTTP_vs_HOTP_etaLocal->Fill(input->v_hoTPdigi_iEta->at(HOTP_index_nearest), input->v_ltTwinMux_thPosition->at(thDTTP_index_nearest));
                            }
                            
                            currentOutput->h2_isolatedMB1DTTP_vs_HOTP_etaGlobal->Fill(input->v_hoTPdigi_iEta->at(HOTP_index_nearest), iDTTP_etaGlobal);
                        }
                    }
                }
            }
            
            else
            {
                currentOutput->h1_unisolatedMB1DTTP_pT->Fill(pT_iDTTP);
                
                if(is_LQ)
                {
                    updateCounterMap(&m_MB1_LQ, input->runNumber, 3, pT_iDTTP);
                    
                    if(isHOTPmatched)
                    {
                        updateCounterMap(&m_MB1_LQ, input->runNumber, 7, pT_iDTTP);
                        
                        currentOutput->h1_unisolatedMB1DTTP_HOTP_pT->Fill(pT_iDTTP);
                    }
                }
                
                else if(is_HQ)
                {
                    updateCounterMap(&m_MB1_HQ, input->runNumber, 3, pT_iDTTP);
                    
                    if(isHOTPmatched)
                    {
                        updateCounterMap(&m_MB1_HQ, input->runNumber, 7, pT_iDTTP);
                        
                        currentOutput->h1_unisolatedMB1DTTP_HOTP_pT->Fill(pT_iDTTP);
                    }
                }
                
                currentOutput->h1_unisolatedMB1DTTP_deltaBX->Fill(deltaBX_nearest);
                currentOutput->h1_unisolatedMB1DTTP_deltaPhi->Fill(deltaPhi_nearest*deltaPhiSign_nearest);
                currentOutput->h2_unisolatedMB1DTTP_deltaBX_vs_deltaPhi->Fill(deltaPhi_nearest*deltaPhiSign_nearest, deltaBX_nearest);
                currentOutput->h2_unisolatedMB1DTTP_pT_vs_deltaPhi->Fill(deltaPhi_nearest*deltaPhiSign_nearest, pT_iDTTP);
                currentOutput->h2_unisolatedMB1DTTP_pT_vs_phiB->Fill(input->v_ltTwinMuxIn_phiB->at(iDTTP), pT_iDTTP);
                
                if(HOTP_index_nearest >= 0)
                {
                    currentOutput->h2_unisolatedMB1DTTP_HOTP_deltaIphi_vs_deltaWheel->Fill(deltaWheel_nearest*deltaWheelSign_nearest, deltaIphi_nearest*deltaIphiSign_nearest);
                    currentOutput->h2_unisolatedMB1DTTP_HOTP_deltaIphi_vs_deltaIeta->Fill(deltaIeta_nearest*deltaIetaSign_nearest, deltaIphi_nearest*deltaIphiSign_nearest);
                    currentOutput->h2_unisolatedMB1DTTP_HOTP_deltaSector_vs_deltaWheel->Fill(deltaWheel_nearest*deltaWheelSign_nearest, deltaSector_nearest*deltaSectorSign_nearest);
                    
                    currentOutput->h2_unisolatedMB1DTTP_vs_HOTP_iPhi->Fill(input->v_hoTPdigi_iPhi->at(HOTP_index_nearest), input->v_ltTwinMuxIn_iPhi->at(iDTTP));
                    
                    int HOTP_phiLocal = (input->v_hoTPdigi_iPhi->at(HOTP_index_nearest) - 1 + 2) % 6;
                    currentOutput->h2_unisolatedMB1DTTP_vs_HOTP_phiLocal->Fill(HOTP_phiLocal, input->v_ltTwinMuxIn_phi->at(iDTTP));
                    
                    if(thDTTP_index_nearest >= 0)
                    {
                        currentOutput->h2_unisolatedMB1DTTP_vs_HOTP_iEta->Fill(input->v_hoTPdigi_iEta->at(HOTP_index_nearest), input->v_ltTwinMux_thIeta->at(thDTTP_index_nearest));
                        
                        if(iDTTP_orientation > 0)
                        {
                            currentOutput->h2_unisolatedPlusMB1DTTP_vs_HOTP_etaLocal->Fill(input->v_hoTPdigi_iEta->at(HOTP_index_nearest), input->v_ltTwinMux_thPosition->at(thDTTP_index_nearest));
                        }
                        
                        if(iDTTP_orientation < 0)
                        {
                            currentOutput->h2_unisolatedMinusMB1DTTP_vs_HOTP_etaLocal->Fill(input->v_hoTPdigi_iEta->at(HOTP_index_nearest), input->v_ltTwinMux_thPosition->at(thDTTP_index_nearest));
                        }
                        
                        currentOutput->h2_unisolatedMB1DTTP_vs_HOTP_etaGlobal->Fill(input->v_hoTPdigi_iEta->at(HOTP_index_nearest), iDTTP_etaGlobal);
                    }
                }
            }
            
            
            if(bestDTsegment_index_iDTTP == -1)
            {
                continue;
            }
            
            /*if(isIsolated_inTimeMatching)
            {
                currentOutput->h1_MB1DTTP_noDTTP_eta->Fill(input->v_dtsegm4D_eta->at(bestDTsegment_index_iDTTP));
            }
            
            int dtSegment_iEta = getIetaFromEta(input->v_dtsegm4D_eta->at(bestDTsegment_index_iDTTP));
            int ltTwinMux_thIeta = -99;
            
            int nThDTTP = input->v_ltTwinMux_thBx->size();
            
            for(int iThDTTP = 0; iThDTTP < nThDTTP; iThDTTP++)
            {
                if(input->v_ltTwinMux_thWheel->at(iThDTTP)+2 == whNum_iDTTP && \
                    input->v_ltTwinMux_thStation->at(iThDTTP)-1 == stNum_iDTTP && \
                    input->v_ltTwinMux_thSector->at(iThDTTP)-1 == scNum_iDTTP)
                {
                    ltTwinMux_thIeta = input->v_ltTwinMux_thIeta->at(iThDTTP);
                }
                
                if(ltTwinMux_thIeta != -99)
                {
                    break;
                }
            }
            
            //printf("%s st%d wh%d sc%d hasZed %d : ltTwinMux_thIeta %d, dtSegment_iEta %d, dtSegment_eta %f \n", \
                quality_str.c_str(), stNum_iDTTP+1, whNum_iDTTP-2, scNum_iDTTP+1, (int) input->v_dtsegm4D_hasZed->at(bestDTsegment_index_iDTTP), \
                ltTwinMux_thIeta, dtSegment_iEta, input->v_dtsegm4D_eta->at(bestDTsegment_index_iDTTP));
            
            currentOutput->v_h2_dtSegmentIeta_vs_thDigiIeta.at(stNum_iDTTP)->Fill(ltTwinMux_thIeta, dtSegment_iEta);*/
        }
    }
}


void updateCounterMap(std::map <long, std::map <int, std::vector <int> > > *myMap, long runNumber, int pos)
{
    // Increase counter for all pTcut
    for(int iPtCut = 0; iPtCut < v_pTcut.size(); iPtCut++)
    {
        (*myMap)[runNumber][v_pTcut.at(iPtCut)].at(pos)++;
    }
}


void updateCounterMap(std::map <long, std::map <int, std::vector <int> > > *myMap, long runNumber, int pos, double pT)
{
    for(int iPtCut = 0; iPtCut < v_pTcut.size(); iPtCut++)
    {
        if(pT >= (double) v_pTcut.at(iPtCut))
        {
            (*myMap)[runNumber][v_pTcut.at(iPtCut)].at(pos)++;
        }
    }
}


void parseCSV_runInfo()
{
    std::ifstream data("runInfo.txt");
    std::string line;
    std::vector <std::vector <std::string> > parsedCsv;
    
    while(std::getline(data, line))
    {
        // Skip comments (start with #)
        if(line.at(0) == '#')
        {
            continue;
        }
        
        std::stringstream lineStream(line);
        std::string cell;
        std::vector <std::string> parsedRow;
        
        while(std::getline(lineStream, cell, ','))
        {
            parsedRow.push_back(cell);
        }
        
        parsedCsv.push_back(parsedRow);
    }
    
    for(unsigned int i = 0; i < parsedCsv.size(); i++)
    {
        // Run number
        std::stringstream lineStream(parsedCsv[i][0]);
        std::string runNumber;
        std::getline(lineStream, runNumber, ':');
        v_runNumber.push_back(std::stol(runNumber));
        
        // Recorded luminosity
        std::string recordedLumi;
        recordedLumi = parsedCsv[i][parsedCsv[i].size()-1];
        v_recordedLumiPerLS.push_back(std::stof(recordedLumi));
        
        //printf("Run: %ld, Recorded lumi per LS: %f \n", v_runNumber[i], v_recordedLumiPerLS[i]);
    }
}


void parseCSV_pTlut()
{
    std::ifstream data("ptb12h_Feb2016.lut");
    std::string line;
    std::vector <std::vector <std::string> > parsedCsv;
    
    while(std::getline(data, line))
    {
        // Skip comments (start with #)
        if(line.at(0) == '#')
        {
            continue;
        }
        
        std::stringstream lineStream(line);
        std::string cell;
        std::vector <std::string> parsedRow;
        
        while(std::getline(lineStream, cell, ','))
        {
            parsedRow.push_back(cell);
        }
        
        parsedCsv.push_back(parsedRow);
        
        v_phiB.push_back(std::stoi(parsedRow.at(0)));
        v_pT.push_back(std::stof(parsedRow.at(1)) * 0.5);
        
        //printf("phiB %d, pT %f \n", v_phiB[v_phiB.size()-1], v_pT[v_pT.size()-1]);
    }
}


double getLumi(long runNumber)
{
    for(int iRun = 0; iRun < v_runNumber.size(); iRun++)
    {
        if(v_runNumber.at(iRun) == runNumber)
        {
            return v_recordedLumiPerLS.at(iRun);
        }
    }
    
    return -1;
}


double getPtFromPhiB(int phiB)
{
    for(int iPhiB = 0; iPhiB < v_phiB.size(); iPhiB++)
    {
        if(v_phiB.at(iPhiB) == phiB)
        {
            return v_pT.at(iPhiB);
        }
    }
    
    return -1;
}


double globalPhiFromDTphi(double phi, int secNum)
{
    double globalPhi = phi / 4096.0;
    globalPhi += M_PI / 6 * (secNum - 1);
    
    if(globalPhi > M_PI)
    {
        globalPhi -= M_PI * 2;
    }
    
    return globalPhi;
}


int getDTorientation(int whNum, int scNum)
{
    // whNum [-2, 2], scNum [0, 11]
    
    if(whNum == -2 || whNum == -1
        || (whNum == 0
            && (scNum == 0 || scNum == 3
                || scNum == 4 || scNum == 7
                || scNum == 8 || scNum == 11)))
    {
        return -1;
    }
    
    else
    {
        return 1;
    }
}


int getIetaFromEta(double eta)
{
    double dEta = 2*M_PI/72;
    
    int sign = eta > 0? 1: -1;
    
    int iEta;
    
    iEta = (int) (fabs(eta)/dEta + 1);
    iEta *= sign;
    
    return iEta;
}


bool isInSameWheel(double eta, int whNum)
{
    int iEta = getIetaFromEta(eta);
    
    return isInSameWheel(iEta, whNum);
}


bool isInSameWheel(int iEta, int whNum)
{
    /*if(iEta < -10 && whNum == -2)
    {
        return true;
    }
    
    if((iEta < -4 && iEta > -11) && whNum == -1)
    {
        return true;
    }
    
    if((iEta < 5 && iEta > -5) && whNum == 0)
    {
        return true;
    }
    
    if((iEta > 4 && iEta < 11) && whNum == 1)
    {
        return true;
    }
    
    if(iEta > 10 && whNum == 2)
    {
        return true;
    }*/
    
    if(whNum == getWheelFromIeta(iEta))
    {
        return true;
    }
    
    return false;
}


int getSectorFromIphi(int iPhi)
{
    // iPhi must be [1-72]
    // Returns sector [1-12]
    
    int secNum = (iPhi-1+2) % 72;
    
    secNum = (int) (secNum/6.0 + 1);
    
    return secNum;
}


int getWheelFromIeta(int iEta)
{
    if(iEta < -10)
    {
        return -2;
    }
    
    if(iEta < -4 && iEta > -11)
    {
        return -1;
    }
    
    if(iEta < 5 && iEta > -5)
    {
        return 0;
    }
    
    if(iEta > 4 && iEta < 11)
    {
        return 1;
    }
    
    if(iEta > 10)
    {
        return 2;
    }
    
    return -99;
}


double HOiEtaToEta(int iEta)
{
    // Eta segmentation in HO is 0.087
    double dEta = 0.087;
    
    double sign = (iEta < 0) ? -1: 1;
    
    // Take the mean eta
    double eta = (fabs(iEta)-1 + fabs(iEta)) / 2 * dEta;
    eta *= sign;
    
    return eta;
}


double HOiPhiToPhi(int iPhi)
{
    // Phi segmentation in HO is 0.087
    double dPhi = 0.087;
    
    // Take the mean phi
    double phi = (fabs(iPhi)-1 + fabs(iPhi)) / 2 * dPhi;
    
    if(phi > M_PI)
    {
        phi -= 2*M_PI;
    }
    
    return phi;
}
