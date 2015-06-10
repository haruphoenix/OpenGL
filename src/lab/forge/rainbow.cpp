#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <iomanip>

using namespace std;

int main(int argc, char** argv)
{
  ofstream fout;
  fout.open("src/model/models/rainbow.d");
  if (fout.fail()) return 1;

  fout << fixed << 4 * 17 * 2 << endl; // A lot of verts

  float Pi = 3.1415926535;

  float rgb[4][3] = { {1, 0, 0}, {1, 1, 0}, {0, 1, 1}, {1, 0, 1} };

  for (int i = 0; i < 2; i++){ // both sides
    for (int j = 0; j < 4; j++){ // 4 colors
      for (int k = 0; k <= 16; k++){ // 16 parts
	float x = cos((float)k / 16.0 * Pi) * (50 * (1 - (.1 * j)));
	float y = sin((float)k / 16.0 * Pi) * (50 * (1 - (.1 * j)));
	float z = 2 * i;
	fout << x << " " << y << " " << z << " 1.0   ";
	fout << rgb[j][0] << " " << rgb[j][1] << " " << rgb[j][2] << " 0.7\n";
      }
    }
  }

  //fout << 16 * 4 * 4 + 68 << endl;
  fout << (12 * 16) + 64  << endl;
  // Side 1
  for (int j = 0; j < 3; j++){
    for (int k = 0; k < 16; k++){
      int start = 17 * j;
      int a = start + k;
      int b = a + 17;
      int c = a + 1;
      fout << a << " " << b << " " << c << endl;
      c = a + 17;
      b = a + 1;
      a = a + 18;
      fout << a << " " << b << " " << c << endl;
    }
  }
  // side 2
  for (int j = 0; j < 3; j++){
    for (int k = 0; k < 16; k++){
      int start = (17 * j) + 68;
      int a = start + k;
      int c = a + 17;
      int b = a + 1;
      fout << a << " " << b << " " << c << endl;
      b = a + 17;
      c = a + 1;
      a = a + 18;
      fout << a << " " << b << " " << c << endl;
    }
  }

  // Outer Connector
  for (int i = 0; i < 16; i++){
    int a = i;
    int c = i + 68;
    int b = i + 69;
    fout << a << " " << b << " " << c << endl;
    b = i + 69;
    c = i;
    a = i + 1;
    fout << a << " " << b << " " << c << endl;
  }
  // Inner Connector
  for (int i = 51; i < 67; i++){
    int a = i;
    int b = i + 68;
    int c = i + 69;
    fout << a << " " << b << " " << c << endl;
    c = i + 69;
    b = i;
    a = i + 1;
    fout << a << " " << b << " " << c << endl;
  }

  // bottom end
  //fout << 0 << " " << 17 << " " << 68 << endl;
  //fout << 0 << " " << 68 << " " << 75 << endl;
  // Other bottom end
  //fout << 0 << " " << 0 << " " << 0 << endl;
  //fout << 0 << " " << 0 << " " << 0 << endl;

  fout.close();
  return 0;
}
