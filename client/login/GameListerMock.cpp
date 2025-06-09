#include "GameListerMock.h"
#include <QMessageBox>

void GameListerMock::showAvailableGames(QWidget *parent) {
    // In real code, retrieve from server
    QString list = "Games:\n - Match #1 (2/4)\n - Match #2 (1/4)\n - Match #3 (0/4)";
    QMessageBox::information(parent, "Available Games", list);
}
