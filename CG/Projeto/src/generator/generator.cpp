#include <string.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <regex>
#include "../../include/point.h"
#include "../../include/generator/plane.h"
#include "../../include/generator/box.h"
#include "../../include/generator/cone.h"
#include "../../include/generator/sphere.h"
#include "../../include/generator/cylinder.h"
#include "../../include/generator/torus.h"
#include "../../include/generator/ellipsoid.h"
#include "../../include/generator/belt.h"
#include "../../include/generator/bezier.h"

using namespace std;

void toFile(char* filename, vector<Point> *vertices, vector<Triangle> *triangles, vector<Point> *normals, vector<Point> *texCoords, vector<Point> *boundingVolume){
    ofstream file;
    char path[100] = "../../../demo-scenes/models/";

    file.open(strcat(path, filename));
    char buffer[1024];


    int nVolume = boundingVolume->size();

    // N�mero de pontos do bounding volume
    file << nVolume << "\n";

    // Bounding Volume
    for (int i = 0; i < nVolume; i++) {
        sprintf(buffer, "%f %f %f\n", (*boundingVolume)[i].x, (*boundingVolume)[i].y, (*boundingVolume)[i].z);
        file << buffer;
    }

    int nVertices = vertices->size(), nTriangles = triangles->size();

    // N�mero de v�rtices e tri�ngulos
    file << nVertices << " " << nTriangles << "\n";

    //Vertices
    for(int i = 0; i < nVertices; i++){
        sprintf(buffer, "%f %f %f\n", (*vertices)[i].x, (*vertices)[i].y, (*vertices)[i].z);
        file << buffer;
    }


    //Triangles
    for(int i = 0; i < nTriangles; i++){
        sprintf(buffer, "%d %d %d\n", (*triangles)[i].indP1, (*triangles)[i].indP2, (*triangles)[i].indP3);
        file << buffer;
    }


    //Normals
    for(int i = 0; i < nVertices; i++){
        sprintf(buffer, "%f %f %f\n", (*normals)[i].x, (*normals)[i].y, (*normals)[i].z);
        file << buffer;
    }


    //Texture Coordinates
    for(int i = 0; i < nVertices; i++){
        sprintf(buffer, "%f %f\n", (*texCoords)[i].x, (*texCoords)[i].y);
        file << buffer;
    }

    file.close();
}

