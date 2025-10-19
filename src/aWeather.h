#ifndef A_WEATHER_H
#define A_WEATHER_H

#include <Arduino.h>
#include "WeatherData.h"

class aWeather
{
	public:
		virtual				~aWeather()		{};
		virtual void		update()		= 0;
};

#endif