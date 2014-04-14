#include <Patcher/Config.hpp>

#include <QUrl>
#include <QInputDialog>
#include <QSettings>
#include <QDir>

#include <fstream>
#include <sstream>

#include <Monitoring/sys.hpp>

namespace patcher
{
    const std::string Config::filename = "config.ini";
    std::string Config::softname = "unknow";
    std::string Config::url;
    unsigned int Config::version = 0;
    std::string Config::os;
    unsigned int Config::bits = 0;

    void Config::init()
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
            msg = " Une URL est obligatoire";
        }
        while(u.isEmpty());

        url = u.toStdString();
    }

    const std::string Config::getUrl()
    {
        return url;
    }

    void Config::setVersion(int v)
    {
        version = v;
    }

    int Config::getVersion()
    {
        return version;
    }

    void Config::setOs()
    {
        os = sys::osName();
    }

    const std::string Config::getOs()
    {
        return os;
    }

    void Config::setBits()
    {
        bits = sys::osBit();
    }

    int Config::getBits()
    {
        return bits;
    }

    std::ostream& Config::print(std::ostream& output)
    {
        output<<"[website]"<<std::endl
            <<"url="<<Config::url<<std::endl

            <<"[soft]"<<std::endl
            //<<"name="<<Config::softname<<std::endl
            <<"version="<<Config::version<<std::endl

            <<"[os]"<<std::endl
            <<"name="<<Config::os<<std::endl
            <<"bit="<<Config::bits<<std::endl;
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
        print(f);
        f.close();
    }

    void Config::loadFile(QFile& f)
    {
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

       if(not QDir("download").exists())
           QDir().mkdir("download");

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
