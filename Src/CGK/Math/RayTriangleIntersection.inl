//-----------------------------------------------------------------------------
template<typename T>
bool CGKMathRayTriangleIntersection(
	T& t, 
	const CGKVector3<T>& rayOrigin,
	const CGKVector3<T>& rayDirection,
	const CGKVector3<T>& a,
	const CGKVector3<T>& b,
	const CGKVector3<T>& c
)
{
	CGKVector3<T> e1 = b - a;
	CGKVector3<T> e2 = c - a;
	CGKVector3<T> p = rayDirection.Cross(e2);
	T det = e1.Dot(p);

	if (det == T(0)) 
	{
	    return false;
	}

	T detInv = T(1)/det;

	CGKVector3<T> tv = rayOrigin - a;

	T u = tv.Dot(p)*detInv;

	if (u < T(0) || u > T(1))
	{
		return false;
	}

	CGKVector3<T> q = tv.Cross(e1);
	T v = rayDirection.Dot(q)*detInv;

	if (v < T(0) || u + v > T(1)) 
	{
	    return false;
	}

	t = e2.Dot(q)*detInv;	

	return true;
}
//-----------------------------------------------------------------------------
