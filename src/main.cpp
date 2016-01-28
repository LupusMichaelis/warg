
#include "app.hpp"

#include <locale>

int main(int argc, char **argv)
{
	try
	{
		std::locale::global(std::locale(""));
		return warg::app::main(argc, argv);
	}
	catch(...)
	{
		std::cerr << "This is awful..." << std::endl;
		return EXIT_FAILURE;
	}
}

