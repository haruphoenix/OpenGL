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
 * Initializes model state
 ******************************************************/
void ArcModel::loadModels(){
  mGraphics.loadModel("data/models/structures/houseX.arcData", "house");
  mGraphics.loadModel("data/models/plants/treeX.arcData", "tree1");
  mGraphics.loadModel("data/models/plants/grass.arcData", "grass");
  mGraphics.loadModel("data/models/misc/dirt.arcData", "dirt");
  mGraphics.loadModel("data/models/misc/lamppost.arcData", "lamppost");
  mGraphics.loadModel("data/models/structures/chapel.arcData", "chapel");
}

/******************************************************
 * Initializes object state
 ******************************************************/
void ArcModel::loadObjects(){

  // Set up House
  ArcGameObject* house = new ArcGameObject("house");
  house->size() = .05;
  house->location().z -= 50;
  mGraphics.registerObject(house);
  mObjects.push_back(house);

  ArcGameObject* chapel = new ArcGameObject("chapel");
  chapel->size() = .05;
  chapel->location().z += 80;
  chapel->location().x += 40;
  chapel->rotation().y = 290;
  mGraphics.registerObject(chapel);
  mObjects.push_back(chapel);


  int size = 50;
  int halfSize = size / 2;
  for (int i = 0; i < size; i++){
    for (int j = 0; j < size; j++){
      ArcGameObject* dirt = new ArcGameObject("dirt");
      dirt->location().z = (i - halfSize) * 8;
      dirt->location().x = (j - halfSize) * 8;
      dirt->size() = 8;
      mGraphics.registerObject(dirt);
      mObjects.push_back(dirt);
    }
  }

  /*
  for (int i = 0; i < size; i++)
    for (int j = 0; j < size; j++){
      ArcGameObject* grass = new ArcGameObject("grass");
      grass->location().z = i - halfSize;
      grass->location().x = j - halfSize;
      grass->location().y += 1;
      grass->rotation().y = rand() % 360;
      mGraphics.registerObject(grass);
      mObjects.push_back(grass);
    }
*/
  
  ArcGameObject* lamppost = new ArcGameObject("lamppost");
  lamppost->size() = 8;
  mGraphics.registerObject(lamppost);
  mObjects.push_back(lamppost);

  for (int i = 0; i < 10; i++){
    ArcGameObject* tree = new ArcGameObject("tree1");
    tree->size() = 10;
    tree->location().x = (((rand() % 2) * 300) - 150) + ((rand() % 200) - 100);
    tree->location().z = (((rand() % 2) * 300) - 150) + ((rand() % 200) - 100);
    //tree->rotation().x = 90;          // This is weird
    mGraphics.registerObject(tree);
    mObjects.push_back(tree);
  }

  // Setup Camera (For some reason, the camera must be done last...)
  ArcGameObject* camera  = new ArcGameObject();
  mGraphics.registerObject(camera);
  mObjects.push_back(camera);
  mGraphics.setCamera(camera);
  setControlObject(camera);

  mControlObject->location().z += 10;
  mControlObject->location().y += 5;
  mGraphics.update(mControlObject);

  ArcLight lamp = { 0, 10, 0,   1, 0.8, 0.5 }; // light yellow
  ArcLight moon = { 0, 30, 0, 0.5, 0.5, 1.0 };
  mGraphics.setLight(1,  moon);
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

//movement *= 4;
//movement /= 10;

// Calculate to keep movement same speed no matter frame rate
//float framerateIndependentFactor = mMovementSpeedFactor * time;

// Apply to movement vector
//movement *= framerateIndependentFactor;

mControlObject->location() += movement;

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
	// Simple
	//mControlObject->location().z -= .001;
        movement |= FORWARD;
	willMove = true;
	break;
      case 's':
	// Simple
	//mControlObject->location().x -= .001;
	willMove = true;
        movement |= LEFT;
        break;
      case 'd':
	// Simple
	//mControlObject->location().z += .001;
	willMove = true;
        movement |= BACKWARD;
        break;
      case 'f':
	// Simple
	//mControlObject->location().x += .001;
	willMove = true;
        movement |= RIGHT;
        break;
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
  if (willMove) mGraphics.update(mControlObject);

  return;
}
