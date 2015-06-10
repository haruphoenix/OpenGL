#ifndef ARC_CONTROLLER
#define ARC_CONTROLLER

#include "ArcControlData.h"
#include "SDL2/SDL.h"
#include "ArcWindow.h"

/**********************************************************
 * Manages user input and puts it into the model
 **********************************************************/
class ArcController{
 public:
  ArcController(ArcWindow* window, ArcControlData* data);
  void update(); // Scan for user input
  void initialize(); 
 private:
  SDL_Window* mWindow;   // Window 
  ArcControlData* mData; // Data to control
  SDL_Event mEvent;      // Event Holder
  int mX;                // mouseX Holder 
  int mY;                // mouseY Holder
};

#endif
