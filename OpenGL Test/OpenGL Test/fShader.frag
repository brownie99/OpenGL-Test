#version 330 core
out vec4 FragColor;
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float mixer;
in vec2 TexCoord;

uniform vec3 objectColor;
uniform vec3 lightColor;

void main()
{
FragColor = texture(texture1, TexCoord);
}