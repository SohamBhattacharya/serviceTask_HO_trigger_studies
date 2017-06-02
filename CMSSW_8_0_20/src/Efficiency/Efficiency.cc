# include <iostream>
# include <fstream>
# include <string>
# include <vector>

# include <CLHEP/Vector/ThreeVector.h>
# include <CLHEP/Vector/LorentzVector.h>

# include <TFile.h>
# include <TH1F.h>
# include <TTree.h>


int nWheel = 5;
int nStation = 4;
int nSector = 12;

int str_len = 500;

double mu_pTcut = 14; // GeV
double mu_etaCut = 1.2;

double deltaRcut = 0.4;
double deltaPhiCut = 0.4;

int DTsegment_nHit_phiLocal_min = 4;
int DTsegment_phiLocal_max = 45; // degree

int nEvent_global = 0;
int nEvent_global_max = 0;


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
    
    
    std::vector <int> *v_ltTwinMux_thBx;
    std::vector <int> *v_ltTwinMux_thWheel;
    std::vector <int> *v_ltTwinMux_thSector;
    std::vector <int> *v_ltTwinMux_thStation;
    std::vector <int> *v_ltTwinMux_thHits;
    std::vector <int> *v_ltTwinMux_thIeta;
    
    
    std::vector <double> *v_Mu_isMuGlobal;
    std::vector <double> *v_Mu_isMuTracker;
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
        
        
        v_ltTwinMux_thBx = 0;
        v_ltTwinMux_thWheel = 0;
        v_ltTwinMux_thSector = 0;
        v_ltTwinMux_thStation = 0;
        v_ltTwinMux_thHits = 0;
        v_ltTwinMux_thIeta = 0;
        
        
        v_Mu_isMuGlobal = 0;
        v_Mu_isMuTracker = 0;
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
        //tree->SetBranchAddress("ltTwinMuxIn_iPhi", &v_ltTwinMuxIn_iPhi);
        
        tree->SetBranchAddress("ltTwinMux_thBx", &v_ltTwinMux_thBx);
        tree->SetBranchAddress("ltTwinMux_thWheel", &v_ltTwinMux_thWheel);
        tree->SetBranchAddress("ltTwinMux_thSector", &v_ltTwinMux_thSector);
        tree->SetBranchAddress("ltTwinMux_thStation", &v_ltTwinMux_thStation);
        tree->SetBranchAddress("ltTwinMux_thHits", &v_ltTwinMux_thHits);
        //tree->SetBranchAddress("ltTwinMux_thIeta", &v_ltTwinMux_thIeta);
        
        tree->SetBranchAddress("Mu_isMuGlobal", &v_Mu_isMuGlobal);
        tree->SetBranchAddress("Mu_isMuTracker", &v_Mu_isMuTracker);
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
    
    TFile *outputFile;
    
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
    
    
    OutputData(const char *outputFileName)
    {
        outputFile = TFile::Open(outputFileName, "RECREATE");
        
        for(int iStation = 0; iStation < nStation; iStation++)
        {
            char histName[str_len];
            char histTitle[str_len];
            
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
            
        }
    }
    
    
    void writeData()
    {
        outputFile->cd();
        
        for(int iStation = 0; iStation < nStation; iStation++)
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
        }
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
        }
        
        outputFile->Close();
        delete outputFile;
    }
};


void analyze(InputData *input, OutputData *output);
double HOiEtaToEta(int iEta);
double HOiPhiToPhi(int iEta);

int getIetaFromEta(double eta);
bool isInSameWheel(double eta, int whNum);


int main()
{
    std::string process = "SingleMuon";
    
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
    
    //OutputData *output = new OutputData("output/efficiency.root");//, "output/eventInfo.txt");
    
    //nEvent_global_max = 2*pow(10, 6);
    nEvent_global_max = -1;
    
    // Analyze input files
    for(int iFile = 0; iFile < v_sourceFileName.size(); iFile++)
    {
        std::string inputFileName = v_sourceFileName.at(iFile);
        
        printf("Input file: %s \n", inputFileName.c_str());
        InputData *input = new InputData(inputFileName.c_str());
        
        char fileNameStripped[500];
        sprintf(fileNameStripped, "%s", \
            (inputFileName.substr(inputFileName.rfind("/")+1, inputFileName.rfind(".root")-inputFileName.rfind("/")-1)).c_str());
        
        char outputFileName[500];
        sprintf(outputFileName, "%s/%s_efficiency.root", outputDir, fileNameStripped);
        
        printf("Output file: %s \n", outputFileName);
        OutputData *output = new OutputData(outputFileName);
        
        analyze(input, output);
        output->writeData();
        
        output->freeMemory();
        delete output;
        
        input->freeMemory();
        delete input;
        
        if(nEvent_global_max > 0 && nEvent_global > nEvent_global_max)
        {
            break;
        }
        
        printf("\n");
    }
    
    return 0;
}


