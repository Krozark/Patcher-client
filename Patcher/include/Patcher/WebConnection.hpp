#ifndef PATCHER_WEBCONNECTION_HPP
#define PATCHER_WEBCONNECTION_HPP

#include <string>

#include <QNetworkAccessManager>
#include <QNetworkRequest>

namespace patcher
{
    class WebConnection
    {
        public:
            WebConnection(const WebConnection&) = delete;
            WebConnection& operator=(const WebConnection&) = delete;
            
            /**
             * \brief Construct the WebConnection
             * \param base_url the patcher base url of the website www.example.com/patcher/
             */
            WebConnection(const std::string& base_url);

        private:
            const std::string base_url;
            QNetworkRequest request;
            QNetworkAccessManager networkManager;

    };
}

#endif
