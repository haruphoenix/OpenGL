/********************************************************************
 * Class is a wrapper for Textures to be used with opengl
 ********************************************************************/
#ifndef ARC_TEXTURE
#define ARC_TEXTURE
#include <SDL2/SDL_image.h>
#include <string>

class ArcTexture{
 public:
  ArcTexture(std::string filename);
  ~ArcTexture();
  int format() { return mFormat;          };
  int height() { return mSurface->h;      } ;
  int width()  { return mSurface->w;      } ;
  void* data() { return mSurface->pixels; } ;
  int internalFormat() { return mInternalFormat; }; 
 private:
  SDL_Surface* mSurface;
  int mFormat;
  int mInternalFormat;
};

#endif
