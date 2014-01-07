#ifndef RAYPLANEINTERSECTION_H
#define RAYPLANEINTERSECTION_H

#include "Vector3.h"

template<typename T>
bool CGKMathRayPlaneIntersection(
	T& t,
	const CGKVector3<T>& rayOrigin,
	const CGKVector3<T>& rayDirection,
	const CGKVector3<T>& planePoint,
	const CGKVector3<T>& planeNormal
);

#endif /* end of include guard: RAYPLANEINTERSECTION_H */
