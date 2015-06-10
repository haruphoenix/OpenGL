#version 400

in vec4 ex_Color;
in vec2 ex_Texture;
out vec4 out_Color;

uniform sampler2D sampler;

void main(void)
{
  //out_Color = texture2D(sampler, ex_Color.st);
  out_Color = texture(sampler, ex_Texture) * ex_Color;
  //out_Color = ex_Color;
}