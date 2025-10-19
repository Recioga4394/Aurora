#include <sys/_intsup.h>
#include "epDisplay.h"
#include "fonts/BreezeSans_Regular_12.h"
#include "fonts/BreezeSans_Regular_24.h"
#include "fonts/BreezeSans_Regular_32.h"
#include "fonts/BreezeSans_Regular_64.h"
#include "fonts/digital_7_64.h"
#include "fonts/digital_7_112.h"
#include "fonts/digital_7_72.h"


extern aDateTime*		dateTime;


epDisplay::epDisplay() :
	_weaterHistoryChart(this)
{
	this->begin();
	this->setRotation(0);
	this->fillScreen(TFT_WHITE);
	this->drawFastVLine(DISPLAY_BORDER_X + DISPLAY_WIDTH/2, DISPLAY_BORDER_Y, DISPLAY_HEIGHT - 2*DISPLAY_BORDER_Y, TFT_BLACK);
		
	_weaterHistoryChart.set_area(DISPLAY_WEATHER_HISTORY_X, DISPLAY_WEATHER_HISTORY_Y, DISPLAY_WEATHER_HISTORY_W, DISPLAY_WEATHER_HISTORY_H);
	_weaterHistoryChart.set_axis(epChart::epAxis::AXIS_LEFT, -15, +25, "%-+2.0f", 5, true);
	_weaterHistoryChart.set_axis(epChart::epAxis::AXIS_RIGHT, 960, 1100, "%5.0f", 5, true);
	_weaterHistoryChart.set_axis(epChart::epAxis::AXIS_BOTTOM, -WEATHER_HISTORY_CAPACITY, 0, "%2.0f", 10, false);

	//drawRect(DISPLAY_TIME_X, DISPLAY_TIME_Y, DISPLAY_TIME_W, DISPLAY_TIME_H, TFT_BLACK);
	//drawRect(DISPLAY_DATE_X, DISPLAY_DATE_Y, DISPLAY_DATE_W, DISPLAY_DATE_H, TFT_BLACK);
	//drawRect(DISPLAY_WEATHER_X, DISPLAY_WEATHER_Y, DISPLAY_WEATHER_W, DISPLAY_WEATHER_H, TFT_BLACK);
	//drawRect(DISPLAY_FORECAST_X, DISPLAY_FORECAST_Y, DISPLAY_FORECAST_W, DISPLAY_FORECAST_H, TFT_BLACK);
	//drawRect(DISPLAY_WEATHER_HISTORY_X, DISPLAY_WEATHER_HISTORY_Y, DISPLAY_WEATHER_HISTORY_W, DISPLAY_WEATHER_HISTORY_H, TFT_BLACK);
}

epDisplay::~epDisplay()
{

}

void	epDisplay::log(const char* msg, ...)
{
	this->loadFont(DISPLAY_LOG_FONT);
	this->setTextColor(TFT_BLACK, TFT_WHITE);
	this->setTextDatum(CL_DATUM);

	char		buf[100];
	uint16_t	len	= 0;
	//If the time module is available - add time to the log
	if (dateTime != nullptr)	len	= snprintf(buf, sizeof(buf), "%02d:%02d:%02d  ", dateTime->h(), dateTime->m(), dateTime->s());

	va_list		args;
	va_start(args, msg);
	vsnprintf(&buf[len], sizeof(buf) - len, msg, args);
	va_end(args);

	//Scroll the lines of the log so that in index 0 there would be the newest
	for (uint8_t idx = DISPLAY_LOG_STRINGS_COUNT-1; idx > 0; idx--)		_logStrings[idx]	= _logStrings[idx-1];
	_logStrings[0]	= String(buf);
	
	//Clean the output area
	uint32_t	x	= DISPLAY_BORDER_X;
	uint32_t	y	= this->height() - DISPLAY_LOG_FONT_HEIGHT * (DISPLAY_LOG_STRINGS_COUNT + 1) - DISPLAY_BORDER_Y;
	uint32_t	w	= this->width() / 2 - DISPLAY_BORDER_X;
	uint32_t	h	= DISPLAY_LOG_FONT_HEIGHT * (DISPLAY_LOG_STRINGS_COUNT + 1);
	this->fillRect(x, y, w, h, TFT_WHITE);
	
	for (uint8_t idx = 0; idx < DISPLAY_LOG_STRINGS_COUNT; idx++)
	{
		this->drawString(_logStrings[idx], DISPLAY_BORDER_X, this->height() - DISPLAY_LOG_FONT_HEIGHT * (idx + 1) - DISPLAY_BORDER_Y);
	}
	this->unloadFont();
	this->update();
};

