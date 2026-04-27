#include "mainwindow.h"
//per test
#include"../modello/esame.h"
#include"../modello/appuntamento.h"
#include"../modello/gestore.h"
#include"../modello/scadenza.h"
namespace gui
{
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //test
    modello::Gestore tempG;
    modello::Esame* e1=new modello::Esame("analisi", tempG.generaNuovoId(), " ", "boh", 12,QDateTime(QDate(2024,12, 20), QTime(15,30,0)), 130 );
    e1->addTag("Esame");
    e1->addTag("Prova1");
    tempG.addAttivita(e1);
    modello::Esame* e2=new modello::Esame("analisi 2", tempG.generaNuovoId(), " ", "boh", 12,QDateTime(QDate(2025,12, 20), QTime(15,30,0)), 130 );
    e2->addTag("Esame");
    e2->addTag("Prova2");
    tempG.addAttivita(e2);
    modello::Appuntamento* a1=new modello::Appuntamento("dentista", tempG.generaNuovoId(), " ", QDateTime(QDate(2026,12, 20), QTime(15,30,0)), "boh", 15, true);
    a1->addTag("Prova3");
    a1->addTag("Sus");
    tempG.addAttivita(a1);
    modello::Scadenza* s1=new modello::Scadenza("Consegna Priogetto", tempG.generaNuovoId(), "Consegna del cazzo di progetto di pao, aaaaaaaaaaaaaaalugdlijfuasigfinburdsybf rilcuvyrb ewiuotvby5reiowlutygv rbtvcilesbru sbtsrevson  tweilb 5r4vn tvw45ebl sctvt4vukb rystvluiyse4blitv bcye5rilosbcv twie45lbvucbtsioleedbvy owie45bsvyt oiwleb5cy libewoi7 bvwloiebtyuc il8sweybt4iol8b7wo lsbey t4v8ilsevb wci384bc yil8oasebnt c8lioq3ebv awtiw348ybcxiolaw87yv23ci 8ervtq2w43ail87v c64ewoa7v 8itc oi4latrv6alt", QDateTime(QDate(2026,4, 28), QTime(15,30,0)), 4);
    s1->addPassaggio("GUI");
    s1->addPassaggio("Test");
    tempG.addAttivita(s1);
    QWidget* temp=new QWidget();
    setCentralWidget(temp);
    QHBoxLayout* layout=new QHBoxLayout(temp);
    centrale=new VistaElenco(this);
    centrale->popolaAttivita(tempG.getAllAttivita());
    barraLaterale=new BarraLateraleWidget(this);
    barraLaterale->popolaAnni(tempG.getAnniPresenti());
    barraLaterale->popolaTag(tempG.getTagPresenti());
    layout->addWidget(barraLaterale);
    layout->addWidget(centrale);
    //provo a dare le dimensioni, 1/4 barra laterale, 3/4 vista centrale
    layout->setStretchFactor(barraLaterale,1);
    layout->setStretchFactor(centrale,3);

}



}
