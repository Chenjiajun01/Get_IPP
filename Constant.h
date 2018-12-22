//
//  Constant.h
//  DCB
//
//  Created by Jiajun Chen on 31/05/2018.
//  Copyright © 2018 Jiajun Chen. All rights reserved.
//

#ifndef Constant_h
#define Constant_h

#define IONO_FACTOR -9.52437 // pow(FL1 * FL2, 2) /(40.28 * (FL2 * FL2 - FL1 * FL1)) / 1e16;
const double    PI = 3.1415926535897932384626433832795;
const  double  LIGHT_SPEED = 299792458.0;
const  double  Dre2Rad = PI / 180.0;
const  double  Rad2Gre = 180.0 / PI;
const  double  A_wgs=6378137.000;
const  double  Shell_H = 450000.0;



//////////////////////////////////////////////////////////////////////
//            WGS-84椭球参数
//////////////////////////////////////////////////////////////////////

const double    A_WGS84        = 6378137.00;        /*WGS-84椭球参数a (m)*/
const double    B_WGS84        = 6356752.3142;        /*WGS-84椭球参数b (m)*/
const double    C_WGS84        = 6399593.6258;        /*WGS-84椭球参数c (m)*/
const double    IB_WGS84    = 1/298.257223563;    /*WGS-84椭球参数ib (m)*/
const double    EE_WGS84    = 0.006694379013;    /*WGS-84椭球参数e平方 (m)*/
const double    EEP_WGS84    = 0.00673949674227; /*WGS-84椭球参数ep 平方 (m)*/
//const double    MR_WGS84    = 6371000.78999407;    /*WGS-84椭球平均半径 (m)*/
const double    MR_WGS84    = 6371317.00;    /*WGS-84椭球平均半径 (m)*/
//////////////////////////////////////////////////////////////////////
//            地球基本几何参数
//////////////////////////////////////////////////////////////////////
const double    A            = 6378164.0;        //长半径
const double    B            = 6356779.0;        //短半径
const double    MR            = 6371027.68505982;    //地球平均半径


#endif /* Constant_h */
