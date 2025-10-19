#include "ntpDateTime.h"
#include "../display/epDisplay.h"
#include "../aWiFi.h"
#include <time.h>
#include "globals.h"

extern epDisplay*		display;
extern aWiFi*			wifi;


ntpDateTime::ntpDateTime()
{
	configTime(NTP_GTM_OFFSET_S, NTP_DAY_LIGHT_OFFSET_S, NTP_SERVER);
	_sync();
	display->time(_time);
	display->date(_date);
}

ntpDateTime::~ntpDateTime()
{

}

//Method of synchronization with universal time
void	ntpDateTime::_sync()
{
	if (wifi->connect() == false)	{display->log(NTP_LOG_NO_CONNECTION);	return;};
	struct tm	info;
	if (!getLocalTime(&info))		{display->log(NTP_LOG_SYNC_ERROR);	return;}
	
	display->log(NTP_LOG_SYNC_SUCCESS, info.tm_hour, info.tm_min, info.tm_sec, info.tm_mday, 1 + info.tm_mon, 1900 + info.tm_year);
	_time		= 1000 * (3600 * info.tm_hour + 60 * info.tm_min + info.tm_sec);
	_date.d		= info.tm_mday;
	_date.m		= 1 + info.tm_mon;
	_date.wd	= (info.tm_wday == 0) ? 7 : info.tm_wday;
	_date.y		= 1900 + info.tm_year;
}

void	ntpDateTime::update()
{
	//Get the current time in ms since the start of work
	time_t	currTime	= millis();
	time_t	delta		= currTime - _prevUpdateTime;
	_prevUpdateTime		= currTime;
	_time				+= delta;
	//Checking if it is time to synchronize with the universal time
	if (((currTime - _prevSyncTime) >= (1000 * NTP_SYNC_TIMEOUT_S)) || (currTime < _prevSyncTime))
	{
		//Save the current time to calculate the error
		time_t	localTime	= _time;
		_sync();
		display->log(NTP_LOG_SYNC_INACCURACY, _time - localTime);
		_prevSyncTime			= currTime;
		display->date(_date);
	}

	display->time(_time);
};