/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobourge <tobourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 09:21:05 by tobourge          #+#    #+#             */
/*   Updated: 2025/10/28 13:11:26 by tobourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.cpp"
#include "RPN.hpp"
#include <iostream>
#include <sstream>
#include <stack>
#include <cctype>
#include <cstdlib>
#include <string>
#include <cstring>
#include <vector>

bool isOperator(char c)
{
    if (c == '+' || c == '-' || c == '*' || c == '/')
        return true;
    return false;
}
void    doOperation(std::stack<int> &args, char op)
{
    int arg2 = args.top();
    args.pop();

    int arg1 = args.top();
    args.pop();

    int result;
    if (op == '+')
        result = arg1 + arg2;
    else if (op == '-')
        result = arg1 - arg2;
    else if (op == '*')
        result = arg1 * arg2;
    else if (op == '/')
    {
        if (arg2 == 0)
            throw DivisionByZeroException();
        result = arg1 / arg2;
    }
    args.push(result);
}

void    doCalc(std::string input)
{
    std::stack<int> args;

    args.push(input[0] - '0');
    args.push(input[2] - '0');

    int i = 4;
    while (input[i] != '\0')
    {
        if (std::isdigit(input[i]))
            args.push(input[i] - 48);
        else if (isOperator(input[i]))
            doOperation(args, input[i]);
        i++;
    }
    std::cout << args.top() << std::endl;
}


void    ftParseArgs(std::string arg)
{
    int numbers = 2;
    int operators = 0;
    
    
    if (arg.size() < 5)
        throw WrongInputException();
    int i = 0;
    for (; i < 4; i++)
    {
        if (i % 2 == 0 && !std::isdigit(arg[i]))
            throw WrongInputException();
        if (i % 2 == 1 && arg[i] != ' ')
            throw WrongInputException();
    }
    
    while (arg[i] != '\0')
    {
        if (i % 2 == 1 && (arg[i] != ' ' || (arg[i] == ' ' && arg[i + 1] == '\0')))
            throw WrongInputException();
        if (i % 2 == 0 && !std::isdigit(arg[i]) && !isOperator(arg[i]))
            throw WrongInputException();
        
        if (std::isdigit(arg[i]))
            numbers += 1;
        if (isOperator(arg[i]))
        {
            operators += 1;
            if (operators >= numbers)
                throw WrongInputException();
        }
        i++;
    }
    if (operators != numbers - 1)
        throw WrongInputException();
}

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        std::cerr << "Error : Missing argument." << std::endl;
        return 1;
    }
    try
    {
        ftParseArgs(argv[1]);
        doCalc(argv[1]);
    }
    catch (std::exception &err)
    {
        std::cerr << err.what() << std::endl;
        return 1;
    }
    return 0;
}