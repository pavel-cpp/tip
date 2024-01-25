#include "font_editor.h"
#include <ui_font_editor.h>

FontEditor::FontEditor(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::FontEditor) {
    ui->setupUi(this);
}

FontEditor::~FontEditor() {
    delete ui;
}
