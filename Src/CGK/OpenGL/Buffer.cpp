//-----------------------------------------------------------------------------
#include "Buffer.h"
#include "../Error/Error.h"
#include <cmath>
#include <vector>
#include "../Math/Vector3.h"
//-----------------------------------------------------------------------------
GLuint CGKOpenGLBufferCreateAsMeshWithHeightField(
	const CGKVector2f& start,
	const CGKVector2f& end,
	float dx,
	float (*f)(const CGKVector2f&)
)
{
	// assert start > end
	unsigned int numSamplesX =  std::ceil(end[0] - start[0]);
	unsigned int numSamplesZ =  std::ceil(end[1] - start[1]);

	std::vector<CGKVector3f>* mesh = new std::vector<CGKVector3f>(
			6*numSamplesX*numSamplesZ
		);

	if (!mesh) 
	{
	    return 0;
	}

	for (unsigned int i = 0; i < numSamplesZ; i++)
	{                          
	    for (unsigned int j = 0; j < numSamplesX; j++)
	    {                          
	    	float x = start[0] + dx*j;
			float z = start[1] + dx*i;
			float x2 = x + dx;
			float z2 = z;
			float x3 = x + dx;
			float z3 = z + dx;
			float x4 = x;
			float z4 = z + dx;

			mesh->push_back(CGKVector3f(x, (*f)(CGKVector2f(x, z)), z));   
			mesh->push_back(CGKVector3f(x2, (*f)(CGKVector2f(x2, z2)), z2));
			mesh->push_back(CGKVector3f(x3, (*f)(CGKVector2f(x3, z3)), z3));
			mesh->push_back(CGKVector3f(x, (*f)(CGKVector2f(x, z)), z));
			mesh->push_back(CGKVector3f(x3, (*f)(CGKVector2f(x3, z3)), z3));
			mesh->push_back(CGKVector3f(x4, (*f)(CGKVector2f(x4, z4)), z4));
	    }                       
                                  
	}

	GLuint buffer;
	
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);

	glBufferData(
		GL_ARRAY_BUFFER, 
		sizeof(float)*6*numSamplesX*numSamplesZ, 
		mesh->data(), 
		GL_STATIC_DRAW
	);	

	delete mesh;
	return buffer;
}
//-----------------------------------------------------------------------------
