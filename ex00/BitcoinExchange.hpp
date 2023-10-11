#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <string>
#include <stdio.h>
#include <cmath>

class	BitcoinExchange
{
public:
	BitcoinExchange();
	~BitcoinExchange();
	void							exchange(const char* fileName);
	static bool						checkMonthDay(std::istringstream& ss);
	static void						checkDate(std::istringstream& ss);
	static void						checkValue(std::istringstream& ss);
	static void						checkInputLine(const std::string& line);

private:
	std::map<std::string, float>*	m_db;
	std::map<std::string, float>*	readDataBase();
};