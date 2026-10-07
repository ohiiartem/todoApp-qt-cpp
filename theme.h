#ifndef THEME_H
#define THEME_H
#include <QPalette>
#include <QColor>

struct Theme
{
    QColor window;
    QColor surface;
    QColor surfaceSelected;
    QColor text;
    QColor textSelected;
    QColor textMuted;
    QColor accent;
    QColor border;
    QColor keycap;
    QColor keycapEdge;
    QColor keycapText;
    QColor textDone;
};

Theme darkTheme();
QPalette makePalette(const Theme &theme);

#endif // THEME_H
