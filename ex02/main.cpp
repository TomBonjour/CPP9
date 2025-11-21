/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobourge <tobourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 14:31:04 by tobourge          #+#    #+#             */
/*   Updated: 2025/11/21 19:01:59 by tobourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

bool    isPositiveNumber(char * arg)
{
    int i = 0;
    
    while(arg[i])
    {
        if (!std::isdigit(arg[i]))
            return false;
        i++;
    }
    return true;
}

int    checkOverflow(char *arg)
{
    char    *end;
    float   n = std::strtof(arg, &end);
    
    if (n > static_cast<float>(INT_MAX))
        throw BigNumberException();
    else
        return n;
}

std::vector<int>    parseArgs(char **argv)
{
    int i = 1;
    std::vector<int>    tab;

    while (argv[i])
    {
        if ((!isPositiveNumber(argv[i])))
            throw NotNumberException();
        tab.push_back(checkOverflow(argv[i]));
        i++;
    }
    return (tab);
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cout << "Error : PmergeMe needs at least 1 argument" << std::endl;
        return 1;
    }
    
    std::vector<int>    tab;

    try 
    {
        tab = parseArgs(argv);
    }
    catch(std::exception & err)
    {
        std::cout << err.what() << std::endl;
    }
    
    FordJohnsonAlgo(tab);
}