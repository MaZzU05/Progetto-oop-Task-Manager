#include "vistaelenco.h"
#include "cardactivityvisitor.h"
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
    this->setStyleSheet("background-color: #f5f5f5;"); //grigio chiaro
    QVBoxLayout* principale=new QVBoxLayout(this);
    principale->setContentsMargins(10,10,10,10);
    areaScorrimento=new QScrollArea(this);
    //per rimuovere il bordo nero
    areaScorrimento->setFrameShape(QFrame::NoFrame);
    areaScorrimento->setWidgetResizable(true);
    areaScorrimento->setStyleSheet("background-color: transparent;"); //mettendo lo sfondo trasparente cerco un effetto piu' elegante
    principale->addWidget(areaScorrimento);
    contenitoreCentrale=new QWidget();
    layout=new QVBoxLayout(contenitoreCentrale);
    contenitoreCentrale->setStyleSheet("background-color: transparent;");
    layout->setSpacing(15); //imposto lo spazio tra una "card' e la successiva
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
    cardEspansaAttualmente=nullptr;
    for (modello::Attivita* a:vec)
    {
        CardActivityVisitor visitor;
        a->accept(&visitor);
        CardAttivita* nuovaCard=visitor.getWidget();
        layout->addWidget(nuovaCard);
        connect(nuovaCard, &CardAttivita::selezionata, this, [this, a, nuovaCard](CardAttivita* c, bool espansa){
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
                }
             }

        });
    }
    layout->addStretch();
}
}
