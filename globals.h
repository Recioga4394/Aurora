//Select language for messages and data
#define		LANGUAGE_RUS
//#define		LANGUAGE_ENG


//WiFi module definitions
#define 	WIFI_SSID						"XXXXXXXX"
#define 	WIFI_PASSWORD					"XXXXXXXX"
#define 	WIFI_CONNECT_TIMEOUT_S			10
#ifdef LANGUAGE_RUS
#define		WIFI_LOG_CONNECTING_PROGRESS	"Подключение к WiFi: %d"
#define		WIFI_LOG_CONNECTED				"Подключен к WiFi, SSID: %s, IP: %03d.%03d.%03d.%03d, RSSI: %d dBm"
#define		WIFI_LOG_CONNECTION_FAILED		"Не удалось подключиться к WiFi"
#define		WIFI_LOG_DISCONNECTED			"Отключен от WiFi"
#elifdef LANGUAGE_ENG
#define		WIFI_LOG_CONNECTING_PROGRESS	"Connecting to WiFi: %d"
#define		WIFI_LOG_CONNECTED				"Connected to WiFi, SSID: %s, IP: %03d.%03d.%03d.%03d, RSSI: %d dBm"
#define		WIFI_LOG_CONNECTION_FAILED		"Connecting to WiFi failed"
#define		WIFI_LOG_DISCONNECTED			"Disconnected from WiFi"
#else
#endif


//Datetime module definitions
#define 	NTP_SERVER						"pool.ntp.org"
#define		NTP_GTM_OFFSET_S				10800	//UTC+N
#define		NTP_DAY_LIGHT_OFFSET_S			0
#define		NTP_SYNC_TIMEOUT_S				3600
#ifdef LANGUAGE_RUS
#define		NTP_LOG_NO_CONNECTION			"Нет подключения для синхронизации времени"
#define		NTP_LOG_SYNC_ERROR				"Ошибка синхронизации времени"
#define		NTP_LOG_SYNC_SUCCESS			"Синхронизировано время: %02d:%02d:%02d %02d.%02d.%04d"
#define		NTP_LOG_SYNC_INACCURACY			"Погрешность времени: %d"
#elifdef LANGUAGE_ENG
#define		NTP_LOG_NO_CONNECTION			"No connection for time synchronization"
#define		NTP_LOG_SYNC_ERROR				"Time synchronization error"
#define		NTP_LOG_SYNC_SUCCESS			"Time synchronized:  %02d:%02d:%02d %02d.%02d.%04d"
#define		NTP_LOG_SYNC_INACCURACY			"Time synchronization inaccuracy: %d"
#else
#endif


