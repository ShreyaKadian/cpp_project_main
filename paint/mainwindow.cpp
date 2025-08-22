#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    Canvas *canvas = new Canvas(this);   // Our custom drawing widget
    setCentralWidget(canvas);            // Put it in the middle of the window
    setWindowTitle("Qt Paint App");      // Window title
    resize(600, 600);                    // Default size
}
