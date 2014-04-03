#include <Patcher/WebConnection.hpp>
#include <Patcher/Config.hpp>
#include <Patcher/Maj.hpp>

#include <sstream>

#include <QObject>
#include <QEventLoop>
#include <QNetworkReply>

//#include <QScriptEngine>
//#include <QScriptValue>

#include <QMessageBox>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

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

    std::list<Maj> WebConnection::getMaj()
    {
        std::list<Maj> results;
        

        QUrl base_url(config.getUrl().c_str());
        QUrl relative_url(majUrl().c_str());
        QUrl url =  base_url.resolved(relative_url);

        request.setUrl(url);

        QNetworkReply* reply = networkManager.get(request);  // GET


        QEventLoop loop;
        QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
        loop.exec();


        if (reply->error() !=  QNetworkReply::NoError)
        {
            QMessageBox::warning(nullptr,"Error","Immpossible to connect to the url:\n"+url.toString());
            delete reply;
            return results;
        }

        QString data = (QString) reply->readAll();
        delete reply;

        QJsonDocument jsonResponse = QJsonDocument::fromJson(data.toUtf8());
        QJsonObject json = jsonResponse.object();

        int status = json.value("status").toVariant().value<int>();

        switch(status) //0:ok, 1:not soft, 2:not src version, 3:no destionation, 4:lastest
        {
            case 0: //all is good
            case 4 : //lastes
            {
            }break;
            default:
            {
                QString msg = json.value("message").toString();
                QMessageBox::warning(nullptr,"Error","Recive error code:"+QString::number(status)
                                     +"\nMessage:"+msg);
                return results;
            }break;
        }


        QJsonObject datas = json.value("datas").toObject();
        QJsonArray files = datas.value("files").toArray();

        const int _size = files.size();
        for(int i=0;i<_size;++i)
        {
            QJsonObject file = files.at(i).toObject();
            results.emplace_back(config,
                                 file.value("action").toVariant().value<int>(),
                                 file.value("filename").toString().toStdString(),
                                 file.value("url").toString().toStdString());
        }


        config.setVersion(datas.value("version").toVariant().value<int>());
        config.makeFile();

        return results;
    }
}
