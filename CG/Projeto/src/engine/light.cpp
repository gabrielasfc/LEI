#include "../../include/engine/light.h"

void Light::setup() {
    float dark[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
    float white[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

    // light colors
    glEnable(light);
    glLightfv(light, GL_AMBIENT, dark);
    glLightfv(light, GL_DIFFUSE, white);
    glLightfv(light, GL_SPECULAR, white);

    // controls global ambient light
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, white);
}


int Light::getLight(int index){
    int light;
    switch (index) {
        case 0: light = GL_LIGHT0; break;
        case 1: light = GL_LIGHT1; break;
        case 2: light = GL_LIGHT2; break;
        case 3: light = GL_LIGHT3; break;
        case 4: light = GL_LIGHT4; break;
        case 5: light = GL_LIGHT5; break;
        case 6: light = GL_LIGHT6; break;
        case 7: light = GL_LIGHT7; break;
        default: exit(1);
    }
    return light;
}


//POINT
PointLight::PointLight(XMLElement *elem, int index){
    elem->Attribute("posX") ? pos[0] = atof((char *)elem->Attribute("posX")) : pos[0] = atof((char *)elem->Attribute("posx"));
    elem->Attribute("posY") ? pos[1] = atof((char *)elem->Attribute("posY")) : pos[1] = atof((char *)elem->Attribute("posy"));
    elem->Attribute("posZ") ? pos[2] = atof((char *)elem->Attribute("posZ")) : pos[2] = atof((char *)elem->Attribute("posz"));
    pos[3] = 1.0;
    light = getLight(index);
}

void PointLight::apply(){
    glLightfv(light, GL_POSITION, pos);
}


//DIRECTIONAL
DirectionalLight::DirectionalLight(XMLElement *elem, int index){
    elem->Attribute("dirX") ? dir[0] = atof((char *)elem->Attribute("dirX")) : dir[0] = atof((char *)elem->Attribute("dirx"));
    elem->Attribute("dirY") ? dir[1] = atof((char *)elem->Attribute("dirY")) : dir[1] = atof((char *)elem->Attribute("diry"));
    elem->Attribute("dirZ") ? dir[2] = atof((char *)elem->Attribute("dirZ")) : dir[2] = atof((char *)elem->Attribute("dirz"));
    dir[3] = 0.0;
    light = getLight(index);
}

void DirectionalLight::apply(){
    glLightfv(light, GL_POSITION, dir);
}


//SPOTLIGHT
SpotLight::SpotLight(XMLElement* elem, int index){
    elem->Attribute("posX") ? pos[0] = atof((char *)elem->Attribute("posX")) : pos[0] = atof((char *)elem->Attribute("posx"));
    elem->Attribute("posY") ? pos[1] = atof((char *)elem->Attribute("posY")) : pos[1] = atof((char *)elem->Attribute("posy"));
    elem->Attribute("posZ") ? pos[2] = atof((char *)elem->Attribute("posZ")) : pos[2] = atof((char *)elem->Attribute("posz"));
    pos[3] = 1.0;

    elem->Attribute("dirX") ? spotDir[0] = atof((char *)elem->Attribute("dirX")) : spotDir[0] = atof((char *)elem->Attribute("dirx"));
    elem->Attribute("dirY") ? spotDir[1] = atof((char *)elem->Attribute("dirY")) : spotDir[1] = atof((char *)elem->Attribute("diry"));
    elem->Attribute("dirZ") ? spotDir[2] = atof((char*)elem->Attribute("dirZ")) : spotDir[2] = atof((char*)elem->Attribute("dirz"));

    cutoff = atof((char *)elem->Attribute("cutoff"));
    light = getLight(index);
}

void SpotLight::apply(){
    glLightfv(light, GL_POSITION, pos);
    glLightfv(light, GL_SPOT_DIRECTION, spotDir);
    glLightf(light, GL_SPOT_CUTOFF, cutoff);
    //glLightf(light, GL_SPOT_EXPONENT, 0);
}
