#pragma once

#include <QDialog>
#include <QLabel>
#include <QScrollArea>
#include <QTimer>
#include <QVBoxLayout>
#include <thread>
#include <vector>

#include "client/Protocol.h"
#include "server/DTO/PlayerChoicesDTO.h"

using namespace Client;

class WaitingRoomDialog : public QDialog {
    Q_OBJECT

private:
    void setupUI();
    void pollLobby();
    void updatePlayerList(const std::vector<PlayerChoicesDTO>& players);

    // UI Components
    QVBoxLayout* playersLayout;
    QScrollArea* playersScrollArea;
    QWidget* playersWidget;
    QPushButton* readyBtn;
    std::vector<QLabel*> playerLabels;

    // Game Data
    QString playerName;
    QString teamStr;
    QString skinStr;
    Protocol& protocol;
    // ELIMINADO: std::map<std::string, PlayerChoicesDTO> allKnownPlayers;

    // Threading
    std::thread roomWaiter;
    std::atomic<bool> shouldStop;
    std::atomic<bool> isReady;

private slots:
    void onReadyClicked();
    void onExitClicked();

protected:
    void closeEvent(QCloseEvent* event) override;

public:
    WaitingRoomDialog(const QString& playerName,
                      const QString& teamStr,
                      const QString& skinStr,
                      Protocol& protocol,
                      QWidget* parent = nullptr);
    ~WaitingRoomDialog();
};