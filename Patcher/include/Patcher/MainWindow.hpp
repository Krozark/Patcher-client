#ifndef PATCHER_MAINWINDOWS_HPP
#define PATCHER_MAINWINDOWS_HPP

#include <QtWidgets>
#include <QString>
#include <list>

namespace patcher
{
    class MainWindow : public QMainWindow
    {
        Q_OBJECT
        public:
            MainWindow(const MainWindow&) = delete;
            MainWindow& operator=(const MainWindow&) = delete;

            MainWindow(const QString& title="");
            ~MainWindow();

        public slots:
            void showVersion()const;
            void configSetUrl()const;
            void configMaj()const;
            void configReset()const;

        private:
            void initMenu();
            std::list<QAction*> actions;
            std::list<QMenu*> menus;
    };
}

#endif
