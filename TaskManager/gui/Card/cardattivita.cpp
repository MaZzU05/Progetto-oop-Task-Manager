#include "cardattivita.h"
#include<vector>
namespace gui
{
namespace card
{
CardAttivita::CardAttivita(QWidget *parent): QWidget(parent), espansa(false)
{
    setup();
}

void CardAttivita::setup()
{
    //per "personalizzare lo sfondo"
    this->setAttribute(Qt::WA_StyledBackground, true);

    //elemnti di stile css, il cazzo di tema scuro sminchia tutto, forzo i colori del testo
    this->setStyleSheet("gui--card--CardAttivita { "
                        "   background-color: white; "
                        "   border: 1px solid #e0e0e0; "
                        "   border-radius: 10px; "
                        "   margin: 5px; "
                        "}"
                        "gui--card--CardAttivita:hover { "
                        "   border: 1px solid #2196F3; " // Cambia bordo al passaggio del mouse (Blu)
                        "}"
                        "gui--card--CardAttivita QLabel {"
                        "   color: #333333;"
                        "}"
                        "gui--card--CardAttivita QListWidget {color: #333333; background-color: transparent; border: none; }"
        );
    layoutPrincipale=new QVBoxLayout(this);
    layoutPrincipale->setContentsMargins(15, 12, 15, 12); // Piu' respiro ai bordi
    layoutPrincipale->setSpacing(10); // Spazio tra titolo e dettagli
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
    dataCreazione=new QLabel(this);
    layoutDettagli->addWidget(dataCreazione);
    urgente=new QLabel(this);
    layoutDettagli->addWidget(urgente);
    priorita=new QLabel(this);
    layoutDettagli->addWidget(priorita);
    tag=new QLabel(this);
    layoutDettagli->addWidget(tag);
    note=new QLabel(this);
    layoutDettagli->addWidget(note);
    dettagliWidget->setVisible(false);//inizialmente i dettagli sono nascosti
    layoutPrincipale->addWidget(dettagliWidget);
}

void CardAttivita::popolaAttivita(const modello::Attivita* a)
{
    attivitaRappresentata=a;
    titolo->setText("Titolo: "+a->getTitle());
    // titolo->setStyleSheet("font-weight: bold; font-size: 14px; color: #333;");
    data_ora->setText("Data-ora: "+a->getDate().toString());
    durata->setText("Durata: "+QString::number(a->getDurata())+" minuti");
    if(a->isComplete()) Completata->setText("Stato: Completata");
    else Completata->setText("Stato: Non completata");
    dataCreazione->setText("Data creazione: "+a->getDataCreazione().toString());
    if(a->isUrgente())
        urgente->setText("Urgente");
    else
        urgente->setText("Non urgente");
    QString prior;
    if(a->getPriority()==modello::Priority::bassa) prior="bassa";
    else if(a->getPriority()==modello::Priority::media) prior="media";
    else prior="Alta";
    priorita->setText("Priorita': "+prior);
    std::vector<QString> tagVec=a->getAllTag();
    QString testoTag="Tag: ";
    for(int i=0; i<tagVec.size(); i++)
    {
        testoTag+=tagVec[i];
        if(i<tagVec.size()-1) testoTag+=", ";
    }
    tag->setText(testoTag);
    tag->setWordWrap(true); //va automaticamenta a capo se sono troppi
    note->setText("Note: "+a->getNote());
    note->setWordWrap(true);
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
}
