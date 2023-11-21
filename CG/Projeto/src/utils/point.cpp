#include "../../include/point.h"

Point::Point(){
    x = 0;
    y = 0;
    z = 0;
}

Point::Point(XMLElement *elem){
    x = atof((char *)elem->Attribute("x"));
    y = atof((char *)elem->Attribute("y"));
    z = atof((char *)elem->Attribute("z"));
}

Point::Point(float x1, float y1, float z1){
    x = x1;
    y = y1;
    z = z1;
}

void Point::normalizeVector(){
    float vectorLength = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));

    x = x / vectorLength;
    y = y / vectorLength;
    z = z / vectorLength;
}

void Point::crossProduct(Point v){
    float xAux = x, yAux = y, zAux = z;
    x = yAux * v.z - zAux * v.y;
    y = zAux * v.x - xAux * v.z; 
    z = xAux * v.y - yAux * v.x;
}


float Point::distanceTo(Point p){
  float dx = x - p.x;
  float dy = y - p.y;
  float dz = z - p.z;
  return sqrt(dx*dx + dy*dy + dz*dz);
}