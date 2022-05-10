#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "line.h"

#include <QPainter>
#include <QColorDialog>
#include <iostream>
#include <math.h>





double firstNum;
bool typingSecondNumber = false;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Graph
    ui->plot->addGraph();
    ui->plot->setInteraction(QCP::iRangeDrag, true);
    ui->plot->setInteraction(QCP::iRangeZoom, true);
    ui->plot->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
    ui->plot->graph(0)->setLineStyle(QCPGraph::lsNone);
    connect(ui->plot, SIGNAL(mouseDoubleClick(QMouseEvent*)), SLOT(clickedGraph(QMouseEvent*)));

    //Equation Manager
    this->equationManager = GraphEquationManager();
    Line firstLine;
    firstLine.calculateFromEquation();
    this->equationManager.addObject(firstLine);


    ui->plot->addGraph();
    ui->plot->graph(0)->setPen(QPen(Qt::blue)); // line color blue
    // generate some points of data (y0 line):
//    QVector<double> x(51), y0(51);
//    for (int i=0; i<points_p->size(); ++i)
//    {
//      x[i] = i;
//      //y0[i] = qExp(-i/15.0)*qCos(i/10.0); // function
//      y0[i] = points_p->at(i);
//    }

    // configure right and top axis to show ticks but no labels:
    // (see QCPAxisRect::setupFullAxesBox for a quicker method to do this)
    ui->plot->xAxis2->setVisible(true);
    ui->plot->xAxis2->setTickLabels(false);
    // make left and bottom axes always transfer their ranges to right and top axes:
    ui->plot->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->plot->xAxis2, SLOT(setRange(QCPRange));
    connect(ui->plot->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->plot->yAxis2, SLOT(setRange(QCPRange)));
    // pass data points to graphs:

    ui->plot->graph(0)->setData(firstLine.xPoints,firstLine.yPoints);
    // let the ranges scale themselves so graph 0 fits perfectly in the visible area:
    ui->plot->graph(0)->rescaleAxes();


    //Calculator
    connect(ui->button_0, SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->button_1, SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->button_2, SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->button_3, SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->button_4, SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->button_5, SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->button_6, SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->button_7, SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->button_8, SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->button_9, SIGNAL(released()),this,SLOT(digit_pressed()));

    connect(ui->plus_minus, SIGNAL(released()),this,SLOT(unary_operation_pressed()));
    connect(ui->percent, SIGNAL(released()),this,SLOT(unary_operation_pressed()));
    connect(ui->sqrt, SIGNAL(released()),this,SLOT(unary_operation_pressed()));
    connect(ui->power, SIGNAL(released()),this,SLOT(unary_operation_pressed()));
    connect(ui->frac, SIGNAL(released()),this,SLOT(unary_operation_pressed()));

     connect(ui->plus, SIGNAL(released()),this,SLOT(binary_operation_pressed()));
     connect(ui->minus, SIGNAL(released()),this,SLOT(binary_operation_pressed()));
     connect(ui->divide, SIGNAL(released()),this,SLOT(binary_operation_pressed()));
     connect(ui->mult, SIGNAL(released()),this,SLOT(binary_operation_pressed()));

     ui->plus->setCheckable(true);
     ui->minus->setCheckable(true);
     ui->divide->setCheckable(true);
     ui->mult->setCheckable(true);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addPoint(double x, double y)
{
    vec_x.append(x);
    vec_y.append(y);

}

void MainWindow::clearData()
{
    vec_x.clear();
    vec_y.clear();
}

void MainWindow::plot()
{
    ui->plot->graph(0)->setData(vec_x, vec_y);
    ui->plot->replot();
    ui->plot->update();

}

void MainWindow::on_add_clicked()
{
    addPoint(ui->x_coord->value(), ui->y_coord->value());
    plot();
}

void MainWindow::on_clear_clicked()
{
    clearData();
    plot();
}

