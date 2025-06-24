#include "MainWindow.h"

#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>

// MainWindow::MainWindow(QWidget* parent): QMainWindow(parent) {
//     QWidget* central = new QWidget(this);
//     QVBoxLayout* layout = new QVBoxLayout(central);
//
//     auto* crear = new QPushButton("Crear");
//     auto* unirse = new QPushButton("Unirse");
//
//     layout->addWidget(crear);
//     layout->addWidget(unirse);
//
//     setCentralWidget(central);
//
//     connect(crear, &QPushButton::clicked, this, &MainWindow::onCrearClicked);
//     connect(unirse, &QPushButton::clicked, this, &MainWindow::onUnirseClicked);
// }
//
// void MainWindow::onCrearClicked() {
//     QMessageBox::information(this, "Crear", "Has hecho clic en Crear.");
// }
//
// void MainWindow::onUnirseClicked() {
//     QMessageBox::information(this, "Unirse", "Has hecho clic en Unirse.");
// }

MainWindow::MainWindow(QWidget* parent): QDialog(parent), choice(ConnectionChoice::None) {
    setWindowTitle("Elegir acción");
    resize(400, 200);

    auto* layout = new QVBoxLayout(this);

    layout->setSpacing(20);                      // Separación entre botones
    layout->setContentsMargins(50, 40, 50, 40);  // Margen interior
                                                 //
    auto* btnCreate = new QPushButton("Crear partida", this);
    auto* btnJoin = new QPushButton("Unirse a partida", this);

    QFont font;
    font.setPointSize(14);  // Aumentar tamaño de fuente
    btnCreate->setFont(font);
    btnJoin->setFont(font);

    btnCreate->setMinimumHeight(50);  // Altura mínima del botón
    btnJoin->setMinimumHeight(50);


    layout->addWidget(btnCreate);
    layout->addWidget(btnJoin);

    connect(btnCreate, &QPushButton::clicked, [this] {
        choice = ConnectionChoice::Create;
        accept();
    });

    connect(btnJoin, &QPushButton::clicked, [this] {
        choice = ConnectionChoice::Join;
        accept();
    });
}

ConnectionChoice MainWindow::getChoice() const { return choice; }
