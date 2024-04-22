#pragma once

    #include <iostream>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <unistd.h>
    #include <cstring>
    #include <sstream>
    #include <map>
    #include <functional>

    #include "logger/logger.hpp"
    #include "signal/Handler.hpp"
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
                {"GET", &Server::HandleGetRequest},
                {"POST", &Server::HandlePostRequest},
                {"PUT", &Server::HandlePutRequest},
                {"OPTIONS", &Server::HandleOptionsRequest},
                {"DELETE", &Server::HandleDeleteRequest},
                {"PATCH", &Server::HandlePatchRequest},
                {"UPDATE", &Server::HandleUpdateRequest}
            };

            struct sockaddr_in address;

            Logger logger;
            Handler signal_Handler;

            bool CreateSocket();
            bool Bind();
            bool Listen();
            void Core();
            void HandleClient(int);
            void HandleSignal(int);

            std::string GetHttpMethod(const char *);
            void HandleGetRequest(int);
            void HandlePostRequest(int);
            void HandlePutRequest(int);
            void HandlePatchRequest(int);
            void HandleOptionsRequest(int);
            void HandleDeleteRequest(int);
            void HandleUpdateRequest(int);
            void HandleConnectRequest(int);
            void HandleTraceRequest(int);
    };
