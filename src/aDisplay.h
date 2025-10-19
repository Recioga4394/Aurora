#ifndef A_DISPLAY_H
#define A_DISPLAY_H

#include <Arduino.h>
#include <stdarg.h>
#include <SPI.h>
#include <TFT_eSPI.h>				// Hardware-specific library by Seeed Studio
#include "aDateTime.h"
#include "aWeather.h"

class aDisplay : public EPaper
{
	public:
		virtual			~aDisplay()		{};
		virtual	void	log(const char* msg, ...)					= 0;
		virtual	void	time(time_t time)							= 0;
		virtual	void	date(aDateTime::date_t date)				= 0;
		virtual	void	weather(weatherCurrent_t* current)			= 0;
		virtual	void	forecast(weatherForecast_t* forecast)		= 0;
		virtual void	weather_history(weatherHistory_t* history)	= 0;
		virtual	void	update()									= 0;
};

#endif