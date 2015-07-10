#include "water.h"

Water::Water(GraphicsView* view)
: HandleAdapter(view)
{
	m_pWater = NULL;
	m_vecPoints = new osg::Vec3dArray;
	m_vecPoints->clear();

	initShader();
}

Water::~Water()
{

}

void Water::slotPickedXYZ(osg::Vec3d pos)
{
	m_vecPoints->push_back(pos);
	if (m_vecPoints->size() <= 2)
	{
		return;
	}

	drawWater();
}

void Water::slotMoveingXYZ(osg::Vec3d pos)
{
	if (m_vecPoints->size() < 2)
	{
		return;
	}

	drawWater(pos);
}

void Water::slotRightHandle()
{
	endHandle();
	m_pWater = nullptr;
}

void Water::drawWater(osg::Vec3d pos /*= osg::Vec3d()*/)
{
	osg::ref_ptr<osg::Vec3dArray> vecPoints = new osg::Vec3dArray;
	vecPoints = m_vecPoints;
	if (pos == osg::Vec3d() && m_vecPoints->size() <= 2)
	{
		return;
	}
	if (pos != osg::Vec3d())
	{
		vecPoints->push_back(pos);
	}
	osg::ref_ptr<osg::Geometry> pWater = new osg::Geometry;
	pWater->setVertexArray(vecPoints);
	pWater->addPrimitiveSet(
		new osg::DrawArrays(osg::PrimitiveSet::TRIANGLE_FAN, 0, vecPoints->size()));

	//Œ∆¿Ì
	osg::ref_ptr<osg::Texture2D> pText2D = new osg::Texture2D;
	pText2D->setTextureSize(1024, 1024);
	pText2D->setInternalFormat(GL_RGBA);

	pWater->getOrCreateStateSet()->setTextureAttributeAndModes(0, pText2D);
	pWater->getOrCreateStateSet()->setTextureAttributeAndModes(1,
		creatText2D("E:/GreatMap/project/version/Data/Bmp/shui_5.jpg"));
	pWater->getOrCreateStateSet()->setTextureAttributeAndModes(2,
		creatText2D("E:/GreatMap/project/version/Data/Bmp/water_DUDV.jpg"));
	pWater->getOrCreateStateSet()->setTextureAttributeAndModes(3,
		creatText2D("E:/GreatMap/project/version/Data/Bmp/water_NM.jpg"));

	// shader
	osg::ref_ptr<osg::Shader> pVeter = new osg::Shader(osg::Shader::VERTEX, m_waterVert);
	osg::ref_ptr<osg::Shader> pFrag = new osg::Shader(osg::Shader::FRAGMENT, m_waterFrag);
	osg::ref_ptr<osg::Program> pProgram = new osg::Program;
	pProgram->addShader(pVeter);
	pProgram->addShader(pFrag);
	pWater->getOrCreateStateSet()->addUniform(new osg::Uniform("reflection", 0));
	pWater->getOrCreateStateSet()->addUniform(new osg::Uniform("defaultTex", 1));
	pWater->getOrCreateStateSet()->addUniform(new osg::Uniform("refraction", 2));
	pWater->getOrCreateStateSet()->addUniform(new osg::Uniform("normalTex", 3));
	pWater->getOrCreateStateSet()->setAttributeAndModes(pProgram);

	if (m_pWater == NULL)
	{
		m_pWater = new osg::Geode;
		m_pLayerGroup->addChild(m_pWater);
	}
	m_pWater->addDrawable(pWater);
	m_pWater->setStateSet(pWater->getOrCreateStateSet());
}

osg::Texture2D* Water::creatText2D(const QString& strFile)
{
	if (strFile.isEmpty())
	{
		return NULL;
	}

	osg::ref_ptr<osg::Texture2D> pText2D = new osg::Texture2D;
	pText2D->setImage(osgDB::readImageFile(strFile.toStdString()));
	pText2D->setWrap(osg::Texture2D::WRAP_S, osg::Texture2D::REPEAT);
	pText2D->setWrap(osg::Texture2D::WRAP_T, osg::Texture2D::REPEAT);
	pText2D->setFilter(osg::Texture2D::MIN_FILTER, osg::Texture::LINEAR_MIPMAP_LINEAR);
	pText2D->setFilter(osg::Texture2D::MAG_FILTER, osg::Texture::LINEAR);
	return pText2D.release();
}

