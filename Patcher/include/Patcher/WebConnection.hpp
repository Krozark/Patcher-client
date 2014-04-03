#ifndef PATCHER_WEBCONNECTION_HPP
#define PATCHER_WEBCONNECTION_HPP

#include <string>
#include <list>

#include <QNetworkAccessManager>
#include <QNetworkRequest>

namespace patcher
{
    class Config;
    class Maj;

    class WebConnection
    {
        public:
            WebConnection(const WebConnection&) = delete;
            WebConnection& operator=(const WebConnection&) = delete;

            
            /**
             * \brief Construct the WebConnection
             * \param conf the patcher configuration
             */
            WebConnection(Config& conf);
                
            std::string majUrl()const;

            std::list<Maj> getMaj();

        private:
            Config& config;
            QNetworkRequest request;
            QNetworkAccessManager networkManager;

    };
}

#endif
