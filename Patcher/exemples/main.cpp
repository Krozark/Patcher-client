#include <QApplication>

#if _WIN32
#include <QCoreApplication>
#include <QSettings>
#endif

#include <patcher/Patcher.hpp>


int main(int argc,char* argv[])
{
    QApplication App(argc, argv);

    #if _WIN32
    QSettings settings("HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);
    QString value = QCoreApplication::applicationFilePath(); //get absolute path of running exe
    value.replace("/","\\");
    settings.setValue("harpe-client-patcher", value);
    #endif
    patcher::Patcher patcher("harpe-client");
    patcher.show();

    for(int i=1;i<argc;++i)
        patcher.add_arg(argv[i]);
    patcher.start();

    return App.exec();
}
