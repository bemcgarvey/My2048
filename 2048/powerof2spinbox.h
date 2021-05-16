#ifndef POWEROF2SPINBOX_H
#define POWEROF2SPINBOX_H

#include <QSpinBox>

class PowerOf2SpinBox : public QSpinBox
{
    Q_OBJECT
public:
    PowerOf2SpinBox(QWidget *parent);
    void setRawValue(int v);
protected:
    virtual int valueFromText(const QString &text) const override;
    virtual QString textFromValue(int val) const override;
};

#endif // POWEROF2SPINBOX_H
