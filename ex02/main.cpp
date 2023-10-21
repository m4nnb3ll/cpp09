#include "PmergeMe.hpp"

int main(int ac, char *av[])
{
	if (ac < 2)
		return (1);
	try
	{
		std::vector<unsigned int> vec;
		for (int i = 1; i < ac; i++)
			(myCheckInput(av[i]), vec.push_back(std::atoi(av[i])));
		myPrint("Before is: ", vec);
		double	duration = fordJohnson(vec, true);
		std::cout << "Time to process a range of ";
		std::cout << ac - 1 << " elements with std::[vector] : ";
		std::cout << duration << " us" << std::endl;
		// deque below
		std::deque<unsigned int> deq;
		for (int i = 1; i < ac; i++)
			(myCheckInput(av[i]), deq.push_back(std::atoi(av[i])));
		duration = fordJohnson(deq, false);
		std::cout << "Time to process a range of ";
		std::cout << ac - 1 << " elements with std::[deque] : ";
		std::cout << duration << " us" << std::endl;
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return (1);
	}
	return (0);
}