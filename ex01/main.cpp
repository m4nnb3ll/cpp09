#include "RPN.hpp"

int main(int argc, char **argv)
{
	int res;

	if (argc != 2)
		exit(1);
	try
	{
		RPN	test(argv[1]);
		res = test.getResult();
		std::cout << "the result is: " << res << std::endl;
	}
	catch (std::exception& e)
	{
		RPN::printError(e.what());
	}
}
