/******************************************************************
 * Graphic Object Data
 * Data describes a specific game object
 * Includes the graphic model ID and a transform matrix
 ******************************************************************/
#ifndef ARC_GOD
#define ARC_GOD

#include <GL/glew.h>
#include "ArcMath.h"
#include <string>

// ID set describing location of data on GPU
struct ArcIDSet{
  GLuint VertexVBO;
  GLuint IBO;
};

// Holds 3 Texture Ids
struct ArcTextureIDSet{
  GLuint Ka;
  GLuint Kd;
  GLuint Ks;
};

// Holds 3 Texture names
struct ArcTextureNameSet{
  std::string Ka;
  std::string Kd;
  std::string Ks;
};

// Holds Data Needed to know how a part of an object should be drawn
struct ArcGraphicController{
  ArcTextureIDSet texture;  // Textures - ambient, diffuse, specular
  int offset;         // Indices
  int numIndices;     // Indices
  float material[10]; // Material array - ambient, diffuse, specular, trans.
};

#ifndef ARC_MAX_LIGHTS
#define ARC_MAX_LIGHTS 10
#endif

// Holds Light Data
struct ArcLight{
  float x;
  float y;
  float z;
  float r;
  float g;
  float b;
};

#include <vector>
typedef std::vector<ArcGraphicController> ArcGC;
typedef std::vector<ArcTextureNameSet> ArcTexSet;

// Contains main ID (VAO), and a list of Controls
// that describe how the object should be drawn -> Required to draw
// object (Graphic Model Pointer)
struct ArcGMP{
  GLuint ID; // VAO (Vertex Data)
  ArcGC set; // Material, texture, & bounds (indices)
};


struct ArcGOD{
  ArcGMP model;
  ArcMatrix transformMatrix;
};

#endif
