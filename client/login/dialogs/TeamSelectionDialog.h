#ifndef TEAM_SELECTION_DIALOG_H
#define TEAM_SELECTION_DIALOG_H

#include <QDialog>
#include <QString>

class QPushButton;
class QVBoxLayout;

class TeamSelectionDialog : public QDialog {
Q_OBJECT

public:
    explicit TeamSelectionDialog(QWidget *parent = nullptr);
    QString getSelectedTeam() const;

private slots:
    void selectCT();
    void selectTT();

private:
    QString selectedTeam; // TODO: Cambiar a uint8_t y usar TeamConstants en el futuro
};

#endif // TEAM_SELECTION_DIALOG_H
