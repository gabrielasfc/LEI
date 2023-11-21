#ifndef __BEZIER__
#define __BEZIER__

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include "../point.h"
#include "../triangle.h"

using namespace std;

void generateBezier(char *path, int level, vector<Point> *vertices, vector<Triangle> *triangles, vector<Point> *normals, vector<Point> *texCoords, vector<Point>* boundingVolume);

#endif