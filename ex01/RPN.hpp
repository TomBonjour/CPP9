/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobourge <tobourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 09:24:53 by tobourge          #+#    #+#             */
/*   Updated: 2025/10/28 13:10:36 by tobourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <exception>

class WrongInputException : public std::exception
{
    public : virtual const char* what() const throw();
};

class DivisionByZeroException : public std::exception
{
    public : virtual const char* what() const throw();
};