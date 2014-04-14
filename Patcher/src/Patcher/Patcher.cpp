#include <Patcher/Patcher.hpp>

#include <Patcher/Config.hpp>
#include <Patcher/WebConnection.hpp>

#include <QProgressBar>

#include <chrono>
#include <thread>

#include <Patcher/Config.hpp>


#define ADD_ACTION(parent,var,str) actions.push_back(new QAction(str,this));\
    QAction* var = actions.back();\
    parent->addAction(var);

#define ADD_MENU(parent,var,str) menus.push_back(parent->addMenu(str));\
    QMenu* var = menus.back();


namespace patcher
{
    Patcher::Patcher(const std::string& soft) : QMainWindow(), maj_avalible(0)
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
    }

    void Patcher::start()
    {
        configMaj();
    }
    
    //// SLOTS //////
    void Patcher::showVersion()const
    {
        QMessageBox::information(nullptr,"Version","Version acctuelle:\n"+QString(Config::numberToString(Config::getVersion()).c_str()));
    }

    void Patcher::configSetUrl()const
    {
        Config::setUrl();
        Config::makeFile();
    }

    void Patcher::configMaj()
    {
        Config::init();
        patcher::WebConnection con;
        majs = con.getMaj();

        maj_avalible = majs.size();

        if(maj_avalible > 0)
        {
            execMaj();
        }
    }

    void Patcher::configReset()const
    {
        Config::makeDefault();
    }

    void Patcher::initMenu()
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
        connect(actionConfigurationUrl,SIGNAL(triggered()),this,SLOT(configSetUrl()));

        ADD_ACTION(menuConfiguration,actionConfigurationMaj,"Lancer une Maj");
        connect(actionConfigurationMaj,SIGNAL(triggered()),this,SLOT(configMaj()));

        ADD_ACTION(menuConfiguration,actionConfigurationReset,"Reset");
        connect(actionConfigurationReset,SIGNAL(triggered()),this,SLOT(configReset()));

        //Aide
        QMenu* menuAide     = menuBar()->addMenu("&Aide");
        ///Version
        ADD_ACTION(menuAide,actionVersion,"&Version")
        connect(actionVersion, SIGNAL(triggered()),this, SLOT(showVersion()));
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
