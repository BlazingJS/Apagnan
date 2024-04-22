#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <sstream>
#include <map>
#include <functional>

#include "logger/logger.hpp"
#include "signal/handler.hpp"
#include "server/request.hpp"

class Server
{
    public:
        Request request;

        Server(int, size_t);
        ~Server();
        
        void Start();
        void Stop();

    private:
        int port = 8080;
        int server_fd;
        size_t buffer_size = 1024;
        std::map<std::string, std::function<void(Server&, int)>> methodHandlers = {
            {"GET", &Server::handleGetRequest},
            {"POST", &Server::handlePostRequest},
            {"PUT", &Server::handlePutRequest},
            {"OPTIONS", &Server::handleOptionsRequest},
            {"DELETE", &Server::handleDeleteRequest},
            {"PATCH", &Server::handlePatchRequest},
            {"UPDATE", &Server::handleUpdateRequest}
        };

        struct sockaddr_in address;

        Logger logger;
        Handler signal_handler;

        bool CreateSocket();
        bool Bind();
        bool Listen();
        void Core();
        void HandleClient(int);
        void HandleSignal(int);

        std::string GetHttpMethod(const char *);
        void handleGetRequest(int);
        void handlePostRequest(int);
        void handlePutRequest(int);
        void handlePatchRequest(int);
        void handleOptionsRequest(int);
        void handleDeleteRequest(int);
        void handleUpdateRequest(int);
        void handleConnectRequest(int);
        void handleTraceRequest(int);
};
