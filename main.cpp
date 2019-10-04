#include "mainwindow.h"

#include <QApplication>
#include <QTranslator>
#include <QDebug>

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(resttimeqt);

    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(QCoreApplication::applicationDirPath() + "/../images/resttime-qt.png"));

    // Load translations
    QString locale = QLocale::system().name();
    QTranslator translator;
    translator.load(QCoreApplication::applicationDirPath() + "/../languages/resttime-qt_" + locale + ".qm");
    translator.translate("MainWindow", "English");
    a.installTranslator(&translator);
    //

    MainWindow w;
    w.show();

    return a.exec();
}
