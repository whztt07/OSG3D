/* ------------------------------------------------------------
** 版权: (C) 2015 北京天耀宏图科技有限公司.
         http://www.greatmap.com.cn
** 名称: MyOSGEarth
** 作者: lugd 
** 日期: 2015/04/21 
** 描述: osgEarth头文件及lib库
** ----------------------------------------------------------*/

#ifndef MYOSGEARTH
#define MYOSGEARTH

#include <osgEarth/MapNode>
#include <osgEarth/ModelLayer>
#include <osgEarth/GeoMath>
#include <osgEarth/Viewpoint>
#include <osgEarth/ImageLayer>
#include <osgEarth/DateTime>

#include <osgEarthUtil/ObjectLocator>
#include <osgEarthUtil/Shadowing>
#include <osgEarthUtil/EarthManipulator>
#include <osgEarthUtil/Controls>
#include <osgEarthUtil/Sky>
#include <osgEarthUtil/RadialLineOfSight>
#include <osgEarthUtil/GeodeticGraticule>
#include <osgEarthUtil/AutoClipPlaneHandler>
#include <osgEarthUtil/LODBlending>
#include <osgEarthUtil/Fog>

#include <osgEarthDrivers/feature_ogr/OGRFeatureOptions>
#include <osgEarthDrivers/agglite/AGGLiteOptions>
#include <osgEarthDrivers/tms/TMSOptions>

#include <osgEarthSymbology/TextSymbol>
#include <osgEarthSymbology/ExtrusionSymbol>
#include <osgEarthSymbology/IconSymbol>
#include <osgEarthSymbology/Geometry>
#include <osgEarthSymbology/ModelSymbol>
#include <osgEarthSymbology/Style>

#include <osgEarthAnnotation/FeatureNode>
#include <osgEarthAnnotation/CircleNode>
#include <osgEarthAnnotation/ImageOverlay>
#include <osgEarthAnnotation/FeatureEditing>
#include <osgEarthAnnotation/PlaceNode>
#include <osgEarthAnnotation/HighlightDecoration>
#include <osgEarthAnnotation/AnnotationEditing>
#include <osgEarthAnnotation/LabelNode>

#include <osgEarthFeatures/FeatureModelGraph>
#include <osgEarthDrivers/gdal/GDALOptions>

#ifdef _DEBUG
#pragma comment(lib,"osgEarthd.lib")
#pragma comment(lib,"osgEarthUtild.lib")
#pragma comment(lib,"osgEarthSymbologyd.lib")
#pragma comment(lib,"osgEarthAnnotationd.lib")
#pragma comment(lib,"osgEarthFeaturesd.lib")
#else
#pragma comment(lib,"osgEarth.lib")
#pragma comment(lib,"osgEarthUtil.lib")
#pragma comment(lib,"osgEarthSymbology.lib")
#pragma comment(lib,"osgEarthAnnotation.lib")
#pragma comment(lib,"osgEarthFeatures.lib")
#endif //_debug

#endif //MYOSGEARTH