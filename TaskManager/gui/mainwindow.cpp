#include "mainwindow.h"
//per test
#include"../modello/esame.h"
#include"../modello/appuntamento.h"
#include"../modello/gestore.h"
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
    QWidget* temp=new QWidget();
    setCentralWidget(temp);
    QHBoxLayout* layout=new QHBoxLayout(temp);
    barraLaterale=new BarraLateraleWidget(this);
    barraLaterale->popolaAnni(tempG.getAnniPresenti());
    barraLaterale->popolaTag(tempG.getTagPresenti());
    layout->addWidget(barraLaterale);
}



}
