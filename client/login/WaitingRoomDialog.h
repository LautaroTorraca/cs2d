#ifndef WAITING_ROOM_DIALOG_H
#define WAITING_ROOM_DIALOG_H

#include <QDialog>
#include <QString>
#include <vector>

#include "GameDTO.h"

class QLabel;
class QVBoxLayout;

class WaitingRoomDialog : public QDialog {
    Q_OBJECT

public:
    explicit WaitingRoomDialog(const GameDTO &config, const QString &playerName,
                                const QString &team, const QString &skin,
                                QWidget *parent = nullptr);

private:
    QVBoxLayout *playersLayout;
    std::vector<QLabel *> playerLabels;

    void populateInitialPlayer(const QString &name, const QString &team, const QString &skin);
    void simulateOtherPlayersJoining(int total);
};

#endif // WAITING_ROOM_DIALOG_H