void	epDisplay::time(time_t time)
{
	uint8_t	h	= (time / (1000 * 60 * 60));
	uint8_t	m	= (time / (1000 * 60)) % 60;
	uint8_t	s	= (time / 1000) % 60;

	char	buf[32];
	snprintf(buf, sizeof(buf), "%02d:%02d", h, m);
	this->loadFont(DISPLAY_TIME_LARGE_FONT);
	this->setTextColor(TFT_BLACK, TFT_WHITE);
	this->setTextDatum(CC_DATUM);
	uint32_t	tw	= this->textWidth(buf);
	this->setTextPadding(tw);
	uint16_t	x	= DISPLAY_TIME_X + DISPLAY_TIME_W/2 - tw/4;
	uint16_t	y	= DISPLAY_TIME_Y + DISPLAY_TIME_H/2;
	x				+= this->drawString(buf, x, y)/2;
	this->unloadFont();

	snprintf(buf, sizeof(buf), ":%02d", s);
	this->loadFont(DISPLAY_TIME_SMALL_FONT);
	this->setTextColor(TFT_BLACK, TFT_WHITE);
	this->setTextDatum(CL_DATUM);
	tw				= this->textWidth(buf);
	this->setTextPadding(tw);
	x				+= tw/4;
	y				-= 18;
	this->drawString(buf, x, y);
	this->unloadFont();
	this->setTextPadding(0);
};

void	epDisplay::date(aDateTime::date_t date)
{
	//Cleanup date area by fill rect white color
	fillRect(DISPLAY_DATE_X, DISPLAY_DATE_Y, DISPLAY_DATE_W, DISPLAY_DATE_H, TFT_WHITE);

	char	buf[32];
	char*		wday		= nullptr;
	switch (date.wd)
	{
		case 0:	wday	= DISPLAY_WEEKDAY_UNKNOWN;		break;
		case 1:	wday	= DISPLAY_WEEKDAY_MONDAY;		break;
		case 2:	wday	= DISPLAY_WEEKDAY_TUESDAY;		break;
		case 3:	wday	= DISPLAY_WEEKDAY_WEDNESDAY;	break;
		case 4:	wday	= DISPLAY_WEEKDAY_THURSDAY;		break;
		case 5:	wday	= DISPLAY_WEEKDAY_FRIDAY;		break;
		case 6:	wday	= DISPLAY_WEEKDAY_SATURDAY;		break;
		case 7:	wday	= DISPLAY_WEEKDAY_SUNDAY;		break;
	}
	snprintf(buf, sizeof(buf), " %s ", wday);
	this->loadFont(DISPLAY_DATE_SMALL_FONT);
	this->setTextColor(TFT_BLACK, TFT_WHITE);
	this->setTextDatum(CC_DATUM);
	uint16_t	x	= DISPLAY_DATE_X + DISPLAY_DATE_W/2;
	uint16_t	y	= DISPLAY_DATE_Y + DISPLAY_DATE_H/4;
	this->drawString(buf, x, y);
	this->unloadFont();

	char*		month		= nullptr;
	switch (date.m)
	{
		case 0:		month	= DISPLAY_MONTH_UNKNOWN;	break;
		case 1:		month	= DISPLAY_MONTH_JANUARY;	break;
		case 2:		month	= DISPLAY_MONTH_FEBRUARY;	break;
		case 3:		month	= DISPLAY_MONTH_MARCH;		break;
		case 4:		month	= DISPLAY_MONTH_APRIL;		break;
		case 5:		month	= DISPLAY_MONTH_MAY;		break;
		case 6:		month	= DISPLAY_MONTH_JUNE;		break;
		case 7:		month	= DISPLAY_MONTH_JULY;		break;
		case 8:		month	= DISPLAY_MONTH_AUGUST;		break;
		case 9:		month	= DISPLAY_MONTH_SEPTEMBER;	break;
		case 10:	month	= DISPLAY_MONTH_OCTOBER;	break;
		case 11:	month	= DISPLAY_MONTH_NOVEMBER;	break;
		case 12:	month	= DISPLAY_MONTH_DECEMBER;	break;
	}
	snprintf(buf, sizeof(buf), "%02d %s %04d", date.d, month, date.y);
	this->loadFont(DISPLAY_DATE_LARGE_FONT);
	this->setTextColor(TFT_BLACK, TFT_WHITE);
	this->setTextDatum(CC_DATUM);
	x				= DISPLAY_DATE_X + DISPLAY_DATE_W/2;
	y				= DISPLAY_DATE_Y + 3*DISPLAY_DATE_H/4;
	this->drawString(buf, x, y);
	this->unloadFont();
};

