
//Süleyman ALEMDAR
//Mustafa Mert KIZILAY

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Counter değerlerini yükle
    loadButtonCounters();

    // Sinyal-slot bağlantılarını yap
    connect(ui->button1, &QPushButton::clicked, this, &MainWindow::handleButtonClicked);
    connect(ui->button2, &QPushButton::clicked, this, &MainWindow::handleButtonClicked);
    connect(ui->button3, &QPushButton::clicked, this, &MainWindow::handleButtonClicked);
    connect(ui->button4, &QPushButton::clicked, this, &MainWindow::handleButtonClicked);
}

MainWindow::~MainWindow()
{
    // Counter değerlerini kaydet
    saveButtonCounters();
    delete ui;
}

void MainWindow::handleButtonClicked()
{
    QPushButton *clickedButton = qobject_cast<QPushButton*>(sender());
    if (clickedButton)
    {
        int buttonIndex = -1;
        if (clickedButton == ui->button1)
        {
            buttonIndex = 0;
        }
        else if (clickedButton == ui->button2)
        {
            buttonIndex = 1;
        }
        else if (clickedButton == ui->button3)
        {
            buttonIndex = 2;
        }
        else if (clickedButton == ui->button4)
        {
            buttonIndex = 3;
        }

        if (buttonIndex != -1)
        {
            // Counter değerini artır
            if (buttonData[buttonIndex].buttonValue == 255)
            {
                buttonData[buttonIndex].buttonValue = 0;
            }
            else
            {
                buttonData[buttonIndex].buttonValue++;
            }

            // Label'a değeri yaz
            QLabel *label = nullptr;
            if (buttonIndex == 0)
            {
                label = ui->label1;
            }
            else if (buttonIndex == 1)
            {
                label = ui->label2;
            }
            else if (buttonIndex == 2)
            {
                label = ui->label3;
            }
            else if (buttonIndex == 3)
            {
                label = ui->label4;
            }

            if (label)
            {
                label->setText(QString("Buton %1: %2").arg(buttonIndex + 1).arg(buttonData[buttonIndex].buttonValue));
            }
        }
    }
}

void MainWindow::loadButtonCounters()
{
    QFile file("flash.bin");
    if (file.open(QIODevice::ReadOnly))
    {
        QDataStream in(&file);
        for (int i = 0; i < 4; ++i)
        {
            in >> buttonData[i].buttonID;
            in >> buttonData[i].buttonValue;

            QLabel *label = nullptr;
            if (i == 0)
            {
                label = ui->label1;
            }
            else if (i == 1)
            {
                label = ui->label2;
            }
            else if (i == 2)
            {
                label = ui->label3;
            }
            else if (i == 3)
            {
                label = ui->label4;
            }

            if (label)
            {
                label->setText(QString("Buton %1: %2").arg(i + 1).arg(buttonData[i].buttonValue));
            }
        }
        file.close();
    }
}

void MainWindow::saveButtonCounters()
{
    QFile file("flash.bin");
    if (file.open(QIODevice::WriteOnly))
    {
        QDataStream out(&file);
        for (int i = 0; i < 4; ++i)
        {
            out << buttonData[i].buttonID;
            out << buttonData[i].buttonValue;
        }
        file.close();
    }
}

void MainWindow::on_pushButton_set_clicked()
{
    for (int i = 0; i < 4; ++i)
    {
        buttonData[i].buttonValue = 254;

        QLabel *label = nullptr;
        if (i == 0)
        {
            label = ui->label1;
        }
        else if (i == 1)
        {
            label = ui->label2;
        }
        else if (i == 2)
        {
            label = ui->label3;
        }
        else if (i == 3)
        {
            label = ui->label4;
        }

        if (label)
        {
            label->setText(QString("Buton %1: %2").arg(i + 1).arg(buttonData[i].buttonValue));
        }
    }

}

