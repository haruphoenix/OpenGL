
#ifndef ARCVERTDATA_H
#define ARCVERTDATA_H
#include "ArcUtils.h"
#include <GL/glew.h>
#include <list>

class ArcVertexData
{
 public:
  ArcVertexData();
  void addVertices(int size, const ArcVertex vertices[]);
  void addIndices (int size, const GLuint indices[]);
  void addVertex(ArcVertex v)    {mVertices.push_back(v) ;};
  void addIndex(GLuint i)        {mIndices .push_back(i) ;};
  std::list<ArcVertex>& getVertices() {return mVertices  ;};
  std::list<GLuint>&    getIndices()  {return mIndices   ;};
  int getVertexSize()            {return mVertices.size();};
  int getIndexSize()             {return mIndices .size();};
  void clear()                   {mVertices.clear(); mIndices.clear();};
  void loadData(const char* filename);
  void exportData(const char* filename);
  void loadData(std::list<ArcVertex> v, std::list<GLuint> i);
 private:
  std::list<ArcVertex> mVertices;
  std::list<GLuint>    mIndices;
};

#endif
