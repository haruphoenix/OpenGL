/*****************************************************
 * Implementation of the Graphic Data
 *****************************************************/
#include "ArcGraphicData.h"
#include "ArcTexture.h"
#include <iostream> // Debug

/*****************************************************
 * Constructor for graphic data
 *****************************************************/
ArcGraphicData::ArcGraphicData(){
  mWindowX = 0;
  mWindowY = 0;
  mWindowChange = false;
  mCamera = NULL;
  mCameraMatrix = IDENTITY_MATRIX;
  // Create Empty Model
  NO_MODEL.ID = 0;
  ArcGraphicController temp;
  NO_MODEL.set.push_back(temp);
  // Turn Off Lights
  ArcLight off = { 0, 0, 0, 0, 0, 0 };
  for (int i = 0; i < ARC_MAX_LIGHTS; i++) mLights[i] = off;
  
  // Test
  /*
  for (int i = 0; i < 10; i++){
    std::cout << "Light " << i << " is "
	      << mLights[i].x << " "
	      << mLights[i].y << " "
	      << mLights[i].z << " "
	      << mLights[i].r << " "
	      << mLights[i].g << " "
	      << mLights[i].b << std::endl;
  }
  */

  // Set Fog to be off
  ArcFog fog = { 0, 0, 0, 0 }; // Gray
  mFog = fog;
}

/*****************************************************
 * Destructor for graphic data
 *****************************************************/
ArcGraphicData::~ArcGraphicData()
{
}

/*****************************************************
 * Call to resize the window to x and y dimensions
 *****************************************************/
void ArcGraphicData::resizeWindow(int x, int y)
{
  mWindowX = x;
  mWindowY = y;
  mWindowChange = true;
}

/*****************************************************
 * Get window change. returns true if there has been
 * a change. changes x and y by reference
 *****************************************************/
bool ArcGraphicData::windowChange(int& x, int& y)
{
  if (mWindowChange)
  {
    x = mWindowX;
    y = mWindowY;
    mWindowChange = false;
    return true;
  }
  return false;
}

// ----------------------------Model Loading----------------------------
// Models to upload onto the GPU at the start of a program


/***********************************************************************
 * Load a graphic model to put onto the GPU
 ***********************************************************************/
void ArcGraphicData::loadModel(const char* filename, std::string name)
{
  try {
   mModels[name] = new ArcGMD(filename);
  } catch (std::bad_alloc) {
    std::cout << "Error: Could not allocate memory for ArcGMD in "
	      << "load model\n";
    exit(1);
  }
}

/***********************************************************************
 * Removes Graphic Data
 ***********************************************************************/
void ArcGraphicData::clearData()
{
  // Delete models
  std::map<std::string, ArcGMD*>::iterator i;
  for (i = mModels.begin(); i != mModels.end(); ++i){
    delete i->second;
  }
}

// --------------------------Model Registering--------------------------

/***********************************************************************
 * Registers and associates a name with a given graphical model
 ***********************************************************************/
void ArcGraphicData::registerModel(ArcGMP GMP, std::string name)
{
  mIDMap[name] = GMP;
}


/***********************************************************************
 * Sets one of the lights
 ***********************************************************************/
void ArcGraphicData::setLight(int number, ArcLight light){
  if (number > 0 && number < ARC_MAX_LIGHTS)
    mLights[number] = light;
}


/***********************************************************************
 * Sets The level of fog from the user's perspective
 ***********************************************************************/
void ArcGraphicData::setFog(float r, float g, float b, float a)
{
  mFog.r = r;
  mFog.g = g;
  mFog.b = b;
  mFog.a = a;
}

// ---------------------------Texture Loading---------------------------
// Textures to upload onto the GPU at the start of a program


/***********************************************************************
 * Load a graphic model to put onto the GPU
 ***********************************************************************/
void ArcGraphicData::loadTexture(const char* filename, std::string name)
{
  try {
    mTextures[name] = new ArcTexture(filename);
  } catch (std::bad_alloc) {
    std::cout << "Error: Could not allocate memory for ArcGMD in "
	      << "load model\n";
    exit(1);
  }
}

// -------------------------Texture Registering-------------------------

/***********************************************************************
 * Registers and associates a name with a given texture
 ***********************************************************************/
void ArcGraphicData::registerTexture(GLuint texture, std::string name)
{
  mTexMap[name] = texture;
}


// --------------------------Object Registering-------------------------

/***********************************************************************
 * Ties a game object to one of the registered models
 ***********************************************************************/
void ArcGraphicData::registerObject(ArcGameObject* object)
{
  object->ID = mObjects.size();
  ArcGOD graphicObjectData;
  mObjects.push_back(graphicObjectData);
  update(object);
}

// ---------------------------Object Updating---------------------------

/***********************************************************************
 * Use to update the graphics for the object which has changed state
 ***********************************************************************/
void ArcGraphicData::update(ArcGameObject* object)
{
  /*
  std::cout << "Ptr in Graphic Data = " << (long)mLights << std::endl;
  for (int i = 0; i < 10; i++){
    std::cout << "Light " << i << " is "
	      << mLights[i].x << " "
	      << mLights[i].y << " "
	      << mLights[i].z << " "
	      << mLights[i].r << " "
	      << mLights[i].g << " "
	      << mLights[i].b << std::endl;
  }
  */

  // Retrieve object graphics
  ArcGOD* graphicObjectData = &(mObjects[object->ID]);

  // Update Object Model
  if (object->model() != "")
    graphicObjectData->model = mIDMap[object->model()];
  else
    graphicObjectData->model = NO_MODEL; // No Model

  // Update ArcGOD Transform Matrix
  graphicObjectData->transformMatrix = IDENTITY_MATRIX;
  ScaleMatrix(&(graphicObjectData->transformMatrix), object->size(),
	      object->size(), object->size());
  RotateAboutY(&(graphicObjectData->transformMatrix), 
	       DegreesToRadians(object->rotation().y));
  RotateAboutX(&(graphicObjectData->transformMatrix), 
	       DegreesToRadians(object->rotation().x));
  RotateAboutZ(&(graphicObjectData->transformMatrix), 
	       DegreesToRadians(object->rotation().z));
  TranslateMatrix(&(graphicObjectData->transformMatrix),
		  object->position().x, object->position().y,
		  object->position().z);
  
  if (graphicObjectData != mCamera) return;
  // Camera
  // Translate First
  mCameraLocationMatrix = graphicObjectData->transformMatrix;
  mCameraMatrix = IDENTITY_MATRIX;
  TranslateMatrix(&mCameraMatrix,
		  -object->position().x, -object->position().y,
		  -object->position().z);
  RotateAboutY(&mCameraMatrix, 
	       DegreesToRadians(object->rotation().y));
  RotateAboutX(&mCameraMatrix, 
	       DegreesToRadians(object->rotation().x));
  RotateAboutZ(&mCameraMatrix, 
	       DegreesToRadians(object->rotation().z));
  
  return;
}


/***********************************************************************
 * Sets a game object to be the camera - point of view in the game
 ***********************************************************************/
void ArcGraphicData::setCamera(ArcGameObject* object)
{
  mCamera = &(mObjects[object->ID]);
}
