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

std::string center(const std::string &s, int W)
{
    int pad = W - (int)s.size();
    int left = pad / 2;
    int right = pad - left;
    return std::string(left, ' ') + s + std::string(right, ' ');
}

void Utils::sendHelp(client &c)
{
    const int W = 62;
    std::string eq(W, '_');
    std::string dash(W, '_');
    std::stringstream os;
    os << std::left;

    os << "+" << eq   << "+\r\n";
    os << "|" << center("Welcome to Our IRC Server!", W)                        << "|\r\n";
    os << "+" << dash  << "+\r\n";
    os << "|" << center("You connected successfully!", W)                       << "|\r\n";
    os << "|" << center("Complete your registration using the commands below.", W) << "|\r\n";
    os << "+" << eq   << "+\r\n";
    os << "|" << center("AVAILABLE COMMANDS", W)                                << "|\r\n";
    os << "+" << dash  << "+\r\n";
    os << "|  " << std::setw(14) << "nickname"    << ": " << std::setw(W - 18) << "/nick <nickname>"                     << "|\r\n";
    os << "|  " << std::setw(14) << "username"    << ": " << std::setw(W - 18) << "/user <username> <*> <0> :<realname>" << "|\r\n";
    os << "+" << eq   << "+\r\n";
    std::string str = os.str();
    send(c.fd,str.c_str(),str.size(),0);
}

void Utils::sendAuthWelcome(client &c)
{
    std::string msg = "Authentication successful. Type /help for more information.\r\n";
    send(c.fd,msg.c_str(),msg.size(),0);
}

void Utils::send_welcome(client &c)
{
    std::string msg; 
    msg = std::string(":ircserv 001 ") + c.nickname +
      " :Welcome to the IRC Network, " +
      c.username + "!\r\n" + '\n'; 
    send(c.fd,msg.c_str(),strlen(msg.c_str()),1);
}

void Utils::sendWelcome(int fd)
{
    std::stringstream os;
    os << std::left;

    os << "+--------------------------------------------------------------+\r\n";
    os << "| " << std::setw(61) << "             Connected to IRC Server!" << "|\r\n";
    os << "+--------------------------------------------------------------+\r\n";
    os << "| " << std::setw(61) << ""                                        << "|\r\n";
    os << "| " << std::setw(61) << "   To connect to the server, use:"       << "|\r\n";
    os << "| " << std::setw(61) << ""                                        << "|\r\n";
    os << "| " << std::setw(61) << "   CONNECT COMMAND:"                     << "|\r\n";
    os << "| " << std::setw(61) << "      /connect <ip> <port> <password>"   << "|\r\n";
    os << "| " << std::setw(61) << ""                                        << "|\r\n";
    os << "| " << std::setw(61) << "   EXAMPLE:"                             << "|\r\n";
    os << "| " << std::setw(61) << "      /connect 127.0.0.1 4444 mypassword" << "|\r\n";
    os << "+--------------------------------------------------------------+\r\n";

    std::string str = os.str();
    send(fd, str.c_str(), str.size(), 0);
}