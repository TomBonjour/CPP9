/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobourge <tobourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 14:31:04 by tobourge          #+#    #+#             */
/*   Updated: 2025/12/06 14:30:19 by tobourge         ###   ########.fr       */
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

void    validSort(std::vector<int> tab)
{
    for (size_t i = 0; i < tab.size() - 1; i++)
    {
        if (tab[i] > tab [i + 1])
        {
            std::cout << "\e[31m[KO]\e[0m" << std::endl;
            return ;
        }
    }
    std::cout << "\e[32m[OK]\e[0m" << std::endl;
    
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
    
    FordJohnsonAlgo(tab, 1);
    printTab(tab);
    validSort(tab);
}