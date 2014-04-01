#include <Patcher/MainWindow.hpp>


namespace patcher
{
    MainWindow::MainWindow(const QString& title) : QMainWindow()
    {
         setWindowTitle(title);
         initMenu();
    }

    void MainWindow::initMenu()
    {
        //Fichier
        QMenu *menuFichier  = menuBar()->addMenu("&Fichier");
        ///Quitter
        QAction *actionQuitter = new QAction("&Quitter", this);
        menuFichier->addAction(actionQuitter);
        connect(actionQuitter, SIGNAL(triggered()), qApp, SLOT(quit()));
        actionQuitter->setShortcut(QKeySequence("Ctrl+Q"));
        //actionQuitter->setIcon(QIcon("quitter.png"));

        //Edition
        QMenu *menuEdition  = menuBar()->addMenu("&Edition");
        //actionGras->setCheckable(true);

        QAction *actionConfiguration = new QAction("&Configuration", this);
        menuEdition->addAction(actionConfiguration);

        //Aide
        QMenu *menuAide     = menuBar()->addMenu("&Aide");

    }
}
