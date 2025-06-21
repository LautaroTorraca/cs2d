#pragma once
#include <QWidget>
#include <QPalette>
#include <QPixmap>
#include <QStringList>


class MenuBackground {
public:
    static void applyTo(QWidget* widget, const QString& relativePath = ":/Login/Assets/image_background.png");
};

