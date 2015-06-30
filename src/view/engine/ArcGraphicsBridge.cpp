/******************************************************************
 * This is the implemention file for the ArcGraphicsBridge. This class 
 * contains all VBOs VAOs IBOs, etc
 ******************************************************************/
#include "ArcGraphicsBridge.h"
#include "ArcGraphicData.h"
#include "ArcGMD.h"
#include <GL/glew.h>
#include <stdio.h>
#include <cstdlib>
#include <ArcTexture.h>
#include <iostream> // Debug

const size_t VERTEX_SIZE = 32; // 4 * 8
const size_t TEX_OFFSET  = 12; // 4 * 3
const size_t NORM_OFFSET = 20; // 4 * 5
const size_t SIZEOFUINT  = 4;

/******************************************************************
 * Constructor for the ArcGraphicsBridge
 ******************************************************************/
ArcGraphicsBridge::ArcGraphicsBridge(){
}

/******************************************************************
 * Destructor for the ArcGraphicsBridge
 * Removes all data from GPU
 ******************************************************************/
ArcGraphicsBridge::~ArcGraphicsBridge(){
}

/*******************************************************
 * Registers all data
 *******************************************************/
void ArcGraphicsBridge::loadGraphicData(ArcGraphicData& data)
{
  // Generate Empty Texture
  ArcTexture texture("no_texture.jpg");
  GLuint none;
  moveToGPU(texture, none);
  mTextures["none"] = none;

  // Load Models
  std::map<std::string, ArcGMD*> GMData = data.getData();
  std::map<std::string, ArcGMD*>::iterator i;
  for (i = GMData.begin(); i != GMData.end(); i++){
    ArcGMP GMP;
    moveToGPU(*(i->second), GMP);         // second = value (GMD)
    GMP.set = (i->second)->getSet();
    data.registerModel(GMP, i->first); // first = key (name)
  }  
  data.clearData();
  //std::cout << "Clearing Data\n";
}

/*******************************************************
 * Copys graphic data over to the GPU
 * Returns a single ID as a reference
 *******************************************************/
void ArcGraphicsBridge::moveToGPU(ArcGMD& data, ArcGMP& GMP){

  // Clear Previous Errors
  GLenum ErrorCheckValue = glGetError();

  // Create VAO - ID for this model
  glGenVertexArrays(1, &GMP.ID);
  glBindVertexArray(GMP.ID);

  // Storing IDs of (VBOs, IBO)
  ArcIDSet location;

  // Create Vertex VBO
  const size_t BufferSize  = VERTEX_SIZE * data.getNumVertices();

  // Generate Buffer
  glGenBuffers(1, &(location.VertexVBO));
  // Bind Buffer to VAO
  glBindBuffer(GL_ARRAY_BUFFER, location.VertexVBO);
  // Send Data over to GPU    
  glBufferData(GL_ARRAY_BUFFER, BufferSize, data.getVertices(), 
	       GL_STATIC_DRAW);
  // Vertices are at index 0 
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VERTEX_SIZE, 0);
  // Textures are at index 1 
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, VERTEX_SIZE, 
			(GLvoid*)TEX_OFFSET);
  // Normals are at index 2 
  glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, VERTEX_SIZE, 
  			(GLvoid*)NORM_OFFSET);

  // Enable Vertices, Textures, and Normals
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);

  // Create Index Buffers in GPU Memory
  const size_t IndicesSize = SIZEOFUINT  * data.getNumIndices();
  glGenBuffers(1, &location.IBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, location.IBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, IndicesSize, 
  	       data.getIndices(), GL_STATIC_DRAW);

  // Unbind Buffers
  glBindVertexArray(0);

  // Load Object Textures
  for (int i = 0; i < data.getTextures().size(); i++){
    // Add Ambient Texture if it doesn't already exist
    if (!mTextures.count(data.getTextures()[i].Ka)){
      ArcTexture texture((data.getTextures()[i].Ka).c_str());
      GLuint KaTexID;
      moveToGPU(texture, KaTexID);
      mTextures[data.getTextures()[i].Ka] = KaTexID;
    }
    // Add Diffuse Texture if it doesn't already exist
    if (!mTextures.count(data.getTextures()[i].Kd)){
      ArcTexture texture((data.getTextures()[i].Kd).c_str());
      GLuint KdTexID;
      moveToGPU(texture, KdTexID);
      mTextures[data.getTextures()[i].Kd] = KdTexID;
    }
    // Add Specular Texture if it doesn't already exist
    if (!mTextures.count(data.getTextures()[i].Ks)){
      ArcTexture texture((data.getTextures()[i].Ks).c_str());
      GLuint KsTexID;
      moveToGPU(texture, KsTexID);
      mTextures[data.getTextures()[i].Ks] = KsTexID;
    }
    // Return Texture IDs to the Model Pointer Set
    data.getSet()[i].texture.Ka = mTextures[data.getTextures()[i].Ka];  
    data.getSet()[i].texture.Kd = mTextures[data.getTextures()[i].Kd];  
    data.getSet()[i].texture.Ks = mTextures[data.getTextures()[i].Ks]; 
  }

  // Load Model Pointer with model set data
  GMP.set = data.getSet();

  // Register Object Locations
  mObjects[GMP.ID] = location;

  // Check for errors
  ErrorCheckValue = glGetError();
  if (ErrorCheckValue != GL_NO_ERROR){
    fprintf(stderr, "ERROR: Could not create a VBO: %s\n\n", 
	    gluErrorString(ErrorCheckValue));
    exit(-1);
  }
}

