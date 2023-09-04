#pragma once
#include <Arduino.h>
#include "TrackSenseProperties.h"

class TrackSenseProperties
{
public:

    /* Datas TrackSense */
    struct TrackSensePropertiesTS
    {
        bool _isRideStarted;
        bool _isRidePaused;
        bool _isRideFinished;
        // bool _isRideSaved;
        // bool _isRideDeleted;

        String _currentRideId;



        // VRAIMENT NECESSAIRE ?? //
        // bool _isWIFIConnected;
        // bool _isBluetoothConnected;
        // bool _isLTEConnected;
        // bool _isSDCardConnected;
        // bool _isScreenConnected;
        // bool _isGPSConnected;
        // bool _isCompassConnected;
        // bool _isGyroscopeConnected;
        // bool _isAccelerometerConnected;
        // bool _isTemperatureConnected;
        // bool _isBatteryConnected;
        // bool _isButton1Connected;
        // bool _isButton2Connected;
        // bool _isBuzzerConnected;
    } PropertiesTS;


    /* datas Buttons */
    struct TrackSensePropertiesButton
    {
        // bool _isButton1Pressed;
        // bool _isButton2Pressed;
        int _TEST_Button1State;
        int _TEST_Button2State;
    } PropertiesButtons;


    /* datas Screen */
    struct TrackSensePropertiesScreen
    {
        bool _isHomePage;
        bool _isCompassPage;
        bool _isRideDirectionPage;
        bool _isRidePage;
        bool _isGlobalStatisticsPage;
        bool _isGoHomePage;
        bool _isRideStatisticsPage;
        bool _isDarkMode;
    } PropertiesScreen;
    

    /* datas SD Card */
    struct TrackSensePropertiesSDCard
    {
        ;
    } PropertiesSDCard;
    

    /* datas Bluetooth */
    struct TrackSensePropertiesBluetooth
    {
        bool _isDeviceBluetoothConnected;
        
        // bool _isBluetoothConnected;
        // bool _isBluetoothActivated;
    } PropertiesBluetooth;


    /* datas LTE */
    struct TrackSensePropertiesLTE
    {
        bool _isDeviceLTEConnected;
    } PropertiesLTE;


    /* datas Wifi */
    struct TrackSensePropertiesWifi
    {
        ;
    } PropertiesWifi;


    /* datas GPS */
    struct TrackSensePropertiesGPS
    {
        double _latitude;
        double _longitude;
        double _altitude;
        double _speed;
    } PropertiesGPS;


    /* datas Compass */
    struct TrackSensePropertiesCompass
    {
        double _heading_angle; // PositionNord
        double _declinationAngle;
        // double _calibrationCompassX;
        // double _calibrationCompassY;
        // double _calibrationCompassZ;
    } PropertiesCompass;


    /* datas Gyroscope */
    struct TrackSensePropertiesGyroscope
    {
        double _roll_angle;  // PositionRoulis
        double _pitch_angle; // PositionTangage
        double _yaw_angle;   // PositionLacet
    } PropertiesGyroscope;


    /* datas Accelerometer */
    struct TrackSensePropertiesAccelerometer
    {
        double _acceleration_x;
        double _acceleration_y;
        double _acceleration_z;
    } PropertiesAccelerometer;


    /* datas Temperature */
    struct TrackSensePropertiesTemperature
    {
        double _temperature;
    } PropertiesTemperature;
    

    /* datas Battery */
    struct TrackSensePropertiesBattery
    {
        double _batteryLevel;
    } PropertiesBattery;
    

    /* datas Buzzer */
    struct TrackSensePropertiesBuzzer
    {
        bool _isBuzzerOn;
    } PropertiesBuzzer;
    
    /* datas CompletedRide to send */
    struct TrackSensePropertiesCompletedRideToSend
    {
        String _completedRideId;
        String _routeId;
        double _maxSpeed;
        double _avgSpeed;
        double _distance;
        double _duration;
        String _dateBegin;
        String _dateEnd;
        String _points;
        int _nbPoints;
        int _nbFalls;
        bool _isReady;
        bool _isReceived;
    } PropertiesCompletedRideToSend;

    /* Methods */
    TrackSenseProperties();
    ~TrackSenseProperties();
};
