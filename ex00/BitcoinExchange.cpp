#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
	: m_db(nullptr)
{
	BitcoinExchange::readDataBase();
}

BitcoinExchange::~BitcoinExchange()
{
	delete m_db;
}

bool	BitcoinExchange::checkMonthDay(std::istringstream& ss)
{
	short	days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	float	month, day;
	char	delim;

	return ((ss >> month && std::fmod(month, 1) == 0 && month > 0 && month < 12)
			&& ss.get(delim) && (delim == '-')
			&& (ss >> day && std::fmod(day, 1) == 0 && day > 0
				&& static_cast<short>(day) < days[static_cast<int>(month)]));
}

void	BitcoinExchange::checkDate(std::istringstream& ss)
{
	std::string			str;
	float				tmpFloat;
	char				delim;

	if (!std::getline(ss, str, '|')
		|| ss.str().find('|') == std::string::npos
		|| str.empty())
	{
		std::ostringstream	tmp;
		tmp << "Error: bad input.=> " << ss.str();
		throw(std::runtime_error(tmp.str()));
	}
	std::istringstream	localStream(str);
	// check if the date field is number and not a float
	if ((localStream >> tmpFloat && tmpFloat > 0 && !std::fmod(tmpFloat, 1))
		&& (localStream.get(delim) && (delim == '-'))
		&& BitcoinExchange::checkMonthDay(localStream))
		return ;
	throw(std::runtime_error("error: wrong date format."));
}

void	BitcoinExchange::checkValue(std::istringstream& ss)
{
	float		tmpFloat;

	if (!(ss >> tmpFloat))
		throw(std::runtime_error("error: wrong value format"));
	if (tmpFloat < 0)
		throw(std::runtime_error("Error: not a positive number."));
	if (tmpFloat > 1000)
		throw(std::runtime_error("Error: too large a number."));
}

void	BitcoinExchange::checkInputLine(const std::string& line)
{
	std::istringstream	ss(line);

	BitcoinExchange::checkDate(ss);
	BitcoinExchange::checkValue(ss);
}

void	BitcoinExchange::exchange(const char* fileName)
{
	float									tmpValue;
	std::string								line, tmpKey;
	std::map<std::string, float>::iterator	it;

    std::ifstream inputFile(fileName);
    if (!inputFile.is_open())
		throw(std::runtime_error("Error: could not open file."));
	if (!std::getline(inputFile, line)
		|| line != "date | value")
		throw(std::runtime_error("Please provide a valid input file!"));
	while (std::getline(inputFile, line))
	{
		try
		{
			BitcoinExchange::checkInputLine(line);
			std::istringstream	lineStream(line);
			std::getline(lineStream, tmpKey, '|');
			if (m_db->find(tmpKey) == m_db->end())
			{
				it = m_db->lower_bound(tmpKey);//std::prev(
				it = (it == m_db->begin()) ? it : std::prev(it);
				tmpKey = it->first;
			}
			lineStream >> tmpValue;
			std::cout << tmpKey << " => " << tmpValue << " = " << (*m_db)[tmpKey] * tmpValue << std::endl;
		}
		catch (std::exception& e)
		{
			std::cerr << e.what() << std::endl;
		}
	}
}

std::map<std::string, float>*	BitcoinExchange::readDataBase()
{
	std::string							line, tmpKey;
	float								tmpValue;

    // Open the CSV file
    std::ifstream inputFile("./data.csv");
    if (!inputFile.is_open())
		throw(std::runtime_error("couldn't open the file!"));
	if (!std::getline(inputFile, line)
		|| line != "date,exchange_rate")
		throw(std::runtime_error("Please provide a valid data file!"));
	m_db = new std::map<std::string, float>;
	while (std::getline(inputFile, line))
	{
		try
		{
			std::istringstream	lineStream(line);
			std::getline(lineStream, tmpKey, ',');
			lineStream >> tmpValue;
			(*m_db).insert(std::make_pair(tmpKey, tmpValue));
		}
		catch (std::exception& e)
		{
			std::cerr << e.what() << std::endl;
		}
	}
	return (m_db);
}
