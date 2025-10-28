/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobourge <tobourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 13:16:01 by tobourge          #+#    #+#             */
/*   Updated: 2025/10/28 16:28:50 by tobourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <ctype.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <exception>

bool    isFile(std::string filename);
void    parseLine(std::string line);
void    analyseFile(std::string filename);

class CantOpenFileException : public std::exception
{
    public : virtual const char* what() const throw();
};

class WrongFileException : public std::exception
{
    public : virtual const char* what() const throw();
};