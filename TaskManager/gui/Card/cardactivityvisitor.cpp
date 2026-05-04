#include "cardactivityvisitor.h"
#include "../modello/esame.h"
#include"../modello/appuntamento.h"
#include"../modello/scadenza.h"
#include"../modello/sport.h"
#include<QVBoxLayout>
#include<QListWidget>
#include<QProgressBar>
#include<vector>
namespace gui
{
namespace card{
void CardActivityVisitor::visit(const modello::Esame* e)
{
    widget=new CardAttivita();
    widget->popolaAttivita(e);
    QWidget* widgetEsame=new QWidget();
    QVBoxLayout* layoutEsame=new QVBoxLayout(widgetEsame);
    QLabel* labelCFU=new QLabel("CFU: "+QString::number(e->getCFU()));
    layoutEsame->addWidget(labelCFU);
    QHBoxLayout* layoutVoto=new QHBoxLayout();
    layoutVoto->setAlignment(Qt::AlignLeft);
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
    layoutVoto->addWidget(labelVoto);
    QProgressBar* barraVoto=new QProgressBar();
    barraVoto->setStyleSheet("QProgressBar { border: 1px solid grey; border-radius: 5px; text-align: center; }"
                             "QProgressBar::chunk { background-color: #4CAF50; width: 10px; margin: 1px; }");
    barraVoto->setRange(0, 30);
    barraVoto->setValue(e->getVoto());
    barraVoto->setFormat("%v/%m");
    layoutVoto->addWidget(barraVoto);
    layoutEsame->addLayout(layoutVoto);
    QLabel* labelSede=new QLabel("Sede: "+e->getSede());
    layoutEsame->addWidget(labelSede);
    QHBoxLayout* layoutProfessori=new QHBoxLayout();
    layoutProfessori->setAlignment(Qt::AlignLeft);
    QLabel* labelProfessori=new QLabel("Professori: ");
    layoutProfessori->addWidget(labelProfessori);
    QListWidget* listaProfessori=new QListWidget();
    listaProfessori->setSelectionMode(QAbstractItemView::NoSelection);
    std::vector<QString> professoriVec=e->getAllProf();
    for(const QString& p:professoriVec) listaProfessori->addItem(p);
    layoutProfessori->addWidget(listaProfessori);
    layoutEsame->addLayout(layoutProfessori);
    widget->addWidget(widgetEsame);

}

void CardActivityVisitor::visit(const modello::Scadenza* s)
{
    widget=new CardAttivita();
    widget->popolaAttivita(s);
    QWidget* widgetScadenza=new QWidget();
    QVBoxLayout* layoutScadenza=new QVBoxLayout(widgetScadenza);
    QHBoxLayout* layoutPreavviso=new QHBoxLayout();
    layoutPreavviso->setAlignment(Qt::AlignLeft);
    QLabel* labelPreavviso= new QLabel("Stato preavviso: ");
    layoutPreavviso->addWidget(labelPreavviso);
    QProgressBar* barraGiorni=new QProgressBar();
    barraGiorni->setRange(0, s->getGiorniPreavviso());
    int giorniMancanti=QDate::currentDate().daysTo(s->getDate().date());
    //riempio la barra nel seguente modo: se i giorni mancanti superano il preavviso la lascio vuota, se sono <=0 vuol dire che e' gia' passata, la metto piena, altrimenti la riempio con valori intermedi
    if(giorniMancanti>static_cast<int>(s->getGiorniPreavviso())) barraGiorni->setValue(0);
    else if (giorniMancanti<=0) barraGiorni->setValue(s->getGiorniPreavviso());
    //non ho rischio di underflow dato i due controlli precedenti
    else barraGiorni->setValue(s->getGiorniPreavviso()-giorniMancanti);
    //%v stampa il valore attuale, %m il massimo dell'intervallo
    barraGiorni->setFormat("%v/%m giorni alla scadenza");
    layoutPreavviso->addWidget(barraGiorni);
    layoutScadenza->addLayout(layoutPreavviso);
    QLabel* labelSottoTask=new QLabel("Task: ");
    layoutScadenza->addWidget(labelSottoTask);
    std::vector<std::pair<QString, bool>> aux=s->getAllSottoTask();
    QListWidget* listaSottoTask=new QListWidget();
    for(const std::pair<QString, bool>& task:aux)
    {
        QListWidgetItem* sottoTask=new QListWidgetItem(task.first);
        //uso la itemFalg per renderlo cliccabile, userCheckable lo rende selezionabile e deselezionabile
        sottoTask->setFlags(sottoTask->flags()|Qt::ItemIsUserCheckable);
        if(task.second) sottoTask->setCheckState(Qt::Checked);
        else sottoTask->setCheckState(Qt::Unchecked);
        listaSottoTask->addItem(sottoTask);
    }
    layoutScadenza->addWidget(listaSottoTask);
    widget->addWidget(widgetScadenza);

}

void CardActivityVisitor::visit(const modello::Appuntamento* i)
{
    widget=new CardAttivita();
    widget->popolaAttivita(i);
    QWidget* widgetAppuntamento=new QWidget();
    QVBoxLayout* layoutAppuntamento=new QVBoxLayout(widgetAppuntamento);
    QHBoxLayout* layoutLuogo=new QHBoxLayout();
    QLabel* labelLuogo=new QLabel("Luogo: "+i->getLuogo());
    layoutLuogo->addWidget(labelLuogo);
    QLabel* labelInPresenza=new QLabel();
    if(i->isInPresenza()) labelInPresenza->setText("In presenza");
    else labelInPresenza->setText("On-Line");
    layoutLuogo->addWidget(labelInPresenza);
    layoutAppuntamento->addLayout(layoutLuogo);
    QHBoxLayout* layoutPartecipanti=new QHBoxLayout();
    layoutPartecipanti->setAlignment(Qt::AlignLeft);
    QLabel* labelPartecipanti=new QLabel("Partecipanti: ");
    layoutPartecipanti->addWidget(labelPartecipanti);
    std::vector<QString> partecipantiVec=i->getAllPartecipanti();
    QListWidget* listaPartecipanti=new QListWidget();
    listaPartecipanti->setSelectionMode(QAbstractItemView::NoSelection);
    for(const QString& p:partecipantiVec) listaPartecipanti->addItem(p);
    layoutPartecipanti->addWidget(listaPartecipanti);
    layoutAppuntamento->addLayout(layoutPartecipanti);
    widget->addWidget(widgetAppuntamento);


}

void CardActivityVisitor::visit(const modello::Sport* s)
{
    widget=new CardAttivita();
    widget->popolaAttivita(s);
    QWidget* widgetSport=new QWidget();
    QVBoxLayout* layoutSport = new QVBoxLayout(widgetSport);
    QLabel* labelDataInizio=new QLabel("Data inizio: "+s->getDataInizio().toString());
    layoutSport->addWidget(labelDataInizio);
    QLabel* labelOraAllenamento=new QLabel("Orario: "+s->getOraAllenamento().toString());
    layoutSport->addWidget(labelOraAllenamento);
    QLabel* labelGiorniRicorrenza=new QLabel("Si ripete ogni: ");
    layoutSport->addWidget(labelGiorniRicorrenza);
    QListWidget* listaGiorni=new QListWidget();
    listaGiorni->setSelectionMode(QAbstractItemView::NoSelection);
    std::vector<Qt::DayOfWeek> giorni=s->getAllGiorniSettimanali();
    for(Qt::DayOfWeek giorno:giorni) {
        switch(giorno) {
        case Qt::Monday:
            listaGiorni->addItem("Lunedì");
            break;
        case Qt::Tuesday:
            listaGiorni->addItem("Martedì");
            break;
        case Qt::Wednesday:
            listaGiorni->addItem("Mercoledì");
            break;
        case Qt::Thursday:
            listaGiorni->addItem("Giovedì");
            break;
        case Qt::Friday:
            listaGiorni->addItem("Venerdì");
            break;
        case Qt::Saturday:
            listaGiorni->addItem("Sabato");
            break;
        case Qt::Sunday:
            listaGiorni->addItem("Domenica");
            break;
        }
    }
    layoutSport->addWidget(listaGiorni);
    widget->addWidget(widgetSport);
}

CardAttivita* CardActivityVisitor::getWidget()
{
    return widget;
}
}}
