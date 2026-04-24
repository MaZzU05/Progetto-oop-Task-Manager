#include "vistaelenco.h"
#include<QPushButton>
namespace gui {


VistaElenco::VistaElenco(QWidget *parent): AbstractVistaAttivita(parent)
{
    setup();
}
/*
    QScrollArea* areaScorrimento;
    QWidget* contenitoreCentrale;
    QVBoxLayout* layout;
 */
void VistaElenco::setup()
{
    this->setStyleSheet("background-color: purple;");
    QVBoxLayout* principale=new QVBoxLayout(this);
    areaScorrimento=new QScrollArea(this);
    principale->addWidget(areaScorrimento);
    contenitoreCentrale=new QWidget();
    layout=new QVBoxLayout(contenitoreCentrale);
    layout->addStretch();
    areaScorrimento->setWidget(contenitoreCentrale);
    areaScorrimento->setWidgetResizable(true);
}
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
    for (modello::Attivita* a:vec)
    {
        QPushButton* bottoneTest=new QPushButton(a->getTitle());
        layout->addWidget(bottoneTest);
    }
    layout->addStretch();
}
}
