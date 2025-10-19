# Aurora
![Image](https://github.com/diy4hobby/Aurora/blob/assets/photo_2025-10-19_20-34-56.jpg)

**Aurora** is a weather informer device, built around the ESP32C3 microcontroller and an 800x480 e-ink display. The device shows the current time, day of the week, date, current weather conditions, a two-day weather forecast, and a small event log for monitoring system operation.
The project is written in C++ using classes, which allows easy extension by adding new weather data sources and time synchronization methods. Its flexible architecture enables integration of additional display elements beyond the current configuration, making future expansions straightforward to implement.

## Custom configurations
**Aurora** provides the ability to configure: display language, WiFi settings, time synchronization server, display parameters, and weather settings. All configurations are located in the `globals.h` file and can be customized by the user to suit their needs. Additionally, this file allows extending the configuration by adding new languages, synchronization methods, and more. This flexibility enables users to tailor Aurora to their specific requirements and expand its functionality as needed, ensuring adaptability for various use cases and preferences.

First and foremost, it is necessary to specify the WiFi network connection parameters:
```
//WiFi module definitions
#define 	WIFI_SSID						"XXXXXXXX"
#define 	WIFI_PASSWORD					"XXXXXXXX"
```
These definitions are essential for configuring the device's WiFi module to connect to the specified network. Properly setting these parameters ensures that the device can establish a stable internet connection, which is critical for features such as time synchronization, weather updates and so on. User should replace the placeholders with the actual network SSID and password to enable connectivity in their environment.

## Hardware
The project is based on the XIAO 7.5" ePaper Panel from SeeedStudio, featuring a 7.5-inch monochrome e-ink display with 800x480 resolution. The panel integrates an ESP32-C3 microcontroller, USB-C programming and power interface, 2000mAh rechargeable battery and includes buttons for boot and reset.
Although the project is developed for this platform, it is designed with flexibility to adapt to other hardware platforms and e-ink displays with similar capabilities.
In the current hardware and firmware configuration, the device can operate on battery power for up to 2.5 days.

## Code structure
**Aurora** is a firmware for the ESP32C3 microcontroller, though support for other platforms is possible without major changes. Currently, it does not support Over-The-Air (OTA) updates.
The main software modules include:
- datetime — responsible for synchronizing time with Internet servers and providing current time information to other modules.
- wifi — manages connection to the WiFi network specified in the project configuration.
- weather — handles forming requests to weather data providers and parsing their responses.
- display — controls rendering of all information onto the e-ink screen.

All these modules are integrated and coordinated in the main aurora.ino file, which serves as the firmware entry point.

## Contributing
The **Aurora** project welcomes contributions that improve or extend its functionality. Whether you want to report issues, suggest enhancements, or submit code changes, your involvement is appreciated.
We appreciate community involvement to help make **Aurora** better for everyone.

## License
The **Aurora** project is distributed under a non-commercial license. It is free to use, modify, and distribute for non-commercial purposes only. Commercial distribution of the source code or any derived works is prohibited

Please note that while the core code is open source with a permissive license, some external modules or libraries used may be subject to different licenses. Contributors should ensure compliance with these third-party licenses when making modifications or redistributing the project.

## Versions
- 1.0.0 - first version, commit for the community. Writed short description.

