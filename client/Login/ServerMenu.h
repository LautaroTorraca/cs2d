#pragma once
#include <QWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include "client/Protocol.h"

class CreateGameButton;
class JoinGameButton;
class ListGamesButton;
class ExitGameButton;

class ServerMenu : public QWidget {
    Q_OBJECT

private:
    void setupUI();
    void setupBackground();
    void setupInput();
    void setupButtons();
    void resizeEvent(QResizeEvent* event) override;

    Protocol protocol;
    QWidget* overlayWidget;
    QVBoxLayout* buttonLayout;
    QLineEdit* usernameInput;

    CreateGameButton* createGameButton;
    JoinGameButton* joinGameButton;
    ListGamesButton* listGamesButton;
    ExitGameButton* exitGameButton;

public:
    explicit ServerMenu(const char* port, QWidget *parent = nullptr);
};

