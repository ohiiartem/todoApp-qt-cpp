#include "mainwindow.h"
#include <QFile>
#include <QApplication>
#include <QFontDatabase>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QFontDatabase::addApplicationFont(":/styles/fonts/Roboto-Regular.ttf");

    QFile styleFile(":/styles/style.qss");
    if (styleFile.open(QFile::ReadOnly)) {
        QString styleSheet = QLatin1String(styleFile.readAll());
        app.setStyleSheet(styleSheet);
        styleFile.close();
    }

    app.setApplicationName("To Do");
    app.setApplicationVersion("1.5");

    MainWindow w;
    w.show();
    return app.exec();
}
