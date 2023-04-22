#ifndef CHARTWIDGET_H
#define CHARTWIDGET_H

#include "routine.h"
#include "chart.h"
#include "chartview.h"

#include <QWidget>
#include <QJsonObject>
#include <QtCharts>
#include <QLineSeries>
#include <QMainWindow>

namespace Ui {
class ChartWidget;
}

class ChartWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ChartWidget(QJsonObject json, QWidget *parent = nullptr);
    ~ChartWidget();

private slots:
    void on_checkBox_acc1x_clicked();

    void on_checkBox_acc1y_clicked();

    void on_checkBox_acc1z_clicked();

    void on_checkBox_acc1v_clicked();

    void on_checkBox_gyro1x_clicked();

    void on_checkBox_mag1x_clicked();

    void on_checkBox_mag1y_clicked();

    void on_checkBox_mag1z_clicked();

    void on_checkBox_mag1v_clicked();

    void on_checkBox_gyro1y_clicked();

    void on_checkBox_gyro1z_clicked();

    void on_checkBox_gyro1v_clicked();

private:
    Ui::ChartWidget *ui;

    Routine *routine;

    QVector<QLineSeries*> acc1;
    QVector<QLineSeries*> gyro1;
    QVector<QLineSeries*> mag1;

    QVector<QLineSeries*> acc2;
    QVector<QLineSeries*> gyro2;
    QVector<QLineSeries*> mag2;

    QLineSeries *temperature;
    QLineSeries *heartRate;
    QLineSeries *sound;

    QVector<QLineSeries*> allSeries;

    QDateTimeAxis *axisX;
    QValueAxis *accAxis;
    QValueAxis *gyroAxis;
    QValueAxis *magAxis;
    QValueAxis *temperatureAxis;
    QValueAxis *heartRateAxis;
    QValueAxis *soundAxis;

    Chart *chart;
    ChartView *chartView;

    void iniChart();
    void fillSeries();
};

#endif // CHARTWIDGET_H
