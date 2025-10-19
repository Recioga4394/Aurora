#include <stdio.h>
#include "wttrWeather.h"
#include "../aDisplay.h"
#include "../aWiFi.h"
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "weather_icons/weater_icons_200x200.h"
#include "weather_icons/weater_icons_64x64.h"

extern aDisplay*		display;
extern aWiFi*			wifi;
extern aDateTime*		dateTime;


wttrWeather::wttrWeather()
{
	memset(&_history.data, 0, sizeof(_history.data));
	_history.count	= 0;

	this->_sync();
	
	display->weather(&_current);
	display->forecast(&_forecast);
	display->weather_history(&_history);
}

wttrWeather::~wttrWeather()
{

}

//Method of synchronization with weather provider
bool	wttrWeather::_sync()
{
	if (wifi->connect() == false)	{display->log(WEATHER_LOG_NO_CONNECTION);	return false;};
	
	HTTPClient http;
	http.begin(WEATHER_PROVIDER_REQUEST);
	int result	= http.GET();
	display->log(WEATHER_LOG_SYNC_RESULT, result);

	if (result > 0)
	{
		String	payload	= http.getString();
		StaticJsonDocument<65536>	doc;
		DeserializationError		error	= deserializeJson(doc, payload);
		if(!error)
		{
			uint8_t	idx	= dateTime->h() / 3;
			_current.valid			= true;

			#ifdef LANGUAGE_RUS
			_current.description	= doc["weather"][0]["hourly"][idx]["lang_ru"][0]["value"].as<String>();
			#elifdef LANGUAGE_ENG
			_current.description	= doc["weather"][0]["hourly"][idx]["weatherDesc"][0]["value"].as<String>();
			#else
			#endif
			_current.icon			= _weather_code_to_large_icon(doc["weather"][0]["hourly"][idx]["weatherCode"]);
			_current.temperature	= doc["weather"][0]["hourly"][idx]["temp_C"];
			_current.feelsLike		= doc["weather"][0]["hourly"][idx]["FeelsLikeC"];
			_current.pressure		= doc["weather"][0]["hourly"][idx]["pressure"];
			_current.humidity		= doc["weather"][0]["hourly"][idx]["humidity"];
			_current.windSpeed		= doc["weather"][0]["hourly"][idx]["windspeedKmph"].as<double>() / 3.6;
			_current.windDeg		= doc["weather"][0]["hourly"][idx]["winddirDegree"];
			_current.cloudiness		= doc["weather"][0]["hourly"][idx]["cloudcover"];
			_current.rainVolume		= doc["weather"][0]["hourly"][idx]["precipMM"];
			_current.snowVolume		= doc["weather"][0]["hourly"][idx]["precipMM"];
			_current.visibility		= doc["weather"][0]["hourly"][idx]["visibility"];

			for (uint8_t idx = 0; idx < sizeof(_forecast.daily)/sizeof(forecastDay_t); idx++)
			{
				_forecast.daily[idx].valid						= true;
				_forecast.daily[idx].date						= doc["weather"][idx+1]["date"];
				//Morning
				#ifdef LANGUAGE_RUS
				_forecast.daily[idx].morning.description		= doc["weather"][idx+1]["hourly"][3]["lang_ru"][0]["value"].as<String>();
				#elifdef LANGUAGE_ENG
				_forecast.daily[idx].morning.description		= doc["weather"][idx+1]["hourly"][3]["weatherDesc"][0]["value"].as<String>();
				#else
				#endif
				_forecast.daily[idx].morning.icon				= _weather_code_to_small_icon(true, doc["weather"][idx+1]["hourly"][3]["weatherCode"]);
				_forecast.daily[idx].morning.temperature		= doc["weather"][idx+1]["hourly"][3]["tempC"];
				_forecast.daily[idx].morning.feelsLike			= doc["weather"][idx+1]["hourly"][3]["FeelsLikeC"];
				_forecast.daily[idx].morning.pressure			= doc["weather"][idx+1]["hourly"][3]["pressure"];
				_forecast.daily[idx].morning.humidity			= doc["weather"][idx+1]["hourly"][3]["humidity"];
				_forecast.daily[idx].morning.windSpeed			= doc["weather"][idx+1]["hourly"][3]["windspeedKmph"].as<double>() / 3.6;
				_forecast.daily[idx].morning.windDeg			= doc["weather"][idx+1]["hourly"][3]["winddirDegree"];
				_forecast.daily[idx].morning.cloudiness			= doc["weather"][idx+1]["hourly"][3]["cloudcover"];
				_forecast.daily[idx].morning.visibility			= doc["weather"][idx+1]["hourly"][3]["visibility"];
				_forecast.daily[idx].morning.chanceOfFog		= doc["weather"][idx+1]["hourly"][3]["chanceoffog"];
				_forecast.daily[idx].morning.chanceOfFrost		= doc["weather"][idx+1]["hourly"][3]["chanceoffrost"];
				_forecast.daily[idx].morning.chanceOfHighTemp	= doc["weather"][idx+1]["hourly"][3]["chanceofhightemp"];
				_forecast.daily[idx].morning.chanceOfOvercast	= doc["weather"][idx+1]["hourly"][3]["chanceofovercast"];
				_forecast.daily[idx].morning.chanceOfRain		= doc["weather"][idx+1]["hourly"][3]["chanceofrain"];
				_forecast.daily[idx].morning.chanceOfRemdry		= doc["weather"][idx+1]["hourly"][3]["chanceofremdry"];
				_forecast.daily[idx].morning.chanceOfSnow		= doc["weather"][idx+1]["hourly"][3]["chanceofsnow"];
				_forecast.daily[idx].morning.chanceOfSunshine	= doc["weather"][idx+1]["hourly"][3]["chanceofsunshine"];
				_forecast.daily[idx].morning.chanceOfThunder	= doc["weather"][idx+1]["hourly"][3]["chanceofthunder"];
				_forecast.daily[idx].morning.chanceOfWindy		= doc["weather"][idx+1]["hourly"][3]["chanceofwindy"];
				//Day
				#ifdef LANGUAGE_RUS
				_forecast.daily[idx].day.description			= doc["weather"][idx+1]["hourly"][5]["lang_ru"][0]["value"].as<String>();
				#elifdef LANGUAGE_ENG
				_forecast.daily[idx].day.description			= doc["weather"][idx+1]["hourly"][5]["weatherDesc"][0]["value"].as<String>();
				#else
				#endif
				_forecast.daily[idx].day.icon					= _weather_code_to_small_icon(true, doc["weather"][idx+1]["hourly"][5]["weatherCode"]);
				_forecast.daily[idx].day.temperature			= doc["weather"][idx+1]["hourly"][5]["tempC"];
				_forecast.daily[idx].day.feelsLike				= doc["weather"][idx+1]["hourly"][5]["FeelsLikeC"];
				_forecast.daily[idx].day.pressure				= doc["weather"][idx+1]["hourly"][5]["pressure"];
				_forecast.daily[idx].day.humidity				= doc["weather"][idx+1]["hourly"][5]["humidity"];
				_forecast.daily[idx].day.windSpeed				= doc["weather"][idx+1]["hourly"][5]["windspeedKmph"].as<double>() / 3.6;
				_forecast.daily[idx].day.windDeg				= doc["weather"][idx+1]["hourly"][5]["winddirDegree"];
				_forecast.daily[idx].day.cloudiness				= doc["weather"][idx+1]["hourly"][5]["cloudcover"];
				_forecast.daily[idx].day.visibility				= doc["weather"][idx+1]["hourly"][5]["visibility"];
				_forecast.daily[idx].day.chanceOfFog			= doc["weather"][idx+1]["hourly"][5]["chanceoffog"];
				_forecast.daily[idx].day.chanceOfFrost			= doc["weather"][idx+1]["hourly"][5]["chanceoffrost"];
				_forecast.daily[idx].day.chanceOfHighTemp		= doc["weather"][idx+1]["hourly"][5]["chanceofhightemp"];
				_forecast.daily[idx].day.chanceOfOvercast		= doc["weather"][idx+1]["hourly"][5]["chanceofovercast"];
				_forecast.daily[idx].day.chanceOfRain			= doc["weather"][idx+1]["hourly"][5]["chanceofrain"];
				_forecast.daily[idx].day.chanceOfRemdry			= doc["weather"][idx+1]["hourly"][5]["chanceofremdry"];
				_forecast.daily[idx].day.chanceOfSnow			= doc["weather"][idx+1]["hourly"][5]["chanceofsnow"];
				_forecast.daily[idx].day.chanceOfSunshine		= doc["weather"][idx+1]["hourly"][5]["chanceofsunshine"];
				_forecast.daily[idx].day.chanceOfThunder		= doc["weather"][idx+1]["hourly"][5]["chanceofthunder"];
				_forecast.daily[idx].day.chanceOfWindy			= doc["weather"][idx+1]["hourly"][5]["chanceofwindy"];
				//Evening
				#ifdef LANGUAGE_RUS
				_forecast.daily[idx].evening.description		= doc["weather"][idx+1]["hourly"][6]["lang_ru"][0]["value"].as<String>();
				#elifdef LANGUAGE_ENG
				_forecast.daily[idx].evening.description		= doc["weather"][idx+1]["hourly"][6]["weatherDesc"][0]["value"].as<String>();
				#else
				#endif
				_forecast.daily[idx].evening.icon				= _weather_code_to_small_icon(false, doc["weather"][idx+1]["hourly"][6]["weatherCode"]);
				_forecast.daily[idx].evening.temperature		= doc["weather"][idx+1]["hourly"][6]["tempC"];
				_forecast.daily[idx].evening.feelsLike			= doc["weather"][idx+1]["hourly"][6]["FeelsLikeC"];
				_forecast.daily[idx].evening.pressure			= doc["weather"][idx+1]["hourly"][6]["pressure"];
				_forecast.daily[idx].evening.humidity			= doc["weather"][idx+1]["hourly"][6]["humidity"];
				_forecast.daily[idx].evening.windSpeed			= doc["weather"][idx+1]["hourly"][6]["windspeedKmph"].as<double>() / 3.6;
				_forecast.daily[idx].evening.windDeg			= doc["weather"][idx+1]["hourly"][6]["winddirDegree"];
				_forecast.daily[idx].evening.cloudiness			= doc["weather"][idx+1]["hourly"][6]["cloudcover"];
				_forecast.daily[idx].evening.visibility			= doc["weather"][idx+1]["hourly"][6]["visibility"];
				_forecast.daily[idx].evening.chanceOfFog		= doc["weather"][idx+1]["hourly"][6]["chanceoffog"];
				_forecast.daily[idx].evening.chanceOfFrost		= doc["weather"][idx+1]["hourly"][6]["chanceoffrost"];
				_forecast.daily[idx].evening.chanceOfHighTemp	= doc["weather"][idx+1]["hourly"][6]["chanceofhightemp"];
				_forecast.daily[idx].evening.chanceOfOvercast	= doc["weather"][idx+1]["hourly"][6]["chanceofovercast"];
				_forecast.daily[idx].evening.chanceOfRain		= doc["weather"][idx+1]["hourly"][6]["chanceofrain"];
				_forecast.daily[idx].evening.chanceOfRemdry		= doc["weather"][idx+1]["hourly"][6]["chanceofremdry"];
				_forecast.daily[idx].evening.chanceOfSnow		= doc["weather"][idx+1]["hourly"][6]["chanceofsnow"];
				_forecast.daily[idx].evening.chanceOfSunshine	= doc["weather"][idx+1]["hourly"][6]["chanceofsunshine"];
				_forecast.daily[idx].evening.chanceOfThunder	= doc["weather"][idx+1]["hourly"][6]["chanceofthunder"];
				_forecast.daily[idx].evening.chanceOfWindy		= doc["weather"][idx+1]["hourly"][6]["chanceofwindy"];
			}

			for (int32_t idx = _history.capacity-1; idx > 0; idx--)		_history.data[idx]	= _history.data[idx-1];
			_history.data[0]	= _current;
			_history.count		= (_history.count < _history.capacity) ? (_history.count + 1) : _history.count;
			return true;
	
		}else	display->log(WEATHER_LOG_PARSING_ERROR);
	}else		display->log(WEATHER_LOG_REQUEST_ERROR);
	
	_current		= {0};
	_current.icon	= _weather_code_to_large_icon(0);
	for (uint8_t idx = 0; idx < sizeof(_forecast.daily)/sizeof(forecastDay_t); idx++)
	{
		_forecast.daily[idx]				= {0};
		_forecast.daily[idx].morning.icon	= _weather_code_to_small_icon(true, 0);
		_forecast.daily[idx].day.icon		= _weather_code_to_small_icon(true, 0);
		_forecast.daily[idx].evening.icon	= _weather_code_to_small_icon(false, 0);
	}

	for (uint32_t idx = _history.capacity-1; idx > 0; idx--)	_history.data[idx]	= _history.data[idx-1];
	_history.data[0].valid	= false;
	_history.count			= (_history.count < _history.capacity) ? (_history.count + 1) : _history.count;

	return  false;
}

