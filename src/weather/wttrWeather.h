#include <sys/_stdint.h>
#ifndef WTTR_WEATHER_H
#define WTTR_WEATHER_H

#include <Arduino.h>
#include <time.h>
#include "../aWeather.h"

class wttrWeather : public aWeather
{
	private:
		weatherCurrent_t		_current;
		weatherForecast_t		_forecast;
		weatherHistory_t		_history;

		time_t					_syncTimeout		= 1000 * 60 * 60 * WEATHER_SYNC_TIMEOUT_H;	//In ms
		time_t					_prevSyncTime		= 0;	//Previous time of clock synchronization with universal time (used with SYNC_TIMEOUT_MS)
	
		//Method of synchronization with weather provider
		bool					_sync();
		//Convert weather code to icon for display
		weatherIcon_t			_weather_code_to_large_icon(int32_t code);
		weatherIcon_t			_weather_code_to_small_icon(bool isDay, int32_t code);
		//Method for determining day or night now
		bool					_is_day_now();

	public:
		wttrWeather();
		~wttrWeather();
		void		update();
};

#endif