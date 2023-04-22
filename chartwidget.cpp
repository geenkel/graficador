#include "chartwidget.h"
#include "ui_chartwidget.h"

ChartWidget::ChartWidget(QJsonObject json, QWidget *parent)
    : QWidget(parent), ui(new Ui::ChartWidget)
{
    ui->setupUi(this);

    routine = new Routine(json);
    fillSeries();
    iniChart();    
}

ChartWidget::~ChartWidget()
{
    delete ui;
}

void ChartWidget::fillSeries()
{
    //IMU1

    QLineSeries *serieAccX = new QLineSeries();
    QLineSeries *serieAccY = new QLineSeries();
    QLineSeries *serieAccZ = new QLineSeries();
    QLineSeries *serieGyroX = new QLineSeries();
    QLineSeries *serieGyroY = new QLineSeries();
    QLineSeries *serieGyroZ = new QLineSeries();
    QLineSeries *serieMagX = new QLineSeries();
    QLineSeries *serieMagY = new QLineSeries();
    QLineSeries *serieMagZ = new QLineSeries();
    for (int i = 0; i < routine->imu1Samples.count(); i++) {
        serieAccX->append(routine->imu1Samples[i].timestamp, routine->imu2Samples[i].acc_x);
        serieAccY->append(routine->imu1Samples[i].timestamp, routine->imu2Samples[i].acc_y);
        serieAccZ->append(routine->imu1Samples[i].timestamp, routine->imu2Samples[i].acc_z);

        serieGyroX->append(routine->imu1Samples[i].timestamp, routine->imu2Samples[i].acc_x);
        serieGyroY->append(routine->imu1Samples[i].timestamp, routine->imu2Samples[i].acc_y);
        serieGyroZ->append(routine->imu1Samples[i].timestamp, routine->imu2Samples[i].acc_z);

        serieMagX->append(routine->imu1Samples[i].timestamp, routine->imu2Samples[i].acc_x);
        serieMagY->append(routine->imu1Samples[i].timestamp, routine->imu2Samples[i].acc_y);
        serieMagZ->append(routine->imu1Samples[i].timestamp, routine->imu2Samples[i].acc_z);
    }
    acc1.append(serieAccX);
    acc1.append(serieAccY);
    acc1.append(serieAccZ);

    gyro1.append(serieGyroX);
    gyro1.append(serieGyroY);
    gyro1.append(serieGyroZ);

    mag1.append(serieMagX);
    mag1.append(serieMagY);
    mag1.append(serieMagZ);

    //IMU2

    QLineSeries *serie2AccX = new QLineSeries();
    QLineSeries *serie2AccY = new QLineSeries();
    QLineSeries *serie2AccZ = new QLineSeries();
    QLineSeries *serie2GyroX = new QLineSeries();
    QLineSeries *serie2GyroY = new QLineSeries();
    QLineSeries *serie2GyroZ = new QLineSeries();
    QLineSeries *serie2MagX = new QLineSeries();
    QLineSeries *serie2MagY = new QLineSeries();
    QLineSeries *serie2MagZ = new QLineSeries();
    for (int i = 0; i < routine->imu2Samples.count(); i++) {
        serie2AccX->append(routine->imu2Samples[i].timestamp, routine->imu2Samples[i].acc_x);
        serie2AccY->append(routine->imu2Samples[i].timestamp, routine->imu2Samples[i].acc_y);
        serie2AccZ->append(routine->imu2Samples[i].timestamp, routine->imu2Samples[i].acc_z);

        serie2GyroX->append(routine->imu2Samples[i].timestamp, routine->imu2Samples[i].acc_x);
        serie2GyroY->append(routine->imu2Samples[i].timestamp, routine->imu2Samples[i].acc_y);
        serie2GyroZ->append(routine->imu2Samples[i].timestamp, routine->imu2Samples[i].acc_z);

        serie2MagX->append(routine->imu2Samples[i].timestamp, routine->imu2Samples[i].acc_x);
        serie2MagY->append(routine->imu2Samples[i].timestamp, routine->imu2Samples[i].acc_y);
        serie2MagZ->append(routine->imu2Samples[i].timestamp, routine->imu2Samples[i].acc_z);
    }
    acc2.append(serie2AccX);
    acc2.append(serie2AccY);
    acc2.append(serie2AccZ);

    gyro2.append(serie2GyroX);
    gyro2.append(serie2GyroY);
    gyro2.append(serie2GyroZ);

    mag2.append(serie2MagX);
    mag2.append(serie2MagY);
    mag2.append(serie2MagZ);

    //Temperatura
    temperature = new QLineSeries();
    for (int i = 0; i < routine->temperatureSamples.count(); i++) {
        temperature->append(routine->temperatureSamples[i].timestamp,
                           routine->temperatureSamples[i].temperature);
    }

    //Heart rate
    heartRate = new QLineSeries();
    for (int i = 0; i < routine->heartRateSamples.count(); i++) {
        heartRate->append(routine->heartRateSamples[i].timestamp,
                         routine->heartRateSamples[i].hearRate);
    }

    allSeries.append(acc1[0]);
    allSeries.append(acc1[1]);
    allSeries.append(acc1[2]);
    allSeries.append(gyro1[0]);
    allSeries.append(gyro1[1]);
    allSeries.append(gyro1[2]);
    allSeries.append(mag1[0]);
    allSeries.append(mag1[1]);
    allSeries.append(mag1[2]);

    allSeries.append(acc2[0]);
    allSeries.append(acc2[1]);
    allSeries.append(acc2[2]);
    allSeries.append(gyro2[0]);
    allSeries.append(gyro2[1]);
    allSeries.append(gyro2[2]);
    allSeries.append(mag2[0]);
    allSeries.append(mag2[1]);
    allSeries.append(mag2[2]);

    allSeries.append(temperature);
    allSeries.append(heartRate);
}

