#include <QApplication>

#include <Patcher/MainWindow.hpp>
#include <Patcher/Config.hpp>
#include <Patcher/WebConnection.hpp>


int main(int argc,char* argv[])
{
    QApplication App(argc, argv);

    patcher::Config::softname = "harpe-client";
    patcher::Config::init();

    patcher::MainWindow window("Patcher");
    window.show();

    patcher::WebConnection con;
    for(patcher::Maj& maj : con.getMaj())
        maj.apply();

    return App.exec();
}
