#include "cardactivityvisitor.h"
#include "../modello/esame.h"
#include"../modello/appuntamento.h"
#include"../modello/scadenza.h"
#include"../modello/sport.h"
#include<QVBoxLayout>
#include<QListWidget>
#include<vector>
namespace gui
{
void CardActivityVisitor::visit(const modello::Esame* e)
{
    widget=new CardAttivita();
    widget->popolaAttivita(e);
    QWidget* widgetEsame=new QWidget();
    QVBoxLayout* layoutEsame=new QVBoxLayout(widgetEsame);
    QLabel* labelCFU=new QLabel("CFU: "+QString::number(e->getCFU()));
    layoutEsame->addWidget(labelCFU);
    QLabel* labelVoto=new QLabel();
    if(e->getVoto()==0)
    {
        labelVoto->setText("Voto: non ancora sostenuto");
    }
    else if(e->hasLode())
    {
        labelVoto->setText("Voto: "+QString::number(e->getVoto())+" con lode");
    }
    else
    {
        labelVoto->setText("Voto: "+QString::number(e->getVoto()));
    }
    layoutEsame->addWidget(labelVoto);
    QLabel* labelSede=new QLabel("Sede: "+e->getSede());
    layoutEsame->addWidget(labelSede);
    QListWidget* listaProfessori=new QListWidget();
    listaProfessori->setSelectionMode(QAbstractItemView::NoSelection);
    std::vector<QString> professoriVec=e->getAllProf();
    for(const QString& p:professoriVec) listaProfessori->addItem(p);
    layoutEsame->addWidget(listaProfessori);
    widget->addWidget(widgetEsame);

}

void CardActivityVisitor::visit(const modello::Scadenza* s)
{
    widget=new CardAttivita();
    widget->popolaAttivita(s);
    QWidget* widgeScadenza=new QWidget();
    QVBoxLayout* layoutScadenza=new QVBoxLayout(widgeScadenza);
}

void CardActivityVisitor::visit(const modello::Appuntamento* i)
{
    widget=new CardAttivita();
    widget->popolaAttivita(i);
    QWidget* widgetAppuntamento=new QWidget();
    QVBoxLayout* layoutAppuntamento=new QVBoxLayout(widgetAppuntamento);
    QHBoxLayout* layoutLuogo=new QHBoxLayout();
    QLabel* luogo=new QLabel("Luogo: "+i->getLuogo());
    layoutLuogo->addWidget(luogo);
    QLabel* inPresenza=new QLabel();
    if(i->isInPresenza()) inPresenza->setText("In presenza");
    else inPresenza->setText("On-Line");
    layoutLuogo->addWidget(inPresenza);
    layoutAppuntamento->addLayout(layoutLuogo);
    std::vector<QString> partecipantiVec=i->getAllPartecipanti();
    QListWidget* listaPartecipanti=new QListWidget();
    listaPartecipanti->setSelectionMode(QAbstractItemView::NoSelection);
    for(const QString& p:partecipantiVec) listaPartecipanti->addItem(p);
    layoutAppuntamento->addWidget(listaPartecipanti);
    widget->addWidget(widgetAppuntamento);


}

void CardActivityVisitor::visit(const modello::Sport* s)
{
    widget=new CardAttivita();
    widget->popolaAttivita(s);
}

CardAttivita* CardActivityVisitor::getWidget()
{
    return widget;
}
}
