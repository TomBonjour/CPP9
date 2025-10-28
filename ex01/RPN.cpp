/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobourge <tobourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 09:21:01 by tobourge          #+#    #+#             */
/*   Updated: 2025/10/28 13:15:21 by tobourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

const char* WrongInputException::what() const throw()
{
    return ("Error : Please enter a valid RPN expression with 0-9 digits.");
}

const char* DivisionByZeroException::what() const throw()
{
    return ("Error : This calculation causes a division by zero.");
}