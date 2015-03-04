#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#define WINDOW_TITLE "Visor de imágenes"
#define WINDOW_CRITICAL "Error - Visor de imágenes"
#define WINDOW_WARNING "Aviso - Visor de imágenes"
#define WINDOW_ABOUT "Acerca de - Visor de imágenes"

#include <QMainWindow>
#include <QProcess>
#include <QFileDialog>
#include <QMessageBox>
#include <QInputDialog>
#include <QLabel>
#include "imagen.hpp"
#include "graphicsview.hpp"
#include <QDebug>


namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {

    Q_OBJECT

    private:

        Ui::MainWindow *ui;
        QGraphicsScene *scene;
        Imagen *imagen;
        QLabel *tamano, *zoom;

    private slots:

        //Archivo
        void on_actionAbrir_triggered(QString rutaImagen = "");
        void on_actionGuardar_como_triggered();
        void on_actionCerrar_triggered();
        void on_actionSalir_triggered();

        //Editar
        void on_actionAbrir_con_triggered();
        void on_actionAbrir_directorio_triggered();
        void on_actionAbrir_terminal_triggered();
        void on_actionRenombrar_triggered();
        void on_actionEliminar_triggered();

        //Herramientas
        void on_actionAmpliar_triggered();
        void on_actionReducir_triggered();
        void on_actionAjustar_triggered();
        void on_actionNormal_triggered();
        void on_actionRotarDerecha_triggered();
        void on_actionRotarIzquierda_triggered();
        void on_actionRestablecer_triggered();

        //Preferencias
        void on_actionPantalla_completa_toggled(bool cond);

        //Ayuda
        void on_actionAyuda_triggered();
        void on_actionAcerca_de_triggered();

    public:

        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();

        void limpiarImagen();
        void activarFuncionalidades(bool cond);
        void ajustarZoom();
};

#endif // MAINWINDOW_HPP
