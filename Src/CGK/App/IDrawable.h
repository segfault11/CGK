#ifndef IDRAWABLE_H__
#define IDRAWABLE_H__

#include "IObject.h"

class CGKAppIDrawable : public CGKAppIObject
{
public:
    CGKAppIDrawable() {};
    ~CGKAppIDrawable() {};

    virtual void Draw() = 0;
};    
 
#endif /* end of include guard: IDRAWABLE_H__ */
