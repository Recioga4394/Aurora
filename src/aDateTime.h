#ifndef A_DATE_TIME_H
#define A_DATE_TIME_H

#include <Arduino.h>

class aDateTime
{
	public:
		typedef struct
		{
				uint8_t				d;
				uint8_t				m;
				uint8_t				wd;
				uint16_t			y;
		}date_t;

	public:
		virtual			~aDateTime()	{};
		virtual void	update()	= 0;
		virtual uint8_t	h()			= 0;
		virtual uint8_t	m()			= 0;
		virtual uint8_t	s()			= 0;
		virtual time_t	time()		= 0;
};

#endif