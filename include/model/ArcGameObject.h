/******************************************************************
 * Basic Game Object. Contains name of the model to use, data
 * related to the object, position, rotation, and size
 ******************************************************************/
#ifndef ARC_GAME_OBJECT
#define ARC_GAME_OBJECT

#include <string>
#include <ArcMath.h>

class ArcGameObject{
 public:
  ArcGameObject();
  ArcGameObject(std::string modelName);
  ArcGameObject(const char* modelName);
  //ArcGameObject(const char* modelName, const char* textureName);
  void useGraphicModel(std::string modelName) { mModel = modelName; };
  //void useTexture(std::string texture) { mTexture = texture; };
  std::string model() { return mModel; };
  //std::string texture() { return mTexture; };
  int ID;
  ArcVector& rotation() { return mRotation; };
  ArcVector& location() { return mLocation; };
  float& size() { return mSize; };
 private:
  std::string mModel;   // Name of the model used
  //std::string mTexture; // Name of the texture used
  float  mSize;         // Percentage
  ArcVector mRotation;  // ABC Rotation 0 - 360 Degrees
  ArcVector mLocation;  // XYZ Location
};

#endif
