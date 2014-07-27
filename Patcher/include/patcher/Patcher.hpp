#ifndef PATCHER_PATCHER_HPP
#define PATCHER_PATCHER_HPP

#include <QtWidgets>
#include <QString>
#include <QListWidget>
#include <QProcess>
#include <QVBoxLayout>


#include <list>
#include <patcher/Maj.hpp>

namespace patcher
{
    class Patcher : public QMainWindow
    {
        Q_OBJECT
        public:
            Patcher(const Patcher&) = delete;
            Patcher& operator=(const Patcher&) = delete;

            Patcher(const std::string& soft="");
            ~Patcher();

            void start();

        public slots:
            void showVersion()const;
            void configSetUrl()const;
            void configMaj();
            void configReset()const;
            void runSoft();
            void quit();


        private:
            void initMenu();
            void iniMainArea();
            int execMaj();

            int maj_avalible;

            std::list<Maj> majs;
            //QListWidget* logList;
            QVBoxLayout layout;

            QProcess soft_thread;
    };
}

#endif
