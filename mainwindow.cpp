#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QJsonArray>
#include <math.h>
#include <QDebug>
#include <QJsonDocument>
#include <QMessageBox>
#include <chartwidget.h>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    generateExample2();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_open_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open File"),
                                                    "",
                                                    tr("Json File (*.json)"));
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::information(this, "", "No se pudo abrir el archivo.\n");
    }
    QByteArray saveData = file.readAll();
    file.close();
    QJsonParseError jsonError;
    QJsonDocument jsonDocument(QJsonDocument::fromJson(saveData, &jsonError));
    if(jsonError.error != QJsonParseError::NoError)
    {
        QMessageBox::information(this, "", "Error de archivo.\n");
        return;
    }
    QJsonObject json = jsonDocument.object();
    qDebug()<<fileName + " loaded!";

    routine = new Routine(json);

    ChartWidget * chartWidget = new ChartWidget(json);
    ui->gridLayout_chart->addWidget(chartWidget);

//    qDebug()<<"Imu1 samples: "<<routine->imu1.count();
//    qDebug()<<"Imu2 samples: "<<routine->imu2.count();
//    qDebug()<<"Temperature samples: "<<routine->temperature.count();
//    qDebug()<<"heart rate samples: "<<routine->heartRate.count();

//    fillChart();
}

void MainWindow::fillChart()
{
//    imu1Serie = new QLineSeries();
//    imu2Serie = new QLineSeries();
//    temperatureSerie = new QLineSeries();
//    hrSerie = new QLineSeries();

//    for(int i = 0; i < routine->imu1.count() ; i++)
//    {
//        imu1Serie->append(routine->imu1Timestamps[i],routine->imu1[i]);
//    }

//    for(int i = 0; i < routine->imu2.count() ; i++)
//    {
//        imu2Serie->append(routine->imu2Timestamps[i],routine->imu2[i]);
//    }

//    for(int i = 0; i < routine->temperature.count() ; i++)
//    {
//        temperatureSerie->append(routine->tempTimestamps[i],routine->temperature[i]);
//    }

//    for(int i = 0; i < routine->heartRate.count() ; i++)
//    {
//        hrSerie->append(routine->hrTimestamps[i],routine->heartRate[i]);
//    }

//    axisX = new QDateTimeAxis;
//    axisX->setTickCount(20);
//    axisX->setFormat("mm:ss");
//    axisX->setTitleText("Día");
//    //axisX->setRange(QDateTime::fromMSecsSinceEpoch(0),QDateTime::fromMSecsSinceEpoch(routine->imu1Timestamps[routine->imu1Timestamps.count()-1]));
//    axisX->setRange(QDateTime::fromMSecsSinceEpoch(0),QDateTime::fromMSecsSinceEpoch(60*1000));



//    axisY = new QValueAxis;
////    axisY->setLabelFormat("%.2f");
////    axisY->setTickType(QValueAxis::TicksDynamic);
//    axisY->setTickAnchor(.1);
//    axisY->setTickInterval(.1);
//    axisY->setTitleText("Value");
//    axisY->setMax(10);
//    axisY->setMin(-10);

//    chart = new Chart();
//    chart->setAnimationOptions(QChart::NoAnimation);

//    this->grabGesture(Qt::PanGesture);
//    this->grabGesture(Qt::PinchGesture);
//    chart->addAxis(axisX,Qt::AlignBottom);
//    chart->addAxis(axisY,Qt::AlignLeft);

//    chart->addSeries(imu1Serie);
//    imu1Serie->setPointsVisible(true);
//    chart->addSeries(imu2Serie);
////    chart->addSeries(&temperatureSerie);
////    chart->addSeries(&hrSerie);

//    imu1Serie->attachAxis(axisX);
//    imu1Serie->attachAxis(axisY);
//    imu1Serie->setUseOpenGL(true);

//    imu2Serie->attachAxis(axisX);
//    imu2Serie->attachAxis(axisY);

////    temperatureSerie->attachAxis(axisX);
////    temperatureSerie->attachAxis(axisY);

////    hrSerie->attachAxis(axisX);
////    hrSerie->attachAxis(axisY);

//    chartView = new ChartView(chart);
//    chartView->setRenderHint(QPainter::Antialiasing);
//    chartView->setOptimizationFlag(QGraphicsView::DontAdjustForAntialiasing);
//    ui->gridLayout_chart->addWidget(chartView);
//    chartView->show();

}


