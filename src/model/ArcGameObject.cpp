/******************************************************************
 * Implementation file for Game Objects
 ******************************************************************/
#include "ArcGameObject.h"
#include <string>

/******************************************************************
 * Simple Constructor - No Model or Texture
 ******************************************************************/
ArcGameObject::ArcGameObject()
{
  mModel = "";
  mSize = 1;
  mLocation.x = 0;
  mLocation.y = 0;
  mLocation.z = 0;
  mRotation.x = 0;
  mRotation.y = 0;
  mRotation.z = 0;
}

/******************************************************************
 * Constructor - Takes a string model
 ******************************************************************/
ArcGameObject::ArcGameObject(std::string modelName)
{
  mModel = modelName;
  mSize = 1;
  mLocation.x = 0;
  mLocation.y = 0;
  mLocation.z = 0;
  mRotation.x = 0;
  mRotation.y = 0;
  mRotation.z = 0;
}

/******************************************************************
 * Constructor - Takes a char* model
 ******************************************************************/
ArcGameObject::ArcGameObject(const char* modelName)
{
  mModel = std::string(modelName);
  mSize = 1;
  mLocation.x = 0;
  mLocation.y = 0;
  mLocation.z = 0;
  mRotation.x = 0;
  mRotation.y = 0;
  mRotation.z = 0;
}

