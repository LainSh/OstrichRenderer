#pragma once
#include<iostream>
#include<gl/glew.h>
#include <string>
#include "Platform.h"
#include "Resource.h"

namespace OST
{
	class CTexture;

	class OST_DLL_EXPORT CFBO : public CResource
	{
		public:
			CFBO();
			CFBO(const std::string& vName);
			virtual ~CFBO(){}

			void createFBO(unsigned int vWidth, unsigned int vHeight);
			void bindFBO();
			void banFBO();
			void addBufferToFBO(GLuint &vBufferId, unsigned int vAttachment);
			void addTextureToFBO(CTexture* vTex, unsigned int vAttachment);

		protected:
			virtual void _initResourceV() override;

		private:
			bool checkFramebufferStatus();

			GLuint m_fboId;
			GLuint m_depId;
			unsigned int m_Width;
			unsigned int m_Height;
	};
}
