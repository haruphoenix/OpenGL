/******************************************************
 * Implementation of ArcModel (State of the game)
 ******************************************************/
#include "ArcModel.h"
#include "ArcMath.h"
#include <cmath>
#include <cstdlib>
#include <iostream> // Debug

/******************************************************
 * Constructor for model.
 ******************************************************/
ArcModel::ArcModel(){
  mExit = false;
}

/******************************************************
 * Destructor for model.
 ******************************************************/
ArcModel::~ArcModel(){
  std::vector<ArcGameObject*>::iterator i;
  for (i = mObjects.begin(); i != mObjects.end(); ++i)
    delete *i;
}

/******************************************************
 * Gives access to the controls for the app model
 ******************************************************/
ArcControlData* ArcModel::getControls(){
  return &mControls;
}

/******************************************************
 * Gives access to the graphic state of the app model
 ******************************************************/
ArcGraphicData* ArcModel::getGraphics(){
  return &mGraphics;
}

/******************************************************
 * Initializes models
 ******************************************************/
void ArcModel::loadModels(){
  mGraphics.loadModel("data/models/structures/houseX.arcData", "house");
  mGraphics.loadModel("data/models/plants/treeX.arcData", "tree1");
  mGraphics.loadModel("data/models/misc/lamppost.arcData", "lamppost");
  mGraphics.loadModel("data/models/structures/chapel.arcData", "chapel");
  mGraphics.loadModel("data/models/background/night.arcData", "sky");
  mGraphics.loadModel("data/models/background/grass1.arcData", "grass1");
  mGraphics.loadModel("data/models/creatures/cat.arcData", "cat");
}

/******************************************************
 * Initializes object state
 ******************************************************/
void ArcModel::loadObjects(){

  // make sky
  ArcGameObject* sky = new ArcGameObject("sky");
  sky->size() = 30;
  mGraphics.registerObject(sky);
  mObjects.push_back(sky);

  // Set up House
  ArcGameObject* house = new ArcGameObject("house");
  house->size() = .05;
  house->position().z -= 50;
  house->dimensions().y = 15;
  house->dimensions().x = 28;
  house->dimensions().z = 25;
  mPhysics.registerObject(house);
  mGraphics.registerObject(house);
  mObjects.push_back(house);

  ArcGameObject* cat = new ArcGameObject("cat");
  cat->size() = 3;
  cat->position().z -= 50;
  cat->position().y = 26;
  cat->position().x -= 18;
  cat->rotation().y = 90;
  mGraphics.registerObject(cat);
  mObjects.push_back(cat);

  ArcGameObject* chapel = new ArcGameObject("chapel");
  chapel->size() = .05;
  chapel->position().z += 80;
  chapel->position().x += 40;
  chapel->rotation().y = 290;
  chapel->dimensions().x = 50;
  chapel->dimensions().y = 50;
  chapel->dimensions().z = 50;
  //mPhysics.registerObject(chapel); // Collision detection still can't handle rotation
  mGraphics.registerObject(chapel);
  mObjects.push_back(chapel);

  ArcGameObject* ground = new ArcGameObject();
  ground->dimensions().x = 1000;
  ground->dimensions().z = 1000;
  mPhysics.registerObject(ground);

  int size = 50;
  int halfSize = size / 2;
  for (int i = 0; i < size; i++){
    for (int j = 0; j < size; j++){
      ArcGameObject* grass = new ArcGameObject("grass1");
      grass->position().z = (i - halfSize) * 8;
      grass->position().x = (j - halfSize) * 8;
      grass->size() = 8;
      //grass->dimensions().x = 8;
      //grass->dimensions().z = 8;
      //mPhysics.registerObject(grass);
      mGraphics.registerObject(grass);
      mObjects.push_back(grass);
    }
  }
  
  ArcGameObject* lamppost = new ArcGameObject("lamppost");
  lamppost->size() = 8;
  lamppost->dimensions().z = 0.5;
  lamppost->dimensions().x = 0.5;
  lamppost->dimensions().y = 12;
  mPhysics.registerObject(lamppost);
  mGraphics.registerObject(lamppost);
  mObjects.push_back(lamppost);

  for (int i = 0; i < 10; i++){
    ArcGameObject* tree = new ArcGameObject("tree1");
    tree->size() = 10;
    tree->position().x = (((rand() % 2) * 300) - 150) + ((rand() % 200) - 100);
    tree->position().z = (((rand() % 2) * 300) - 150) + ((rand() % 200) - 100);
    //tree->rotation().x = 90;          // This is weird
    mGraphics.registerObject(tree);
    mObjects.push_back(tree);
  }

  // Setup Camera (For some reason, the camera must be done last...)
  ArcGameObject* camera  = new ArcGameObject();
  camera->dimensions().x = 1;
  camera->dimensions().z = 1;
  camera->dimensions().y = 6;
  mPhysics.registerObject(camera);
  mGraphics.registerObject(camera);
  mObjects.push_back(camera);
  mGraphics.setCamera(camera);
  setControlObject(camera);

  mControlObject->position().z += 10;
  mControlObject->position().y += 15;
  mGraphics.update(mControlObject);

  // Create Lights
  ArcLight lamp = { 0, 10,    0,   1, 0.8, 0.5 };  // light yellow
  ArcLight moon = { 30, 150, 250, 0.5, 0.5, 0.5 }; // silver
  mGraphics.setLight(1, moon);
  mGraphics.setLight(2, lamp);

  update();

  // Set up warp
  mControls.setTrap(true);
}

