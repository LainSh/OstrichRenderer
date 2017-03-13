#include "Texture.h"
#include <SOIL/SOIL.h>
#include "ProductFactory.h"
#include "Interface.h"
#include <boost/tokenizer.hpp>

using namespace OST;

OST::CProductFactory<CTexture> theCreater(RESOURCE_SIG::RS_TEXTURE);

CTexture::CTexture()
{
	setSig(RESOURCE_SIG::RS_TEXTURE);
	m_Image = nullptr;
}

OST::CTexture::CTexture(const std::string& vName, GLenum TextureType)
{
	setSig(RESOURCE_SIG::RS_TEXTURE);
	setName(vName);
	m_TextureSize.resize(3);
	m_TextureTarget = TextureType;
	m_Image = nullptr;
	__genTexObj();
}

CTexture::~CTexture(void)
{
	SOIL_free_image_data(m_Image);
}

//******************************************************************
//FUNCTION:
bool CTexture::load(const std::string& vFileName)
{
	m_Image = SOIL_load_image(vFileName.c_str(), &m_TextureSize[0], &m_TextureSize[1], &m_Channel, SOIL_LOAD_RGB);

	if (!m_Image)
	{
		return false;
	}

	__genTexObj();
	glBindTexture(m_TextureTarget, m_TextureObj);
	glTexParameterf(m_TextureTarget, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(m_TextureTarget, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(m_TextureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(m_TextureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvf(m_TextureTarget, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexImage2D(m_TextureTarget, 0, GL_RGB, m_TextureSize[0], m_TextureSize[1], 0, GL_RGB, GL_UNSIGNED_BYTE, m_Image);

	glBindTexture(m_TextureTarget, 0);

	return true;
}

//******************************************************************
//FUNCTION:
void CTexture::bind(GLenum vTextureUnit)
{
	glActiveTexture(vTextureUnit);
	glBindTexture(m_TextureTarget, m_TextureObj);
}


//******************************************************************
//FUNCTION:
void OST::CTexture::_initResourceV()
{
	const CConfig* pConfig = _getConfig();
	_ASSERT(pConfig);
	if (!pConfig->isAttributeExisted(CONFIG_KEYWORD::TEXTURE_NAME))
	{
		// error;
		return;
	}

	setName(pConfig->getAttribute<std::string>(CONFIG_KEYWORD::TEXTURE_NAME));

	std::string TextureType = boost::algorithm::to_upper_copy(pConfig->getAttribute<std::string>(CONFIG_KEYWORD::TEXTURE_TYPE));
	int TexTarget = 0;
	OSTInterpretString2GraphicsEnum<int>(TextureType, TexTarget);

	m_TextureTarget = TexTarget;

	m_TextureSize.resize(3);
	std::string TextureSize = pConfig->getAttribute<std::string>(CONFIG_KEYWORD::TEXTURE_SIZE);
	boost::char_separator<char> Sep(" ");
	boost::tokenizer<boost::char_separator<char>> Token(TextureSize, Sep);
	for (auto TokenIter : Token)
	{
		std::string Temp = TokenIter;
		m_TextureSize.push_back(std::atoi(Temp.c_str()));
	}

	__genTexObj();
}

//******************************************************************
//FUNCTION:
void OST::CTexture::__genTexObj()
{
	glGenTextures(1, &m_TextureObj);
}