#ifndef MATRIX4_H__
#define MATRIX4_H__
 
#include "Vector4.h"
#include "Vector3.h"
#include <string>

/// Declaration of a 4x4 Matrix. Note memory is layed out in ROW MAJOR 
/// fashion.
template<typename T>
class CGKMatrix4
{
public:
    CGKMatrix4() {};
    
    CGKMatrix4(
        const CGKVector4<T>& row0,
        const CGKVector4<T>& row1,
        const CGKVector4<T>& row2,
        const CGKVector4<T>& row3
    );
    
    ~CGKMatrix4() {};

    inline void Transpose();
    inline const CGKVector4<T>& operator[](unsigned int i) const;
    inline CGKVector4<T>& operator[](unsigned int i);
	inline CGKMatrix4<T> operator*(const CGKMatrix4<T>& m) const;
	inline CGKVector3<T> operator*(const CGKVector3<T>& v) const;
	inline CGKVector4<T> operator*(const CGKVector4<T>& v) const;

    /// Gets the raw data in form of a linear array with 16 elements.
    const T* GetData() const;


    /// Turns the matrix to an OpenGL perspective matrix. NOTE THAT THE 
    /// MATRIX IS STILL ROW MAJOR AND NEEDS TO BE TRANSPOSED WHEN BEING 
    /// PASSED TO OPENGL.
    inline void MakePerspective(
        const T& l, const T& r, 
        const T& b, const T& t, 
        const T& n, const T& f
    );

    /// Burns the matrix to an OpenGL perspective matrix. NOTE THAT THE 
    /// MATRIX IS STILL ROW MAJOR AND NEEDS TO BE TRANSPOSED WHEN BEING 
    /// PASSED TO OPENGL.
    inline void MakePerspective(
        const T& fovy, 
        const T& aspect, 
        const T& near,
        const T& far
    );

    /// Turns the matrix to an OpenGL view matrix.NOTE THAT THE 
    /// MATRIX IS STILL ROW MAJOR AND NEEDS TO BE TRANSPOSED WHEN BEING 
    /// PASSED TO OPENGL.
    ///
    /// @param eye The position of the camera.
    /// @param f The point the camera focuses on.
    /// @param up The orientation of the camera.
    inline void MakeView(    
        const CGKVector3<T>& eye, 
        const CGKVector3<T>& f,
        const CGKVector3<T>& up
    );

    inline void MakeViewInverse(    
        const CGKVector3<T>& eye, 
        const CGKVector3<T>& f,
        const CGKVector3<T>& up
    );    

    /// Turns the matrix to an OpenGL rotation matrix for the y axis. NOTE 
    /// THAT THE MATRIX IS STILL ROW MAJOR AND NEEDS TO BE TRANSPOSED WHEN 
    /// BEING PASSED TO OPENGL.
    inline void MakeRotationY(const T& angle);

    /// Turns the matrix to an OpenGL scale matrix. 
    ///
    /// NOTE: 
    /// THAT THE MATRIX IS STILL ROW MAJOR AND NEEDS TO BE TRANSPOSED WHEN 
    /// BEING PASSED TO OPENGL.
    inline void MakeScale(const T& sx, const T& sy, const T& sz);
	inline void MakeTranslation(const T& x, const T& y, const T& z);

    /// Fills the matrix with zeroes.        
    inline void MakeZero();

    /// Turns the matrix to an identity matrix.    
    inline void MakeIdentity();

    /// Computes the the determinant
    inline T ComputeDeterminant() const;

	/// Inverts the matrix. Returns false if the matrix cannot be inverted.
	inline bool Invert();

private:    
    CGKVector4<CGKVector4<T> > data_;
};

#include "Matrix4.inl"

typedef CGKMatrix4<float> CGKMatrix4f;

#endif /* end of include guard: MATRIX4_H__ */