/******************************************************
 * Update model logic
 ******************************************************/
void ArcModel::update(){
  checkInput();
  mPhysics.update(mControlObject);
  mGraphics.update(mControlObject);
}

/******************************************************
 * Returns bool exit (Whether the app is allowed to
 * close)
 ******************************************************/
bool ArcModel::exit(){
  return mExit;
}

#include <iostream>
#define FORWARD 1
#define BACKWARD 2
#define RIGHT 4
#define LEFT 8

/******************************************************
 * Moves the control object in the direction its facing
 ******************************************************/
void ArcModel::move(char direction)
{
  ArcVector rotation = mControlObject->rotation();
  ArcVector movement;
  zero(movement);

  
  // Prepare for advanced movement...
  float sinXRot = (float)sin(DegreesToRadians(rotation.x));
  float cosXRot = (float)cos(DegreesToRadians(rotation.x));
  float sinYRot = (float)sin(DegreesToRadians(rotation.y));
  float cosYRot = (float)cos(DegreesToRadians(rotation.y));

float pitchLimitFactor = cosXRot;

if (FORWARD & direction){
  movement.x += (sinYRot * pitchLimitFactor);
  movement.y -= (-sinXRot);
  movement.z += (-cosYRot * pitchLimitFactor);
}

if (BACKWARD & direction){
  movement.x += (-sinYRot * pitchLimitFactor);
  movement.y -= sinXRot;
  movement.z += (cosYRot * pitchLimitFactor);
}

if (LEFT & direction){
  movement.x += -cosYRot;
  movement.z += -sinYRot;
}

if (RIGHT & direction){
  movement.x += cosYRot;
  movement.z += sinYRot;
}

normalize(movement);

movement /= 4;
//movement /= 10;

// Calculate to keep movement same speed no matter frame rate
//float framerateIndependentFactor = mMovementSpeedFactor * time;

// Apply to movement vector
//movement *= framerateIndependentFactor;

 movement.y = 0;

//mControlObject->position() += movement;
 mControlObject->posAccel() += movement;
}

/******************************************************
 * Take into account user input
 ******************************************************/
void ArcModel::checkInput(){

  int x;
  int y;
  if (mControls.quit()){
    mExit = true;
    return;
  }
  if (mControls.getSize(&x, &y)){
    mGraphics.resizeWindow(x, y);
  }

  bool willMove = false;
  // Handle Mouse Positions
  int a, b;
  if (mControls.getMouse(&a, &b)){
    mControlObject->rotation().y -= ((x / 2) - a) / 10;
    mControlObject->rotation().x += ((y / 2) - b) / 10;
    // Limit looking up and down
    if (mControlObject->rotation().x < -90)
      mControlObject->rotation().x = -90;
    if (mControlObject->rotation().x > 90)
      mControlObject->rotation().x = 90;
    // Revolve around
    if (mControlObject->rotation().y < 0)
      mControlObject->rotation().y += 360;
    if (mControlObject->rotation().y > 360)
      mControlObject->rotation().y -= 360;
    willMove = true;
  }

  char movement = 0;

  // Handle Keys
  char c;
  do{
    //std::cout << "A\n";
    c = (mControls.getNextKey());
    //std::cout << "D\n";
    switch (c){
      case 'q':
        mExit = true;
        break;
      case 'e':
        movement |= FORWARD;
	willMove = true;
	break;
      case 's':
	willMove = true;
        movement |= LEFT;
        break;
      case 'd':
	willMove = true;
        movement |= BACKWARD;
        break;
      case 'f':
	willMove = true;
        movement |= RIGHT;
        break;
      case 32: // space
	mControlObject->posAccel().y += 0.5;
      default:
        break;
    }
  } while (c != '\0');

  if (mControls.getMouseLeft()){
    //mGraphics.setCamera(camera);
    //setControlObject(camera);
  }
  if (mControls.getMouseMiddle()){
    //mGraphics.setCamera(moon);
    //setControlObject(moon);
  }
  if (mControls.getMouseRight()){
  }

  if (movement) move(movement);
  //if (willMove) mGraphics.update(mControlObject);

  return;
}
