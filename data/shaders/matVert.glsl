#version 400

layout(location=0) in vec3 in_Position;
layout(location=1) in vec2 in_Texture;
layout(location=2) in vec3 in_Normal;
out vec2 ex_Texture;
out vec3 ex_Normal;
out vec3 ex_Position;

uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;

void main(void)
{
  mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
  gl_Position = MVP * vec4(in_Position, 1.0);
  ex_Texture = in_Texture;
  ex_Normal = in_Normal;
  ex_Position = in_Position;
  //ex_Normal = normalize(vec3((MVP * vec4(in_Normal, 1.0)).xyz));
  //ex_Normal = normalize(transpose(inverse(mat3(ModelMatrix))) * in_Normal);
}