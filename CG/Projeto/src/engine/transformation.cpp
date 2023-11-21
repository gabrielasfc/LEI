#include "../../include/engine/transformation.h"

// STATIC TRANSLATION
TranslateStatic::TranslateStatic(XMLElement *elem){
    x = atof((char *)elem->Attribute("x"));
    y = atof((char *)elem->Attribute("y"));
    z = atof((char *)elem->Attribute("z"));
}


void TranslateStatic::transform(){
    glTranslatef(x, y, z);
}


// DYNAMIC TRANSLATION
TranslateDynamic::TranslateDynamic(XMLElement *elem){
    time = atof((char *)elem->Attribute("time"));
    yi = Point(0,1,0);
    tesselation = 100;
    show = true;
    
    if (!strcasecmp((char *)elem->Attribute("align"), "True")){
        align = true;
    } 
    else if (!strcasecmp((char *)elem->Attribute("align"), "False")){
        align = false;
    }

    int i=0;
    for(XMLElement *childElem = elem->FirstChildElement(); childElem; childElem = childElem->NextSiblingElement(), i++){
        string name(childElem->Name());

        if (name == "ellipsepoints"){
            int n=0, a=0, b=0, xrotation=0, yrotation=0, xcenter=0, zcenter=0;
            float step=0;

            if (childElem->Attribute("n")){
                n = atoi((char *)childElem->Attribute("n"));
                step = 2*M_PI / n;
            }
            if (childElem->Attribute("a")) a = atoi((char *)childElem->Attribute("a"));
            if (childElem->Attribute("b")) b = atoi((char *)childElem->Attribute("b"));
            if (childElem->Attribute("xRotationAngle")) xrotation = atoi((char *)childElem->Attribute("xRotationAngle"));
            if (childElem->Attribute("yRotationAngle")) yrotation = atoi((char *)childElem->Attribute("yRotationAngle"));
            if (childElem->Attribute("xCenter")) xcenter = atoi((char *)childElem->Attribute("xCenter"));
            if (childElem->Attribute("zCenter")) zcenter = atoi((char *)childElem->Attribute("zCenter"));

            for (int j=0; j<n; j++){
                float x = xcenter + a * cos(yrotation*M_PI / 180.0) * cos(j*step) - b * sin(yrotation*M_PI / 180.0) * sin(j*step) * cos(xrotation*M_PI / 180.0);
                float y = b * sin(j*step) * sin(xrotation*M_PI / 180.0);
                float z = zcenter + a * sin(yrotation*M_PI / 180.0) * cos(j*step) + b * cos(yrotation*M_PI / 180.0) * sin(j*step) * cos(xrotation*M_PI / 180.0);
                points.push_back(Point(x, y, z));
            }
            i+=n;
        }
        else if (name == "point"){
            points.push_back(Point(childElem));
        }
    }

    if (i < 4){
        cout << "ERROR: Due to Catmull-Rom's curve definition it is always required an initial point before the initial curve segment and another point after the last segment. The minimum number of points is 4" << endl;
        exit(1);
    }
    
    pointCount = points.size();

    if (elem->Attribute("tesselation")){
        tesselation = atoi((char *)elem->Attribute("tesselation"));
    }

    if (elem->Attribute("show") && !strcasecmp((char *)elem->Attribute("show"),"False")){
        show = false;
    }
}


void TranslateDynamic::buildRotMatrix(Point x, Point y, Point z, float *m) {
	m[0] = x.x; m[1] = x.y; m[2] = x.z; m[3] = 0;
	m[4] = y.x; m[5] = y.y; m[6] = y.z; m[7] = 0;
	m[8] = z.x; m[9] = z.y; m[10] = z.z; m[11] = 0;
	m[12] = 0; m[13] = 0; m[14] = 0; m[15] = 1;
}


void TranslateDynamic::multMatrixVector(float *m, float *v, float *res){
    for (int j = 0; j < 4; ++j) {
        res[j] = 0;
        for (int k = 0; k < 4; ++k) {
            res[j] += v[k] * m[j * 4 + k];
        }
    }
}


