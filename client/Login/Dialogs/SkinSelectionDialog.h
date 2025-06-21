#pragma once

#include <QDialog>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include <QStringList>

class SkinSelectionDialog : public QDialog {
    Q_OBJECT

private:
    void setupUI();
    void setupConnections();
    void loadSkinsForTeam(uint8_t teamId);
    void updateSkinImage(int index);
    void handleConfirm();

    QComboBox* skinComboBox;
    QPushButton* confirmButton;
    QLabel* skinImageLabel;

    QStringList skinPaths;
    uint8_t selectedSkin;

public:
    explicit SkinSelectionDialog(uint8_t teamId, QWidget* parent = nullptr);
    uint8_t getSelectedSkin() const;

};
