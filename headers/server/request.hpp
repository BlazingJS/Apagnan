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

            template <typename T>
            void GET(int, std::vector<std::string>, T const &);

            template <typename T>
            void POST(int, std::vector<std::string>, T const &);
            
            template <typename T>
            void PUT(int, std::vector<std::string>, T const &);
            
            template <typename T>
            void PATCH(int, std::vector<std::string>, T const &);
            
            template <typename T>
            void DELETE(int, std::vector<std::string>, T const &);
            
            template <typename T>
            void OPTIONS(int, std::vector<std::string>, T const &);
            
            template <typename T>
            void UPDATE(int, std::vector<std::string>, T const &);
            
            template <typename T>
            void TRACE(int, std::vector<std::string>, T const &);
            
            template <typename T>
            void CONNECT(int, std::vector<std::string>, T const &);

        private:
            std::string Prepare(std::vector<std::string>);
            char *Build(std::vector<std::string>);

            template <typename T>
            char *Send(int, std::vector<std::string>, T const &data);

            size_t ContentLength(std::string);
    };
