#version 400

in vec2 ex_Texture;
in vec3 ex_Normal;
in vec3 ex_Position;
out vec4 out_Color;

uniform sampler2D samplerKa;
uniform sampler2D samplerKd;
uniform sampler2D samplerKs;
uniform float material[10];
uniform float light[60]; // 6 * 10
uniform float fog[4];

uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 CameraMatrix;

void main(void)
{
  vec4 ambient  = vec4(material[0], material[1], material[2], material[9]);
  vec4 diffuse  = vec4(material[3], material[4], material[5], material[9]);
  vec4 specular = vec4(material[6], material[7], material[8], material[9]);

  vec3 lightPositions[10];
  vec3 lightColors[10];
  for (int i = 0; i < 10; i++){
    int offset = 6 * i;
    lightPositions[i].x = light[offset];
    lightPositions[i].y = light[offset + 1];
    lightPositions[i].z = light[offset + 2];
    lightColors[i].r = light[offset + 3];
    lightColors[i].g = light[offset + 4];
    lightColors[i].b = light[offset + 5];
  }

  //lightColors[0] = vec3(1, 0, 0);

  // Calculate Normal in world coordinates
  mat3 normalMatrix = transpose(inverse(mat3(ModelMatrix)));
  vec3 normal = normalize(normalMatrix * ex_Normal);

  // Calculate the location of this pixel in world coordinates
  vec3 fragPosition = vec3(ModelMatrix * vec4(ex_Position, 1.0));

  // Calculate the vector from pixel surface to light source
  vec3 surfaceToLight[10];
  for (int i = 0; i < 10; i++)
    surfaceToLight[i] = lightPositions[i] - fragPosition;
  float brightness[10];
  for (int i = 0; i < 10; i++){
    float dotProduct = dot(normal, surfaceToLight[i]);
    float distanceA = length(surfaceToLight[i]);
    float distanceB = length(normal);
    brightness[i] = clamp((dotProduct / distanceA) * distanceB, 0, 1);
  }

  // Calculate final color of the pixel, based on:
  // 1. The angle of incidence: brightness
  // 2. The color/intesities of the light
  // 3. The texture and texture coord: texture(tex, fragTexCoord)
 
  vec4 ambientTexture  = texture(samplerKa, ex_Texture);
  vec4 diffuseTexture  = texture(samplerKd, ex_Texture);
  vec4 specularTexture = texture(samplerKs, ex_Texture);
  
  vec4 lightMap = ambient;

  for (int i = 0; i < 10; i++)
      lightMap += vec4(brightness[i] * vec4(lightColors[i], 1));

  // Calculate Fog
  vec3 cameraPosition = vec3(CameraMatrix * vec4(1, 1, 1, 1));// * vec4(ex_Position, 1));
  float distance = length(cameraPosition - fragPosition);
  float scalar = clamp(fog[3] * (distance / 100), 0, 1);
  vec4 fogEffect = vec4(fog[0], fog[1], fog[2], 1);// * scalar;

  // General
  out_Color = (lightMap * diffuseTexture + (diffuse * diffuseTexture));
  // Add Fog
  out_Color = ((out_Color * (1 - scalar)) + (fogEffect * scalar));
  

 }