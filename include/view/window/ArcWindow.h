#ifndef ARC_WINDOW
#define ARC_WINDOW

#include <SDL2/SDL.h>

/***********************************
 * Creates window and OpenGL context
 * using SDL
 ***********************************/
class ArcWindow
{
 public:
  ArcWindow(const char* title, int w, int h);
  ~ArcWindow();
  bool initialize();
  void resize(int w, int h);
  void update();
  SDL_Window* getHandle() { return mWindow; };
 private:
  SDL_Window* mWindow;
  SDL_GLContext mContext;
  int mWidth;
  int mHeight;
  const char* mTitle;
};

#endif
