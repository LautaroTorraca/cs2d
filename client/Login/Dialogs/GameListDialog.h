#pragma once

#include <QDialog>
#include <QStringList>

class QListWidget;
class QPushButton;

class GameListDialog : public QDialog {
Q_OBJECT

public:
    explicit GameListDialog(const QStringList& games, QWidget* parent = nullptr);
    QString getSelectedGame() const;

private:
    QListWidget* listWidget;
    QPushButton* joinButton;
    QString selectedGame;

    void applyStyle();
    void setupUI(const QStringList& games);
    void handleJoin();
};
