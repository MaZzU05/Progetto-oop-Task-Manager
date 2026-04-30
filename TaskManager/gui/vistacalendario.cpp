#include "vistacalendario.h"
#include<QDate>
#include<QLabel>
#include<QTextCharFormat>
#include<QPushButton>
namespace gui
{
VistaCalendario::VistaCalendario(QWidget* parent): AbstractVistaAttivita(parent)
{
    setup();
    connectSegnali();
}

/*
 *  QVBoxLayout* layoutPrincipale;
    QCalendarWidget* calendario;
    QScrollArea* AreaScorrimento;
    QWidget* contenitoreCentrale;
    //creo un layout composito di 7 layout verticali per le attività settimanali
    QHBoxLayout* layoutSettimana;
    std::vector<QVBoxLayout*> vecLayoutSettimana;
    std::vector<modello::Attivita*> vecAttivita;
 */
void VistaCalendario::setup()
{
    layoutPrincipale=new QVBoxLayout(this);
    calendario=new QCalendarWidget(this);
    calendario->setMinimumDate(QDate(2005, 04, 20));
    calendario->setFirstDayOfWeek(Qt::Monday); //serve per impostare lunedi come primo giorno della settimana, di default mi partiva da domenica
    calendario->setGridVisible(true); //mostra i giorni a griglia
    calendario->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader); //disabilita la barra a sinistra, che mostrava il numero di settimana dell'anno, che mi sembrava inutile
    calendario->setSelectedDate(QDate::currentDate());//imposto che di default seleziona la giornata odierna
    layoutPrincipale->addWidget(calendario);
    AreaScorrimento=new QScrollArea(this);
    contenitoreCentrale=new QWidget(this);
    layoutSettimana=new QHBoxLayout(contenitoreCentrale);
    AreaScorrimento->setWidget(contenitoreCentrale);
    for(unsigned int i=0; i<7; i++)
    {
        QVBoxLayout* giornoSett=new QVBoxLayout();
        giornoSett->setAlignment(Qt::AlignTop|Qt::AlignCenter);
        vecLayoutSettimana.push_back(giornoSett);
        QLabel* giorno=new QLabel();
        giorno->setStyleSheet("color: #7e7f76; font-weight:bold;");
        switch(i){
            case 0:
                giorno->setText("Lunedì");
                giornoSett->addWidget(giorno);
            break;
            case 1:
                giorno->setText("Martedi");
                giornoSett->addWidget(giorno);
                break;
            case 2:
                giorno->setText("Mercoledì");
                giornoSett->addWidget(giorno);
                break;
            case 3:
                giorno->setText("Giovedì");
                giornoSett->addWidget(giorno);
                break;
            case 4:
                giorno->setText("Venerdì");
                giornoSett->addWidget(giorno);
                break;
            case 5:
                giorno->setText("Sabato");
                giornoSett->addWidget(giorno);
                break;
            case 6:
                giorno->setText("Domenica");
                giornoSett->addWidget(giorno);
                break;
        }
        layoutSettimana->addLayout(giornoSett);
    }
    layoutPrincipale->addWidget(AreaScorrimento);
    AreaScorrimento->setWidgetResizable(true);
}

void VistaCalendario::connectSegnali()
{
    connect(calendario, &QCalendarWidget::selectionChanged, this, [=]()
            {
            QDate nuova=calendario->selectedDate();
        costruisciSettimana(nuova);
    });
    connect(calendario, &QCalendarWidget::currentPageChanged, this, [=](int anno, int mese){
        decoloraGiorni(mese, anno); //cancello eventuali colorazioni precedenti
        coloraGiorni(mese, anno);
    });
}

/*    bool inRange=dataInizio.daysTo(giorno)>=0&&giorno.daysTo(getDate().date())>=0;
    if(inRange&&isGiornoAllenamento(static_cast<Qt::DayOfWeek>(giorno.dayOfWeek()))) return true; */