weatherIcon_t	wttrWeather::_weather_code_to_large_icon(int32_t code)
{
	switch (code)
	{
		default:	return weatherIcon_t(200, 200, weather_200x200_na);
		case 113:	return (_is_day_now()) ? weatherIcon_t(200, 200, weather_200x200_sun_clear)					: weatherIcon_t(200, 200, weather_200x200_moon_clear);
		case 116:	return (_is_day_now()) ? weatherIcon_t(200, 200, weather_200x200_sun_clouds_little)			: weatherIcon_t(200, 200, weather_200x200_moon_clouds_little);
		case 119:	return (_is_day_now()) ? weatherIcon_t(200, 200, weather_200x200_sun_clouds_intense)		: weatherIcon_t(200, 200, weather_200x200_moon_clouds_intense);
		case 122:	return (_is_day_now()) ? weatherIcon_t(200, 200, weather_200x200_sun_clouds_intense)		: weatherIcon_t(200, 200, weather_200x200_moon_clouds_intense);
		case 176:	return (_is_day_now()) ? weatherIcon_t(200, 200, weather_200x200_rain_little)				: weatherIcon_t(200, 200, weather_200x200_rain_little);
		case 263:	return (_is_day_now()) ? weatherIcon_t(200, 200, weather_200x200_rain_little)				: weatherIcon_t(200, 200, weather_200x200_rain_little);
		case 266:	return (_is_day_now()) ? weatherIcon_t(200, 200, weather_200x200_rain_little)				: weatherIcon_t(200, 200, weather_200x200_rain_little);
		case 296:	return (_is_day_now()) ? weatherIcon_t(200, 200, weather_200x200_sun_rainy)					: weatherIcon_t(200, 200, weather_200x200_moon_rainy);
		case 353:	return (_is_day_now()) ? weatherIcon_t(200, 200, weather_200x200_rain)						: weatherIcon_t(200, 200, weather_200x200_moon_rainy);
	}
}

