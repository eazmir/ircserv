#include "../include/client.hpp"
#include "../include/utls.hpp"

managerchannel::managerchannel(std::map<int, client> &clients,const std::string &pass)
    : _clients(clients),
      auth(pass)
{
}

void managerchannel::handle_input(const std::string &input, client &c)
{
    this->auth.tryRegister(c,input);
    if (input.compare(0,5,"PRINT") == 0)
        Utils::printClientsInfo(_clients);
}