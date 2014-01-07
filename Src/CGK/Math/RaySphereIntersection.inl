//-----------------------------------------------------------------------------
template<typename T>
bool CGKMathRaySphereIntersection(
	T& t, 
	const CGKVector3<T>& rayOrigin,
	const CGKVector3<T>& rayDirection,
	const CGKVector3<T>& sphereOrigin,
	const T& sphereRadius 
)
{
	CGKVector3<T> l = sphereOrigin - rayOrigin;
	T s = l.Dot(rayDirection);
	T ll = l.Dot(l);
	T rr = sphereRadius*sphereRadius;	

	if (s < T(0) && ll > rr) 
	{
	    return false;
	}

	T mm =ll - s*s;

	if (mm > rr)
	{
		return false;
	}

	T q = sqrt(rr - mm);

	if (ll > rr) 
	{
	   	t = s - q; 
	}
	else
	{
		t = s + q;
	}

	return true;
}
//-----------------------------------------------------------------------------
