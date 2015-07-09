#include "motion.h"

Motion::Motion(GraphicsView* view, QWidget* parent)
	: m_pOSGView(view), QWidget(parent)
{
	ui.setupUi(this);

	addSphere();

	connect(ui.radioButton, SIGNAL(pressed()), this, SLOT(slotRadioChanged()));
	connect(ui.radioButton_2, SIGNAL(pressed()), this, SLOT(slotRadioChanged()));
	connect(ui.radioButton_3, SIGNAL(pressed()), this, SLOT(slotRadioChanged()));
	connect(ui.radioButton_4, SIGNAL(pressed()), this, SLOT(slotRadioChanged()));
	connect(ui.radioButton_5, SIGNAL(pressed()), this, SLOT(slotRadioChanged()));
	connect(ui.radioButton_6, SIGNAL(pressed()), this, SLOT(slotRadioChanged()));
	connect(ui.radioButton_7, SIGNAL(pressed()), this, SLOT(slotRadioChanged()));
	connect(ui.radioButton_8, SIGNAL(pressed()), this, SLOT(slotRadioChanged()));
	connect(ui.radioButton_9, SIGNAL(pressed()), this, SLOT(slotRadioChanged()));
	connect(ui.radioButton_10, SIGNAL(pressed()), this, SLOT(slotRadioChanged()));
	connect(ui.radioButton_11, SIGNAL(pressed()), this, SLOT(slotRadioChanged()));
	connect(ui.radioButton_12, SIGNAL(pressed()), this, SLOT(slotRadioChanged()));
	connect(ui.radioButton_13, SIGNAL(pressed()), this, SLOT(slotRadioChanged()));
	connect(ui.radioButton_14, SIGNAL(pressed()), this, SLOT(slotRadioChanged()));
	connect(ui.radioButton_15, SIGNAL(pressed()), this, SLOT(slotRadioChanged()));
	connect(ui.radioButton_16, SIGNAL(pressed()), this, SLOT(slotRadioChanged()));
	connect(ui.radioButton_17, SIGNAL(pressed()), this, SLOT(slotRadioChanged()));
	connect(ui.radioButton_18, SIGNAL(pressed()), this, SLOT(slotRadioChanged()));
	connect(ui.radioButton_19, SIGNAL(pressed()), this, SLOT(slotRadioChanged()));
	connect(ui.radioButton_20, SIGNAL(pressed()), this, SLOT(slotRadioChanged()));
	connect(ui.radioButton_21, SIGNAL(pressed()), this, SLOT(slotRadioChanged()));
	connect(ui.radioButton_22, SIGNAL(pressed()), this, SLOT(slotRadioChanged()));
	connect(ui.radioButton_23, SIGNAL(pressed()), this, SLOT(slotRadioChanged()));
	connect(ui.radioButton_24, SIGNAL(pressed()), this, SLOT(slotRadioChanged()));
	connect(ui.radioButton_25, SIGNAL(pressed()), this, SLOT(slotRadioChanged()));
	connect(ui.radioButton_26, SIGNAL(pressed()), this, SLOT(slotRadioChanged()));
	connect(ui.radioButton_27, SIGNAL(pressed()), this, SLOT(slotRadioChanged()));
}

Motion::~Motion()
{

}

