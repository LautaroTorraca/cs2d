#pragma once

#include <QComboBox>
#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QStringList>

#include "client/Protocol.h"

using namespace Client;

class SkinSelectionDialog : public QDialog {
    Q_OBJECT

private:
    void setupUI();
    void setupConnections();
    void loadSkinsForTeam(uint8_t teamId);
    void updateSkinImage(int index);
    void handleConfirm();
    void closeEvent(QCloseEvent* event);

    QComboBox* skinComboBox;
    QPushButton* confirmButton;
    QLabel* skinImageLabel;

    QStringList skinPaths;
    uint8_t selectedSkin;
    Protocol& protocol;

public:
    SkinSelectionDialog(uint8_t teamId, Protocol& protocol , QWidget* parent = nullptr);
    uint8_t getSelectedSkin() const;

};