void Water::initShader()
{
	m_waterVert = {
		"uniform float osg_FrameTime;\n"
		"varying vec4 projCoords;\n"
		"varying vec3 lightDir, eyeDir;\n"
		"varying vec2 flowCoords, rippleCoords;\n"

		"void main()\n"
		"{\n"
		"   vec3 T = vec3(0.0, 1.0, 0.0);\n"
		"   vec3 N = vec3(0.0, 0.0, 1.0);\n"
		"   vec3 B = vec3(1.0, 0.0, 0.0);\n"
		"   T = normalize(gl_NormalMatrix * T);\n"
		"   B = normalize(gl_NormalMatrix * B);\n"
		"   N = normalize(gl_NormalMatrix * N);\n"

		"   mat3 TBNmat;\n"
		"   TBNmat[0][0] = T[0]; TBNmat[1][0] = T[1]; TBNmat[2][0] = T[2];\n"
		"   TBNmat[0][1] = B[0]; TBNmat[1][1] = B[1]; TBNmat[2][1] = B[2];\n"
		"   TBNmat[0][2] = N[0]; TBNmat[1][2] = N[1]; TBNmat[2][2] = N[2];\n"

		"   vec3 vertexInEye = vec3(gl_ModelViewMatrix * gl_Vertex);\n"
		"   lightDir =  gl_LightSource[0].position.xyz - vertexInEye;\n"
		"   lightDir = normalize(TBNmat * lightDir);\n"
		"   eyeDir = normalize(TBNmat * (-vertexInEye));\n"

		"   vec2 t1 = vec2(osg_FrameTime*0.02, osg_FrameTime*0.02);\n"
		"   vec2 t2 = vec2(osg_FrameTime*0.05, osg_FrameTime*0.05);\n"
		"   flowCoords = gl_MultiTexCoord0.xy + t1/10.0;\n" //* 5.0 + t1
		"   rippleCoords = gl_MultiTexCoord0.xy + t1;\n"   //

		"   gl_TexCoord[0] = gl_MultiTexCoord0;\n"
		"   gl_Position = ftransform();\n"
		"   projCoords = gl_Position;\n"
		"}\n"
	};

	m_waterFrag = {
		"uniform sampler2D defaultTex;\n"
		"uniform sampler2D reflection;\n"
		"uniform sampler2D refraction;\n"
		"uniform sampler2D normalTex;\n"
		"varying vec4 projCoords;\n"
		"varying vec3 lightDir, eyeDir;\n"
		"varying vec2 flowCoords, rippleCoords;\n"

		"void main()\n"
		"{\n"
		"   vec2 rippleEffect = 0.02 * texture2D(refraction, rippleCoords * 0.01).xy;\n"
		"   vec4 N = texture2D(normalTex, flowCoords + rippleEffect);\n"
		"   N = N * 2.0 - vec4(1.0);\n"
		"   N.a = 1.0; N = normalize(N);\n"

		"   vec3 refVec = normalize(reflect(-lightDir, vec3(N) * 0.6));\n"
		"   float refAngle = clamp(dot(eyeDir, refVec), 0.0, 1.0);\n"
		"   vec4 specular = vec4(pow(refAngle, 40.0));\n"

		"   vec2 dist = texture2D(refraction, flowCoords + rippleEffect).xy;\n"
		"   dist = (dist * 2.0 - vec2(1.0)) * 0.1;\n"
		"   vec2 uv = projCoords.xy / projCoords.w;\n"
		"   uv = clamp((uv + 1.0) * 0.5 + dist, 0.0, 1.0);\n"

		"   vec4 base = texture2D(defaultTex, uv);\n"
		"   vec4 refl = texture2D(reflection, uv);\n"
		"   gl_FragColor = mix(base, refl + specular, 0.6);\n"
		"}\n"
	};
}
