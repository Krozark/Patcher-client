#include <QApplication>

#include <patcher/Patcher.hpp>


int main(int argc,char* argv[])
{
    QApplication App(argc, argv);

    patcher::Patcher patcher("harpe-client");
    patcher.show();

    for(int i=1;i<argc;++i)
        patcher.add_arg(argv[i]);
    patcher.start();

    return App.exec();
}
