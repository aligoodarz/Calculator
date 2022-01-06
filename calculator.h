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

    //Kind of like a state machine
    double currentValue;
    // True when any of these are pressed
    // False when they are not
    bool divPressed;
    bool addPressed;
    bool subPressed;
    bool multPressed;

private:
    Ui::Calculator *ui;


private slots:
    void NumPressed(); // handles all the numbers
    void MathButtonPressed(); //handles all the math operations
    void CalculateButtonPressed(); // handles calculating the final answer
    void on_clear_clicked(); //Clears the calculator
};
#endif // CALCULATOR_H