/*******************************************************
 * Move a texture onto the GPU
 *******************************************************/
void ArcGraphicsBridge::moveToGPU(ArcTexture& texture, GLuint& ID)
{
  GLuint ErrorCheckValue = glGetError();

  // Find Space on GPU
  glGenTextures(1, &ID);

  // Bind Texture
  glBindTexture(GL_TEXTURE_2D, ID);


  // Load Texture
  glTexImage2D(GL_TEXTURE_2D, 0, texture.internalFormat(), 
	       texture.width(), texture.height(), 0, 
	       texture.format(), GL_UNSIGNED_BYTE, texture.data());


  // Generate a MipMap
  glGenerateMipmap(GL_TEXTURE_2D);


  // Set it to display nearest pixel while interpolating
  //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

  // Set it to clamp to edge
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

  // Set it to blend with background color
  //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
  // Set it to replace color
  //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
  // Default Multiply together
  //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);


  // Unbind texture
  glBindTexture(GL_TEXTURE_2D, 0);

  ErrorCheckValue = glGetError();
  if (ErrorCheckValue != GL_NO_ERROR){
    fprintf(stderr, "ERROR: Could not load texture: %s\n\n", 
	    gluErrorString(ErrorCheckValue));
    exit(-1);
  }

}

/*******************************************************
 * Remove Object from GPU
 *******************************************************/
void ArcGraphicsBridge::removeObject(ArcGMP& GMP){

  // Clear any previous errors
  GLenum ErrorCheckValue = glGetError();

  // Get ID Set for the VAO (E.g. Address of VBOs, IBOs, etc)
  ArcIDSet* location = &mObjects[GMP.ID];

  // Connect to VAO
  glBindVertexArray(GMP.ID);
  
  // Disable attributes in reverse order
  glDisableVertexAttribArray(2);
  glDisableVertexAttribArray(1);
  glDisableVertexAttribArray(0);

  // Delete VBO
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glDeleteBuffers(1, &location->VertexVBO);

  // Delete IBO
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glDeleteBuffers(1, &location->IBO);

  // Delete VAO
  glBindVertexArray(0);
  glDeleteVertexArrays(1, &GMP.ID); 
  
  // Check for Errors
  ErrorCheckValue = glGetError();
  if (ErrorCheckValue != GL_NO_ERROR){
    fprintf(stderr, "ERROR: Could not destroy the VBO: %s\n", 
	    gluErrorString(ErrorCheckValue));
    exit(-1);
  }
}