void analyze(InputData *input, OutputData *output)
{
    int nEvent = input->tree->GetEntries();
    
    //int nEvent_max = 2*pow(10, 6);
    //nEvent = (nEvent > nEvent_max)? nEvent_max: nEvent;
    
    for(int iEvent = 0; iEvent < nEvent; iEvent++)
    {
        nEvent_global++;
        
        printf("********** Event %d/%d ********** \n", iEvent+1, nEvent);
        printf("********** Total event %d/%d ********** \n", nEvent_global, nEvent_global_max);
        
        if(!((iEvent+1)%1000))
        {
            fflush(stdout);
        }
        
        int entryStatus = input->tree->GetEntry(iEvent);
        
        // Check for corrupt entry
        if(entryStatus == -1)
        {
            printf("Corrupt entry.");
            
            continue;
        }
        
        if(input->eventNumber <= 0)
        {
            continue;
        }
        
        printf("runNumber %ld, lumiBlock %ld, eventNumber %ld, iEvent %d \n", \
            input->runNumber, input->lumiBlock, input->eventNumber, iEvent);
        
        //fprintf(output->eventInfoFile, "%d,%d,%d,%d \n", \
            input->runNumber, input->lumiBlock, input->eventNumber, iEvent);
        
        
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
        for(int iStation = 0; iStation < nStation; iStation++)
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
                        double pT_BMTF = input->v_gmt_pT->at(iBMTF);
                        double eta_BMTF = input->v_gmt_eta->at(iBMTF);
                        double phi_BMTF = input->v_gmt_phi->at(iBMTF);
                        
                        double eta_dtsegm4D = input->v_dtsegm4D_eta->at(bestDTsegment_index);
                        double phi_dtsegm4D = input->v_dtsegm4D_phi->at(bestDTsegment_index);
                        
                        /*int nMatchedDTTP = v_matchedDTTP_index.size();
                        
                        for(int iDTTP = 0; iDTTP < nMatchedDTTP; iDTTP++)
                        {
                            int bx_DTTP = (int) input->v_ltTwinMuxIn_bx->at(v_matchedDTTP_index[iDTTP]);
                            int secNum_DTTP = (int) input->v_ltTwinMuxIn_sector->at(v_matchedDTTP_index[iDTTP]);
                            
                            double phi_DTTP = input->v_ltTwinMuxIn_phi->at(v_matchedDTTP_index[iDTTP]);
                            
                            // Convert to global phi
                            phi_DTTP /= 4096.0;
                            phi_DTTP += 2.0*M_PI/12.0 * (secNum_DTTP - 1);
                            
                            if(phi_DTTP > M_PI)
                            {
                                phi_DTTP -= 2*M_PI;
                            }*/
                            
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
                        /*}
                        
                        if(foundBMTF)
                        {
                            break;
                        }*/
                    }
                    
                    if(foundDTTP)
                    {
                        printf("Matching DTTP found. \n");
                        
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
                    if(iStation+1 != 2)
                    {
                        continue;
                    }
                    
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
                        
                        //double deltaEta = fabs(input->v_dtsegm4D_eta->at(bestDTsegment_index) - input->v_dtsegm4D_eta->at(bestDTsegment_index_MB1));
                        //double deltaPhi = fabs(input->v_dtsegm4D_phi->at(bestDTsegment_index) - input->v_dtsegm4D_phi->at(bestDTsegment_index_MB1));
                        double deltaEta = fabs(matchedMuon_eta - input->v_dtsegm4D_eta->at(bestDTsegment_index_MB1));
                        double deltaPhi = fabs(matchedMuon_phi - input->v_dtsegm4D_phi->at(bestDTsegment_index_MB1));
                        double deltaR = sqrt(pow(deltaEta, 2) + pow(deltaPhi, 2));
                        
                        // Match the MB1 DTTP (using its best DT-segment) to the MB2 DT-segment
                        if(deltaR > deltaRcut)
                        {
                            continue;
                        }
                        
                        printf("Matching MB1 DTTP found. \n");
                        foundMB1DTTP = true;
                        
                        // Search for an HOTP matching the MB1 DTTP
                        int nHOTP = input->v_hoTPdigi_bits->size();
                        
                        for(int iHOTP = 0; iHOTP < nHOTP; iHOTP++)
                        {
                            //int deltaIeta = (int) fabs(input->v_hoTPdigi_iEta - etaToIeta(matchedMuon_eta));
                            //int deltaIphi = (int) fabs(input->v_hoTPdigi_iPhi - phiToIphi(matchedMuon_phi));
                            
                            //deltaEta = fabs(HOiEtaToEta(input->v_hoTPdigi_iEta->at(iHOTP)) - input->v_dtsegm4D_eta->at(bestDTsegment_index_MB1));
                            //deltaPhi = fabs(HOiPhiToPhi(input->v_hoTPdigi_iPhi->at(iHOTP)) - input->v_dtsegm4D_phi->at(bestDTsegment_index_MB1));
                            
                            deltaEta = fabs(HOiEtaToEta(input->v_hoTPdigi_iEta->at(iHOTP)) - matchedMuon_eta);
                            deltaPhi = fabs(HOiPhiToPhi(input->v_hoTPdigi_iPhi->at(iHOTP)) - matchedMuon_phi);
                            
                            deltaR = sqrt(pow(deltaEta, 2) + pow(deltaPhi, 2));
                            
                            // Match the HO-TP to the muon that was matched to the MB2 DT-segment
                            //if(deltaEta < 0.087 && deltaPhi < 0.087)
                            if(deltaR < 0.2)
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
                        output->v_h1_dtdegm4D_noDTTP_withMB1DTTP_mu_pT[iStation]->Fill(matchedMuon_pT);
                        output->v_h1_dtdegm4D_noDTTP_withMB1DTTP_mu_eta[iStation]->Fill(matchedMuon_eta);
                        
                        if(!foundBMTF)
                        {
                            output->v_h1_dtdegm4D_noDTTP_noBMTF_withMB1DTTP_mu_pT[iStation]->Fill(matchedMuon_pT);
                            output->v_h1_dtdegm4D_noDTTP_noBMTF_withMB1DTTP_mu_eta[iStation]->Fill(matchedMuon_eta);
                        }
                    }
                    
                    if(!foundHOTP)
                    {
                        printf("Matching HOTP NOT found. \n");
                        
                        continue;
                    }
                    
                    printf("Matching HOTP found: index %d, eta %f, phi %f \n", \
                        HOiPhiToPhi(input->v_hoTPdigi_iPhi->at(matchedHOTP_index)), HOiPhiToPhi(input->v_hoTPdigi_iPhi->at(matchedHOTP_index)));
                    
                    output->v_h1_dtdegm4D_noDTTP_withMB1DTTP_withHOTP_mu_pT[iStation]->Fill(matchedMuon_pT);
                    output->v_h1_dtdegm4D_noDTTP_withMB1DTTP_withHOTP_mu_eta[iStation]->Fill(matchedMuon_eta);
                    
                    if(!foundBMTF)
                    {
                        output->v_h1_dtdegm4D_noDTTP_noBMTF_withMB1DTTP_withHOTP_mu_pT[iStation]->Fill(matchedMuon_pT);
                        output->v_h1_dtdegm4D_noDTTP_noBMTF_withMB1DTTP_withHOTP_mu_eta[iStation]->Fill(matchedMuon_eta);
                    }
                    
                    if(foundMipHOTP)
                    {
                        printf("Matching mip-HOTP found. \n");
                        
                        output->v_h1_dtdegm4D_noDTTP_withMB1DTTP_withMipHOTP_mu_pT[iStation]->Fill(matchedMuon_pT);
                        output->v_h1_dtdegm4D_noDTTP_withMB1DTTP_withMipHOTP_mu_eta[iStation]->Fill(matchedMuon_eta);
                    }
                }
            }
        }
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
    
    if(iEta < -10 && whNum == -2)
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
    }
    
    return false;
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
