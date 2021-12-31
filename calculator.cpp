#include "calculator.h"
#include "ui_calculator.h"


Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
{
    ui->setupUi(this);

    //Initialize the parameters
    currentValue = 0.0;
    divPressed = false;
    addPressed = false;
    subPressed = false;
    multPressed = false;

    //Initialize the display
    ui->displayLineEdit->setText(QString::number(currentValue));
    QPushButton * numberButtons[10];
    for (int i = 0; i<10 ; i++)
    {
        QString buttonName = "button"+QString::number(i);
        numberButtons[i] = Calculator::findChild<QPushButton *>(buttonName);
        connect (numberButtons[i],SIGNAL(released()), this,
                 SLOT(NumPressed()));
    }

    //connect the operations to the slot
    connect (ui->plus,SIGNAL(released()), this,
             SLOT(MathButtonPressed()));
    connect (ui->minus, SIGNAL(released()),this,
             SLOT(MathButtonPressed()));
    connect (ui->divide, SIGNAL(released()),this,
             SLOT(MathButtonPressed()));
    connect (ui->multiply, SIGNAL(released()),this,
             SLOT(MathButtonPressed()));

    //for the equals sign
    connect (ui->equals, SIGNAL(released()),this,
             SLOT(CalculateButtonPressed()));
}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::NumPressed()
{
    QPushButton * button = (QPushButton*)sender();
    QString buttonValue = button->text();
    QString displayValue = ui->displayLineEdit->text();
    if ((displayValue.toDouble() == 0.0) || (displayValue.toDouble() == 0.0)) {
        ui->displayLineEdit->setText(buttonValue);
    }else
    {
        QString newValue = displayValue + buttonValue;
        double numberNewValue = newValue.toDouble();
        ui->displayLineEdit->setText(QString::number(numberNewValue,'g',20));
    }


}

void Calculator::MathButtonPressed()
{
    divPressed = false;
    addPressed = false;
    subPressed = false;
    multPressed = false;
    QString displayValue = ui->displayLineEdit->text();
    currentValue = displayValue.toDouble();
    QPushButton *button = (QPushButton * )sender();
    QString buttonValue = button->text();
    if (QString::compare(buttonValue, "/") == 0){
        divPressed = true;
    }else if (QString::compare(buttonValue, "*") == 0){
        multPressed = true;
    }else if (QString::compare(buttonValue, "+") == 0){
        addPressed = true;
    }else subPressed = true;
    ui->displayLineEdit->setText("");
}

void Calculator::CalculateButtonPressed()
{
    double answer = 0.0;
    QString displayValue = ui->displayLineEdit->text();
    double doubleDisplayValue = displayValue.toDouble();
    if (addPressed || subPressed || multPressed || divPressed){
        if (addPressed){
            answer = currentValue + doubleDisplayValue;
        } else if (subPressed){
            answer = currentValue - doubleDisplayValue;
        } else if (multPressed){
            answer = currentValue * doubleDisplayValue;
        } else{
            answer = currentValue / doubleDisplayValue;
        }
    }
    ui->displayLineEdit->setText(QString::number(answer));
}



void Calculator::on_clear_clicked()
{
    //Have to initialize everything again
    currentValue = 0.0;
    divPressed = false;
    addPressed = false;
    subPressed = false;
    multPressed = false;
    ui->displayLineEdit->setText("");
}

