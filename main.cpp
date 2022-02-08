#include "principal.h"

#include <QApplication>
#include <QTranslator>
#include <QInputDialog>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator traducion;
    QString idioma =  QLocale::system().name();
    int idiom=idioma.indexOf('_');
    idioma=idioma.mid(0,idiom);

    if (idioma == "de"){
        traducion.load(":/mipaint_al.qm");

    }
    if (idioma == "zh"){
        traducion.load(":/mipaint_ch.qm");

    }
    if (idioma == "ja"){
        traducion.load(":/mipaint_jp.qm");

    }
    // Si es diferente de español, se instala la traducción en TODA la aplicación
    if (idioma != "es"){
        a.installTranslator(&traducion);
    }

    Principal w;
    w.show();
    return a.exec();
}
