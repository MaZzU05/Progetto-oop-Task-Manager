#include "cardesame.h"
namespace gui {namespace card{
CardEsame::CardEsame(QWidget* parent): AbstractCardEdit(parent)
{
    setup();
    connectSegnali();
}

void CardEsame::setup()
{
    //uniformo lo stile dei bottoni
    this->setStyleSheet("QPushButton { background-color: transparent; padding: 5px; border: 1px solid grey; border-radius: 10px; } QPushButton:hover { background-color: lightblue; } QPushButton:pressed { background-color: #e0e0e0; border: 1px solid #b0b0b0; }");
    contenitore=new QWidget(this);
    layoutPrincipale=new QVBoxLayout();
    QHBoxLayout* layoutCfu = new QHBoxLayout();
    labelCFU=new QLabel("CFU: ", this);
    layoutCfu->addWidget(labelCFU);
    selezionaCFU=new QSpinBox(this);
    selezionaCFU->setMinimum(1);
    selezionaCFU->setMaximum(24);
    layoutCfu->addWidget(selezionaCFU);
    layoutPrincipale->addLayout(layoutCfu);
    QHBoxLayout* layoutVoto=new QHBoxLayout();
    labelVoto=new QLabel("Voto: (31 per lode)", this);
    layoutVoto->addWidget(labelVoto);
    selezionaVoto=new QSpinBox(this);
    selezionaVoto->setMinimum(0);
    selezionaVoto->setMaximum(31); //senza mettere una casella per flaggare la lode, metto 31, poi la gestiro' nella creazione
    layoutVoto->addWidget(selezionaVoto);
    layoutPrincipale->addLayout(layoutVoto);
    QHBoxLayout* layoutSede=new QHBoxLayout();
    labelSede=new QLabel("Sede: ", this);
    layoutSede->addWidget(labelSede);
    inserisciSede=new QLineEdit(this);
    inserisciSede->setPlaceholderText("inserisci sede");
    layoutSede->addWidget(inserisciSede);
    layoutPrincipale->addLayout(layoutSede);
    QHBoxLayout* layoutProfessori=new QHBoxLayout();
    labelProfessori=new QLabel("Professori: ", this);
    layoutProfessori->addWidget(labelProfessori);
    QVBoxLayout* layoutProfessoriInterno=new QVBoxLayout();
    QHBoxLayout* layoutProfTools=new QHBoxLayout();
    inserisciProfessore=new QLineEdit(this);
    inserisciProfessore->setPlaceholderText("inserisci professore");
    layoutProfTools->addWidget(inserisciProfessore);
    bottoneAggiungiProfessore=new QPushButton("Aggiungi", this);
    layoutProfTools->addWidget(bottoneAggiungiProfessore);
    bottoneTogliProfessore=new QPushButton("Rimuovi", this);
    layoutProfTools->addWidget(bottoneTogliProfessore);
    layoutProfessoriInterno->addLayout(layoutProfTools);
    listaProfessori=new QListWidget(this);
    layoutProfessoriInterno->addWidget(listaProfessori);
    layoutProfessori->addLayout(layoutProfessoriInterno);
    layoutPrincipale->addLayout(layoutProfessori);
    contenitore->setLayout(layoutPrincipale);
    addWidget(contenitore);
}

void CardEsame::connectSegnali()
{
    //seguo lo stesso schema usato nella base
    connect(bottoneTogliProfessore, &QPushButton::clicked, this, [this](){
        /*QListWidgetItem* elementoSelezionato=listaProfessori->currentItem();
        delete elementoSelezionato;*/
        int riga=listaProfessori->currentRow(); //restituisce l'indice di riga selezionata
        //controllo che sia selezionata
        if (riga!=-1)
            delete listaProfessori->takeItem(riga); //elimino l'elemento estratto
    });
    connect(bottoneAggiungiProfessore, &QPushButton::clicked, this, [this](){
        if(!inserisciProfessore->text().isEmpty())
            {
            bool check=true;
            for(int i=0; i<listaProfessori->count()&&check; i++)
            {
                check=(listaProfessori->item(i)->text().trimmed().toLower()!=inserisciProfessore->text().trimmed().toLower()); //aggiunto toLower per renderlo case insensitive
            }
            if(check)
            {
                listaProfessori->addItem(inserisciProfessore->text());
            }

        }
    });
}

modello::Esame* CardEsame::generaAttivita(unsigned int id)
{
    modello::Esame* nuovoEsame=new modello::Esame(getTitle(), id, getNote(), inserisciSede->text(), selezionaCFU->value(), QDateTime(getDate(), getTime()), getDurata(), isComplete(), getPriorita());
    std::vector<QString> vecTag=getTag();
    for(const QString& tag:vecTag) nuovoEsame->addTag(tag);
    std::vector<QString> vecProf;
    for(int i=0; i<listaProfessori->count(); i++) vecProf.push_back(listaProfessori->item(i)->text());
    for(const QString& prof:vecProf) nuovoEsame->addProfessor(prof);
    nuovoEsame->setVoto(selezionaVoto->value()!=31 ? selezionaVoto->value(): 30); //da impedire in fase di creazione di settare un voto se data ancora da avvenire
    if(selezionaVoto->value()==31)
        nuovoEsame->modifyLode(true);
    return nuovoEsame;
}

void CardEsame::popola(const modello::Esame* e)
{
    preparaBase(e);
    selezionaCFU->setValue(e->getCFU());
    selezionaVoto->setValue(e->getVoto());
    inserisciSede->setText(e->getSede());
    std::vector<QString> vecProf=e->getAllProf();
    for(const QString& prof:vecProf) listaProfessori->addItem(prof);

}
}}
