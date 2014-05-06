#include <patcher/Log.hpp>

#include <patcher/Config.hpp>

namespace patcher
{
    Log::Log(int v,const std::string& m) : number(v), msg(m)
    {
    }

    std::string Log::getNumber()const
    {
        return Config::numberToString(number);
    }

    std::string Log::getMsg()const
    {
        return msg;
    }
}
