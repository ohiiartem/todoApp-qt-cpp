#include "mainwindow.h"
#include <QFile>
#include <QApplication>
#include <QFontDatabase>
#include <QDebug>

static QString styleSheetPath()
{
    #if defined(QT_DEBUG) && defined(QSS_SOURCE_PATH)
        return QStringLiteral(QSS_SOURCE_PATH);
    #else
        return QStringLiteral(":/styles/style.qss");
    #endif
}

static void applyStyleSheet()
{
    const QString path = styleSheetPath();

    QFile styleFile(path);
        if (styleFile.open(QFile::ReadOnly)) {
            QString styleSheet = QString::fromUtf8(styleFile.readAll());
            qApp->setStyleSheet(styleSheet);
        } else
        {
            qWarning() << "Failed to open style file:" << path;
        }
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QFontDatabase::addApplicationFont(":/styles/fonts/Roboto-Regular.ttf");
    QFontDatabase::addApplicationFont(":/styles/fonts/Roboto-Medium.ttf");
    QFontDatabase::addApplicationFont(":/styles/fonts/Roboto-Bold.ttf");


    applyStyleSheet();

    app.setApplicationName("To Do");
    app.setApplicationVersion("1.5");

    MainWindow w;
    w.show();
    return app.exec();
}
