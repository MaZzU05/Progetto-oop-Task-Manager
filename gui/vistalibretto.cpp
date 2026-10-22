#include "vistalibretto.h"
#include"QLabel"
#include<QInputDialog>
#include<QMessageBox>
#include"finestrainizializzazionelibretto.h"
#include"Card/cardactivityvisitor.h"
namespace gui
{
VistaLibretto::VistaLibretto(modello::Libretto* libretto, QWidget *parent): QWidget(parent), libretto(libretto)
{
    setup();
    aggiornaVista();
    connectSegnali();
}


void VistaLibretto::setup()
{
    layout=new QVBoxLayout(this);
    layoutAlto=new QHBoxLayout();
    labeltipoCorso=new QLabel(this);
    layoutAlto->addWidget(labeltipoCorso);
    labelnomeCorso=new QLabel(this);
    layoutAlto->addWidget(labelnomeCorso);
    modificaInfo=new QPushButton("Modifica Tipologia Laurea", this);
    layoutAlto->addWidget(modificaInfo);
    layout->addLayout(layoutAlto);
    contenitoreCentrale=new QWidget(this);
    areaScorrimento=new QScrollArea(this);
    areaScorrimento->setWidget(contenitoreCentrale);
    areaScorrimento->setFrameShape(QFrame::NoFrame);
    areaScorrimento->setWidgetResizable(true);
    layout->addWidget(areaScorrimento);
    layoutCentrale=new QVBoxLayout(contenitoreCentrale);
    layoutCentrale->setAlignment(Qt::AlignTop);
    layoutBasso=new QGridLayout();
    labelMediaPesata=new QLabel(this);
    layoutBasso->addWidget(labelMediaPesata, 0, 0, 1, 1);
    barraMedia=new QProgressBar(this);
    layoutBasso->addWidget(barraMedia, 0,1,1,2);
    labelVotoAtteso=new QLabel(this);
    layoutBasso->addWidget(labelVotoAtteso, 1,0,1,1);
    barraVotoAtteso=new QProgressBar(this);
    layoutBasso->addWidget(barraVotoAtteso, 1, 1, 1, 2);
    labelCFU=new QLabel(this);
    layoutBasso->addWidget(labelCFU, 2, 0, 1, 1);
    barraCFU=new QProgressBar(this);
    layoutBasso->addWidget(barraCFU, 2, 1, 1, 2);
    layout->addLayout(layoutBasso);
}

void VistaLibretto::connectSegnali()
{
    connect(modificaInfo, &QPushButton::clicked, this, [this](){
        FinestraInizializzazioneLibretto finestraLibretto(this);
        if(finestraLibretto.exec()==QDialog::Accepted)
        {
            libretto->setCfu(finestraLibretto.getCFU());
            libretto->setCorsoLaurea(finestraLibretto.getNomeCorso());
            aggiornaVista();
        }

    });
}
void VistaLibretto::setWidget(std::vector<modello::Esame*> esami)
{
    QLayoutItem* daEliminare;
    while((daEliminare=layoutCentrale->takeAt(0))!=nullptr)
    {QWidget* elementoInterno=daEliminare->widget();
        delete elementoInterno;
        delete daEliminare;
    }
    for(modello::Esame* esame:esami)
    {
        card::CardActivityVisitor visitor;
        esame->accept(&visitor);
        card::CardAttivita* nuovaCard=visitor.getWidget();
        layoutCentrale->addWidget(nuovaCard);

    }
}
void VistaLibretto::aggiornaVista()
{
    switch(libretto->getCfu())
    {
       case 120:
        labeltipoCorso->setText("Laurea Magistrale");
           break;

       case 180:
        labeltipoCorso->setText("Laurea Triennale");
           break;
       case 300:
           labeltipoCorso->setText("Laurea a ciclo unico");
           break;
       default:
           labeltipoCorso->setText("Errore");
    }
    labelnomeCorso->setText(libretto->getCorsoLaurea());
    labelCFU->setText("CFU: "+QString::number(libretto->getCfuCompletati())+"/"+QString::number(libretto->getCfu()));
    barraCFU->setRange(0, libretto->getCfu());
    barraCFU->setValue(libretto->getCfuCompletati());
    barraCFU->setFormat("%v/%m");
    labelMediaPesata->setText("Media Pesata: "+QString::number(libretto->getMediaPesata())+"/30");
    barraMedia->setRange(0,30);
    barraMedia->setValue(libretto->getMediaPesata());
    barraMedia->setFormat("%v/%m");
    labelVotoAtteso->setText("Voto Finale Atteso: "+QString::number(libretto->getVotoFinaleAtteso())+"/110");
    barraVotoAtteso->setRange(0,110);
    barraVotoAtteso->setValue(libretto->getVotoFinaleAtteso());
    barraVotoAtteso->setFormat("%v/%m");
    std::vector<modello::Esame*> vecEsami;
    auto vecFuturi=libretto->getEsamiFuturi();
    auto vecSuperati=libretto->getEsamiSuperati();
    auto vecNonSuperati=libretto->getEsamiNonSuperati();
    vecEsami.insert(vecEsami.end(), vecFuturi.begin(), vecFuturi.end());
    vecEsami.insert(vecEsami.end(), vecSuperati.begin(), vecSuperati.end());
    vecEsami.insert(vecEsami.end(), vecNonSuperati.begin(), vecNonSuperati.end());
    setWidget(vecEsami);


}

void VistaLibretto::notify(modello::Gestore&)
{
    aggiornaVista();
}
}
