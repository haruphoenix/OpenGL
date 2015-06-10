#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>

using namespace std;

int main(int argc, char** argv)
{
  ofstream fout;
  fout.open("src/model/models/orangeFlower.d");
  if (fout.fail()) return 1;

  fout << 22 << endl; // 22 Vertices
  
  fout << "0.0 1.8 0.0 1.0    1.0 1.0 0.0 1.0\n"; // Center 0

  float TwoPi = 3.1415926535 * 2;

  for (int i = 0; i < 16; i++){                   // Petals 1 - 16
    float x = cos((float)i / 16.0 * TwoPi);
    float z = sin((float)i / 16.0 * TwoPi);
    if (i % 2 == 0){
      x *= .7;
      z *= .7;
    }
    fout << x << " 2.0 " << z << " 1.0    ";
    if (i % 2 == 0){
      fout << "1.0 0.0 0.0 1.0\n";
    }
    else{
      fout << "1.0 0.5 0.0 1.0\n";
    }    
  }

  fout << " 0   0    0   1   0  5  0  1\n";      // flower base 17
  fout << " 0.1 1.8  0.1 1   0  5  0  1\n";      // tops 18-21
  fout << " 0.1 1.8 -0.1 1   0  5  0  1\n";
  fout << "-0.1 1.8 -0.1 1   0  5  0  1\n";
  fout << "-0.1 1.8  0.1 1   0  5  0  1\n";

  fout << "20\n";

  for (int i = 1; i <= 16; i++){
    int i1 = (i + 1) % 17;
    int i2 = i % 17;
    if (!i1) i1 = 1;
    fout << "0 " << i1 << " " << i2 << endl;
  }

  fout << "17 20 19\n";
  fout << "17 21 20\n";
  fout << "17 18 21\n";
  fout << "17 19 18\n";
  
  fout.close();
  return 0;
}