int main(int argc, char *argv[]){
    if (argc == 1 || (argc == 2 && strcmp(argv[1], "--help") == 0)){
        cout << "--------------------------------------------HELP------------------------------------------------" << endl;
        cout << "USAGE: ./generator {MODEL} {ARGUMENTS} {TexMapType} {OUTPUT FILE}" << endl;
        cout << "TexMapType is an optional parameter which defines the map type for textures" << endl;
        cout << "- map type can be 'tiled' or 'stretched' - by default is 'stretched'" << endl;
        cout << "------------------------------------------------------------------------------------------------" << endl;
        cout << "MODEL     | ARGUMENTS                                                            | OUTPUT FILE" << endl;
        cout << "plane     | {length} {divisions}                                                 | {filename}.3d" << endl;
        cout << "box       | {length} {divisions}                                                 | {filename}.3d" << endl;
        cout << "cone      | {radius} {height} {slices} {stacks}                                  | {filename}.3d" << endl;
        cout << "sphere    | {radius} {slices} {stacks}                                           | {filename}.3d" << endl;
        cout << "cylinder  | {radius} {height} {slices}                                           | {filename}.3d" << endl;
        cout << "torus     | {radius_in} {radius_out} {slices} {stacks}                           | {filename}.3d" << endl;
        cout << "ellipsoid | {a} {b} {c} {slices} {stacks}                                        | {filename}.3d" << endl;
        cout << "belt      | {n} {radiusIn} {radiusOut} {height} {lengthMin} {lengthMax} {seed}   | {filename}.3d" << endl;
        cout << "patch     | {filepath}.patch {tesselation_level}                                 | {filename}.3d" << endl;
        cout << "------------------------------------------------------------------------------------------------" << endl;
        
        return 1;
    }

    string inp;

    for (int i=1; argv[i] != NULL; i++) {
        inp.append(argv[i]);
        inp.push_back(' ');
    }
    inp.pop_back();

    char erPlane[] = "plane ([0-9]+[.])?[0-9]+ [0-9]+([ ]stretched|[ ]tiled)? [a-zA-Z0-9_]+\\.3d$";
    char erBox[] = "box ([0-9]+[.])?[0-9]+ [0-9]+([ ]stretched|[ ]tiled)? [a-zA-Z0-9_]+\\.3d$";
    char erCone[] = "cone ([0-9]+[.])?[0-9]+ ([0-9]+[.])?[0-9]+ [0-9]+ [0-9]+ [a-zA-Z0-9_]+\\.3d$";
    char erSphere[] = "sphere ([0-9]+[.])?[0-9]+ [0-9]+ [0-9]+ [a-zA-Z0-9_]+\\.3d$";
    char erCylinder[] = "cylinder ([0-9]+[.])?[0-9]+ ([0-9]+[.])?[0-9]+ [0-9]+ [a-zA-Z0-9_]+\\.3d$";
    char erTorus[] = "torus ([0-9]+[.])?[0-9]+ ([0-9]+[.])?[0-9]+ [0-9]+ [0-9]+ [a-zA-Z0-9_]+\\.3d$";
    char erEllipsoid[] = "ellipsoid ([0-9]+[.])?[0-9]+ ([0-9]+[.])?[0-9]+ ([0-9]+[.])?[0-9]+ [0-9]+ [0-9]+ [a-zA-Z0-9_]+\\.3d$";
    char erBelt[] = "belt [0-9]+ ([0-9]+[.])?[0-9]+ ([0-9]+[.])?[0-9]+ ([0-9]+[.])?[0-9]+ ([0-9]+[.])?[0-9]+ ([0-9]+[.])?[0-9]+ [0-9]+ [a-zA-Z0-9_]+\\.3d$";
    char erBezier[] = "patch [a-zA-Z0-9_/.-]+\\.patch [0-9]+ [a-zA-Z0-9_]+\\.3d$";

    vector<Point> *vertices = new vector<Point>;
    vector<Triangle> *triangles = new vector<Triangle>;
    vector<Point> *normals = new vector<Point>;
    vector<Point> *texCoords = new vector<Point>;
    vector<Point>* boundingVolume = new vector<Point>;

    if (regex_match(inp, regex(erPlane))){
        float length = atof(argv[2]);
        int divisions = atoi(argv[3]);
        int mappingType = 1;
        char* filename;
        if (argv[5]) {
            mappingType = !strcmp(argv[4], "tiled") ? 2 : 1;
            filename = argv[5];
        }
        else filename = argv[4];

        generatePlane(length, divisions, mappingType, vertices, triangles, normals, texCoords, boundingVolume);
        toFile(filename, vertices, triangles, normals, texCoords, boundingVolume);
    }
    else if(regex_match(inp, regex(erBox))){
        float length = atof(argv[2]);
        int divisions = atoi(argv[3]);
        int mappingType = 1;
        char* filename;
        if (argv[5]) {
            mappingType = !strcmp(argv[4], "tiled") ? 2 : 1;
            filename = argv[5];
        }
        else filename = argv[4];

        generateBox(length, divisions, mappingType, vertices, triangles, normals, texCoords, boundingVolume);
        toFile(filename, vertices, triangles, normals, texCoords, boundingVolume);
    }
    else if(regex_match(inp, regex(erCone))){
        float radius = atof(argv[2]);
        float height = atof(argv[3]);
        int slices = atoi(argv[4]);
        int stacks = atoi(argv[5]);
        char *filename = argv[6];

        generateCone(radius, height, slices, stacks, vertices, triangles, normals, texCoords, boundingVolume);
        toFile(filename, vertices, triangles, normals, texCoords, boundingVolume);
    }
    else if(regex_match(inp, regex(erSphere))){
        float radius = atof(argv[2]);
        int slices = atoi(argv[3]);
        int stacks = atoi(argv[4]);
        char *filename = argv[5];

        generateSphere(radius, slices, stacks, vertices, triangles, normals, texCoords, boundingVolume);
        toFile(filename, vertices, triangles, normals, texCoords, boundingVolume);
    }
    else if(regex_match(inp, regex(erCylinder))){
        float radius = atof(argv[2]);
        float height = atof(argv[3]);
        int slices = atoi(argv[4]);
        char *filename = argv[5];

        generateCylinder(radius, height, slices, vertices, triangles, normals, boundingVolume);
        toFile(filename, vertices, triangles, normals, texCoords, boundingVolume);
    }
    else if(regex_match(inp, regex(erTorus))){
        float radiusIn = atof(argv[2]);
        float radiusOut = atof(argv[3]);
        int slices = atoi(argv[4]);
        int stacks = atoi(argv[5]);
        char *filename = argv[6];

        generateTorus(radiusIn, radiusOut, slices, stacks, vertices, triangles, normals, texCoords, boundingVolume);
        toFile(filename, vertices, triangles, normals, texCoords, boundingVolume);
    }
    else if(regex_match(inp, regex(erEllipsoid))){
        float a = atof(argv[2]);
        float b = atof(argv[3]);
        float c = atof(argv[4]);
        int slices = atoi(argv[5]);
        int stacks = atoi(argv[6]);
        char *filename = argv[7];

        generateEllipsoid(a, b, c, slices, stacks, vertices, triangles, normals, texCoords, boundingVolume);
        toFile(filename, vertices, triangles, normals, texCoords, boundingVolume);
    }
    else if(regex_match(inp, regex(erBelt))){
        int n = atoi(argv[2]);
        float radiusIn = atof(argv[3]);
        float radiusOut = atof(argv[4]);
        float height = atof(argv[5]);
        float lengthMin = atof(argv[6]);
        float lengthMax = atof(argv[7]);
        int seed = atoi(argv[8]);
        char *filename = argv[9];

        generateBelt(n, radiusIn, radiusOut, height, lengthMin, lengthMax, seed, vertices, triangles, normals, texCoords, boundingVolume);
        toFile(filename, vertices, triangles, normals, texCoords, boundingVolume);
    }
    else if(regex_match(inp, regex(erBezier))){
        char *ctrlpoints_file = argv[2];
        int level = atoi(argv[3]);
        char *filename = argv[4];

        generateBezier(ctrlpoints_file, level, vertices, triangles, normals, texCoords, boundingVolume);
        toFile(filename, vertices, triangles, normals, texCoords, boundingVolume);
    }
    else cout << "Invalid input!" << endl;


    return 0;
}
