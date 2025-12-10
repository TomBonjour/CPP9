/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobourge <tobourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 14:31:04 by tobourge          #+#    #+#             */
/*   Updated: 2025/12/10 12:06:04 by tobourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

void    printTab(std::vector<int> tab)
{
    for (std::vector<int>::iterator it = tab.begin(); it != tab.end(); it++)
    {
        std::cout << *it << ' ';
    }
}

void    printDeque(std::deque<int> tab)
{
    for (std::deque<int>::iterator it = tab.begin(); it != tab.end(); it++)
    {
        std::cout << *it << ' ';
    }
}

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

std::vector<int>    parseVectorArgs(char **argv)
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

std::deque<int>    parseDequeArgs(char **argv)
{
    int i = 1;
    std::deque<int>    deq;

    while (argv[i])
    {
        if ((!isPositiveNumber(argv[i])))
            throw NotNumberException();
        deq.push_back(checkOverflow(argv[i]));
        i++;
    }
    return (deq);
}

void    validSortVec(std::vector<int> tab)
{
    for (size_t i = 0; i < tab.size() - 1; i++)
    {
        if (tab[i] > tab [i + 1])
        {
            std::cout << "Vector \e[31m[KO]\e[0m" << std::endl;
            return ;
        }
    }
    std::cout << "Vector \e[32m[OK]\e[0m" << std::endl;
    
}

void    validSortDeq(std::deque<int> tab)
{
    for (size_t i = 0; i < tab.size() - 1; i++)
    {
        if (tab[i] > tab [i + 1])
        {
            std::cout << "Deque \e[31m[KO]\e[0m" << std::endl;
            return ;
        }
    }
    std::cout << "Deque \e[32m[OK]\e[0m" << std::endl;
    
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cout << "Error : PmergeMe needs at least 1 argument" << std::endl;
        return 1;
    }
    
    std::vector<int>    tab;
    std::deque<int>    deq;

    try 
    {
        tab = parseVectorArgs(argv);
        deq = parseDequeArgs(argv);
    }
    catch(std::exception & err)
    {
        std::cout << err.what() << std::endl;
    }
    std::cout << "Vector Before: ";
    printTab(tab);
    std::cout << std::endl;
    std::cout << "Deque Before: ";
    printDeque(deq);
    std::cout << std::endl;
    FordJohnsonVector(tab, 1);
    FordJohnsonDeque(deq, 1);
    std::cout << "Vector After: ";
    printTab(tab);
    std::cout << std::endl;
    std::cout << "Deque After: ";
    printDeque(deq);
    std::cout << std::endl;
    validSortVec(tab);
    validSortDeq(deq);
}