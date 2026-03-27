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
    //durata impostata a 0 di default dato che una scadenza non ha durata
    Scadenza(const QString& title,
             const unsigned int id,
             const QString& note,
             const QDateTime& dataFine,
             const unsigned int giorniPreavviso,
             bool complete=false,
             Priority priorita=Priority::bassa);
    Scadenza* clone() const override;
    unsigned int getGiorniPreavviso() const;
    void setGiorniPreavviso(unsigned int);
    void addPassaggio(const QString&);
    void setPassaggioCompletato(const QString& tag_Elemento, bool completato);
    unsigned int getNumPassaggiTotali() const;
    unsigned int getNumPassaggiCompletati() const;
    std::vector<QString> getPassaggiCompletati() const;
    std::vector<QString> getPassaggiNonCompletati() const;
    void accept(ActivityVisitorInterface* visitor) override;
    void accept(ConstActivityVisitorInterface* visitor) const override;
    bool isUrgente() const override;

};
}
#endif // SCADENZA_H
