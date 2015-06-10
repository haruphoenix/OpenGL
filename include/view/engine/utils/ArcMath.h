#ifndef ARCMATH_H
#define ARCMATH_H

static const double PI = 3.14159265358979323846;

typedef struct ArcVertex
{
  float xyzw[4];
  float rgba[4];
} ArcVertex;

typedef struct ArcMatrix
{
  float m[16];
} ArcMatrix;

typedef struct ArcVector
{
  float x;
  float y;
  float z;
  float w;
  ArcVector();
  ArcVector(float, float, float, float);
  float& operator[] (int);
} ArcVector;

float Cotangent(float angle);
float DegreesToRadians(float degrees);
float RadiansToDegrees(float radians);

extern const ArcMatrix IDENTITY_MATRIX;
ArcMatrix MultiplyMatrices(const ArcMatrix* m1, const ArcMatrix* m2);
void RotateAboutX(ArcMatrix* m, float angle);
void RotateAboutY(ArcMatrix* m, float angle);
void RotateAboutZ(ArcMatrix* m, float angle);
void ScaleMatrix(ArcMatrix* m, float x, float y, float z);
void TranslateMatrix(ArcMatrix* m, float x, float y, float z);
ArcMatrix CreateProjectionMatrix(float fovy, float aspectRatio,
				 float nearPlane, float farPlane);
ArcMatrix operator + (const ArcMatrix &m1, const ArcMatrix &m2);
ArcMatrix operator - (const ArcMatrix &m1, const ArcMatrix &m2);
ArcMatrix operator * (const ArcMatrix &m1, const ArcMatrix &m2);
ArcMatrix operator * (const ArcMatrix &m, const float &c);

void zero(ArcVector &v);
void normalize(ArcVector &v);
float dotProduct(const ArcVector &v1, const ArcVector &v2);
ArcVector crossProduct(const ArcVector &v1, const ArcVector &v2);
float getDistance(const ArcVector &v1, const ArcVector &v2);

// Operator stuff
ArcVector operator + (const ArcVector &v1, const ArcVector &v2);
ArcVector operator - (const ArcVector &v1, const ArcVector &v2);
ArcVector operator * (const ArcVector &v1, const ArcVector &v2);
ArcVector operator * (const ArcVector &v,  const float &c);
ArcVector operator / (const ArcVector &v1, const ArcVector &v2);
ArcVector operator / (const ArcVector &v,  const float &c);
void operator += (ArcVector &v1, const ArcVector &v2);
void operator -= (ArcVector &v1, const ArcVector &v2);
void operator *= (ArcVector &v1, const ArcVector &v2);
void operator *= (ArcVector &v,  const float &c);
void operator /= (ArcVector &v1, const ArcVector &v2);
void operator /= (ArcVector &v,  const float &c);

ArcVector operator * (const ArcMatrix &m, const ArcVector &v); 

void printVertex(ArcVertex v);

void printMatrix(ArcMatrix m);

#endif
