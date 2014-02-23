//-----------------------------------------------------------------------------
template<typename T>
CGKMatrix3<T>::CGKMatrix3(
    const CGKVector3<T>& row0,
    const CGKVector3<T>& row1,
    const CGKVector3<T>& row2
)
{
    data_[0] = row0;
    data_[1] = row1;
    data_[2] = row2;
}
//------------------------------------------------------------------------------
template<typename T>
CGKVector3<T>& CGKMatrix3<T>::operator[](unsigned int i)
{
    return data_[i];
}
//------------------------------------------------------------------------------
template<typename T>
const CGKVector3<T>& CGKMatrix3<T>::operator[](unsigned int i) const
{
    return data_[i];
}
//-----------------------------------------------------------------------------
template<typename T>
CGKVector3<T> CGKMatrix3<T>::operator*(const CGKVector3<T>& v) const
{
	T x = data_[0][0]*v[0] + data_[0][1]*v[1] + data_[0][2]*v[2];
	T y = data_[1][0]*v[0] + data_[1][1]*v[1] + data_[1][2]*v[2];
	T z = data_[2][0]*v[0] + data_[2][1]*v[1] + data_[2][2]*v[2];

	return CGKVector3<T>(x, y, z);
}
//-----------------------------------------------------------------------------
template<typename T>
CGKMatrix3<T> CGKMatrix3<T>::operator*(const CGKMatrix3<T>& m) const
{
	CGKMatrix3<T> res;

	for (int i = 0; i < 3; i++)
	{
	    for (int j = 0; j < 3; j++)
	    {
	        for (int k = 0; k < 3; k++)
	        {
	            res[i][j] += data_[i][k] * m[k][j];
	        }
	    }
	}

	return res;
}
//-----------------------------------------------------------------------------
template<typename T>
void CGKMatrix3<T>::Transpose()
{
    unsigned int k = 1;
    for (unsigned int i = 0; i < 3; i++)
    {
        for (unsigned int j = k; j < 3; j++)
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
const T* CGKMatrix3<T>::GetData() const
{
    return &data_[0][0];
}
//------------------------------------------------------------------------------
template<typename T>
void CGKMatrix3<T>::MakeIdentity()
{
    for (unsigned int i = 0; i < 3; i++)
    {
        for (unsigned int j = 0; j < 3; j++)
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
void CGKMatrix3<T>::MakeZero()
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
bool CGKMatrix3<T>::Invert()
{
    CGKMatrix3 m;

    T det = data_[0][0]*data_[1][1]*data_[2][2]
          + data_[1][0]*data_[2][1]*data_[0][2]
          + data_[2][0]*data_[0][1]*data_[1][2]
          - data_[0][0]*data_[2][1]*data_[1][2]
          - data_[2][0]*data_[1][1]*data_[0][2]
          - data_[1][0]*data_[0][1]*data_[2][2];

    if (det == static_cast<T>(0))
    {
        return false;
    }


    m[0][0] = (data_[1][1]*data_[2][2] - data_[1][2]*data_[2][1])/det;
    m[0][1] = (data_[0][2]*data_[2][1] - data_[0][1]*data_[2][2])/det;
    m[0][2] = (data_[0][1]*data_[1][2] - data_[0][2]*data_[1][1])/det;
    
    m[1][0] = (data_[1][2]*data_[2][0] - data_[1][0]*data_[2][2])/det;
    m[1][1] = (data_[0][0]*data_[2][2] - data_[0][2]*data_[2][0])/det;
    m[1][2] = (data_[0][2]*data_[1][0] - data_[0][0]*data_[1][2])/det;
    
    m[2][0] = (data_[1][0]*data_[2][1] - data_[1][1]*data_[2][0])/det;
    m[2][1] = (data_[0][1]*data_[2][0] - data_[0][0]*data_[2][1])/det;
    m[2][2] = (data_[0][0]*data_[1][1] - data_[0][1]*data_[1][0])/det;
    
    *this = m;
    
    return true;
}
//------------------------------------------------------------------------------
template<typename T>
void CGKMatrix3<T>::Dump() const
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            std::cout << (*this)[i][j] << " ";
        }
        
        std::cout << std::endl;
    }
}
//------------------------------------------------------------------------------