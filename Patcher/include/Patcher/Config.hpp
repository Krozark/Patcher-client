#ifndef PATCHER_CONFIG_HPP
#define PATCHER_CONFIG_HPP

#include <string>
#include <QFile>

namespace patcher
{
    class Config
    {
        public:
            Config(const Config&) = delete;
            Config& operator=(const Config&) = delete;

            static const std::string filename;

            Config();

            void setUrl(const std::string&);
            void setUrl();
            const std::string getUrl() const;

            void setVertion(int);
            int getVersion() const;

            void setOs();
            const std::string getOs() const;

            void setBits();
            int getBits() const;
            
            
        private:
            void makeDefault();
            void makeFile();
            void loadFile(QFile& f);
            void createOrLoad();

            std::string url;
            int version;
            std::string os;
            int bits;
    };
}
#endif
