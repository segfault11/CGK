#ifndef BOX3_H
#define BOX3_H

#include "Vector3.h"


template<typename T>
class CGKBox3
{
public:
    CGKBox3(const CGKVector3<T>& v0, const CGKVector3<T>& v1);
    ~CGKBox3();

    const CGKVector3<T>& GetLL() const;
    const CGKVector3<T>& GetUR() const;

private:
    CGKVector3<T> ll;
    CGKVector3<T> ur;
};

#include "Box3.inl"

typedef CGKBox3<float> CGKBox3f;

#endif /* end of include guard: BOX3_H */