void ChartWidget::iniChart()
{
    axisX = new QDateTimeAxis;
    //accAxis->setTickType(QValueAxis::TicksFixed);
    axisX->setTickCount(10);
    axisX->setFormat("mm:ss");
    axisX->setTitleText("Tiempo");
    //axisX->setRange(QDateTime::fromMSecsSinceEpoch(0),QDateTime::fromMSecsSinceEpoch(routine->imu1Timestamps[routine->imu1Timestamps.count()-1]));
    axisX->setRange(QDateTime::fromMSecsSinceEpoch(0), QDateTime::fromMSecsSinceEpoch(60 * 1000));

    accAxis = new QValueAxis;
    //    axisY->setLabelFormat("%.2f");
    //    axisY->setTickType(QValueAxis::TicksDynamic);
    accAxis->setTickType(QValueAxis::TicksFixed);
    accAxis->setTickCount(10);
//    accAxis->setTickAnchor(.1);
//    accAxis->setTickInterval(.1);
    accAxis->setTitleText("Aceleración");
    accAxis->setMax(10);
    accAxis->setMin(-10);

    gyroAxis = new QValueAxis;
    gyroAxis->setTickAnchor(.1);
    gyroAxis->setTickInterval(.1);
    gyroAxis->setTitleText("Velocidad Angular");
    gyroAxis->setMax(10);
    gyroAxis->setMin(-10);

    magAxis = new QValueAxis;
    magAxis->setTickAnchor(.1);
    magAxis->setTickInterval(.1);
    magAxis->setTitleText("Magnitud");
    magAxis->setMax(10);
    magAxis->setMin(-10);

    temperatureAxis = new QValueAxis();
    temperatureAxis->setTickAnchor(.1);
    temperatureAxis->setTickInterval(.1);
    temperatureAxis->setTitleText("Temperatura °C");
    temperatureAxis->setMax(10);
    temperatureAxis->setMin(-10);

    heartRateAxis = new QValueAxis;
    heartRateAxis->setTickAnchor(.1);
    heartRateAxis->setTickInterval(.1);
    heartRateAxis->setTitleText("HR");
    heartRateAxis->setMax(10);
    heartRateAxis->setMin(-10);

    chart = new Chart();
    chart->setAnimationOptions(QChart::NoAnimation);

    this->grabGesture(Qt::PanGesture);
    this->grabGesture(Qt::PinchGesture);
    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(accAxis, Qt::AlignLeft);

    for(int i = 0; i < allSeries.count(); i++)
    {
        chart->addSeries(allSeries[i]);
        allSeries[i]->setPointsVisible(true);
        allSeries[i]->setVisible(false);
    }

    for(int i = 0; i < 3; i++){
        acc1[i]->attachAxis(axisX);
        acc1[i]->attachAxis(accAxis);

        acc2[i]->attachAxis(axisX);
        acc2[i]->attachAxis(accAxis);

        gyro1[i]->attachAxis(axisX);
        gyro1[i]->attachAxis(gyroAxis);

        gyro2[i]->attachAxis(axisX);
        gyro2[i]->attachAxis(gyroAxis);

        mag1[i]->attachAxis(axisX);
        mag1[i]->attachAxis(magAxis);

        mag2[i]->attachAxis(axisX);
        mag2[i]->attachAxis(magAxis);
    }

    temperature->attachAxis(axisX);
    temperature->attachAxis(temperatureAxis);

    heartRate->attachAxis(axisX);
    heartRate->attachAxis(heartRateAxis);

    acc1[0]->setVisible(true);

//    chart->addSeries(acc1[0]);
//    chart->addSeries(acc1[1]);
//    chart->addSeries(acc1[2]);

//    chart->addSeries(acc2[0]);
//    chart->addSeries(acc2[1]);
//    chart->addSeries(acc2[2]);

//    chart->addSeries(gyro1[0]);
//    chart->addSeries(gyro1[1]);
//    chart->addSeries(gyro1[2]);

//    chart->addSeries(gyro2[0]);
//    chart->addSeries(gyro2[1]);
//    chart->addSeries(gyro2[2]);

//    chart->addSeries(mag1[0]);
//    chart->addSeries(mag1[1]);
//    chart->addSeries(mag1[2]);

//    chart->addSeries(mag2[0]);
//    chart->addSeries(mag2[1]);
//    chart->addSeries(mag2[2]);

//    chart->addSeries(temperature);
//    chart->addSeries(heartRate);

    chartView = new ChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setOptimizationFlag(QGraphicsView::DontAdjustForAntialiasing);
    ui->gridLayout_chart->addWidget(chartView);
    chartView->show();
}

