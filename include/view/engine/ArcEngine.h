#ifndef ARC_ENGINE
#define ARC_ENGINE

#include "ArcWindow.h"
#include "ArcGraphicData.h"
#include "ArcShader.h"
#include "ArcGraphicsBridge.h"
#include <GL/glew.h>
#include "ArcMath.h"

/*****************************************************
 * Manages all the graphics for the app. Displays
 * to window.
 *****************************************************/
class ArcEngine{
 public:
  ArcEngine(ArcWindow*, ArcGraphicData*);
  ~ArcEngine();
  bool initialize(); // Initialize Engine
  void update();     // Update Graphics
 private:
  ArcWindow* mWindow;    // Window to draw to
  ArcGraphicData* mData; // Data to draw
  ArcShader mShader; 
  ArcGraphicsBridge mGraphicsBridge;

  //

  //
  void loadShaders();
};

#endif
