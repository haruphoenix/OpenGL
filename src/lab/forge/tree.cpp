#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>

using namespace std;

int main(int argc, char** argv)
{
  ofstream fout;
  fout.open("src/model/models/texTree.d");
  if (fout.fail()) return 1;

  float TwoPi = 3.1415926535 * 2;

  fout << fixed << "0\n"; // Texture

  float trunkTextureCoords[2][4] = { { 0.0, 0.39, 0.0, 1.0 },
                                   { 0.29, 0.39, 0.29, 0.95 } };

  float x0 = (330.0 / 512.0);
  float x1 = (220.0 / 512.0);
  float x2 = (470.0 / 512.0);
  float y0 = (140.0 / 512.0);
  float y1 = (350.0 / 512.0);
  float y2 = (350.0 / 512.0);
  
  //float branchTextureCoords[] = { 0.34, 0.32, 0.39, 0.9, 0.68, 0.9 };
  float branchTextureCoords[] = { x0, y0, x1, y1, x2, y2 };

  int width = 2;
  int height = 4;

  // Trunk Vertices  
  fout << (13 * height) + 12 << std::endl;
  for (int i = 0; i < 6; i++){
    float a = ((float)i / 6) * TwoPi;
    float x = cos(a);
    float z = sin(a);
    float t1 = trunkTextureCoords[i % 2][0];
    float t2 = trunkTextureCoords[i % 2][1];
    float t3 = trunkTextureCoords[i % 2][2];
    float t4 = trunkTextureCoords[i % 2][3];
    fout << x << " " << -0.5 << " " << z << " 1.0 "
	 << "1.0 1.0 1.0 1.0 " << t1 << " " << t2 << std::endl;
    fout << x << " " << 2.5 << " " << z << " 1.0 "
	 << "1.0 1.0 1.0 1.0 " << t3 << " " << t4 << std::endl;
  }


  // Branch Vertices
  for (int i = 0; i < height; i++){
    float scale = height - (((float)(i) / (float)height)) * (float)width;
    float y = ((i + 1) * 1) + 1;
    fout << "0 " << ((i + 1) * 1.5) + 2.0 << " 0 1   1 1 1 1 " << branchTextureCoords[0]
	 << " " << branchTextureCoords[1] << std::endl;
    for (int j = 0; j < 6; j++){
      // Two Vertices at each point
      float a = ((float)j / 6.0) * TwoPi;
      float x = cos(a) * scale;
      float z = sin(a) * scale;
      float t1 = branchTextureCoords[2];
      float t2 = branchTextureCoords[3];
      float t3 = branchTextureCoords[4];
      float t4 = branchTextureCoords[5];
      fout << x << " " << y << " " << z << " 1.0 "
	   << "1.0 1.0 1.0 1.0 " << t1 << " " << t2 << std::endl;
      fout << x << " " << y << " " << z << " 1.0 "
	   << "1.0 1.0 1.0 1.0 " << t3 << " " << t4 << std::endl;
    }
  }

  // Trunk Indices
  fout << (height * 6) +12 << std::endl;
  for (int i = 0; i < 6; i++){
    int a = 2 * i;
    int b = ((2 * i) + 1);
    int c = (b + 1) % 12;
    fout << a << " " << b << " " << c << std::endl;
    a = (2 * (i + 1)) % 12;
    c = (b + 2) % 12;
    fout << a << " " << b << " " << c << std::endl;
  }

  // Branch Indices
  for (int i = 0; i < height; i++){
    for (int j = 0; j < 6; j++){
      int base = 12 + (13 * i);
      int a = base + (2 * (j + 1));
      int b = base;
      int c = base + (((2 * (j + 1)) + 1) % 13);
      if (b == c) c++;
      fout << a << " " << b << " " << c << std::endl;
    }
  }

  fout.close();
  return 0;
}
