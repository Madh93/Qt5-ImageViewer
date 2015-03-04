#ifndef IMAGEN_HPP
#define IMAGEN_HPP

#include <QPixmap>
#include <QFile>
#include <QFileInfo>


class Imagen {

    private:

        QPixmap pixmap;
        QFileInfo *info;

    public:

        Imagen(QString ruta);
        ~Imagen();

        void load(QString ruta);
        void save(QString ruta);

        QPixmap pixmapObject();
        QString path();         // /home/migue/Escritorio/foto.jpg
        QString name();         // foto.jpg
        QString baseName();     // foto
        QString extension();    // .jpg
        QString directory();    // /home/migue/Escritorio/

        int width();
        int height();
};

#endif // IMAGEN_HPP
