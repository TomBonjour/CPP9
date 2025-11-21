/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobourge <tobourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 13:16:04 by tobourge          #+#    #+#             */
/*   Updated: 2025/10/30 11:23:51 by tobourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

typedef std::map<std::string, float> map_t;


bool    isEmpty(std::string line)
{
    int i = 0;
    while (line[i])
    {
        if (!isblank(line[i]))
            return false;
        i++;
    }
    return true;
}

float    convertValue(float val, map_t::iterator it)
{
    return (val * it->second);
}

void    findInDatabase(std::string date, float val, map_t datamap)
{
    for (map_t::iterator it = datamap.begin(); it->first <= date; it++)
    {
        if (it->first == date)
            std::cout << date << " => " << val << " = " << val * it->second << std::endl;
        else if (it->first > date)
            std::cout << date << " => " << val << " = " << val * (it--)->second << std::endl;
    }
}

bool    parseYear(int year, int month, int day)
{
    if (year < 2009 || year > 2022)
        return false;
    if (year == 2009 && month == 1 && day == 1)
        return false;
    if (year != 2012 && year != 2016 && year != 2020 && month == 2 && day == 29)
        return false;
    
    return true;
}
bool    parseMonth(int month, int day)
{
    if (month < 1 || month > 12)
        return false;
    
    if (month == 2 && (day == 30 || day == 31))
        return false;
    
    int monthes[] = {1, 3, 5, 7, 8, 10, 12};
    int *p = std::find(monthes, monthes + 7, month);
    if (p == monthes + 7 && day == 31)
        return false;
    
    return true;
}
bool    parseDay(int day)
{
    if (day < 1 || day > 31)
        return false;

    return true;
}

std::string    parseDate(std::string &date)
{
    if (date == "" || isEmpty(date))
        throw MissingDateOrValueException();
    if (date.size() != 11)
    {
        throw InvalidDateException();
    }
    
    if (!std::isdigit(date[0])
        || !std::isdigit(date[1])
        || !std::isdigit(date[2])
        || !std::isdigit(date[3])
        || date[4] != '-'
        || !std::isdigit(date[5])
        || !std::isdigit(date[6])
        || date[7] != '-'
        || !std::isdigit(date[8])
        || !std::isdigit(date[9])
        || date[10] != ' ')
    {
        throw InvalidDateException();
    }
           
    int year = strtol(date.substr(0, 4).c_str(), NULL, 10);
    int month = strtol(date.substr(5, 2).c_str(), NULL, 10);
    int day = strtol(date.substr(8, 2).c_str(), NULL, 10);
    if (!parseDay(day) || !parseMonth(month, day) || !parseYear(year, month, day))
    {
        throw InvalidDateException();
    }
    return (date.substr(0, 10));
}

float    parseValue(std::string &value)
{
    if (value == "" || isEmpty(value))
        throw MissingDateOrValueException();
    if (value[0] != ' ' || value.size() < 2)
        throw InvalidValueException();
    
    int dot = 0;
    for (std::size_t i = 1; i < value.size() - 1; i++)
    {
        if (value[i] == '.')
            dot += 1;   
        else if (!std::isdigit(value[i]) || dot > 1)
            throw InvalidValueException();
    }
    char    *end;
    float n = std::strtof(value.substr(1).c_str(), &end);
    if (*end != '\0')
        throw InvalidValueException();
    if (n > static_cast<float>(INT_MAX))
        throw OverflowException();
    return n;
}

void        parseLine(std::string line, map_t &datamap)
{
    if (line == "" || isEmpty(line))
        throw WrongFileException();
    int i = 0;
    while (line[i] && line[i] != '|')
        i++;
    if (line[i] != '|')
    {
        std::cerr << "Error : bad input --> " << line << std::endl;
        return ;
    }
    
    std::string date = line.substr(0, i);
    std::string value_str = line.substr(i + 1);
    date = parseDate(date);
    float val = parseValue(value_str);
    findInDatabase(date, val, datamap);
}


void    analyseFile(std::string filename, map_t &datamap)
{
    std::ifstream    file(filename.c_str());
    if (!file)
        throw CantOpenFileException();

    std::string line;

    std::getline(file, line);
    if (line != "data | value")
        parseLine(line, datamap);
        
    while (std::getline(file, line))
    {
        try
        {
            parseLine(line, datamap);
        }
        catch(std::exception& err)
        {
            std::cerr << err.what() << std::endl;
        }
    }
}

//------------------------------------------------------------EXCEPTIONS

const char* CantOpenFileException::what() const throw()
{
    return "Error : Can't open file passed as argument";
}
const char* WrongFileException::what() const throw()
{
    return "Error : Empty line in file";
}
const char* InvalidDateException::what() const throw()
{
    return "Error : Invalid date";
}

const char* InvalidValueException::what() const throw()
{
    return "Error : Invalid value";
}

const char* OverflowException::what() const throw()
{
    return "Error : value is too big";
}

const char* MissingDateOrValueException::what() const throw()
{
    return "Error : Missing Element";
}