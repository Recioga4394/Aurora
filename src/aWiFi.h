#ifndef A_WIFI_H
#define A_WIFI_H

#include <Arduino.h>

class aWiFi
{
	public:
		virtual			~aWiFi()	{};
		virtual bool	connect()		= 0;
		virtual void	disconnect()	= 0;
};

#endif