#ifndef GAME_LIST_DIALOG_H
#define GAME_LIST_DIALOG_H

#include <QDialog>
#include <QStringList>

class QVBoxLayout;
class QListWidget;
class QPushButton;

class GameListDialog : public QDialog {
Q_OBJECT

public:
    explicit GameListDialog(const QStringList& games, QWidget* parent = nullptr);
    QString getSelectedGame() const;

private slots:
    void handleJoin();

private:
    void setupUI(const QStringList& games);
    void applyStyle();

    QListWidget* listWidget;
    QPushButton* joinButton;
    QString selectedGame;
};

#endif // GAME_LIST_DIALOG_H
