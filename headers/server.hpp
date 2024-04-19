#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>

class Server
{
    public:
        Server();
        ~Server();
        
        void Start();

    private:
        int server_fd;
        struct sockaddr_in address;
        int port;

        void HandleClient(int);
};
