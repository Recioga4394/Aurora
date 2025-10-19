#ifndef EP_DISPLAY_H
#define EP_DISPLAY_H

#include <Arduino.h>
#include <stdarg.h>
#include <SPI.h>
#include <TFT_eSPI.h>		// Hardware-specific library
#include "epChart.h"
#include "../aDisplay.h"
#include "../aDateTime.h"
#include "globals.h"

class epDisplay : private aDisplay
{
	typedef struct{
		float	min;
		float	max;
		uint8_t	ticks;
		char*	format;
	}lims_t;

	private:
		String			_logStrings[DISPLAY_LOG_STRINGS_COUNT];
		epChart			_weaterHistoryChart;

		//Method for drawing forecast for part of the day
		void		_draw_forecast_data(uint32_t x, uint32_t y, uint32_t w, uint32_t h, forecastData_t* data);
		//Method for drawing chart with 2 vertical and 1 horizontal axis
		//void		_draw_chart(tft_espi_gl::rect_t rect, lims_t vert1, lims_t vert2, lims_t hor);

	public:
		epDisplay();
		~epDisplay();
		void	log(const char* msg, ...);
		void	time(time_t time);
		void	date(aDateTime::date_t date);
		void	weather(weatherCurrent_t* current);
		void	forecast(weatherForecast_t* forecast);
		void	weather_history(weatherHistory_t* history);
		void	update()	{this->EPaper::update();}
};

#endif