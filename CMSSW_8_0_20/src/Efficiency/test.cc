# include <iostream>
# include <map>

# include "Common.h"


void test(std::map <int, std::map <int, double> > *myMap)
{
    (*myMap)[0][1] = 2.0;
    
    std::cout << "test " << (*myMap)[0][1] << "\n";
}


int main()
{
    /*std::map <int, std::map <int, double> > myMap;
    
    myMap[0][1] = 2.4;
    
    //std::cout << ((myMap.find(0)->second).find(1) == (myMap.find(0)->second).end()) << "\n";
    
    std::cout << "main " << myMap[0][1] << "\n";
    
    test(&myMap);
    
    std::cout << "main " << myMap[0][1] << "\n";
    
    std::cout << (1.0 == 1) << "\n";
    
    //std::cout << (false > 0.5) << "\n";*/
    
    
    /*int mask = 0;
    
    mask |= (1 << 2);
    printf("mask %d \n", mask);
    
    mask |= (1 << 1);
    printf("mask %d \n", mask);
    
    return 0;*/
    
    
    double eta = 0.125;
    int iEta = Common::etaToIeta(eta);
    int subIeta = Common::etaToSubIeta(eta, 2);
    printf("eta %f, iEta %d/%d \n", eta, iEta, subIeta);
}
