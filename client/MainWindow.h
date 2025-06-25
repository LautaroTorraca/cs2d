#pragma once

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

#include <qdialog.h>
enum class ConnectionChoice { None, Create, Join };

class MainWindow: public QDialog {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ConnectionChoice getChoice() const;

private:
    ConnectionChoice choice;
};
