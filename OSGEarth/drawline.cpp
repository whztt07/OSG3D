#include "drawline.h"

DrawLine::DrawLine(GraphicsView* view)
: HandleAdapter(view)
{
	m_pFeature = NULL;
	m_pFeatureNode = NULL;
	m_pStippleFeature = NULL;
	m_pStippleFeatureNode = NULL;

	m_vecPoint.clear();

	// init style
	m_lineStyle.getOrCreate<osgEarth::Symbology::LineSymbol>()
		->stroke()->color() = osgEarth::Symbology::Color::Yellow;
	m_lineStyle.getOrCreate<osgEarth::Symbology::LineSymbol>()
		->stroke()->width() = 2.0;
	m_lineStyle.getOrCreate<osgEarth::Symbology::LineSymbol>()
		->tessellation() = 20.0;
	m_lineStyle.getOrCreate<osgEarth::Symbology::AltitudeSymbol>()
		->clamping() = osgEarth::Symbology::AltitudeSymbol::CLAMP_TO_TERRAIN;
	m_lineStyle.getOrCreate<osgEarth::Symbology::AltitudeSymbol>()
		->technique() = osgEarth::Symbology::AltitudeSymbol::TECHNIQUE_MAP;
	m_lineStyle.getOrCreate<osgEarth::Symbology::AltitudeSymbol>()
		->verticalOffset() = 0.1;

	m_stippleLineStyle.getOrCreate<osgEarth::Symbology::LineSymbol>()
		->stroke()->color() = osgEarth::Symbology::Color::Red;
	m_stippleLineStyle.getOrCreate<osgEarth::Symbology::LineSymbol>()
		->stroke()->width() = 2.0;
	m_stippleLineStyle.getOrCreate<osgEarth::Symbology::LineSymbol>()
		->tessellation() = 20.0;
	m_stippleLineStyle.getOrCreate<osgEarth::Symbology::AltitudeSymbol>()
		->clamping() = osgEarth::Symbology::AltitudeSymbol::CLAMP_TO_TERRAIN;
	m_stippleLineStyle.getOrCreate<osgEarth::Symbology::AltitudeSymbol>()
		->technique() = osgEarth::Symbology::AltitudeSymbol::TECHNIQUE_MAP;
	m_stippleLineStyle.getOrCreate<osgEarth::Symbology::AltitudeSymbol>()
		->verticalOffset() = 0.1;
	m_stippleLineStyle.getOrCreate<osgEarth::Symbology::LineSymbol>()
		->stroke()->stipple() = 255;
}

DrawLine::~DrawLine()
{

}

void DrawLine::slotPicked(osg::Vec3d pos)
{
	m_vecPoint.push_back(pos);
	if (m_vecPoint.size() <= 1)
	{
		return;
	}

	if (m_pFeatureNode == NULL)
	{
		m_pFeature = new osgEarth::Features::Feature(
			new osgEarth::Annotation::LineString,
			m_pMap3D->getMapNode()->getMapSRS(), m_lineStyle);
		m_pFeatureNode = new osgEarth::Annotation::FeatureNode(
			m_pMap3D->getMapNode(), m_pFeature);

		m_pLayerGroup->addChild(m_pFeatureNode);
	}

	m_pFeature->getGeometry()->clear();
	m_pFeatureNode->setStyle(m_lineStyle);
	for (auto& n : m_vecPoint)
	{
		m_pFeature->getGeometry()->push_back(n);
	}

	m_pFeatureNode->init();

	if (m_pStippleFeatureNode != NULL)
	{
		m_pStippleFeature->getGeometry()->clear();
	}

	osg::Vec3d center = getWorldCoord(pos);
	osg::ref_ptr<osg::ShapeDrawable> shape = new osg::ShapeDrawable(
		new osg::Cylinder(center, 5, 10000));

	shape->setColor(osg::Vec4d(0, 0, 1, 1));

	osg::ref_ptr<osg::Geode> pGeode = new osg::Geode;
	pGeode->addDrawable(shape);
	m_pLayerGroup->addChild(pGeode);
// 	const osg::Vec4 vColor(0, 0, 1, 1);
// 
// 	osg::ref_ptr<osg::MatrixTransform> pMatrixTransform = new osg::MatrixTransform;
// 	osg::Matrixd matrix;
// 	osg::ref_ptr<osg::Node> pNode;
// 
// 	//线参数
// 	const osg::Vec3d &pt1 = m_vecPoint.at(0);
// 	const osg::Vec3d &pt2 = m_vecPoint.at(1);
// 
// 	osg::Vec3d ptTemp1, ptTemp2;
// 	ptTemp1 = getWorldCoord(pt1);
// 	ptTemp2 = getWorldCoord(pt2);
// 
// 	//管线的长度
// 	osg::Vec3d vecLen = ptTemp2 - ptTemp1;
// 	const double dblLength = vecLen.normalize();
// 
// 	//缩放
// 	matrix.postMultScale(osg::Vec3d(1, 1, dblLength));
// 
// 	//旋转
// // 		const osg::Quat qtRotation(osg::Vec3d(0.0, 0.0, 1.0), vecLen);
// // 		matrix.postMultRotate(qtRotation);
// 
// 	//平移
// 	const osg::Vec3d ptCenter = (ptTemp1 + ptTemp2) * 0.5;
// 	matrix.postMultTranslate(ptCenter);
// 
// 	//osgUtil::CommonModelCreater::instance()->createStandardModel(osgUtil::CommonModelCreater::CYLINDER, eCoverType, m_bImageStretched, vColor, pNode);
// 
// 	osg::Vec3Array* pArray = new osg::Vec3Array;
// 	for (auto coord : m_vecPoint)
// 	{
// 		pArray->push_back(coord);
// 	}
// 	pNode = createPrism(pArray, 1892, true, vColor);
// 
// 	pMatrixTransform->getOrCreateStateSet()->getOrCreateUniform("btexture", osg::Uniform::BOOL)->set(false);
// 
// 	if (pNode)
// 	{
// 		pMatrixTransform->addChild(pNode);
// 	}
// 	m_pLayerGroup->addChild(pMatrixTransform);
}

