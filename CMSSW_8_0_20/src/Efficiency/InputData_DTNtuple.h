# ifndef InputData_DTNtuple_H
# define InputData_DTNtuple_H


# include <vector>

# include <TFile.h>
# include <TTree.h>


namespace InputData_DTNtuple
{
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
        std::vector <double> *v_Mu_isMuLoose;
        std::vector <double> *v_Mu_isMuMedium;
        std::vector <double> *v_Mu_isMuTight;
        std::vector <double> *v_Mu_charge;
        std::vector <double> *v_Mu_px;
        std::vector <double> *v_Mu_py;
        std::vector <double> *v_Mu_pz;
        std::vector <double> *v_Mu_phi;
        std::vector <double> *v_Mu_eta;
        std::vector <double> *v_Mu_phiMB1;
        std::vector <double> *v_Mu_etaMB1;
        std::vector <double> *v_Mu_phiMB2;
        std::vector <double> *v_Mu_etaMB2;
        
        
        std::vector <double> *v_bmtf_pT;
        std::vector <double> *v_bmtf_eta;
        std::vector <double> *v_bmtf_phi;
        std::vector <double> *v_bmtf_globalPhi;
        std::vector <double> *v_bmtf_bx;
        std::vector <double> *v_bmtf_processor;
        std::vector <double> *v_bmtf_trAddress;
        std::vector <double> *v_bmtf_wheel;
        
        
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
            v_Mu_isMuLoose = 0;
            v_Mu_isMuMedium = 0;
            v_Mu_isMuTight = 0;
            v_Mu_charge = 0;
            v_Mu_px = 0;
            v_Mu_py = 0;
            v_Mu_pz = 0;
            v_Mu_phi = 0;
            v_Mu_eta = 0;
            v_Mu_phiMB1 = 0;
            v_Mu_etaMB1 = 0;
            v_Mu_phiMB2 = 0;
            v_Mu_etaMB2 = 0;
            
            
            v_bmtf_pT = 0;
            v_bmtf_eta = 0;
            v_bmtf_phi = 0;
            v_bmtf_globalPhi = 0;
            v_bmtf_bx = 0;
            v_bmtf_processor = 0;
            v_bmtf_trAddress = 0;
            v_bmtf_wheel = 0;
            
            
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
            tree->SetBranchAddress("Mu_isMuLoose", &v_Mu_isMuLoose);
            tree->SetBranchAddress("Mu_isMuMedium", &v_Mu_isMuMedium);
            tree->SetBranchAddress("Mu_isMuTight", &v_Mu_isMuTight);
            tree->SetBranchAddress("Mu_charge", &v_Mu_charge);
            tree->SetBranchAddress("Mu_px", &v_Mu_px);
            tree->SetBranchAddress("Mu_py", &v_Mu_py);
            tree->SetBranchAddress("Mu_pz", &v_Mu_pz);
            tree->SetBranchAddress("Mu_phi", &v_Mu_phi);
            tree->SetBranchAddress("Mu_eta", &v_Mu_eta);
            tree->SetBranchAddress("Mu_phiMB1", &v_Mu_phiMB1);
            tree->SetBranchAddress("Mu_etaMB1", &v_Mu_etaMB1);
            tree->SetBranchAddress("Mu_phiMB2", &v_Mu_phiMB2);
            tree->SetBranchAddress("Mu_etaMB2", &v_Mu_etaMB2);
            
            
            tree->SetBranchAddress("bmtfPt", &v_bmtf_pT);
            tree->SetBranchAddress("bmtfEta", &v_bmtf_eta);
            tree->SetBranchAddress("bmtfPhi", &v_bmtf_phi);
            tree->SetBranchAddress("bmtfGlobalPhi", &v_bmtf_globalPhi);
            tree->SetBranchAddress("bmtfbx", &v_bmtf_bx);
            tree->SetBranchAddress("bmtfprocessor", &v_bmtf_processor);
            tree->SetBranchAddress("bmtftrAddress", &v_bmtf_trAddress);
            tree->SetBranchAddress("bmtfwh", &v_bmtf_wheel);
        }
        
        
        void freeMemory()
        {
            delete tree;
            
            inputFile->Close();
            delete inputFile;
        }
    };
}


# endif
