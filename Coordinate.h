#ifndef COORDINATE_H
#define COORDINATE_H
#include "Constant.h"

class AngleDMS      //角度，度分秒形式
{
public:
	short int degree;     //度
	short int minute;     //分
	double second;        //秒
};



//笛卡尔坐标，形如(X,Y,Z)，可用于表示空间直角坐标、站心坐标、地心坐标等
class CoorCar
{
public:
	double X;
	double Y;
	double Z;

	CoorCar();
	CoorCar(double b, double l, double h);// 大地坐标转空间直角坐标
	//CoorCar(Angle bb, Angle ll,double hh);                 //重载构造函数，用于和大地坐标之间的转换
	//CoorCar(double rr, Angle aa, Angle eaea);              //重载构造函数，用于和极坐标之间的转换	
	//void fromBLH(double bbJiao/*大地纬度（角度形式）*/, double llJjiao/*大地经度（角度形式）*/, double hh);  //从大地坐标转换到空间直角坐标
};
class CoorGeo    //Geodetic Coordinate
{
public:
//	AngleDMS b;
//	AngleDMS l;
	double B;
	double L;
	double H;
	CoorGeo();
//	CoorGeo(double b,double l,double h );//重载构造函数，用于角度赋值
	CoorGeo(CoorCar coorCar);       //convert Car to Geo
//	CoorGeo(CoorTiCar coorTiCar);   //重载构造函数，用于和CoorTiCar类型之间的转换
};
class CoorPol   //Polar Coordinat，极坐标系坐标，形如（r,a,ea）
{
public:
	/*CoorPol(double rr = 0.0, Angle aa = 0.0, Angle eaea = 0.0)
	{
		r = rr;
		a = aa;
		ea = eaea;
	}*/
	//CoorPol(double rr, double aaJiao, double eaeaJiao);//重载构造函数，用于角度赋值
	//CoorPol(CoorCar coorCar);          //重载构造函数，用于和空间直角坐标之间的转换
	//CoorPol(CoorTiCar coorTiCar);      //重载构造函数，用于和CoorTiCar类型之间的转换

	double r;      //距离
	//Angle a;       //方位角
	//Angle ea;      //高度角
};

class CoorTiCar : public CoorCar   //笛卡尔坐标和钟差组成的四维信息
{
public:
	
	//CoorTiCar(double clockBias, CoorCar coorCar);

	double dc;    //钟差
};

class CoorDirec
{
public:
	double azimuth;
	double elevation;

	CoorDirec();
	CoorDirec(CoorCar recv_Car, CoorCar sat_Car);
};
//弧度转换成角度
double RadtoAngle(double radian);
//角度转换成弧度
double AngletoRad(double angle);


CoorGeo co_convCarToGeo(CoorCar coorCar);   //空间直角坐标转大地坐标

//convert geo to car
CoorCar co_convGeoToCar(CoorGeo coorGeo);

// 地心系转站心系
CoorCar	co_earthToTopo(CoorCar coorCar, CoorCar centCoor);	

//地心纬度转大地纬度
double co_phiToB(double phi);

//大地纬度转地心纬度
double co_BToPhi(double B);

CoorDirec co_CarToDirec(CoorCar coorCar1, CoorCar coorCar2); //calculate azimuth and elevation from coorCar

//求中点
CoorCar GetMidpoint(CoorCar P1, CoorCar P2);



#endif