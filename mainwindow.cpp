#include "mainwindow.hpp"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {

    ui->setupUi(this);

    scene = new QGraphicsScene;
    imagen = NULL;
    tamano = new QLabel;
    zoom = new QLabel;

    scene->setBackgroundBrush(QColor::fromRgb(224,224,224));
    ui->graphicsView->setScene(scene);
    ui->statusBar->addPermanentWidget(tamano);
    ui->statusBar->addWidget(zoom);

    //Señales y slots de los botones
    connect(ui->abrirButton, SIGNAL(clicked()), this, SLOT(on_actionAbrir_triggered()));
    connect(ui->cerrarButton, SIGNAL(clicked()), this, SLOT(on_actionCerrar_triggered()));
    connect(ui->guardarButton, SIGNAL(clicked()), this, SLOT(on_actionGuardar_como_triggered()));
    connect(ui->zoomInButton, SIGNAL(clicked()), this, SLOT(on_actionAmpliar_triggered()));
    connect(ui->zoomOutButton, SIGNAL(clicked()), this, SLOT(on_actionReducir_triggered()));
    connect(ui->zoomZeroButton, SIGNAL(clicked()), this, SLOT(on_actionNormal_triggered()));
}


MainWindow::~MainWindow() {

    delete ui;

    if (scene) {
        delete scene;
        scene = NULL;
    }

    if (imagen) {
        delete imagen;
        imagen = NULL;
    }

    if (tamano) {
        delete tamano;
        tamano = NULL;
    }

    if (zoom) {
        delete zoom;
        zoom = NULL;
    }
}


void MainWindow::limpiarImagen() {

    if (scene) {
        delete scene;
        scene = new QGraphicsScene;
        scene->setBackgroundBrush(QColor::fromRgb(224,224,224));
        ui->graphicsView->setScene(scene);
    }

    if (imagen) {
        delete imagen;
        imagen = NULL;
    }

    if (tamano) {
        delete tamano;
        tamano = new QLabel;
        ui->statusBar->addPermanentWidget(tamano);
    }

    if (zoom) {
        delete zoom;
        zoom = new QLabel;
        ui->statusBar->addWidget(zoom);
    }

    this->setWindowTitle(WINDOW_TITLE);
    ui->graphicsView->resetTransform();
    ui->graphicsView->setFactor(0);
    activarFuncionalidades(false);
}


void MainWindow::activarFuncionalidades(bool cond) {

    ui->actionGuardar_como->setEnabled(cond);
    ui->actionCerrar->setEnabled(cond);
    ui->actionAbrir_con->setEnabled(cond);
    ui->actionAbrir_directorio->setEnabled(cond);
    ui->actionAbrir_terminal->setEnabled(cond);
    ui->actionRenombrar->setEnabled(cond);
    ui->actionEliminar->setEnabled(cond);
    ui->menuZoom->setEnabled(cond);
    ui->menuRotar->setEnabled(cond);
    ui->actionRestablecer->setEnabled(cond);
    ui->cerrarButton->setEnabled(cond);
    ui->guardarButton->setEnabled(cond);
    ui->zoomInButton->setEnabled(cond);
    ui->zoomOutButton->setEnabled(cond);
    ui->zoomZeroButton->setEnabled(cond);
}


void MainWindow::ajustarZoom() {

    int num = 100*pow(1.2,ui->graphicsView->getFactor());
    QString porcentaje = QString::number(num);
    zoom->setText(porcentaje + "%");
}


void MainWindow::on_actionAbrir_triggered(QString rutaImagen) {

    if (rutaImagen.isEmpty()) {

         //Abrir ruta y seleccionar tipo de imagen
        rutaImagen = QFileDialog::getOpenFileName(this, tr("Abrir imagen"), QString(),
            tr("Todos los archivos (*);;Todas las imágenes (*.bpm *.gif *.jpg *.jpeg *.png *.ppm *.xbm *.xpm);;Imagen BPM (*.bpm);;Imagen GIF (*.gif);;Imagen JPG (*.jpg);;Imagen JPEG (*.jpeg);;Imagen PNG (*.png);;Imagen PPM (*.ppm);;Imagen XBM (*.xbm);;Imagen XPM (*.xpm);;"));
    }

    if (!rutaImagen.isEmpty()) {

        QFile file(rutaImagen);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::critical(this, tr(WINDOW_CRITICAL), tr("No se puede abrir la imagen."));
            return;
        }

        //Borrar imagen anterior
        limpiarImagen();

        //Cargar imagen
        imagen = new Imagen(rutaImagen);
        scene->addPixmap(imagen->pixmapObject());

        //Ajustes
        this->setWindowTitle(imagen->name() + " - Visor de Imágenes");
        activarFuncionalidades(true);
        tamano->setText(QString::number(imagen->width()) + " x " + QString::number(imagen->height()));
        if (qMax(imagen->width(),imagen->height()) > qMin(ui->graphicsView->width(),ui->graphicsView->height()))
            on_actionAjustar_triggered();
        else
            ajustarZoom();
    }
}


