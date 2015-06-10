#version 400

in vec2 ex_Texture;
in vec3 ex_Normal;
out vec4 out_Color;

uniform sampler2D sampler;

void main(void)
{
  //out_Color = texture2D(sampler, ex_Color.st);
  //out_Color = texture(sampler, ex_Texture) * ex_Color;
  //out_Color = ex_Color;
  out_Color = texture(sampler, ex_Texture);
}