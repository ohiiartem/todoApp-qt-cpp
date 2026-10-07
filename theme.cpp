#include "theme.h"

Theme darkTheme()
{
    Theme theme;

    theme.window = QColor("#15171c");
    theme.surface = QColor("#1a1e25");
    theme.surfaceSelected = QColor("#1e2630");
    theme.text = QColor("#dfe3ea");
    theme.textSelected = QColor("#ffffff");
    theme.textMuted = QColor("#6e7683");
    theme.accent = QColor("#4fd1a5");
    theme.border = QColor("#21252d");
    theme.keycap = QColor("#252a34");
    theme.keycapEdge = QColor("#171a21");
    theme.keycapText = QColor("#e2e6ec");
    theme.textDone = QColor("#585f6b");

    return theme;
}

QPalette makePalette(const Theme &theme)
{
    QPalette palette;
    palette.setColor(QPalette::Window, theme.window);
    palette.setColor(QPalette::Base, theme.surface);
    palette.setColor(QPalette::Highlight, theme.surfaceSelected);
    palette.setColor(QPalette::Text, theme.text);
    palette.setColor(QPalette::WindowText, theme.text);
    palette.setColor(QPalette::HighlightedText, theme.textSelected);
    palette.setColor(QPalette::PlaceholderText, theme.textMuted);
    palette.setColor(QPalette::Accent, theme.accent);
    palette.setColor(QPalette::Mid, theme.border);
    palette.setColor(QPalette::Button, theme.keycap);
    palette.setColor(QPalette::Dark, theme.keycapEdge);
    palette.setColor(QPalette::ButtonText, theme.keycapText);

    return palette;
}
