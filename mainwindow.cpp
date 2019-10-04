#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTimer>

#include <QStyle>
#include <QScreen>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Center window
    QScreen *screen = QGuiApplication::primaryScreen();
    this->setGeometry(
      QStyle::alignedRect(
        Qt::LeftToRight,
        Qt::AlignCenter,
        this->size(),
        //qApp->desktop()->availableGeometry()
        screen->availableGeometry()
      )
    );
    //

    myTimer = new QTimer(this);
    myTimer->setInterval(1000);
    timerCount = 0;

    connect(myTimer, SIGNAL(timeout()), this, SLOT(timerTimeout()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::timerTimeout()
{
    --timerCount;

    int hDecenas = timerCount / 36000;
    int hUnidades = (timerCount - (hDecenas * 36000) ) / 3600;

    int mDecenas = ( timerCount - (hDecenas * 36000) - (hUnidades * 3600) ) / 600;
    int mUnidades = ( timerCount - (hDecenas * 36000) - (hUnidades * 3600) - (mDecenas * 600) ) / 60;

    int sDecenas = ( timerCount - (hDecenas * 36000) - (hUnidades * 3600) - (mDecenas * 600) - (mUnidades * 60) ) / 10;
    int sUnidades = ( timerCount - (hDecenas * 36000) - (hUnidades * 3600) - (mDecenas * 600) - (mUnidades * 60) - (sDecenas * 10) );

    ui->sbDecenasHoras->setValue(hDecenas);
    ui->sbUnidadesHoras->setValue(hUnidades);

    ui->sbDecenasMinutos->setValue(mDecenas);
    ui->sbUnidadesMinutos->setValue(mUnidades);

    ui->sbDecenasSegundos->setValue(sDecenas);
    ui->sbUnidadesSegundos->setValue(sUnidades);

    this->setWindowTitle( QString::number(hDecenas) + QString::number(hUnidades) + ":" +
                          QString::number(mDecenas) + QString::number(mUnidades) + ":" +
                          QString::number(sDecenas) + QString::number(sUnidades) +
                          " (" + QString::number(timerCount) + " " + tr("seconds") + ")" );

    if (timerCount <= 0)
        pararCronometro("ENDED");
}

void MainWindow::pararCronometro(QString modo)
{
    myTimer->stop();
    ui->pbIniciarCuentaAtras->setEnabled(true);
    ui->sbDecenasHoras->setEnabled(true);
    ui->sbUnidadesHoras->setEnabled(true);
    ui->sbDecenasMinutos->setEnabled(true);
    ui->sbUnidadesMinutos->setEnabled(true);
    ui->sbDecenasSegundos->setEnabled(true);
    ui->sbUnidadesSegundos->setEnabled(true);
    ui->sbDecenasHoras->setButtonSymbols(QSpinBox::UpDownArrows);
    ui->sbUnidadesHoras->setButtonSymbols(QSpinBox::UpDownArrows);
    ui->sbDecenasMinutos->setButtonSymbols(QSpinBox::UpDownArrows);
    ui->sbUnidadesMinutos->setButtonSymbols(QSpinBox::UpDownArrows);
    ui->sbDecenasSegundos->setButtonSymbols(QSpinBox::UpDownArrows);
    ui->sbUnidadesSegundos->setButtonSymbols(QSpinBox::UpDownArrows);

    if (modo == "ENDED") {
        this->setWindowTitle(tr("It's time to rest!"));
    } else if (modo == "STOPPED") {
        this->setWindowTitle(tr("STOPPED"));
    }

    qApp->alert(this, 0);

    if (ui->cbRestaurarAlTerminar->checkState())
        this->setWindowState((this->windowState() & ~Qt::WindowMinimized) | Qt::WindowActive);

    ui->sbUnidadesSegundos->setValue(unidadesSegundosGuardados);
    ui->sbDecenasSegundos->setValue(decenasSegundosGuardados);
    ui->sbUnidadesMinutos->setValue(unidadesMinutosGuardados);
    ui->sbDecenasMinutos->setValue(decenasMinutosGuardados);
    ui->sbUnidadesHoras->setValue(unidadesHorasGuardados);
    ui->sbDecenasHoras->setValue(decenasHorasGuardados);
}

void MainWindow::on_pbIniciarCuentaAtras_clicked()
{
    if (ui->cbMinimizarAlIniciar->checkState())
        this->setWindowState(Qt::WindowMinimized);

    timerCount = ui->sbUnidadesSegundos->value() +
                 (ui->sbDecenasSegundos->value() * 10) +
                 (ui->sbUnidadesMinutos->value() * 60) +
                 (ui->sbDecenasMinutos->value() * 600) +
                 (ui->sbUnidadesHoras->value() * 3600) +
                 (ui->sbDecenasHoras->value() * 36000);

    unidadesSegundosGuardados = ui->sbUnidadesSegundos->value();
    decenasSegundosGuardados = ui->sbDecenasSegundos->value();
    unidadesMinutosGuardados = ui->sbUnidadesMinutos->value();
    decenasMinutosGuardados = ui->sbDecenasMinutos->value();
    unidadesHorasGuardados = ui->sbUnidadesHoras->value();
    decenasHorasGuardados = ui->sbDecenasHoras->value();

    if (!myTimer->isActive() && (timerCount > 0)) {
      ui->pbIniciarCuentaAtras->setEnabled(false);
      ui->sbDecenasHoras->setEnabled(false);
      ui->sbDecenasHoras->setButtonSymbols(QSpinBox::NoButtons);
      ui->sbUnidadesHoras->setEnabled(false);
      ui->sbUnidadesHoras->setButtonSymbols(QSpinBox::NoButtons);
      ui->sbDecenasMinutos->setEnabled(false);
      ui->sbDecenasMinutos->setButtonSymbols(QSpinBox::NoButtons);
      ui->sbUnidadesMinutos->setEnabled(false);
      ui->sbUnidadesMinutos->setButtonSymbols(QSpinBox::NoButtons);
      ui->sbDecenasSegundos->setEnabled(false);
      ui->sbDecenasSegundos->setButtonSymbols(QSpinBox::NoButtons);
      ui->sbUnidadesSegundos->setEnabled(false);
      ui->sbUnidadesSegundos->setButtonSymbols(QSpinBox::NoButtons);

      this->setWindowTitle( QString::number(decenasHorasGuardados) + QString::number(unidadesHorasGuardados) + ":" +
                            QString::number(decenasMinutosGuardados) + QString::number(unidadesMinutosGuardados) + ":" +
                            QString::number(decenasSegundosGuardados) + QString::number(unidadesSegundosGuardados) +
                            " (" + QString::number(timerCount) + " " + tr("seconds") + ")" );

      myTimer->start();
    }
}

void MainWindow::on_pbPararCuentaAtras_clicked()
{
    if (myTimer->isActive())
        pararCronometro("STOPPED");
}

void MainWindow::on_sbDecenasHoras_valueChanged(int arg1)
{
    if (!myTimer->isActive()) {
        if (arg1 > 0) {
            ui->pbIniciarCuentaAtras->setEnabled(true);
            ui->pbPararCuentaAtras->setEnabled(true);
        } else {
            activaDesactivaBotones();
        }
    }
}

void MainWindow::activaDesactivaBotones()
{
    if (ui->sbDecenasHoras->value() != 0 ||
        ui->sbUnidadesHoras->value() != 0 ||
        ui->sbDecenasMinutos->value() != 0 ||
        ui->sbUnidadesMinutos->value() != 0 ||
        ui->sbDecenasSegundos->value() != 0 ||
        ui->sbUnidadesSegundos->value() != 0 )
    {
        ui->pbIniciarCuentaAtras->setEnabled(true);
        ui->pbPararCuentaAtras->setEnabled(true);
    } else {
        ui->pbIniciarCuentaAtras->setEnabled(false);
        ui->pbPararCuentaAtras->setEnabled(false);
    }
}

void MainWindow::on_sbUnidadesHoras_valueChanged(int arg1)
{
    if (!myTimer->isActive()) {
        if (arg1 > 0) {
            ui->pbIniciarCuentaAtras->setEnabled(true);
            ui->pbPararCuentaAtras->setEnabled(true);
        } else {
            activaDesactivaBotones();
        }
    }
}

void MainWindow::on_sbDecenasMinutos_valueChanged(int arg1)
{
    if (!myTimer->isActive()) {
        if (arg1 > 0) {
            ui->pbIniciarCuentaAtras->setEnabled(true);
            ui->pbPararCuentaAtras->setEnabled(true);
        } else {
            activaDesactivaBotones();
        }
    }
}

void MainWindow::on_sbUnidadesMinutos_valueChanged(int arg1)
{
    if (!myTimer->isActive())
    {
        if (arg1 > 0) {
            ui->pbIniciarCuentaAtras->setEnabled(true);
            ui->pbPararCuentaAtras->setEnabled(true);
        } else {
            activaDesactivaBotones();
        }
    }
}

void MainWindow::on_sbDecenasSegundos_valueChanged(int arg1)
{
    if (!myTimer->isActive()) {
        if (arg1 > 0) {
            ui->pbIniciarCuentaAtras->setEnabled(true);
            ui->pbPararCuentaAtras->setEnabled(true);
        } else {
            activaDesactivaBotones();
        }
    }
}

void MainWindow::on_sbUnidadesSegundos_valueChanged(int arg1)
{
    if (!myTimer->isActive()) {
        if (arg1 > 0) {
            ui->pbIniciarCuentaAtras->setEnabled(true);
            ui->pbPararCuentaAtras->setEnabled(true);
        } else {
            activaDesactivaBotones();
        }
    }
}
