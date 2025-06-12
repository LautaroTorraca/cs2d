#ifndef SERVERMENU_H
#define SERVERMENU_H

#include <QWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include <memory>

class ServerMenu : public QWidget {
Q_OBJECT

public:
    explicit ServerMenu(QWidget *parent = nullptr);

protected:
    void resizeEvent(QResizeEvent* event) override;

private:
    void setupUI();

    std::unique_ptr<QWidget> overlayWidget;
    std::unique_ptr<QVBoxLayout> buttonLayout;
    std::unique_ptr<QLineEdit> usernameInput;
};

#endif // SERVERMENU_H