void MainWindow::on_actionGuardar_como_triggered() {

    //Seleccionar ruta nueva
    QString rutaNueva = QFileDialog::getSaveFileName(this, tr("Guardar imagen"), QString(),
            tr("Todos los archivos (*);;Imagen BPM (*.bpm);;Imagen GIF (*.gif);;Imagen JPG (*.jpg);;Imagen JPEG (*.jpeg);;Imagen PNG (*.png);;Imagen PPM (*.ppm);;Imagen XBM (*.xbm);;Imagen XPM (*.xpm);;"));

    if (!rutaNueva.isEmpty()) {

        QFile file(rutaNueva);
        if (!file.open(QIODevice::WriteOnly)) {
            QMessageBox::critical(this, tr(WINDOW_CRITICAL), tr("No se puede guardar la imagen."));
            return;
        }

        //Guardar imagen en la nueva ruta
        imagen->save(rutaNueva);
    }
}


void MainWindow::on_actionCerrar_triggered() {

    limpiarImagen();
}


void MainWindow::on_actionSalir_triggered() {

    qApp->quit();
}


void MainWindow::on_actionAbrir_con_triggered() {

    QInputDialog inputAbrir;
    QString aplicacion, rutaAplicacion;
    bool okButton;

    aplicacion = inputAbrir.getText(NULL ,"Abrir imagen con...","Introduzca el nombre de la aplicación:",
                                          QLineEdit::Normal,"Ej: gimp", &okButton);

    rutaAplicacion = "/usr/bin/" + aplicacion;

    //Comprobar si existe la aplicación y ejecutar
    if (okButton && !aplicacion.isEmpty()){

        if (QFile::exists(rutaAplicacion) || QFile::exists(aplicacion)) {
            QProcess *proceso = new QProcess(this);
            proceso->start(aplicacion, QStringList() << imagen->path());
        }
        else
            QMessageBox::warning(this, tr(WINDOW_WARNING), tr("No se encuentra la aplicacion."));
    }
}


void MainWindow::on_actionAbrir_directorio_triggered() {

    QProcess *proceso = new QProcess(this);
    proceso->start("xdg-open", QStringList() << imagen->directory());
}


void MainWindow::on_actionAbrir_terminal_triggered() {

    QProcess *proceso = new QProcess(this);
    proceso->setWorkingDirectory(imagen->directory());
    proceso->start("x-terminal-emulator", QStringList() << imagen->directory());
}


void MainWindow::on_actionRenombrar_triggered() {

    QInputDialog inputRenombrar;
    QString nuevoNombre, nuevaRuta;
    bool okButton;

    nuevoNombre = inputRenombrar.getText(NULL ,"Renombrar imagen","Introduzca un nuevo nombre:",
                                          QLineEdit::Normal,imagen->baseName(), &okButton);

    if (okButton && !nuevoNombre.isEmpty()){

        nuevaRuta = imagen->directory() + nuevoNombre + imagen->extension();

        //Si no existe un archivo con el mismo nombre sobreescribir
        if (!QFile::exists(nuevaRuta)) {

            QFile::rename(imagen->path(),nuevaRuta);
            imagen->load(nuevaRuta);
            this->setWindowTitle(imagen->name() + " - Visor de Imágenes");
        }

        else {

            QMessageBox yaExiste;
            yaExiste.setWindowTitle(WINDOW_WARNING);
            yaExiste.setText("Ya existe una imagen con el mismo nombre.");
            yaExiste.setInformativeText("¿Desea sobreescribir la imagen?");
            yaExiste.setStandardButtons(QMessageBox::Save | QMessageBox::Cancel);
            yaExiste.setButtonText(QMessageBox::Save, "Renombrar");
            yaExiste.setButtonText(QMessageBox::Cancel, "Cancelar");
            yaExiste.setDefaultButton(QMessageBox::Cancel);

            //Si se desea sobreescribir un archivo con el mismo nombre
            if (yaExiste.exec() == QMessageBox::Save) {

                QFile fileNuevo(nuevaRuta);
                if (!fileNuevo.open(QIODevice::WriteOnly)) {
                    QMessageBox::critical(this, tr(WINDOW_CRITICAL), tr("No se puede renombrar la imagen."));
                    return;
                }

                QFile::remove(nuevaRuta);
                QFile::rename(imagen->path(),nuevaRuta);
                imagen->load(nuevaRuta);
                this->setWindowTitle(imagen->name() + " - Visor de Imágenes");
            }
        }
    }
}


