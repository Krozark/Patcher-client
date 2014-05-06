#ifndef PATCHER_LOG_HPP
#define PATCHER_LOG_HPP

#include <string>

namespace patcher
{
    class Log
    {
        public:
            Log(int version,const std::string& msg);
            Log(const Log&) = delete;
            Log& operator=(const Log&) = delete;

            std::string getNumber()const;
            std::string getMsg()const;

        private:
            const int number;
            const std::string msg;
    };
}
#endif
