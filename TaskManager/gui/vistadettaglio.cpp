#include "vistadettaglio.h"
#include<QPushButton>
#include<QHBoxLayout>
#include<QIcon>
#include"cardactivityvisitor.h"
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

void VistaDettaglio::setWidget(QWidget* nuovaCard)
{
    QLayoutItem* daEliminare=layoutCentrale->takeAt(0);
    if(daEliminare!=nullptr)
    {QWidget* elementoInterno=daEliminare->widget();
        delete elementoInterno;
        delete daEliminare;
    }
    layoutCentrale->addWidget(nuovaCard);
}

void VistaDettaglio::mostraAttivita(modello::Attivita* a)
{
    attivitaCorrente=a;
    CardActivityVisitor visitor;
    attivitaCorrente->accept(&visitor);
    CardAttivita* cardDaVisualizzare=visitor.getWidget();
    setWidget(cardDaVisualizzare);
}
}
