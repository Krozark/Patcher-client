#include <QApplication>

#include <Patcher/MainWindow.hpp>


int main(int argc,char* argv[])
{
    QApplication App(argc, argv);

    patcher::MainWindow window("Patcher");
    window.show();

    return App.exec();
}
