#include "cardsport.h"
namespace gui
{namespace card{

CardSport::CardSport(QWidget* parent): AbstractCardEdit(parent)
{
    setup();
}

void CardSport::setup()
{
    contenitore=new QWidget(this);
    layoutPrincipale=new QVBoxLayout();
    QHBoxLayout* layoutLuogo=new QHBoxLayout();
    layoutLuogo->setAlignment(Qt::AlignLeft);
    labelLuogo=new QLabel("Luogo: ", this);
    layoutLuogo->addWidget(labelLuogo);
    inserisciLuogo=new QLineEdit(this);
    inserisciLuogo->setPlaceholderText("inserisci luogo");
    layoutLuogo->addWidget(inserisciLuogo);
    layoutPrincipale->addLayout(layoutLuogo);
    QHBoxLayout* layoutDataInizio=new QHBoxLayout();
    layoutDataInizio->setAlignment(Qt::AlignLeft);
    labelDataInizio=new QLabel("Data inizio: ", this);
    layoutDataInizio->addWidget(labelDataInizio);
    selezionaDataInizio=new QDateEdit(this);
    selezionaDataInizio->setDate(QDate::currentDate());
    selezionaDataInizio->setCalendarPopup(true); //attiva la selezione a calendario
    layoutDataInizio->addWidget(selezionaDataInizio);
    layoutPrincipale->addLayout(layoutDataInizio);
    QHBoxLayout* layoutGiorniSport=new QHBoxLayout();
    layoutGiorniSport->setAlignment(Qt::AlignLeft);
    labelGiorniSport=new QLabel("Seleziona gioni ripetizione: ", this);
    layoutGiorniSport->addWidget(labelGiorniSport);
    listaGiorniSport=new QListWidget(this);
    listaGiorniSport->setSelectionMode(QAbstractItemView::MultiSelection);//abilito la selezione multipla
    listaGiorniSport->addItem("Lunedì");
    listaGiorniSport->addItem("Martedì");
    listaGiorniSport->addItem("Mercoledì");
    listaGiorniSport->addItem("Giovedì");
    listaGiorniSport->addItem("Venerdì");
    listaGiorniSport->addItem("Sabato");
    listaGiorniSport->addItem("Domenica");
    layoutGiorniSport->addWidget(listaGiorniSport);
    layoutPrincipale->addLayout(layoutGiorniSport);
    contenitore->setLayout(layoutPrincipale);
    addWidget(contenitore);
}

modello::Sport* CardSport::generaAttivita(unsigned int id, QDateTime dataCreazione)
{
    modello::Sport* nuovoSport=new modello::Sport(getTitle(), id, getNote(), QDateTime(getDate(), getTime()), getDurata(), selezionaDataInizio->date(), inserisciLuogo->text(), isComplete(), getPriorita());
    nuovoSport->changeDataCreazione(dataCreazione);
    std::vector<QString> vecTag=getTag();
    for(const QString& tag:vecTag)
        nuovoSport->addTag(tag);
    std::vector<Qt::DayOfWeek> vecGiorni;
    for(QListWidgetItem* selezionato:listaGiorniSport->selectedItems())
    {
        if(selezionato->text()=="Lunedì")
            vecGiorni.push_back(Qt::DayOfWeek::Monday);
        else if(selezionato->text()=="Martedì")
            vecGiorni.push_back(Qt::DayOfWeek::Tuesday);
        else if(selezionato->text()=="Mercoledì")
            vecGiorni.push_back(Qt::DayOfWeek::Wednesday);
        else if(selezionato->text()=="Giovedì")
            vecGiorni.push_back(Qt::DayOfWeek::Thursday);
        else if(selezionato->text()=="Venerdì")
            vecGiorni.push_back(Qt::DayOfWeek::Friday);
        else if(selezionato->text()=="Sabato")
            vecGiorni.push_back(Qt::DayOfWeek::Saturday);
        else
            vecGiorni.push_back(Qt::DayOfWeek::Sunday);
    }
    for(Qt::DayOfWeek giorno:vecGiorni)
        nuovoSport->setGiornoSettimana(giorno);
    return nuovoSport;
}

void CardSport::popola(const modello::Sport* s)
{
    preparaBase(s);
    inserisciLuogo->setText(s->getLuogo());
    selezionaDataInizio->setDate(s->getDataInizio());
    std::vector<Qt::DayOfWeek> vecGiorni=s->getAllGiorniSettimanali();
    listaGiorniSport->clearSelection(); //deseleziono tutto per sicurezza
    for(Qt::DayOfWeek giorno:vecGiorni)
    {
        QListWidgetItem* elemento=nullptr;
        switch(giorno)
        {
        case Qt::DayOfWeek::Monday:
            elemento=listaGiorniSport->item(0);
            break;
        case Qt::DayOfWeek::Tuesday:
            elemento=listaGiorniSport->item(1);
            break;
        case Qt::DayOfWeek::Wednesday:
            elemento=listaGiorniSport->item(2);
            break;
        case Qt::DayOfWeek::Thursday:
            elemento=listaGiorniSport->item(3);
            break;
        case Qt::DayOfWeek::Friday:
            elemento=listaGiorniSport->item(4);
            break;
        case Qt::DayOfWeek::Saturday:
            elemento=listaGiorniSport->item(5);
            break;
        case Qt::DayOfWeek::Sunday:
            elemento=listaGiorniSport->item(6);
            break;
        }
        if(elemento)
            elemento->setSelected(true);
    }
}

QString CardSport::validaSelezioni()
{
    if(!validazioneBase().isEmpty())
        return validazioneBase();
    //un attivita' sportiva non puo' iniziare dopo la fine
    if(selezionaDataInizio->date().daysTo(getDate())<0)
        return "Non può iniziare dopo la data di fine!";
    if(listaGiorniSport->selectedItems().empty())
        return "Devi selezionare almeno un giorno!";
    return "";
}
}}
