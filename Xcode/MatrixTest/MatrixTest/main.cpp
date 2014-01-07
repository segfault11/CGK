//
//  main.cpp
//  MatrixTest
//
//  Created by Arno in Wolde Lübke on 04.01.14.
//  Copyright (c) 2014 Arno in Wolde Lübke. All rights reserved.
//

#include <iostream>
#include <CGK/Math/Matrix4.h>

int main(int argc, const char * argv[])
{
    CGKMatrix4f b;
    b[0] = CGKVector4f(0.0, 1.0, 0.0, 0.0);
    b.MakeIdentity();
    std::cout << b.ComputeDeterminant() << std::endl;
    return 0;
}

