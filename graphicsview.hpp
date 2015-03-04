#ifndef GRAPHICSVIEW_HPP
#define GRAPHICSVIEW_HPP

#include <QGraphicsView>
#include <QWheelEvent>
#include <QtMath>

class GraphicsView : public QGraphicsView {

    private:

        int factor;

    public:

        GraphicsView(QWidget* parent = 0);
        ~GraphicsView();

        int getFactor();
        void setFactor(int fact);

    protected:

        virtual void wheelEvent(QWheelEvent* e);
};

#endif // GRAPHICSVIEW_HPP
