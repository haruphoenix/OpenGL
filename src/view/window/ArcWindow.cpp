#include "ArcWindow.h"

/*****************************************************
 * Constructor - sets the window title and dimensions
 *****************************************************/
ArcWindow::ArcWindow(const char* title, int w, int h)
{
  mTitle = title;
  mWidth = w;
  mHeight = h;
}

/*****************************************************
 * Destructor - Closes SDL
 *****************************************************/
ArcWindow::~ArcWindow()
{
  SDL_GL_DeleteContext(mContext);
  SDL_DestroyWindow(mWindow);
  SDL_Quit();
}

/*****************************************************
 * Initializes SDL, creates the window
 *****************************************************/
bool ArcWindow::initialize()
{
  // Attempt to initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO)) return false;
  
  SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
  


  mWindow = SDL_CreateWindow(mTitle,
			     SDL_WINDOWPOS_CENTERED,
			     SDL_WINDOWPOS_CENTERED,
			     mWidth, mHeight,
			     SDL_WINDOW_OPENGL |
			     SDL_WINDOW_SHOWN |
			     SDL_WINDOW_RESIZABLE);
  if (!mWindow) return false;
  mContext = SDL_GL_CreateContext(mWindow);
  if (mContext == NULL) return false;

  SDL_GL_MakeCurrent(mWindow, mContext);
  
  
  SDL_GL_SetSwapInterval(1);

  
  return true;
}

/*****************************************************
 * Resizes the window
 *****************************************************/
void ArcWindow::resize(int w, int h)
{
  mWidth = w;
  mHeight = h;
  SDL_SetWindowSize(mWindow, mWidth, mHeight);
}

/*****************************************************
 * Updates the window
 *****************************************************/
void ArcWindow::update()
{
  SDL_GL_SwapWindow(mWindow);
}
