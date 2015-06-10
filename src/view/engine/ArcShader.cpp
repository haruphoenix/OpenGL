
#include <stdio.h>
#include <stdlib.h>
#include "ArcShader.h"


/*******************************************************
 * Constructor for the Shader Program
 *******************************************************/
ArcShader::ArcShader(){
}  

/*******************************************************
 * Destructor for the Shader Program
 *******************************************************/
ArcShader::~ArcShader(){
  GLenum ErrorCheckValue = glGetError();
  
  // Tell OpenGL to stop using the program
  glUseProgram(0);

  GLuint shader;
  while (!mShaders.empty()){
    shader = mShaders.back();
    mShaders.pop_back();

    // Detach Shader
    glDetachShader(mProgramId, shader);

    // Delete Shader
    glDeleteShader(shader);
  }

  // Delete the Shader Program
  glDeleteProgram(mProgramId);

  // Check for Errors
  ErrorCheckValue = glGetError();
  if (ErrorCheckValue != GL_NO_ERROR){
    fprintf(stderr, "ERROR: Could not destroy the shaders: %s \n",
	    gluErrorString(ErrorCheckValue));
    exit(-1);
  }
}  

/*******************************************************
 * Create Shader Program
 *******************************************************/
void ArcShader::initialize(){
  mProgramId = glCreateProgram();
}  

#include <iostream>

/*******************************************************
 * Draw an object
 *******************************************************/
void ArcShader::draw(ArcGOD& object){

  GLuint Error = glGetError();

  // Set Model Transform Matrix
  glUniformMatrix4fv(mModelMatrix, 1, GL_FALSE, object.transformMatrix.m); 

  // Bind Model
  glBindVertexArray(object.model.ID);

  
  if (object.model.ID == 0) return; // Don't draw nothing

  for (int i = 0; i < object.model.set.size(); i++){

    // Bind Texture
    glActiveTexture(GL_TEXTURE0); // Ambient
    glBindTexture(GL_TEXTURE_2D, object.model.set[i].texture.Ka);

    glActiveTexture(GL_TEXTURE1); // Diffuse
    glBindTexture(GL_TEXTURE_2D, object.model.set[i].texture.Kd);

    glActiveTexture(GL_TEXTURE2); // Specular
    glBindTexture(GL_TEXTURE_2D, object.model.set[i].texture.Ks);

    // Bind Material
    glUniform1fv(mMaterial, 10, object.model.set[i].material);

    // Draw Object
    glDrawElements(GL_TRIANGLES, object.model.set[i].numIndices,
		   GL_UNSIGNED_INT, (GLvoid*)(object.model.set[i].offset * 4));
  }

  // Unbind Model
  glBindVertexArray(0);
  
  Error = glGetError();
  if (Error != GL_NO_ERROR){    
    std::cout << "Error Rendering: " << gluErrorString(Error) << std::endl;
    exit(1);
  }
}  

/*******************************************************
 * Sets the view matrix (I.e. The camera location)
 *******************************************************/
void ArcShader::setView(ArcMatrix view)
{
  glUniformMatrix4fv(mViewMatrix, 1, GL_FALSE, view.m);
}

/*******************************************************
 * Sets the projection matrix (Orthographic or Perspective)
 *******************************************************/
void ArcShader::setProjection(ArcMatrix projection)
{
  glUniformMatrix4fv(mProjectionMatrix, 1, GL_FALSE, projection.m);
}

/*******************************************************
 * A simple way to get a shader from a file
 *******************************************************/
void ArcShader::setLights(ArcLight* lights)
{
  // 24 is the size of a ArcLight - float(4) * numFloatsInStruct(6)
  glUniform1fv(mLights, ARC_MAX_LIGHTS * 24, (float*)lights);
}

/*******************************************************
 * Adds a vertex shader to the program
 *******************************************************/
