#pragma once
#include <QWidget>
#include <QVBoxLayout>
#include "client/Protocol.h"

class UsernameInput;
class CreateGameButton;
class JoinGameButton;
class ListGamesButton;
class ExitGameButton;

using namespace Client;
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
    UsernameInput* usernameInput;

    CreateGameButton* createGameButton;
    JoinGameButton* joinGameButton;
    ListGamesButton* listGamesButton;
    ExitGameButton* exitGameButton;

public:
    explicit ServerMenu(const char* port, QWidget *parent = nullptr);
};

