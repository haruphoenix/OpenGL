
#ifndef CAMERA_H
#define CAMERA_H

#include "ArcMath.h"

class ArcCamera
{
 public:

  // Holding keys down
  bool Forward;
  bool Backward;
  bool Left;
  bool Right;

  // Constructor
  ArcCamera();
  ArcCamera(int width, int height);

  // Destructor
  ~ArcCamera();

  // Move camera based on current direction
  void move(float deltaTime);
  void move();
  
  void changeDirection(int x, int y);

  void setScreen(int width, int height);

  ArcMatrix getMatrix(void);

  /* Inline Methods */

  float getPitchSensitivity()            { return mPitchSensitivity;  }
  float getYawSensitivity()              { return mYawSensitivity;    }
  void  setPitchSensitivity(float value) { mPitchSensitivity = value; }
  void  setYawSensitivity(float value)   { mYawSensitivity   = value; }

  ArcVector getPosition() const { return mPosition;   }
  float     getXPos()     const { return mPosition.x; }
  float     getYPos()     const { return mPosition.y; }
  float     getZPos()     const { return mPosition.z; }
  void      setPosition(float x, float y, float z);
  void      setRotation(float x, float y, float z);

  ArcVector getRotation() const { return mRotation;   }
  float     getXRot()     const { return mRotation.x; }
  float     getYRot()     const { return mRotation.y; }
  float     getZRot()     const { return mRotation.z; }

 protected:

  ArcVector mPosition;
  ArcVector mRotation;
  ArcVector mSpeed;

  float mMovementSpeedFactor; // How fast camera moves
  float mPitchSensitivity;    // How sensitive mouse movement is up and down
  float mYawSensitivity;      // How sensitive mouse movement is left and right

  void initCamera();

  int mMidX;
  int mMidY;

  ArcMatrix mView;
};

#endif
