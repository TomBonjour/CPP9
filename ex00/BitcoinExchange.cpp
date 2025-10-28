/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobourge <tobourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 13:16:04 by tobourge          #+#    #+#             */
/*   Updated: 2025/10/28 16:28:48 by tobourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <map>

bool    isFile(std::string filename)
{
    if (filename.size() < 3)
        return false;
    if (*filename.begin() == '.' || *filename.end() - 1 == '.')
        return false;
    
    int i = 0;
    int dots = 0;
    while (filename[i])
    {
        if (std::isblank(filename[i]))
            return false;
        if (filename[i] == '.')
            dots = 1;
        i++;
    }
    if (dots == 0)
        return false;
    return true;
}

bool    parseDate(std::string date)
{

}

bool    parseValue(std::string date)
{

}

void    parseLine(std::string &line, std::map<std::string,int> &map)
{
    int i = 0;

    while (line[i] && line[i] != '|')
        i++;
    if (i != 11 || line[i] != '|')
        throw WrongFileException();
    else
    {
        std::string date = line.substr(0, 10);
        std::string value = line.substr(12, std::string::npos);
        if (parseDate(date) && parseValue(value))
            map[date]; // = atoi de value;
    }
}

void    analyseFile(std::string filename)
{
    std::ifstream    file(filename.c_str());
    if (!file)
        throw CantOpenFileException();

    std::string line;

    getline(file, line);
    if (line != "date | value")
        throw WrongFileException();
    
    std::map<std::string, int>   map;
    while (getline(file, line))
    {
        if (line == "")
            throw WrongFileException();
        parseLine(line, map);
    }
    //convert btc exchange
}

//------------------------------------------------------------EXCEPTIONS

const char* CantOpenFileException::what() const throw()
{
    return "Error : Can't open file passed as argument";
}
const char* WrongFileException::what() const throw()
{
    return "Error : Wrong File passed as argument";
}
