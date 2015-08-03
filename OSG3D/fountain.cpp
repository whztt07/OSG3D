#include "fountain.h"

Fountain::Fountain()
{
	m_dParticlesNum = 1000;
	m_dParticlesSize = 0.1;
	m_dParticlesSpeed = 100;
}

Fountain::~Fountain()
{

}

void Fountain::setFountainParas(double num /*= 1000*/, double size /*= 0.2*/, double speed /*= 100*/)
{
	m_dParticlesNum = num;
	m_dParticlesSize = size;
	m_dParticlesSpeed = speed;
}

osg::ref_ptr<osg::Node> Fountain::createFountain(osg::Vec3d postion, osg::Group* parent)
{
	// 设置粒子模板的参数，包括生命周期、颜色、透明度、半径、重量等
	osgParticle::Particle pParticle;
	pParticle.setLifeTime(3);
	pParticle.setColorRange(osgParticle::rangev4(
		osg::Vec4(0.7, 1.0, 1.0, 1.0),
		osg::Vec4(0.8, 1.0, 1.0, 0.0)));
	pParticle.setSizeRange(osgParticle::rangef(0.1f, 0.1f));
	pParticle.setAlphaRange(osgParticle::rangef(1.0f, 0.5f));
	pParticle.setRadius(m_dParticlesSize);
	pParticle.setMass(0.05);

	osg::ref_ptr<osgParticle::ParticleSystem> pParticleSys =
		new osgParticle::ParticleSystem;
	pParticleSys->setDefaultAttributes("E:/GreatMap/project/GM3ds/dev/trunk/ext/osg3.2.1_x86/Data/Image/smoke.rgb", false, false);
	pParticleSys->setDefaultParticleTemplate(pParticle);

	// 发射器
	osg::ref_ptr<osgParticle::ModularEmitter> pEmitter = new osgParticle::ModularEmitter;
	pEmitter->setParticleSystem(pParticleSys);

	osg::ref_ptr<osgParticle::RandomRateCounter> pRandomCounter = new osgParticle::RandomRateCounter;
	pRandomCounter->setRateRange(osgParticle::rangef(m_dParticlesNum, m_dParticlesNum));
	pEmitter->setCounter(pRandomCounter);

	osg::ref_ptr<osgParticle::PointPlacer> pPoint = new osgParticle::PointPlacer;
	pPoint->setCenter(postion);
	//pEmitter->setPlacer(pPoint);

	// 粒子发射枪
	osg::ref_ptr<osgParticle::RadialShooter> pShooter = new osgParticle::RadialShooter;
	pShooter->setInitialSpeedRange(m_dParticlesSpeed, 0);
	pEmitter->setShooter(pShooter);

	// 速度细节控制
	osg::ref_ptr<osgParticle::ModularProgram> pProgram = new osgParticle::ModularProgram;
	pProgram->setParticleSystem(pParticleSys);
	osg::ref_ptr<osgParticle::AccelOperator> pAccelOperator = new osgParticle::AccelOperator;
	pAccelOperator->setToGravity();
	pProgram->addOperator(pAccelOperator);
	osg::ref_ptr<osgParticle::FluidFrictionOperator> pOperator = new osgParticle::FluidFrictionOperator;
	pOperator->setFluidToAir();
	pProgram->addOperator(pOperator);

	osg::ref_ptr<osg::Geode> pGeode = new osg::Geode;
	pGeode->addDrawable(pParticleSys);
	parent->addChild(pEmitter);
	parent->addChild(pProgram);
	parent->addChild(pGeode);

	osg::ref_ptr<osgParticle::ParticleSystemUpdater> pParticleSysUpdate =
		new osgParticle::ParticleSystemUpdater;
	pParticleSysUpdate->addParticleSystem(pParticleSys);
	return pParticleSysUpdate;
}
