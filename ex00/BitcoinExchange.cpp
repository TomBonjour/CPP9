/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobourge <tobourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 13:16:04 by tobourge          #+#    #+#             */
/*   Updated: 2025/10/29 12:36:26 by tobourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <map>

typedef std::map<std::string, int> map_t;


bool    isEmpty(std::string line)
{
    int i = 0;
    while (line[i])
    {
        if (!std::isblank(line[i]))
            return false;
        i++;
    }
    return true;
}

// bool    parseDate(std::string &date)
// {
//     int i = 0;
    
//     for(; i < 4; i++)
//     {
//         if (!std::isdigit(date[i]))
//             throw InvalidDateException();
//     }
//     if (date[i] != '-')
//         throw InvalidDateException();
//     int year = stoi(date.substr(0, 4));
// }

// bool    parseValue(std::string &date)
// {

// }

map_t   &createMapElement(map_t map, std::string date, std::string value)
{
    if (date == "")
        map[""] = NULL;
    else if (value == "" || isEmpty(value))
        map[date] = NULL;
    else if (value[0] != ' ' || value.size() < 2)
        map["W" + value] = NULL;
    // for (int i = 1; i < value.size() - 1; i++)
    // {
    //     if (!std::isdigit(value[i]))
    //         map["W" + value] = NULL;
    // }
    try 
    {
        int n = stoi(value.substr(1));
        map[date] = n;
    }
    catch (std:: exception &err) 
    {
        map["W" + value] = NULL;
    }
}


map_t    &analyseFile(std::string filename)
{
    std::ifstream    file(filename.c_str());
    if (!file)
        throw CantOpenFileException();

    std::string line;
    map_t       map;

    while (getline(file, line))
    {
        if (line == "" || isEmpty(line))
            throw WrongFileException();
        int i = 0;
        while (line[i] && line[i] != '|')
            i++;
        if (line[i] != '|')
            map["W" + line] = NULL;
        else
        {
            std::string date = line.substr(0, i);
            std::string value = line.substr(i + 1);
            createMapElement(map, date, value);
        }
    }
    return map;
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
    return "Error : Invalid Date found ni file";
}