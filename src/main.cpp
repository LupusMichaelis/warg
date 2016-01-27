
#include "app.h"

int main(int argc, char **argv)
{
	try
	{
		return warg::app::main(argc, argv);
	}
	catch(...)
	{
		std::cerr << "This is awful..." << std::endl;
		return EXIT_FAILURE;
	}
}

