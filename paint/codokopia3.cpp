#include <QApplication>
#include "mainwindow.h"

// g++ codokopia3.cpp -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -o codokopia3
// ./codokopia3

int main(int argc, char *argv[]){

    QApplication app(argc,argv);
    MainWindow w;
    w.show();
    return app.exec();
}