//-----------------------------------------------------------------------------
template<typename T>
CGKBox3<T>::CGKBox3(const CGKVector3<T>& v0, const CGKVector3<T>& v1)
{
    if (v0[0] < v1[0])
    {
        this->ll[0] = v0[0];
        this->ur[0] = v1[0];
    }
    else
    {
        this->ll[0] = v1[0];
        this->ur[0] = v0[0];
    }

    if (v0[1] < v1[1])
    {
        this->ll[1] = v0[1];
        this->ur[1] = v1[1];
    }
    else
    {
        this->ll[1] = v1[1];
        this->ur[1] = v0[1];
    }

    if (v0[2] < v1[2])
    {
        this->ll[2] = v0[2];
        this->ur[2] = v1[2];
    }
    else
    {
        this->ll[2] = v1[2];
        this->ur[2] = v0[2];
    }
}
//-----------------------------------------------------------------------------
template<typename T>
CGKBox3<T>::~CGKBox3()
{

}
//-----------------------------------------------------------------------------
template<typename T>
const CGKVector3<T>& CGKBox3<T>::GetLL() const
{
    return this->ll;
}
//-----------------------------------------------------------------------------
template<typename T>
const CGKVector3<T>& CGKBox3<T>::GetUR() const
{
    return this->ur;
}
//-----------------------------------------------------------------------------
