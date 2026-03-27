#ifndef SPORT_H
#define SPORT_H
#include"attivita.h"
#include<QDate>
#include<QDateTime>
#include<QTime>
#include<QString>
#include<vector>
namespace modello
{
class Sport:public Attivita
{
private:
    QString luogo;
    //Qt::DayOfWeek tipo enumeraativo incluso in Qt per gestire giorni della settimana incluso in QDate e che vi si può interfacciare
    QDate dataInizio; //lascio come ora di inizio quella nel QDateTime dataFine della base, qui sufficente QDate per intervallo
    std::vector<Qt::DayOfWeek> giorni_sport;
public:
    Sport(const QString& title,
          const unsigned int id,
          const QString& note,
          const QDateTime& dataFine,
          const unsigned int durata,
          const QDate& dataInizio,
          const QString& luogo,
          bool complete=false,
          Priority priorita=Priority::bassa);
    Sport* clone() const override;
    const QString& getLuogo() const;
    void setLuogo(const QString& l);
    const QTime getOraAllenamento() const;
    void setGiornoSettimana(Qt::DayOfWeek d);
    void removeGiornoSettimana(Qt::DayOfWeek giornoDaRimuovere);
    bool isGiornoAllenamento(Qt::DayOfWeek d) const;
    void accept(ActivityVisitorInterface* visitor) override;
    void accept(ConstActivityVisitorInterface* visitor) const override;
    bool isUrgente() const override;
    bool avvieneInData(const QDate&) const override;
};
}
#endif // SPORT_H
