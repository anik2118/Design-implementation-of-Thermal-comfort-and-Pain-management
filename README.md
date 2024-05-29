
# Thermal comfort and Pain management Using IOT connectivity

This project demonstrates how to use an ESP8266 microcontroller to read data from various sensors, display the data on an LCD screen, and send the data to a Blynk app. The system includes a heart rate sensor (MAX30105), a GSR sensor, an EMG sensor, and a DHT11 temperature and humidity sensor.
## Components Used

- ESP8266 Microcontroller
- MAX30105 Heart Rate Sensor
- GSR Sensor
- EMG Sensor
- DHT11 Temperature and Humidity Sensor
- LCD Display with I2C
- WiFi Network

## Libraries Required

- [ESP8266WiFi](https://github.com/esp8266/Arduino)
- [ESP8266HTTPClient](https://github.com/esp8266/Arduino)
- [LiquidCrystal_I2C](https://github.com/johnrickman/LiquidCrystal_I2C)
- [ESP8266WebServer](https://github.com/esp8266/Arduino)
- [Wire](https://github.com/PaulStoffregen/Wire)
- [MAX30105](https://github.com/sparkfun/SparkFun_MAX3010x_Sensor_Library)
- [heartRate](https://github.com/sparkfun/SparkFun_MAX3010x_Sensor_Library/tree/master/src)
- [BlynkSimpleEsp8266](https://github.com/blynkkk/blynk-library)
- [DHT](https://github.com/adafruit/DHT-sensor-library)

## Setup Instructions

1. **Clone the Repository**
   ```bash
   git clone https://github.com/yourusername/esp8266-sensor-monitoring.git
   cd esp8266-sensor-monitoring
   ```

2. **Install Libraries**
   Install the required libraries listed above via the Arduino Library Manager.

3. **Configure WiFi and Blynk**
   Open the code file and update the following lines with your WiFi credentials and Blynk authentication token:
   ```cpp
   char auth[] = "YOUR_BLYNK_AUTH_TOKEN";  // Enter your Blynk Auth token
   char ssid[] = "YOUR_WIFI_SSID";         // Enter your WiFi SSID
   char pass[] = "YOUR_WIFI_PASSWORD";     // Enter your WiFi Password
   ```

4. **Upload the Code**
   Connect your ESP8266 to your computer and upload the code.

## Code Explanation

### Libraries

The code includes several libraries for handling WiFi, HTTP communication, LCD display, sensors, and Blynk integration.

### Constants and Globals

Defines pins, Blynk credentials, and initializes sensor objects.

### Setup Function

- Initializes serial communication and sensor pins.
- Connects to the specified WiFi network.
- Initializes the heart rate sensor and Blynk.
  
### Loop Function

- Runs the Blynk library and timer.
- Reads data from the sensors and sends it to the Blynk app.

### Sensor Functions

- **DHT11sensor:** Reads temperature and humidity, calculates PMV and PPD, and sends data to Blynk.
- **Heart_Beat:** Reads heart rate data and sends it to Blynk.
- **gsrf:** Reads data from the GSR sensor and sends it to Blynk.
- **emgs:** Reads data from the EMG sensor and sends it to Blynk.

## Circuit Diagram

![Circuit_diagram](https://github.com/anik2118/Design-implementation-of-Thermal-comfort-and-Pain-management/assets/155141315/bca11eb4-34c0-468d-bb68-0fab71ce2b00)


## Usage

After uploading the code, the ESP8266 will connect to the WiFi network, initialize the sensors, and start sending data to the Blynk app. You can monitor the sensor data on your Blynk app dashboard.


## Acknowledgments

- [SparkFun MAX3010x Sensor Library](https://github.com/sparkfun/SparkFun_MAX3010x_Sensor_Library)
- [Blynk](https://blynk.io/)
- [Adafruit DHT Sensor Library](https://github.com/adafruit/DHT-sensor-library)

---

