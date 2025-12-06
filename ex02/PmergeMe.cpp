/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobourge <tobourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 14:31:11 by tobourge          #+#    #+#             */
/*   Updated: 2025/12/06 14:29:40 by tobourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <algorithm>
#include <cmath>


void    printTab(std::vector<int> tab)
{
    for (std::vector<int>::iterator it = tab.begin(); it != tab.end(); it++)
    {
        std::cout << *it << ' ';
    }
}

void    mergeTab(std::vector<int> & tab, int n)
{
    for (std::vector<int>::iterator it1 = tab.begin() + (n - 1); it1 < tab.end(); it1 += n)
    {
        std::vector<int>::iterator it2 = it1 + n;
        if (it2 >= tab.end())
            break ;
        if (*it1 > *it2)
        {
            for (int i = 0; i < n; i++)
            {
                std::swap(*(it1 - i), *(it2 - i));
            }
        }
        it1 += n;
    }
}




std::vector<int>    createSideChain(std::vector<int> & tab, int n, int nb_insert)
{
    std::vector<int>    toInsert;
    std::vector<int>::iterator it = tab.begin();
    
    
    for (int i = 0; i < nb_insert; i++)
    {
        for (int i = 0; i < n; i++)
        {
                toInsert.push_back(*it);
                it = tab.erase(it);
        }
        it += n;
    }
    return toInsert;
}
 
void    insertTab(std::vector<int> & tab, int n)
{
    std::vector<int>    toInsert;
    int                 nb_insert;
    
    if (n == 1)
        nb_insert = (tab.size() + 1) / 2;
    else
        nb_insert = ((tab.size() / n) + 1) / 2;
    
    toInsert = createSideChain(tab, n, nb_insert);
    
    int                 nb_elem;
    int                 _jacob = 0;
    int                 jacob = 1;
    int                 pos = 2;
    int                 to_last_elem = 0;
    
    for (unsigned long i = 0; i < toInsert.size() / n; i++)
    {
        if (jacob == 1)
        {
            for (int i = 0; i < n; i++)
            {
                tab.insert(tab.begin(), *(toInsert.begin() + (n - 1) - i));
            }
        }
        else
        {
            if (nb_insert < jacob)
                to_last_elem = jacob - nb_insert;
            for (std::vector<int>::iterator it_side = toInsert.begin() + (jacob - to_last_elem) * n - 1
            ; it_side >= toInsert.begin() + (jacob * n - 1) - ((jacob - _jacob) * n - 1); )
            {
                if (nb_insert < jacob)
                    nb_elem = (tab.size()) / n;
                else
                    nb_elem = _jacob + jacob - 1;
                
                int pos_to_cmp = ((nb_elem + 1) / 2) * n;
                std::vector<int>::iterator  it_tab;
                
                while (true)
                {
                    it_tab = tab.begin() + pos_to_cmp - 1;
                    
                    if (*it_side > *it_tab)
                    {
                        
                        if (nb_elem == 1 || (nb_elem == 2 && it_tab + 1 == tab.end()))
                        {
                            it_tab++;
                            for (int i = 0; i < n; i++)
                            {
                                tab.insert(it_tab, *it_side);
                                it_side--;
                            }
                            break;
                        }
                        nb_elem /= 2;
                        if (nb_elem == 1)
                            pos_to_cmp += n;
                        else
                            pos_to_cmp += ((nb_elem + 1) / 2) * n;
                    }
                    else if (*it_side <= *it_tab)
                    {
                        if (nb_elem == 1 || (nb_elem == 2 && pos_to_cmp == 1))
                        {
                            if (it_tab != tab.begin())
                                it_tab -= n - 1;
                            for (int i = 0; i < n; i++)
                            {
                                tab.insert(it_tab, *it_side);
                                it_side--;
                            }
                            break;
                        }
                        nb_elem /= 2;
                        if (nb_elem == 1)
                            pos_to_cmp -= n;
                        else
                            pos_to_cmp -= ((nb_elem + 1) / 2) * n;
                    }
                }
                
            }
        }
        
        if (nb_insert <= jacob)
            break;
        
        _jacob = jacob;
        jacob = std::pow(2, pos) - jacob;
        pos++;
    }
}

// 10 8 7 9 6 3 4 5 2 1 11
    
void   FordJohnsonAlgo(std::vector<int> & tab, unsigned long n)
{
    if (tab.size() <= 1 || n > (tab.size() / 2))
        return ;
    mergeTab(tab, n);
    FordJohnsonAlgo(tab, n * 2);
    std::cout << "n : " << n << std::endl;
    insertTab(tab, n);
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

// std::cout << "[Main] : ";
// printTab(tab);
// std::cout << std::endl;
// std::cout << "[ToInsert] : ";
// printTab(toInsert);
// std::cout << std::endl << std::endl;