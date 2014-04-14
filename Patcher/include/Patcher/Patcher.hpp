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

        public slots:
            void showVersion()const;
            void configSetUrl()const;
            void configMaj();
            void configReset()const;


        private:
            void initMenu();

            QAction* actionQuitter;
            QAction* actionConfiguration;
            QAction* actionVersion;

            
            int execMaj();

            int maj_avalible;

            std::list<Maj> majs;
            std::list<QAction*> actions;
            std::list<QMenu*> menus;
    };
}

#endif
