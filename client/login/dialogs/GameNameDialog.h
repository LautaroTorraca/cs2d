#ifndef GAME_NAME_DIALOG_H
#define GAME_NAME_DIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>

class GameNameDialog : public QDialog {
Q_OBJECT

public:
    explicit GameNameDialog(QWidget* parent = nullptr);
    QString getGameName() const;

private:
    QLineEdit* input;
};

#endif // GAME_NAME_DIALOG_H
