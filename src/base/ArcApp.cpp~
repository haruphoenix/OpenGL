/*************************************************************
 * Implementation for App (Runs loop for model-view-controller)
 *************************************************************/
#include "ArcApp.h"

/*************************************************************
 * Constructor for App
 * Input: ArcModel*      - Model to update
 *        ArcEngine*     - Engine to handle graphics
 *        ArcController* - Controller to get User Input
 *************************************************************/
ArcApp::ArcApp(ArcModel* model, ArcEngine* engine,
	       ArcController* controller){
  mModel      = model;
  mEngine     = engine;
  mController = controller;
}

/************************************************************
 * Runs the app
 ************************************************************/
void ArcApp::run(){
  // Initialize Components
  mModel->loadModels();
  mController->initialize();
  if (!mEngine->initialize()) return;
  mModel->loadObjects();

  // Run loop until told to quit
  while (!mModel->exit()){
    mController->update();
    mModel->update();
    mEngine->update();
  }
}
