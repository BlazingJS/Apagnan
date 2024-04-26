#pragma once

    #include <iostream>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <unistd.h>
    #include <cstring>
    #include <sstream>
    #include <map>
    #include <functional>
    #include <algorithm>
    #include <csignal>

    class Request
    {
        public:
            Request();
            ~Request();

            void GET(int, std::vector<std::string>, std::vector<std::string>);
            void POST(int, std::vector<std::string>, std::vector<std::string>);
            void PUT(int, std::vector<std::string>, std::vector<std::string>);
            void PATCH(int, std::vector<std::string>, std::vector<std::string>);
            void DELETE(int, std::vector<std::string>, std::vector<std::string>);
            void OPTIONS(int, std::vector<std::string>, std::vector<std::string>);
            void UPDATE(int, std::vector<std::string>, std::vector<std::string>);
            void TRACE(int, std::vector<std::string>, std::vector<std::string>);
            void CONNECT(int, std::vector<std::string>, std::vector<std::string>);

        private:
            char *Build(std::vector<std::string>);
            char *Send(int, std::vector<std::string>, std::vector<std::string>);
    };
