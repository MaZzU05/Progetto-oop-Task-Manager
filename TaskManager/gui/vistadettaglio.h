#ifndef VISTADETTAGLIO_H
#define VISTADETTAGLIO_H

#include <QWidget>
#include <QLabel>
#include<QVBoxLayout>
#include<QScrollArea>
namespace gui
{
class VistaDettaglio : public QWidget
{
    Q_OBJECT
public:
    VistaDettaglio(QWidget *parent = nullptr);
    void addWidget(QWidget* nuovaCard);
private:
    QScrollArea* areaScorrimento;
    QWidget* contenitoreCentrale;
    QVBoxLayout* layout;
    QVBoxLayout* layoutCentrale;
    void setup();
//signals:
Q_SIGNALS:
    void tornaIndietro();

};
}
#endif // VISTADETTAGLIO_H
