#include "server/server.hpp"

int main(int argc, char **argv)
{
    int port = 8080;

    Server server = Server(port, 1024);

    server.Start();

    return 0;
}
