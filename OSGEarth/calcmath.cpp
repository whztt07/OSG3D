#include "calcmath.h"

CalcMath::CalcMath()
{

}

CalcMath::~CalcMath()
{

}

double CalcMath::calcArea(std::vector<osg::Vec3d> points)
{
	double dTotalArea = 0.0;
	int iCount = points.size();
	if (iCount > 2)
	{
		double dLowX = 0.0;
		double dLowY = 0.0;
		double dMiddleX = 0.0;
		double dMiddleY = 0.0;
		double dHighX = 0.0;
		double dHighY = 0.0;
		double AM = 0.0;
		double BM = 0.0;
		double CM = 0.0;
		double AL = 0.0;
		double BL = 0.0;
		double CL = 0.0;
		double AH = 0.0;
		double BH = 0.0;
		double CH = 0.0;
		//Coefficient系数
		double dCoefficientL = 0.0;
		double dCoefficientH = 0.0;
		//tangent切线
		double dALtangent = 0.0;
		double dBLtangent = 0.0;
		double dCLtangent = 0.0;
		double dAHtangent = 0.0;
		double dBHtangent = 0.0;
		double dCHtangent = 0.0;
		//NormalLine法线     
		double dANormalLine = 0.0;
		double dBNormalLine = 0.0;
		double dCNormalLine = 0.0;
		//Orientation  Value方向值  
		double dOrientationValue = 0.0;
		//余弦角
		double dAngleCos = 0.0;

		double dSum1 = 0.0;
		double dSum2 = 0.0;
		int iCount2 = 0;
		int iCount1 = 0;

		double dSum = 0.0;

		for (int i = 0; i < iCount; i++)
		{
			if (i == 0)
			{
				//换算成弧度;
				dLowX = osg::DegreesToRadians(points.at(iCount - 1).x());
				dLowY = osg::DegreesToRadians(points.at(iCount - 1).y());
				dMiddleX = osg::DegreesToRadians(points.at(0).x());
				dMiddleY = osg::DegreesToRadians(points.at(0).y());
				dHighX = osg::DegreesToRadians(points.at(1).x());
				dHighY = osg::DegreesToRadians(points.at(1).y());
			}
			else if (i == iCount - 1)
			{
				dLowX = osg::DegreesToRadians(points.at(iCount - 2).x());
				dLowY = osg::DegreesToRadians(points.at(iCount - 2).y());
				dMiddleX = osg::DegreesToRadians(points.at(iCount - 1).x());
				dMiddleY = osg::DegreesToRadians(points.at(iCount - 1).y());
				dHighX = osg::DegreesToRadians(points.at(0).x());
				dHighY = osg::DegreesToRadians(points.at(0).y());
			}
			else
			{
				dLowX = osg::DegreesToRadians(points.at(i - 1).x());
				dLowY = osg::DegreesToRadians(points.at(i - 1).y());
				dMiddleX = osg::DegreesToRadians(points.at(i).x());
				dMiddleY = osg::DegreesToRadians(points.at(i).y());
				dHighX = osg::DegreesToRadians(points.at(i + 1).x());
				dHighY = osg::DegreesToRadians(points.at(i + 1).y());
			}
			AM = cos(dMiddleY) * cos(dMiddleX);
			BM = cos(dMiddleY) * sin(dMiddleX);
			CM = sin(dMiddleY);
			AL = cos(dLowY) * cos(dLowX);
			BL = cos(dLowY) * sin(dLowX);
			CL = sin(dLowY);
			AH = cos(dHighY) * cos(dHighX);
			BH = cos(dHighY) * sin(dHighX);
			CH = sin(dHighY);

			dCoefficientL = (AM*AM + BM*BM + CM*CM) / (AM*AL + BM*BL + CM*CL);
			dCoefficientH = (AM*AM + BM*BM + CM*CM) / (AM*AH + BM*BH + CM*CH);

			dALtangent = dCoefficientL * AL - AM;
			dBLtangent = dCoefficientL * BL - BM;
			dCLtangent = dCoefficientL * CL - CM;
			dAHtangent = dCoefficientH * AH - AM;
			dBHtangent = dCoefficientH * BH - BM;
			dCHtangent = dCoefficientH * CH - CM;

			dAngleCos = (dAHtangent * dALtangent + dBHtangent * dBLtangent + dCHtangent * dCLtangent) /
				(sqrt(dAHtangent * dAHtangent + dBHtangent * dBHtangent + dCHtangent * dCHtangent) *
				sqrt(dALtangent * dALtangent + dBLtangent * dBLtangent + dCLtangent * dCLtangent));

			dAngleCos = acos(dAngleCos);

			dANormalLine = dBHtangent * dCLtangent - dCHtangent * dBLtangent;
			dBNormalLine = 0 - (dAHtangent * dCLtangent - dCHtangent * dALtangent);
			dCNormalLine = dAHtangent * dBLtangent - dBHtangent * dALtangent;

			if (AM != 0)
			{
				dOrientationValue = dANormalLine / AM;
			}
			else if (BM != 0)
			{
				dOrientationValue = dBNormalLine / BM;
			}
			else
			{
				dOrientationValue = dCNormalLine / CM;
			}
			if (dOrientationValue > 0)
			{
				dSum1 += dAngleCos;
				iCount1++;
			}
			else
			{
				dSum2 += dAngleCos;
				iCount2++;
			}
		}
		if (dSum1 > dSum2)
		{
			dSum = dSum1 + (2 * osg::PI*iCount2 - dSum2);
		}
		else
		{
			dSum = (2 * osg::PI*iCount1 - dSum1) + dSum2;
		}

		dTotalArea = (dSum - (iCount - 2)*osg::PI)* osg::WGS_84_RADIUS_EQUATOR *
			osg::WGS_84_RADIUS_EQUATOR;
	}
	return dTotalArea;
}
