#include <cmath>
#include "Coordinate.h"
#include "Constant.h"
#include <cstring>

//cartesian coordinate
CoorCar::CoorCar()
{
	X = 0.0;
	Y = 0.0;
	Z = 0.0;
}

//covert geodetic to cartesian
CoorCar::CoorCar(double b, double l, double h)
{
	CoorGeo cg;
	cg.B = b;
	cg.L = l;
	cg.H = h;
	CoorCar cr = co_convGeoToCar(cg);
	X = cr.X;
	Y = cr.Y;
	Z = cr.Z;
}

//CoorGeo初始化
CoorGeo::CoorGeo()
{
	B = 0.0;
	L = 0.0;
	H = 0.0;
}

//重载CoorTiCar的构造函数，用于用角度为大地坐标赋值
//////////////////////////////////////////////////////////////////////////
/*
CoorGeo::CoorGeo(double bbJiao,double llJiao,double hh )
{
	B = bbJiao * PI / 180;
	L = llJiao * PI / 180;
	H = hh;
}*/
//covert cartesian to geodetic
CoorGeo::CoorGeo(CoorCar coorCar)
{
	CoorGeo cr = co_convCarToGeo(coorCar);
	B = cr.B;
	L = cr.L;
	H = cr.H;
}

//////////////////////////////////////////////////////////////////////////
//
CoorGeo co_convCarToGeo(CoorCar coorCar)
{
	CoorGeo coorGeo;
	//////////////////////////////大地经度///////////////////////////////////////
	//coorGeo.L = RadtoAngle(atan2(coorCar.Y, coorCar.X));  
	coorGeo.L = atan2(coorCar.Y, coorCar.X); 
	/////////////////////////////大地纬度///////////////////////////////////////
	double B1 = atan2(coorCar.Z, sqrt(pow(coorCar.X, 2) + pow(coorCar.Y, 2)));  //大地纬度的初始值
	double B2; //用于存放大地纬度的新值
	double W;  //辅助变量，用于存放中间量
	double NN; //卯酉圈曲率半径

	for (;;)    //大地纬度的迭代求解，直至精度为0.000001度
	{
		W	= sqrt(1 - EE_WGS84 * pow(sin(B1 ), 2));	                                               //《大地测量学》P99，式4-9		
		NN	= A_WGS84 / W;                                                                             //《大地测量学》P107，式4-64
		B2	= atan2(coorCar.Z + NN * EE_WGS84 * sin(B1), sqrt(pow(coorCar.X, 2) + pow(coorCar.Y, 2))); //《大地测量学》P103，式4-32
		if(fabs(B2 - B1) < 1e-8) // 0.000001°
		{
			//coorGeo.B = RadtoAngle(B2);
			coorGeo.B = B2;
			break;
		}
		else
		{
			B1 = B2;
		}
	}
	///////////////////////////////大地高///////////////////////////////////////
//	W	= sqrt(1 - EE_WGS84 * pow(sin(AngletoRad(coorGeo.B)), 2));//根据计算得到的大地纬度重新计算中间变量
	W	= sqrt(1 - EE_WGS84 * pow(sin(coorGeo.B), 2));
	NN	= A_WGS84 / W;	
	coorGeo.H = coorCar.Z / sin(coorGeo.B) - NN * (1 - EE_WGS84); 
//	coorGeo.H = coorCar.Z / sin(AngletoRad(coorGeo.B)) - NN * (1 - EE_WGS84);//《大地测量学》P103，式4-34

	return coorGeo;
}

//大地坐标转空间直角坐标
CoorCar co_convGeoToCar(CoorGeo coorGeo)
{
	CoorCar coorCar;
	double N = A_WGS84 / sqrt (1 - EE_WGS84 * sin(coorGeo.B) * sin(coorGeo.B));
	coorCar.X = (N + coorGeo.H) * cos(coorGeo.B) * cos(coorGeo.L);
	coorCar.Y = (N + coorGeo.H) * cos(coorGeo.B) * sin(coorGeo.L);
	coorCar.Z = (N * (1 - EE_WGS84) + coorGeo.H) * sin(coorGeo.B);
	return coorCar;
}


