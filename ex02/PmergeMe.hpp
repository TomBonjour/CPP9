/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobourge <tobourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 14:31:51 by tobourge          #+#    #+#             */
/*   Updated: 2025/11/25 17:34:41 by tobourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <cctype>
#include <climits>
#include <cstdlib>
#include <vector>
#include <exception>

void    FordJohnsonAlgo(std::vector<int> tab, unsigned long n);


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