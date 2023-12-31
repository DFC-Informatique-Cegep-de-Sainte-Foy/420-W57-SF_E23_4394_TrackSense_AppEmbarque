#include "ControlerButtons.h"

ControlerButtons::ControlerButtons(TSProperties *TSProperties) : _TSProperties(TSProperties),
                                                                 _button1(nullptr),
                                                                 _button2(nullptr),
                                                                 // _isPressedButton1(false),
                                                                 // _isPressedButton2(false),
                                                                 _finalStateButton1(0),
                                                                 _finalStateButton2(0),
                                                                 _guidGenerator(nullptr),
                                                                 _lastDateChangementStateButtons(millis())
{
    this->_button1 = new ButtonTactile(PIN_BUTTON1, _TSProperties);
    this->_button2 = new ButtonTactile(PIN_BUTTON2, _TSProperties);
    this->_guidGenerator = new UUID();
    this->_guidGenerator->setRandomMode();
}

ControlerButtons::~ControlerButtons()
{
    ;
}

void ControlerButtons::tick()
{
    // this->_isPressedButton1 = this->_button1->getIsPressedButton();   // 0 == not pressed    // 1 == pressed
    // this->_isPressedButton2 = this->_button2->getIsPressedButton();

    this->_finalStateButton1 = this->_button1->getFinalState(); // 0 == not pressed    // 1 == short press    // 2 == long press    // 3 == double short press
    this->_finalStateButton2 = this->_button2->getFinalState();

    long dateActuelle = millis();

#if DEBUG_TS_BUTTONS_HARDCORE
    this->_TSProperties->PropertiesButtons.Button1State = this->_finalStateButton1;
    this->_TSProperties->PropertiesButtons.Button2State = this->_finalStateButton2;
#endif

    if (this->_finalStateButton1 != 0 || this->_finalStateButton2 != 0)
    {
        this->_lastDateChangementStateButtons = dateActuelle;
        this->_TSProperties->PropertiesTS.IsOnStanby = false;
        digitalWrite(TFT_BLK, HIGH); // Backlight on
    }

    int controlerState = this->_finalStateButton1 + 4 * this->_finalStateButton2;

    switch (controlerState)
    {
    case 0:
        /* Nothing Happened... */
        DEBUG_STRING_LN(DEBUG_TS_BUTTONS, "No button pressed");

        if (!this->_TSProperties->PropertiesCurrentRide.IsRideStarted)
        {
            if (dateActuelle - this->_lastDateChangementStateButtons > this->_TSProperties->PropertiesButtons.TimeBeforeInactivityMS)
            {
                this->_TSProperties->PropertiesTS.IsOnStanby = true;
                DEBUG_STRING_LN(DEBUG_TS_BUTTONS, "++++++++++++++++++++++ IsOnStanby = true ++++++++++++++++++++++");
            }
        }
        break;

    case 1:
        /* Change Page Up */
        if (this->_TSProperties->PropertiesCurrentRide.IsRideStarted) // À retirer pour quand on ajoutera la boussole
        {
            DEBUG_STRING_LN(DEBUG_TS_BUTTONS, "Button 1 SHORT press");
            this->changePageUp();
        }
        break;

    case 2:
        /* Start/Stop Ride */
        DEBUG_STRING_LN(DEBUG_TS_BUTTONS, "Button 1 LONG press");

        if (this->_TSProperties->PropertiesCurrentRide.IsRideStarted)
        {
            this->finishRide();
        }
        else
        {
            this->startRide();
        }
        break;

    case 3:
        /* Trigger The Buzzer */
        DEBUG_STRING_LN(DEBUG_TS_BUTTONS, "Button 1 DOUBLE SHORT press"); // Impossible !!!
        this->makeNoiseBuzzer();
        break;

    case 4:
        /* Change Page Down */
        if (this->_TSProperties->PropertiesCurrentRide.IsRideStarted) // À retirer pour quand on ajoutera la boussole
        {
            DEBUG_STRING_LN(DEBUG_TS_BUTTONS, "Button 2 SHORT press");
            this->changePageDown();
        }
        break;

    case 5:
        /* Activate GoHome Mode */
        DEBUG_STRING_LN(DEBUG_TS_BUTTONS, "Buttons 1 and 2 SHORT press");
        this->goHome();
        break;

    case 8:
        /* Pause/Restart Ride */
        DEBUG_STRING_LN(DEBUG_TS_BUTTONS, "Button 2 LONG press");

        if (this->_TSProperties->PropertiesCurrentRide.IsRideStarted)
        {
            if (this->_TSProperties->PropertiesCurrentRide.IsRidePaused)
            {
                this->restartRide();
            }
            else
            {
                this->pauseRide();
            }
        }
        break;

    case 10:
        /* Trigger The Buzzer */
        DEBUG_STRING_LN(DEBUG_TS_BUTTONS, "Buttons 1 and 2 LONG press");
        this->makeNoiseBuzzer();
        break;

    case 12:
        /* Trigger The Buzzer */
        DEBUG_STRING_LN(DEBUG_TS_BUTTONS, "Button 2 DOUBLE SHORT press"); // Impossible !!!
        this->makeNoiseBuzzer();
        break;

    default:
        /* Nothing Good Happened... */
        DEBUG_STRING_LN(DEBUG_TS_BUTTONS, "BUTTONS ERROR !!!");
        break;
    }
}

