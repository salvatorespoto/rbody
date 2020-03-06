// main.cpp

#define GLFW_INCLUDE_NONE

#include <iostream>

#include "Viewer.h"



int main()
{
	try
	{
		Viewer::GetInstance().Run();
	}
	catch (const std::exception & e)
	{
		std::cout << "Exception: [ " << e.what() << " ]" << std::endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}