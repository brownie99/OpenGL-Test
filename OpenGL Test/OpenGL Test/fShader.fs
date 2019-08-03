#version 330 core
out vec4 FragColor;
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float mixer;
in vec2 TexCoord;
void main()
{
FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), mixer);
}