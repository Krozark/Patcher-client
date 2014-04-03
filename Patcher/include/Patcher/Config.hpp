#ifndef PATCHER_CONFIG_HPP
#define PATCHER_CONFIG_HPP

#include <string>
#include <iostream>

#include <QFile>

namespace patcher
{
    class Config
    {
        public:
            Config(const Config&) = delete;
            Config& operator=(const Config&) = delete;

            static const std::string filename;
            static std::string softname;

            Config();

            void setUrl(const std::string&);
            void setUrl();
            const std::string getUrl() const;

            void setVersion(int);
            int getVersion() const;

            void setOs();
            const std::string getOs() const;

            void setBits();
            int getBits() const;

            friend std::ostream& operator<<(std::ostream& output,const Config& self);

            /**
             * \brief convert number version to x.y.z
             * \param number a number version
             */
            static std::string numberToString(int number);
            
        private:
            void makeDefault();
            void makeFile();
            void loadFile(QFile& f);
            void createOrLoad();

            std::string url;
            unsigned int version;
            std::string os;
            unsigned int bits;

    };
}
#endif
