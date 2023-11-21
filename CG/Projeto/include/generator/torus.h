#ifndef __TORUS__
#define __TORUS__

#include <vector>
#include <math.h>
#include "../point.h"
#include "../triangle.h"

using namespace std;

void generateTorus(float radiusIn, float radiusOut, int slices, int layers, vector<Point> *vertices, vector<Triangle> *triangles, vector<Point> *normals, vector<Point> *texCoords, vector<Point>* boundingVolume);

#endif