void TranslateDynamic::getCatmullRomPoint(float t, int *indexes, float *pos, float *deriv) {
	// catmull-rom matrix
	float m[4][4] = {	{-0.5f,  1.5f, -1.5f,  0.5f},
						{ 1.0f, -2.5f,  2.0f, -0.5f},
						{-0.5f,  0.0f,  0.5f,  0.0f},
						{ 0.0f,  1.0f,  0.0f,  0.0f}};
			
	float T[4] = {(float)pow(t,3), (float)pow(t,2), t, 1};
	float TL[4] = {3*(float)pow(t,2), 2*t, 1, 0};

    float Point::*coordinates[3] = { &Point::x, &Point::y, &Point::z };
    for (int i = 0; i < 3; i++) {
        // A = M * P
        float P[4] = {points[indexes[0]].*coordinates[i], points[indexes[1]].*coordinates[i], points[indexes[2]].*coordinates[i], points[indexes[3]].*coordinates[i]};
        float A[4];
        multMatrixVector(&m[0][0], P, A);

        // pos = T * A
		pos[i] = T[0] * A[0] + T[1] * A[1] + T[2] * A[2] + T[3] * A[3]; 

        // deriv = T' * A
		deriv[i] = TL[0] * A[0] + TL[1] * A[1] + TL[2] * A[2] + TL[3] * A[3];
    }
}


void TranslateDynamic::getGlobalCatmullRomPoint(float gt, float *pos, float *deriv) {
	float t = gt * pointCount;
	int index = floor(t);
	t -= index;

	int indexes[4]; 
	indexes[0] = (index + pointCount-1)%pointCount;	
	indexes[1] = (indexes[0]+1)%pointCount;
	indexes[2] = (indexes[1]+1)%pointCount; 
	indexes[3] = (indexes[2]+1)%pointCount;

	getCatmullRomPoint(t, indexes, pos, deriv);
}


void TranslateDynamic::transform(){
    float pos[3];
	float deriv[3];

    if (show) {
        float step = 1/(float)tesselation;

        glPushAttrib(GL_CURRENT_BIT);
        glColor3f(1,1,1);

        glBegin(GL_LINE_LOOP);
		    for (float gt = 0; gt < 1; gt += step) {
		    	getGlobalCatmullRomPoint(gt, pos, deriv);
		    	glVertex3f(pos[0], pos[1], pos[2]);
		    }
	    glEnd();

        glPopAttrib();
    }
	
    
    float t = (glutGet(GLUT_ELAPSED_TIME) / 1000.0) / (float)time;
    getGlobalCatmullRomPoint(t, pos, deriv);
	glTranslatef(pos[0], pos[1], pos[2]);

    if(align){
        Point xi = Point(deriv[0], deriv[1], deriv[2]);
        xi.normalizeVector();

        Point zi = Point(xi.x, xi.y, xi.z);
        zi.crossProduct(yi);
        zi.normalizeVector();

        yi = Point(zi.x, zi.y, zi.z);
        yi.crossProduct(xi);
        yi.normalizeVector();

        float m[16];
        buildRotMatrix(xi, yi, zi, m);

        glMultMatrixf(m);
    }
}


// STATIC ROTATION
RotateStatic::RotateStatic(XMLElement *elem){
    x = atof((char *)elem->Attribute("x"));
    y = atof((char *)elem->Attribute("y"));
    z = atof((char *)elem->Attribute("z"));
    angle = atof((char *)elem->Attribute("angle"));
}


void RotateStatic::transform(){
    glRotatef(angle, x, y, z);
}


// DYNAMIC ROTATION
RotateDynamic::RotateDynamic(XMLElement *elem){
    clockwise = false;
    x = atof((char *)elem->Attribute("x"));
    y = atof((char *)elem->Attribute("y"));
    z = atof((char *)elem->Attribute("z"));
    time = atof((char *)elem->Attribute("time"));
    
    if (elem->Attribute("clockwise") && !strcasecmp((char *)elem->Attribute("clockwise"),"True")){
        clockwise = true;
    }
}

void RotateDynamic::transform(){
    float t = (glutGet(GLUT_ELAPSED_TIME) / 1000.0) / (float)time;

    if(clockwise)
        glRotatef(-t*360, x, y, z);
    else
        glRotatef(t*360, x, y, z);
}


// SCALE
Scale::Scale(XMLElement *elem){
    x = atof((char *)elem->Attribute("x"));
    y = atof((char *)elem->Attribute("y"));
    z = atof((char *)elem->Attribute("z"));
}


void Scale::transform(){
    glScalef(x, y, z);
}