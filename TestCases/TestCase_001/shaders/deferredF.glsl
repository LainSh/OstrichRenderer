#version 430

out vec4 FragColor;

struct SBaseLight
{
	vec3 Color;
	float AmbientIntensity;
	float DiffuseIntensity;
};

struct SAttenuation
{
	float Constant;
	float Linear;
	float Exp;
};

struct SDirecionalLight
{
	SBaseLight Base;
	vec3 Direction;
};

uniform vec3 uDirectionalLightColor = vec3(1.0, 1.0, 1.0);
uniform vec3 uDirectionalLightDirection = vec3(-1.0, -1.0, 0.0);
uniform float uDirectionalLightAmbientIntensity = 0.3;
uniform float uDirectionalLightDiffuseIntensity = 0.7;

uniform sampler2D   uPositionSampler;
uniform sampler2D   uNormalSampler;

uniform vec3		uEyeWorldPos = vec3(0.0, 0.0, 1.0);
uniform vec2		uScreenSize = vec2(1024, 768);
uniform	float		uSpecularIntensity = 0.5;
uniform	float		uSpecularPower = 32.0;

vec2 calculateTexCoord()
{
    return gl_FragCoord.xy / uScreenSize;
}

vec4 calculateLightInternal(vec3 vWorldPos, vec3 vNormal)
{
	vec4 AmbientColor  = vec4(uDirectionalLightColor * uDirectionalLightAmbientIntensity, 1.0);
	vec4 DiffuseColor  = vec4(0.0, 0.0, 0.0, 0.0);
	vec4 SpecularColor = vec4(0.0, 0.0, 0.0, 0.0);

	float DiffuseFactor = dot(vNormal, -uDirectionalLightDirection);
	if (DiffuseFactor > 0.0)
	{
		DiffuseColor = vec4(uDirectionalLightColor * uDirectionalLightDiffuseIntensity * DiffuseFactor, 1.0);

		vec3 Vertex2Eye = normalize(uEyeWorldPos - vWorldPos);
		vec3 LightReflect = normalize(reflect(uDirectionalLightDirection, vNormal));
		float SpecularFactor = dot(Vertex2Eye, LightReflect);
		if (SpecularFactor > 0.0)
		{
			SpecularFactor = pow(SpecularFactor, uSpecularPower);
			SpecularColor  = vec4(uDirectionalLightColor * uSpecularIntensity * SpecularFactor, 1.0);
		}
	}

	return (AmbientColor + DiffuseColor + SpecularColor);
}


void main()
{
	vec2 TexCoord = calculateTexCoord();
	vec3 WorldPos = texture(uPositionSampler, TexCoord).xyz;
	vec3 Normal = texture(uNormalSampler, TexCoord).xyz;
	Normal = normalize(Normal);

//	if (WorldPos.z < 0) discard;

	FragColor = calculateLightInternal(WorldPos, Normal);
//	FragColor = vec4(1.0, 0.0 ,0.0, 0.0);
}