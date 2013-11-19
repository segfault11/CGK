#ifndef CAMERA_H__
#define CAMERA_H__

#include "../Math/Vector3.h"
#include "../Math/Matrix4.h"
#include <string>
#include <list>

class CGKCamera
{
public:
    CGKCamera();
    ~CGKCamera();

    CGKCamera(
        const CGKVector3f& eye, 
        const CGKVector3f& f,
        const CGKVector3f& up,
        float fovy, 
        float aspect, 
        float near, 
        float far
    );

    /// Move camera for a distance [dist] in U, V and/or N direction, or in 
    /// an arbitrary direction.       
    void Move(const CGKVector3f& dir);
    void MoveU(float dist);
    void MoveV(float dist);
    void MoveN(float dist);
    void MoveUVN(float distU, float distV, float distN);
        
    /// Rotates the camera around U, V, N using Rodrigues formula.
    void RotateU(float ang);
    void RotateV(float ang);

    CGKCamera(const CGKCamera& orig);
    CGKCamera& operator=(const CGKCamera& orig);

    std::string ToString() const;

    const float* GetViewData() const;
    const float* GetPerspectiveData() const;

private:
    void updateViewData();
    void setPerspectiveData(
        float l, float r, 
        float b, float t, 
        float n, float f
    );

    CGKVector3f eye_;
    CGKVector3f u_, v_, n_;

    float fovy_, aspect_, near_, far_;
        
    CGKMatrix4f perspective;

    float data_[16];
    float perspectiveData_[16];
};

#endif /* end of include guard: CAMERA_H__ */