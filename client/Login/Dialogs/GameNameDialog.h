#ifndef GAMENAMEDIALOG_H
#define GAMENAMEDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>

class GameNameDialog : public QDialog {
    Q_OBJECT

public:
    explicit GameNameDialog(QWidget* parent = nullptr,
                            const QString& labelText = "Enter game name:",
                            const QString& confirmText = "OK");

    QString getGameName() const;

private slots:
    void onTextChanged(const QString& text);

private:
    void setupStyle();
    void setupUI(const QString& labelText, const QString& confirmText);

    QLineEdit* input;
    QPushButton* confirmBtn;
};

#endif // GAMENAMEDIALOG_H