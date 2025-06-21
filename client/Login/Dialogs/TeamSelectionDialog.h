#pragma once
#include <QDialog>
#include <QString>

#include "server/Team.h"

class QPushButton;
class QVBoxLayout;


class TeamSelectionDialog : public QDialog {
    Q_OBJECT

private slots:
    void selectCT();
    void selectTT();

private:
    QString selectedTeam;
    void setupUI();

public:
    explicit TeamSelectionDialog(QWidget* parent = nullptr);
    Team getSelectedTeam() const;
};

