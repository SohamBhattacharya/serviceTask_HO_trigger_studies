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

# include "Common.h"
# include "InputData_DTNtuple.h"


int nWheel = 5;
int nStation = 4;
int nSector = 12;

int str_len = 500;

double mu_pTcut = 0; // GeV
double mu_pTcutUpr = 0; // GeV
double mu_etaCut = 0.83;

double BMTF_pTcut = 0;
double BMTF_etaCut = 0.83;

bool selectHOiEta = true;

int isoMB1HO_3x3_cut = 1;
bool isoMB1HO_3x3_placeCut = true;

double MB34onlyBMTF_HO_deltaRcut = 0.4;

double deltaRcut = 0.4;
double deltaPhiCut = 0.4;

double DT_deltaPhicut = 0.4;
int MB1_pTcut = 0;
int MB1_HO_deltaIphiCut = 1;
int MB1_HO_deltaSectorCut = 0;
int MB1_HO_deltaIetaCut = 1;
int MB1_HO_deltaWheelCut = 0;

int MB2_HO_deltaIphiCut = 1;

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

int MB1_phiLocal_wrapAround = 2048;

int HOTP_bits_SOI = 4;

std::vector <int> v_runNumber;
std::vector <double> v_recordedLumiPerLS;

std::vector <int> v_phiB;
std::vector <double> v_pT;

// <run, <pTcut, 
//      <event_n, MB1_n, isolatedMB1_n, unisolatedMB1_n, 
//      HOTP_n, HOTP_SOI_n, isolatedMB1_withHOTP_SOI_n, unisolatedMB1_withHOTP_SOI_n, BMTF_n> > >
std::map <long, std::map <int, std::vector <int> > > m_MB1_LQ;
std::map <long, std::map <int, std::vector <int> > > m_MB1_HQ;

// <run, <event_n, 
//        MB2_n, MB2_wh+1_n, MB2_wh-1_n,
//        HO_SOI_n, HO_SOI_iEta+4_n, HO_SOI_iEta+4_MB2_wh+1_n, HO_SOI_iEta+4_MB2_wh-1_n, 
//        HO_SOI_iEta-4_n, HO_SOI_iEta-4_MB2_wh-1_n, HO_SOI_iEta-4_MB2_wh+1_n> >
std::map <long, std::vector <int> > m_MB2_LQ;
std::map <long, std::vector <int> > m_MB2_HQ;

std::vector <int> v_pTcut = {0, 5, 10, 14, 18, 22, 25, 30};

int DT_phi_max = 0;
int DT_phi_min = 0;


class OutputData
{
    public:
    
    
    std::vector <TH1F*> v_h1_dtsegm4D_mu_pT;
    std::vector <TH1F*> v_h1_dtsegm4D_mu_eta;
    
    std::vector <TH2F*> v_h2_dtsegm4D_mu_pT_vs_eta;
    
    std::vector <TH1F*> v_h1_dtsegm4D_withDTTP_mu_pT;
    std::vector <TH1F*> v_h1_dtsegm4D_withDTTP_mu_eta;
    
