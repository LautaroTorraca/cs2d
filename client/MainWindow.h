#pragma once

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

#include <qdialog.h>
// class MainWindow: public QMainWindow {
//     Q_OBJECT
//
// public:
//     MainWindow(QWidget* parent = nullptr);
// private slots:
//     void onCrearClicked();
//     void onUnirseClicked();
// };
//
enum class ConnectionChoice { None, Create, Join };

class MainWindow: public QDialog {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ConnectionChoice getChoice() const;

    // private slots:
    //     void onCreateClicked();
    //     void onJoinClicked();

private:
    ConnectionChoice choice;
};
