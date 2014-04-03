#include <Patcher/Maj.hpp>

#include <QUrl>
#include <QNetworkRequest>

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
        std::cout<<"[patcher] download file \""<<filename<<"\" from "<<url<<std::endl;

        QUrl base_url(config.getUrl().c_str());
        QUrl relative_url(majUrl().c_str());
        QUrl url =  base_url.resolved(relative_url);


        QNetworkAccessManager networkManager;
        QNetworkRequest request;

        request.setUrl(url);
        QNetworkReply* reply = networkManager.get(request);  // GET
        
        delete reply;

        bool ok = true;
        return ok;
    }

    bool Maj::erase()
    {
        bool ok = true;
        return ok;
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
        bool ok = true;
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
