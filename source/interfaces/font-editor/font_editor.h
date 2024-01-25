#pragma once

#include <QDialog>
#include <QColor>

namespace Ui {
    class FontEditor;
}

class FontEditor : public QDialog {
Q_OBJECT

public:
    explicit FontEditor(QWidget *parent = nullptr);

    ~FontEditor() override;

private slots:

    

private:

    Ui::FontEditor *ui;
};
