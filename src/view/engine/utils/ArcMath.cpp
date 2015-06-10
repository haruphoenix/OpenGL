/*****************************************************************
 * Vertex, Vector, and Matrix Math
 *****************************************************************/

#include "ArcMath.h"
#include <math.h>
#include <GL/glew.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

/****************************************************************
 * Math Operations
*****************************************************************/

float Cotangent(float angle)
{
  return (float)(1.0 / tan(angle));
}

float DegreesToRadians(float degrees)
{
  return degrees * (float)(PI / 180);
}

float RadiansToDegrees(float radians)
{
  return radians * (float)(180 / PI);
}

/****************************************************************
 * Vector Implementation
*****************************************************************/
ArcVector::ArcVector()
{
  x = 0;
  y = 0;
  z = 0;
  w = 1;
}

ArcVector::ArcVector(float pX, float pY, float pZ, float pW)
{
  x = pX;
  y = pY;
  z = pZ;
  w = pW;
}

float& ArcVector::operator [] (int index)
{
  switch (index)
  {
  case 0: return x;
  case 1: return y;
  case 2: return z;
  default: return w;
  }
}

void zero(ArcVector &v)
{
  v.x = 0;
  v.y = 0;
  v.z = 0;
  v.w = 1;
}

void normalize(ArcVector &v)
{
  float magnitude = sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
  if (magnitude != 0)
  {
    v.x /= magnitude;
    v.y /= magnitude;
    v.z /= magnitude;
  }
}

float dotProduct(const ArcVector &v1, const ArcVector &v2)
{
  return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}

ArcVector crossProduct(const ArcVector &v1, const ArcVector &v2)
{
  return ArcVector((v1.y * v2.z) - (v1.z * v2.y),
		   (v1.z * v2.x) - (v1.x * v2.z),
		   (v1.x * v2.y) - (v1.y * v2.x), 
		   1);
}

float getDistance(const ArcVector &v1, const ArcVector &v2)
{
  float dx = v2.x - v1.x;
  float dy = v2.y - v1.y;
  float dz = v2.z - v1.z;
  return sqrt((dx * dx) + (dy * dy) + (dz * dz));
}

ArcVector operator + (const ArcVector &v1, const ArcVector &v2)
{
  return ArcVector((v1.x + v2.x), 
		   (v1.y + v2.y),
		   (v1.z + v2.z),
		   1);
}

ArcVector operator - (const ArcVector &v1, const ArcVector &v2)
{
  return ArcVector((v1.x - v2.x), 
		   (v1.y - v2.y),
		   (v1.z - v2.z),
		   1);
}

ArcVector operator * (const ArcVector &v1, const ArcVector &v2)
{
  return ArcVector((v1.x * v2.x), 
		   (v1.y * v2.y),
		   (v1.z * v2.z),
		   1);
}

ArcVector operator * (const ArcVector &v,  const float &c)
{
  return ArcVector((v.x * c), 
		   (v.y * c),
		   (v.z * c),
		   1);
}

ArcVector operator / (const ArcVector &v1, const ArcVector &v2)
{
  return ArcVector((v1.x / v2.x), 
		   (v1.y / v2.y),
		   (v1.z / v2.z),
		   1);
}

ArcVector operator / (const ArcVector &v,  const float &c)
{
  return ArcVector((v.x / c), 
		   (v.y / c),
		   (v.z / c),
		   1);
}

void operator += (ArcVector &v1, const ArcVector &v2)
{
  v1.x += v2.x;
  v1.y += v2.y;
  v1.z += v2.z;
}

void operator -= (ArcVector &v1, const ArcVector &v2)
{
  v1.x -= v2.x;
  v1.y -= v2.y;
  v1.z -= v2.z;
}

void operator *= (ArcVector &v1, const ArcVector &v2)
{
  v1.x *= v2.x;
  v1.y *= v2.y;
  v1.z *= v2.z;
}

void operator *= (ArcVector &v,  const float &c)
{
  v.x *= c;
  v.y *= c;
  v.z *= c;
}

void operator /= (ArcVector &v1, const ArcVector &v2)
{
  v1.x /= v2.x;
  v1.y /= v2.y;
  v1.z /= v2.z;
}

void operator /= (ArcVector &v,  const float &c)
{
  v.x /= c;
  v.y /= c;
  v.z /= c;
}


/*********************************************************
 * Matrix Implementation
 *********************************************************/

const ArcMatrix IDENTITY_MATRIX = {{
    1, 0, 0, 0,
    0, 1, 0, 0,
    0, 0, 1, 0,
    0, 0, 0, 1
}};


ArcMatrix MultiplyMatrices(const ArcMatrix* m1, const ArcMatrix* m2)
{
  ArcMatrix out = IDENTITY_MATRIX;
  unsigned int row, column, rowOffset;

  for (row = 0, rowOffset = row * 4; row < 4; ++row, rowOffset = row * 4)
    for (column = 0; column < 4; ++column)
      out.m[rowOffset + column] =
	(m1->m[rowOffset + 0] * m2->m[column +  0]) +
	(m1->m[rowOffset + 1] * m2->m[column +  4]) +
	(m1->m[rowOffset + 2] * m2->m[column +  8]) +
	(m1->m[rowOffset + 3] * m2->m[column + 12]);

  return out;
}

