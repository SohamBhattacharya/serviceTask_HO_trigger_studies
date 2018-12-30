# ifndef Common_H
# define Common_H


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


namespace Common
{
    void parseCSV_pTlut(std::string fileName, std::vector <int> *v_phiB, std::vector <double> *v_pT)
    {
        std::ifstream data(fileName);
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
            
            v_phiB->push_back(std::stoi(parsedRow.at(0)));
            v_pT->push_back(std::stof(parsedRow.at(1)) * 0.5);
            
            //printf("phiB %d, pT %f \n", v_phiB[v_phiB.size()-1], v_pT[v_pT.size()-1]);
        }
    }
    
    
    double getPtFromPhiB(int phiB, std::vector <int> *v_phiB, std::vector <double> *v_pT)
    {
        for(int iPhiB = 0; iPhiB < v_phiB->size(); iPhiB++)
        {
            if(v_phiB->at(iPhiB) == phiB)
            {
                return v_pT->at(iPhiB);
            }
        }
        
        return -1;
    }
    
    
    double globalPhiFromDTphi(double phi, int secNum)
    {
        // secNum must be [1, 12]
        double globalPhi = phi / 4096.0;
        globalPhi += M_PI / 6 * (secNum - 1);
        
        if(globalPhi > M_PI)
        {
            globalPhi -= M_PI * 2;
        }
        
        return globalPhi;
    }
    
    
    double bmtfGlobalPhiToCmsPhi(int phi)
    {
        // [0, 576] to [-pi, pi]
        
        double cmsPhi = 2*M_PI*phi/576;
        
        if(cmsPhi > M_PI)
        {
            cmsPhi -= M_PI * 2;
        }
        
        return cmsPhi;
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
        // Returns [-2, 2]
        
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
        // Eta segmentation in HO is 2*pi/72 = ~0.087
        double dEta = 2*M_PI/72;
        
        double sign = (iEta < 0) ? -1: 1;
        
        // Take the mean eta
        double eta = (fabs(iEta)-1 + fabs(iEta)) / 2 * dEta;
        eta *= sign;
        
        return eta;
    }
    
    
    double HOiPhiToPhi(int iPhi)
    {
        // Phi segmentation in HO is 0.087
        double dPhi = 2.0*M_PI/72.0;
        
        // Take the mean phi
        double phi = (fabs(iPhi)-1 + fabs(iPhi)) / 2 * dPhi;
        
        if(phi > M_PI)
        {
            phi -= 2*M_PI;
        }
        
        return phi;
    }
    
    
    int etaToIeta(double eta)
    {
        double dEta = 2*M_PI/72;
        
        int sign = (eta < 0) ? -1: 1;
        
        int iEta = (int) (fabs(eta)/dEta + 1);
        iEta *= sign;
        
        return iEta;
    }
    
    
    int phiToIphi(double phi)
    {
        // [-pi, pi] to [1, 72]
        
        double dPhi = 2*M_PI/72;
        
        phi = (phi < 0)? phi+2*M_PI: phi;
        
        int iPhi = (int) (fabs(phi)/dPhi + 1);
        
        return iPhi;
    }
    
    
    int etaToSubIeta(double eta, int nDiv)
    {
        double dEta = 2*M_PI/72;
        double dSubEta = dEta / nDiv;
        
        int iEta = etaToIeta(eta);
        
        eta = fabs(eta);
        eta -= (abs(iEta)-1) * dEta;
        
        int subIeta = (int) (eta/dSubEta + 1);
        
        return subIeta;
    }
    
    
    int getBMTFstationMask(int trAdd_MB1, int trAdd_MB2, int trAdd_MB3, int trAdd_MB4)
    {
        int stationMask = 0;
        
        if(trAdd_MB1 != 3)
        {
            stationMask |= (1<<0);
        }
        
        if(trAdd_MB2 != 15)
        {
            stationMask |= (1<<1);
        }
        
        if(trAdd_MB3 != 15)
        {
            stationMask |= (1<<2);
        }
        
        if(trAdd_MB4 != 15)
        {
            stationMask |= (1<<3);
        }
        
        return stationMask;
    }
    
    
    bool isEtaMatched_MB34HO(int iEta_HO, int whNum_DTTP, int stNum_DTTP)
    {
        // stNum_DTTP must be 3 or 4
        if(stNum_DTTP != 3 && stNum_DTTP != 4)
        {
            printf("Error in function Common::isEtaMatched_MB34HO. \n");
            printf("stNum_DTTP MUST be 3 or 4 \n");
            
            exit(EXIT_FAILURE);
        }
        
        // whNum_DTTP must be [-2, 2] 
        if(abs(whNum_DTTP) > 2)
        {
            printf("Error in function Common::isEtaMatched_MB34HO. \n");
            printf("whNum_DTTP MUST be [-2, 2] \n");
            
            exit(EXIT_FAILURE);
        }
        
        
        bool isMatched = true;
        
        // HO in iEta1/2, MB3/4 in wh0
        if(abs(iEta_HO) <= 2 && abs(whNum_DTTP) != 0)
        {
            isMatched = false;
        }
        
        // HO in iEta3, MB3 in wh0/1
        else if(abs(iEta_HO) == 3 && stNum_DTTP == 3 && abs(whNum_DTTP) == 2)
        {
            isMatched = false;
        }
        
        // HO in iEta3, MB4 in wh1
        else if(abs(iEta_HO) == 3 && stNum_DTTP == 4 && abs(whNum_DTTP) != 1)
        {
            isMatched = false;
        }
        
        // HO in iEta4/5/6, MB3/4 in wh1
        else if(abs(iEta_HO) >= 4 && abs(iEta_HO) <= 6 && abs(whNum_DTTP) != 1)
        {
            isMatched = false;
        }
        
        // HO in iEta7, MB3 in wh1
        else if(abs(iEta_HO) == 7 && stNum_DTTP == 3 && abs(whNum_DTTP) != 1)
        {
            isMatched = false;
        }
        
        // HO in iEta7, MB4 in wh1/2
        else if(abs(iEta_HO) == 7 && stNum_DTTP == 4 && abs(whNum_DTTP) == 0)
        {
            isMatched = false;
        }
        
        // HO in iEta8/9/10, MB3/4 in wh2
        else if(abs(iEta_HO) >= 8 && abs(iEta_HO) <= 10 && abs(whNum_DTTP) != 2)
        {
            isMatched = false;
        }
        
        
        return isMatched;
    }
    
    
    // Returns the number of hits in a 3x3 tile window around the given hit
    int getHO3x3hits(int HOTP_iEta, int HOTP_iPhi,
        std::vector <int> *v_HOTP_iEta, std::vector <int> *v_HOTP_iPhi,
        std::vector <int> *v_HOTP_bits, int HOTP_bits_SOI
    )
    {
        int nHO3x3hit = 0;
        int nHOTP = v_HOTP_iEta->size();
        
        for(int iHOTP = 0; iHOTP < nHOTP; iHOTP++)
        {
            // HOTP at SOI only
            if(v_HOTP_bits->at(iHOTP) != HOTP_bits_SOI)
            {
                continue;
            }
            
            int iPhi_iHOTP = v_HOTP_iPhi->at(iHOTP);
            int iEta_iHOTP = v_HOTP_iEta->at(iHOTP);
            
            //int whNum_iHOTP = Common::getWheelFromIeta(input->v_HOTP_iEta->at(iHOTP));
            //int scNum_iHOTP = Common::getSectorFromIphi(input->v_HOTP_iPhi->at(iHOTP));
            
            int deltaIeta = HOTP_iEta - iEta_iHOTP;
            
            int deltaIphi = HOTP_iPhi - iPhi_iHOTP;
            deltaIphi = (deltaIphi > 36)? (deltaIphi-72): deltaIphi;
            deltaIphi = (deltaIphi < -36)? (deltaIphi+72): deltaIphi;
            
            if(abs(deltaIeta) <= 1 && abs(deltaIphi) <= 1)
            {
                nHO3x3hit++;
            }
        }
        
        // Subtract the count for the same hit (i.e. deltaIeta = 0 && deltaIphi = 0)
        nHO3x3hit--;
        
        return nHO3x3hit;
    }
    
    
    // Returns pair <iDTTP, deltaPhi>
    std::pair <int, double> getNearestDTTPtoBMTF(
        int phi_BMTF, int st_iBMTF,
        std::vector <int> *v_DTTP_bx,
        std::vector <int> *v_DTTP_station,
        std::vector <int> *v_DTTP_wheel,
        std::vector <int> *v_DTTP_sector,
        std::vector <int> *v_DTTP_phi,
        std::vector <int> *v_DTTP_BMTFindex
    )
    {
        int nearestDTTP_index = -1;
        double deltaPhi_min = 9999;
        int nDTTP = v_DTTP_bx->size();
        
        std::pair <int, double> p_nearestDTTP_info(nearestDTTP_index, deltaPhi_min);
        
        for(int iDTTP = 0; iDTTP < nDTTP; iDTTP++)
        {
            int st_iDTTP = v_DTTP_station->at(iDTTP);
            int wh_iDTTP = v_DTTP_wheel->at(iDTTP);
            int sc_iDTTP = v_DTTP_sector->at(iDTTP);
            
            int bx_iDTTP = v_DTTP_bx->at(iDTTP);
            
            if(bx_iDTTP != 0)
            {
                continue;
            }
            
            // Skip if already associated to a BMTF
            //if(v_DTTP_BMTFindex->at(iDTTP) >= 0)
            //{
            //    continue;
            //}
            
            // Select the correct station
            if(st_iDTTP != st_iBMTF)
            {
                continue;
            }
            
            // Exclude wheels +-2 of MB1
            if(st_iDTTP == 1 && abs(wh_iDTTP) == 2)
            {
                continue;
            }
            
            double phi_iDTTP = Common::globalPhiFromDTphi(v_DTTP_phi->at(iDTTP), sc_iDTTP);
            
            double deltaPhi = phi_BMTF - phi_iDTTP;
            deltaPhi = (deltaPhi > M_PI)? (deltaPhi-2*M_PI): deltaPhi;
            deltaPhi = (deltaPhi < -M_PI)? (deltaPhi+2*M_PI): deltaPhi;
            
            if(fabs(deltaPhi) < fabs(deltaPhi_min))
            {
                nearestDTTP_index = iDTTP;
                deltaPhi_min = deltaPhi;
            }
        }
        
        p_nearestDTTP_info.first = nearestDTTP_index;
        p_nearestDTTP_info.second = deltaPhi_min;
        
        return p_nearestDTTP_info;
    }
}


# endif
