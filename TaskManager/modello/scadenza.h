#ifndef SCADENZA_H
#define SCADENZA_H
#include"attivita.h"
#include<QString>
#include<vector>
namespace modello
{
class Scadenza:public Attivita
{private:
    class SottoTask
    {
        friend class Scadenza;
    private:
        QString descrizione;
        bool completa;
    public:
        SottoTask(const QString& descrizione, bool completa=false): descrizione(descrizione), completa(completa) {}
    };
    unsigned int giorniPreavviso;
    std::vector<SottoTask> todoList;
public:
    Scadenza(const QString& title,
             const unsigned int id,
             const QString& note,
             const QDateTime& dataFine,
             unsigned int giorniPreavviso,
             bool complete=false,
             Priority priorita=Priority::bassa);
    unsigned int getGiorniPreavviso() const;
    void setGiorniPreavviso(unsigned int);
    void addPassaggio(const QString&);
    void setPassaggioCompletato(unsigned int index, bool completato);
    unsigned int getPassaggiTotali() const;
    unsigned int getPassaggiCompletati() const;
    void accept(ActivityVisitorInterface* visitor) override;
    void accept(ConstActivityVisitorInterface* visitor) const override;
    bool isUrgente() const override;

};
}
#endif // SCADENZA_H