void DrawLine::slotMoveing(osg::Vec3d pos)
{
	if (m_vecPoint.size() <= 0)
	{
		return;
	}
	if (m_pStippleFeatureNode == NULL)
	{
		m_pStippleFeature = new osgEarth::Features::Feature(
			new osgEarth::Annotation::LineString,
			m_pMap3D->getMapNode()->getMapSRS(), m_lineStyle);
		m_pStippleFeatureNode = new osgEarth::Annotation::FeatureNode(
			m_pMap3D->getMapNode(), m_pStippleFeature);

		m_pLayerGroup->addChild(m_pStippleFeatureNode);
	}

	m_pStippleFeature->getGeometry()->clear();
	m_pStippleFeatureNode->setStyle(m_stippleLineStyle);
	m_pStippleFeature->getGeometry()->push_back(m_vecPoint[m_vecPoint.size() - 1]);
	m_pStippleFeature->getGeometry()->push_back(pos);

	m_pStippleFeatureNode->init();
}

void DrawLine::slotRightHandle()
{
	m_vecPoint.clear();
	if (m_pStippleFeatureNode != NULL)
	{
		m_pStippleFeature->getGeometry()->clear();
	}
}

osg::Node* DrawLine::createPrism(const osg::Vec3Array *pVertex, float fHeight,
	bool bTexStretched, const osg::Vec4 &vColor)
{
	osg::ref_ptr<osg::Geode> pGeode = new osg::Geode;

	//颜色
	osg::ref_ptr<osg::Vec4Array> pColorArray = new osg::Vec4Array;
	pColorArray->push_back(vColor);

	const float fHalfHeight = fHeight * 0.5f;

	std::vector<osg::Vec3> vecVertex;

	//创建侧面
	{
		osg::ref_ptr<osg::Geometry> pGeometry = new osg::Geometry;
		osg::ref_ptr<osg::Vec3Array> pVertexArray = new osg::Vec3Array;
		osg::ref_ptr<osg::Vec3Array> pNormalArray = new osg::Vec3Array;
		osg::ref_ptr<osg::Vec2Array> pTexCoordArray = new osg::Vec2Array;

		unsigned int nSize = pVertex->size();
		for (unsigned int i = 0u; i < nSize; i++)
		{
			vecVertex.push_back(osg::Vec3((*pVertex)[i][0], (*pVertex)[i][1], -fHalfHeight));
		}
		for (unsigned int i = 0u; i < nSize; i++)
		{
			vecVertex.push_back(osg::Vec3((*pVertex)[i][0], (*pVertex)[i][1], fHalfHeight));
		}

		for (unsigned int i = 0u; i < nSize - 1u; i++)
		{
			osg::Vec3 v1 = vecVertex[i + 1u] - vecVertex[i];
			osg::Vec3 v2 = vecVertex[i + nSize] - vecVertex[i];
			osg::Vec3 vN = v2 ^ v1;
			vN.normalize();
			pNormalArray->push_back(vN);
		}

		nSize--;
		float fTex = 0.0f;
		for (unsigned int i = 0; i < nSize; i++)
		{
			osg::Vec3 vTemp = vecVertex[i + 1] - vecVertex[i];
			const float fTemp = vTemp.length();

			pVertexArray->push_back(vecVertex[i]);
			pTexCoordArray->push_back(osg::Vec2(fHeight, fTex));

			pVertexArray->push_back(vecVertex[i + 1]);
			pTexCoordArray->push_back(osg::Vec2(fHeight, fTex + fTemp));

			pVertexArray->push_back(vecVertex[nSize + 2 + i]);
			pTexCoordArray->push_back(osg::Vec2(0.0f, fTex + fTemp));

			pVertexArray->push_back(vecVertex[nSize + 1 + i]);
			pTexCoordArray->push_back(osg::Vec2(0.0f, fTex));

			fTex += fTemp;
		}

		pGeometry->setVertexArray(pVertexArray.get());
		pGeometry->setNormalArray(pNormalArray.get()); 
		pGeometry->setNormalBinding(osg::Geometry::BIND_PER_PRIMITIVE_SET);
		pGeometry->setColorArray(pColorArray.get());
		pGeometry->setColorBinding(osg::Geometry::BIND_OVERALL);
		pGeometry->setTexCoordArray(0, pTexCoordArray.get());
		pGeometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, pVertexArray->size()));

		pGeode->addDrawable(pGeometry.get());
	}

	osg::ref_ptr<osg::Vec2Array> pTexCoordArray = createTexCoordByVertex(pVertex, bTexStretched);

	osg::ref_ptr<osgUtil::Tessellator>  pTessellator = new osgUtil::Tessellator;

	osg::ref_ptr<osg::Geometry> pGeometry = new osg::Geometry;
	osg::ref_ptr<osg::Vec3Array> pVertexArray = new osg::Vec3Array;
	osg::ref_ptr<osg::Vec3Array> pNormalArray = new osg::Vec3Array;

	pVertexArray->insert(pVertexArray->end(), vecVertex.begin() + pVertex->size(), vecVertex.end());
	pNormalArray->push_back(osg::Vec3(0.0f, 0.0f, 1.0f));

	pGeometry->setVertexArray(pVertexArray.get());
	pGeometry->setNormalArray(pNormalArray.get());
	pGeometry->setNormalBinding(osg::Geometry::BIND_OVERALL);
	pGeometry->setColorArray(pColorArray.get());
	pGeometry->setColorBinding(osg::Geometry::BIND_OVERALL);
	if (!pTexCoordArray->empty())
	{
		pGeometry->setTexCoordArray(0, pTexCoordArray.get());
	}
	pGeometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::POLYGON, 0, pVertex->size()));
	pTessellator->retessellatePolygons(*pGeometry);
	pGeode->addDrawable(pGeometry.get());

	pGeode->getOrCreateStateSet()->setAttributeAndModes(new osg::CullFace(osg::CullFace::FRONT_AND_BACK), osg::StateAttribute::OFF);

	return pGeode.release();
}

