#include "mainwindow.h"
//per test
#include"../modello/esame.h"
#include"../modello/appuntamento.h"
#include"../modello/scadenza.h"
#include<QIcon>
namespace gui
{
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), libretto(180, "Informatica", gestorePrincipale.getAllAttivita())
{
    this->setStyleSheet("gui--MainWindow QPushButton{border: 1px solid grey; border-radius: 10px;} gui--MainWindow QPushButton:hover { background-color: lightblue;} gui--MainWindow QPushButton:pressed{ background-color: #e0e0e0; border: 1px solid #b0b0b0;}");
    //test
    modello::Esame* e1=new modello::Esame("analisi", gestorePrincipale.generaNuovoId(), " ", "boh", 12,QDateTime(QDate(2024,12, 20), QTime(15,30,0)), 130 );
    e1->addTag("Esame");
    e1->addTag("Prova1");
    e1->setVoto(27);
    e1->setComplete(true);
    gestorePrincipale.addAttivita(e1);
    modello::Esame* e2=new modello::Esame("analisi 2", gestorePrincipale.generaNuovoId(), " ", "boh", 12,QDateTime(QDate(2025,12, 20), QTime(15,30,0)), 130 );
    e2->addTag("Esame");
    e2->addTag("Prova2");
    e2->setVoto(17);
    e2->setComplete(true);
    gestorePrincipale.addAttivita(e2);
    modello::Appuntamento* a1=new modello::Appuntamento("dentista", gestorePrincipale.generaNuovoId(), " ", QDateTime(QDate(2026,12, 20), QTime(15,30,0)), "boh", 15, true);
    a1->addTag("Prova3");
    a1->addTag("Sus");
    gestorePrincipale.addAttivita(a1);
    modello::Scadenza* s1=new modello::Scadenza("Consegna Priogetto", gestorePrincipale.generaNuovoId(), "Consegna del cazzo di progetto di pao, aaaaaaaaaaaaaaalugdlijfuasigfinburdsybf rilcuvyrb ewiuotvby5reiowlutygv rbtvcilesbru sbtsrevson  tweilb 5r4vn tvw45ebl sctvt4vukb rystvluiyse4blitv bcye5rilosbcv twie45lbvucbtsioleedbvy owie45bsvyt oiwleb5cy libewoi7 bvwloiebtyuc il8sweybt4iol8b7wo lsbey t4v8ilsevb wci384bc yil8oasebnt c8lioq3ebv awtiw348ybcxiolaw87yv23ci 8ervtq2w43ail87v c64ewoa7v 8itc oi4latrv6alt", QDateTime(QDate(2026,4, 28), QTime(15,30,0)), 4);
    s1->addPassaggio("GUI");
    s1->addPassaggio("Test");
    gestorePrincipale.addAttivita(s1);
    QWidget* temp=new QWidget();
    setCentralWidget(temp);
    finestraPrincipale=new QStackedWidget(this);
    QHBoxLayout* layout=new QHBoxLayout(temp);
    centrale=new VistaElenco(this);
    centrale->popolaAttivita(gestorePrincipale.getAllAttivita());
    finestraPrincipale->addWidget(centrale);
    calendarioCentrale=new VistaCalendario(this);
    calendarioCentrale->popolaAttivita(gestorePrincipale.getAllAttivita());
    finestraPrincipale->addWidget(calendarioCentrale);
    dettaglioCentrale=new VistaDettaglio(this);
    finestraPrincipale->addWidget(dettaglioCentrale);
    librettoCentrale=new VistaLibretto(&libretto);
    finestraPrincipale->addWidget(librettoCentrale);
    barraLaterale=new BarraLateraleWidget(this);
    barraLaterale->popolaAnni(gestorePrincipale.getAnniPresenti());
    barraLaterale->popolaTag(gestorePrincipale.getTagPresenti());
    layout->addWidget(barraLaterale);
    QVBoxLayout* layoutCentrale=new QVBoxLayout();
    QHBoxLayout* layoutBottoni=new QHBoxLayout();
    layoutBottoni->setAlignment(Qt::AlignRight);
    bottoneVistaLista=new QPushButton(this);
    QIcon iconaLista(":/gui/assets/icona_lista.png");
    bottoneVistaLista->setIcon(iconaLista);
    bottoneVistaLista->setIconSize(QSize(24,24));
    layoutBottoni->addWidget(bottoneVistaLista);
    bottoneVistaCalendario=new QPushButton(this);
    QIcon iconaCalendario(":/gui/assets/icona_calendario.png");
    bottoneVistaCalendario->setIcon(iconaCalendario);
    bottoneVistaCalendario->setIconSize(QSize(24,24));
    layoutBottoni->addWidget(bottoneVistaCalendario);
    bottoneVistaLibretto=new QPushButton(this);
    QIcon iconaLibretto(":/gui/assets/icona_scuola.png");
    bottoneVistaLibretto->setIcon(iconaLibretto);
    bottoneVistaLibretto->setIconSize(QSize(24,24));
    layoutBottoni->addWidget(bottoneVistaLibretto);
    layoutCentrale->addLayout(layoutBottoni);
    layoutCentrale->addWidget(finestraPrincipale);
    layout->addLayout(layoutCentrale);
    //provo a dare le dimensioni, 1/5 barra laterale, 4/5 vista centrale
    layout->setStretchFactor(barraLaterale,1);
    layout->setStretchFactor(layoutCentrale,4);
    connectSegnali();

}

void MainWindow::connectSegnali()
{
    connect(bottoneVistaLista, &QPushButton::pressed, this, [this](){finestraPrincipale->setCurrentIndex(0);});
    connect(bottoneVistaCalendario, &QPushButton::pressed, this, [this](){finestraPrincipale->setCurrentIndex(1);});
    connect(bottoneVistaLibretto, &QPushButton::pressed, this, [this](){finestraPrincipale->setCurrentIndex(3);});
    connect(calendarioCentrale, &VistaCalendario::attivitaSelezionata, this, [this](modello::Attivita* a) {
        dettaglioCentrale->mostraAttivita(a);
        finestraPrincipale->setCurrentIndex(2);
    });
    connect(dettaglioCentrale, &VistaDettaglio::tornaIndietro, this, [this](){finestraPrincipale->setCurrentIndex(1);});
}}