void MainWindow::on_actionEliminar_triggered() {

    QMessageBox avisoEliminar;
    avisoEliminar.setWindowTitle(WINDOW_WARNING);
    avisoEliminar.setText("Está a punto de eliminar la imagen del disco.");
    avisoEliminar.setInformativeText("¿Desea eliminar la imagen?");
    avisoEliminar.setStandardButtons(QMessageBox::Save | QMessageBox::Cancel);
    avisoEliminar.setButtonText(QMessageBox::Save, "Eliminar");
    avisoEliminar.setButtonText(QMessageBox::Cancel, "Cancelar");
    avisoEliminar.setDefaultButton(QMessageBox::Cancel);

    //Eliminar del disco si se da el visto bueno
    if (avisoEliminar.exec() == QMessageBox::Save) {

        QFile::remove(imagen->path());
        limpiarImagen();
    }
}


void MainWindow::on_actionAmpliar_triggered() {

    ui->graphicsView->scale(1.2,1.2);
    ui->graphicsView->setFactor(1);
    ajustarZoom();
}


void MainWindow::on_actionReducir_triggered() {

    ui->graphicsView->scale(1/1.2,1/1.2);
    ui->graphicsView->setFactor(-1);
    ajustarZoom();
}


void MainWindow::on_actionAjustar_triggered() {

    int height = imagen->height();
    int width = imagen->width();
    int max_height = ui->graphicsView->height();
    int max_width = ui->graphicsView->width();
    int size,max_size,fact=0;
    double val=0;

    //Buscar medida maxima y minima de imagen y ventana
    size = qMin(width,height);
    max_size = qMin(max_width,max_height);

    //Dependiendo de si es menor o mayor que la ventana
    if (size < max_size) {
        while ((size*val) < max_size)
            val = pow(1.2,fact++);
        val = pow(1.2,fact-2);
        ui->graphicsView->setFactor(fact-2);
    }

    else {
        val = 1;
        while ((size*val) > max_size)
            val = pow(1.2,fact--);
        val = pow(1.2,fact+1);
        ui->graphicsView->setFactor(fact+1);
    }

    ui->graphicsView->scale(val,val);
    ajustarZoom();
}


void MainWindow::on_actionNormal_triggered() {

    qreal val = pow(1.2, -ui->graphicsView->getFactor());
    ui->graphicsView->scale(val,val);
    ui->graphicsView->setFactor(0);
    ajustarZoom();
}


void MainWindow::on_actionRotarDerecha_triggered() {

    ui->graphicsView->rotate(90);
}


void MainWindow::on_actionRotarIzquierda_triggered() {

    ui->graphicsView->rotate(-90);
}


void MainWindow::on_actionRestablecer_triggered() {

    ui->graphicsView->resetTransform();
    ui->graphicsView->setFactor(0);
    ajustarZoom();
}


void MainWindow::on_actionPantalla_completa_toggled(bool cond) {

    if (cond)
        this->showFullScreen();
    else
        this->showMaximized();
}


void MainWindow::on_actionAyuda_triggered() {

    QMessageBox::warning(this, tr(WINDOW_WARNING), tr("La documentación no está disponible actualmente."));
}


void MainWindow::on_actionAcerca_de_triggered() {

    QMessageBox::about(this, tr(WINDOW_ABOUT), tr("     Visor de imágenes con Qt.\n\n Sistemas Operativos Avanzados."));
}
