//-----------------------------------------------------------------------------
#include "MainCamera.h"
//-----------------------------------------------------------------------------
static CGKMatrix4f perspective;
static CGKMatrix4f view;
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
	const CGKVector3f& eye,
	const CGKVector3f& focus,
	const CGKVector3f& up
)
{
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
