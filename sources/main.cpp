#include "server.hpp"

int main(int argc, char **argv)
{
    int port = 8080;

    Server server = Server();

    server.Start();

    return 0;
}
