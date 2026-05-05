#include "vistadettaglio.h"
#include<QPushButton>
#include<QHBoxLayout>
#include<QIcon>
#include"Card/cardactivityvisitor.h"
namespace gui
{
VistaDettaglio::VistaDettaglio(QWidget *parent): QWidget(parent)
{
    setup();
}

void VistaDettaglio::setup()
{
    layout=new QVBoxLayout(this);
    QHBoxLayout* layoutAlto= new QHBoxLayout();
    layoutAlto->setAlignment(Qt::AlignLeft);
    QPushButton* backButton=new QPushButton(this);
    QIcon backIcon(":/gui/assets/freccia_sx.png");
    backButton->setIcon(backIcon);
    backButton->setIconSize(QSize(24,24)); //la ingrandisco leggermente, qt la faceva troppo piccola
    layoutAlto->addWidget(backButton);
    connect(backButton, &QPushButton::pressed, this, &VistaDettaglio::tornaIndietro);
    layout->addLayout(layoutAlto);
    areaScorrimento=new QScrollArea(this);
    areaScorrimento->setFrameShape(QFrame::NoFrame);
    areaScorrimento->setStyleSheet("background-color: transparent;"); //mettendo lo sfondo trasparente cerco un effetto piu' elegante
    layout->addWidget(areaScorrimento);
    contenitoreCentrale=new QWidget(this);
    layoutCentrale=new QVBoxLayout(contenitoreCentrale);
    layoutCentrale->setAlignment(Qt::AlignTop);
    areaScorrimento->setWidget(contenitoreCentrale);
    areaScorrimento->setWidgetResizable(true);
}
/*
void VistaElenco::popolaAttivita(const std::vector<modello::Attivita*>& vec)
{
    QLayoutItem* daEliminare;
    //devo svuotare il layout dai widget contenuti prima di caricarlo, non essendoci un clear faccio un loop eliminandoli uno ad uno dal primo fintanto che non e' vuoto
    while((daEliminare=layout->takeAt(0)))//estraggo il primo elemento
    {
        QWidget* elementoInterno=daEliminare->widget();//estraggo il vidget contenuto
        delete elementoInterno;
        delete daEliminare;
    }
    cardEspansaAttualmente=nullptr;
    for (modello::Attivita* a:vec)
    {
        card::CardActivityVisitor visitor;
        a->accept(&visitor);
        card::CardAttivita* nuovaCard=visitor.getWidget();
        layout->addWidget(nuovaCard);
        connect(nuovaCard, &card::CardAttivita::selezionata, this, [this, a, nuovaCard](card::CardAttivita*, bool espansa){
            if(espansa)
             {
                //se vi e' aperta una card diversa la chiudo
                if(cardEspansaAttualmente!=nullptr&&cardEspansaAttualmente!=nuovaCard)
                {
                    cardEspansaAttualmente->setSelezionata(false);
                }
                //segno che ora e' aperta questa
                cardEspansaAttualmente=nuovaCard;
                //lo dico alla mainWindow
                //emit attivitaSelezionata(a);
                Q_EMIT attivitaSelezionata(a);
             }
             else {
                 //la si sta chiudendo
                if(cardEspansaAttualmente==nuovaCard)
                 {
                     cardEspansaAttualmente=nullptr;
                    Q_EMIT attivitaSelezionata(nullptr); //necessario per indicare la deselezione
                }
             }

        });
    }
    layout->addStretch();
}
 */

void VistaDettaglio::setWidget(QWidget* nuovaCard)
{
    QLayoutItem* daEliminare;
    //uso il while anche se ho un solo elemento, cosi' e' gia' robusta per eventuali modifiche
    while((daEliminare=layoutCentrale->takeAt(0))!=nullptr)
    {QWidget* elementoInterno=daEliminare->widget();
        delete elementoInterno;
        delete daEliminare;
    }
    layoutCentrale->addWidget(nuovaCard);
}

void VistaDettaglio::mostraAttivita(modello::Attivita* a)
{
    //replico il pattern per la emit di VistaElenco, rivolto ad una singola attivita
    attivitaCorrente=a;
    card::CardActivityVisitor visitor;
    attivitaCorrente->accept(&visitor);
    card::CardAttivita* cardDaVisualizzare=visitor.getWidget();
    setWidget(cardDaVisualizzare);
    connect(cardDaVisualizzare, &card::CardAttivita::selezionata, this, [this, a](card::CardAttivita*, bool espansa){
        if(espansa)
        {
            //lo dico alla mainWindow
            //emit attivitaSelezionata(a);
            Q_EMIT attivitaSelezionata(a);
        }
        else {
            //la si sta chiudendo
                Q_EMIT attivitaSelezionata(nullptr); //necessario per indicare la deselezione

        }
    });
}
}

