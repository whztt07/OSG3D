#include "fog.h"

Fog::Fog(GraphicsView* view)
: m_pMap3D(view)
{
	m_pFog = nullptr;
	m_pFogEffect = nullptr;
}

Fog::~Fog()
{

}

void Fog::run(int iLevel)
{
	if (m_pFog)
	{
		stop();
	}
	m_pFog = new osg::Fog;
	m_pFog->setColor(osg::Vec4d(0.66f, 0.7f, 0.81f, 0.3));
	m_pFog->setStart(1.0f);
	m_pFog->setEnd(1000.0f);
	m_pFog->setMode(osg::Fog::EXP2);
	m_pFog->setDensity(iLevel / 1000.0);

	m_pFogEffect = new osgEarth::Util::FogEffect;
	m_pFogEffect->attach(m_pMap3D->getSky()->getOrCreateStateSet());
	m_pMap3D->getRoot()->getOrCreateStateSet()->setAttributeAndModes(
		m_pFog, osg::StateAttribute::ON);
}

void Fog::stop()
{
	if (m_pFog == nullptr)
	{
		return;
	}
	m_pFogEffect->detach(m_pMap3D->getSky()->getOrCreateStateSet());
	m_pMap3D->getRoot()->getOrCreateStateSet()->setAttributeAndModes(
		m_pFog, osg::StateAttribute::OFF);
}