/*
    0 : Home Page
    1 : Ride Page
    2 : Ride Statistics Page
    3 : Compass Page
    4 : Ride Direction Page
    5 : Global Statistics Page
    6 : Go Home Page
    -1 : Init TS Page
    -2 : Ending Ride Page
    -3 : No Page (error)

    0 : Page Accueil
    1 : Page Trajet
    2 : Page Statistiques Trajet
    3 : Page Boussole
    4 : Page Direction Trajet
    5 : Page Statistiques Globales
    6 : Page Retour Maison
    -1 : Page Init TS
    -2 : Page Fin Trajet
    -3 : Page Erreur
*/
void ControlerButtons::changePageUp()
{
    this->_TSProperties->PropertiesScreen.ActiveScreen++;

    if (this->_TSProperties->PropertiesScreen.ActiveScreen >= NB_ACTIVE_PAGES || this->_TSProperties->PropertiesScreen.ActiveScreen < 0)
    {
        this->_TSProperties->PropertiesScreen.ActiveScreen = 0;
    }
}

/*
    0 : Home Page
    1 : Ride Page
    2 : Ride Statistics Page
    3 : Compass Page
    4 : Ride Direction Page
    5 : Global Statistics Page
    6 : Go Home Page
    -1 : Init TS Page
    -2 : Ending Ride Page
    -3 : No Page (error)

    0 : Page Accueil
    1 : Page Trajet
    2 : Page Statistiques Trajet
    3 : Page Boussole
    4 : Page Direction Trajet
    5 : Page Statistiques Globales
    6 : Page Retour Maison
    -1 : Page Init TS
    -2 : Page Fin Trajet
    -3 : Page Erreur
*/
void ControlerButtons::changePageDown()
{
    this->_TSProperties->PropertiesScreen.ActiveScreen--;

    if (this->_TSProperties->PropertiesScreen.ActiveScreen < 0 || this->_TSProperties->PropertiesScreen.ActiveScreen > NB_ACTIVE_PAGES)
    {
        this->_TSProperties->PropertiesScreen.ActiveScreen = NB_ACTIVE_PAGES - 1;
    }
}

void ControlerButtons::startRide()
{
    if (this->_TSProperties->PropertiesCurrentRide.IsRideStarted == false)
    {
        DEBUG_STRING_LN(DEBUG_TS_BUTTONS, "===================== Start Ride =====================");
        this->_TSProperties->PropertiesCurrentRide.resetCurrentRide();
        this->_TSProperties->PropertiesGPS.resetGPSValues();

        this->_TSProperties->PropertiesCurrentRide.IsRideStarted = true;
        this->_TSProperties->PropertiesCurrentRide.IsRideFinished = false;

        this->_TSProperties->PropertiesCurrentRide.StartTimeMS = millis();

        this->_guidGenerator->seed(this->_TSProperties->PropertiesCurrentRide.StartTimeMS);
        this->_guidGenerator->generate();
        this->_TSProperties->PropertiesCurrentRide.CompletedRideId = this->_guidGenerator->toCharArray();

        this->_TSProperties->PropertiesScreen.ActiveScreen = RIDE_PAGE_ID;
    }
}

void ControlerButtons::finishRide()
{
    if (this->_TSProperties->PropertiesCurrentRide.IsRideStarted)
    {
        this->_TSProperties->PropertiesCurrentRide.IsRideFinished = true;
        this->_TSProperties->PropertiesCurrentRide.IsRideStarted = false;

        this->_TSProperties->PropertiesCurrentRide.EndTimeMS = millis();
        this->_TSProperties->PropertiesCurrentRide.DurationS = (this->_TSProperties->PropertiesCurrentRide.EndTimeMS - this->_TSProperties->PropertiesCurrentRide.StartTimeMS) / 1000;

        this->_TSProperties->PropertiesCurrentRide.IsRideReadyToSave = true;

        this->_TSProperties->PropertiesScreen.ActiveScreen = ENDING_RIDE_PAGE_ID;

        this->_TSProperties->PropertiesGPS.CounterTotal = 0;
        this->_TSProperties->PropertiesGPS.CounterGoodValue = 0;

        DEBUG_STRING_LN(DEBUG_TS_BUTTONS, "===================== Finish Ride =====================");
    }
}

void ControlerButtons::pauseRide()
{
    if (this->_TSProperties->PropertiesCurrentRide.IsRideStarted)
    {
        this->_TSProperties->PropertiesCurrentRide.IsRidePaused = true;
    }
}

void ControlerButtons::restartRide()
{
    if (this->_TSProperties->PropertiesCurrentRide.IsRideStarted)
    {
        this->_TSProperties->PropertiesCurrentRide.IsRidePaused = false;
    }
}

void ControlerButtons::makeNoiseBuzzer()
{
    this->_TSProperties->PropertiesBuzzer.IsBuzzerOn = true;
}

void ControlerButtons::goHome()
{
    this->_TSProperties->PropertiesScreen.ActiveScreen = GO_HOME_PAGE_ID;
}

void ControlerButtons::resetLastDateChangementStateButtons()
{
    this->_lastDateChangementStateButtons = millis();
}
