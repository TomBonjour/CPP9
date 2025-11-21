/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobourge <tobourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 14:31:11 by tobourge          #+#    #+#             */
/*   Updated: 2025/11/21 19:14:22 by tobourge         ###   ########.fr       */
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

std::vector<int>    buildMainTab(std::vector<int> tab)
{
    if (tab.size() <= 1)
        return tab;

    std::vector<int>    big;
    int                 a;
    int                 b;

    for (std::vector<int>::iterator it = tab.begin(); it != tab.end(); it++)
    {
        a = *it;
        it++;
        if (it != tab.end())
        {    
            b = *it;
            big.push_back(a > b ? a : b);
        }
        else
            break;
    }

    std::vector<int>    main_tab = buildMainTab(big);

    return main_tab;
}

void    FordJohnsonAlgo(std::vector<int> tab)
{
    std::vector<int> main_tab = buildMainTab(tab);

    printTab(tab);
    std::cout << std::endl;
    printTab(main_tab);
}



const char* NotNumberException::what() const throw()
{
    return "Error : a least one argument is not a positive number";
}

const char* BigNumberException::what() const throw()
{
    return "Error : at least one number is higher than INT_MAX";
}

const char* NegativeNumberException::what() const throw()
{
    return "Error : at least one number is higher than INT_MAX";
}