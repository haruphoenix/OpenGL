#include "ArcModel.h"
#include "ArcWindow.h"
#include "ArcEngine.h"
#include "ArcController.h"
#include "ArcApp.h"

int main(int argc, char** argv)
{
  // Create Model
  ArcModel model;

  // Create Window
  ArcWindow window("Base ArcApp", 600, 400);
  window.initialize();

  // Create Engine
  ArcEngine engine(&window, model.getGraphics());

  // Create Controller
  ArcController controller(&window, model.getControls());
  
  // Create App
  ArcApp app(&model, &engine, &controller);
  
  // Run App
  app.run();

  return 0;
}

