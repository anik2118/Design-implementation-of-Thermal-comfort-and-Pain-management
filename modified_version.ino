#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <LiquidCrystal_I2C.h>
#include <ESP8266WebServer.h>
LiquidCrystal_I2C lcd(0x3F, 16, 2); 
#include <Wire.h>
#include "MAX30105.h"
#include "heartRate.h"
#define BLYNK_TEMPLATE_ID "TMPL6T4Oo4mqI"
#define BLYNK_TEMPLATE_NAME "Quickstart Template"
#define BLYNK_PRINT Serial
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
MAX30105 particleSensor;
const int analogPin = A0;
const int sensor1Pin = D7;     // Digital pin connected to Sensor 1
const int sensor2Pin = D8;     // Digital pin connected to Sensor 2
const int switchControlPin = D6;
//const int emg=A0;
int sensorValue = 0;
int gsr_average = 0;
//int emg_avg = 0;
long sum = 0;
const float metabolicRate = 1.2;  // Adjust this based on activity level
const float clothingInsulation = 0.7; 
char auth[] = "6k-c3gTcrj5tgQCpNtMU0BdrxfWC78w4";  //Enter your Blynk Auth token
char ssid[] = "404";  //Enter your WIFI SSID
char pass[] = "anik8021"; 
DHT dht(D4, DHT11);
BlynkTimer timer;
float vref = 3.3;
float resolution = vref/1023;
float h,t,pmv,ppd;
 
void setup()
{
  Serial.begin(9600);
  pinMode(sensor1Pin, INPUT);
  pinMode(sensor2Pin, INPUT);
  pinMode(switchControlPin, OUTPUT);
  Serial.println("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
    lcd.setCursor(0, 1);
    lcd.print(".........");
  }
  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.println("WiFi connected");
  Serial.println("Initializing...");
  if (!particleSensor.begin(Wire, I2C_SPEED_FAST)) 
  {
    Serial.println("MAX30102 sensor not found");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Heart Beat sensor not found");
    delay(500);
  }
  Serial.println("Place your index finger on the sensor.");
  particleSensor.setup(); 
  particleSensor.setPulseAmplitudeRed(0x0A); 
  particleSensor.setPulseAmplitudeGreen(0); 
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
}
BLYNK_CONNECTED() {

  // Request the latest state from the server
//  Blynk.syncVirtual(VPIN_BUTTON_1);
}

  
void loop()
{ 
  Blynk.run();//Run the Blynk library
  timer.run();//Run the Blynk timer
  DHT11sensor(t, h, pmv ,ppd);
  Heart_Beat();
  gsrf();
  emgs();
  /*send_mail();
  send_mail1();
  send_mail2();
  Serial.print("Body_temperature=");
  Serial.print(ody_temperature);
  Serial.println();*/

}
void DHT11sensor(float& temperature, float& humidity ,float& ppd ,float& pmv) {
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();

  // Calculate PMV
  float airVelocity = .5;  // Modify as needed
  float meanRadiantTemperature = 25.0;  // Modify as needed

  float part1 = 0.303 * exp(-0.036 * metabolicRate);
  float part2 = 0.028 * metabolicRate;
  float part3 = (metabolicRate - clothingInsulation) - 3.05 * (5733 - 6.99 * metabolicRate - 0.00649 * h - meanRadiantTemperature);
  pmv = (((part1 + part2) * part3)/1000);
  pmv = fmaxf(-2.67, fminf(pmv, 3.0));
  // Calculate PPD
  ppd = 100 - 95 * exp(-0.03353 * pow(pmv, 4) - 0.2179 * pow(pmv, 2));
  ppd = fminf(ppd, 19.6);

  Serial.print("PMV");
  Serial.print(pmv);
  Serial.print("PPD");
  Serial.print("temperature");
  Serial.print(temperature);
  Blynk.virtualWrite(V5, pmv);
  Blynk.virtualWrite(V6, ppd);

  delay(2000); // Wait for a moment

  // Display value from sensor 3

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

 
}
void Heart_Beat() {
  float body_temperature = particleSensor.readTemperature();
  Serial.print(body_temperature, 4);

 /* if (checkForBeat(irValue) == true) {
    long delta = millis() - lastBeat;
    lastBeat = millis();
    beatsPerMinute = 60 / (delta / 1000.0);

    if (beatsPerMinute < 255 && beatsPerMinute > 20) {
      rates[rateSpot++] = (byte)beatsPerMinute;
      rateSpot %= RATE_SIZE;
      beatAvg = 0;
      for (byte x = 0; x < RATE_SIZE; x++) beatAvg += rates[x];
      beatAvg /= RATE_SIZE;
      Blynk.virtualWrite(V4, beatAvg);
      Serial.println(beatAvg); // Print beatAvg here
    }*/
    Blynk.virtualWrite(V4,body_temperature);
  }
 void gsrf()
{ Serial.println("going to the gsr sensor");
  digitalWrite(switchControlPin, LOW);  // Connect Sensor 1 // Delay for stabilization
  int gsr_average = analogRead(analogPin);
  Serial.println(gsr_average);
  Blynk.virtualWrite(V2, gsr_average);
}
 
 void emgs()
{ Serial.println("going to the emg_sensor");
  digitalWrite(switchControlPin, HIGH);  // Connect Sensor 2// Delay for stabilization
  int emg_value = analogRead(analogPin);
  Blynk.virtualWrite(V3, emg_value);
  Serial.println("emg_value");
  Serial.println(emg_value);
  delay(2000); 
}







