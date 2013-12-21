//-----------------------------------------------------------------------------
#include <cmath>
#include "MainCamera.h"
#include "../Math/Vector2.h"
#include <iostream>
//-----------------------------------------------------------------------------
static CGKMatrix4f perspective;
static CGKMatrix4f view;
static CGKVector3f eye;
static CGKVector3f focus;
static CGKVector3f up;
//-----------------------------------------------------------------------------
void CGKMainCameraSetPerspective(
	float fovy,
	float aspect,
	float near,
	float far
)
{
	perspective.MakePerspective(fovy, aspect, near, far);
}
//-----------------------------------------------------------------------------
void CGKMainCameraSetView(
	const CGKVector3f& e,
	const CGKVector3f& f,
	const CGKVector3f& u
)
{
	eye = e;
	focus = f;
	up = u;

	view.MakeView(eye, focus, up);
}
//-----------------------------------------------------------------------------
const CGKMatrix4f& CGKMainCameraGetPerspective()
{
	return perspective;
}
//-----------------------------------------------------------------------------
const CGKMatrix4f& CGKMainCameraGetView()
{
	return view;
}
//-----------------------------------------------------------------------------
void CGKMainCameraRotateAroundYAxisAtPointWithAngle(
	const CGKVector3f& point,
	float angle
)
{
	CGKVector3f v = eye - point;
	CGKVector2f w(v[0], v[2]);
	float mag = w.GetMagnitude();
	w.Normalize();

	// compute current angle		
	float a = acos(w[0]); 

	if (w[1] < 0.0) 
	{
	    a = 2.0*M_PI - a;
	}

	// add the angle the camera is rotated
	a += angle;
	
	std::cout << angle << std::endl;
	std::cout << a << std::endl;

//	if (a > 2*M_PI) 
//	{
//	    a -= 2*M_PI;
//	}
//
//	if (a < -2*M_PI) 
//	{
//	    a += 2*M_PI;
//	}

	// update eye
	eye[0] = mag*cos(a) + point[0];
	eye[2] = mag*sin(a) + point[2];

	view.MakeView(eye, focus, up);
}
//-----------------------------------------------------------------------------
const CGKVector3f& CGKMainCameraGetFocus()
{
	return focus;
}
//-----------------------------------------------------------------------------
