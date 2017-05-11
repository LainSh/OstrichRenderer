#include "Renderer.h"
#include "EffectManager.h"
#include "Effect.h"
#include "ModelManager.h"
#include "CameraManager.h"
#include "ResourceManager.h"

using namespace OST;

CRenderer::CRenderer(void) : m_pDisplayWindow(nullptr), m_pSceneConfig(nullptr), m_pEffectConfig(nullptr), m_pResourceConfig(nullptr)
{
}


CRenderer::~CRenderer(void)
{
}

//******************************************************************
//FUNCTION:
bool CRenderer::initRenderer()
{
	__loadConfig();
	
	CConfig* pWindowConfig = m_pSceneConfig->fetchSubConfigByName(CONFIG_KEYWORD::WINDOW);
	_OST_SIMPLE_IF_ELSE(!pWindowConfig->isAttributeExisted(CONFIG_KEYWORD::WINDOW_TITLE),  m_WindowTitle = DEFAULT_CONFIG::DEFAULT_WIN_TITLE, m_WindowTitle = pWindowConfig->getAttribute<std::string>(CONFIG_KEYWORD::WINDOW_TITLE));
	_OST_SIMPLE_IF_ELSE(!pWindowConfig->isAttributeExisted(CONFIG_KEYWORD::WINDOW_WIDTH),  m_WinWidth = DEFAULT_CONFIG::DEFAULT_WIN_WIDTH,    m_WinWidth = pWindowConfig->getAttribute<int>(CONFIG_KEYWORD::WINDOW_WIDTH));
	_OST_SIMPLE_IF_ELSE(!pWindowConfig->isAttributeExisted(CONFIG_KEYWORD::WINDOW_HEIGHT), m_WinHeight = DEFAULT_CONFIG::DEFAULT_WIN_HEIGHT,  m_WinHeight = pWindowConfig->getAttribute<int>(CONFIG_KEYWORD::WINDOW_HEIGHT));

	if (!__initEnvironment()) return false;

	__initScene();
	__initAllResource();
	__initAllEffect();

	return true;
}

//******************************************************************
//FUNCTION:
void CRenderer::run()
{
	if (!m_pDisplayWindow)
	{
		fprintf(stderr, "Error: can not run without window instance \n");
		return;
	}

	while (!m_pDisplayWindow->windowShouldClose())
	{
		_renderV();

		glfwSwapBuffers(m_pDisplayWindow->fetchWindowInstance());
		glfwPollEvents();
	}

	__destroy();
}

//******************************************************************
//FUNCTION:
void CRenderer::__destroy()
{
	glfwTerminate();
	delete m_pDisplayWindow;
	m_pDisplayWindow = nullptr;
}

//******************************************************************
//FUNCTION:
bool CRenderer::__initEnvironment()
{
	if (m_pDisplayWindow) delete m_pDisplayWindow;

	m_pDisplayWindow = new CDisplayWindow;
	m_pDisplayWindow->createWindowInstance(m_WindowTitle, m_WinWidth, m_WinHeight);

	glfwMakeContextCurrent(m_pDisplayWindow->fetchWindowInstance());

	GLuint res = glewInit();
	if (res != GLEW_OK)
	{
		fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
		return false;
	}

	return true;
}

//******************************************************************
//FUNCTION:
void CRenderer::__loadConfig()
{

	m_pOptionConfig = new CConfig;
	m_pOptionConfig->parseXMLFile(OST::DEFAULT_CONFIG::OPTION_PATH);

	m_pSceneConfig = new CConfig;
	m_pSceneConfig->parseXMLFile(OST::DEFAULT_CONFIG::SCENE_PATH);

	m_pEffectConfig = new CConfig;
	m_pEffectConfig->parseXMLFile(OST::DEFAULT_CONFIG::EFFECT_PATH);

	m_pResourceConfig = new CConfig;
	m_pResourceConfig->parseXMLFile(OST::DEFAULT_CONFIG::RESOURCE_PATH);
}

//******************************************************************
//FUNCTION:
bool CRenderer::__initAllEffect()
{
	OST::CEffectManager::getInstance()->createAllEffect(m_pEffectConfig, m_EffectMap);

	return true;
}

//******************************************************************
//FUNCTION:
bool CRenderer::_loadEffect(const std::string& vEffectSig)
{
	if (m_EffectMap.find(vEffectSig) == m_EffectMap.end()) return false;

	m_EffectMap[vEffectSig]->loadEffect();

	return true;
}

//******************************************************************
//FUNCTION:
bool OST::CRenderer::__initAllResource()
{
	_ASSERT(m_pResourceConfig);
	OST::CResourceManager::getInstance()->createAllResource(m_pResourceConfig->fetchSubConfigByName(CONFIG_KEYWORD::RESOURCE));
	return true;
}

//******************************************************************
//FUNCTION:
bool OST::CRenderer::__initScene()
{
	CConfig* SceneModelConfig = m_pSceneConfig->fetchSubConfigByName(CONFIG_KEYWORD::SCENE_CONFIG);
	if (!CModelManager::getInstance()->createAllModel(SceneModelConfig)) return false;

	CConfig* CameraConfig = m_pSceneConfig->fetchSubConfigByName(CONFIG_KEYWORD::CAMERA_CONFIG);
	if (!CCameraManager::getInstance()->createCameraManipulator(CameraConfig)) return false;

	return true;
}
