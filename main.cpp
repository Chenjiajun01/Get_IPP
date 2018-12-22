//
//  main.cpp
//  Get_IPP
//
//  Created by Jiajun Chen on 16/11/2018.
//  Copyright © 2018 Jiajun Chen. All rights reserved.
//

#include <iostream>
#include <string>
#include "getIPP.hpp"

using namespace std;


int main(int argc, const char * argv[]) {
    
    if(argc<6)
    {
        cout<<"Usage:   Get_IPP L B H AZIMUTH INCIDENCE"<<endl;
        cout<<"Example:  Get_IPP " << endl;
        
        return 1;
    }
    string temp = "";
    CoorGeo grecv;
    temp = argv[1];
    grecv.L = atof(temp.c_str());
    temp = argv[2];
    grecv.B = atof(temp.c_str());
    temp = argv[3];
    double H = atof(temp.c_str());
    temp = argv[4];
    double Azi = atof(temp.c_str());
    temp = argv[5];
    double Elev = 90-atof(temp.c_str());
    
    CoorGeo geoIPP;
    
    GetCoorIPP(grecv, Azi, Elev, H, geoIPP);
    cout << geoIPP.L << "  " << geoIPP.B << endl;
    return 0;
}
