#ifndef SERVER_MENU_H
#define SERVER_MENU_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>
#include <memory>

class ServerMenu : public QWidget {
    Q_OBJECT

public:
    explicit ServerMenu(QWidget *parent = nullptr);

private slots:
    void handleCreateGame();
    void handleJoinGame();
    void handleListGames();
    void handleExitGame();

private:
    std::unique_ptr<QLabel> backgroundLabel;
    std::unique_ptr<QWidget> overlayWidget;
    std::unique_ptr<QVBoxLayout> buttonLayout;

    std::unique_ptr<QLineEdit> usernameInput;
    std::unique_ptr<QPushButton> createGameBtn;
    std::unique_ptr<QPushButton> joinGameBtn;
    std::unique_ptr<QPushButton> listGamesBtn;
    std::unique_ptr<QPushButton> exitBtn;

    void setupUI();
};

#endif // SERVER_MENU_H
