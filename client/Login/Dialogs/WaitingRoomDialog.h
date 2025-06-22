#pragma once

#include <QDialog>
#include <QLabel>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QCloseEvent>
#include <thread>
#include <vector>
#include <atomic>

#include "client/Protocol.h"
#include "server/DTO/PlayerChoicesDTO.h"
#include "Login/ServerMenu.h"

using namespace Client;

class WaitingRoomDialog : public QDialog {
    Q_OBJECT

private:

    // UI Components
    QVBoxLayout* playersLayout;
    QHBoxLayout* buttonLayout;
    QScrollArea* playersScrollArea;
    QWidget* playersWidget;
    QPushButton* readyBtn;
    std::vector<QLabel*> playerLabels;

    // Game Data
    QString playerName;
    QString teamStr;
    QString skinStr;
    Protocol& protocol;
    ServerMenu* menu;

    // State Management
    std::thread roomWaiter;
    std::atomic<bool> shouldStop;
    std::atomic<bool> isReady;
    std::atomic<bool> gameStarted;

    // UI Setup methods
    void setupUI();
    void setupPlayersArea();
    void setupButtons();

    // Threading methods
    void startPolling();
    void stopPolling();
    void pollLobby();

    // UI Update methods
    void updatePlayerList(const std::vector<PlayerChoicesDTO>& players);
    void updateSelfPlayerDisplay();
    void clearPlayerLabels();

    // Helper methods
    QLabel* createPlayerLabel(const QString& name, const QString& team, const QString& skin,
                              bool ready, bool isSelf = false);
    bool isLocalPlayerInList(const std::vector<PlayerChoicesDTO>& players);
    void restoreMenu();

    // Event handlers
    void handleGameStart();
    void closeMenuAndStartGame();
    void handleConnectionError(const std::string& error);



private slots:
    void onReadyClicked();
    void onExitClicked();

protected:
    void closeEvent(QCloseEvent* event) override;

public:
    WaitingRoomDialog(const QString& playerName, const QString& teamStr, const QString& skinStr,
                      Protocol& protocol, ServerMenu* menu = nullptr, QWidget* parent = nullptr);
    ~WaitingRoomDialog();




};