/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobourge <tobourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 09:21:05 by tobourge          #+#    #+#             */
/*   Updated: 2025/10/27 16:08:51 by tobourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.cpp"
#include "RPN.hpp"
#include <iostream>
#include <stack>
#include <cctype>
#include <cstdlib>
#include <string>
#include <cstring>

bool isOperator(char c)
{
    if (c == '+' || c == '-' || c == '*' || c == '/')
        return true;
    return false;
}
void    doOperation(std::stack<int> &args, std::string op)
{
    int arg2 = args.top();
    args.pop();

    int arg1 = args.top();
    args.pop();


    int result;
    if (op[0] == '+')
        result = arg1 + arg2;
    else if (op[0] == '-')
        result = arg1 - arg2;
    else if (op[0] == '*')
        result = arg1 * arg2;
    else if (op[0] == '/')
    {
        if (arg2 == 0)
            throw DivisionByZeroException();
        result = arg1 / arg2;
    }
    args.push(result);
}

void    doCalc(char **argv)
{
    std::stack<int> args;

    args.push(atoi(argv[1]));
    args.push(atoi(argv[2]));

    int i = 3;
    while (argv[i] != NULL)
    {
        if (std::isdigit(argv[i][0]))
            args.push(atoi(argv[i]));
        else if (isOperator(argv[i][0]))
            doOperation(args, argv[i]);
        i++;
        std::cout << "Top : " << args.top() << std::endl;
        std::cout << "Size : " << args.size() << std::endl;

    }
    std::cout << args.top() << std::endl;
}


void    ftParseArgs(char **argv)
{
    int numbers = 2;
    int operators = 0;
    
    for (int i = 1; i < 3; i++)
    {
        if (std::strlen(argv[i]) != 1 || !std::isdigit(argv[i][0]))
            throw WrongInputException();
    }
    int i = 3;
    while (argv[i] != NULL)
    {
        if (std::strlen(argv[i]) != 1 || (!std::isdigit(argv[i][0]) && !isOperator(argv[i][0])))    
            throw WrongInputException();
        else if (std::isdigit(argv[i][0]))
            numbers += 1;
        else if (isOperator(argv[i][0]))
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

    if (argc < 3)
    {
        std::cerr << "Error : Please enter a valid RPN mathematical expression." << std::endl;
        return (1);
    }
    try
    {
        ftParseArgs(argv);
        doCalc(argv);
    }
    catch (std::exception &err)
    {
        std::cerr << err.what() << std::endl;
    }
}