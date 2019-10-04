#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void timerTimeout();
    void pararCronometro(QString modo);
    void on_pbIniciarCuentaAtras_clicked();
    void on_pbPararCuentaAtras_clicked();
    void on_sbDecenasHoras_valueChanged(int arg1);
    void activaDesactivaBotones();
    void on_sbUnidadesHoras_valueChanged(int arg1);
    void on_sbDecenasMinutos_valueChanged(int arg1);
    void on_sbUnidadesMinutos_valueChanged(int arg1);
    void on_sbDecenasSegundos_valueChanged(int arg1);
    void on_sbUnidadesSegundos_valueChanged(int arg1);

private:
    Ui::MainWindow *ui;
    QTimer *myTimer;
    int timerCount;
    int unidadesSegundosGuardados;
    int decenasSegundosGuardados;
    int unidadesMinutosGuardados;
    int decenasMinutosGuardados;
    int unidadesHorasGuardados;
    int decenasHorasGuardados;
};
#endif // MAINWINDOW_H
