#ifndef ARC_SHADER
#define ARC_SHADER

#include <GL/glew.h>
#include "ArcGOD.h"
#include "ArcMath.h"
#include <list>
#include <vector>

#ifndef ARC_MAX_LIGHTS
#define ARC_MAX_LIGHTS 10
#endif

class ArcShader{
 public:
  ArcShader();
  ~ArcShader();
  void initialize();
  void addVertexShader(const char* filename);
  void addFragmentShader(const char* filename);
  void link();
  void use();
  void draw(ArcGOD& object);
  void setView(ArcMatrix view);
  void setCameraLocation(ArcMatrix cameraLocation);
  void setProjection(ArcMatrix projection);
  void setLights(ArcLight* lights);
  void setFog(ArcFog* fog);
 private:
  GLuint loadShader(const char* filename, GLenum shader_type);
  std::list<GLuint> mShaders;
  GLuint mProgramId;
  GLuint mModelMatrix;
  GLuint mViewMatrix;       // View Matrix from camera
  GLuint mCameraMatrix;     // Position of the camera
  GLuint mProjectionMatrix;
  GLuint mKaTexture;
  GLuint mKdTexture;
  GLuint mKsTexture;
  GLuint mMaterial;
  GLuint mLights;
  int    mNumLights;
  GLuint mFog;
};

#endif
