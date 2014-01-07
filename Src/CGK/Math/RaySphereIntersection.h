#ifndef RAYSPHEREINTERSECTION_H
#define RAYSPHEREINTERSECTION_H

#include "Vector3.h"

/// Computes whether or not a ray intersects a sphere or not. In case of 
/// intersection the parameter [t] is assigned the distance of the ray's
/// origin to the closest intersection point. NOTE: the ray's direction is
/// assumed to be normalized.
template<typename T>
bool CGKMathRaySphereIntersection(
	T& t, 
	const CGKVector3<T>& rayOrigin,
	const CGKVector3<T>& rayDirection,
	const CGKVector3<T>& sphereOrigin,
	const T& sphereRadius 
);

#include "RaySphereIntersection.inl"

#endif /* end of include guard: RAYSPHEREINTERSECTION_H */
