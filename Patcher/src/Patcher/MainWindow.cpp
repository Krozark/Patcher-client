#include <Patcher/MainWindow.hpp>
#include <Patcher/WebConnection.hpp>

#include <Patcher/Config.hpp>


#define ADD_ACTION(parent,var,str) actions.push_back(new QAction(str,this));\
    QAction* var = actions.back();\
    parent->addAction(var);

#define ADD_MENU(parent,var,str) menus.push_back(parent->addMenu(str));\
    QMenu* var = menus.back();

namespace patcher
{
    MainWindow::MainWindow(const QString& title) : QMainWindow()
    {
         setWindowTitle(title);
         initMenu();
    }

    MainWindow::~MainWindow()
    {
        for(QAction* action : actions)
            delete action;
        actions.clear();

        for(QMenu* menu : menus)
            delete menu;
        menus.clear();
    }

    //// SLOTS //////
    void MainWindow::showVersion()const
    {
        QMessageBox::information(nullptr,"Version","Version acctuelle:\n"+QString(Config::numberToString(Config::getVersion()).c_str()));
    }

    void MainWindow::setUrl()const
    {
        Config::setUrl();
        Config::makeFile();
    }

    void MainWindow::maj()const
    {
        patcher::WebConnection con;
        for(patcher::Maj& maj : con.getMaj())
            maj.apply();
    }

    void MainWindow::initMenu()
    {
        //Fichier
        QMenu* menuFichier  = menuBar()->addMenu("&Fichier");
        ///Quitter

        ADD_ACTION(menuFichier,actionQuitter,"&Quitter");
        connect(actionQuitter, SIGNAL(triggered()), qApp, SLOT(quit()));
        actionQuitter->setShortcut(QKeySequence("Ctrl+Q"));
        //actionQuitter->setIcon(QIcon("quitter.png"));

        //Edition
        QMenu* menuEdition  = menuBar()->addMenu("&Edition");
        //actionGras->setCheckable(true);

        ADD_MENU(menuEdition,menuConfiguration,"&Configuration");
        ADD_ACTION(menuConfiguration,actionConfigurationUrl,"definir Url du site");
        connect(actionConfigurationUrl,SIGNAL(triggered()),this,SLOT(setUrl()));
        ADD_ACTION(menuConfiguration,actionConfigurationMaj,"Lancer une Maj");
        connect(actionConfigurationUrl,SIGNAL(triggered()),this,SLOT(maj()));

        //Aide
        QMenu* menuAide     = menuBar()->addMenu("&Aide");
        ///Version
        ADD_ACTION(menuAide,actionVersion,"&Version")
        connect(actionVersion, SIGNAL(triggered()),this, SLOT(showVersion()));


    }
}
