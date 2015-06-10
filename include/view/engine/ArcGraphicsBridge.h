/*************************************************************************
 * This class is the bridge between the program graphics data and the
 * Shader program on the GPU
 *************************************************************************/
#ifndef ARC_GRAPHICS_BRIDGE
#define ARC_GRAPHICS_BRIDGE

#include <GL/glew.h>
#include "ArcGraphicData.h"
#include "ArcGMD.h"
#include "ArcGOD.h"
#include "ArcTexture.h"
#include "string"

class ArcGraphicsBridge{
 public:
  ArcGraphicsBridge();
  ~ArcGraphicsBridge();
  void loadGraphicData(ArcGraphicData& model);
  void moveToGPU(ArcGMD& model, ArcGMP& GMP); // Updates Graphic Model Ptr
  void moveToGPU(ArcTexture& texture, GLuint& ID);
  void removeObject(ArcGMP& GMP);
 private:
  std::map<GLuint, ArcIDSet> mObjects;
  std::map<std::string, GLuint> mTextures; // Maps a texture to its ID
};

#endif
