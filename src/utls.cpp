#include "../include/utls.hpp"
#include "../include/server.hpp"

std::string Utils::strTrim(const std::string &str) 
{
    size_t start = 0;
    size_t end = str.size();
    
    if (str[start] != ' ' || str[start] != '\t')
        return ""; 
    // Trim start
    while (start < end && (str[start] == ' ' || str[start] == '\t'))
        start++;
    // Trim end
    while (end > start && (str[end - 1] == ' ' || str[end - 1] == '\t'))
        end--;
    return (str.substr(start, end - start));
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
        throw std::runtime_error("No clients connected");
    std::cout << std::left;
    std::cout << "----------------------------------------------------------"
              << std::endl;
    std::cout << "| " << std::setw(4)  << "FD"
              << "| " << std::setw(5)  << "Pass"
              << "| " << std::setw(5)  << "User"
              << "| " << std::setw(5)  << "Nick"
              << "| " << std::setw(4)  << "Reg"
              << "| " << std::setw(10) << "Nickname"
              << "| " << std::setw(10) << "Username"
              << "|" << std::endl;

    std::cout << "----------------------------------------------------------"
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
                  << "|" << std::endl;
    }
}