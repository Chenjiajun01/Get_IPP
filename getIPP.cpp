//
//  getIPP.cpp
//  Get_IPP
//
//  Created by Jiajun Chen on 16/11/2018.
//  Copyright © 2018 Jiajun Chen. All rights reserved.
//

#include "getIPP.hpp"
#include <cmath>
#include <iostream>


//计算穿刺点坐标
bool GetCoorIPP( CoorGeo grecv, double Azi, double E, float H, CoorGeo& geoIPP)
{
    if ( E < 0 )
    {
        std::cout << ("Error!!\n卫星高度角小于0!!");
        return false;
    }
    E = Dre2Rad * E;
    Azi = Dre2Rad * Azi;
    
    // 用户及穿刺点在地心的张角
    double PHI = acos( MR_WGS84 / ( MR_WGS84 + H ) * cos( E ) ) - E;
    
    // 测站处卫星天顶角
    //double rz = PI / 2 - E;
    
    // 在穿刺点处卫星天顶距 (MSLM function, H = 506.7km)
    //double Z = asin( MR_WGS84 * sin( 0.9782 * rz ) / ( MR_WGS84 + H ) );
    
    // SLM function, H = 450km
    //double Z = asin( MR_WGS84 * sin( rz ) / ( MR_WGS84 + H ) );
    //double Fz = 1 / cos(Z); //SLM factor
    
    //GPS书 P98
    //CoorGeo grecv = CoorGeo(recv);
    
    //degree to radian
    grecv.B = Dre2Rad * grecv.B;
    grecv.L = Dre2Rad * grecv.L;
    
    grecv.B = co_BToPhi(grecv.B);
    
    geoIPP.B = (grecv.B+ PHI * cos( Azi )) * Rad2Gre;
    geoIPP.L = (grecv.L + PHI * sin( Azi ) / cos(grecv.B)) * Rad2Gre;
    geoIPP.H = H;
    
    return true;
}
