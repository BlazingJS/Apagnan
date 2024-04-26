#include "server/server.hpp"

int main(int argc, char **argv)
{
    int port = 8080;
    int buffer_size = 1024;

    Server server = Server(
        port,
        buffer_size
    );

    server.Start();

    return 0;
}
