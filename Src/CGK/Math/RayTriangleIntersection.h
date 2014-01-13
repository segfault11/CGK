#ifndef RAYTRIANGLEINTERSECTION_H
#define RAYTRIANGLEINTERSECTION_H

#include "Vector3.h"

template<typename T>
bool CGKMathRayTriangleIntersection(
	T& t, 
	const CGKVector3<T>& rayOrigin,
	const CGKVector3<T>& rayDirection,
	const CGKVector3<T>& a,
	const CGKVector3<T>& b,
	const CGKVector3<T>& c
);

#include "RayTriangleIntersection.inl"

#endif /* end of include guard: RAYTRIANGLEINTERSECTION_H */
