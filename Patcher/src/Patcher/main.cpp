#include <QApplication>

#include <Patcher/MainWindow.hpp>
#include <Patcher/Config.hpp>


int main(int argc,char* argv[])
{
    QApplication App(argc, argv);

    patcher::Config::softname = "Patcher";

    patcher::MainWindow window("Patcher");
    window.show();


    patcher::Config conf;
    std::cout<<conf<<std::endl;

    return App.exec();
}
