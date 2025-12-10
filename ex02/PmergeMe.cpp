/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobourge <tobourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 14:31:11 by tobourge          #+#    #+#             */
/*   Updated: 2025/12/10 12:05:59 by tobourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <algorithm>
#include <cmath>


//CONTAINER 1 : VECTOR

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
                    int tab_idx = pos_to_cmp - 1;
                    // it_tab = tab.begin() + pos_to_cmp - 1;
                    
                    if (*it_side > tab[tab_idx])
                    {
                        
                        if (nb_elem == 1 || (nb_elem == 2 && tab_idx + 1 > tab.size()))
                        {
                            tab_idx++;
                            for (int i = 0; i < n; i++)
                            {
                                tab.insert(tab.begin() + tab_idx, *it_side);
                                it_side--;
                            }
                            break;
                        }
                        nb_elem /= 2;
                        pos_to_cmp += ((nb_elem + 1) / 2) * n;
                    }
                    else if (*it_side <= tab[tab_idx])
                    {
                        if (nb_elem == 1 || (nb_elem == 2 && pos_to_cmp == 1))
                        {
                            if (tab_idx != 0)
                                tab_idx -= n - 1;
                            for (int i = 0; i < n; i++)
                            {
                                tab.insert(tab.begin() + tab_idx, *it_side);
                                it_side--;
                            }
                            break;
                        }
                        nb_elem /= 2;
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
    
void   FordJohnsonVector(std::vector<int> & tab, unsigned long n)
{
    if (tab.size() <= 1 || n > (tab.size() / 2))
        return ;
    mergeTab(tab, n);
    FordJohnsonVector(tab, n * 2);
    insertTab(tab, n);
}

//CONTAINER 2 : DEQUE

void    mergeDeque(std::deque<int> & tab, int n)
{
    for (std::deque<int>::iterator it1 = tab.begin() + (n - 1); it1 < tab.end(); it1 += n)
    {
        std::deque<int>::iterator it2 = it1 + n;
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

std::deque<int>    createSideChain(std::deque<int> & tab, int n, int nb_insert)
{
    std::deque<int>    toInsert;
    std::deque<int>::iterator it = tab.begin();
    
    
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
 
void    insertDeque(std::deque<int> & tab, int n)
{
    std::deque<int>     toInsert;
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
            for (std::deque<int>::iterator it_side = toInsert.begin() + (jacob - to_last_elem) * n - 1
            ; it_side >= toInsert.begin() + (jacob * n - 1) - ((jacob - _jacob) * n - 1); )
            {
                if (nb_insert < jacob)
                    nb_elem = (tab.size()) / n;
                else
                    nb_elem = _jacob + jacob - 1;
                
                int pos_to_cmp = ((nb_elem + 1) / 2) * n;
                std::deque<int>::iterator  it_tab;
                
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

void   FordJohnsonDeque(std::deque<int> & tab, unsigned long n)
{
    if (tab.size() <= 1 || n > (tab.size() / 2))
        return ;
    mergeDeque(tab, n);
    FordJohnsonDeque(tab, n * 2);
    insertDeque(tab, n);
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