void ArcShader::addVertexShader(const char* filename){
  GLuint shader = loadShader(filename, GL_VERTEX_SHADER);
  glAttachShader(mProgramId, shader);
  mShaders.push_back(shader);
}

/*******************************************************
 * Adds a fragment shader to the program
 *******************************************************/
void ArcShader::addFragmentShader(const char* filename){
  GLuint shader = loadShader(filename, GL_FRAGMENT_SHADER);
  glAttachShader(mProgramId, shader);
  mShaders.push_back(shader);
}


/*******************************************************
 * Links the shader program with all of the shaders
 *******************************************************/
void ArcShader::link(){
  glLinkProgram(mProgramId);
}

/*******************************************************
 * Use this shader program
 *******************************************************/
void ArcShader::use(){

  GLenum ErrorCheckValue = glGetError();
  
  // Use Program - This program remains active until another is used
  glUseProgram(mProgramId);
  // Matrices
  mProjectionMatrix = glGetUniformLocation(mProgramId, "ProjectionMatrix");
  mModelMatrix = glGetUniformLocation(mProgramId, "ModelMatrix");
  mViewMatrix = glGetUniformLocation(mProgramId, "ViewMatrix");
  // Texture Samplers
  mKaTexture = glGetUniformLocation(mProgramId, "samplerKa");
  mKdTexture = glGetUniformLocation(mProgramId, "samplerKd");
  mKsTexture = glGetUniformLocation(mProgramId, "samplerKs");
  // Define Texture Enumerants - Can handle up to 70ish?
  glUniform1i(mKaTexture, 0); // Bind to GL_TEXTURE0 - Ambient Texture
  glUniform1i(mKdTexture, 1); // Bind to GL_TEXTURE1 - Diffuse Texture
  glUniform1i(mKsTexture, 2); // Bind to GL_TEXTURE2 - Specular Texture
  
  // Add Material
  mMaterial = glGetUniformLocation(mProgramId, "material");

  mLights = glGetUniformLocation(mProgramId, "light");

  // Check for Errors
  ErrorCheckValue = glGetError();
  if (ErrorCheckValue != GL_NO_ERROR){
    fprintf(stderr, "ERROR: Could not create the shaders: %s \n",
	    gluErrorString(ErrorCheckValue));
    exit(-1);
  }
}

/*******************************************************
 * A simple way to get a shader from a file
 *******************************************************/
GLuint ArcShader::loadShader(const char* filename, GLenum shader_type){
  GLuint shader_id = 0;
  FILE* file;
  long file_size = -1;
  char* glsl_source;
 

  if (NULL != (file = fopen(filename, "rb")) &&
    0 == fseek(file, 0, SEEK_END) &&
    -1 != (file_size = ftell(file)))
  {
    rewind(file);
    
    if (NULL != (glsl_source = (char*)malloc(file_size + 1)))
    {
      if (file_size == (long)fread(glsl_source, sizeof(char), file_size, file))
      {
        glsl_source[file_size] = '\0';
 
        if (0 != (shader_id = glCreateShader(shader_type)))
        {
          glShaderSource(shader_id, 1, (const GLchar**)&glsl_source, NULL);
          glCompileShader(shader_id);
	  // Check for errors
	  GLenum ErrorCheckValue = glGetError();
	  if (ErrorCheckValue != GL_NO_ERROR){
	    fprintf(stderr, "ERROR: Could not read shader program: %s\n", 
		    gluErrorString(ErrorCheckValue));
	    exit(-1);
	  }
        }
        else
          fprintf(stderr, "ERROR: Could not create a shader.\n");
      }
      else
        fprintf(stderr, "ERROR: Could not read file %s\n", filename);
 
      free(glsl_source);
    }
    else
      fprintf(stderr, "ERROR: Could not allocate %li bytes.\n", file_size);
 
    fclose(file);
  }
  else
  {
    if (NULL != file)
      fclose(file);
    fprintf(stderr, "ERROR: Could not open file %s\n", filename);
  }
 
  return shader_id;
}
