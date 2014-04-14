#include <Patcher/Maj.hpp>
#include <Patcher/Config.hpp>

#include <QObject>
#include <QUrl>
#include <QFile>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkReply>

#include <QEventLoop>

#include <stdio.h>

namespace patcher
{
    
    Maj::Maj(int action,std::string filename,std::string url): action(action), filename(filename), url(url), done(false)
    {
    }

    bool Maj::apply()
    {
        bool ok = true;
        switch(action)
        {
            case 1: //new
            {
                ok = download();
                if (ok)
                    write();
            }break;
            case 2: //maj
            {
                ok = replace();
            }break;
            case 3: //delete 
            {
                ok = erase();
            }break;
            default: //unknow
            {
                ok = false;
            }break;
        }
        done = ok;
        return ok;
    }

    bool Maj::download()
    {
        std::cout<<"[patcher] download file \""<<filename<<"\" from "<<url<<" "<<std::flush;

        QUrl base_url(Config::getUrl().c_str());
        QUrl relative_url(url.c_str());
        QUrl url =  base_url.resolved(relative_url);


        QNetworkRequest request;
        request.setUrl(url);

        QNetworkAccessManager networkManager;
        QNetworkReply* reply = networkManager.get(request);

        QEventLoop loop;
        QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
        loop.exec();
        
        //open file
        QFile localFile(("download/"+filename).c_str());
        if (!localFile.open(QIODevice::WriteOnly))
        {
            std::cout<<"Failed"<<std::endl;
            return false;
        }
        //write in it
        localFile.write(reply->readAll());
        localFile.close();
        delete reply;

        std::cout<<"Ok"<<std::endl;
        return true;
    }

    bool Maj::erase()
    {
        return QFile::remove(filename.c_str());
    }

    bool Maj::replace()
    {
        bool ok = download();
        if(ok)
        {
            erase();
            ok = write();
        }
        return ok;
    }

    bool Maj::write()
    {
        bool ok = ::rename(("download/"+filename).c_str(),filename.c_str()) == 0;
        if (filename == Config::softname or filename == Config::softname+".exe")
            QFile::setPermissions(filename.c_str(),
                                  QFile::ReadOwner|QFile::WriteOwner|QFile::ExeOwner
                                  |QFile::ReadGroup|QFile::ExeGroup
                                  |QFile::ReadOther|QFile::ExeOther
                                  );
        return ok;
    }
    
    std::ostream& operator<<(std::ostream& output,const Maj& self)
    {
        output<<"{action:"<<self.action
            <<",\nfilename:"<<self.filename
            <<",\nurl:"<<self.url
            <<",\ndone:"<<self.done
            <<"}";
        return output;
    }
}
