#include "vistaedit.h"
#include"Card/cardeditactivityvisitor.h"
#include"Card/cardappuntamento.h"
#include"Card/cardesame.h"
#include"Card/cardscadenza.h"
#include"Card/cardsport.h"
#include<QDateTime>
#include<QHBoxLayout>
#include<QMessageBox>
namespace gui
{
VistaEdit::VistaEdit(QWidget *parent)
    : QWidget(parent)
{
    setup();
    connectSegnali();
}

void VistaEdit::setup()
{
    layout=new QVBoxLayout(this);
    QHBoxLayout* layoutAlto=new QHBoxLayout();
    layoutAlto->setAlignment(Qt::AlignLeft);
    labelTipo=new QLabel("Seleziona Tipo", this);
    layoutAlto->addWidget(labelTipo);
    comboTipo=new QComboBox(this);
    comboTipo->addItem("Appuntamento");
    comboTipo->addItem("Esame");
    comboTipo->addItem("Sport");
    comboTipo->addItem("Scadenza");
    layoutAlto->addWidget(comboTipo);
    layout->addLayout(layoutAlto);
    areaScorrimento=new QScrollArea(this);
    areaScorrimento->setFrameShape(QFrame::NoFrame); //come su tutte disabilito il contorno
    layout->addWidget(areaScorrimento);
    contenitoreCentrale=new QWidget(this);
    layoutCentrale=new QVBoxLayout(contenitoreCentrale);
    layoutCentrale->setAlignment(Qt::AlignTop);
    areaScorrimento->setWidget(contenitoreCentrale);
    areaScorrimento->setWidgetResizable(true);
    QHBoxLayout* layoutBasso=new QHBoxLayout();
    layoutBasso->setAlignment(Qt::AlignRight);
    bottoneAnnulla=new QPushButton("Annulla", this);
    layoutBasso->addWidget(bottoneAnnulla);
    bottoneSalva=new QPushButton("Salva", this);
    layoutBasso->addWidget(bottoneSalva);
    layout->addLayout(layoutBasso);
}
void VistaEdit::connectSegnali()
{
    connect(comboTipo, &QComboBox::currentIndexChanged, this, [this](){
        int indice=comboTipo->currentIndex();
        if(cardVisualizzata)
            {
              layoutCentrale->removeWidget(cardVisualizzata); //rimuovo la vecchia card
              delete cardVisualizzata; //e la elimino
            cardVisualizzata=nullptr;
            }
        switch(indice)
        {
        case 0:
            cardVisualizzata=new card::CardAppuntamento(this);
            break;
        case 1:
            cardVisualizzata=new card::CardEsame(this);
            break;
        case 2:
            cardVisualizzata=new card::CardSport(this);
            break;
        case 3:
            cardVisualizzata=new card::CardScadenza(this);
            break;
        }

        if(cardVisualizzata)
            layoutCentrale->addWidget(cardVisualizzata); //setto la card
    });
    connect(bottoneAnnulla, &QPushButton::clicked, this, &VistaEdit::operazioneAnnulata);
    connect(bottoneSalva, &QPushButton::clicked, this, [this](){
        //faccio tutti i controlli necessari
        if(!cardVisualizzata->validaSelezioni().isEmpty())
        {
            QMessageBox::warning(this, "Operazione Annullata", cardVisualizzata->validaSelezioni());
        }
        else
        {
            //emit VistaEdit::operazioneConfermata(getAttivita());
            Q_EMIT VistaEdit::operazioneConfermata(getAttivita());
        }


    });
}

void VistaEdit::impostaPerCreazione(unsigned int id_daSalvare)
{
    comboTipo->setEnabled(true);
    id=id_daSalvare;
    dataCreazione=QDateTime::currentDateTime();
    //simulo un cambio indice per far generare la card
    comboTipo->setCurrentIndex(-1);//resetta
    comboTipo->setCurrentIndex(0);
}

void VistaEdit::impostaPerModifca(const modello::Attivita* a)
{
    comboTipo->setEnabled(false);//lo disattivo, perche' un attivita' gia' creata non puo' cambiare tipo
    id=a->getID();
    dataCreazione=a->getDataCreazione(); //cosi non si resetta ad ogni modifica
    card::CardEditActivityVisitor visitor;
    a->accept(&visitor);
    //controllo come sopra
    if(cardVisualizzata)
    {
        layoutCentrale->removeWidget(cardVisualizzata);
        delete cardVisualizzata;
    }
    cardVisualizzata=visitor.getCard();

    if(cardVisualizzata)
        layoutCentrale->addWidget(cardVisualizzata);
}

modello::Attivita* VistaEdit::getAttivita()  const
{
    return cardVisualizzata->generaAttivita(id, dataCreazione);
}
}
