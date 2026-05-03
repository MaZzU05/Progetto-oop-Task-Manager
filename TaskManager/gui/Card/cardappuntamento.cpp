#include "cardappuntamento.h"
namespace gui
{
namespace card
{

CardAppuntamento::CardAppuntamento(QWidget* parent): AbstractCardEdit(parent)
{
    setup();
    connectSegnali();

}

void CardAppuntamento::setup()
{
    //uniformo lo stile dei bottoni
    this->setStyleSheet("QPushButton { background-color: transparent; padding: 5px; border: 1px solid grey; border-radius: 10px; } QPushButton:hover { background-color: lightblue; } QPushButton:pressed { background-color: #e0e0e0; border: 1px solid #b0b0b0; }");
    contenitore=new QWidget(this);
    layoutPrincipale=new QVBoxLayout();
    QHBoxLayout* layoutLuogo=new QHBoxLayout();
    labelLuogo=new QLabel("Luogo: ", this);
    layoutLuogo->addWidget(labelLuogo);
    inserisciLuogo=new QLineEdit(this);
    inserisciLuogo->setPlaceholderText("Inserisci luogo");
    layoutLuogo->addWidget(inserisciLuogo);
    layoutPrincipale->addLayout(layoutLuogo);
    QHBoxLayout* layoutInPresenza=new QHBoxLayout();
    labelInPresenza=new QLabel("Modalita appuntamento: ", this);
    layoutInPresenza->addWidget(labelInPresenza);
    //provo con anche il testo nella QGroupBox poi valuto
    groupModalita=new QGroupBox("Modalita Appuntamento: ", this);
    QHBoxLayout* layoutModalita=new QHBoxLayout(groupModalita);
    radPresenza=new QRadioButton("In presenza", this);
    radPresenza->setChecked(true); //selezione di default
    layoutModalita->addWidget(radPresenza);
    radOnline=new QRadioButton("Online", this);
    layoutModalita->addWidget(radOnline);
    layoutInPresenza->addLayout(layoutModalita);
    layoutPrincipale->addLayout(layoutInPresenza);
    QHBoxLayout* layoutPartecipanti=new QHBoxLayout();
    labelPartecipanti=new QLabel("Partecipanti: ", this);
    layoutPartecipanti->addWidget(labelPartecipanti);
    QVBoxLayout* layoutPartecipantiInterno=new QVBoxLayout();
    QHBoxLayout* layoutPartTools=new QHBoxLayout();
    inserisciPartecipante=new QLineEdit(this);
    inserisciPartecipante->setPlaceholderText("inserisci partecipante, formato mail@entita.dominio, i formati diversi non verranno salvati alla fine");
    layoutPartTools->addWidget(inserisciPartecipante);
    bottoneAggiungiPartecipante=new QPushButton("Aggiungi", this);
    layoutPartTools->addWidget(bottoneAggiungiPartecipante);
    bottoneTogliPartecipante=new QPushButton("Rimuovi", this);
    layoutPartTools->addWidget(bottoneTogliPartecipante);
    layoutPartecipantiInterno->addLayout(layoutPartTools);
    listaPartecipanti=new QListWidget(this);
    layoutPartecipantiInterno->addWidget(listaPartecipanti);
    layoutPartecipanti->addLayout(layoutPartecipantiInterno);
    layoutPrincipale->addLayout(layoutPartecipanti);
    contenitore->setLayout(layoutPrincipale);
    addWidget(contenitore);
}
void CardAppuntamento::connectSegnali()
{
    //seguo lo stesso schema usato nella base
    connect(bottoneTogliPartecipante, &QPushButton::clicked, this, [this](){
        int riga=listaPartecipanti->currentRow(); //restituisce l'indice di riga selezionata
        //controllo che sia selezionata
        if (riga!=-1)
            delete listaPartecipanti->takeItem(riga); //elimino l'elemento estratto
    });
    connect(bottoneAggiungiPartecipante, &QPushButton::clicked, this, [this](){
        //controllo che contenga almeno la @, il resto del controllo avviene nel gestore
        if(!inserisciPartecipante->text().isEmpty()&&inserisciPartecipante->text().contains("@"))
        {
            bool check=true;
            for(int i=0; i<listaPartecipanti->count()&&check; i++)
            {
                check=(listaPartecipanti->item(i)->text().trimmed().toLower()!=inserisciPartecipante->text().trimmed().toLower()); //aggiunto toLower per renderlo case insensitive
            }
            if(check)
            {
                listaPartecipanti->addItem(inserisciPartecipante->text());
            }

        }
    });
}
modello::Appuntamento* CardAppuntamento::generaAttivita(unsigned int id)
{
    modello::Appuntamento* nuovoAppuntamento=new modello::Appuntamento(getTitle(), id, getNote(), QDateTime(getDate(), getTime()), inserisciLuogo->text(), getDurata(), radPresenza->isChecked(), isComplete(), getPriorita());
    std::vector<QString> vecPartecipanti;
    for(int i=0; i<listaPartecipanti->count(); i++)
        vecPartecipanti.push_back(listaPartecipanti->item(i)->text());
    for(const QString& partecipante:vecPartecipanti)
        nuovoAppuntamento->addPartecipante(partecipante);
    return nuovoAppuntamento;
}

void CardAppuntamento::popola(const modello::Appuntamento* a)
{
    preparaBase(a);
    inserisciLuogo->setText(a->getLuogo());
    if(a->isInPresenza())
    {
        radPresenza->setChecked(true);
        radOnline->setChecked(false);
    }
    else
    {
        radPresenza->setChecked(false);
        radOnline->setChecked(true);
    }
    std::vector<QString> vecPartecipanti=a->getAllPartecipanti();
    for(const QString& partecipante:vecPartecipanti)
        listaPartecipanti->addItem(partecipante);

}

}}
