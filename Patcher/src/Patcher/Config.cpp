#include <Patcher/Config.hpp>

#include <QUrl>
#include <QInputDialog>
#include <QSettings>

#include <fstream>
#include <sstream>

#include <Monitoring/sys.hpp>

namespace patcher
{
    const std::string Config::filename = "config.ini";
    std::string Config::softname = "unknow";

    Config::Config()
    {
        createOrLoad();
    }

    void Config::setUrl(const std::string& u)
    {
        url = u;
    }

    void Config::setUrl()
    {
        QString u;
        QString msg = "";
        do {
            u = QInputDialog::getText(nullptr, "title", "Url du site"+msg, QLineEdit::Normal);
            msg = " Une URL valide est obligatoire";
        }
        while(not QUrl(u).isValid() or u.isEmpty());

        url = u.toStdString();
    }

    const std::string Config::getUrl() const
    {
        return url;
    }

    void Config::setVersion(int v)
    {
        version = v;
    }

    int Config::getVersion()const
    {
        return version;
    }

    void Config::setOs()
    {
        os = sys::osName();
    }

    const std::string Config::getOs()const
    {
        return os;
    }

    void Config::setBits()
    {
        bits = sys::osBit();
    }

    int Config::getBits()const
    {
        return bits;
    }

    std::ostream& operator<<(std::ostream& output,const Config& self)
    {
        output<<"[website]"<<std::endl
            <<"url="<<self.url<<std::endl

            <<"[soft]"<<std::endl
            //<<"name="<<Config::softname<<std::endl
            <<"version="<<self.version<<std::endl

            <<"[os]"<<std::endl
            <<"name="<<self.os<<std::endl
            <<"bit="<<self.bits<<std::endl;
        return output;
    }

    std::string Config::numberToString(int number)
    {
        unsigned int major = number / (100*100);
        unsigned int minor = number / 100 - major*100;
        unsigned int patch = number - (minor + major*100)*100;
        std::stringstream stream;
        stream<<major<<"."<<minor<<"."<<patch;
        return stream.str();
    }

    void Config::makeDefault()
    {
        setUrl();
        version = 0;
        setOs();
        setBits();

        makeFile();
    }

    void Config::makeFile()
    {
        std::fstream f(filename, std::fstream::out | std::fstream::trunc);
        f<<*this;
        f.close();
    }

    void Config::loadFile(QFile& f)
    {
        std::cout<<"loadFile"<<std::endl;
        QSettings settings(filename.c_str(),QSettings::IniFormat);

        //website
        {
            auto tmp = settings.value("website/url");
            if(tmp.isNull())
                setUrl();
            else
                url = tmp.toString().toStdString();
        }
        //soft
        {
            auto tmp = settings.value("soft/version");
            if (tmp.isNull())
                version = 0;
            else
                version = tmp.toInt();
        }
        //os
        {
            auto tmp = settings.value("os/name");
            if(tmp.isNull())
                setOs();
            else
                os = tmp.toString().toStdString();
        }
        {
            auto tmp= settings.value("os/bit");
            if(tmp.isNull())
                setBits();
            else
                bits = tmp.toInt();
        }
    }

    void Config::createOrLoad()
    {
       QFile f(filename.c_str());

        if(!f.exists()) 
        {       
            makeDefault();
            makeFile();
        }  
        else
        {
            loadFile(f);
        }
    }
}