void MainWindow::digit_pressed()
{
    QPushButton * button = (QPushButton*)sender();
        double labelNumber;
        QString newLabel;

        if((ui->plus->isChecked() || ui->minus->isChecked() ||
            ui->mult->isChecked()  || ui->divide->isChecked()) && (!typingSecondNumber))
        {
            labelNumber = button->text().toDouble();
            typingSecondNumber = true;
            newLabel = QString::number(labelNumber, 'g', 15);
        }

        else
        {
            if(ui->label_cal->text().contains('.') && button->text() == "0")
            {
                newLabel = ui->label_cal->text() + button->text();
            }
            else
            {
                 labelNumber = (ui->label_cal->text() + button->text()).toDouble();
                 newLabel = QString::number(labelNumber, 'g', 15);
             }
         }
         ui->label_cal->setText(newLabel);
}

void MainWindow::on_decimal_released()
{
        ui->label_cal->setText(ui->label_cal->text() + ".");
}

void MainWindow::unary_operation_pressed()
{
        QPushButton * button = (QPushButton*) sender();
        double labelNumber;
        QString newLabel;

        if (button->text() == "+/-")
        {
            labelNumber = ui->label_cal->text().toDouble();
            labelNumber = labelNumber * -1;
            newLabel = QString::number(labelNumber, 'g', 15);
            ui->label_cal->setText(newLabel);
        }
        if (button->text() == "%")
        {
            labelNumber = ui->label_cal->text().toDouble();
            labelNumber = labelNumber * 0.01;
            newLabel = QString::number(labelNumber, 'g', 15);
            ui->label_cal->setText(newLabel);
        }
        if (button->text() == "Sqrt")
        {
            labelNumber = ui->label_cal->text().toDouble();
            labelNumber = sqrt(labelNumber);
            newLabel = QString::number(labelNumber, 'g', 15);
            ui->label_cal->setText(newLabel);
        }
        if (button->text() == "x^2")
        {
            labelNumber = ui->label_cal->text().toDouble();
            labelNumber = pow(labelNumber, 2);
            newLabel = QString::number(labelNumber, 'g', 15);
            ui->label_cal->setText(newLabel);
        }
        if (button->text() == "1/x")
        {
            labelNumber = ui->label_cal->text().toDouble();
            labelNumber = (1.0) / (labelNumber);
            newLabel = QString::number(labelNumber, 'g', 15);
            ui->label_cal->setText(newLabel);
        }
}

void MainWindow::on_clear_cal_released()
{
    ui->plus->setChecked(false);
    ui->minus->setChecked(false);
    ui->mult->setChecked(false);
    ui->divide->setChecked(false);

    typingSecondNumber = false;
    ui->label_cal->setText("0");
}

void MainWindow::on_equal_released()
{
    double labelNumber, secondNum;
    QString newLabel;

    secondNum = ui->label_cal->text().toDouble();

    if (ui->plus->isChecked())
    {
        labelNumber = firstNum + secondNum;
        newLabel = QString::number(labelNumber, 'g', 15);
        ui->label_cal->setText(newLabel);
        ui->plus->setChecked(false);
    }
    else if (ui->minus->isChecked())
    {
        labelNumber = firstNum - secondNum;
        newLabel = QString::number(labelNumber, 'g', 15);
        ui->label_cal->setText(newLabel);
        ui->minus->setChecked(false);
    }
    else if (ui->mult->isChecked())
    {
        labelNumber = firstNum * secondNum;
        newLabel = QString::number(labelNumber, 'g', 15);
        ui->label_cal->setText(newLabel);
        ui->mult->setChecked(false);
    }
    else if (ui->divide->isChecked())
    {
        labelNumber = firstNum / secondNum;
        newLabel = QString::number(labelNumber, 'g', 15);
        ui->label_cal->setText(newLabel);
        ui->divide->setChecked(false);
    }
    typingSecondNumber = false;
}

void MainWindow::binary_operation_pressed()
{
    QPushButton * button = (QPushButton*) sender();
    firstNum = ui->label_cal->text().toDouble();
    button->setCheckable(true);
}

void MainWindow::on_GraphButton_clicked()
{

    double intercept = ui->interceptInput->text().toDouble();
    double slope = ui->slopeInput->text().toDouble();
    qInfo() << "slope" << slope;
    qInfo() << " intercept" << intercept;
    Line line(slope,intercept);
    line.calculateFromEquation();
    qInfo() << line.xPoints.size();
    qInfo() << line.yPoints.size();
    ui->plot->graph(0)->setData(line.xPoints,line.yPoints);
    ui->plot->replot();
    ui->plot->update();

}
