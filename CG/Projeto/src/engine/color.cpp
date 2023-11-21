#include "../../include/engine/color.h"


Color::Color(){}


Color::Color(XMLElement* elem) {
    for(XMLElement *child = elem->FirstChildElement(); child; child=child->NextSiblingElement()){
        string childName(child->Name());

        if (childName == "diffuse"){
            diffuse[0] = atof((char*)child->Attribute("R")) / 255.0;
            diffuse[1] = atof((char*)child->Attribute("G")) / 255.0;
            diffuse[2] = atof((char*)child->Attribute("B")) / 255.0;
        }
        else if (childName == "ambient"){
            ambient[0] = atof((char*)child->Attribute("R")) / 255.0;
            ambient[1] = atof((char*)child->Attribute("G")) / 255.0;
            ambient[2] = atof((char*)child->Attribute("B")) / 255.0;
        }
        else if (childName == "specular"){
            specular[0] = atof((char*)child->Attribute("R")) / 255.0;
            specular[1] = atof((char*)child->Attribute("G")) / 255.0;
            specular[2] = atof((char*)child->Attribute("B")) / 255.0;
        }
        else if (childName == "emissive"){
            emissive[0] = atof((char*)child->Attribute("R")) / 255.0;
            emissive[1] = atof((char*)child->Attribute("G")) / 255.0;
            emissive[2] = atof((char*)child->Attribute("B")) / 255.0;
        }
        else if (childName == "shininess"){
            shininess = atof((char*)child->Attribute("value"));
        }
    }
}