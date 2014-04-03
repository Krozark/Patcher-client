#include <Patcher/MainWindow.hpp>


namespace patcher
{
    MainWindow::MainWindow(const QString& title) : QMainWindow()
    {
         actionQuitter = 
             actionConfiguration = 
             actionVersion = nullptr;

         setWindowTitle(title);
         initMenu();

    }

    MainWindow::~MainWindow()
    {
        delete actionQuitter;
        delete actionConfiguration;
        delete actionVersion;
    }

    void MainWindow::initMenu()
    {
        //Fichier
        QMenu* menuFichier  = menuBar()->addMenu("&Fichier");
        ///Quitter
        actionQuitter = new QAction("&Quitter", this);
        menuFichier->addAction(actionQuitter);
        connect(actionQuitter, SIGNAL(triggered()), qApp, SLOT(quit()));
        actionQuitter->setShortcut(QKeySequence("Ctrl+Q"));
        //actionQuitter->setIcon(QIcon("quitter.png"));

        //Edition
        QMenu* menuEdition  = menuBar()->addMenu("&Edition");
        //actionGras->setCheckable(true);

        actionConfiguration = new QAction("&Configuration", this);
        menuEdition->addAction(actionConfiguration);

        //Aide
        QMenu* menuAide     = menuBar()->addMenu("&Aide");
        ///Version
        actionVersion  = new QAction("&Version",this);
        menuAide->addAction(actionVersion);


    }
}
