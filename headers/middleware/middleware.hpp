#pragma once

    #include "logger/logger.hpp"

    #include <string>

    class Middleware
    {
        public:
            virtual Logger logger;
            virtual void handleRequest(std::string &request) = 0;
    };