    std::vector <TH2F*> v_h2_dtsegm4D_withDTTP_mu_pT_vs_eta;
    
    
    OutputData()
    {
        char histName[str_len];
        char histTitle[str_len];
        
        for(int iStation = 0; iStation < nStation; iStation++)
        {
            //
            sprintf(histName, "dtsegm4D_mu_pT_station%d", iStation+1);
            sprintf(histTitle, "dtsegm4D_mu_pT_station%d", iStation+1);
            v_h1_dtsegm4D_mu_pT.push_back(new TH1F(histName, histTitle, 2000, 0, 1000));
            
            sprintf(histName, "dtsegm4D_mu_eta_station%d", iStation+1);
            sprintf(histTitle, "dtsegm4D_mu_eta_station%d", iStation+1);
            v_h1_dtsegm4D_mu_eta.push_back(new TH1F(histName, histTitle, 68, -3, 3));
            
            sprintf(histName, "dtsegm4D_mu_pT_vs_eta_station%d", iStation+1);
            sprintf(histTitle, "dtsegm4D_mu_pT_vs_eta_station%d", iStation+1);
            v_h2_dtsegm4D_mu_pT_vs_eta.push_back(new TH2F(histName, histTitle, 68, -3, 3, 2000, 0, 1000));
            
            //
            sprintf(histName, "dtsegm4D_withDTTP_mu_pT_station%d", iStation+1);
            sprintf(histTitle, "dtsegm4D_withDTTP_mu_pT_station%d", iStation+1);
            v_h1_dtsegm4D_withDTTP_mu_pT.push_back(new TH1F(histName, histTitle, 2000, 0, 1000));
            
            sprintf(histName, "dtsegm4D_withDTTP_mu_eta_station%d", iStation+1);
            sprintf(histTitle, "dtsegm4D_withDTTP_mu_eta_station%d", iStation+1);
            v_h1_dtsegm4D_withDTTP_mu_eta.push_back(new TH1F(histName, histTitle, 68, -3, 3));
            
            sprintf(histName, "dtsegm4D_withDTTP_mu_pT_vs_eta_station%d", iStation+1);
            sprintf(histTitle, "dtsegm4D_withDTTP_mu_pT_vs_eta_station%d", iStation+1);
            v_h2_dtsegm4D_withDTTP_mu_pT_vs_eta.push_back(new TH2F(histName, histTitle, 68, -3, 3, 2000, 0, 1000));
        }
    }
    
    
    void writeData()
    {
        for(int iStation = 0; iStation < nStation; iStation++)
        {
            v_h1_dtsegm4D_mu_pT.at(iStation)->Write();
            v_h1_dtsegm4D_mu_eta.at(iStation)->Write();
            v_h2_dtsegm4D_mu_pT_vs_eta.at(iStation)->Write();
            
            v_h1_dtsegm4D_withDTTP_mu_pT.at(iStation)->Write();
            v_h1_dtsegm4D_withDTTP_mu_eta.at(iStation)->Write();
            v_h2_dtsegm4D_withDTTP_mu_pT_vs_eta.at(iStation)->Write();
        }
    }
    
    
    void freeMemory()
    {
        for(int iStation = 0; iStation < nStation; iStation++)
        {
            delete v_h1_dtsegm4D_mu_pT.at(iStation);
            delete v_h1_dtsegm4D_mu_eta.at(iStation);
            delete v_h2_dtsegm4D_mu_pT_vs_eta.at(iStation);
            
            delete v_h1_dtsegm4D_withDTTP_mu_pT.at(iStation);
            delete v_h1_dtsegm4D_withDTTP_mu_eta.at(iStation);
            delete v_h2_dtsegm4D_withDTTP_mu_pT_vs_eta.at(iStation);
        }
    }
};


void analyze(InputData_DTNtuple::InputData *input, OutputData *output, OutputData *output_LQ, OutputData *output_HQ);


int main()
{
    std::string process;
    
    process = "@process@";
    //process = "SingleMuon_Run2017C-ZMu-PromptReco-v3_RAW-RECO";
    //process = "MET_Run2017C-v1_RAW";
    
    char sourceFileList[500];
    
    sprintf(sourceFileList, "@source@");
    //sprintf(sourceFileList, "sourceFiles/%s/%s.txt", process.c_str(), process.c_str());
    printf("Source file list: %s \n", sourceFileList);
    
    Common::parseCSV_pTlut("ptb12h_Feb2016.lut", &v_phiB, &v_pT);
    
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
    sprintf(outputDir, "output/%s_DTTPefficiency", process.c_str());
    
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
        //n++; if(n > 200) break; 
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
        
        if(nEvent_global_max > 0 && nEvent_global > nEvent_global_max)
        {
            break;
        }
        
        printf("\n");
    }
    
    
    printf("\n");
    printf("********** Total events processed = %d ********** \n", nEvent_global);
    printf("\n");
    
    return 0;
}


