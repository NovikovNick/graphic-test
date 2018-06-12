#version 330 core
in vec3 ourColor;
in vec2 TexCoord;

out vec4 color;


uniform vec3 objectColor;
uniform vec3 lightColor;
uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;

void main()
{
    color =  mix(texture(ourTexture1, TexCoord), vec4(lightColor * objectColor, 1.0f), 0.5);
}