#include "../../include/engine/settings.h"

// -----------WINDOW-----------
Window::Window(){}

Window::Window(XMLElement *windowElement){
    width = atoi(windowElement->Attribute("width"));
    height = atoi(windowElement->Attribute("height"));
}


// -----------CAMERA-----------
Camera::Camera(){}

Camera::Camera(XMLElement *cameraElement){
    up = Point(0, 1, 0); // Default value
    projection = Projection(60, 1, 1000); // Default value
    explorerCenter = Point(0, 0, 0); // Default value
    mode = STATIC;
    radius = 5;
    alpha = 0;
    beta = 0;
    moveSpeed = 3;
    rotationSpeed = 0.01;
    firstTime = true;

    if(cameraElement->Attribute("mode")){
        string name(cameraElement->Attribute("mode"));

        if(name == "static"){
            mode = STATIC;
        }
        else if(name == "explorer"){
            mode = EXPLORER;
        }
        else if(name == "fps"){
            mode = FPS;
        }
    }

    for(XMLElement *elem = cameraElement->FirstChildElement(); elem; elem=elem->NextSiblingElement()){
        string name(elem->Name());
        
        if(name == "position"){
            position = Point(atof(elem->Attribute("x")), atof(elem->Attribute("y")), atof(elem->Attribute("z")));
        }
        else if(name == "lookAt"){
            lookAt = Point(atof(elem->Attribute("x")), atof(elem->Attribute("y")), atof(elem->Attribute("z")));
        }
        else if(name == "up"){
            up = Point(atof(elem->Attribute("x")), atof(elem->Attribute("y")), atof(elem->Attribute("z")));
        }
        else if(name == "projection"){
            projection = Projection(atof(elem->Attribute("fov")), atof(elem->Attribute("near")), atof(elem->Attribute("far")));
        }
    }
}

void Camera::updateDirection(){
    // Vetor D
    direction.x = lookAt.x - position.x;
    direction.y = lookAt.y - position.y;
    direction.z = lookAt.z - position.z;
    
    // Normalizar o vetor
    direction.normalizeVector();
}


void Camera::updateLateralDirection(){
    // Vetor R
    direction.x = lookAt.x - position.x;
    direction.y = lookAt.y - position.y;
    direction.z = lookAt.z - position.z;
    
    // Produto externo
    direction.crossProduct(up);

    // Normalizar o vetor
    direction.normalizeVector();
}


void Camera::updateExplorerPosition(){
    position.x = radius * cos(beta) * sin(alpha) + explorerCenter.x;
    position.y = radius * sin(beta) + explorerCenter.y;
    position.z = radius * cos(beta) * cos(alpha) + explorerCenter.z;
}


void Camera::updateExplorer(Point p){
    explorerCenter = p;
    lookAt.x = p.x;
	lookAt.y = p.y;
	lookAt.z = p.z;

    updateExplorerPosition();
}


void Camera::updateFPSPosition(int coef){
    position.x = position.x + coef * moveSpeed * direction.x;
    position.y = position.y + coef * moveSpeed * direction.y;
    position.z = position.z + coef * moveSpeed * direction.z;

    lookAt.x = lookAt.x + coef * moveSpeed * direction.x;
    lookAt.y = lookAt.y + coef * moveSpeed * direction.y;
    lookAt.z = lookAt.z + coef * moveSpeed * direction.z;
}


void Camera::processNormalKeys(unsigned char key){
    key = tolower(key);

    switch(key){
        case '-':
            if(mode == EXPLORER){
                radius += 0.5;
                updateExplorerPosition();
            }
            break;
        case '+':
            if(mode == EXPLORER){
                if (radius - 0.5 < 0)
                    radius = 0;
                else radius -= 0.5;
                updateExplorerPosition();
            }
            break;
        case 'w':
            if(mode == FPS){
                int mod = glutGetModifiers();
                if (mod == GLUT_ACTIVE_SHIFT) {
                    moveSpeed = 15;
                }
                else {
                    moveSpeed = 3;
                }

                updateDirection();
                updateFPSPosition(1);
            }
            break;
        case 's':
            if(mode == FPS){
                int mod = glutGetModifiers();
                if (mod == GLUT_ACTIVE_SHIFT) {
                    moveSpeed = 15;
                }
                else {
                    moveSpeed = 3;
                }
		    
                updateDirection();
                updateFPSPosition(-1);
            }
            break;
        case 'a':
            if(mode == FPS){
                int mod = glutGetModifiers();
                if (mod == GLUT_ACTIVE_SHIFT) {
                    moveSpeed = 15;
                }
                else {
                    moveSpeed = 3;
                }
		  
                updateLateralDirection();
                updateFPSPosition(-1);
            }
            break;
        case 'd':
            if(mode == FPS){
                int mod = glutGetModifiers();
                if (mod == GLUT_ACTIVE_SHIFT) {
                    moveSpeed = 15;
                }
                else {
                    moveSpeed = 3;
                }
		  
                updateLateralDirection();
                updateFPSPosition(1);
            }
            break;
        default:
            break;
    }
}

void Camera::processSpecialKeys(int key){
    switch(key){
        case GLUT_KEY_LEFT:
            if(mode == EXPLORER){
                alpha -= M_PI / 20;
                updateExplorerPosition();
            }
            break;
        case GLUT_KEY_RIGHT:
            if(mode == EXPLORER){
                alpha += M_PI / 20;
                updateExplorerPosition();
            }
            break;
        case GLUT_KEY_UP:
            if(mode == EXPLORER){
                beta += M_PI / 20;

			    if (beta > M_PI / 2) beta = M_PI / 2;
                updateExplorerPosition();
            }
            break;
        case GLUT_KEY_DOWN:
            if(mode == EXPLORER){
                beta -= M_PI / 20;

			    if (beta < -M_PI / 2) beta = -M_PI / 2;
                updateExplorerPosition();
            }
            break;
    }
}


void Camera::processMouseButtons(int button){
    switch (button) {
        case 3:
            if (mode == EXPLORER){
                if (radius - 5 < 0)
                    radius = 0;
                else radius -= 5;
                updateExplorerPosition();
            }
            break;
        case 4:
            if (mode == EXPLORER){
                radius += 5;
                updateExplorerPosition();
            }
            break;
        default:
            break;
    }
}

void Camera::processMouseMotion(int x, int y){
    if(mode == FPS || mode == EXPLORER){
        if(firstTime){
            firstTime = false;
            startX = x;
            startY = y;
        }

        float deltaX = (x - startX) * rotationSpeed;
        float deltaY = (startY - y) * rotationSpeed;

        startX = x;
        startY = y;

        alpha += deltaX;

        if (beta + deltaY <= M_PI_2 && beta + deltaY >= -M_PI_2) {
            beta += deltaY;
        }

        if(mode == FPS){        
            lookAt.x = position.x + sin(alpha) * cos(beta);
            lookAt.y = position.y + sin(beta);
            lookAt.z = position.z - cos(alpha) * cos(beta);
        }
        else if(mode == EXPLORER){
            updateExplorerPosition();
        }
    }
}

// -----------PROJECTION-----------
Projection::Projection(){}

Projection::Projection(float newFov, float newNear, float newFar){
    fov = newFov;
    near = newNear;
    far = newFar;
}
