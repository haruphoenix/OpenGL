#include "ArcTexture.h"
#include <SDL2/SDL_image.h>
#include <GL/glew.h>
#include <iostream> // Debugging
#include <string>

// Helper Methods - Courtesy of Jordan Reed
Uint32 get_pixel32(SDL_Surface *surface, int x, int y);
void put_pixel32(SDL_Surface *surface, int x, int y, Uint32 pixel);
SDL_Surface *flip_surface(SDL_Surface *surface, int flags);

/*********************************************************************
 * Constructor
 *********************************************************************/
ArcTexture::ArcTexture(std::string filename)
{
  // Prepend directory
  std::string prefix1 = "data/textures/plants/";
  std::string prefix2 = "data/textures/structures/";
  std::string prefix3 = "data/textures/misc/";

  // Load Surface
  mSurface = IMG_Load((prefix1 + filename).c_str());
  if (mSurface == NULL) mSurface = IMG_Load((prefix2 + filename).c_str());
  if (mSurface == NULL) mSurface = IMG_Load((prefix3 + filename).c_str()); 
  if (mSurface == NULL) std::cout << "IMG_LOAD Failed\n";       

  // Check Extension
  std::string extension = filename.substr(filename.find_last_of(".") + 1);

  // Does the texture use Alpha?
  if (mSurface->format->BytesPerPixel == 4){
    if (extension == "tga"){
      mFormat = GL_BGRA;
      mInternalFormat = GL_RGBA;
    }
    else {
      mFormat = GL_RGBA;
      mInternalFormat = GL_RGBA;
    }
  }
  else {
    if (extension == "tga"){
      mFormat = GL_BGR;
      mInternalFormat = GL_RGB;
    }
    else {
      mFormat = GL_RGB;
      mInternalFormat = GL_RGB;
    }
  }

  //SDL_Surface* flipped = flip_surface(mSurface, 0);
  //SDL_free(mSurface);
  //mSurface = flipped;
}

/*********************************************************************
 * Destructor
 *********************************************************************/
ArcTexture::~ArcTexture()
{
  SDL_free(mSurface); 
}


/*********************************************************************/



/*********************************************************************
 * Get Pixel - Courtesy of Jordan
 *********************************************************************/
Uint32 get_pixel32(SDL_Surface *surface, int x, int y)
{
    Uint32 *pixels = (Uint32 *)surface->pixels;
    return pixels[(y * surface->w) + x];
}


/*********************************************************************
 * Put Pixel - Courtesy of Jordan
 *********************************************************************/
void put_pixel32(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    Uint32 *pixels = (Uint32 *)surface->pixels;
    pixels[(y * surface->w ) + x] = pixel;
}


/*********************************************************************
 * Flip Surface - Courtesy of Jordan
 *********************************************************************/
SDL_Surface *flip_surface(SDL_Surface *surface, int flags)
{
    SDL_Surface *flipped = SDL_CreateRGBSurface(SDL_SWSURFACE, surface->w, surface->h,
                                                surface->format->BitsPerPixel,
                                                surface->format->Rmask,
                                                surface->format->Gmask,
                                                surface->format->Bmask,
                                                surface->format->Amask);
    if (SDL_MUSTLOCK(surface)) SDL_LockSurface(surface);
    for (int x = 0, rx = flipped->w - 1; x < flipped->w; x++, rx--)
    {
        for (int y = 0, ry = flipped->h - 1; y < flipped->h; y++, ry--)
        {
            Uint32 pixel = get_pixel32(surface, x, y);
            //put_pixel32(flipped, rx, y, pixel);
            put_pixel32(flipped, x, ry, pixel);
        }
    }
    if (SDL_MUSTLOCK(surface)) SDL_UnlockSurface(surface);
    return flipped;
}
