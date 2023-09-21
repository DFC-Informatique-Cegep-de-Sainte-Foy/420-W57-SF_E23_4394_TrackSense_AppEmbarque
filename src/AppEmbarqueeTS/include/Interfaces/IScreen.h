#pragma once
#include "TSProperties.h"

class IScreen
{
public:
    /* Test for debug */
    virtual void testButtonsScreen() = 0;
    virtual void testGPS() = 0;

    /* Elements */
    virtual void drawLogoTS() = 0;
    virtual void drawBattery(int16_t coordX, int16_t coordY, int16_t largeurX, int pourcentage) = 0;
    virtual void drawIsRideStarted(int16_t coordX, int16_t coordY, int16_t largeurX) = 0;
    virtual void drawError() = 0;

    /* Drawing tools */
    virtual int calculateXCoordTextToCenter(String text) = 0;
    virtual int calculateXCoordItemToCenter(uint16_t lengthInPixels) = 0;

    virtual void drawOnScreen() = 0;
    virtual void setRotation(u_int8_t rotation) = 0;
    virtual void drawBackgroundColor(uint16_t darkModeColor, uint16_t lightModeColor) = 0;
    virtual void setTextColor(uint16_t textDarkModeColor,
                              uint16_t backgroundDarkModeColor,
                              uint16_t textLightModeColor,
                              uint16_t backgroundLightModeColor) = 0;

    virtual void drawRect(int16_t x, int16_t y, int16_t width, int16_t height,
                          uint16_t darkModeColor,
                          uint16_t lightModeColor) = 0;

    virtual void drawFillRect(int16_t x, int16_t y, int16_t width, int16_t height,
                              uint16_t darkModeColor,
                              uint16_t lightModeColor) = 0;



};
