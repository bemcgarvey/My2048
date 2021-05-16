#include "powerof2spinbox.h"
#include <QDebug>

PowerOf2SpinBox::PowerOf2SpinBox(QWidget *parent) : QSpinBox(parent)
{

}

void PowerOf2SpinBox::setRawValue(int v)
{
    setValue(valueFromText(QString::number(v)));
}

int PowerOf2SpinBox::valueFromText(const QString &text) const
{
    int pow2 = text.toInt();
    int val = 0;
    while (pow2 > 1) {
        pow2 >>= 1;
        ++val;
    }
    return val;
}

QString PowerOf2SpinBox::textFromValue(int val) const
{
    if (val < 0) {
        return "-";
    }
    int pow2 = 1;
    while (val > 0) {
        pow2 <<= 1;
        --val;
    }
    return(QString::number(pow2));
}
