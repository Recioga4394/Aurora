#include "src/display/epDisplay.h"
#include "src/wifi/epWiFi.h"
#include "src/datetime/ntpDateTime.h"
#include "src/weather/wttrWeather.h"


epDisplay*		display			= nullptr;
aWiFi*			wifi			= nullptr;
aDateTime*		dateTime		= nullptr;
aWeather*		weather			= nullptr;


void setup(void)
{
	display		= new epDisplay();
	wifi		= new epWiFi();
	dateTime	= new ntpDateTime();
	weather		= new wttrWeather();

	wifi->connect();
}

void loop()
{
 	dateTime->update();
	weather->update();
	wifi->disconnect();
	display->update();
}
