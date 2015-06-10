
#include "ArcVertexData.h"
#include <GL/glew.h>
#include <list>
#include <iostream>
#include <fstream>
#include "ArcUtils.h"

ArcVertexData::ArcVertexData()
{
}

void ArcVertexData::loadData(const char* filename)
{
  std::ifstream fin;
  fin.open(filename);
  if (fin.fail()) return;
  int x;
  while (fin >> x)
  {
    switch (x)
    {
       case 0:
	 ArcVertex v;
	 fin >> v.Position[0];
	 fin >> v.Position[1];
	 fin >> v.Position[2];
	 fin >> v.Position[3];
	 fin >> v.Color[0];
	 fin >> v.Color[1];
	 fin >> v.Color[2];
	 fin >> v.Color[3];
	 mVertices.push_back(v);
	 break;
       case 1:
	 GLuint g;
	 fin >> g;
	 mIndices.push_back(g);
	 fin >> g;
	 mIndices.push_back(g);
	 fin >> g;
	 mIndices.push_back(g);
	 break;
       default:
	 break;
    }
  }
  fin.close();
}

void ArcVertexData::exportData(const char* filename)
{
  std::ofstream fout;
  fout.open(filename);
  if (fout.fail()) return;
  std::list<ArcVertex>::iterator v;
  for (v = mVertices.begin(); v != mVertices.end(); ++v)
  {
    fout << 0 << " "
	 << v->Position[0] << " "
	 << v->Position[1] << " "
	 << v->Position[2] << " "
	 << v->Position[3] << " "
	 << v->Color[0] << " "
	 << v->Color[1] << " "
	 << v->Color[2] << " "
	 << v->Color[3] << std::endl;
  }

  fout << std::endl;
  
  std::list<GLuint>::iterator i;
  for (i = mIndices.end(); i != mIndices.begin();)
  {
    fout << 1 << " " 
	 << *(--i) << " "
	 << *(--i) << " "
	 << *(--i) << std::endl;
  }
  fout.close();
}

void ArcVertexData::loadData(std::list<ArcVertex> v, std::list<GLuint> i)
{
  std::list<ArcVertex>::iterator vertex;
  for (vertex = v.begin(); vertex != v.end(); ++vertex)
    mVertices.push_back(*vertex);

  std::list<GLuint>::iterator index;
  for (index = i.begin(); index != i.end(); ++index)
    mIndices.push_back(*index);
}

void ArcVertexData::addVertices(int size, const ArcVertex vertices[])
{
  for (int i = 0; i < size; i++)
    mVertices.push_back(vertices[i]);
}

void ArcVertexData::addIndices(int size, const GLuint indices[])
{
  for (int i = 0; i < size; i++)
    mIndices.push_back(indices[i]);
}

