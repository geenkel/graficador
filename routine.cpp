#include "routine.h"

#include <QJsonArray>
#include <QDebug>

Routine::Routine()
{


}

Routine::Routine(QJsonObject json)
{

    QJsonObject imu1 = json["imu_back"].toObject();
    QJsonObject imu2 = json["imu_tail"].toObject();
    QJsonObject temperatureJson = json["temperature"].toObject();
    QJsonObject heartRateJson = json["heart_rate"].toObject();

    QJsonArray acc1x = imu1["acc_x"].toArray();
    QJsonArray acc1y = imu1["acc_y"].toArray();
    QJsonArray acc1z = imu1["acc_z"].toArray();

    QJsonArray acc2x = imu2["acc_x"].toArray();
    QJsonArray acc2y = imu2["acc_y"].toArray();
    QJsonArray acc2z = imu2["acc_z"].toArray();

    QJsonArray gyro1x = imu1["gyro_x"].toArray();
    QJsonArray gyro1y = imu1["gyro_y"].toArray();
    QJsonArray gyro1z = imu1["gyro_z"].toArray();

    QJsonArray gyro2x = imu1["gyro_x"].toArray();
    QJsonArray gyro2y = imu2["gyro_y"].toArray();
    QJsonArray gyro2z = imu2["gyro_z"].toArray();

    QJsonArray mag1x = imu1["mag_x"].toArray();;
    QJsonArray mag1y = imu1["mag_y"].toArray();
    QJsonArray mag1z = imu1["mag_z"].toArray();

    QJsonArray mag2x = imu2["mag_x"].toArray();
    QJsonArray mag2y = imu2["mag_y"].toArray();
    QJsonArray mag2z = imu2["mag_z"].toArray();

    QJsonArray timeStamps1 = imu1["timestamps"].toArray();

    QJsonArray timeStamps2 = imu2["timestamps"].toArray();

    QJsonArray temperature = temperatureJson["samples"].toArray();
    QJsonArray timeStampsTemp = temperatureJson["timestamps"].toArray();

    QJsonArray heartRate = heartRateJson["samples"].toArray();
    QJsonArray timeStampsHr = heartRateJson["timestamps"].toArray();

    qDebug()<<"timeStamps1 "<<timeStamps1.count();
    qDebug()<<"acc1x "<<acc1x.count();
    qDebug()<<"acc_y "<<acc1y.count();
    qDebug()<<"acc_z "<<acc1z.count();
    qDebug()<<"gyro_x "<<gyro1x.count();
    qDebug()<<"gyro_y "<<gyro1y.count();
    qDebug()<<"gyro_z "<<gyro1z.count();


    for(int i = 0; i < timeStamps1.count(); i++)
    {
        ImuSample sample;
        sample.acc_x = acc1x[i].toDouble();
        sample.acc_y = acc1y[i].toDouble();
        sample.acc_z = acc1z[i].toDouble();

        sample.gyro_x = gyro1x[i].toDouble();
        sample.gyro_y = gyro1y[i].toDouble();
        sample.gyro_z = gyro1z[i].toDouble();

        sample.mag_x = mag1x[i].toDouble();
        sample.mag_y = mag1y[i].toDouble();
        sample.mag_z = mag1z[i].toDouble();

        sample.timestamp = timeStamps1[i].toInt();

        imu1Samples.append(sample);
    }

    qDebug()<<"2";

    for(int i = 0; i < timeStamps2.count(); i++)
    {
        ImuSample sample;
        sample.acc_x = acc2x[i].toDouble();
        sample.acc_y = acc2y[i].toDouble();
        sample.acc_z = acc2z[i].toDouble();

        sample.gyro_x = gyro2x[i].toDouble();
        sample.gyro_y = gyro2y[i].toDouble();
        sample.gyro_z = gyro2z[i].toDouble();

        sample.mag_x = mag2x[i].toDouble();
        sample.mag_y = mag2y[i].toDouble();
        sample.mag_z = mag2z[i].toDouble();
        sample.timestamp = timeStamps2[i].toInt();
        imu2Samples.append(sample);
    }

    qDebug()<<"3";

    for(int i = 0; i < timeStampsTemp.count(); i++)
    {
        TemperatureSample sample;
        sample.temperature = temperature[i].toDouble();
        sample.timestamp = timeStampsTemp[i].toInt();
        temperatureSamples.append(sample);
    }

    qDebug()<<"4";

    for(int i = 0; i < timeStampsHr.count(); i++)
    {
        HeartRateSample sample;
        sample.hearRate = heartRate[i].toDouble();
        sample.timestamp = timeStampsHr[i].toInt();
        heartRateSamples.append(sample);
    }


//    QJsonArray imuSamples = json["samples"].toObject()["imu1"].toArray();
//    QJsonArray imu2Samples = json["samples"].toObject()["imu2"].toArray();
//    QJsonArray tempSamples = json["samples"].toObject()["temperature"].toArray();
//    QJsonArray heartRateSamples = json["samples"].toObject()["heartRate"].toArray();

//    for(int i = 0; i < imuSamples.count(); i++)
//    {
//        imu1.append(imuSamples[i].toObject()["value"].toDouble(0));
//        imu1Timestamps.append(imuSamples[i].toObject()["timestamp"].toInt());
//    }
//    for(int i = 0; i < imu2Samples.count(); i++)
//    {
//        imu2.append(imu2Samples[i].toObject()["value"].toDouble(0));
//        imu2Timestamps.append(imu2Samples[i].toObject()["timestamp"].toInt());
//    }
//    for(int i = 0; i < tempSamples.count(); i++)
//    {
//        temperature.append(tempSamples[i].toObject()["value"].toDouble(0));
//        tempTimestamps.append(tempSamples[i].toObject()["timestamp"].toInt());
//    }
//    for(int i = 0; i < heartRateSamples.count(); i++)
//    {
//        heartRate.append(heartRateSamples[i].toObject()["value"].toInt(0));
//        hrTimestamps.append(heartRateSamples[i].toObject()["timestamp"].toInt());
//    }
}