void	epDisplay::weather(weatherCurrent_t* current)
{
	//Cleanup weather area by fill rect white color
	fillRect(DISPLAY_WEATHER_X, DISPLAY_WEATHER_Y, DISPLAY_WEATHER_W, DISPLAY_WEATHER_H, TFT_WHITE);

	uint16_t	x	= DISPLAY_WEATHER_X + DISPLAY_WEATHER_W/2;
	uint16_t	y	= DISPLAY_WEATHER_Y + DISPLAY_WEATHER_H/12;
	uint16_t	h	= DISPLAY_WEATHER_H;
	char		buf[32];
	this->loadFont(DISPLAY_WEATHER_MEDIUM_FONT);
	this->setTextColor(TFT_BLACK, TFT_WHITE);
	this->setTextDatum(CC_DATUM);
	snprintf(buf, sizeof(buf), "%s", current->description.c_str());
	this->drawString(buf, x, y);
	this->unloadFont();
	h	-= 2*DISPLAY_WEATHER_H/12;

	x	= DISPLAY_WEATHER_X + 1;
	y	+= DISPLAY_WEATHER_H/12 - 1;
	this->pushImage(x, y, current->icon.w, current->icon.h, (uint16_t*)current->icon.data);

	//Display the temperature with a large font
	this->loadFont(BreezeSans_Regular_64);
	this->setTextColor(TFT_BLACK, TFT_WHITE);
	this->setTextDatum(CL_DATUM);
	snprintf(buf, sizeof(buf), DISPLAY_WEATHER_TEMP_FORMAT, current->feelsLike);
	x	= DISPLAY_WEATHER_X + current->icon.w + 8;
	y	+= (4 * h / 10)/2;
	this->drawString(buf, x, y);
	this->unloadFont();
	y	+= (4 * h / 10)/2;

	//Other values display by medium font
	this->loadFont(DISPLAY_WEATHER_MEDIUM_FONT);
	this->setTextColor(TFT_BLACK, TFT_WHITE);
	this->setTextDatum(CL_DATUM);
	//Humidity
	x	= DISPLAY_WEATHER_X + 12*DISPLAY_WEATHER_W/20;
	y	+= (2 * h / 10)/2;
	snprintf(buf, sizeof(buf), "%2.0f", current->humidity);
	this->drawString(buf, x, y);
	x	= DISPLAY_WEATHER_X + 16*DISPLAY_WEATHER_W/20;
	this->drawString("%", x, y);
	y	+= (2 * h / 10)/2;
	//Pressure
	x	= DISPLAY_WEATHER_X + 12*DISPLAY_WEATHER_W/20;
	y	+= (2 * h / 10)/2;
	snprintf(buf, sizeof(buf), "%-5.0f", current->pressure);
	this->drawString(buf, x, y);
	x	= DISPLAY_WEATHER_X + 16*DISPLAY_WEATHER_W/20;
	this->drawString(DISPLAY_WEATHER_PRESSURE_UNITS, x, y);
	y	+= (2 * h / 10)/2;
	//Wind speed
	x	= DISPLAY_WEATHER_X + 12*DISPLAY_WEATHER_W/20;
	y	+= (2 * h / 10)/2;
	snprintf(buf, sizeof(buf), "%-5.1f", current->windSpeed);
	this->drawString(buf, x, y);
	x	= DISPLAY_WEATHER_X + 16*DISPLAY_WEATHER_W/20;
	this->drawString(DISPLAY_WEATHER_WIND_UNITS, x, y);
	y	+= (2 * h / 10)/2;
	this->unloadFont();

	this->drawFastHLine(DISPLAY_WEATHER_X + DISPLAY_BORDER_X, DISPLAY_WEATHER_Y + DISPLAY_WEATHER_H, DISPLAY_WEATHER_W - 2*DISPLAY_BORDER_Y, TFT_BLACK);
}

