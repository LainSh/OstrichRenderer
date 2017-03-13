#include "FBO.h"
#include "Texture.h"
#include "ProductFactory.h"
#include "Interface.h"

using namespace OST;

OST::CProductFactory<CFBO> theCreater(RESOURCE_SIG::RS_FBO);

OST::CFBO::CFBO()
{
	setSig(RESOURCE_SIG::RS_FBO);
}

CFBO::CFBO(const std::string& vName)
{
	setSig(RESOURCE_SIG::RS_FBO);
	setName(vName);
}

//******************************************************************
//FUNCTION:
void CFBO::bindFBO()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_fboId);
}

//******************************************************************
//FUNCTION:
void CFBO::banFBO()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

//******************************************************************
//FUNCTION:
void CFBO::createFBO(unsigned int vWidth, unsigned int vHeight)
{ 
	m_Width = vWidth;
	m_Height = vHeight;
	glGenFramebuffers(1, &m_fboId);
	glGenRenderbuffers(1, &m_depId); 

	glBindFramebuffer(GL_FRAMEBUFFER, m_fboId);
	glBindRenderbuffer(GL_RENDERBUFFER, m_depId);  
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, m_Width, m_Height);  
	glBindRenderbuffer(GL_RENDERBUFFER, 0); 

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depId);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);  
}

void CFBO::addBufferToFBO(GLuint &vBufferId, unsigned int vAttachment)
{
	bool status;
	glBindFramebuffer(GL_FRAMEBUFFER, m_fboId);

	glGenTextures(1, &vBufferId);  
	glBindTexture(GL_TEXTURE_2D, vBufferId);  
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, m_Width, m_Height, 0, GL_RGBA, GL_FLOAT, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);  
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0); 

	switch(vAttachment)
	{
	case 0:
		glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, vBufferId, 0);
		break;
	case 1:
		glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, vBufferId, 0);
		break;
	case 2:
		glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, vBufferId, 0); 
		break;
	case 3:
		glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT3, GL_TEXTURE_2D, vBufferId, 0); 
		break;
	default :
		std::cout<<"Ìí¼Ó»º´æµ½FBOÊ§°Ü"<<std::endl;
	}
	status = checkFramebufferStatus();
	glBindFramebuffer(GL_FRAMEBUFFER, 0); 
}

bool CFBO::checkFramebufferStatus()
{
	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	switch(status)
	{
	case GL_FRAMEBUFFER_COMPLETE:
		std::cout << "Framebuffer complete." << std::endl;
		return true;

	case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
		std::cout << "[ERROR] Framebuffer incomplete: Attachment is NOT complete." << std::endl;
		return false;

	case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
		std::cout << "[ERROR] Framebuffer incomplete: No image is attached to FBO." << std::endl;
		return false;

	case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
		std::cout << "[ERROR] Framebuffer incomplete: Draw buffer." << std::endl;
		return false;

	case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
		std::cout << "[ERROR] Framebuffer incomplete: Read buffer." << std::endl;
		return false;

	case GL_FRAMEBUFFER_UNSUPPORTED:
		std::cout << "[ERROR] Framebuffer incomplete: Unsupported by FBO implementation." << std::endl;
		return false;

	default:
		std::cout << "[ERROR] Framebuffer incomplete: Unknown error." << std::endl;
		return false;
	}
}

//******************************************************************
//FUNCTION:
void CFBO::addTextureToFBO(CTexture* vTex, unsigned int vAttachment)
{
	bool status;
	glBindFramebuffer(GL_FRAMEBUFFER, m_fboId);
	glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0+vAttachment, GL_TEXTURE_2D, vTex->getTextureObject(), 0);
	status = checkFramebufferStatus();
	glBindFramebuffer(GL_FRAMEBUFFER, 0); 
}

//******************************************************************
//FUNCTION:
void CFBO::_initResourceV()
{
	const CConfig* pConfig = _getConfig();
	if (!pConfig->isAttributeExisted(CONFIG_KEYWORD::FBO_NAME))
	{
		// error;
		return;
	}

	setName(pConfig->getAttribute<std::string>(CONFIG_KEYWORD::FBO_NAME));

	glm::vec2 FBOSize = pConfig->getAttribute<glm::vec2>(CONFIG_KEYWORD::FBO_SIZE);
	createFBO(FBOSize.x, FBOSize.y);
	unsigned int AttachmentID = 0;
	for (unsigned int i=0; i<pConfig->getSubConfigNum(); i++)
	{
		CConfig* pAttachConfig = pConfig->fetchSubConfigAt(i);
//		if (pAttachConfig->getConfigSig() != CONFIG_KEYWORD::FBO_ATTACHMENT || pAttachConfig->isAttributeExisted(CONFIG_KEYWORD::FBO_ATTACHED_TEXTURE)) continue;
		std::string AttachedTex = pAttachConfig->getAttribute<std::string>(CONFIG_KEYWORD::FBO_ATTACHED_TEXTURE);
		CTexture* pTex = OSTFetchTexture(AttachedTex);
		addTextureToFBO(pTex, AttachmentID);
		AttachmentID++;
	}
}