void VistaCalendario::popolaAttivita(const std::vector<modello::Attivita*>& vec)
{
    vecAttivita=vec;
    //essendo che lo sport e' l'unica attivita' ricorrente, fare un visitor in questo caso mi sembrava un esagerazione, ho optato per un metodo che in base al mese
    //e all'anno corrente visualizzato nel calendario, rendendola "atea", scorre tutti i giorni, e colora le date sfruttando il metodo polimorfo avvieneInData che ho scritto per attivita
    //questo se implementassi nuove attivita ricorrenti si adatterebbe comunque, inoltre anche computazionalmente e' piu' efficiente dato che ciclo al piu' 31 giorni ogni volta
    decoloraGiorni(calendario->monthShown(), calendario->yearShown()); //gli shown danno il mese e l'anno attualmente visualizzato nel calendario
    coloraGiorni(calendario->monthShown(), calendario->yearShown()); //analogo a sopra
    costruisciSettimana(QDate::currentDate());//per popolare gia' alla creazione


}
void VistaCalendario::coloraGiorni(int mese, int anno)
{
    //coloro le caselle dei giorni nelle quali vi e' almeno una attivita'
    QTextCharFormat format;
    format.setBackground(QColor("lightblue")); //colore sfondo
    format.setForeground(Qt::white); //colore testo
    format.setFontWeight(QFont::Bold); //mette il testo in grassetto
    for(int i=1; i<=QDate(anno, mese, 1).daysInMonth(); i++)
    {
        for(auto it=vecAttivita.begin(); it!=vecAttivita.end(); it++)
        {
           QDate dataAttuale(anno, mese, i);
            if((*it)->avvieneInData(dataAttuale))
              {calendario->setDateTextFormat(dataAttuale, format);
                it=vecAttivita.end();
                it--;//per uscire dal ciclo, una volta colorato, non ha senso continuare a testare le altre attivita
              }
        }
    }
}
void VistaCalendario::decoloraGiorni(int mese, int anno)
{
    for(int i=1; i<=QDate(anno, mese, 1).daysInMonth(); i++)
    {
        //per cancellare le parti colorate, semplicemente vi passo il costruttore di default del QTextCharFormat
        calendario->setDateTextFormat(QDate(anno, mese, i), QTextCharFormat());
    }
}

void VistaCalendario::costruisciSettimana(QDate giornoSelezionato)
{
    for(QVBoxLayout* lay:vecLayoutSettimana)
    {
        QLayoutItem* daEliminare;
        //parto dal secondo elemento a svuotare perche' il primo e' la qlabel del giorno, che deve rimanere
    while((daEliminare=lay->takeAt(1))!=nullptr)
    {QWidget* elementoInterno=daEliminare->widget();
        delete elementoInterno;
        delete daEliminare;
    }}
    //per disegnare la settimana devo partire dal lunedi', grazie a dayOfWeek so il numero da 1 a 7, mi muovo in base a quello
    QDate InizioSettimana=giornoSelezionato.addDays(-giornoSelezionato.dayOfWeek()+1);
    int i=0;
    for(auto it=vecLayoutSettimana.begin(); it!=vecLayoutSettimana.end(); it++)
    {
        QDate giornoCheck=InizioSettimana.addDays(i);
        for(modello::Attivita* a:vecAttivita)
        {
            if(a->avvieneInData(giornoCheck))
            {
                QPushButton* bottoneAttivita=new QPushButton(a->getTitle());
                bottoneAttivita->setStyleSheet("QPushButton { background-color: transparent; padding: 5px; border: 1px solid grey; border-radius: 10px; } QPushButton:hover { background-color: lightblue; } QPushButton:pressed { background-color: #e0e0e0; border: 1px solid #b0b0b0; }");
                //devo chiamare la connect qua, dato che e' una variabile creata dentro la funzione e connectSegnali non la puo' vedere, siccome devo passare l'attivita nel segnale, uso una lambda e faccio l'emit dentro
                connect(bottoneAttivita, &QPushButton::pressed, this, [this, a](){
                    //emit VistaCalendario::attivitaSelezionata(a);
                    Q_EMIT VistaCalendario::attivitaSelezionata(a);
                });
                (*it)->addWidget(bottoneAttivita);
            }

        }
        i++;
    }
}
}
