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
    ui->displayLineEdit->setText(QString::number(currentValue)); //sets the value to 0.0

    QPushButton * numberButtons[10]; // array of 10 for numbers from 0-9

    //
    for (int i = 0; i<10 ; i++)
    {
        QString buttonName = "button"+QString::number(i); //gives button names, names have been declared in qt designer before
        numberButtons[i] = Calculator::findChild<QPushButton *>(buttonName);// finds the buttons in Calculator
        connect (numberButtons[i],SIGNAL(released()), this,
                 SLOT(NumPressed())); //Connecting the released signal to the NumPressed function
    }

    //connect the math operations to the slot
    connect (ui->plus,SIGNAL(released()), this,
             SLOT(MathButtonPressed()));
    connect (ui->minus, SIGNAL(released()),this,
             SLOT(MathButtonPressed()));
    connect (ui->divide, SIGNAL(released()),this,
             SLOT(MathButtonPressed()));
    connect (ui->multiply, SIGNAL(released()),this,
             SLOT(MathButtonPressed()));

    //connect the calculate button to the slot
    connect (ui->equals, SIGNAL(released()),this,
             SLOT(CalculateButtonPressed()));
}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::NumPressed()
{
    QPushButton * button = (QPushButton*)sender();//returns a pointer to the sender of signal, button1......button9
    QString buttonValue = button->text();
    QString displayValue = ui->displayLineEdit->text();
    //check to see if anything other than zero is pressed
    // if it is add it to current value and update new value
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
    //Initially no math operation is selected
    divPressed = false;
    addPressed = false;
    subPressed = false;
    multPressed = false;

    QString displayValue = ui->displayLineEdit->text();
    currentValue = displayValue.toDouble();
    QPushButton *button = (QPushButton * )sender();
    QString buttonValue = button->text();
    //Checks to see which math operation is selected and sets it to true
    if (QString::compare(buttonValue, "/") == 0){
        divPressed = true;
    }else if (QString::compare(buttonValue, "*") == 0){
        multPressed = true;
    }else if (QString::compare(buttonValue, "+") == 0){
        addPressed = true;
    }else subPressed = true;

    ui->displayLineEdit->setText(""); //Empty the calculator for the next number
}

void Calculator::CalculateButtonPressed()
{
    //Initialize the final answer
    double answer = 0.0;
    QString displayValue = ui->displayLineEdit->text();
    double doubleDisplayValue = displayValue.toDouble();
    //If any of the operations is clicked
    //check to see which one is and do the necessary operation
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
    //display the final answer on the calculator
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

