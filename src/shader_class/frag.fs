#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

// texture samplers
uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
	FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.5) * vec4(0.2,0.6,0.8,1.0) ;
	// FragColor = texture(texture1, TexCoord) * vec4(ourColor , 1.0f);
}