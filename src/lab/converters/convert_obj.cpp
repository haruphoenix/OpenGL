#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <map>
using namespace std;

// Data Types
struct V3F { float x; float y; float z; };
struct V2F { float x; float y; };
struct V3I { int x; int y; int z; };
struct V4I { int x; int y; int z; int w; };

struct Texture  { string map_Ka; string map_Kd; string map_Ks; };
struct Material { V3F Ka; V3F Kd; V3F Ks; float d; Texture Tex; };

// Operators for V3I
bool operator < (V3I left, V3I right);
bool operator > (V3I left, V3I right);
bool operator == (V3I left, V3I right);
bool operator != (V3I left, V3I right);
bool operator <= (V3I left, V3I right);
bool operator >= (V3I left, V3I right);
// Operators for V4I
bool operator < (V4I left, V4I right);
bool operator > (V4I left, V4I right);
bool operator == (V4I left, V4I right);
bool operator != (V4I left, V4I right);
bool operator <= (V4I left, V4I right);
bool operator >= (V4I left, V4I right);


/***********************************************************
 * Class for creating .arcData files from .obj files
 ***********************************************************/
class ObjectLoader {
 public:
  ObjectLoader();
  void loadFile(string filename);
  void writeFile(string filename);
 private:
  void loadMaterials(ifstream& fin);
  void readVertex(ifstream& fin);
  void readTexCoord(ifstream& fin);
  void readNormal(ifstream& fin);
  void readFace(ifstream& fin);
  void translateIndex(string index, V3I& vector);

  // Data Lists
  vector<V3F> mVertices;
  vector<V2F> mTextureCoords;
  vector<V3F> mNormals;
  vector<V3I> mF_Vertices; // Face Vertices
  map<V3I, int> mVertexMap;
  vector<float> mIndices;
  vector<Material> mMaterials;
  map<string, int> mMaterialMap;
  int mVNum;
  int mCurrentMaterial;
  vector<int> mIndForMaterial;
  vector<int> mMatNumber;
  string mDirectory;
  bool mTriangles;
};

/***********************************************************
 * Creates an object loader to parse an obj file and export
 * it as a arcData filetype
 ***********************************************************/
int main(int argc, char** argv)
{
  // Check Arguments
  if (argc != 3){
    cout << "Usage: Enter a .obj file to convert\n";
    return 0;
  }

  ObjectLoader object;
  object.loadFile(argv[1]);
  object.writeFile(argv[2]);

  return 0;
}

/*************************************************************
 * Constructor
 *************************************************************/
ObjectLoader::ObjectLoader()
{
  mVNum = 0;
  mCurrentMaterial = 0;
  mTriangles = true;
}

/*************************************************************
 * Reads and parses an obj file
 *************************************************************/
void ObjectLoader::loadFile(string filename)
{
  // Store Directory
  int endOfDirectory = filename.find_last_of("/");
  mDirectory = filename.substr(0, endOfDirectory) + '/';

  // Open File
  ifstream fin;
  fin.open(filename.c_str());

  // Check For Success
  if (fin.fail()){
    cout << "Error: Could not open " << filename << endl;
    return;
  }

  // Read File
  string header;
  while (fin >> header){
    if (header == "#") getline(fin, header); // Comment
    else if (header == "v") readVertex(fin);
    else if (header == "vt") readTexCoord(fin);
    else if (header == "vn") readNormal(fin);
    else if (header == "f"){
      readFace(fin);
      if (mTriangles) mIndForMaterial[mIndForMaterial.size() - 1] += 3;
      else mIndForMaterial[mIndForMaterial.size() - 1] += 6;
    }
    else if (header == "mtllib") loadMaterials(fin);
    else if (header == "usemtl"){
      fin >> header;
      mCurrentMaterial = mMaterialMap[header];
      mMatNumber.push_back(mCurrentMaterial);
      mIndForMaterial.push_back(0);
    }
    else getline(fin, header); // Unimplemented
  }

  // Close File
  fin.close();
}


/*************************************************************
 * Exports file as a arcData formatted file
 *************************************************************/
