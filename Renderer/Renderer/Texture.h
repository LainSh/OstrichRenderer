#pragma once
#include <gl/glew.h>
#include <string>
#include <vector>
#include "Platform.h"
#include "Resource.h"

namespace OST
{
	class OST_DLL_EXPORT CTexture : public CResource
	{
	public:
		CTexture(const std::string& vName, GLenum TextureType);
		CTexture();
		~CTexture(void);

		bool load(const std::string& vFileName);
		void bind(GLenum vTextureUnit);
		int getTextureWidth() const {return m_TextureSize[0];}
		int getTextureHeight() const {return m_TextureSize[1];}
		int getTextureDepth() const { return m_TextureSize[2]; }

		GLuint getTextureObject() const {return m_TextureObj;}
	
	protected:
		virtual void _initResourceV() override;

	private:
		void __genTexObj();

	private:
		GLenum m_TextureTarget;
		GLuint m_TextureObj;
		GLuint64 m_TextureHandle;
		std::vector<int> m_TextureSize;
		
		unsigned char* m_Image;
		int m_Channel;
	};

}
