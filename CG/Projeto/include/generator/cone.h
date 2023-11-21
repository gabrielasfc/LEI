#ifndef __CONE__
#define __CONE__

#include <math.h>
#include <vector>
#include "../point.h"
#include "../triangle.h"

using namespace std;

void generateCone(float radius, float height, int slices, int stacks, vector<Point> *vertices, vector<Triangle> *triangles, vector<Point> *normals, vector<Point> *texCoords, vector<Point>* boundingVolume);

#endif