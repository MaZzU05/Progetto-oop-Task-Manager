#ifndef ATTIVITA_H
#define ATTIVITA_H
#include<QString>
#include<QDateTime>
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
    Priority priorita;
public:
    Attivita(const QString& title,
             const unsigned int id,
             const QString& note,
             bool complete=false,
             Priority priorita=Priority::bassa);
    virtual ~Attivita()=default;
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
    const QDateTime& getDataCreazione() const;
    virtual void accept(ActivityVisitorInterface* visitor)=0;
    virtual void accept(ConstActivityVisitorInterface* visitor) const=0;
    virtual bool isUrgente() const =0; //avra' un comportamento polimorfo in base alla specializzazione di attivita, ricordati dipensarle

};
}
#endif // ATTIVITA_H
