#ifndef NTP_DATE_TIME_H
#define NTP_DATE_TIME_H

#include "../aDateTime.h"

class ntpDateTime : public aDateTime
{
	private:
		time_t				_time			= 0;
		aDateTime::date_t	_date			= {0};

		time_t				_prevUpdateTime	= 0;	//Previous update time - used to calculate the delta in ms for the clock increment
		time_t				_prevSyncTime	= 0;	//Previous time of clock synchronization with universal time (used with NTP_SYNC_TIMEOUT_S)
		
		//Method of synchronization with universal time
		void					_sync();

	public:
		ntpDateTime();
		~ntpDateTime();
		void		update();
		uint8_t		h()			{return _time / (1000 * 60 * 60);}
		uint8_t		m()			{return (_time / (1000 * 60)) % 60;}
		uint8_t		s()			{return (_time / 1000) % 60;}
		time_t		time()		{return _time;}
};

#endif