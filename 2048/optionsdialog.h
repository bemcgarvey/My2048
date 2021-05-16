#ifndef OPTIONSDIALOG_H
#define OPTIONSDIALOG_H

#include <QDialog>

namespace Ui {
class OptionsDialog;
}

class OptionsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OptionsDialog(QWidget *parent = nullptr);
    ~OptionsDialog();
    void setOptions(int size, int startTiles, int winningTile);
    void getOptions(int &size, int &startTiles, int &winningTile) const;
private:
    Ui::OptionsDialog *ui;
};

#endif // OPTIONSDIALOG_H
