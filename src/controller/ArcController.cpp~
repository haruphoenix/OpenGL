/**********************************************************
 * Implementation of Controller Updates model with user
 * input
 **********************************************************/
#include "ArcController.h"
#include "SDL2/SDL.h"
#include <iostream> // For debugging

/**********************************************************
 * Controller Constructor
 * Input: ArcControlData* Data to modify from input
 **********************************************************/
ArcController::ArcController(ArcWindow* window, 
			     ArcControlData* data){
  mWindow = window->getHandle();
  mData = data;
}


/**********************************************************
 * Scans for user input and updates the model
 **********************************************************/
void ArcController::update(){

  bool mouseChange = false;
  // While there are events to handle
  while (SDL_PollEvent(&mEvent))
  {
    switch (mEvent.type)
    {
       case SDL_QUIT:
	 mData->setQuit(true);
       case SDL_WINDOWEVENT:
	 switch (mEvent.window.event)
	 {
	   case SDL_WINDOWEVENT_RESIZED:
	   {
	     mData->setSize(mEvent.window.data1, 
			    mEvent.window.data2);
	     int x, y;
	     break;
	   }
	   default:
	     break;
	 }
	 break;
       case SDL_MOUSEMOTION:
	 SDL_GetMouseState(&mX, &mY);
	 mData->setMouse(mX, mY);
         mouseChange = true;

	 //getCamera().changeDirection(x, y);
	 break;
       case SDL_KEYDOWN:
         // Handle keypress
	 mData->setKey(mEvent.key.keysym.sym, true);
         break;
       case SDL_KEYUP:
	 mData->setKey(mEvent.key.keysym.sym, false);
	 break;
       case SDL_MOUSEBUTTONDOWN:
	 switch (mEvent.button.button){
	   case SDL_BUTTON_LEFT:
	     mData->setMouseLeft(true);
	     break;
	   case SDL_BUTTON_MIDDLE:
	     mData->setMouseMiddle(true);
	     break;
	   case SDL_BUTTON_RIGHT:
	     mData->setMouseRight(true);
	     break;
	   default:
	     break;
	 }
         break;
       case SDL_MOUSEBUTTONUP:
	 switch (mEvent.button.button){
	   case SDL_BUTTON_LEFT:
	     mData->setMouseLeft(false);
	     break;
	   case SDL_BUTTON_MIDDLE:
	     mData->setMouseMiddle(false);
	     break;
	   case SDL_BUTTON_RIGHT:
	     mData->setMouseRight(false);
	     break;
	   default:
	     break;
	 }
	 break;
       default:
         break;
    }
  }

  // May need to warp mouse to center
  if (mData->trap() && mouseChange){
    int x, y;
    mData->getSize(&x, &y);
    SDL_WarpMouseInWindow(mWindow, 
			    x / 2, 
			    y / 2);
   }
}


/**********************************************************
 * Initializes controller values
 **********************************************************/
void ArcController::initialize(){
  mX = 0;
  mY = 0;
  int x, y;
  SDL_GetWindowSize(mWindow, &x, &y);
  mData->setSize(x, y);
}
