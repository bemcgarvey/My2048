#include "optionsdialog.h"
#include "ui_optionsdialog.h"

OptionsDialog::OptionsDialog(QWidget *parent) :
    QDialog(parent, Qt::MSWindowsFixedSizeDialogHint | Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint),
    ui(new Ui::OptionsDialog)
{
    ui->setupUi(this);
}

OptionsDialog::~OptionsDialog()
{
    delete ui;
}

void OptionsDialog::setOptions(int size, int startTiles, int winningTile)
{
    switch (size) {
    case 4: ui->sizeComboBox->setCurrentIndex(0);
        break;
    case 5: ui->sizeComboBox->setCurrentIndex(1);
        break;
    case 6: ui->sizeComboBox->setCurrentIndex(2);
        break;
    default: ui->sizeComboBox->setCurrentIndex(0);
        break;
    }
    ui->startTilesSpinBox->setValue(startTiles);
    ui->winingTileSpinBox->setRawValue(winningTile);
}

void OptionsDialog::getOptions(int &size, int &startTiles, int &winningTile) const
{
   size = ui->sizeComboBox->currentIndex() + 4;
   startTiles = ui->startTilesSpinBox->value();
   winningTile = ui->winingTileSpinBox->text().toInt();
}
