#ifndef MAINCAMERA_H
#define MAINCAMERA_H

#include "../Math/Matrix4.h"

void CGKMainCameraSetPerspective(
	float fovy, 
	float aspect, 
	float near, 
	float far
);

void CGKMainCameraSetView(
	const CGKVector3f& eye,
	const CGKVector3f& focus,
	const CGKVector3f& up
);

const CGKMatrix4f& CGKMainCameraGetPerspective();
const CGKMatrix4f& CGKMainCameraGetView();

void CGKMainCameraRotateAroundYAxisAtPointWithAngle(
	const CGKVector3f& point, 
	float angle
);

const CGKVector3f& CGKMainCameraGetFocus();

#endif /* end of include guard: MAINCAMERA_H */
