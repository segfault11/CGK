#include <CGK/Grid/Grid1.h>
#include <iostream>


float bla(const float& b)
{
	return b;
}

int main(int argc, const char *argv[])
{
    CGKGrid1f grid(0.0, 1.0, 0.02);
	grid.SetDataWithFunc(bla);


	for (unsigned int i = 0; i < grid.GetSize(); i++)
	{
		std::cout << grid[i] << std::endl;
	}


    return 0;
}
