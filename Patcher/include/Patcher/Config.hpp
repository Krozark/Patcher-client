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
            Config() = delete;
            Config(const Config&) = delete;
            Config& operator=(const Config&) = delete;

            static const std::string filename;
            static std::string softname;

            static void init();

            static void setUrl(const std::string&);
            static void setUrl();
            static const std::string getUrl();

            static void setVersion(int);
            static int getVersion();

            static void setOs();
            static const std::string getOs();

            static void setBits();
            static int getBits();

            static void makeFile();

            static std::ostream& print(std::ostream& output);

            /**
             * \brief convert number version to x.y.z
             * \param number a number version
             */
            static std::string numberToString(int number);

            
        private:
            static void makeDefault();
            static void loadFile(QFile& f);
            static void createOrLoad();

            static std::string url;
            static unsigned int version;
            static std::string os;
            static unsigned int bits;

    };
}
#endif
