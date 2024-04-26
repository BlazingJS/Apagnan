#pragma once

    #include <iostream>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <unistd.h>
    #include <cstring>
    #include <sstream>
    #include <map>
    #include <functional>
    #include <csignal>

    #include "logger/logger.hpp"
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

            struct sockaddr_in address;

            Logger logger;

            bool CreateSocket();
            bool Bind();
            bool Listen();
            void Core();
            void HandleClient(int);

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