void	epDisplay::forecast(weatherForecast_t* forecast)
{
	//Cleanup forecast area by fill rect white color
	fillRect(DISPLAY_FORECAST_X, DISPLAY_FORECAST_Y, DISPLAY_FORECAST_W, DISPLAY_FORECAST_H, TFT_WHITE);

	uint16_t	x	= DISPLAY_FORECAST_X + DISPLAY_FORECAST_W/6;
	uint16_t	y	= DISPLAY_FORECAST_Y + DISPLAY_FORECAST_H/20;
	uint32_t	w	= DISPLAY_FORECAST_W/3;
	uint16_t	h	= DISPLAY_FORECAST_H;
	this->loadFont(DISPLAY_FORECAST_SMALL_FONT);
	this->setTextColor(TFT_BLACK, TFT_WHITE);
	this->setTextDatum(CC_DATUM);
	this->drawString(DISPLAY_FORECAST_MORNING, x, y);
	x	+= w;
	this->drawString(DISPLAY_FORECAST_DAY, x, y);
	x	+= w;
	this->drawString(DISPLAY_FORECAST_EVENING, x, y);
	y	+= DISPLAY_FORECAST_H/10;
	h	-= DISPLAY_FORECAST_H/10 + DISPLAY_FORECAST_H/10;

	char*		days[3]		= DISPLAY_FORECAST_DAYS;
	uint8_t		count		= sizeof(forecast->daily)/sizeof(forecastDay_t);

	for (uint8_t idx = 0; idx < count; idx++)
	{
		this->setTextDatum(CC_DATUM);
		x	= DISPLAY_FORECAST_X + DISPLAY_FORECAST_W/2;
		this->drawString(days[idx], x, y);
		
		x	= DISPLAY_FORECAST_X;
		y	+= DISPLAY_FORECAST_H/20;
		w	= DISPLAY_FORECAST_W/3;
		_draw_forecast_data(x, y, w, h/2, &forecast->daily[idx].morning);
		x	+= DISPLAY_FORECAST_W/3;
		_draw_forecast_data(x, y, w, h/2, &forecast->daily[idx].day);
		x	+= DISPLAY_FORECAST_W/3;
		_draw_forecast_data(x, y, w, h/2, &forecast->daily[idx].evening);
		y	+= h / count;
	}
	this->unloadFont();
}

void	epDisplay::_draw_forecast_data(uint32_t x, uint32_t y, uint32_t w, uint32_t h, forecastData_t* data)
{
	this->setTextDatum(TC_DATUM);

	char			buf[32];
	snprintf(buf, sizeof(buf), "%s", data->description.c_str());
	this->drawString(buf, x + w/2, y);
	y	+= 12;

	x	+= 10;
	this->pushImage(x, y, data->icon.w, data->icon.h, (uint16_t*)data->icon.data);
	x	+= data->icon.w;
	y	+= 12;

	this->setTextDatum(TL_DATUM);
	snprintf(buf, sizeof(buf), DISPLAY_FORECAST_TEMP_FORMAT, data->temperature);
	this->drawString(buf, x + 2, y);
	y	+= 12;
	snprintf(buf, sizeof(buf), "%-2.0f %%", data->humidity);
	this->drawString(buf, x + 2, y);
	y	+= 12;
	snprintf(buf, sizeof(buf), DISPLAY_FORECAST_PRESSURE_FORMAT, data->pressure);
	this->drawString(buf, x + 2, y);
	y	+= 12;
	snprintf(buf, sizeof(buf), DISPLAY_FORECAST_WIND_FORMAT, data->windSpeed);
	this->drawString(buf, x + 2, y);
	y	+= 12;
}

void	epDisplay::weather_history(weatherHistory_t* history)
{
	//Cleanup forecast area by fill rect white color
	fillRect(DISPLAY_WEATHER_HISTORY_X, DISPLAY_WEATHER_HISTORY_Y, DISPLAY_WEATHER_HISTORY_W, DISPLAY_WEATHER_HISTORY_H, TFT_WHITE);

	//Count valid weather history data
	uint8_t		count	= 0;
	for (uint8_t idx = 0; idx < history->count; idx++)
	{
		if (history->data[idx].valid == false)		continue;
		count++;
	}
	//If no valid data present - return immediately
	if (count == 0)									return;

	//Allocate memory for data arrays
	float*	yVal[2]	= {nullptr, nullptr};
	float*	xVal	= nullptr;
	yVal[0]			= new float[count];
	if (yVal[0] == nullptr)			return;
	yVal[1]			= new float[count];
	if (yVal[1] == nullptr)		{delete[] yVal[0];	return;}
	xVal			= new float[count];
	if (xVal == nullptr)		{delete[] yVal[0];	delete[] yVal[1];	return;}

	count	= 0;
	for (uint8_t idx = 0; idx < history->count; idx++)
	{
		if (history->data[idx].valid == false)		continue;
		yVal[0][count]	= history->data[idx].feelsLike;
		yVal[1][count]	= history->data[idx].pressure;
		xVal[count]		= -1.0 * idx;
		count++;
	}

	//Update weather history chart
	this->loadFont(DISPLAY_WEATHER_HISTORY_SMALL_FONT);
	this->setTextColor(TFT_BLACK, TFT_WHITE);
	_weaterHistoryChart.update(yVal, xVal, count);
	this->unloadFont();

	//Return memory to system
	delete[]	yVal[0];
	delete[]	yVal[1];
	delete[]	xVal;
}
