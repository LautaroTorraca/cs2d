#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include "client/Protocol.h"

class UsernameInput;
class CreateGameButton;
class JoinGameButton;
class ListGamesButton;
class ExitGameButton;
class MusicManager;

class ServerMenu : public QWidget {
    Q_OBJECT

private:
    void setupUI();
    void setupBackground();
    void setupInput();
    void setupButtons();
    void setupBackgroundMusic();
    void resizeEvent(QResizeEvent* event) override;

    Protocol protocol;
    QWidget* overlayWidget;
    QVBoxLayout* buttonLayout;
    UsernameInput* usernameInput;

    CreateGameButton* createGameButton;
    JoinGameButton* joinGameButton;
    ListGamesButton* listGamesButton;
    ExitGameButton* exitGameButton;

    MusicManager* musicManager;

public:
    explicit ServerMenu(const char* port, QWidget *parent = nullptr);
};