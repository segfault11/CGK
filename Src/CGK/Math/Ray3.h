#ifndef RAY_H
#define RAY_H

#include "Vector3.h"
#include "../Util.h"

template<typename T>
class CGKRay3 
{
public:
    CGKRay3(const CGKVector3<T>& origin, const CGKVector3<T>& direction);
    virtual ~CGKRay3();

    DEF_MEMBER_RW( Origin, CGKVector3<T>, origin )
    DEF_MEMBER_RW( Direction, CGKVector3<T>, direction )

private:
    CGKVector3<T> origin;
    CGKVector3<T> direction;
};

typedef CGKRay3<float> CGKRay3f;

#endif /* end of include guard: RAY_H */
