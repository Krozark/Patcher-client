#include <Patcher/Config.hpp>

#include <QUrl>
#include <QInputDialog>

#include <Monitoring/sys.hpp>

namespace patcher
{
    const std::string Config::filename = "config.ini";

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

    void Config::setVertion(int v)
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

    }

    void Config::loadFile(QFile& f)
    {
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
