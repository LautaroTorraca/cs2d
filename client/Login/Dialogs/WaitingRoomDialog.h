#ifndef WAITINGROOMDIALOG_H
#define WAITINGROOMDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <thread>
#include <vector>

#include "server/DTO/GameLobbyDTO.h"
#include "server/DTO/PlayerChoicesDTO.h"
#include "client/Protocol.h"
#include "server/DTO/PlayerChoicesDTO.h"

#include "Protocol.h"

class WaitingRoomDialog : public QDialog {
    Q_OBJECT

public:
    explicit WaitingRoomDialog(const QString& playerName,
                               const QString& team,
                               const QString& skin,
                               Protocol& protocol,
                               QWidget* parent = nullptr);

    ~WaitingRoomDialog();

private:
    std::string playerName;
    uint8_t team;
    uint8_t skin;

    Protocol& protocol;

    std::thread roomWaiter;

    QVBoxLayout* playersLayout;
    std::vector<QLabel*> playerLabels;

    QPushButton* readyButton;
    QPushButton* exitButton;

    void setupUI(const QString& playerName, const QString& team, const QString& skin);
    void pollLobby();
    void updatePlayerList(const std::vector<PlayerChoicesDTO>& players);

private slots:
    void onReadyClicked();
};

#endif // WAITINGROOMDIALOG_H
