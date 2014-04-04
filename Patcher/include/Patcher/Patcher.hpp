#ifndef PATCHER_PATCHER_HPP
#define PATCHER_PATCHER_HPP

#include <QtWidgets>
#include <QString>

#include <list>
#include <Patcher/Maj.hpp>

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


        private:
            void initMenu();

            QAction* actionQuitter;
            QAction* actionConfiguration;
            QAction* actionVersion;

            
            int checkForMaj();
            int execMaj();

            Config* conf;
            int maj_avalible;

            std::list<Maj> majs;
    };
}

#endif
