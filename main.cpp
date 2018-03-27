#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>
#include <QLibraryInfo>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator Translator;
    QString path = QLibraryInfo::location(QLibraryInfo::TranslationsPath);
    if (Translator.load("qt_ru", path))
        QCoreApplication::installTranslator(&Translator);

    MainWindow w;
    w.setWindowTitle("Программа анализа движения");
    w.setWindowState(Qt::WindowMaximized);
    w.show();

    return a.exec();
}
