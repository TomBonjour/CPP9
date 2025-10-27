/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobourge <tobourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 09:24:53 by tobourge          #+#    #+#             */
/*   Updated: 2025/10/27 13:26:34 by tobourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <exception>

void    solveCalc(char** argv);

class WrongInputException : public std::exception
{
    public : virtual const char* what() const throw()
    {
        return ("Error : Please enter a valid RPN mathematical expression.");
    }
};
