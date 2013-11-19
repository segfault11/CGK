//------------------------------------------------------------------------------
#include "Camera.h"
#include <sstream>
#include <iostream>
//------------------------------------------------------------------------------
CGKCamera::CGKCamera()
:
    eye_(0.0f, 0.0f, 0.0f),
    u_(1.0f, 0.0f, 0.0f),
    v_(0.0f, 1.0f, 0.0f),
    n_(0.0f, 0.0f, 1.0f)
{
    this->updateViewData();
}
//------------------------------------------------------------------------------
CGKCamera::~CGKCamera()
{
    
}
//------------------------------------------------------------------------------
CGKCamera::CGKCamera(            
    const CGKVector3f& eye, 
    const CGKVector3f& f,
    const CGKVector3f& up,
    float fovy, 
    float aspect, 
    float near, 
    float far    
)
: fovy_(fovy), aspect_(aspect), near_(near), far_(far)
{
    // init view matrix
    eye_ = eye;

    n_ = eye - f;
    n_.Normalize();

    u_ = up.Cross(n_);
    u_.Normalize();

    v_ = n_.Cross(u_);

    this->updateViewData();

    // init projection matrix
    float t = tanf((fovy/2.0)*(3.141593f/180.0f));
    float h = near*t;
    float w = h*aspect;

    this->setPerspectiveData(-w, w, -h, h, near, far);
}
//------------------------------------------------------------------------------
CGKCamera& CGKCamera::operator=(const CGKCamera& orig)
{
    this->eye_ = orig.eye_;
    this->u_ = orig.u_;
    this->v_ = orig.v_;
    this->n_ = orig.n_;

    this->fovy_ = orig.fovy_;
    this->aspect_ = orig.aspect_;
    this->near_ = orig.near_;
    this->far_ = orig.far_;

    for (unsigned int i = 0; i < 16; i++)
    {
        this->data_[i] = orig.data_[i];
        this->perspectiveData_[i] = orig.perspectiveData_[i];
    }

    return *this;
}
//------------------------------------------------------------------------------
CGKCamera::CGKCamera(const CGKCamera& orig)
{
    *this = orig;
}
//------------------------------------------------------------------------------
const float* CGKCamera::GetViewData() const 
{
    return data_;
}
//------------------------------------------------------------------------------
const float* CGKCamera::GetPerspectiveData() const
{
    return perspectiveData_;
}
//------------------------------------------------------------------------------
std::string CGKCamera::ToString() const
{
    std::stringstream s;

    s << "[ ";

    for (unsigned int i = 0; i < 16; i++)
    {
        s << data_[i] << " ";
    }

    s << "]";

    return s.str();
}
//------------------------------------------------------------------------------
void CGKCamera::Move(const CGKVector3f& dir)
{
    eye_ += dir;

    this->updateViewData();   
}
//------------------------------------------------------------------------------
void CGKCamera::MoveU(float dist)
{
    this->Move(u_*dist);
}
//------------------------------------------------------------------------------
void CGKCamera::MoveV(float dist)
{
    this->Move(v_*dist);
}
//------------------------------------------------------------------------------
void CGKCamera::MoveN(float dist)
{
    this->Move(n_*dist);
}
//------------------------------------------------------------------------------
void CGKCamera::MoveUVN(float distU, float distV, float distN)
{
    CGKVector3f dir = u_*distU + v_*distV + n_*distN;
    this->Move(dir);
}
//------------------------------------------------------------------------------
void CGKCamera::RotateU(float ang)
{
    v_ = v_*cos(ang) + u_.Cross(v_)*sin(ang) + u_*(u_.Dot(v_)*(1.0f - cos(ang)));
    n_ = n_*cos(ang) + u_.Cross(n_)*sin(ang) + u_*(u_.Dot(n_)*(1.0f - cos(ang)));
    this->updateViewData();
}
//------------------------------------------------------------------------------
void CGKCamera::RotateV(float ang)
{
    u_ = u_*cos(ang) + v_.Cross(u_)*sin(ang) + v_*(v_.Dot(u_)*(1.0f - cos(ang)));
    n_ = n_*cos(ang) + v_.Cross(n_)*sin(ang) + v_*(v_.Dot(n_)*(1.0f - cos(ang)));
    this->updateViewData();
}
//------------------------------------------------------------------------------
void CGKCamera::updateViewData()
{
    data_[0] = u_[0];
    data_[4] = u_[1];
    data_[8] = u_[2];
    data_[12] = -u_.Dot(eye_);

    data_[1] = v_[0];
    data_[5] = v_[1];
    data_[9] = v_[2];
    data_[13] = -v_.Dot(eye_);   

    data_[2] = n_[0];
    data_[6] = n_[1];
    data_[10] = n_[2];
    data_[14] = -n_.Dot(eye_);   

    data_[3] = 0.0f;
    data_[7] = 0.0f;
    data_[11] = 0.0f;
    data_[15] = 1.0f;
}
//------------------------------------------------------------------------------
void CGKCamera::setPerspectiveData(
    float l, float r, 
    float b, float t, 
    float n, float f
)
{
    perspectiveData_[0] = 2.0f*n/(r - l);
    perspectiveData_[1] = 0.0f;
    perspectiveData_[2] = 0.0f;
    perspectiveData_[3] = 0.0f;

    perspectiveData_[4] = 0.0f;
    perspectiveData_[5] = 2.0f*n/(t - b);
    perspectiveData_[6] = 0.0f;
    perspectiveData_[7] = 0.0f;

    perspectiveData_[8] = (r + l)/(r - l);
    perspectiveData_[9] = (t + b)/(t - b);
    perspectiveData_[10] = -(f + n)/(f - n);
    perspectiveData_[11] = -1.0f;

    perspectiveData_[12] = 0.0f;
    perspectiveData_[13] = 0.0f;
    perspectiveData_[14] = -2.0f*f*n/(f - n);
    perspectiveData_[15] = 0.0f;     
}
//------------------------------------------------------------------------------