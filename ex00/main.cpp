/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobourge <tobourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 13:24:38 by tobourge          #+#    #+#             */
/*   Updated: 2025/10/28 16:28:51 by tobourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

/*

On donne en argument un fichier (toute extension) qui contient "date | value"
On crée une map qui contient date | value
Le programme doit aller chercher le taux de la date demandée (jour le plus proche)
dans la database et convertir la valeur

Q : Dois-t-on parser les '/' dans le nom de fichier ?
Q : Est-ce une bonne pratique de faire un try general dans le main ?
Q : Comment faire quand dans la meme fonction on a un throw et un return a faire ?

*/

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << "Error : This program takes one file as argument.";
        return 1;
    }
    if (isFile(argv[1]))
    {
        try
        {
            analyseFile(argv[1]);
        }
        catch(std::exception &err)
        {
            std::cerr << err.what() << std::endl;
        }
        
    }
}