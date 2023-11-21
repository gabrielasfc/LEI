#include "../../include/engine/frustumplane.h"


FrustumPlane::FrustumPlane(){}


FrustumPlane::FrustumPlane(float newA, float newB, float newC, float newD) {
	A = newA;
	B = newB;
	C = newC;
	D = newD;
}


float FrustumPlane::distance(Point p) {
	return A * p.x + B * p.y + C * p.z + D;
}
