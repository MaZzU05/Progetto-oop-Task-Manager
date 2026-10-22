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
    //per "personalizzare lo sfondo" mi serve per mostrare le modifiche estetiche applicate alle card
    this->setAttribute(Qt::WA_StyledBackground, true);
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
    QHBoxLayout* layoutCambiaStato=new QHBoxLayout();
    layoutCambiaStato->setAlignment(Qt::AlignLeft);
    bottoneCambiaStato=new QPushButton("Cambia lo stato di completamento", this);
    layoutCambiaStato->addWidget(bottoneCambiaStato);
    layoutDettagli->addLayout(layoutCambiaStato);
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

void CardAttivita::popolaAttivita(modello::Attivita* a)
{
    attivitaRappresentata=a;
    titolo->setText("Titolo: "+a->getTitle());
    data_ora->setText("Data-ora: "+a->getDate().toString("ddd dd/MM/yyyy HH:mm")); //la stringa dentro il tostring serve per dare una formattazione visiva della data all'italiana
    //se non e' ancora passata l'attivita' non la rendo flaggabile come completata
    if(QDate::currentDate().daysTo(a->getDate().date())>0)
        nascondiBottoneCambiaStato();
    durata->setText("Durata: "+QString::number(a->getDurata())+" minuti");
    if(a->isComplete()) Completata->setText("Stato: Completata");
    else Completata->setText("Stato: Non completata");
    dataCreazione->setText("Data creazione: "+a->getDataCreazione().toString("ddd dd/MM/yyyy HH:mm"));
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
    //se uso int genera warning, uso size_t, che e' il tipo corretto
    for(size_t i=0; i<tagVec.size(); i++)
    {
        testoTag+=tagVec[i];
        if(i<tagVec.size()-1) testoTag+=", ";
    }
    tag->setText(testoTag);
    tag->setWordWrap(true); //va automaticamenta a capo se sono troppi
    note->setText("Note: "+a->getNote());
    note->setWordWrap(true);
    connect(bottoneCambiaStato, &QPushButton::clicked, this, [this]() {
        attivitaRappresentata->setComplete(!attivitaRappresentata->isComplete());
        // aggiorno la label per coerenza visiva immediata
        if(attivitaRappresentata->isComplete())
            Completata->setText("Stato: Completata");
        else
            Completata->setText("Stato: Non completata");
        // aggiorno anche l'urgenza dato che dipende dallo stato di completamento
        if(attivitaRappresentata->isUrgente())
            urgente->setText("Urgente");
        else
            urgente->setText("Non urgente");
    });

}
void CardAttivita::nascondiBottoneCambiaStato()
{
    bottoneCambiaStato->setVisible(false);
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