void Motion::slotRadioChanged()
{
	QRadioButton* button = dynamic_cast<QRadioButton*>(sender());
	if (button)
	{
		QString str = button->text();

		if (!str.compare("OutQuadMotion"))
			m_pMotion->setMotion<osgAnimation::OutQuadMotion>()
			;

		else if (!str.compare("InQuadMotion"))
			m_pMotion->setMotion<osgAnimation::InQuadMotion>()
			;

		else if (!str.compare("InOutQuadMotion"))
			m_pMotion->setMotion<osgAnimation::InOutQuadMotion>()
			;

		else if (!str.compare("OutCubicMotion"))
			m_pMotion->setMotion<osgAnimation::OutCubicMotion>()
			;

		else if (!str.compare("InCubicMotion"))
			m_pMotion->setMotion<osgAnimation::InCubicMotion>()
			;

		else if (!str.compare("InOutCubicMotion"))
			m_pMotion->setMotion<osgAnimation::InOutCubicMotion>()
			;

		else if (!str.compare("OutQuartMotion"))
			m_pMotion->setMotion<osgAnimation::OutQuartMotion>()
			;

		else if (!str.compare("InQuartMotion"))
			m_pMotion->setMotion<osgAnimation::InQuartMotion>()
			;

		else if (!str.compare("InOutQuartMotion"))
			m_pMotion->setMotion<osgAnimation::InOutQuartMotion>()
			;

		else if (!str.compare("OutBounceMotion"))
			m_pMotion->setMotion<osgAnimation::OutBounceMotion>()
			;

		else if (!str.compare("InBounceMotion"))
			m_pMotion->setMotion<osgAnimation::InBounceMotion>()
			;

		else if (!str.compare("InOutBounceMotion"))
			m_pMotion->setMotion<osgAnimation::InOutBounceMotion>()
			;

		else if (!str.compare("OutElasticMotion"))
			m_pMotion->setMotion<osgAnimation::OutElasticMotion>()
			;

		else if (!str.compare("InElasticMotion"))
			m_pMotion->setMotion<osgAnimation::InElasticMotion>()
			;

		else if (!str.compare("InOutElasticMotion"))
			m_pMotion->setMotion<osgAnimation::InOutElasticMotion>()
			;

		else if (!str.compare("OutSineMotion"))
			m_pMotion->setMotion<osgAnimation::OutSineMotion>()
			;

		else if (!str.compare("InSineMotion"))
			m_pMotion->setMotion<osgAnimation::InSineMotion>()
			;

		else if (!str.compare("InOutSineMotion"))
			m_pMotion->setMotion<osgAnimation::InOutSineMotion>()
			;

		else if (!str.compare("OutBackMotion"))
			m_pMotion->setMotion<osgAnimation::OutBackMotion>()
			;

		else if (!str.compare("InBackMotion"))
			m_pMotion->setMotion<osgAnimation::InBackMotion>()
			;

		else if (!str.compare("InOutBackMotion"))
			m_pMotion->setMotion<osgAnimation::InOutBackMotion>()
			;

		else if (!str.compare("OutCircMotion"))
			m_pMotion->setMotion<osgAnimation::OutCircMotion>()
			;

		else if (!str.compare("InCircMotion"))
			m_pMotion->setMotion<osgAnimation::InCircMotion>()
			;

		else if (!str.compare("InOutCircMotion"))
			m_pMotion->setMotion<osgAnimation::InOutCircMotion>()
			;

		else if (!str.compare("OutExpoMotion"))
			m_pMotion->setMotion<osgAnimation::OutExpoMotion>()
			;

		else if (!str.compare("InExpoMotion"))
			m_pMotion->setMotion<osgAnimation::InExpoMotion>()
			;

		else if (!str.compare("InOutExpoMotion"))
			m_pMotion->setMotion<osgAnimation::InOutExpoMotion>()
			;

		else m_pMotion->setMotion<osgAnimation::LinearMotion>();
	}
}

void Motion::addSphere()
{
	osg::ref_ptr<osg::Geode> pGeo = new osg::Geode;
	pGeo->addDrawable(new osg::ShapeDrawable(new osg::Sphere(osg::Vec3d(), 4.0)));

	m_pMotion = new MotionCallback;

	osg::ref_ptr<osg::MatrixTransform> pMat = new osg::MatrixTransform;
	pMat->addChild(pGeo);
	pMat->addUpdateCallback(m_pMotion);

	m_pOSGView->getRoot()->addChild(pMat);
}
