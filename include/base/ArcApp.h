#ifndef ARC_APP
#define ARC_APP

#include "ArcModel.h"
#include "ArcEngine.h"
#include "ArcController.h"

/*************************************************************
 * App contains model-view-controller loop for game
 *************************************************************/
class ArcApp{
 public:
  ArcApp(ArcModel* model, 
	 ArcEngine* engine,
	 ArcController* controller);
  void run();
 private:
  ArcModel* mModel;           // Model (Contains App Data)
  ArcEngine* mEngine;         // View  (Generates view)
  ArcController* mController; // Controller (Gets user input)
};

#endif
