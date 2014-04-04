#include <Patcher/Patcher.hpp>

#include <Patcher/Config.hpp>
#include <Patcher/WebConnection.hpp>

#include <QProgressBar>

#include <chrono>
#include <thread>


namespace patcher
{
    Patcher::Patcher(const std::string& soft) : QMainWindow(), conf(nullptr), maj_avalible(0)
    {
        patcher::Config::softname = soft;

         actionQuitter = 
             actionConfiguration = 
             actionVersion = nullptr;

         setWindowTitle(("Patcher - "+soft).c_str());
         initMenu();

    }

    Patcher::~Patcher()
    {
        delete actionQuitter;
        delete actionConfiguration;
        delete actionVersion;

        delete conf;
    }

    void Patcher::start()
    {
        checkForMaj();
        if(maj_avalible > 0)
        {
            execMaj();
        }
    }

    void Patcher::initMenu()
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

    int Patcher::checkForMaj()
    {
        if(not conf)
            conf = new Config;

        patcher::WebConnection con(*conf);
        majs = con.getMaj();

        maj_avalible = majs.size();



        return maj_avalible;
    }

    int Patcher::execMaj()
    {
        if (maj_avalible <= 0)
            return 0;

        QProgressBar progressBar;
        progressBar.setMaximumHeight(16);
        progressBar.setMaximumWidth(200);
        //progressBar->setTextVisible(false);
        progressBar.setRange(0,maj_avalible);
        this->statusBar()->addPermanentWidget(&progressBar, 0);
        this->statusBar()->showMessage(QString("Loading"));
        
        int nb = 0;
        int i = 1;
        for(patcher::Maj& maj : majs)
        {
            this->statusBar()->showMessage(QString("download "+QString::number(i)+"/"+QString::number(maj_avalible)));
            if(not maj.isDone())
                nb+= maj.apply();
            progressBar.setValue(++i);
        }

        this->statusBar()->clearMessage();
        this->statusBar()->removeWidget(&progressBar);

        return nb;
    }
}
