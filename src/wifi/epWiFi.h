#ifndef EP_WIFI_H
#define EP_WIFI_H

#include "../aWiFi.h"

class epWiFi : public aWiFi
{
	public:
		epWiFi();
		~epWiFi();
		bool	connect();
		void	disconnect();
};

#endif