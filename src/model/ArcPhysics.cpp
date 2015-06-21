/************************************************************************
 * Physics Engine - Makes sure objects do what they are supposed to do
 ************************************************************************/
#include "ArcPhysics.h"
#include "ArcGameObject.h"
#include <vector>
#include <iostream> // Debugging

/************************************************************************
 * Constructor for physics engine
 ************************************************************************/
ArcPhysics::ArcPhysics()
{
  mGravity = 0.3;
}

/************************************************************************
 * Destructor for physics engine
 ************************************************************************/
ArcPhysics::~ArcPhysics()
{
}


/************************************************************************
 * Registers an object to have physics apply to it
 ************************************************************************/
void ArcPhysics::registerObject(ArcGameObject* object)
{
  mObjects.push_back(object);
}

/************************************************************************
 * Updates all objects
 * Changes velocity based on accelleration
 * Slows accelleration (friction)
 * Further changes velocity and accelleration based on collision
 * detection
 ************************************************************************/
void ArcPhysics::update()
{

}

/************************************************************************
 * Updates all objects due to the effects of a single object
 ************************************************************************/
void ArcPhysics::update(ArcGameObject* object, bool applyGravity)
{
  //std::cout << "Velocity: " << object->posVeloc().x << " " << object->posVeloc().y << " " << object->posVeloc().z << std::endl;

  // Increase Velocity According to acceleration
  object->posVeloc().x += object->posAccel().x;
  object->posVeloc().y += object->posAccel().y;
  object->posVeloc().z += object->posAccel().z;

  // Decrement Acceleration or return to zero when velocity reaches zero
  object->posAccel().x = (object->posAccel().x * 0.5);
  object->posAccel().y = (object->posAccel().y * 0.5);
  object->posAccel().z = (object->posAccel().z * 0.5);

  //std::cout << "Acceleration: " << object->posAccel().x << " " << object->posAccel().y << " " << object->posAccel().z << std::endl;

  //if (object->posAccel().x == 0 && object->posAccel().y == 0 && object->posAccel().z == 0)
  //  std::cout << "Stop\n";
  //else
  //  std::cout << "Go\n";

  // Apply Velocity to position
  object->position().x += object->posVeloc().x;
  object->position().y += object->posVeloc().y;
  object->position().z += object->posVeloc().z;

  //std::cout << "changing position\n";

  //object->posAccel().y -= mGravity;
  //object->position().x += object->posAccel().x;
  //object->position().y += object->posAccel().y;
  //object->position().z += object->posAccel().z;

  if (object->posVeloc().x || object->posVeloc().y || object->posVeloc().z){
  // Revert in the case of collision (velocity and acceleration go to zero
  // in the direction of the collision)
  for (int i = 0; i < mObjects.size(); i++){
    if (collision(object, mObjects[i])){
      object->position().y -= object->posVeloc().y;
      object->posVeloc().y = 0;
      object->posAccel().y = 0;
      if (collision(object, mObjects[i])){
	object->position().z -= object->posVeloc().z;
	object->posVeloc().z = 0;
	object->posAccel().z = 0;
	if (collision(object, mObjects[i])){
	  object->position().x -= object->posVeloc().x;
	  object->posVeloc().x = 0;
	  object->posAccel().x = 0;
	}
      }
      //object->position().x -= object->posAccel().x;
      //object->position().y -= object->posAccel().y;
      //object->position().z -= object->posAccel().z;
      //std::cout << "Collision\n";
      break;
    }
  }
  }

  //object->posAccel().x = 0;
  //object->posAccel().y = 0;
  //object->posAccel().z = 0;

  // Apply gravity to acceleration
  object->posAccel().y -= mGravity;

  // Apply friction
  object->posVeloc().x = (object->posVeloc().x * 0.5);
  object->posVeloc().y = (object->posVeloc().y * 0.5);
  object->posVeloc().z = (object->posVeloc().z * 0.5);
}


/************************************************************************
 * Checks to see if two objects collide
 ************************************************************************/
bool ArcPhysics::collision(ArcGameObject* left, ArcGameObject* right)
{
  if (left == right) return false; // Don't compare the same object

  struct collisionChecker{
    float LA; float LB; float UA; float UB;
    bool checkCollision(){
      return (((LA <= LB) && (UA >= LB)) || // A Overlaps B
	      ((LA <= UB) && (UA >= UB)) || // B Overlaps A
	      ((LA <= LB) && (UA >= UB)) || // A Inside B
	      ((LA >= LB) && (UA <= UB)));  // B Inside A
    }
  } X, Y, Z;

  // Check to see if objects occupy the same space on the X axis
  X.LA = left->position().x  - left->dimensions().x;
  X.UA = left->position().x  + left->dimensions().x;
  X.LB = right->position().x - right->dimensions().x;
  X.UB = right->position().x + right->dimensions().x;
  if (X.checkCollision()){
    // Check to see if objects occupy the same space on the Y axis
    Y.LA = left->position().y  - left->dimensions().y;
    Y.UA = left->position().y  + left->dimensions().y;
    Y.LB = right->position().y - right->dimensions().y;
    Y.UB = right->position().y + right->dimensions().y;
    if (Y.checkCollision()){
      // Check to see if objects occupy the same space on the Z axis
      Z.LA = left->position().z  - left->dimensions().z;
      Z.UA = left->position().z  + left->dimensions().z;
      Z.LB = right->position().z - right->dimensions().z;
      Z.UB = right->position().z + right->dimensions().z;
      if (Z.checkCollision())
	return true; // There was a collision
    }
  }
  return false; // There wasn't a collision
}
