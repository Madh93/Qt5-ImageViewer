#include "imagen.hpp"


Imagen::Imagen(QString ruta) {

    pixmap.load(ruta);
    QFile file(ruta);
    info = new QFileInfo(file.fileName());
}


Imagen::~Imagen() {

    if (info) {
        delete info;
        info = NULL;
    }
}


void Imagen::load(QString ruta) {

    pixmap.load(ruta);
    QFile file(ruta);
    if (info) {
        delete info;
        info = new QFileInfo(file.fileName());
    }
}


void Imagen::save(QString ruta) { pixmap.save(ruta,0,60); }

QPixmap Imagen::pixmapObject(){ return pixmap; }

QString Imagen::path() { return info->absoluteFilePath(); }

QString Imagen::name() { return info->fileName(); }

QString Imagen::baseName() { return info->baseName(); }

QString Imagen::extension() { return "." + info->suffix(); }

QString Imagen::directory() { return info->path() + "/"; }

int Imagen::width() { return pixmap.width(); }

int Imagen::height() { return pixmap.height(); }
