#ifndef GAME_NAME_DIALOG_H
#define GAME_NAME_DIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>


class GameNameDialog : public QDialog {
    Q_OBJECT

private:
    QLineEdit* input;

    void setupUI(const QString& labelText, const QString& confirmText);
    void setupStyle();

public:
    explicit GameNameDialog(QWidget* parent = nullptr,
                            const QString& labelText = "Please enter the game name:",
                            const QString& confirmText = "OK");

    QString getGameName() const;
};

#endif // GAME_NAME_DIALOG_H
