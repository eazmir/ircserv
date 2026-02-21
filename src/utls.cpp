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

void Utils::printClientsInfo(const std::map<int, client> &clients) 
{
    if (clients.empty()) 
    {
        std::cout << "No clients connected" << std::endl;
        return;
    }
    for (std::map<int, client>::const_iterator it = clients.begin(); it != clients.end(); ++it) 
    {
        const client &c = it->second;
        std::cout << "FD: " << it->first << std::endl;
        std::cout << "Status: " << c.status << std::endl;
        std::cout << "Pass OK: " << c.pass_ok << std::endl;
        std::cout << "User OK: " << c.user_ok << std::endl;
        std::cout << "Nick OK: " << c.nick_ok << std::endl;
        std::cout << "Registered: " << c.regestred<< std::endl;
        std::cout << "Nickname: " << c.nickname << std::endl;
        std::cout << "Username: " << c.username << std::endl;
        std::cout << "Real Name: " << c.realname << std::endl;
        std::cout << "--------------------------" << std::endl;
    }
}