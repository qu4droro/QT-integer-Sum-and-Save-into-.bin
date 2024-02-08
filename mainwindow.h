#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QFile>
#include <QDataStream>
#include <QVBoxLayout>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void handleButtonClicked();

    void on_pushButton_set_clicked();

private:
    void loadButtonCounters();
    void saveButtonCounters();

    Ui::MainWindow *ui;
    struct ButtonData {
        uint16_t buttonID;
        uint8_t buttonValue;
    };
    ButtonData buttonData[4];
};

#endif // MAINWINDOW_H