void ObjectLoader::writeFile(string filename)
{
  // Open New File
  ofstream fout;
  fout.open(filename.c_str());

  // Check for success
  if (fout.fail()){
    cout << "Error writing to " << filename << endl;
    return;
  }
  
  // Write to file //
  
  // Just In Case
  V3F tempV3F = {0, 0, 0};
  V2F tempV2F = {0, 0};
  mVertices.push_back(tempV3F);
  mTextureCoords.push_back(tempV2F);
  mNormals.push_back(tempV3F);

  // Print Number of Vertices
  fout << mF_Vertices.size() << endl;

  // Print Vertices
  for (int i = 0; i < mF_Vertices.size(); i++){
    int vIndex = mF_Vertices[i].x - 1;
    int tIndex = mF_Vertices[i].y - 1;
    int nIndex = mF_Vertices[i].z - 1;
    // Print Vertex Coordinate
    fout << fixed
	 << mVertices[vIndex].x << " "
	 << mVertices[vIndex].y << " "
	 << mVertices[vIndex].z << " "
      // Print Texture Coordinates
	 << mTextureCoords[tIndex].x << " "
	 << mTextureCoords[tIndex].y << " "
      // Print Normals
	 << mNormals[nIndex].x << " "
	 << mNormals[nIndex].y << " "
	 << mNormals[nIndex].z << endl;
  }

  // Print Number of Materials
  fout << std::setprecision(0) << mIndForMaterial.size() << endl;

  // Print Materials  
  for (int i = 0; i < mIndForMaterial.size(); i++)
    fout << mIndForMaterial[i] << setprecision(6) << " "
      // Ambient
	 << mMaterials[mMatNumber[i]].Ka.x << " "
	 << mMaterials[mMatNumber[i]].Ka.y << " "
	 << mMaterials[mMatNumber[i]].Ka.z << " "
      // Diffuse
	 << mMaterials[mMatNumber[i]].Kd.x << " "
	 << mMaterials[mMatNumber[i]].Kd.y << " "
	 << mMaterials[mMatNumber[i]].Kd.z << " "
      // Specular
	 << mMaterials[mMatNumber[i]].Ks.x << " "
	 << mMaterials[mMatNumber[i]].Ks.y << " "
	 << mMaterials[mMatNumber[i]].Ks.z << " "
      // Transparency
	 << mMaterials[mMatNumber[i]].d << endl
      // Textures
	 << mMaterials[mMatNumber[i]].Tex.map_Ka << endl
	 << mMaterials[mMatNumber[i]].Tex.map_Kd << endl
	 << mMaterials[mMatNumber[i]].Tex.map_Ks << endl;

  // Print Num Indices
  fout << std::setprecision(0) << mIndices.size() << endl;

  // Print Indices
  for (int i = 0; i < mIndices.size(); i++){
    if (i % 3 == 0) fout << endl;
    else fout << " ";
    fout << mIndices[i];
  }

  // Close File
  fout.close();

}

/*************************************************************
 * Loads a material library
 *************************************************************/
void ObjectLoader::loadMaterials(ifstream& fin)
{
  // Get Matllib filename
  string filename;
  fin >> filename;
  
  // Open File
  ifstream matFin;
  matFin.open((mDirectory + filename).c_str());
  if (matFin.fail()) {
    cout << "Error: Could not open " << mDirectory + filename << endl;
    return;
  }

  // Read File
  string header;
  bool first = true;
  string name;
  Material m;
  m.d = 1.0; // Default Opaque
  m.Tex.map_Ka = m.Tex.map_Kd = m.Tex.map_Ks = "none"; // no texture
  while (matFin >> header){
    if (header == "newmtl"){
      if (!first){ // Save Material
	mMaterialMap[name] = mMaterials.size();
	mMaterials.push_back(m);
      }
      matFin >> name;
      first = false;
    }
    else if (header == "Ka") matFin >> m.Ka.x >> m.Ka.y >> m.Ka.z;
    else if (header == "Kd") matFin >> m.Kd.x >> m.Kd.y >> m.Kd.z;
    else if (header == "Ks") matFin >> m.Ks.x >> m.Ks.y >> m.Ks.z;
    else if (header == "d" ) matFin >> m.d;
    else if (header == "map_Ka") matFin >> m.Tex.map_Ka;
    else if (header == "map_Kd") matFin >> m.Tex.map_Kd;
    else if (header == "map_Ks") matFin >> m.Tex.map_Ks;
    else getline(matFin, header);
  }

  // Save Last Material
  mMaterialMap[name] = mMaterials.size();
  mMaterials.push_back(m);

  matFin.close();
}


/*************************************************************
 * Reads a single vertex from a .obj file
 *************************************************************/
void ObjectLoader::readVertex(ifstream& fin)
{
  V3F vertex;
  fin >> vertex.x;
  fin >> vertex.y;
  fin >> vertex.z;
  mVertices.push_back(vertex);
}

/*************************************************************
 * Reads a single texture coordinate from a .obj file
 *************************************************************/
void ObjectLoader::readTexCoord(ifstream& fin)
{
  V2F texCoord;
  fin >> texCoord.x;
  fin >> texCoord.y;
  mTextureCoords.push_back(texCoord);
}

/*************************************************************
 * Reads a single normal from a .obj file
 *************************************************************/
void ObjectLoader::readNormal(ifstream& fin)
{
  V3F normal;
  fin >> normal.x;
  fin >> normal.y;
  fin >> normal.z;
  mNormals.push_back(normal);
}

/*************************************************************
 * Reads a single face from a .obj file
 *************************************************************/
