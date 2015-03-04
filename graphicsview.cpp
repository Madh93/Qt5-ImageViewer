#include "graphicsview.hpp"

GraphicsView::GraphicsView(QWidget *parent) : QGraphicsView(parent) {

    factor = 0;
}


GraphicsView::~GraphicsView() { }


int GraphicsView::getFactor() { return factor; }


void GraphicsView::setFactor(int fact) {

    if (fact == 0)
        factor = 0;
    else
        factor += fact;
}


void GraphicsView::wheelEvent(QWheelEvent *e) {

    //Calcular movimiento de rueda
    int distancia = e->delta()/15/8;
    qreal val;

    if (distancia != 0) {
        val = pow(1.2, distancia);
        this->scale(val,val);
        if (distancia > 0)
            factor++;
        else
            factor--;
    }
}