//Display module definitions
#define		DISPLAY_BORDER_X				6
#define		DISPLAY_BORDER_Y				2
#define		DISPLAY_WIDTH					(800 - 2*DISPLAY_BORDER_X)
#define		DISPLAY_HEIGHT					(480 - 2*DISPLAY_BORDER_Y)
//Log parameters
#define		DISPLAY_LOG_STRINGS_COUNT		3
#define		DISPLAY_LOG_FONT				BreezeSans_Regular_12
#define		DISPLAY_LOG_FONT_HEIGHT			12
//Time and date parameters
#define		DISPLAY_TIME_X					DISPLAY_BORDER_X
#define		DISPLAY_TIME_Y					DISPLAY_BORDER_Y
#define		DISPLAY_TIME_W					DISPLAY_WIDTH/2
#define		DISPLAY_TIME_H					DISPLAY_HEIGHT/5
#define		DISPLAY_TIME_LARGE_FONT			digital_7_112
#define		DISPLAY_TIME_SMALL_FONT			digital_7_64
#define		DISPLAY_DATE_X					DISPLAY_BORDER_X
#define		DISPLAY_DATE_Y					(DISPLAY_TIME_Y + DISPLAY_TIME_H)
#define		DISPLAY_DATE_W					DISPLAY_WIDTH/2
#define		DISPLAY_DATE_H					DISPLAY_HEIGHT/6
#define		DISPLAY_DATE_LARGE_FONT			BreezeSans_Regular_32
#define		DISPLAY_DATE_SMALL_FONT			BreezeSans_Regular_24
#ifdef LANGUAGE_RUS
#define		DISPLAY_WEEKDAY_UNKNOWN			"НЕВАЛИДНО"
#define		DISPLAY_WEEKDAY_MONDAY			"ПОНЕДЕЛЬНИК"
#define		DISPLAY_WEEKDAY_TUESDAY			"ВТОРНИК"
#define		DISPLAY_WEEKDAY_WEDNESDAY		"СРЕДА"
#define		DISPLAY_WEEKDAY_THURSDAY		"ЧЕТВЕРГ"
#define		DISPLAY_WEEKDAY_FRIDAY			"ПЯТНИЦА"
#define		DISPLAY_WEEKDAY_SATURDAY		"СУББОТА"
#define		DISPLAY_WEEKDAY_SUNDAY			"ВОСКРЕСЕНЬЕ"
#define		DISPLAY_MONTH_UNKNOWN			"НЕВАЛИДНО"
#define		DISPLAY_MONTH_JANUARY			"ЯНВАРЯ"
#define		DISPLAY_MONTH_FEBRUARY			"ФЕВРАЛЯ"
#define		DISPLAY_MONTH_MARCH				"МАРТА"
#define		DISPLAY_MONTH_APRIL				"АПРЕЛЯ"
#define		DISPLAY_MONTH_MAY				"МАЯ"
#define		DISPLAY_MONTH_JUNE				"ИЮНЯ"
#define		DISPLAY_MONTH_JULY				"ИЮЛЯ"
#define		DISPLAY_MONTH_AUGUST			"АВГУСТА"
#define		DISPLAY_MONTH_SEPTEMBER			"СЕНТЯБРЯ"
#define		DISPLAY_MONTH_OCTOBER			"ОКТЯБРЯ"
#define		DISPLAY_MONTH_NOVEMBER			"НОЯБРЯ"
#define		DISPLAY_MONTH_DECEMBER			"ДЕКАБРЯ"
#elifdef LANGUAGE_ENG
#define		DISPLAY_WEEKDAY_UNKNOWN			"UNKNOWN"
#define		DISPLAY_WEEKDAY_MONDAY			"MONDAY"
#define		DISPLAY_WEEKDAY_TUESDAY			"TUESDAY"
#define		DISPLAY_WEEKDAY_WEDNESDAY		"WEDNESDAY"
#define		DISPLAY_WEEKDAY_THURSDAY		"THURSDAY"
#define		DISPLAY_WEEKDAY_FRIDAY			"FRIDAY"
#define		DISPLAY_WEEKDAY_SATURDAY		"SATURDAY"
#define		DISPLAY_WEEKDAY_SUNDAY			"SUNDAY"
#define		DISPLAY_MONTH_UNKNOWN			"UNKNOWN"
#define		DISPLAY_MONTH_JANUARY			"JANUARY"
#define		DISPLAY_MONTH_FEBRUARY			"FEBRUARY"
#define		DISPLAY_MONTH_MARCH				"MARCH"
#define		DISPLAY_MONTH_APRIL				"APRIL"
#define		DISPLAY_MONTH_MAY				"MAY"
#define		DISPLAY_MONTH_JUNE				"JUNE"
#define		DISPLAY_MONTH_JULY				"JULY"
#define		DISPLAY_MONTH_AUGUST			"AUGUST"
#define		DISPLAY_MONTH_SEPTEMBER			"SEPTEMBER"
#define		DISPLAY_MONTH_OCTOBER			"OCTOBER"
#define		DISPLAY_MONTH_NOVEMBER			"NOVEMBER"
#define		DISPLAY_MONTH_DECEMBER			"DECEMBER"
#else
#endif
//Current weather parameters
#define		DISPLAY_WEATHER_X				(1 + DISPLAY_BORDER_X + DISPLAY_WIDTH/2)
#define		DISPLAY_WEATHER_Y				DISPLAY_BORDER_Y
#define		DISPLAY_WEATHER_W				(DISPLAY_WIDTH/2 - 1)
#define		DISPLAY_WEATHER_H				DISPLAY_HEIGHT/2
#define		DISPLAY_WEATHER_MEDIUM_FONT		BreezeSans_Regular_32
#define		DISPLAY_WEATHER_LARGE_FONT		BreezeSans_Regular_64
#ifdef LANGUAGE_RUS
#define		DISPLAY_WEATHER_TEMP_FORMAT		"%+2.0f°C"
#define		DISPLAY_WEATHER_PRESSURE_UNITS	"гПа"
#define		DISPLAY_WEATHER_WIND_UNITS		"м/с"
#define		DISPLAY_FORECAST_TEMP_FORMAT	"%+2.0f°C"
#define		DISPLAY_FORECAST_PRESSURE_FORMAT"%-4.0f гПа"
#define		DISPLAY_FORECAST_WIND_FORMAT	"%-3.1f м/с"
#elifdef LANGUAGE_ENG
#define		DISPLAY_WEATHER_TEMP_FORMAT		"%+2.0f°C"
#define		DISPLAY_WEATHER_PRESSURE_UNITS	"hPa"
#define		DISPLAY_WEATHER_WIND_UNITS		"m/s"
#define		DISPLAY_FORECAST_TEMP_FORMAT	"%+2.0f°C"
#define		DISPLAY_FORECAST_PRESSURE_FORMAT"%-4.0f hPa"
#define		DISPLAY_FORECAST_WIND_FORMAT	"%-3.1f m/s"
#else
#endif
//Weather forecast parameters
#define		DISPLAY_FORECAST_X				(1 + DISPLAY_BORDER_X + DISPLAY_WIDTH/2)
#define		DISPLAY_FORECAST_Y				(DISPLAY_WEATHER_H + 3)
#define		DISPLAY_FORECAST_W				(DISPLAY_WIDTH/2 - 1)
#define		DISPLAY_FORECAST_H				DISPLAY_HEIGHT/2
#define		DISPLAY_FORECAST_SMALL_FONT		BreezeSans_Regular_12
#ifdef LANGUAGE_RUS
#define		DISPLAY_FORECAST_MORNING		"УТРО"
#define		DISPLAY_FORECAST_DAY			"ДЕНЬ"
#define		DISPLAY_FORECAST_EVENING		"ВЕЧЕР"
#define		DISPLAY_FORECAST_DAYS			{"ЗАВТРА", "ПОСЛЕЗАВТРА", "ПОСЛЕПОСЛЕЗАВТРА"}
#elifdef LANGUAGE_ENG
#define		DISPLAY_FORECAST_MORNING		"MORNING"
#define		DISPLAY_FORECAST_DAY			"DAY"
#define		DISPLAY_FORECAST_EVENING		"EVENING"
#define		DISPLAY_FORECAST_DAYS			{"TOMORROW", "DAY AFTER TOMORROW", "TWO DAYS AFTER TOMORROW"}
#else
#endif
//Weather history parameters
#define		DISPLAY_WEATHER_HISTORY_X				DISPLAY_BORDER_X
#define		DISPLAY_WEATHER_HISTORY_Y				(DISPLAY_DATE_Y + DISPLAY_DATE_H)
#define		DISPLAY_WEATHER_HISTORY_W				DISPLAY_WIDTH/2
#define		DISPLAY_WEATHER_HISTORY_H				3*DISPLAY_HEIGHT/6
#define		DISPLAY_WEATHER_HISTORY_SMALL_FONT		BreezeSans_Regular_12
#ifdef LANGUAGE_RUS
#elifdef LANGUAGE_ENG
#else
#endif


