#ifndef MATRIX3_H__
#define MATRIX3_H__

#include "Vector3.h"
#include <string>
#include <istream>

template<typename T>
class CGKMatrix3
{
public:
    CGKMatrix3() {};
    
    CGKMatrix3(
        const CGKVector3<T>& row0,
        const CGKVector3<T>& row1,
        const CGKVector3<T>& row2
    );
    
    ~CGKMatrix3() {};

    inline void Transpose();
    inline const CGKVector3<T>& operator[](unsigned int i) const;
    inline CGKVector3<T>& operator[](unsigned int i);
    inline CGKMatrix3<T> operator*(const CGKMatrix3<T>& m) const;
    inline CGKVector3<T> operator*(const CGKVector3<T>& v) const;

    const T* GetData() const;

    /// Computes the the determinant
    inline T ComputeDeterminant() const;

	/// Inverts the matrix. Returns false if the matrix cannot be inverted.
	inline bool Invert();

    void MakeIdentity();
    void MakeZero();
    
    void Dump() const;

private:    
    CGKVector3<CGKVector3<T> > data_;
};

#include "Matrix3.inl"

typedef CGKMatrix3<float> CGKMatrix3f;

#endif /* end of include guard: MATRIX4_H__ */
