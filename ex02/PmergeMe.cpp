#include "PmergeMe.hpp"

void	mySwap(unsigned int& a, unsigned int& b)
{
	unsigned int s;

	s = a;
	a = b;
	b = s;
}

void	myCheckInput(char *input)
{
	for (size_t i = 0; input[i]; i++)
		if (!std::isdigit(input[i])) throw(std::runtime_error("invalid input"));
}

