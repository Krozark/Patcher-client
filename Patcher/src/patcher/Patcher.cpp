#include <patcher/Patcher.hpp>

#include <patcher/Config.hpp>
#include <patcher/WebConnection.hpp>
#include <patcher/Log.hpp>

#include <QProgressBar>
#include <QListWidgetItem>
#include <QLabel>
#include <QGroupBox>
#include <QScrollArea>
#include <QMessageBox>



#include <iostream>

#define ADD_ACTION(parent,var,str) QAction* var = new QAction(str,this);\
    parent->addAction(var);

#define ADD_MENU(parent,var,str) QMenu* var = parent->addMenu(str);


namespace patcher
{
    Patcher::Patcher(const std::string& soft) : QMainWindow(), maj_avalible(0)//, logList(nullptr)
    {
        patcher::Config::softname = soft;
        setFixedSize(400,300);

        setWindowTitle(("Patcher - "+soft).c_str());
        initMenu();
        iniMainArea();
        soft_thread.setStandardOutputFile(("logs/"+soft+".txt").c_str(),QIODevice::Append);
        soft_thread.setStandardErrorFile(("logs/"+soft+".err.txt").c_str(),QIODevice::Append);
        QStringList env = QProcess::systemEnvironment();
        env<<"LD_LIBRARY_PATH=.";
        soft_thread.setEnvironment(env);
    }

    Patcher::~Patcher()
    {
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

        std::list<Log> logs;
        majs = con.getMaj(logs);
        //layout.clear();

        for(Log& log : logs)
        {
            QLabel* widget = new QLabel((log.getNumber()
                                           +": "
                                           +log.getMsg()).c_str());
            //widget->setMinimumSize(widget->minimumSizeHint());

            this->layout.addWidget(widget);

            std::cout<<log.getNumber()<<" "<<log.getMsg()<<std::endl;
        }

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

    void Patcher::runSoft()
    {
        QString name = QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + QDir::separator() + Config::softname.c_str()).toString();
        #if __WIN32
            name +=".exe";
        #endif
        soft_thread.start(name);
    }

    void Patcher::quit()
    {
        if(soft_thread.state() == QProcess::Running)
        {
            QMessageBox::warning(nullptr,"Error",QString((Config::softname+" is running. Close it.").c_str()));
        }
        else
            qApp->quit();
    }

    ////////

    void Patcher::initMenu()
    {
        //Fichier
        QMenu* menuFichier  = menuBar()->addMenu("&Fichier");
        ///Quitter

        ADD_ACTION(menuFichier,actionRun,("Lancer" + Config::softname).c_str());
        connect(actionRun, SIGNAL(triggered()),this, SLOT(runSoft()));
        actionRun->setShortcut(QKeySequence("Ctrl+Enter"));

        ADD_ACTION(menuFichier,actionQuitter,"&Quitter");
        connect(actionQuitter, SIGNAL(triggered()),this, SLOT(quit()));
        actionQuitter->setShortcut(QKeySequence("Ctrl+Q"));
        //actionQuitter->setIcon(QIcon("quitter.png"));

        //Edition
        QMenu* menuEdition  = menuBar()->addMenu("&Edition");
        //actionGras->setCheckable(true);

        ADD_MENU(menuEdition,menuConfiguration,"&Configuration");

        ADD_ACTION(menuConfiguration,actionConfigurationUrl,"Definir l'url du site");
        connect(actionConfigurationUrl,SIGNAL(triggered()),this,SLOT(configSetUrl()));

        ADD_ACTION(menuConfiguration,actionConfigurationMaj,"Lancer une Maj");
        connect(actionConfigurationMaj,SIGNAL(triggered()),this,SLOT(configMaj()));
        actionConfigurationMaj->setShortcut(QKeySequence("F5"));

        ADD_ACTION(menuConfiguration,actionConfigurationReset,"Reset");
        connect(actionConfigurationReset,SIGNAL(triggered()),this,SLOT(configReset()));
        actionConfigurationReset->setShortcut(QKeySequence("Ctrl+L"));

        //Aide
        QMenu* menuAide     = menuBar()->addMenu("&Aide");
        ///Version
        ADD_ACTION(menuAide,actionVersion,"&Version")
        connect(actionVersion, SIGNAL(triggered()),this, SLOT(showVersion()));
    }

    void Patcher::iniMainArea()
    {
       QWidget* zoneCentrale = new QScrollArea;

       zoneCentrale->setLayout(&layout);
       setCentralWidget(zoneCentrale);
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
