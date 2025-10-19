#include <sys/_stdint.h>
#ifndef EP_WEATHER_DATA_H
#define EP_WEATHER_DATA_H

#include <Arduino.h>
#include "globals.h"

typedef struct
{
		uint16_t				w;
		uint16_t				h;
		const unsigned char*	data;
}weatherIcon_t;

typedef struct
{
	bool						valid;
	String						description;			// Detailed description (e.g., "light rain")
	weatherIcon_t				icon;
	float						temperature;			// Temperature in Celsius
	float						feelsLike;				// Feels like temperature (Celsius)
	float						pressure;				// Atmospheric pressure (hPa)
	float						humidity;				// Humidity percentage (%)
	float						windSpeed;				// Wind speed (m/s)
	float						windDeg;				// Wind direction (degrees)
	float						cloudiness;				// Cloud cover percentage (%)
	float						rainVolume;				// Rain volume in last hour (mm), if available
	float						snowVolume;				// Snow volume in last hour (mm), if available
	float						visibility;				// Visibility in meters
}weatherCurrent_t;

typedef struct
{
	String						description;			// Detailed description (e.g., "light rain")
	weatherIcon_t				icon;
	float						temperature;			// Temperature in Celsius
	float						feelsLike;				// Feels like temperature (Celsius)
	float						pressure;				// Atmospheric pressure (hPa)
	float						humidity;				// Humidity percentage (%)
	float						windSpeed;				// Wind speed (m/s)
	float						windDeg;				// Wind direction (degrees)
	float						cloudiness;				// Cloud cover percentage (%)
	float						visibility;				// Visibility in meters
	uint8_t						chanceOfFog;
	uint8_t						chanceOfFrost;
	uint8_t						chanceOfHighTemp;
	uint8_t						chanceOfOvercast;
	uint8_t						chanceOfRain;
	uint8_t						chanceOfRemdry;
	uint8_t						chanceOfSnow;
	uint8_t						chanceOfSunshine;
	uint8_t						chanceOfThunder;
	uint8_t						chanceOfWindy;
}forecastData_t;

typedef struct
{
	bool						valid;
	uint64_t					date;				// Forecast date (Unix time or YYYYMMDD)
	forecastData_t				morning;			// Morning weather data
	forecastData_t				day;				// Daytime weather data
	forecastData_t				evening;			// Evening weather data
	float						pop;				// Probability of precipitation (0.0 - 1.0)
}forecastDay_t;

typedef struct
{
	forecastDay_t				daily[2];	// Daily forecast for 2 days
	// Optional hourly forecast can be added:
	// WeatherData hourly[24];
}weatherForecast_t;

typedef struct
{
	const uint8_t		capacity	= WEATHER_HISTORY_CAPACITY;
	uint8_t				count		= 0;
	weatherCurrent_t	data[WEATHER_HISTORY_CAPACITY];
}weatherHistory_t;

#endif