void ObjectLoader::readFace(ifstream& fin)
{
  V3I index[3] = { {0, 0, 0}, { 0, 0, 0 }, { 0, 0, 0 } };
  string indexString;

  for (int i = 0; i < 4; i++){
    if (i == 3){
      mTriangles = (fin.peek() != ' ');
      if (mTriangles) break; // Only read 3 for triangles
    }
    // Read index string
    fin >> indexString;
    // Turn index string into vector of indices
    translateIndex(indexString, index[i]);
    // Check if index vector is unique
    if (mVertexMap.find(index[i]) == mVertexMap.end()){
      mF_Vertices.push_back(index[i]);          // Add Vertex
      mVertexMap[index[i]] = mVNum++;           // Vertex Num
    }
  }

  // Record Indices
  mIndices.push_back(mVertexMap[index[0]]);
  mIndices.push_back(mVertexMap[index[1]]);
  mIndices.push_back(mVertexMap[index[2]]);

  if (!mTriangles){
    mIndices.push_back(mVertexMap[index[3]]);
    mIndices.push_back(mVertexMap[index[0]]);
    mIndices.push_back(mVertexMap[index[2]]);
  }

}


/*************************************************************
 * Turns an index into a vector - to be able to read from
 *************************************************************/
void ObjectLoader::translateIndex(string indexString, V3I& index)
{
  string d = "/"; // delimiter for indices

  // Get Values
  int pos = indexString.find(d);
  
  // Position Index
  string x = indexString.substr(0, pos);
  indexString.erase(0, pos + d.length());
  // Texture Index (optional)
  string y;
  if (string::npos != (pos = indexString.find(d))){
    y = indexString.substr().c_str();
    indexString.erase(0, pos + d.length());
  } else y = indexString;
  // Normal Index
  string z = indexString.substr(0, pos);

  // Convert Values to ints
  index.x = atoi(x.c_str());
  index.y = atoi(y.c_str());
  index.z = atoi(z.c_str());

  // Check for negative Indices
  if (index.x < 0) index.x += mVertices.size() + 1;
  if (index.y < 0) index.y += mVertices.size() + 1;
  if (index.z < 0) index.z += mVertices.size() + 1;
}


/* ~~~~~~~~~~~~~~~~~~~~~ V3I Operations ~~~~~~~~~~~~~~~~~~~~ */




/*************************************************************
 * Returns true if the vector on the left is less than the
 * vector on the right
 *************************************************************/
bool operator < (V3I left, V3I right){
  if (left.x < right.x) return true;
  else if ((left.x == right.x) && 
	   (left.y < right.y)) return true;
  else if ((left.x == right.x) && 
	   (left.y == right.y) && 
	   (left.z < right.z)) return true;
  return false;
}

/*************************************************************
 * Returns true if the vector on the left is greater than the
 * vector on the right
 *************************************************************/
bool operator > (V3I left, V3I right){
  if (left.x > right.x) return true;
  else if ((left.x == right.x) && 
	   (left.y > right.y)) return true;
  else if ((left.x == right.x) && 
	   (left.y == right.y) && 
	   (left.z > right.z)) return true;
  return false;
}

/*************************************************************
 * Returns true if the vectors are equal
 *************************************************************/
bool operator == (V3I left, V3I right)
{
  if ((left.x == right.x) &&
      (left.y == right.y) &&
      (left.z == right.z)) return true;
  return false;
}


/*************************************************************
 * Returns true if the vectors are not equal
 *************************************************************/
bool operator != (V3I left, V3I right)
{
  return  !(left == right);
}


/*************************************************************
 * Returns true if the vector on the left is less than or
 * equal to the vector on the right
 *************************************************************/
bool operator <= (V3I left, V3I right)
{
  return !(left > right);
}


/*************************************************************
 * Returns true if the vector on the left is greater than or
 * equal to the vector on the right
 *************************************************************/
bool operator >= (V3I left, V3I right)
{
  return !(right > left);
}



/* ~~~~~~~~~~~~~~~~~~~~~ V3F Operations ~~~~~~~~~~~~~~~~~~~~ */




/*************************************************************
 * Returns true if the vector on the left is less than the
 * vector on the right
 *************************************************************/
bool operator < (V4I left, V4I right){
  if (left.x < right.x) return true;
  else if ((left.x == right.x) && 
	   (left.y < right.y)) return true;
  else if ((left.x == right.x) && 
	   (left.y == right.y) && 
	   (left.z < right.z)) return true;
  return false;
}

/*************************************************************
 * Returns true if the vector on the left is greater than the
 * vector on the right
 *************************************************************/
bool operator > (V4I left, V4I right){
  if (left.x > right.x) return true;
  else if ((left.x == right.x) && 
	   (left.y > right.y)) return true;
  else if ((left.x == right.x) && 
	   (left.y == right.y) && 
	   (left.z > right.z)) return true;
  return false;
}

/*************************************************************
 * Returns true if the vectors are equal
 *************************************************************/
bool operator == (V4I left, V4I right)
{
  if ((left.x == right.x) &&
      (left.y == right.y) &&
      (left.z == right.z)) return true;
  return false;
}


/*************************************************************
 * Returns true if the vectors are not equal
 *************************************************************/
bool operator != (V4I left, V4I right)
{
  return  !(left == right);
}


/*************************************************************
 * Returns true if the vector on the left is less than or
 * equal to the vector on the right
 *************************************************************/
bool operator <= (V4I left, V4I right)
{
  return !(left > right);
}


/*************************************************************
 * Returns true if the vector on the left is greater than or
 * equal to the vector on the right
 *************************************************************/
bool operator >= (V4I left, V4I right)
{
  return !(right > left);
}
