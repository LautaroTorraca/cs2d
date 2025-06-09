#ifndef SKIN_SELECTION_DIALOG_H
#define SKIN_SELECTION_DIALOG_H

#include <QDialog>
#include <QString>

class QComboBox;
class QPushButton;

class SkinSelectionDialog : public QDialog {
    Q_OBJECT

public:
    explicit SkinSelectionDialog(const QString &team, QWidget *parent = nullptr);
    QString getSelectedSkin() const;

private slots:
    void handleConfirm();

private:
    QString selectedSkin;
    QComboBox *skinComboBox;
    QPushButton *confirmButton;

    void loadSkinsForTeam(const QString &team);
};

#endif // SKIN_SELECTION_DIALOG_H
