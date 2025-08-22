#include "canvas.h"

//./paintapp



Canvas::Canvas(QWidget *parent) : QWidget(parent)
{
    image = QImage(600, 600, QImage::Format_RGB32);  
    image.fill(Qt::white);                           
    setFixedSize(600, 600);                         
}

void Canvas::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawImage(0, 0, image);   
}

void Canvas::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        lastPoint = event->pos();     
        drawing = true;
    }
}

void Canvas::mouseMoveEvent(QMouseEvent *event)
{
    if (drawing && (event->buttons() & Qt::LeftButton)) {
        QPainter painter(&image);
        painter.setPen(QPen(Qt::black, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        painter.drawLine(lastPoint, event->pos());  
        lastPoint = event->pos();                   
        update();                                   
    }
}

void Canvas::clear()
{
    image.fill(Qt::white);   
    update();                }
