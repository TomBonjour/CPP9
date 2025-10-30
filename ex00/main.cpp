/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobourge <tobourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 13:24:38 by tobourge          #+#    #+#             */
/*   Updated: 2025/10/30 11:19:23 by tobourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

/*

On donne en argument un fichier (toute extension) qui contient "date | value"
On crée une map qui contient date | value
Le programme doit aller chercher le taux de la date demandée (jour le plus proche)
dans la database et convertir la valeur

*/





int   createDatabase(map_t &datamap)
{
    std::ifstream   data("data.csv");    

    if(!data.is_open())
    {
        std::cerr << "Error : database opening failed." << std::endl;
        return (-1);
    }
    
    std::string line;
    while (std::getline(data, line))
    {
        std::size_t     i = line.find(',');
        std::string     date = line.substr(0, i);
        std::string     value = line.substr(i + 1);
        datamap[date] = std::strtol(value.c_str(), NULL, 10);
    }
    return 0;
}

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
        if (isblank(filename[i]))
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
    (void)argv;
    if (argc != 2)
    {
        std::cout << "Error : This program takes one file as argument.";
        return 1;
    }
    map_t   datamap;   
    if (createDatabase(datamap) == -1)
        return 1;
    if (isFile(argv[1]))
    {
        try
        {
            analyseFile(argv[1], datamap);
        }
        catch(std::exception &err)
        {
            std::cerr << err.what() << std::endl;
            return 1;
        }
    }
    return 0;
}