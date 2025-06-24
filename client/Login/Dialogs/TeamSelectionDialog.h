#pragma once
#include <QDialog>
#include <QString>

#include "client/Protocol.h"
#include "server/Team.h"

class QPushButton;
class QVBoxLayout;

using namespace Client;
class TeamSelectionDialog : public QDialog {
    Q_OBJECT

private slots:
    void selectCT();
    void selectTT();

private:
    Protocol& protocol;
    QString selectedTeam;
    void setupUI();

public:
    explicit TeamSelectionDialog(Protocol& protocol, QWidget* parent = nullptr);
    Team getSelectedTeam() const;
    void closeEvent(QCloseEvent* event);
};

