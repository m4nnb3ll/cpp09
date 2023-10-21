#include "RPN.hpp"

RPN::RPN() {}

RPN::RPN(std::string input)
{
	std::istringstream iss(input);

	RPN::fillStack(iss);
}

RPN::~RPN() { }

RPN::RPN(const RPN& o)
{
	this->operator=(o);
}

RPN&	RPN::operator=(const RPN& o)
{
	if (this != &o)
		this -> m_stack = o.m_stack;
	return (*this);
}

int	RPN::getResult()
{
	int	res = 0;

	res = RPN::calc(m_stack);
	if (!m_stack.empty())
		throw(std::runtime_error("Error: bad RPN format"));
	return (res);
}

bool	RPN::isValid(const std::string& input)
{
	if (input.length() > 1
		|| (!std::isdigit(input[0])
			&& input[0] != '+' && input[0] != '-'
			&& input[0] != '*' && input[0] != '/'))
		return (false);
	return (true);
}

int	RPN::add(std::stack<std::string>& stack)
{
	return (RPN::calc(stack) + RPN::calc(stack));
}

int	RPN::subtract(std::stack<std::string>& stack)
{
	int	f, s;

	f = RPN::calc(stack);
	s = RPN::calc(stack);
	return (s - f);
}

int	RPN::multiply(std::stack<std::string>& stack)
{
	return (RPN::calc(stack) * RPN::calc(stack));
}

int	RPN::divide(std::stack<std::string>& stack)
{
	int	f, s;

	f = RPN::calc(stack);
	s = RPN::calc(stack);
	return (s / f);
}

int	RPN::calc(std::stack<std::string>& stack)
{
	const std::string&	token = stack.empty() ? "?" : stack.top();

	if (!isValid(token))
		throw(std::runtime_error("Error: bad RPN format"));
	if (std::isdigit(token[0]))
		return (stack.pop(), std::stoi(token));
	if (token == "+")
		return (stack.pop(), add(stack));
	if (token == "-")
		return (stack.pop(), subtract(stack));
	if (token == "*")
		return (stack.pop(), multiply(stack));
	if (token == "/")
		return (stack.pop(), divide(stack));
	throw(std::runtime_error("Error: bad RPN format"));
}

void	RPN::fillStack(std::istringstream& iss)
{
	std::string	token;

	while ((iss >> token))
	{
		if (!isValid(token))
			throw(std::runtime_error("Error: Invalid Token!"));
		m_stack.push(token);
	}
}

void	RPN::printError(const std::string& str)
{
	std::cerr << ASCII_RED;
	std::cerr << str;
	std::cerr << ASCII_RESET;
	std::cerr << std::endl;
}