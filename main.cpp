#include "calculator.h"

#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QDebug>


//This function reads the Css file
QString readTextFile (QString path);


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Make sure the css file is there and apply the style to it
    //if not outputs an error indicating this
    QString css = readTextFile("C:/Users/gooda/OneDrive/Desktop/QtApp/Calculator/styleSheet.css");
    if (css.length() > 0 )
    {
        a.setStyleSheet(css);
    }else
    {
       qDebug ()<<"Failed to find the css file";
    }

    Calculator w;
    w.show();
    return a.exec();
}



QString readTextFile (QString path)
{
    QFile file(path);

    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        return in.readAll();
    }else
    {
    qDebug()<<"File Failed to Open";
    }
    return "";
}
