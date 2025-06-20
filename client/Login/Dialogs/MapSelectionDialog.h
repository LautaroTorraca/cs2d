#pragma once

#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

class MapSelectionDialog : public QDialog {
Q_OBJECT

private:
    uint8_t selectedMap;

    private slots:
    void selectDust();
    void selectAztec();
    void selectTraining();

public:
    explicit MapSelectionDialog(QWidget* parent = nullptr);
    uint8_t getSelectedMap() const;

};