osg::Vec2Array* DrawLine::createTexCoordByVertex(const osg::Vec3Array *pVertexArray, bool bTexStretched)
{
    if(pVertexArray == NULL || pVertexArray->size() == 0)
    {
        return NULL;
    }

    osg::BoundingBox bb;
    const unsigned int nSize = pVertexArray->size();
    for(unsigned int i = 0; i < nSize; i++)
    {
        bb.expandBy((*pVertexArray)[i]);
    }

    osg::ref_ptr<osg::Vec2Array> pTexCoordArray = new osg::Vec2Array;
    const float w = bb.xMax() - bb.xMin();
    const float h = bb.yMax() - bb.yMin();
    for(unsigned int i = 0; i < nSize; i++)
    {
        if(bTexStretched)
        {
            pTexCoordArray->push_back(osg::Vec2(((*pVertexArray)[i]._v[0] - bb.xMin()) / w, ((*pVertexArray)[i]._v[1] - bb.yMin()) / h));
        }
        else
        {
            pTexCoordArray->push_back(osg::Vec2((*pVertexArray)[i]._v[0] - bb.xMin(), (*pVertexArray)[i]._v[1] - bb.yMin()));
        }
    }

    return pTexCoordArray.release();
}

osg::Vec3d DrawLine::getWorldCoord(osg::Vec3d pos)
{
	osg::Vec3d world;
	m_pMap3D->getSRS()->getEllipsoid()->convertLatLongHeightToXYZ(
		osg::DegreesToRadians(pos.y()),
		osg::DegreesToRadians(pos.x()),
		pos.z(), world.x(), world.y(), world.z());

	return world;
}
