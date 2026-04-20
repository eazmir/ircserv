#include "../include/server.hpp"
#include "../include/utls.hpp"

int	main(int argc, char *argv[])
{
	try
	{
		if (argc != 3)
			throw std::runtime_error("Error");
		server server(Utils::validatePort(argv[1]), argv[2]);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}	
}