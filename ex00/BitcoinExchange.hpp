/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobourge <tobourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 13:16:01 by tobourge          #+#    #+#             */
/*   Updated: 2025/10/29 19:25:25 by tobourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <cstring>
#include <ctype.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <exception>
#include <map>
#include <climits>
#include <algorithm>
#include <ctime>

typedef std::map<std::string, int> map_t;


bool        isFile(std::string filename);
void        analyseFile(std::string filename, map_t &datamap);

class CantOpenFileException : public std::exception
{
    public : virtual const char* what() const throw();
};

class WrongFileException : public std::exception
{
    public : virtual const char* what() const throw();
};

class InvalidDateException : public std::exception
{
    public : virtual const char* what() const throw();
};

class InvalidValueException : public std::exception
{
    public : virtual const char* what() const throw();
};

class OverflowException : public std::exception
{
    public : virtual const char* what() const throw();
};

class MissingDateOrValueException : public std::exception
{
    public : virtual const char* what() const throw();
};