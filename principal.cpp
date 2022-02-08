#include "principal.h"
#include "ui_principal.h"
#include <QImage>
#include <QPainter>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QDebug>
#include <QRectF>
#include <QInputDialog>
#include <QColorDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QMessageBox>
#include <QColorDialog>
#include <QColor>
#include <QInputDialog>


#define DEFAULT_ANCHO 3

Principal::Principal(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Principal)
{
    ui->setupUi(this);
    // Instanciando la imagen (creando)
    mImagen = new QImage(this->size(),QImage::Format_ARGB32_Premultiplied);
    // Rellenar la imagen de color blanco
    mImagen->fill(Qt::white);
    // Instanciar el Painter a partir de la imagen
    mPainter = new QPainter(mImagen);
    mPainter->setRenderHint(QPainter::Antialiasing);
    // Inicializar otras variables
    mPuedeDibujar = true;
    mColor = Qt::black;
    mAncho = DEFAULT_ANCHO;
    mNumLineas = 0;
}

Principal::~Principal()
{
    delete ui;
    delete mPainter;
    delete mImagen;
}

void Principal::paintEvent(QPaintEvent *event)
{
    // Crear el painter de la ventana principal
    QPainter painter(this);
    // Dibujar la imagen
    painter.drawImage(0, 0, *mImagen);
    // Acepatr el evento
    event->accept();
}

void Principal::mousePressEvent(QMouseEvent *event)
{

    switch (menu) {
    case 'L':
        mInicial = event->pos();
            ui->statusbar->showMessage("Número de líneas: " + QString::number(++mNumLineas));
        break;
    case 'l':
        linea(event);
            ui->statusbar->showMessage("Número de líneas: " + QString::number(++mNumLineas));
        break;
    case 'r':
        rectangulo(event);
            ui->statusbar->showMessage("Número de líneas: " + QString::number(++mNumLineas*2));
        break;
    case 'c':
        circulo(event);
            ui->statusbar->showMessage("Número de líneas: " + QString::number(++mNumLineas/2));
        break;
    default:
        break;
    }

    mPuedeDibujar = !mPuedeDibujar;
}

void Principal::mouseMoveEvent(QMouseEvent *event)
{
    if(menu=='L')
    {
        mFinal = event->pos();
        QPen pincel;
        pincel.setWidth(mAncho);
        pincel.setColor(mColor);
        mPainter->setPen(pincel);
        mPainter->drawLine(mInicial,mFinal);
    }
    update();
    mInicial = mFinal;
}



void Principal::on_actionAncho_triggered()
{
    mAncho = QInputDialog::getInt(this,
                                  "Ancho del pincel",
                                  "Ingrese el ancho del pincel de dibujo",
                                  mAncho,
                                  1, 100);
}

void Principal::on_actionSalir_triggered()
{
    this->close();
}

void Principal::on_actionColor_triggered()
{
    mColor = QColorDialog::getColor(mColor,
                                    this,
                                    "Color del pincel");
}

void Principal::on_actionNuevo_triggered()
{
    mImagen->fill(Qt::white);
    mNumLineas = 0;
    update();
}

void Principal::on_actionGuardar_triggered()
{
    QString nombreArchivo = QFileDialog::getSaveFileName(this,
                                                         "Guardar imagen",
                                                         QString(),
                                                         "Imágenes (*.png)");
    if ( !nombreArchivo.isEmpty() ){
        if (mImagen->save(nombreArchivo))
            QMessageBox::information(this,
                                     "Guardar imagen",
                                     "Archivo almacenado en: " + nombreArchivo);
        else
            QMessageBox::warning(this,
                                 "Guardar imagen",
                                 "No se pudo almacenar la imagen.");
    }
}


QPoint Principal::inicial() const
{
    return mInicial;
}

void Principal::setInicial(QPoint newInicial)
{
    mInicial = newInicial;
}

QPoint Principal::final() const
{
    return mFinal;
}

void Principal::setFinal(QPoint newFinal)
{
    mFinal = newFinal;
}



void Principal::on_actionRect_nculos_triggered()
{

    menu='r';
}


void Principal::on_actionLineas_triggered()
{
    menu='l';
}


void Principal::on_actionLibre_triggered()
{
    menu='L';
}


void Principal::on_actionCircunferencias_triggered()
{
    menu='c';
}

void Principal::linea(QMouseEvent *event)
{
    if(mPuedeDibujar){
        mInicial = event->pos();
    }else{
        mFinal = event->pos();
        QPen pincel;
                pincel.setWidth(mAncho);
                 pincel.setColor(mColor);


                  mPainter->setPen(pincel);
             mPainter->drawLine(mInicial, mFinal);

        update();
    }
}

void Principal::rectangulo(QMouseEvent *event)
{
    if(mPuedeDibujar){
        mInicial = event->pos();
    }else{
        mFinal = event->pos();
        QPen pincel;
        pincel.setWidth(mAncho);
                 pincel.setColor(mColor);


                    mPainter->setPen(pincel);


                  QRect rectangulo(mInicial,mFinal);
                 mPainter->setPen(pincel);

                      mPainter->drawRect(rectangulo);
        update();
    }
}

void Principal::circulo(QMouseEvent *event)
{
    if(mPuedeDibujar){
        mInicial = event->pos();
    }else{
        mFinal = event->pos();
        QPen pincel;
            pincel.setWidth(mAncho);
             pincel.setColor(mColor);
        mPainter->setPen(pincel);


        QRect rectangulo(mInicial,mFinal);
             QPainter ellipsePainter(this);
                 ellipsePainter.drawEllipse(rectangulo);
                     mPainter->setPen(pincel);
                    mPainter->drawEllipse(rectangulo);
        update();
    }
}

