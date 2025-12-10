/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobourge <tobourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 14:31:51 by tobourge          #+#    #+#             */
/*   Updated: 2025/12/10 12:06:00 by tobourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <cctype>
#include <climits>
#include <cstdlib>
#include <vector>
#include <deque>
#include <exception>

void    FordJohnsonVector(std::vector<int> & tab, unsigned long n);
void    FordJohnsonDeque(std::deque<int> & tab, unsigned long n);
void    printTab(std::vector<int> tab);


 class NotNumberException : public std::exception
 {
    public :  
        virtual const char* what() const throw();
 };
 
 class BigNumberException : public std::exception
 {
    public :  
        virtual const char* what() const throw();
 };

  class NegativeNumberException : public std::exception
 {
    public : 
        virtual const char* what() const throw();
 };