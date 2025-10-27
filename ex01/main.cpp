/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobourge <tobourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 09:21:05 by tobourge          #+#    #+#             */
/*   Updated: 2025/10/27 13:26:32 by tobourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.cpp"
#include "RPN.hpp"
#include <iostream>
#include <stack>
#include <cctype>
#include <cstring>

void    solveCalc(char **argv)
{
    
}

bool isOperator(char c)
{
    if (c == '+' || c == '-' || c == '*' || c == '/')
        return true;
    return false;
}

void    ftParseArgs(char **argv)
{
    int i = 1;
    int numbers = 0;
    int operators = 0;
    
    for (int i = 1; i < 3; i++)
    {
        if (strlen(argv[i]) != 1 || !isdigit(argv[i][0]))
            throw WrongInputException();
    }
    while (argv[i] != NULL)
    {
        if (strlen(argv[i]) != 1 || (!isdigit(argv[i][0]) && !isOperator(argv[i][0])))    
            throw WrongInputException();
        else if (isdigit(argv[i][0]))
            numbers += 1;
        else if (isOperator(argv[i][0]))
        {
            operators += 1;
            if (operators != numbers - 1)
                throw WrongInputException();
        }
        i++;
    }
    if (operators != numbers - 1)
        throw WrongInputException();
}

int main(int argc, char** argv)
{

    if (argc < 3)
    {
        std::cerr << "Error : Please enter a valid RPN mathematical expression." << std::endl;
        return (1);
    }
    try
    {
        ftParseArgs(argv);
        solveCalc(argv);
    }
    catch (std::exception &err)
    {
        std::cerr << err.what() << std::endl;
    }
}