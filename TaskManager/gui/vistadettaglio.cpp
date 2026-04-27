#include "vistadettaglio.h"
#include<QPushButton>
#include<QHBoxLayout>
#include<QIcon>
namespace gui
{
VistaDettaglio::VistaDettaglio(QWidget *parent): QWidget(parent)
{
    setup();
}
/*    VistaDettaglio(QWidget *parent = nullptr);
    void addWidget(QWidget* nuovaCard);
private:
    QScrollArea* areaScorrimento;
    QWidget* contenitoreCentrale;
    QVBoxLayout* layout;
    void setup();*/
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
    layout->addWidget(areaScorrimento);
    layout->addWidget(areaScorrimento);
    contenitoreCentrale=new QWidget(this);
    layoutCentrale=new QVBoxLayout(contenitoreCentrale);
    areaScorrimento->setWidget(contenitoreCentrale);
}

void VistaDettaglio::addWidget(QWidget* nuovaCard)
{
    QLayoutItem* daEliminare=layoutCentrale->takeAt(0);
    if(daEliminare!=nullptr)
    {QWidget* elementoInterno=daEliminare->widget();
        delete elementoInterno;
        delete daEliminare;
    }
    layoutCentrale->addWidget(nuovaCard);
}
}
