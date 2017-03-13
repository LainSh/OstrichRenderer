#version 450

out vec4 FragColor;

uniform sampler2D uTexSampler;
uniform vec2 uScreenSize = vec2(1024, 768);

vec2 calculateTexCoord()
{
    return gl_FragCoord.xy / uScreenSize;
}

void main()
{
	vec2 TexCoord = calculateTexCoord();
	FragColor = texture(uTexSampler, TexCoord);
//	FragColor = vec4(1.0, 0.0, 0.0, 0.0);
}
