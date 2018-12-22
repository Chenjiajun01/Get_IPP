//
//  getIPP.hpp
//  Get_IPP
//
//  Created by Jiajun Chen on 16/11/2018.
//  Copyright © 2018 Jiajun Chen. All rights reserved.
//

#ifndef getIPP_hpp
#define getIPP_hpp

#include <stdio.h>
#include "Coordinate.h"

//calculate IPP geoid coordinate with ground receiver and direction
bool GetCoorIPP(CoorGeo recv, double Azi, double E, float H, CoorGeo& geoIPP);


#endif /* getIPP_hpp */
