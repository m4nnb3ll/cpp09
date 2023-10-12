#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <string>
#include <stdio.h>
#include <cmath>
#include <cctype>
#include <stack>

#define ASCII_RED "\x1B[31m"
#define ASCII_RESET "\x1B[0m"

class	RPN
{
public:
	RPN();
	RPN(std::string input);
	~RPN();
	int	getResult();
	static void	printError(const std::string& str);
private:
	std::stack<std::string>*	m_stack;
	void		fillStack(std::istringstream& iss);
	static int	calc(std::stack<std::string>& stack);
	static bool	isValid(const std::string& input);
	static int	add(std::stack<std::string>& stack);
	static int	subtract(std::stack<std::string>& stack);
	static int	multiply(std::stack<std::string>& stack);
	static int	divide(std::stack<std::string>& stack);
};
