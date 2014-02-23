//-----------------------------------------------------------------------------
template<typename T>
CGKMatrix4<T>::CGKMatrix4(
    const CGKVector4<T>& row0,
    const CGKVector4<T>& row1,
    const CGKVector4<T>& row2,
    const CGKVector4<T>& row3
)
{
    data_[0] = row0;
    data_[1] = row1;
    data_[2] = row2;
    data_[3] = row3;
}
//------------------------------------------------------------------------------
template<typename T>
CGKVector4<T>& CGKMatrix4<T>::operator[](unsigned int i)
{
    return data_[i];
}
//------------------------------------------------------------------------------
template<typename T>
const CGKVector4<T>& CGKMatrix4<T>::operator[](unsigned int i) const
{
    return data_[i];
}
//-----------------------------------------------------------------------------
template<typename T>
CGKVector3<T> CGKMatrix4<T>::operator*(const CGKVector3<T>& v) const
{
	T x = data_[0][0]*v[0] + data_[0][1]*v[1] + data_[0][2]*v[2] + data_[0][3];
	T y = data_[1][0]*v[0] + data_[1][1]*v[1] + data_[1][2]*v[2] + data_[1][3];
	T z = data_[2][0]*v[0] + data_[2][1]*v[1] + data_[2][2]*v[2] + data_[2][3];
	T w = data_[3][0]*v[0] + data_[3][1]*v[1] + data_[3][2]*v[2] + data_[3][3];

	return CGKVector3<T>(x/w, y/w, z/w);
}
//-----------------------------------------------------------------------------
template<typename T>
CGKVector4<T> CGKMatrix4<T>::operator*(const CGKVector4<T>& v) const
{
	T x = data_[0][0]*v[0] + data_[0][1]*v[1] + data_[0][2]*v[2] + data_[0][3]*v[3];
	T y = data_[1][0]*v[0] + data_[1][1]*v[1] + data_[1][2]*v[2] + data_[1][3]*v[3];
	T z = data_[2][0]*v[0] + data_[2][1]*v[1] + data_[2][2]*v[2] + data_[2][3]*v[3];
	T w = data_[3][0]*v[0] + data_[3][1]*v[1] + data_[3][2]*v[2] + data_[3][3]*v[3];

	return CGKVector4<T>(x, y, z, w);
}
//-----------------------------------------------------------------------------
template<typename T>
CGKMatrix4<T> CGKMatrix4<T>::operator*(const CGKMatrix4<T>& m) const
{
	CGKMatrix4<T> res;

	for (int i = 0; i < 4; i++) 
	{
	    for (int j = 0; j < 4; j++) 
	    {
	        for (int k = 0; k < 4; k++) 
	        {
	            res[i][j] += data_[i][k] * m[k][j];
	        }
	    }
	}

	return res;
}
//-----------------------------------------------------------------------------
template<typename T>
void CGKMatrix4<T>::Transpose()
{
    unsigned int k = 1;
    for (unsigned int i = 0; i < 4; i++)
    {
        for (unsigned int j = k; j < 4; j++)
        {
            T ele = (*this)[i][j];
            (*this)[i][j] = (*this)[j][i];
            (*this)[j][i] = ele;
        }
        k++;
    }
}
//------------------------------------------------------------------------------
template<typename T>
const T* CGKMatrix4<T>::GetData() const
{
    return &data_[0][0];
}
//------------------------------------------------------------------------------
template<typename T>
inline void CGKMatrix4<T>::MakeScale(const T& sx, const T& sy, const T& sz)
{
	this->MakeZero();
	data_[0][0] = sx;
	data_[1][1] = sy;
	data_[2][2] = sz;
	data_[3][3] = T(1);
}
//-----------------------------------------------------------------------------
template<typename T>
inline void CGKMatrix4<T>::MakeTranslation(const T& x, const T& y, const T& z)
{
	this->MakeIdentity();
	data_[0][3] = x;
	data_[1][3] = y;
	data_[2][3] = z;
}
//-----------------------------------------------------------------------------
template<typename T>
void CGKMatrix4<T>::MakePerspective(
    const T& fovy, 
    const T& aspect, 
    const T& near, 
    const T& far
)
{
    T t = tanf(fovy/2.0);
    T h = near*t;
    T w = h*aspect;

    this->MakePerspective(-w, w, -h, h, near, far);
}
//------------------------------------------------------------------------------
template<typename T>
void CGKMatrix4<T>::MakePerspective(
    const T& l, const T& r, 
    const T& b, const T& t, 
    const T& n, const T& f
)
{
    T* raw = static_cast<T*>(data_[0]);

    raw[0] = 2.0f*n/(r - l);
    raw[1] = 0.0f;
    raw[2] = 0.0f;
    raw[3] = 0.0f;

    raw[4] = 0.0f;
    raw[5] = 2.0f*n/(t - b);
    raw[6] = 0.0f;
    raw[7] = 0.0f;

    raw[8] = (r + l)/(r - l);
    raw[9] = (t + b)/(t - b);
    raw[10] = -(f + n)/(f - n);
    raw[11] = -1.0f;

    raw[12] = 0.0f;
    raw[13] = 0.0f;
    raw[14] = -2.0f*f*n/(f - n);
    raw[15] = 0.0f;     

    this->Transpose();
}
//------------------------------------------------------------------------------
template<typename T>
void CGKMatrix4<T>::MakeView(    
    const CGKVector3<T>& eye, 
    const CGKVector3<T>& f,
    const CGKVector3<T>& up
)
{
    CGKVector3<T> n = eye - f;
    n.Normalize();

    CGKVector3<T> u = up.Cross(n);
    u.Normalize();

    CGKVector3<T> v = n.Cross(u);

    T* raw = static_cast<T*>(data_[0]);

    raw[0] = u[0];
    raw[4] = u[1];
    raw[8] = u[2];
    raw[12] = -u.Dot(eye);

    raw[1] = v[0];
    raw[5] = v[1];
    raw[9] = v[2];
    raw[13] = -v.Dot(eye);   

    raw[2] = n[0];
    raw[6] = n[1];
    raw[10] = n[2];
    raw[14] = -n.Dot(eye);   

    raw[3] = 0.0f;
    raw[7] = 0.0f;
    raw[11] = 0.0f;
    raw[15] = 1.0f;

    this->Transpose();
}
//------------------------------------------------------------------------------
template<typename T>
void CGKMatrix4<T>::MakeViewInverse(    
    const CGKVector3<T>& eye, 
    const CGKVector3<T>& f,
    const CGKVector3<T>& up
)
{
    CGKVector3<T> n = eye - f;
    n.Normalize();

    CGKVector3<T> u = up.Cross(n);
    u.Normalize();

    CGKVector3<T> v = n.Cross(u);

    T* raw = static_cast<T*>(data_[0]);

    raw[0] = u[0];
    raw[4] = u[1];
    raw[8] = u[2];
    raw[12] = 0;

    raw[1] = v[0];
    raw[5] = v[1];
    raw[9] = v[2];
    raw[13] = 0;   

    raw[2] = n[0];
    raw[6] = n[1];
    raw[10] = n[2];
    raw[14] = 0;   

    raw[3] = eye[0];
    raw[7] = eye[1];
    raw[11] = eye[2];
    raw[15] = 1.0f;
}
//------------------------------------------------------------------------------
template<typename T>
void CGKMatrix4<T>::MakeIdentity()
{
    for (unsigned int i = 0; i < 4; i++)
    {
        for (unsigned int j = 0; j < 4; j++)
        {
            if (i == j)
            {
                data_[i][j] = static_cast<T>(1);
            }
            else
            {
                data_[i][j] = static_cast<T>(0);
            }
        }
    }
}
//------------------------------------------------------------------------------
template<typename T>
void CGKMatrix4<T>::MakeZero()
{
    for (unsigned int i = 0; i < 4; i++)
    {
        for (unsigned int j = 0; j < 4; j++)
        {
            data_[i][j] = static_cast<T>(0);
        }
    }
}
//------------------------------------------------------------------------------
template<typename T>
void CGKMatrix4<T>::MakeRotationY(const T& angle)
{
    this->MakeZero();

    (*this)[0][0] = std::cos(angle);
    (*this)[0][2] = std::sin(angle);
    (*this)[1][1] = static_cast<T>(1);
    (*this)[2][0] = -std::sin(angle);
    (*this)[2][2] = std::cos(angle);    
    (*this)[3][3] = static_cast<T>(1);
}
//------------------------------------------------------------------------------
template<typename T>
inline T CGKMatrix4<T>::ComputeDeterminant() const
{
    #define a(i,j) data_[i][j]
    float det;
    
    det = a(0,0)*(a(1,1)*a(2,2)*a(3,3)+a(1,2)*a(2,3)*a(3,1)+a(1,3)*a(2,1)*a(3,2)
                 -a(1,1)*a(2,3)*a(3,2)-a(1,2)*a(2,1)*a(3,3)-a(1,3)*a(2,2)*a(3,1))
        + a(0,1)*(a(1,0)*a(2,3)*a(3,2)+a(1,2)*a(2,0)*a(3,3)+a(1,3)*a(2,2)*a(3,0)
                 -a(1,0)*a(2,2)*a(3,3)-a(1,2)*a(2,3)*a(3,0)-a(1,3)*a(2,0)*a(3,2))
        + a(0,2)*(a(1,0)*a(2,1)*a(3,3)+a(1,1)*a(2,3)*a(3,0)+a(1,3)*a(2,0)*a(3,1)
                 -a(1,0)*a(2,3)*a(3,1)-a(1,1)*a(2,0)*a(3,3)-a(1,3)*a(2,1)*a(3,0))
        + a(0,3)*(a(1,0)*a(2,2)*a(3,1)+a(1,1)*a(2,0)*a(3,2)+a(1,2)*a(2,1)*a(3,0)
                 -a(1,0)*a(2,1)*a(3,2)-a(1,1)*a(2,2)*a(3,0)-a(1,2)*a(2,0)*a(3,1));
    
    #undef a // end of a
    return det;
}
//------------------------------------------------------------------------------
template<typename T>
bool CGKMatrix4<T>::Invert()
{
	this->Transpose();
    T inv[16], det;
    T* m = &data_[0][0];

    inv[0] = m[5]  * m[10] * m[15] - 
             m[5]  * m[11] * m[14] - 
             m[9]  * m[6]  * m[15] + 
             m[9]  * m[7]  * m[14] +
             m[13] * m[6]  * m[11] - 
             m[13] * m[7]  * m[10];

    inv[4] = -m[4]  * m[10] * m[15] + 
              m[4]  * m[11] * m[14] + 
              m[8]  * m[6]  * m[15] - 
              m[8]  * m[7]  * m[14] - 
              m[12] * m[6]  * m[11] + 
              m[12] * m[7]  * m[10];

    inv[8] = m[4]  * m[9] * m[15] - 
             m[4]  * m[11] * m[13] - 
             m[8]  * m[5] * m[15] + 
             m[8]  * m[7] * m[13] + 
             m[12] * m[5] * m[11] - 
             m[12] * m[7] * m[9];

    inv[12] = -m[4]  * m[9] * m[14] + 
               m[4]  * m[10] * m[13] +
               m[8]  * m[5] * m[14] - 
               m[8]  * m[6] * m[13] - 
               m[12] * m[5] * m[10] + 
               m[12] * m[6] * m[9];

    inv[1] = -m[1]  * m[10] * m[15] + 
              m[1]  * m[11] * m[14] + 
              m[9]  * m[2] * m[15] - 
              m[9]  * m[3] * m[14] - 
              m[13] * m[2] * m[11] + 
              m[13] * m[3] * m[10];

    inv[5] = m[0]  * m[10] * m[15] - 
             m[0]  * m[11] * m[14] - 
             m[8]  * m[2] * m[15] + 
             m[8]  * m[3] * m[14] + 
             m[12] * m[2] * m[11] - 
             m[12] * m[3] * m[10];

    inv[9] = -m[0]  * m[9] * m[15] + 
              m[0]  * m[11] * m[13] + 
              m[8]  * m[1] * m[15] - 
              m[8]  * m[3] * m[13] - 
              m[12] * m[1] * m[11] + 
              m[12] * m[3] * m[9];

    inv[13] = m[0]  * m[9] * m[14] - 
              m[0]  * m[10] * m[13] - 
              m[8]  * m[1] * m[14] + 
              m[8]  * m[2] * m[13] + 
              m[12] * m[1] * m[10] - 
              m[12] * m[2] * m[9];

    inv[2] = m[1]  * m[6] * m[15] - 
             m[1]  * m[7] * m[14] - 
             m[5]  * m[2] * m[15] + 
             m[5]  * m[3] * m[14] + 
             m[13] * m[2] * m[7] - 
             m[13] * m[3] * m[6];

    inv[6] = -m[0]  * m[6] * m[15] + 
              m[0]  * m[7] * m[14] + 
              m[4]  * m[2] * m[15] - 
              m[4]  * m[3] * m[14] - 
              m[12] * m[2] * m[7] + 
              m[12] * m[3] * m[6];

    inv[10] = m[0]  * m[5] * m[15] - 
              m[0]  * m[7] * m[13] - 
              m[4]  * m[1] * m[15] + 
              m[4]  * m[3] * m[13] + 
              m[12] * m[1] * m[7] - 
              m[12] * m[3] * m[5];

    inv[14] = -m[0]  * m[5] * m[14] + 
               m[0]  * m[6] * m[13] + 
               m[4]  * m[1] * m[14] - 
               m[4]  * m[2] * m[13] - 
               m[12] * m[1] * m[6] + 
               m[12] * m[2] * m[5];

    inv[3] = -m[1] * m[6] * m[11] + 
              m[1] * m[7] * m[10] + 
              m[5] * m[2] * m[11] - 
              m[5] * m[3] * m[10] - 
              m[9] * m[2] * m[7] + 
              m[9] * m[3] * m[6];

    inv[7] = m[0] * m[6] * m[11] - 
             m[0] * m[7] * m[10] - 
             m[4] * m[2] * m[11] + 
             m[4] * m[3] * m[10] + 
             m[8] * m[2] * m[7] - 
             m[8] * m[3] * m[6];

    inv[11] = -m[0] * m[5] * m[11] + 
               m[0] * m[7] * m[9] + 
               m[4] * m[1] * m[11] - 
               m[4] * m[3] * m[9] - 
               m[8] * m[1] * m[7] + 
               m[8] * m[3] * m[5];

    inv[15] = m[0] * m[5] * m[10] - 
              m[0] * m[6] * m[9] - 
              m[4] * m[1] * m[10] + 
              m[4] * m[2] * m[9] + 
              m[8] * m[1] * m[6] - 
              m[8] * m[2] * m[5];

    det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

    if (det == 0)
    {
		this->Transpose();
        return false;
    }

    det = 1.0 / det;

    for (int i = 0; i < 16; i++)
    {
        m[i] = inv[i] * det;
    }

    this->Transpose();

	return true;
}
//-----------------------------------------------------------------------------
