#version 400

layout(location=0) in vec3 in_Position;
layout(location=1) in vec2 in_Texture;
layout(location=2) in vec3 in_Normal;
out vec2 ex_Texture;
out vec3 ex_Normal;

uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;

void main(void)
{
  mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
  gl_Position = MVP * vec4(in_Position, 1.0);
  ex_Texture = in_Texture;
  ex_Normal = in_Normal;
}