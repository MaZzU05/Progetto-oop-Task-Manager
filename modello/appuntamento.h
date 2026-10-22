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
    bool inPresenza;
    std::vector<QString> partecipanti;
public:
    Appuntamento(const QString& title,
                 const unsigned int id,
                 const QString& note,
                 const QDateTime& dataFine,
                 const QString& luogo,
                 const unsigned int durata,
                 bool inPresenza,
                 bool complete=false,
                 Priority priorita=Priority::bassa);
    Appuntamento* clone() const override;
    const QString& getLuogo() const;
    void setLuogo(const QString&);
    bool isInPresenza() const;
    void setPresenza(bool);
    bool addPartecipante(const QString&);
    void removePartecipante(const QString&);
    std::vector<QString> getAllPartecipanti() const;
    void accept(ActivityVisitorInterface* visitor) override;
    void accept(ConstActivityVisitorInterface* visitor) const override;
    bool isUrgente() const override;
};
}
#endif // APPUNTAMENTO_H
