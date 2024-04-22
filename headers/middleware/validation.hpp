#pragma once

    #include "middleware/middleware.hpp"

    #include <iostream>
    #include <algorithm>
    #include <cctype>
    #include <sstream>
    #include <vector>

    class Validation : public Middleware
    {
        public:
            Validation();
            ~Validation();

            void HandleRequest(std::string &request) override;
        
        private:
            Logger logger;
    };
