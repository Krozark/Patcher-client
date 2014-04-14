#ifndef PATCHER_WEBCONNECTION_HPP
#define PATCHER_WEBCONNECTION_HPP

#include <string>
#include <list>

#include <QNetworkAccessManager>
#include <QNetworkRequest>

#include <Patcher/Maj.hpp>

namespace patcher
{
    class WebConnection
    {
        public:
            WebConnection(const WebConnection&) = delete;
            WebConnection& operator=(const WebConnection&) = delete;

            
            /**
             * \brief Construct the WebConnection
             * \param conf the patcher configuration
             */
            WebConnection();
                
            std::string majUrl()const;

            std::list<Maj> getMaj();

        private:
            QNetworkRequest request;
            QNetworkAccessManager networkManager;

    };
}

#endif
