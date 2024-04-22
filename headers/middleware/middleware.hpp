#pragma once

    #include "logger/logger.hpp"

    #include <string>

    class Middleware
    {
        public:
            virtual void HandleRequest(std::string &request) = 0;
    };