void MainWindow::generateExample()
{
    QJsonObject routine;
    QJsonArray imuSamples;
    QJsonArray imu2Samples;
    QJsonArray tempSamples;
    QJsonArray heartRateSamples;

    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    int timeStamp = 0;
    for(int i = 0; i < 36000; i++)
    {
        QJsonObject sample;
        timeStamp += 33;
        sample["timestamp"] = timeStamp;

        QJsonObject imuSample = {
            {"acc",cos(i)},
            {"acc",cos(i)},
            {"acc",cos(i)}
        };
        sample["value"] = cos(i);
        imuSamples.append(sample);

        sample["value"]= (sin(i));
        imu2Samples.append(sample);

        sample["value"]= (2*cos(i)+1.05);
        tempSamples.append(sample);

        sample["value"]= (qrand()%10 + 70);
        heartRateSamples.append(sample);
    }

    routine["startTime"] = "23/04/2022 13:25";
    routine["name"] = "test";
    routine["device"] = "raspberry1";

    QJsonObject samples
        {
            {"imu1", imuSamples},
            {"imu2", imu2Samples},
            {"temperature",tempSamples},
            {"hearRate",heartRateSamples}
        };

    routine["samples"] = samples;
    saveJson(routine);

}

void MainWindow::generateExample2()
{
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

    QJsonArray acc1x;
    QJsonArray acc1y;
    QJsonArray acc1z;

    QJsonArray acc2x;
    QJsonArray acc2y;
    QJsonArray acc2z;

    QJsonArray gyro1x;
    QJsonArray gyro1y;
    QJsonArray gyro1z;

    QJsonArray timeStamps1;

    QJsonArray gyro2x;
    QJsonArray gyro2y;
    QJsonArray gyro2z;

    QJsonArray mag1x;
    QJsonArray mag1y;
    QJsonArray mag1z;

    QJsonArray mag2x;
    QJsonArray mag2y;
    QJsonArray mag2z;

    QJsonArray timeStamps2;

    QJsonArray temperature;
    QJsonArray timeStampsTemp;

    QJsonArray heartRate;
    QJsonArray timeStampsHr;

    int time = 0;

    for(int i = 0; i < 200; i++){
        acc1x.append(cos(i));
        acc1y.append(cos(i)+1);
        acc1z.append(cos(i)+2);

        acc2x.append(sin(i));
        acc2y.append(sin(i)+1);
        acc2z.append(sin(i)+2);

        gyro1x.append(cos(i+1));
        gyro1y.append(cos(i+2));
        gyro1z.append(cos(i+3));

        gyro2x.append(sin(i+1));
        gyro2y.append(sin(i+2));
        gyro2z.append(sin(i+3));

        mag1x.append(cos(i+1));
        mag1y.append(cos(i+1));
        mag1z.append(cos(i+1));

        mag2x.append(cos(i+1));
        mag2y.append(cos(i+1));
        mag2z.append(cos(i+1));

        timeStamps1.append(time);
        timeStamps2.append(time+1);
        time+=33;
    }

    time = 0;
    for(int i = 0; i < 1200; i++){
        temperature.append(qrand()%10 + 30);
        heartRate.append(qrand()%10 + 70);
        timeStampsTemp.append(time);
        timeStampsHr.append(time);
        time+=1000;
    }


    QJsonObject imu_back = {
        {"acc_x",acc1x},
        {"acc_y",acc1y},
        {"acc_z",acc1z},

        {"gyro_x",gyro1x},
        {"gyro_y",gyro1y},
        {"gyro_z",gyro1z},

        {"mag_x",mag1x},
        {"mag_y",mag1y},
        {"mag_z",mag1z},

        {"timestamps",timeStamps1}
    };

    QJsonObject imu_tail = {
        {"acc_x",acc2x},
        {"acc_y",acc2y},
        {"acc_z",acc2z},

        {"gyro_x",gyro2x},
        {"gyro_y",gyro2y},
        {"gyro_z",gyro2z},

        {"mag_x",mag2x},
        {"mag_y",mag2y},
        {"mag_z",mag2z},

        {"timestamps",timeStamps2}
    };

    QJsonObject temperatureJson = {
        {"samples",temperature},
        {"timestamps",timeStampsTemp}
    };

    QJsonObject heartRateJson = {
        {"samples",heartRate},
        {"timestamps",timeStampsHr}
    };

    QJsonObject json ={
        {"imu_back",imu_back},
        {"imu_tail",imu_tail},
        {"temperature",temperatureJson},
        {"heart_rate",heartRateJson}
    };

    saveJson(json);
}

bool MainWindow::saveJson(QJsonObject &json)
{
    QFile file("test.json");
    if (!file.open(QIODevice::WriteOnly))
    {
        qDebug()<<"Failed to save json";
        file.close();
        return false;
    }
    if(file.write(QJsonDocument(json).toJson(QJsonDocument::Indented)) == -1 )
    {
        qDebug()<<"Failed to save json";
        file.close();
        return false;
    }
    file.close();
    qDebug()<<"File created in "<<file;
    return true;
}

void MainWindow::on_checkBox_imu1_clicked()
{

}

