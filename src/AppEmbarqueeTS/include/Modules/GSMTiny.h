#pragma once
#include <Arduino.h>
#include "Interfaces/IGSM.h"
#include "Configurations.h"
#include "TrackSenseProperties.h"
#include <TinyGsmClient.h>



class GSMTiny : public IGSM
{
private:
    TrackSenseProperties *_trackSenseProperties;
    TinyGsm *modem;

    bool _isInitialized;
    bool _isGpsOn;
    bool _isFixIsValid; // ???

    float _latitude;
    float _longitude;
    float _altitude;
    float _speed;
    int _visibleSatellites;
    int _usedSatellites;
    float _accuracy;
    int _year;
    int _month;
    int _day;
    int _hour;
    int _minute;
    int _seconde;

    int _TEST_counterGoodValue;
    int _TEST_counterTotal;

    String getDate();
    String getTime();
    String getDatetime();

    bool readDatas();
    void gpsPowerOn();
    void gpsPowerOff();
    void gpsRestart();

    bool isFixValid();
    void saveFixToTSProperties();

public:
    GSMTiny(TrackSenseProperties *trackSenseProperties);
    ~GSMTiny();

    void init();
    void tick() override;

};