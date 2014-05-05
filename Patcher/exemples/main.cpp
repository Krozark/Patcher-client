#include <QApplication>

#include <Patcher/Patcher.hpp>


int main(int argc,char* argv[])
{
    QApplication App(argc, argv);

    patcher::Patcher patcher("harpe-client");
    patcher.show();

    patcher.start();

    return App.exec();
}
