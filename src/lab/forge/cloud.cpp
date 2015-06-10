#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>

using namespace std;

int main(int argc, char** argv)
{
  ofstream fout;
  fout.open("src/model/models/cloud1.d");
  if (fout.fail()) return 1;

  int latitude   = 5; // Left and right
  int longitude  = 5; // Up and Down
  int numVertices = 2 + ((longitude - 2) * latitude);
  fout << fixed << numVertices << endl;

  // Top Vertex
  fout << 0 << " " << 1 << " " << 0 << " 1    1 1 1 .5\n";

  float Pi = 3.1415926535;
  float TwoPi = 3.1415926535 * 2;

  // For each longitude (y level)
  for (int lon = 1; lon < longitude - 1; lon++){
    //cout << lon << "/" << longitude - 1 << endl;
    float a = (float)lon * Pi / ((float)longitude - 1);
    //cout << fixed << a << endl;
    float y = cos(a);
    //cout << y << endl;
    if (y > 0)
      y += (float)(rand() % 10) / 10.0;
    else
      y -= (float)(rand() % 10) / 10.0;
      float t = y < 0 ? -y : y;

    float n = (float)lon / (float)longitude;

    // for each latitude (x z level)
    for (int lat = 0; lat < latitude; lat++){

      float b = ((float)lat * TwoPi / (float)latitude);
      // Width
      float x = cos(b) * sin(a);
      // Depth
      float z = sin(b) * sin(a);

      if (x > 0)
	x += (float)(rand() % 15) / 10.0;
      else
	x -= (float)(rand() % 15) / 10.0;
      if (z > 0)
	z += (float)(rand() % 15) / 10.0;
      else
	z -= (float)(rand() % 15) / 10.0;

      float s = x < 0 ? -x : x;
      float v = z < 0 ? -z : z;

      float a = .6 * x;

      fout << x << " " << y << " " << z << " 1.0    "
	   << a << " " << a << " " << a << " " << .5 << endl;
    }
  }

  // Bottom Vertex
  fout << 0 << " " << -1 << " " << 0 << " 1    1 1 1 .5\n";

  int numIndices = (2 * latitude) + ((longitude - 3) * latitude * 2);
  // Indices
  fout << numIndices << endl;
  // top
  for (int i = 0; i < latitude; i++){
    int b = (i + 1) % (latitude + 1);
    int a = (i + 2) % (latitude + 1);
    if (a == 0) { a = 1; };
    fout << 0 << " " << a << " " << b << endl;
  }

  // Sides
  for (int i = 1; i < numVertices - latitude - 1; i++){
    int a = i;
    int b = (i + 1) + (!((i) % latitude) * -latitude);
    int c = (i + latitude) % (numVertices - 1);
    if (!c) c = 1;
    fout << a << " " << b << " " << c << endl;
    int m = a;
    a = b;
    b = (m + latitude + 1);
    if ((b - 1) % latitude == 0) b -= latitude;
    fout << a << " " << b << " " << c << endl;
  }

  // bottom
  for (int i = 0; i < latitude; i++){
    int n = numVertices - i - 1;
    int a = (n - 2);
    int b = (n - 1);
    if (a < numVertices - latitude - 1) a = numVertices - 2;
    fout << numVertices - 1 << " " << a << " " << b << endl;
  }

  fout.close();
  return 0;
}
