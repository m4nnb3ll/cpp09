#include "BitcoinExchange.hpp"

int main(int argc, char **argv)
{
	BitcoinExchange	test;
	if (argc != 2)
		(printf("invalid args!\n"), exit(1));
	try
	{
		test.exchange(argv[1]);
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
}
