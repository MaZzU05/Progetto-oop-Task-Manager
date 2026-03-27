#ifndef ATTIVITA_H
#define ATTIVITA_H
#include<QString>
#include<QDateTime>
#include<QDate>
#include<QTime>
#include<vector>
#include"activityvisitorinterface.h"
#include"constactivityvisitorinterface.h"
namespace modello
{
enum class  Priority {bassa, media, alta};
class Attivita
{
private:
    QString title;
    unsigned int id;
    QString note;
    bool complete;
    std::vector<QString> tag;
    QDateTime dataCreazione;
    QDateTime dataFine;
    unsigned int durata; //spostata nella classe base, e cambiato il tipo da QTime ad unsigned int considerandolo per i minuti, effettivamente QTime era abbastanza ambiguo e sbagliato
    Priority priorita;
public:
    Attivita(const QString& title,
             const unsigned int id,
             const QString& note,
             const QDateTime& dataFine,
             const unsigned int durata,
             bool complete=false,
             Priority priorita=Priority::bassa);
    virtual ~Attivita()=default;
    virtual Attivita* clone() const=0;
    const QString& getTitle() const;
    void setTitle(const QString& tit);
    unsigned int getID() const;
    const QString& getNote() const;
    void setNote(const QString& nota);
    const std::vector<QString>& getAllTag() const;
    void addTag(const QString& t);
    bool tagIsIn(const QString& t) const; //verifica tag presente o meno
    Priority getPriority() const;
    void changePriority(Priority nuova);
    bool isComplete() const;
    void setComplete(bool flag=true); //flagga attivita
    void changeDate(const QDate&);
    void changeTime(const QTime&);
    const QDateTime& getDate() const;
    const QDateTime& getDataCreazione() const;
    //spostate nella classe base per chiare motivazioni logiche
    unsigned int getDurata() const;
    void setDurata(const unsigned int d);
    virtual bool avvieneInData(const QDate&) const; //aggiunto per gestire problema della attivita ricorrente in sport
    virtual void accept(ActivityVisitorInterface* visitor)=0;
    virtual void accept(ConstActivityVisitorInterface* visitor) const=0;
    virtual bool isUrgente() const =0; //avra' un comportamento polimorfo in base alla specializzazione di attivita, ricordati dipensarle

};
}
#endif // ATTIVITA_H
