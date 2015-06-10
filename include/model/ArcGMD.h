/****************************************************************
 * Graphical Model Data (GMD) - Holds the graphic data of a
 * Game Object
 ****************************************************************/
#ifndef ARC_GMD
#define ARC_GMD

#include <GL/glew.h>
#include <ArcGOD.h>
#include <vector>
#include <string>

class ArcGMD{

 public:

  ArcGMD();
  ArcGMD(const char* filename);
  ~ArcGMD();
  void       loadData(const char* filename);
  float*     getVertices()      { return mVertices;    };
  GLuint*    getIndices()       { return mIndices;     };
  int        getNumVertices()   { return mNumVertices; };
  int        getNumIndices()    { return mNumIndices;  };
  ArcGC&     getSet()           { return mSet;         };
  ArcTexSet& getTextures()      { return mTexSet;      };

 private:

  float*    mVertices; // Includes vertices, colors, texture coords, & normals
  GLuint*   mIndices;
  int       mNumVertices;
  int       mNumMaterials;
  int       mNumIndices;
  ArcGC     mSet;
  ArcTexSet mTexSet;
};

#endif
