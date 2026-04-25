/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utls.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitaabe <haitaabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 21:41:46 by haitaabe          #+#    #+#             */
/*   Updated: 2026/04/21 18:46:09 by haitaabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/utls.hpp"
#include "../include/server.hpp"

std::string Utils::strTrim(const std::string &str) 
{
    size_t start = str.find_first_not_of(" \t\r\n");

    if (start == std::string::npos) 
        return ""; 

    size_t end = str.find_last_not_of(" \t\r\n");

    return (str.substr(start, end - start + 1));
}

int Utils::check_port(const std::string& port)
{
    if (port.empty())
        return (-1);
    for (size_t i = 0; i < port.size(); i++) 
    {
        if (!std::isdigit(port[i]))
            return (-1);
    }
    if (port.size() > 5)
        return (-2);
    int _port = std::atoi(port.c_str());
    if (_port < 1 || _port > 65535)
        return (-2);
    if (_port < 1024 || _port > 49151)
        return (-3);
    return (_port);
}

int Utils::validatePort(const std::string& port)
{
    int result = check_port(port);
    if (result == -1)
        throw std::runtime_error("Port must contain digits only.");
    if (result == -2)
        throw std::runtime_error("Port must be between 1 and 65535.");
    if (result == -3)
        throw std::runtime_error("Use a safe port range (1024 - 49151).");
    return result;
}

void Utils::printClientsInfo(const std::map<int, client> &clients)
{
    if (clients.empty())
    {
        std::cout << "No clients connected" << std::endl;
        return;
    }
    std::cout << std::left;
    std::cout << "-----------------------------------------------------------------------"
              << std::endl;
    std::cout << "| " << std::setw(4)  << "FD"
              << "| " << std::setw(5)  << "Pass"
              << "| " << std::setw(5)  << "User"
              << "| " << std::setw(5)  << "Nick"
              << "| " << std::setw(4)  << "Reg"
              << "| " << std::setw(10) << "Nickname"
              << "| " << std::setw(10) << "Username"
              << "| " << std::setw(10) << "realname"
              << "|" << std::endl;

    std::cout << "-----------------------------------------------------------------------"
              << std::endl;
    for (std::map<int, client>::const_iterator it = clients.begin(); it != clients.end(); ++it)
    {
        const client &c = it->second;

        std::cout << "| " << std::setw(4)  << it->first
                  << "| " << std::setw(5)  << c.pass_ok
                  << "| " << std::setw(5)  << c.user_ok
                  << "| " << std::setw(5)  << c.nick_ok
                  << "| " << std::setw(4)  << c.regestred
                  << "| " << std::setw(10) << c.nickname
                  << "| " << std::setw(10) << c.username
                  << "| " << std::setw(10) << c.realname
                  << "|" << std::endl;
    }
}

std::string Utils::getTime()
{
    time_t now = time(0);
    struct tm* tm_info = localtime(&now);
    char buffer[9];
    strftime(buffer, 9, "%H:%M:%S", tm_info);
    return std::string(buffer);
}

std::string Utils::getMachineName()
{
    char hostname[1024];

    if (gethostname(hostname, sizeof(hostname)) == -1)
        return "unknown";

    hostname[sizeof(hostname) - 1] = '\0'; // safety

    return std::string(hostname);
}
