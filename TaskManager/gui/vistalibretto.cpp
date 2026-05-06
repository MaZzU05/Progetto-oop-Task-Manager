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

/*
 *     void popolaAttivita(const std::vector<modello::Attivita*>& vec) override;
private:
    void setup();
    std::vector<modello::Attivita*> vecAttivita;
    QScrollArea* areaScorrimento;
    QWidget* contenitoreCentrale;
    QVBoxLayout* layout;
    QHBoxLayout* layoutAlto;
    QVBoxLayout* layoutCentrale;
    QVBoxLayout* layoutBasso;
    void setWidget(QWidget* nuovaCard);
    QLabel* labeltipoCorso;
    QLabel* labelnomeCorso;
    QLabel* labelCFU;
    QProgressBar* barraCFU;
    QLabel* labelMediaPesata;
    QProgressBar* barraMedia;
    QLabel* labelVotoAtteso;
    QProgressBar* barraVotoAtteso;
 */

void VistaLibretto::setup()
{
    layout=new QVBoxLayout(this);
    layoutAlto=new QHBoxLayout();
    labeltipoCorso=new QLabel(this);
    layoutAlto->addWidget(labeltipoCorso);
    labelnomeCorso=new QLabel(this);
    layoutAlto->addWidget(labelnomeCorso);
    modificaInfo=new QPushButton("Modifica Tipologia Laurea", this);
    //modificaInfo->setStyleSheet("QPushButton { background-color: transparent; padding: 5px; border: 1px solid grey; border-radius: 10px; } QPushButton:hover { background-color: lightblue; } QPushButton:pressed { background-color: #e0e0e0; border: 1px solid #b0b0b0; }");
    layoutAlto->addWidget(modificaInfo);
    layout->addLayout(layoutAlto);
    contenitoreCentrale=new QWidget(this);
    areaScorrimento=new QScrollArea(this);
    areaScorrimento->setWidget(contenitoreCentrale);
    areaScorrimento->setFrameShape(QFrame::NoFrame);
    //areaScorrimento->setStyleSheet("background-color: transparent;"); //mettendo lo sfondo trasparente cerco un effetto piu' elegante
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
           labeltipoCorso->setText("Laurea a cilco unico");
           break;
       default:
           labeltipoCorso->setText("Errore");
    }
    labelnomeCorso->setText(libretto->getCorsoLaurea());
    labelCFU->setText("CFU: "+QString::number(libretto->getCfuCompletati())+"/"+QString::number(libretto->getCfu()));
    barraCFU->setRange(0, libretto->getCfu());
    barraCFU->setValue(libretto->getCfuCompletati());
    labelMediaPesata->setText("Media Pesata: "+QString::number(libretto->getMediaPesata())+"/30");
    barraMedia->setRange(0,30);
    barraMedia->setValue(libretto->getMediaPesata());
    labelVotoAtteso->setText("Voto Finale Atteso: "+QString::number(libretto->getVotoFinaleAtteso())+"/110");
    barraVotoAtteso->setRange(0,110);
    barraVotoAtteso->setValue(libretto->getVotoFinaleAtteso());
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