//Weather module definitions
#ifdef LANGUAGE_RUS
#define		WEATHER_PROVIDER_REQUEST		"https://wttr.in/Minsk?format=j1&lang=ru"
#elifdef LANGUAGE_ENG
#define		WEATHER_PROVIDER_REQUEST		"https://wttr.in/Minsk?format=j1&lang=en"
#else
#endif
#define		WEATHER_SYNC_TIMEOUT_H			1
#define		WEATHER_HISTORY_CAPACITY		48
#ifdef LANGUAGE_RUS
#define		WEATHER_LOG_NO_CONNECTION		"Нет подключения для синхронизации погоды"
#define		WEATHER_LOG_SYNC_RESULT			"Результат синхронизации погоды: %i"
#define		WEATHER_LOG_PARSING_ERROR		"Ошибка парсинга JSON погоды"
#define		WEATHER_LOG_REQUEST_ERROR		"Ошибка запроса погоды"
#elifdef LANGUAGE_ENG
#define		WEATHER_LOG_NO_CONNECTION		"No connection for weather synchronization"
#define		WEATHER_LOG_SYNC_RESULT			"Weather synchronization result: %i"
#define		WEATHER_LOG_PARSING_ERROR		"Weather JSON parsing error"
#define		WEATHER_LOG_REQUEST_ERROR		"Weather request error"
#else
#endif