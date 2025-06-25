#pragma once

#include <QLineEdit>
#include <QString>
#include <QWidget>
#include <utility>

#include "client/Protocol.h"
#include "common/Constants/Skin.h"
#include "common/Constants/MapTypeConstants.h"
#include "common/Constants/TeamConstants.h"
using namespace Client;


class GameFlowUtils {
public:
    static QString getUsername(QLineEdit* input, QWidget* parent);
    static QString askGameName(QWidget* parent);

    static MapType askMap(QWidget* parent);
    static std::pair<uint8_t, uint8_t> askConfig(QWidget* parent);

    static Team askTeam(QWidget* parent, Protocol& protocol);
    static Skin askSkin(uint8_t teamId, QWidget* parent, Protocol& protocol);

    static void showError(QWidget* parent, const QString& title, const QString& message);
};
