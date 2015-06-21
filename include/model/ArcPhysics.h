/************************************************************************
 * Physics Engine - Makes sure objects do what they are supposed to do
 ************************************************************************/
#ifndef ARC_PHYSICS
#define ARC_PHYSICS
#include <vector>
#include "ArcGameObject.h"

class ArcPhysics {
 public:
  ArcPhysics();
  ~ArcPhysics();
  void registerObject(ArcGameObject* object);
  void update();
  void update(ArcGameObject* object, bool applyGravity = true);
  void setGravity(float value) { mGravity = value; };
 private:
  bool collision(ArcGameObject* left, ArcGameObject* right);
  std::vector<ArcGameObject*> mObjects;
  float mGravity;
};

#endif
