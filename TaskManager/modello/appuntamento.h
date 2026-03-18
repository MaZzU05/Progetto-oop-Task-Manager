#ifndef APPUNTAMENTO_H
#define APPUNTAMENTO_H
#include"attivita.h"
#include<QString>
#include<QTime>
#include<vector>
namespace modello
{
class Appuntamento: public Attivita
{
private:
    QString luogo;
    QTime durata;
    bool inPresenza;
    std::vector<QString> partecipanti;
public:
    Appuntamento(const QString& title,
                 const unsigned int id,
                 const QString& note,
                 const QDateTime& dataFine,
                 const QString& luogo,
                 const QTime& durata,
                 bool inPresenza,
                 bool complete=false,
                 Priority priorita=Priority::bassa);
    const QString& getLuogo() const;
    void setLuogo(const QString&);
    const QTime& getDurata() const;
    void setDurata(const QTime&);
    bool isInPresenza() const;
    void setPresenza(bool);
    bool addPartecipante(const QString&);
    void removePartecipante(const QString&);
    void accept(ActivityVisitorInterface* visitor) override;
    void accept(ConstActivityVisitorInterface* visitor) const override;
    bool isUrgente() const override;
};
}
#endif // APPUNTAMENTO_H
