#ifndef ROUTINE_H
#define ROUTINE_H

#include <QString>
#include <QVector>
#include <QJsonObject>

typedef struct ImuSample{
    float acc_x;
    float acc_y;
    float acc_z;
    float gyro_x;
    float gyro_y;
    float gyro_z;
    float mag_x;
    float mag_y;
    float mag_z;
    long timestamp;
}ImuSample;

typedef struct HeartRateSample{
    float hearRate;
    long timestamp;
}HeartRateSample;

typedef struct TemperatureSample{
    float temperature;
    long timestamp;
}TemperatureSample;

class Routine
{
public:
    QString name;
    QString startDate;

    QVector<ImuSample> imu1Samples;

    QVector<ImuSample> imu2Samples;

    QVector<HeartRateSample> heartRateSamples;

    QVector<TemperatureSample> temperatureSamples;

    Routine();
    Routine(QJsonObject json);
};

#endif // ROUTINE_H
