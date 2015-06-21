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
  mWeight = 100;
  mDimensions.x = 0;
  mDimensions.y = 0;
  mDimensions.z = 0;
  setPosition(0, 0, 0);
  setRotation(0, 0, 0);
  stop();
}

#include <iostream>

/******************************************************************
 * Constructor - Takes a string model
 ******************************************************************/
ArcGameObject::ArcGameObject(std::string modelName)
{
  //std::cout << "Starting Constructor\n";
  mModel = modelName;
  mSize = 1;
  mWeight = 100;
  mDimensions.x = 0;
  mDimensions.y = 0;
  mDimensions.z = 0;
  setPosition(0, 0, 0);
  setRotation(0, 0, 0);
  stop();
  //std::cout << "Finishing Constructor\n";
}

/******************************************************************
 * Sets the current position of an object
 ******************************************************************/
void ArcGameObject::setPosition(float x, float y, float z)
{
  mPosition.x = x;
  mPosition.y = y;
  mPosition.z = z;
}

/******************************************************************
 * Sets the current rotation of an object
 ******************************************************************/
void ArcGameObject::setRotation(float x, float y, float z)
{
  mRotation.x = x;
  mRotation.y = y;
  mRotation.z = z;
}

/******************************************************************
 * Sets the current positional velocity of an object
 ******************************************************************/
void ArcGameObject::setPosVeloc(float x, float y, float z, float w)
{
  mPosVeloc.x = x;
  mPosVeloc.y = y;
  mPosVeloc.z = z;
  mPosVeloc.w = w;
}

/******************************************************************
 * Sets the current rotational velocity of an object
 ******************************************************************/
void ArcGameObject::setRotVeloc(float x, float y, float z, float w)
{
  mRotVeloc.x = x;
  mRotVeloc.y = y;
  mRotVeloc.z = z;
  mRotVeloc.w = w;
}

/******************************************************************
 * Sets the current positional acceleration of an object
 ******************************************************************/
void ArcGameObject::setPosAccel(float x, float y, float z, float w)
{
  mPosAccel.x = x;
  mPosAccel.y = y;
  mPosAccel.z = z;
  mPosAccel.w = w;
}

/******************************************************************
 * Sets the current rotational acceleration of an object
 ******************************************************************/
void ArcGameObject::setRotAccel(float x, float y, float z, float w)
{
  mRotAccel.x = x;
  mRotAccel.y = y;
  mRotAccel.z = z;
  mRotAccel.w = w;
}

/******************************************************************
 * Stops an objects movement
 ******************************************************************/
void ArcGameObject::stop()
{
  // Stop Movement
  setPosVeloc(0, 0, 0, 0);
  setRotVeloc(0, 0, 0, 0);
  // Stop Acceleration
  setPosAccel(0, 0, 0, 0);
  setRotAccel(0, 0, 0, 0);
}
