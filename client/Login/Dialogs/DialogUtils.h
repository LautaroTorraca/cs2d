#pragma once
#include <QDialog>
#include <QDialogButtonBox>
#include <QVBoxLayout>

namespace DialogUtils {

// Crea y conecta un botón estándar Ok / Cancel
inline QDialogButtonBox* createStandardButtonBox(QDialog* dialog) {
    auto* box = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    QObject::connect(box, &QDialogButtonBox::accepted, dialog, &QDialog::accept);
    QObject::connect(box, &QDialogButtonBox::rejected, dialog, &QDialog::reject);
    return box;
}

// Crea un layout vertical base con márgenes razonables
inline QVBoxLayout* createBaseLayout(QWidget* parent = nullptr) {
    auto* layout = new QVBoxLayout(parent);
    layout->setContentsMargins(20, 20, 20, 20);
    layout->setSpacing(15);
    return layout;
}

}

