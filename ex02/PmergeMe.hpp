#include <iostream>
#include <vector>
#include <deque>
#include <ctime>

void	mySwap(unsigned int& a, unsigned int& b);
void	myCheckInput(char *input);

template <typename T>
void	myPrint(std::string s, T& toPrint)
{
	std::cout << s;
	for (size_t i = 0; i < toPrint.size(); i++)
		std::cout << toPrint[i] << " ";
	std::cout << std::endl;
}

template <typename T>
double	fordJohnson(T& c, bool print)
{
	T		l, r;
	clock_t	startTime, endTime;

	startTime = clock();// getting start time

	for (size_t	i = 0; i + 1 < c.size(); i += 2)
		if (c[i + 1] < c[i]) ::mySwap(c[i], c[i + 1]);

	for (size_t i = 0; i < c.size(); i++)//push the even
    	if (i % 2 == 0) l.push_back(c[i]);
	for (size_t i = 0; i < c.size(); i++)//push the odd
    	if (i % 2) r.push_back(c[i]);

	std::sort(l.begin(), l.end());
	for (size_t i = 0; i < r.size(); i++)
        l.insert(std::lower_bound(l.begin(), l.end(), r[i]), r[i]);
	if (print)
		myPrint("After is: ", l);
	endTime = clock();// getting end time
	double duration = static_cast<double>(endTime - startTime) / CLOCKS_PER_SEC * 1000000.0;
    return (duration);
}
