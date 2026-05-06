#include "cardscadenza.h"
namespace gui{
namespace card{
CardScadenza::CardScadenza(QWidget* parent): AbstractCardEdit(parent)
{
    setup();
    connectSegnali();
}
void CardScadenza::setup()
{
    nascondiDurata();
    contenitore=new QWidget(this);
    layoutPrincipale=new QVBoxLayout();
    QHBoxLayout* layoutPreavviso=new QHBoxLayout();
    layoutPreavviso->setAlignment(Qt::AlignLeft);
    labelPreavviso=new QLabel("Inserisci giorrni preavviso: ", this);
    layoutPreavviso->addWidget(labelPreavviso);
    selezionaPreavviso=new QSpinBox(this);
    selezionaPreavviso->setMinimum(0);
    selezionaPreavviso->setMaximum(30); //al piu' un mese di preavviso
    layoutPreavviso->addWidget(selezionaPreavviso);
    layoutPrincipale->addLayout(layoutPreavviso);
    QHBoxLayout* layoutToDo=new QHBoxLayout();
    layoutToDo->setAlignment(Qt::AlignLeft);
    labelToDoList=new QLabel("Inserisci le task da completare: ", this);
    layoutToDo->addWidget(labelToDoList);
    QVBoxLayout* layoutToDoInterno=new QVBoxLayout();
    QHBoxLayout* layoutToDoTools=new QHBoxLayout();
    inserisciTask=new QLineEdit(this);
    inserisciTask->setPlaceholderText("Inserisci task da completare");
    layoutToDoTools->addWidget(inserisciTask);
    bottoneAggiungiTask=new QPushButton("Aggiungi", this);
    layoutToDoTools->addWidget(bottoneAggiungiTask);
    bottoneTogliTask=new QPushButton("Rimuovi", this);
    layoutToDoTools->addWidget(bottoneTogliTask);
    layoutToDoInterno->addLayout(layoutToDoTools);
    listaTask=new QListWidget(this);
    layoutToDoInterno->addWidget(listaTask);
    layoutToDo->addLayout(layoutToDoInterno);
    layoutPrincipale->addLayout(layoutToDo);
    contenitore->setLayout(layoutPrincipale);
    addWidget(contenitore);
}

void CardScadenza::connectSegnali()
{
    connect(bottoneTogliTask, &QPushButton::clicked, this, [this](){
        int riga=listaTask->currentRow(); //restituisce l'indice di riga selezionata
        //controllo che sia selezionata
        if (riga!=-1)
            delete listaTask->takeItem(riga); //elimino l'elemento estratto
    });
    connect(bottoneAggiungiTask, &QPushButton::clicked, this, [this](){
        if(!inserisciTask->text().isEmpty())
        {
            bool check=true;
            for(int i=0; i<listaTask->count()&&check; i++)
            {
                check=(listaTask->item(i)->text().trimmed().toLower()!=inserisciTask->text().trimmed().toLower()); //aggiunto toLower per renderlo case insensitive
            }
            if(check)
            {
                listaTask->addItem(inserisciTask->text());
            }

        }
    });
}

modello::Scadenza* CardScadenza::generaAttivita(unsigned int id, QDateTime dataCreazione)
{
    modello::Scadenza* nuovaScadenza=new modello::Scadenza(getTitle(), id, getNote(), QDateTime(getDate(), getTime()), selezionaPreavviso->value(), getDurata(),isComplete(), getPriorita());
    nuovaScadenza->changeDataCreazione(dataCreazione);
    std::vector<QString> vecTag=getTag();
    for(const QString& tag:vecTag)
        nuovaScadenza->addTag(tag);
    std::vector<QString> vecTask;
    for(int i=0; i<listaTask->count(); i++)
        vecTask.push_back(listaTask->item(i)->text());
    for(const QString& task:vecTask)
        nuovaScadenza->addPassaggio(task);
    if(!taskGiaPresenti.empty())
    {
        for(const std::pair<QString, bool>& sottoTask:taskGiaPresenti)
            nuovaScadenza->setPassaggioCompletato(sottoTask.first, sottoTask.second);//se non piu' presenti non fa nulla
    }
    return nuovaScadenza;
}

void CardScadenza::popola(const modello::Scadenza* s)
{
    preparaBase(s);
    selezionaPreavviso->setValue(s->getGiorniPreavviso());
    taskGiaPresenti=s->getAllSottoTask();
    for(const std::pair<QString, bool>& sottoTask:taskGiaPresenti)
        listaTask->addItem(sottoTask.first);


}

QString CardScadenza::validaSelezioni()
{
    //non ha bisogno di validazioni ulteriori
    return validazioneBase();
}

}}
