#ifndef GAMEMENUBUTTON_H
#define GAMEMENUBUTTON_H

#include <QPushButton>
#include <QWidget>

class GameMenuButton : public QPushButton {
Q_OBJECT

public:
    explicit GameMenuButton(const QString& label, QWidget* parent = nullptr);

protected:
    void applyStyle();
};

#endif // GAMEMENUBUTTON_H
