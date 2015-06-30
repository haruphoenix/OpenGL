#ifndef ARC_MODEL
#define ARC_MODEL

#include "ArcControlData.h"
#include "ArcGraphicData.h"
#include "ArcPhysics.h"

/*****************************************************
 * Contains the state of all aspects of the game
 *****************************************************/
class ArcModel{
 public:
  ArcModel();
  ~ArcModel();
  ArcControlData* getControls(); // Access to the controls
  ArcGraphicData* getGraphics(); // Access to the graphics
  void loadModels();
  void loadObjects();
  void update();                 // Update model logic
  bool exit();                   // Valid to quit
  void setControlObject(ArcGameObject* controlObject) { 
    mControlObject = controlObject; };
  ArcGameObject* getControlObject() { return mControlObject; };
 private:
  ArcControlData mControls; // Updated by Controller
  ArcGraphicData mGraphics; // Displayed by Graphic Engine
  ArcPhysics     mPhysics;  // Controls Physics
  bool mExit;               // Valid state to quit
  void checkInput();        // Check ControlData for input
  std::vector<ArcGameObject*> mObjects; // Objects in the game
  ArcGameObject* mControlObject;
  void move(char direction);
  ArcGameObject* createObject(std::string name);
  ArcGameObject* createObject();
};

#endif
