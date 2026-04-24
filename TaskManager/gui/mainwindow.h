#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include "barralateralewidget.h"
#include"vistaelenco.h"
namespace gui
{
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent=nullptr);

private:
    BarraLateraleWidget* barraLaterale;
    VistaElenco* centrale;
};
}
#endif // MAINWINDOW_H
