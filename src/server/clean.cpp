#include "../../include/server.hpp"
#include "../../include/client.hpp"
#include "../../include/utls.hpp"

void server::clean()
{
    for (size_t i = 0; i < _pfds.size();i++)
        close(_pfds[i].fd);
    bye();
}