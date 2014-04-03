#include <Patcher/WebConnection.hpp>
#include <Patcher/Config.hpp>
#include <Patcher/Maj.hpp>

#include <sstream>

namespace patcher
{
    //url(r'^maj/(?P<soft>[\w-]+)/(?P<from_major>[\d]+).(?P<from_minor>[\d]+).(?P<from_patch>[\d]+)/((?P<to_key>last)|(?P<to_major>[\d]+).(?P<to_minor>[\d]+).(?P<to_patch>[\d]+))/(?P<os>[\w-]+)-x(?P<bit>[\d]+).json'),

    WebConnection::WebConnection(Config& conf) : config(conf)
    {
    }

    std::string WebConnection::majUrl()const
    {
        std::stringstream stream;
        stream<<"maj/"
            <<Config::softname<<"/"
            <<Config::numberToString(config.getVersion())<<"/"
            <<"last/"
            <<config.getOs()<<"-x"<<config.getBits()<<".json";
        return stream.str();
    }

    std::list<Maj>::getMaj()
    {
        std::list<Maj> results;
        return results;
    }
}