void ScaleMatrix(ArcMatrix* m, float x, float y, float z)
{
  ArcMatrix scale = IDENTITY_MATRIX;

  scale.m[0]  = x;
  scale.m[5]  = y;
  scale.m[10] = z;

  //memcpy(m->m, MultiplyMatrices(m, &scale).m, sizeof(m->m));
  *m = MultiplyMatrices(m, &scale);
}

void TranslateMatrix(ArcMatrix* m, float x, float y, float z)
{
  ArcMatrix translation = IDENTITY_MATRIX;
  
  translation.m[12] = x;
  translation.m[13] = y;
  translation.m[14] = z;

  *m = MultiplyMatrices(m, &translation);
}

void RotateAboutX(ArcMatrix* m, float angle)
{
  ArcMatrix rotation = IDENTITY_MATRIX;
  float sine = (float)sin(angle);
  float cosine = (float)cos(angle);

  rotation.m[5]  = cosine;
  rotation.m[6]  = -sine;
  rotation.m[9]  = sine;
  rotation.m[10] = cosine;

  *m = MultiplyMatrices(m, &rotation);
}

void RotateAboutY(ArcMatrix* m, float angle)
{
  ArcMatrix rotation = IDENTITY_MATRIX;
  float sine = (float)sin(angle);
  float cosine = (float)cos(angle);

  rotation.m[0]  = cosine;
  rotation.m[8]  = sine;
  rotation.m[2]  = -sine;
  rotation.m[10] = cosine;

  *m = MultiplyMatrices(m, &rotation);
}

void RotateAboutZ(ArcMatrix* m, float angle)
{
  ArcMatrix rotation = IDENTITY_MATRIX;
  float sine = (float)sin(angle);
  float cosine = (float)cos(angle);

  rotation.m[0] = cosine;
  rotation.m[1] = -sine;
  rotation.m[4] = sine;
  rotation.m[5] = cosine;

  *m = MultiplyMatrices(m, &rotation);
}

ArcMatrix CreateProjectionMatrix(float fovy, float aspectRatio,
				 float nearPlane, float farPlane)
{
  ArcMatrix out = {{0}};
  const float
    yScale = Cotangent(DegreesToRadians(fovy / 2)),
    xScale = yScale / aspectRatio,
    frustumLength = farPlane - nearPlane;

  out.m[0]  = xScale;
  out.m[5]  = yScale;
  out.m[10] = -((farPlane + nearPlane) / frustumLength);
  out.m[11] = -1;
  out.m[14] = -((2 * nearPlane * farPlane) / frustumLength);

  return out;
}
			      
ArcMatrix operator + (const ArcMatrix &m1, const ArcMatrix &m2)
{
  ArcMatrix sum;
  for (int i = 0; i < 16; i++) sum.m[i] = m1.m[i] + m2.m[i];
  return sum;
}

ArcMatrix operator - (const ArcMatrix &m1, const ArcMatrix &m2)
{
  ArcMatrix dif;
  for (int i = 0; i < 16; i++) dif.m[i] = m1.m[i] - m2.m[i];
  return dif;
}

ArcMatrix operator * (const ArcMatrix &m1, const ArcMatrix &m2)
{
  return MultiplyMatrices(&m1, &m2);
}

ArcMatrix operator * (const ArcMatrix &m, const float &c)
{
  ArcMatrix product;
  for (int i = 0; i < 16; i++) product.m[i] *= c;
  return product;
}


ArcVector operator * (const ArcMatrix &m, const ArcVector &v)
{
  return ArcVector((m.m[0]  * v.x) + (m.m[1]  * v.y) + 
		   (m.m[2]  * v.z) + (m.m[3]  * v.z),
		   (m.m[4]  * v.x) + (m.m[5]  * v.y) + 
		   (m.m[6]  * v.z) + (m.m[7]  * v.z),
		   (m.m[8]  * v.x) + (m.m[9]  * v.y) + 
		   (m.m[10] * v.z) + (m.m[11] * v.z),
		   (m.m[12] * v.x) + (m.m[13] * v.y) + 
		   (m.m[14] * v.z) + (m.m[15] * v.z));
}


void printMatrix(ArcMatrix m)
{
  std::cout << m.m[0 ] << ", "
	    << m.m[1 ] << ", "
	    << m.m[2 ] << ", "
	    << m.m[3 ] << ",\n"
	    << m.m[4 ] << ", "
	    << m.m[5 ] << ", "
	    << m.m[6 ] << ", "
	    << m.m[7 ] << ",\n"
	    << m.m[8 ] << ", "
	    << m.m[9 ] << ", "
	    << m.m[10] << ", "
	    << m.m[11] << ",\n"
	    << m.m[12] << ", "
	    << m.m[13] << ", "
	    << m.m[14] << ", "
	    << m.m[15] << "\n";
}

/*********************************************************
 * Vertex Operations
 *********************************************************/

void printVertex(ArcVertex v)
{
  std::cout << "{"
	    << v.xyzw[0] << ", "
	    << v.xyzw[1] << ", "
	    << v.xyzw[2] << ", "
	    << v.xyzw[3] << "} {"
	    << v.rgba[0] << ", "
	    << v.rgba[1] << ", "
	    << v.rgba[2] << ", "
	    << v.rgba[3] << "}\n";
}
