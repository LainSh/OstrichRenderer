#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <assimp/types.h>
#include <assimp/matrix4x4.h>
#include <assimp/matrix3x3.h>
#include <string>
#include <gl/glew.h>

namespace OST
{

#define _OST_SIMPLE_IF(condition, opTrue)                  if (condition) {opTrue;}
#define _OST_SIMPLE_IF_ELSE(condition, opTrue, opFalse)    if (condition) {opTrue;} else {opFalse;}

	static glm::mat4 mat4FromaiMatrix4x4(const aiMatrix4x4& vAssimpMat4)
	{
		glm::mat4 retMatrix;

		float Value[16];

		Value[0] = vAssimpMat4.a1; Value[1] = vAssimpMat4.b1; Value[2] = vAssimpMat4.c1; Value[3] = vAssimpMat4.d1;
		Value[4] = vAssimpMat4.a2; Value[5] = vAssimpMat4.b2; Value[6] = vAssimpMat4.c2; Value[7] = vAssimpMat4.d2;
		Value[8] = vAssimpMat4.a3; Value[9] = vAssimpMat4.b3; Value[10]= vAssimpMat4.c3; Value[11]= vAssimpMat4.d3;
		Value[12]= vAssimpMat4.a4; Value[13]= vAssimpMat4.b4; Value[14]= vAssimpMat4.c4; Value[15]= vAssimpMat4.d4;

		retMatrix = glm::make_mat4(Value);
		return retMatrix;
	};

	static glm::mat4 mat4FromaiMatrix3x3(const aiMatrix3x3& vAssimpMat3)
	{
		glm::mat4 retMatrix;

		float Value[16];

		Value[0] = vAssimpMat3.a1; Value[1] = vAssimpMat3.b1; Value[2] = vAssimpMat3.c1; Value[3] = 0.0;
		Value[4] = vAssimpMat3.a2; Value[5] = vAssimpMat3.b2; Value[6] = vAssimpMat3.c2; Value[7] = 0.0;
		Value[8] = vAssimpMat3.a3; Value[9] = vAssimpMat3.b3; Value[10]= vAssimpMat3.c3; Value[11]= 0.0;
		Value[12]= 0.0;			   Value[13]= 0.0;			  Value[14]= 0.0;			 Value[15]= 1.0;

		retMatrix = glm::make_mat4(Value);
		return retMatrix;
	};

	namespace DEFAULT_CONFIG
	{
		const std::string SCENE_PATH = "scene.xml";
		const std::string EFFECT_PATH = "effect.xml";
		const std::string RESOURCE_PATH = "resource.xml";
		const std::string MODEL_PATH = "../../Resources/Model/";

		const std::string DEFAULT_WIN_TITLE  = "Default Title";
		const int DEFAULT_WIN_WIDTH  = 1280;
		const int DEFAULT_WIN_HEIGHT = 720;
	}

	namespace CONFIG_KEYWORD
	{
		const std::string SCENE = "SCENE";
		const std::string EFFECT = "EFFECT";
		const std::string EFFECT_SIG = "EFFECT_SIG";
		const std::string WINDOW = "WINDOW";
		const std::string WINDOW_TITLE  = "WIN_TITLE";
		const std::string WINDOW_WIDTH  = "WIN_WIDTH";
		const std::string WINDOW_HEIGHT = "WIN_HEIGHT";
		const std::string MODEL = "MODEL";
		const std::string MODEL_SIG = "MODEL_SIG";
		const std::string MODEL_FILE = "MODEL_FILE";
		const std::string SHADER = "SHADER";
		const std::string SHADER_NAME = "SHADER_NAME";
		const std::string VERTEX_SHADER = "VERTEX_SHADER";
		const std::string FRAGMENT_SHADER = "FRAGMENT_SHADER";

		const std::string RESOURCE = "RESOURCE";

		const std::string TEXTURE  = "TEXTURE";
		const std::string TEXTURE_NAME = "TEXTURE_NAME";
		const std::string TEXTURE_TYPE = "TEXTURE_TYPE";
		const std::string TEXTURE_SIZE = "TEXTURE_SIZE";

		const std::string FBO = "FBO";
		const std::string FBO_NAME = "FBO_NAME";
		const std::string FBO_SIZE = "FBO_SIZE";
		const std::string FBO_STENCIL = "FBO_STENCIL";
		const std::string FBO_ATTACHMENT = "FBO_ATTACHMENT";
		const std::string FBO_ATTACHED_TEXTURE = "FBO_ATTACHED_TEXTURE";
	}

	namespace RESOURCE_SIG
	{
		const std::string RS_TEXTURE = "TEXTURE";
		const std::string RS_FBO = "FBO";
	}

	namespace TEXTURE_TYPE_SIG
	{
		const std::string TTS_1D = "TEX1D";
		const std::string TTS_2D = "TEX2D";
		const std::string TTS_3D = "TEX3D";
	}

}