/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobourge <tobourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 13:24:38 by tobourge          #+#    #+#             */
/*   Updated: 2025/10/29 12:36:27 by tobourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

/*

On donne en argument un fichier (toute extension) qui contient "date | value"
On crée une map qui contient date | value
Le programme doit aller chercher le taux de la date demandée (jour le plus proche)
dans la database et convertir la valeur

Q : comment garder l'ordre des input alors que map classe automatiquement dans l'ordre croissant ?
Q : Dois-t-on parser les '/' dans le nom de fichier ?
Q : Est-ce une bonne pratique de faire un try general dans le main ?
Q : Comment faire quand dans la meme fonction on a un throw et un return a faire ?

MEMO map :
- [W + ...] --> Error : Bad input [...]
- [""] = xxx --> Error : Empty date
- [date] = NULL --> Error : Empty value

*/

bool    isFile(std::string filename)
{
    if (filename.size() < 3)
        return false;
    if (*filename.begin() == '.' || *filename.end() - 1 == '.')
        return false;
    
    int i = 0;
    int dots = 0;
    while (filename[i])
    {
        if (std::isblank(filename[i]))
            return false;
        if (filename[i] == '.')
            dots = 1;
        i++;
    }
    if (dots == 0)
        return false;
    return true;
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << "Error : This program takes one file as argument.";
        return 1;
    }
    if (isFile(argv[1]))
    {
        std::map<std::string,int>   map;
        try
        {
            map = analyseFile(argv[1]);
            //convertBtc
        }
        catch(std::exception &err)
        {
            std::cerr << err.what() << std::endl;
            return 1;
        }
        
    }
}