#ifndef PATCHER_MAINWINDOWS_HPP
#define PATCHER_MAINWINDOWS_HPP

#include <QtWidgets>
#include <QString>

namespace patcher
{
    class MainWindow : public QMainWindow
    {
        Q_OBJECT
        public:
            MainWindow(const MainWindow&) = delete;
            MainWindow& operator=(const MainWindow&) = delete;

            MainWindow(const QString& title="");

        private:
            void initMenu();
    };
}

#endif
