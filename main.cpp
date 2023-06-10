//#include "mainwindow.h"

//#include <QApplication>

//int main(int argc, char *argv[])
//{
//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
//    return a.exec();
//}


#include <QApplication>
#include "DarkStyle.h"
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    QApplication::setStyle(new DarkStyle);
//    FramelessWindow framelessWindow;
    //framelessWindow.setWindowState(Qt::WindowFullScreen);
    //framelessWindow.setWindowTitle("test title");
//    framelessWindow.setWindowIcon(a.style()->standardIcon(QStyle::SP_DesktopIcon));

    // create our mainwindow instance
//    MainWindow *mainWindow = new MainWindow;

    // add the mainwindow to our custom frameless window
//    framelessWindow.setContent(mainWindow);
//    framelessWindow.show();
    MainWindow w;
    w.setWindowIcon(QIcon("C:/Users/Имя/Documents/photo_2023-06-10_02-50-21.png"));
    w.setWindowTitle("MOTORCYCLE MANAGER");
    w.show();
    return a.exec();
}
