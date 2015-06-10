/*******************************************************
 * Implementation of graphics engine. Draws data from
 * model to window.
 *******************************************************/
#include "ArcEngine.h"
#include "ArcGMD.h"
#include "GL/glew.h"
#include <iostream>

/*******************************************************
 * ArcEngine Constructor
 * Input: ArcWindow*      Window to draw to
 *        ArcGraphicData* Data to draw
 *******************************************************/
ArcEngine::ArcEngine(ArcWindow* window, ArcGraphicData* data){
  mWindow = window;
  mData = data;
}

/*******************************************************
 * Destructor
 *******************************************************/
ArcEngine::~ArcEngine(){
}

#include <iostream>

/*******************************************************
 * Initializes the engine
 *******************************************************/
bool ArcEngine::initialize(){
  glewExperimental = GL_TRUE;
  
  // Initialize GLEW
  GLenum GlewInitResult = glewInit();
  if (GLEW_OK != GlewInitResult){
    std::cout << "Error: " 
	      << glewGetErrorString(GlewInitResult);
    return false;
  }

  // Print Version
  fprintf(stdout, "INFO: OpenGL Version: %s\n",
	  glGetString(GL_VERSION));

  // Clear any errors
  glGetError();

  // Load Shaders
  loadShaders();


  // Put Data onto the GPU
  mGraphicsBridge.loadGraphicData(*mData);


  // Set Clear color
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  
  // Enable Depth Buffering
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  // Enable Backface culling
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  glFrontFace(GL_CCW);

  // Blending
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  // Check for Errors
  GLenum ErrorCheckValue = glGetError();
  if (ErrorCheckValue != GL_NO_ERROR){
    fprintf(stderr, "ERROR: Could not initialize graphics engine: %s\n\n", 
	    gluErrorString(ErrorCheckValue));
    exit(1);
  }
  return true;
}

/*******************************************************
 * Updates the view based on graphic data
 *******************************************************/
void ArcEngine::update(){
  int x;
  int y;
  // Check for window resize
  if (mData->windowChange(x, y)){
    glViewport(0, 0, x, y);
    mWindow->resize(x, y);
    mShader.setProjection(CreateProjectionMatrix(60,
    						 (float)x / y,
    						 1.0f,
    						 1000.0f));
  }

  // Clear Buffers
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Set Camera Location
  mShader.setView(mData->getCameraMatrix());

  // Set Lights
  mShader.setLights(mData->getLights());

  // Draw the objects
  std::vector<ArcGOD>* objects = &mData->objects();
  std::vector<ArcGOD>::iterator object;
  for (object = objects->begin(); object != objects->end(); object++)
    mShader.draw(*object);

  // Update Window
  mWindow->update();
}


/*******************************************************
 * Create Shaders
 *******************************************************/
void ArcEngine::loadShaders(){
  mShader.initialize();
  mShader.addVertexShader("data/shaders/matVert.glsl");
  mShader.addFragmentShader("data/shaders/matFrag.glsl");
  mShader.link();
  mShader.use();
}





