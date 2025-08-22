#ifndef CANVAS_H
#define CANVAS_H



// sssssssssssssssssssssssssssssssssssssssssssssssssss

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QImage>

class Canvas : public QWidget
{
    Q_OBJECT

public:
    explicit Canvas(QWidget *parent = nullptr);
    void clear();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    QImage image;
    QPoint lastPoint;
    bool drawing = false;
};

#endif 
