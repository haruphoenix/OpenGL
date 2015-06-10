/****************************************************************
 * Graphical Model Data (GMD) - Holds the graphic data of a
 * Game Object
 ****************************************************************/
#include "ArcGMD.h"
#include <fstream>
#include <iostream> // Debug
#include <vector>
#include <string>

/****************************************************************
 * General Constructor. 
 ****************************************************************/
ArcGMD::ArcGMD()
{
  mVertices = 0;
  mIndices  = 0;
  mNumVertices = 0;
  mNumIndices  = 0;
}

/****************************************************************
 * Constructor. Loads graphic data from a file 
 ****************************************************************/
ArcGMD::ArcGMD(const char* filename)
{
  mVertices = 0;
  mIndices = 0;
  mNumVertices = 0;
  mNumIndices = 0;
  loadData(filename);
}


/****************************************************************
 * Loads graphic data from a file
 ****************************************************************/
void ArcGMD::loadData(const char* filename)
{
  // Delete old data
  if (mVertices)
    delete mVertices;
  if (mIndices)
    delete mIndices;

  // Open File
  std::ifstream fin;
  fin.open(filename); 
  if (fin.fail()) return;

  // Get Vertices
  fin >> mNumVertices;
  mVertices = new float[mNumVertices * 8];
  for (int i = 0; i < mNumVertices * 8; i++)
    fin >> mVertices[i];

  // Get Material Data
  fin >> mNumMaterials;
  int offset = 0;
  ArcGraphicController temp;
  ArcTextureNameSet textures;
  for (int i = 0; i < mNumMaterials; i++){
    // Calculate Bounds
    temp.offset = offset;
    fin >> temp.numIndices;
    offset += temp.numIndices;
    // Read Materials
    for (int i = 0; i < 10; i++){
      fin >> temp.material[i];
    }
    // Read Texture Files
    fin >> textures.Ka;
    fin >> textures.Kd;
    fin >> textures.Ks;
    mTexSet.push_back(textures);
    mSet.push_back(temp);
  }

  // Get Indices
  fin >> mNumIndices;
  mIndices = new GLuint[mNumIndices];
  for (int i = 0; i < mNumIndices; i++)
    fin >> mIndices[i];

  // Close File
  fin.close();
}

/****************************************************************
 * Destructor. Deletes Data
 ****************************************************************/
ArcGMD::~ArcGMD()
{
  if (mVertices)
    delete mVertices;
  if (mIndices)
    delete mIndices;
}
