#include "epWiFi.h"
#include <WiFi.h>
#include "../display/epDisplay.h"
#include "globals.h"

extern epDisplay*		display;


epWiFi::epWiFi()
{

}

epWiFi::~epWiFi()
{

}

bool	epWiFi::connect()
{
	if (WiFi.status() == WL_CONNECTED)	return true;

	WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
	
	uint32_t	timeout	= 1000 * WIFI_CONNECT_TIMEOUT_S / 100;
	
	while ((WiFi.status() != WL_CONNECTED) && (timeout > 0))
	{
		delay(100);
		display->log(WIFI_LOG_CONNECTING_PROGRESS, timeout);
		timeout--;
	}

	if (timeout > 0)
	{	display->log(WIFI_LOG_CONNECTED, WiFi.SSID(), WiFi.localIP()[0], WiFi.localIP()[1], WiFi.localIP()[2], WiFi.localIP()[3], WiFi.RSSI());
		return true;
	}else{
		display->log(WIFI_LOG_CONNECTION_FAILED);
		return false;
	}
}

void	epWiFi::disconnect()
{
	if (WiFi.status() != WL_CONNECTED)		return;
	WiFi.disconnect();
	display->log(WIFI_LOG_DISCONNECTED);
}
