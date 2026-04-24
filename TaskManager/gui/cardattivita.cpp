#include "cardattivita.h"
#include<vector>
namespace gui
{
/*
    QWidget* Principile;
    QWidget* dettagliWidget;
    bool espansa;
    QLabel* titolo;
    QLabel* data_ora;
    QLabel* durata;
    QLabel* Completata;
    QLabel* tag;*/
CardAttivita::CardAttivita(QWidget *parent): QWidget(parent), espansa(false)
{
    setup();
}

void CardAttivita::setup()
{
    layoutPrincipale=new QVBoxLayout(this);
    layoutAlto=new QHBoxLayout();
    layoutAlto->setAlignment(Qt::AlignLeft);
    titolo=new QLabel(this);
    layoutAlto->addWidget(titolo);
    data_ora=new QLabel(this);
    layoutAlto->addWidget(data_ora);
    durata=new QLabel(this);
    layoutAlto->addWidget(durata);
    Completata=new QLabel(this);
    layoutAlto->addWidget(Completata);
    layoutPrincipale->addLayout(layoutAlto);
    dettagliWidget=new QWidget();
    layoutDettagli=new QVBoxLayout(dettagliWidget);
    priorita=new QLabel(this);
    layoutDettagli->addWidget(priorita);
    tag=new QLabel("Tag:",this);
    layoutDettagli->addWidget(tag);
    listaTag=new QListWidget(this);
    listaTag->setSelectionMode(QAbstractItemView::NoSelection);//necessario per disabilitare la selezione mmultipla
    layoutDettagli->addWidget(listaTag);
    QHBoxLayout* layoutNote=new QHBoxLayout();
    note=new QLabel("Note: ", this);
    layoutNote->addWidget(note);
    noteEffettive=new QLabel(this);
    layoutNote->addWidget(noteEffettive);
    layoutDettagli->addLayout(layoutNote);
    dettagliWidget->setVisible(false);//inizialmente i dettagli sono nascosti
    layoutPrincipale->addWidget(dettagliWidget);
}

void CardAttivita::popolaAttivita(const modello::Attivita* a)
{
    titolo->setText("Titolo: "+a->getTitle());
    data_ora->setText("Data-ora: "+a->getDate().toString());
    durata->setText("Durata: "+QString::number(a->getDurata())+" minuti");
    std::vector<QString> tagVec=a->getAllTag();
    for(const QString& t:tagVec) listaTag->addItem(t);
    noteEffettive->setText(a->getNote());
}

void CardAttivita::setSelezionata(bool stato)
{
    espansa=stato;
    dettagliWidget->setVisible(espansa);
}
void CardAttivita::mousePressEvent(QMouseEvent *event)
{
    setSelezionata(!espansa); //negandola, se era espansa la riduco, e viceversa
    dettagliWidget->setVisible(espansa);

    //emit selezionata(this);
    Q_EMIT selezionata(this, espansa);

    QWidget::mousePressEvent(event);
}
void CardAttivita::addWidget(QWidget* w)
{
    layoutDettagli->addWidget(w);
}
}