weatherIcon_t	wttrWeather::_weather_code_to_small_icon(bool isDay, int32_t code)
{
	switch (code)
	{
		default:	return weatherIcon_t(64, 64, weather_64x64_na);
		case 113:	return (isDay) ? weatherIcon_t(64, 64, weather_64x64_sun_clear)								: weatherIcon_t(64, 64, weather_64x64_moon_clear);
		case 116:	return (isDay) ? weatherIcon_t(64, 64, weather_64x64_sun_clouds_little)						: weatherIcon_t(64, 64, weather_64x64_moon_clouds_little);
		case 119:	return (isDay) ? weatherIcon_t(64, 64, weather_64x64_sun_clouds_intense)					: weatherIcon_t(64, 64, weather_64x64_moon_clouds_intense);
		case 122:	return (isDay) ? weatherIcon_t(64, 64, weather_64x64_sun_clouds_intense)					: weatherIcon_t(64, 64, weather_64x64_moon_clouds_intense);
		case 176:	return (isDay) ? weatherIcon_t(64, 64, weather_64x64_rain_little)							: weatherIcon_t(64, 64, weather_64x64_rain_little);
		case 263:	return (isDay) ? weatherIcon_t(64, 64, weather_64x64_rain_little)							: weatherIcon_t(64, 64, weather_64x64_rain_little);
		case 266:	return (isDay) ? weatherIcon_t(64, 64, weather_64x64_rain_little)							: weatherIcon_t(64, 64, weather_64x64_rain_little);
		case 296:	return (isDay) ? weatherIcon_t(64, 64, weather_64x64_sun_rainy)								: weatherIcon_t(64, 64, weather_64x64_moon_rainy);
		case 353:	return (isDay) ? weatherIcon_t(64, 64, weather_64x64_rain)									: weatherIcon_t(64, 64, weather_64x64_moon_rainy);
	}
}

bool	wttrWeather::_is_day_now()
{
	return (dateTime->h() >= 7) && (dateTime->h() < 21);
}

void	wttrWeather::update()
{
	//Get the current time in ms since the start of work
	time_t	currTime	= millis();
	
	//Checking if it is time to synchronize with weather provider
	if (((currTime - _prevSyncTime) >= _syncTimeout) || (currTime < _prevSyncTime))
	{
		this->_sync();
		display->weather(&_current);
		display->forecast(&_forecast);
		display->weather_history(&_history);
		_prevSyncTime		= currTime;
	}
};