void analyze(InputData_DTNtuple::InputData *input, OutputData *output, OutputData *output_LQ, OutputData *output_HQ)
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
        
        nEvent_global++;
        
        //printf("runNumber %ld, lumiBlock %ld, eventNumber %ld, iEvent %d \n", \
            input->runNumber, input->lumiBlock, input->eventNumber, iEvent);
        
        //fprintf(output->eventInfoFile, "%d,%d,%d,%d \n", \
            input->runNumber, input->lumiBlock, input->eventNumber, iEvent);
        
        int nMuon = input->v_Mu_eta->size();
        
        int nMuon_selected = 0;
        std::vector <int> v_mu_isSelected(nMuon, false);
        
        for(int iMuon = 0; iMuon < nMuon; iMuon++)
        {
            // Muon must be Global and Tracker
            if(/* !input->v_Mu_isMuGlobal->at(iMuon) || */!input->v_Mu_isMuTracker->at(iMuon))
            {
                continue;
            }
            
            //if(!input->v_Mu_isMuMedium->at(iMuon))
            //{
            //    continue;
            //}
            
            double pT_iMuon = sqrt(pow(input->v_Mu_px->at(iMuon), 2) + pow(input->v_Mu_py->at(iMuon), 2));
            double eta_iMuon = input->v_Mu_eta->at(iMuon);
            double phi_iMuon = input->v_Mu_phi->at(iMuon);
            
            // Muon pT, eta cut
            if(pT_iMuon < mu_pTcut || fabs(eta_iMuon) > mu_etaCut)
            {
                continue;
            }
            
            // Muon pT upper cut (apply only if cut > 0)
            if(mu_pTcutUpr > 0 && pT_iMuon > mu_pTcutUpr)
            {
                continue;
            }
            
            nMuon_selected++;
            v_mu_isSelected.at(iMuon) = true;
        }
        
        // At least one muon in the event
        if(!nMuon_selected)
        {
            continue;
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
                    
                    //std::vector <bool> v_mu_isMatched(nMuon, false);
                    
                    for(int iMuon = 0; iMuon < nMuon; iMuon++)
                    {
                        if(!v_mu_isSelected.at(iMuon))
                        {
                            continue;
                        }
                        
                        double pT_iMuon = sqrt(pow(input->v_Mu_px->at(iMuon), 2) + pow(input->v_Mu_py->at(iMuon), 2));
                        double eta_iMuon = input->v_Mu_eta->at(iMuon);
                        double phi_iMuon = input->v_Mu_phi->at(iMuon);
                        
                        double deltaEta = eta_iMuon - input->v_dtsegm4D_eta->at(bestDTsegment_index);
                        
                        double deltaPhi = phi_iMuon - input->v_dtsegm4D_phi->at(bestDTsegment_index);
                        deltaPhi = (deltaPhi > M_PI)? (deltaPhi-2*M_PI): deltaPhi;
                        deltaPhi = (deltaPhi < -M_PI)? (deltaPhi+2*M_PI): deltaPhi;
                        
                        double deltaR = sqrt(pow(deltaEta, 2) + pow(deltaPhi, 2));
                        
                        // Check only deltaPhi for MB4
                        if(iStation+1 == 4)
                        {
                            if(fabs(deltaPhi) < deltaPhiCut && fabs(deltaPhi) < deltaPhi_min)
                            {
                                deltaPhi_min = deltaPhi;
                                
                                isMuMatched = true;
                                matchedMuon_index = iMuon;
                                matchedMuon_pT = pT_iMuon;
                                matchedMuon_eta = eta_iMuon;
                                matchedMuon_phi = phi_iMuon;
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
                                matchedMuon_pT = pT_iMuon;
                                matchedMuon_eta = eta_iMuon;
                                matchedMuon_phi = phi_iMuon;
                            }
                        }
                    }
                    
                    if(!isMuMatched)
                    {
                        continue;
                    }
                    
                    
                    output->v_h1_dtsegm4D_mu_pT[iStation]->Fill(matchedMuon_pT);
                    output->v_h1_dtsegm4D_mu_eta[iStation]->Fill(matchedMuon_eta);
                    output->v_h2_dtsegm4D_mu_pT_vs_eta[iStation]->Fill(matchedMuon_eta, matchedMuon_pT);
                    
                    printf("Matching muon found: index %d, st %d, wh %d, sc %d, " \
                        "pT %f, eta %f, phi %f \n", \
                        bestDTsegment_index, iStation+1, iWheel-2, iSector+1, \
                        matchedMuon_pT, matchedMuon_eta, matchedMuon_phi);
                    
                    
                    // Search for matching DTTP (at BX = 0) in the same wheel, station, and sector
                    int matchedDTTP_index = -1;
                    int matchedDTTP_isHQ = false;
                    
                    deltaPhi_min = 9999;
                    int nDTTP = input->v_ltTwinMuxOut_wheel->size();
                    
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
                        
                        double phi_iDTTP = Common::globalPhiFromDTphi(input->v_ltTwinMuxOut_phi->at(iDTTP), scNum_iDTTP);
                        
                        double deltaPhi = fabs(matchedMuon_phi - phi_iDTTP);
                        deltaPhi = (deltaPhi > M_PI)? (deltaPhi-2*M_PI): deltaPhi;
                        deltaPhi = (deltaPhi < -M_PI)? (deltaPhi+2*M_PI): deltaPhi;
                        
                        if(iWheel-2 == whNum_iDTTP &&
                            iStation+1 == stNum_iDTTP //&&
                            //iSector+1 == scNum_iDTTP
                        )
                        {
                            if(fabs(deltaPhi) < 0.4 && fabs(deltaPhi) < deltaPhi_min)
                            {
                                matchedDTTP_index = iDTTP;
                            }
                        }
                    }
                    
                    if(matchedDTTP_index >= 0)
                    {
                        output->v_h1_dtsegm4D_withDTTP_mu_pT[iStation]->Fill(matchedMuon_pT);
                        output->v_h1_dtsegm4D_withDTTP_mu_eta[iStation]->Fill(matchedMuon_eta);
                        output->v_h2_dtsegm4D_withDTTP_mu_pT_vs_eta[iStation]->Fill(matchedMuon_eta, matchedMuon_pT);
                    }
                }
            }
        }
    }
}
