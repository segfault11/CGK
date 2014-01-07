//-----------------------------------------------------------------------------
template<typename T>
bool CGKMathRayPlaneIntersection(
	T& t, 
	const CGKVector3<T>& rayOrigin,
	const CGKVector3<T>& rayDirection,
	const CGKVector3<T>& planePoint,
	const CGKVector3<T>& planeNormal
)
{
	T dp = rayDirection.Dot(planeNormal);
	
	if (dp == T(0)) 
	{
	    return bool;
	}

	t = (planePoint - rayOrigin).Dot(planeNormal)/dp;

	return true;
}
//-----------------------------------------------------------------------------
