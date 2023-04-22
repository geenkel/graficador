#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "routine.h"
#include "chart.h"
#include "chartview.h"

#include <QJsonObject>
#include <QLineSeries>
#include <QMainWindow>
#include <QtCharts>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_open_clicked();

    void on_checkBox_imu1_clicked();

private:
    Ui::MainWindow *ui;

    QLineSeries *imu1Serie;
    QLineSeries *imu2Serie;
    QLineSeries *temperatureSerie;
    QLineSeries *hrSerie;

    Routine *routine;

    void fillChart();
    void generateExample();
    void generateExample2();
    bool saveJson(QJsonObject &json);

    QDateTimeAxis *axisX;
    QValueAxis *axisY;

    Chart *chart;
    ChartView *chartView;

};
#endif // MAINWINDOW_H
