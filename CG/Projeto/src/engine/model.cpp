#include "../../include/engine/model.h"


Model::Model(XMLElement* elem) {
    modelPath = strdup((char*)elem->Attribute("file"));
    const char* textureDir = "../../../demo-scenes/textures/";
    texturePath = NULL;
    nIndexes = 0;
    
    for(XMLElement *child = elem->FirstChildElement(); child; child=child->NextSiblingElement()){
        string name(child->Name());

        if (name == "color") {
            color = Color(child);
        }
        else if(name == "texture"){
            const char* textureFile = (char*)child->Attribute("file");
            int length = strlen(textureDir) + strlen(textureFile) + 1;
            texturePath = new char[length];
            strcpy(texturePath, textureDir);
            strcat(texturePath, textureFile);
        }
    }
}


Model::Model(char* newPath) {
    modelPath = strdup(newPath);
    color = NULL;
}


void Model::load() {
    vector<float> points;
    vector<int> indexes;
    vector<float> normals;
    vector<float> texCoords;

    char newPath[100] = "../../../demo-scenes/models/";
    ifstream file(strcat(newPath, modelPath));

    if (!file.is_open()) {
        return; // caso em que nao há o modelo gerado no .3d
    }

    string line, nVolumeStr, nVerticesStr, nTrianglesStr;
    getline(file, line);
    stringstream ss1(line);
    ss1 >> nVolumeStr;

    int nVolume = stoi(nVolumeStr);

    for (int i = 0; i < nVolume; i++) {
        getline(file, line);
        stringstream ss(line);
        string x, y, z;
        ss >> x >> y >> z;
        boundingVolume.push_back(Point(stof(x), stof(y), stof(z)));
    }

    getline(file, line);
    stringstream ss2(line);
    ss2 >> nVerticesStr >> nTrianglesStr;

    int nVertices = stoi(nVerticesStr);
    int nTriangles = stoi(nTrianglesStr);

    for (int i = 0; i < nVertices; i++) {
        getline(file, line);
        stringstream ss(line);
        string x, y, z;
        ss >> x >> y >> z;
        points.push_back(stof(x));
        points.push_back(stof(y));
        points.push_back(stof(z));
    }

    for (int i = 0; i < nTriangles; i++) {
        getline(file, line);
        stringstream ss(line);
        string indP1, indP2, indP3;
        ss >> indP1 >> indP2 >> indP3;
        indexes.push_back(stoi(indP1));
        indexes.push_back(stoi(indP2));
        indexes.push_back(stoi(indP3));
    }

    for(int i = 0; i < nVertices; i++) {
        getline(file, line);
        stringstream ss(line);  
        string x, y, z;
        ss >> x >> y >> z;
        normals.push_back(stof(x));
        normals.push_back(stof(y));
        normals.push_back(stof(z));
    }

    for (int i = 0; i < nVertices; i++) {
        getline(file, line);
        stringstream ss(line);
        string x, y;
        ss >> x >> y;
        texCoords.push_back(stof(x));
        texCoords.push_back(stof(y));
    }

    file.close();


    glGenBuffers(1, &verticesBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, verticesBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * points.size(), points.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &normalsBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, normalsBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * normals.size(), normals.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &texCoordsBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, texCoordsBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * texCoords.size(), texCoords.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &indexesBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexesBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * indexes.size(), indexes.data(), GL_STATIC_DRAW);

    nIndexes = indexes.size();

    if (texturePath) {
        loadTexture();
    }

}


void Model::loadTexture() {
    unsigned int t, tw, th;
	unsigned char *texData;
	ilGenImages(1, &t);
	ilBindImage(t);
	ilLoadImage((ILstring)texturePath);
	tw = ilGetInteger(IL_IMAGE_WIDTH);
	th = ilGetInteger(IL_IMAGE_HEIGHT);
	ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
	texData = ilGetData();

	glGenTextures(1, &texture);

	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_LINEAR_MIPMAP_NEAREST, GL_LINEAR); // Ver isto

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tw, th, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);

	glGenerateMipmap(GL_TEXTURE_2D);
}


void Model::draw() {
    glMaterialfv(GL_FRONT, GL_DIFFUSE, color.diffuse);
    glMaterialfv(GL_FRONT, GL_AMBIENT, color.ambient);
    glMaterialfv(GL_FRONT, GL_SPECULAR, color.specular);    
    glMaterialfv(GL_FRONT, GL_EMISSION, color.emissive);
    glMaterialf(GL_FRONT, GL_SHININESS, color.shininess);
    
    if (texturePath) {
        glBindTexture(GL_TEXTURE_2D, texture);
    }

    glBindBuffer(GL_ARRAY_BUFFER, verticesBuffer);
    glVertexPointer(3, GL_FLOAT, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, normalsBuffer);
    glNormalPointer(GL_FLOAT, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, texCoordsBuffer);
    glTexCoordPointer(2, GL_FLOAT, 0, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexesBuffer);
    glDrawElements(GL_TRIANGLES, nIndexes, GL_UNSIGNED_INT, NULL);

    if(texturePath){
        glBindTexture(GL_TEXTURE_2D, 0);
    }

;
}