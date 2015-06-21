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

  // Constructors
  ArcGameObject();
  ArcGameObject(std::string modelName);

  // Graphic Representation
  void useGraphicModel(std::string modelName) { mModel = modelName; };
  std::string model() { return mModel; };
  float& size() { return mSize; };

  // Reference ID
  int ID;

  // Position
  ArcVector& position() { return mPosition; };
  ArcVector& rotation() { return mRotation; };
  void setPosition(float x, float y, float z);
  void setRotation(float x, float y, float z);

  // Movement
  void stop();
  // Velocity
  ArcVector& posVeloc() { return mPosVeloc; };    
  ArcVector& rotVeloc() { return mRotVeloc; };
  void setPosVeloc(float x, float y, float z, float w);
  void setRotVeloc(float x, float y, float z, float w);
  // Acceleration
  ArcVector& posAccel() { return mPosAccel; };
  ArcVector& rotAccel() { return mRotAccel; };
  void setPosAccel(float x, float y, float z, float w);
  void setRotAccel(float x, float y, float z, float w);

  // Weight & Dimensions
  float& weight() { return mWeight; };
  ArcVector& dimensions() { return mDimensions; };

 private:
  std::string mModel;   // Name of the model used
  float  mSize;         // Percentage

  // Physics Factors
  ArcVector mRotation;  // ABC Rotation 0 - 360 Degrees
  ArcVector mPosition;  // XYZ Location
  ArcVector mRotAccel;  // Rotational Acceleration XYZW (W = intensity)
  ArcVector mPosAccel;  // Positional Acceleration XYZW (W = intensity)
  ArcVector mRotVeloc;  // Rotational Velocity XYZW (W = intensity)
  ArcVector mPosVeloc;  // Positional Velocity XYZW (W = intensity)

  ArcVector mDimensions; // How much space to the object take
  float     mWeight;     // How much does the object weigh
};

#endif
