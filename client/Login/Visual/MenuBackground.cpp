#include "MenuBackground.h"
#include <QCoreApplication>
#include <QBrush>
#include <QDebug>

void MenuBackground::applyTo(QWidget* widget, const QString& relativePath) {
    QPixmap backgroundPixmap(relativePath);

    if (backgroundPixmap.isNull()) {
        QString appDir = QCoreApplication::applicationDirPath();
        QStringList fallbackPaths = {
                appDir + "/../client/Login/Assets/image_background.png",
                "client/Login/Assets/image_background.png",
                "Login/Assets/image_background.png"
        };

        for (const auto& path : fallbackPaths) {
            backgroundPixmap = QPixmap(path);
            if (!backgroundPixmap.isNull()) break;
        }
    }

    QPalette palette;

    if (!backgroundPixmap.isNull()) {
        backgroundPixmap = backgroundPixmap.scaled(
                widget->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation
        );
        palette.setBrush(QPalette::Window, QBrush(backgroundPixmap));
    } else {
        palette.setColor(QPalette::Window, QColor(20, 25, 35));
    }

    widget->setAttribute(Qt::WA_StyledBackground, true);
    widget->setPalette(palette);
    widget->setAutoFillBackground(true);
}