void ChartWidget::on_checkBox_acc1x_clicked() {
    acc1[0]->setVisible(ui->checkBox_acc1x->isChecked());
    accAxis->applyNiceNumbers();
}

void ChartWidget::on_checkBox_acc1y_clicked()
{
    acc1[1]->setVisible(ui->checkBox_acc1y->isChecked());
    accAxis->applyNiceNumbers();
}


void ChartWidget::on_checkBox_acc1z_clicked()
{
    acc1[2]->setVisible(ui->checkBox_acc1z->isChecked());
    accAxis->applyNiceNumbers();
}


void ChartWidget::on_checkBox_acc1v_clicked()
{

}


void ChartWidget::on_checkBox_gyro1x_clicked()
{
    gyro1[0]->setVisible(ui->checkBox_gyro1x->isChecked());
    gyroAxis->applyNiceNumbers();
}


void ChartWidget::on_checkBox_gyro1y_clicked()
{
    gyro1[1]->setVisible(ui->checkBox_gyro1y->isChecked());
    gyroAxis->applyNiceNumbers();
}


void ChartWidget::on_checkBox_gyro1z_clicked()
{
    gyro1[2]->setVisible(ui->checkBox_gyro1z->isChecked());
    gyroAxis->applyNiceNumbers();
}


void ChartWidget::on_checkBox_gyro1v_clicked()
{

}


void ChartWidget::on_checkBox_mag1x_clicked()
{
    mag1[0]->setVisible(ui->checkBox_mag1x->isChecked());
}


void ChartWidget::on_checkBox_mag1y_clicked()
{
    mag1[1]->setVisible(ui->checkBox_mag1y->isChecked());
}


void ChartWidget::on_checkBox_mag1z_clicked()
{
    mag1[2]->setVisible(ui->checkBox_mag1z->isChecked());
}


void ChartWidget::on_checkBox_mag1v_clicked()
{

}

