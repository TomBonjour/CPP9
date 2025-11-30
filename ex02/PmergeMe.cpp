/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobourge <tobourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 14:31:11 by tobourge          #+#    #+#             */
/*   Updated: 2025/11/30 13:58:15 by tobourge         ###   ########.fr       */
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


/*TODO : j'aai reussi la premier recursive ! lors de la construction des tableaux main et side
au debut de la deuxieme récursive, j'ai les bons chiffres mais ils ne sont pas dans l'ordre,
comme si le précédent tri n'avait pas été pris en compte.
 */

std::vector<int>    createSideChain(std::vector<int> & tab, int n)
{
    std::vector<int>    toInsert;
    
    for (std::vector<int>::iterator it1 = tab.begin(); it1 < tab.end(); it1 += n)
    {
        for (int i = 0; i < n; i++)
        {
            toInsert.push_back(*it1);
            
            it1 = tab.erase(it1);
        }
    }
    return toInsert;
}
 
void    insertTab(std::vector<int> & tab, int n)
{
    if (n != 1)
    n /= 2;
    
    std::cout << "DEBUT REC n = " << n << std::endl;
    std::cout << "[Main] : ";
    printTab(tab);
    std::cout << std::endl << std::endl;
    
    std::vector<int>    toInsert = createSideChain(tab, n);
    int                 nb_side = toInsert.size() / n;
    int                 nb_elem;
    
    int                 _jacob = 0;
    int                 jacob = 1;
    int                 pos = 2;
    int                 to_last_elem = 0;
    
        

    std::cout << "[ToInsert] :";
    printTab(toInsert);
    std::cout << std::endl;
    std::cout << "[Main] : ";
    printTab(tab);
    std::cout << std::endl << std::endl;
    
    for (unsigned long i = 0; i < toInsert.size() / n; i++)
    {
        std::cout << "Round " << i + 1 << "| Jacob " << jacob << "| Side Elem " << nb_side << std::endl << std::endl;
        
        if (nb_side <= jacob)
        {
            to_last_elem = jacob - nb_side;
        }
        if (jacob == 1)
        {
            for (int i = 0; i < n; i++)
            {
                tab.insert(tab.begin(), *(toInsert.begin() + (n - 1) - i));
            }

            std::cout << "REC n = " << n << " | INSERT ELEM 1" << std::endl;
            std::cout << "[Main] : ";
            printTab(tab);
            std::cout << std::endl << std::endl;
            std::cout << "[ToInsert] :";
            printTab(toInsert);
            std::cout << std::endl << std::endl;
        }
        else
        {
            for (std::vector<int>::iterator it_side = toInsert.begin() + (jacob - to_last_elem) * n - 1
                ; it_side >= toInsert.begin() + (jacob * n - 1) - ((jacob - _jacob) * n - 1); )
            {
                
                nb_elem = _jacob + jacob - 1;
                
                std::cout << "INSERT " << *it_side << "| nb_elem to cmp : " << nb_elem << std::endl;
                
                std::vector<int>::iterator  it_tab;
                int pos_to_cmp = (nb_elem + 1) / 2;
                while (true)
                {
                    it_tab = tab.begin() + (pos_to_cmp * n) - 1;
                    
                    std::cout << "Compare with" << *it_tab << "| nb_elem to cmp : " << nb_elem << std::endl;
                    
                    if (*it_side > *it_tab)
                    {
                        if (nb_elem == 1)
                        {
                            it_tab++;
                            for (int i = 0; i < n; i++)
                            {
                                tab.insert(it_tab, *it_side--);
                            }
                            break;
                        }
                        nb_elem /= 2;
                        pos_to_cmp += nb_elem;
                    }
                    else if (*it_side <= *it_tab)
                    {
                        if (nb_elem == 1)
                        {
                            it_tab -= n - 1;
                            for (int i = 0; i < n; i++)
                            {
                                tab.insert(it_tab, *it_side--);
                            }
                            break;
                        }
                        nb_elem /= 2;
                        pos_to_cmp -= nb_elem;
                    }
                }
                std::cout << "[Main] : ";
                printTab(tab);
                std::cout << std::endl;
                std::cout << "[ToInsert] : ";
                printTab(toInsert);
                std::cout << std::endl << std::endl;
            }
        }

        if (nb_side <= jacob)
            break;
        
        _jacob = jacob;
        jacob = std::pow(2, pos) - jacob;
        pos++;
    }
    if (n == 1)
        return;
}

// 10 8 7 9 6 3 4 5 2 1 11
    
void   FordJohnsonAlgo(std::vector<int> & tab, unsigned long n)
{
    if (tab.size() <= 1 || n > (tab.size() / 2))
        return ;
    mergeTab(tab, n);
    FordJohnsonAlgo(tab, n * 2);
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