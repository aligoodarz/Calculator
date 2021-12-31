#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Calculator; }
QT_END_NAMESPACE

class Calculator : public QMainWindow
{
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr);
    ~Calculator();

    double currentValue;
    bool divPressed;
    bool addPressed;
    bool subPressed;
    bool multPressed;

private:
    Ui::Calculator *ui;


private slots:
    void NumPressed();
    void MathButtonPressed();
    void CalculateButtonPressed();

    void on_clear_clicked();
};
#endif // CALCULATOR_H
