#ifndef SKINSELECTIONDIALOG_H
#define SKINSELECTIONDIALOG_H

#include <QDialog>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include <QStringList>


class SkinSelectionDialog : public QDialog {
    Q_OBJECT

private slots:
    void handleConfirm();
    void updateSkinImage(int index);

private:
    void setupUI();
    void setupConnections();
    void loadSkinsForTeam(uint8_t team);

    QComboBox* skinComboBox;
    QPushButton* confirmButton;
    QLabel* skinImageLabel;
    QStringList skinPaths;
    uint8_t selectedSkin;

public:
    explicit SkinSelectionDialog(uint8_t team, QWidget* parent = nullptr);
    uint8_t getSelectedSkin() const;
};

#endif // SKINSELECTIONDIALOG_H