//////////////////////////////////////////////////////////////////////////
//地心系转站心系
//参数：coorCar表示待转换的地心直角坐标；centCoor表示中心点（站心点）在地心系下的空间直角坐标
//////////////////////////////////////////////////////////////////////////
CoorCar	co_earthToTopo(CoorCar coorCar, CoorCar centCoor)
{
	double matrixT[3][3];  //存放旋转矩阵T
	double *matrixTemp = new double[3];    //存放计算的中间结果

	CoorGeo	geoTemp;       //存放站心点的大地坐标
	CoorCar topoTemp;      //存放返回值

	geoTemp = co_convCarToGeo(centCoor);   //将站心点在站心系下的直角坐标转换为在站心系下的大地坐标，用于求旋转矩阵

	matrixT[0][0] = -sin(geoTemp.B) * cos(geoTemp.L);				 //旋转矩阵
	matrixT[1][0] =	-sin(geoTemp.L);                                 //《GPS测量与数据处理》P165，式8-11
	matrixT[2][0] =	 cos(geoTemp.B) * cos(geoTemp.L);
	matrixT[0][1] = -sin(geoTemp.B) * sin(geoTemp.L);
	matrixT[1][1] =	 cos(geoTemp.L);
	matrixT[2][1] =	 cos(geoTemp.B) * sin(geoTemp.L);
	matrixT[0][2] =  cos(geoTemp.B);
	matrixT[1][2] =	 0.0;
	matrixT[2][2] =	 sin(geoTemp.B);

	matrixTemp[0] = coorCar.X - centCoor.X;      //矩阵减法
	matrixTemp[1] = coorCar.Y - centCoor.Y;
	matrixTemp[2] = coorCar.Z - centCoor.Z;

	topoTemp.X = matrixT[0][0] * matrixTemp[0] + matrixT[0][1] * matrixTemp[1] + matrixT[0][2] * matrixTemp[2];  //矩阵乘法
	topoTemp.Y = matrixT[1][0] * matrixTemp[0] + matrixT[1][1] * matrixTemp[1] + matrixT[1][2] * matrixTemp[2];  //《GPS测量与数据处理》P164，式8-10
	topoTemp.Z = matrixT[2][0] * matrixTemp[0] + matrixT[2][1] * matrixTemp[1] + matrixT[2][2] * matrixTemp[2];

	delete [] matrixTemp;
	matrixTemp = NULL;
	return(topoTemp);
}

//弧度转换成角度
double RadtoAngle(double radian)
{
	double angle = radian * 180 / PI;
	return angle;
}
//角度转换成弧度
double AngletoRad(double angle)
{
	double radian = angle * PI / 180;
	return radian;
}

//地心纬度转大地纬度
double co_phiToB(double phi)
{
	return atan(pow((A_WGS84 / B_WGS84), 2) * tan(phi)) ;
}

//大地纬度转地心纬度
double co_BToPhi(double B)
{
	return atan(pow((B_WGS84 / A_WGS84), 2) * tan(B));
}


CoorDirec::CoorDirec()
{
	elevation = 0.0;
	azimuth = 0.0;
}
CoorDirec::CoorDirec(CoorCar sat, CoorCar recv)
{
	CoorDirec cdi = co_CarToDirec(sat, recv);
	elevation = cdi.elevation;
	azimuth = cdi.azimuth;
}
//calculate elevation and  azimuth from XYZ
CoorDirec co_CarToDirec(CoorCar recv, CoorCar sat)
{
	CoorDirec direc;
	//elevation
	double elev;
	CoorCar topo = co_earthToTopo(sat, recv);
	double ds = sqrt(topo.X * topo.X + topo.Y * topo.Y);
//	return (atan((topo.Z / ds) * 180 / PI));
	elev = (atan(topo.Z / ds));

	//azimuth
	double X, Y, Azi;

	X = recv.X;
	Y = recv.Y;

	if ( Y > 0 )
	{
		if ( X > 0 )    // 第一象限
		{
			Azi = atan( fabs( Y / X ) );
		}
		else if ( X < 0 )       // 第二象限
		{
			Azi =  PI/2 + atan( fabs( X / Y ) );
		}
		else // X == 0
		{
			Azi =  PI / 2;
		}
	}
	else if ( Y < 0 )
	{
		if ( X < 0 )    // 第三象限
		{
			Azi =  PI + atan( fabs( Y / X ) );
		}
		else if ( X > 0 )       // 第四象限
		{
			Azi =  1.5 * PI + atan( fabs( X / Y ) );
		}
		else
		{
			Azi =  1.5 * PI;
		}
	}
	else // Y == 0
	{
		if ( X > 0 )
		{
			Azi =  0;
		}
		else if ( X < 0 )
		{
			Azi =  PI;
		}
		else
		{
			Azi = 0;
		}
	}
	direc.azimuth = Azi;
	direc.elevation = elev;
	return direc;
}

//求中点
CoorCar GetMidpoint(CoorCar P1, CoorCar P2)
{
	CoorCar midP;
	midP.X = (P1.X + P2.X) / 2;
	midP.Y = (P1.Y + P2.Y) / 2;
	midP.Z = (P1.Z + P2.Z) / 2;
	return midP;
}
