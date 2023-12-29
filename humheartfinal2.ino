
#include <ESP8266WiFi.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 16, 2); 
#include <Wire.h>
#include "MAX30105.h"
#include "heartRate.h"
#define BLYNK_TEMPLATE_ID "TMPL6T4Oo4mqI"
#define BLYNK_TEMPLATE_NAME "Quickstart Template"
#define BLYNK_PRINT Serial
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

int RelayPin = D0;
MAX30105 particleSensor;
const int GSR = A0;
//const int emg=A0;
int sensorValue = 0;
int gsr_average = 0;
//int emg_avg = 0;
long sum = 0;
const float metabolicRate = 1.0;  // Adjust this based on activity level
const float clothingInsulation = 0.5; 
char auth[] = "6k-c3gTcrj5tgQCpNtMU0BdrxfWC78w4";  //Enter your Blynk Auth token
char ssid[] = "404";  //Enter your WIFI SSID
char pass[] = "anik8021"; 
DHT dht(D4, DHT11);
BlynkTimer timer;
const byte RATE_SIZE = 4; 
byte rates[RATE_SIZE];
byte rateSpot = 0;
long lastBeat = 0;
float beatsPerMinute;
int beatAvg;
float vref = 3.3;
float resolution = vref/1023;
 
void setup()
{
  lcd.init();                       // Initialize the LCD
  lcd.backlight();                  // Turn on the backlight
  lcd.clear();
  Serial.begin(9600);
  pinMode(RelayPin, OUTPUT);
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Connecting to");
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
  Serial.println("WiFi connected");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("WiFi connected");
  lcd.setCursor(0, 1);
  lcd.print("bylnk connected ");
  delay(2000);
  Serial.println("Initializing...");
  if (!particleSensor.begin(Wire, I2C_SPEED_FAST)) 
  {
    Serial.println("Heart Beat sensor not found");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Heart Beat sensor not found");
    while (1);
  }
  Serial.println("Place your index finger on the sensor.");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Place your index finger on the sensor.");
  particleSensor.setup(); 
  particleSensor.setPulseAmplitudeRed(0x0A); 
  particleSensor.setPulseAmplitudeGreen(0); 
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  timer.setInterval(100L, Heart_Beat);
  timer.setInterval(100L, DHT11sensor);
  timer.setInterval(100L, gsrf);
}
BLYNK_CONNECTED() {

  // Request the latest state from the server
//  Blynk.syncVirtual(VPIN_BUTTON_1);
}

  
void loop()
{
  digitalWrite(RelayPin, HIGH);
	delay(3000);
  digitalWrite(RelayPin, LOW);
	delay(3000);
	
  Blynk.run();//Run the Blynk library
  timer.run();//Run the Blynk timer
  for(int i=0;i<500;i++)
  Heart_Beat();
  gsrf();
  send_mail();
  send_mail1();
  send_mail2();

  Serial.print("BPM=");
  Serial.print(beatsPerMinute);
  Serial.print(", Avg BPM=");
  Serial.print(beatAvg); 
  Serial.println();
  delay(5000);

}
void DHT11sensor() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();


  // Calculate PMV
  float airVelocity = .1;  // Modify as needed
  float meanRadiantTemperature = 25.0;  // Modify as needed

  float part1 = 0.303 * exp(-0.036 * metabolicRate);
  float part2 = 0.028 * metabolicRate;
  float part3 = (metabolicRate - clothingInsulation) - 3.05 * (5733 - 6.99 * metabolicRate - 0.00649 * h - meanRadiantTemperature);
  float pmv = (((part1 + part2) * part3)/1000)+2.5;

  // Calculate PPD
  float ppd = (100 - 95 * exp(-0.0335 * pow(pmv, 4) - 0.2179 * pow(pmv, 2)))-82;

  Serial.print("PMV");
  Serial.print(pmv);
  Serial.print("PPD");
  Serial.println(ppd);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("temp: ");
  lcd.print(t);
  lcd.setCursor(0, 1);
  lcd.print("hum: ");
  lcd.print(h);
  delay(2000); // Wait for a moment

  // Display value from sensor 3
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("pmv: ");
  lcd.print(pmv);
  lcd.setCursor(0, 1);
  lcd.print("ppd: ");
  lcd.print(ppd);
  delay(2000);


  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  Blynk.virtualWrite(V0, t);
  Blynk.virtualWrite(V1, h);
  Blynk.virtualWrite(V3, ppd);
  
}
void Heart_Beat(){
  long irValue = particleSensor.getIR();
  if (checkForBeat(irValue) == true)
  {
    long delta = millis() - lastBeat;
    lastBeat = millis();
    beatsPerMinute = 60 / (delta / 1000.0);
    if (beatsPerMinute < 255 && beatsPerMinute > 20)
    {
      rates[rateSpot++] = (byte)beatsPerMinute; 
      rateSpot %= RATE_SIZE; 
      beatAvg = 0;
      for (byte x = 0 ; x < RATE_SIZE ; x++)
      beatAvg += rates[x];
      beatAvg /= RATE_SIZE;
       Blynk.virtualWrite(V4, beatAvg);
    }
  }
    
  if (irValue < 50000){
    beatsPerMinute = 0;
    beatAvg = 0;
  }
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("HR: ");
  lcd.print(beatAvg);
}
 
 void gsrf()
{
   long sum = 0;
  for (int i = 0; i < 10; i++)
  {
    sensorValue = analogRead(GSR);
    sum += sensorValue;
    delay(5);
  }
  gsr_average = sum / 10;
  Blynk.virtualWrite(V2, gsr_average);

  Serial.println(gsr_average);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("GSR: ");
  lcd.print(gsr_average);
}

 /* void emgs()
{
   long sum = 0;
  for (int i = 0; i < 10; i++)
  {
    sensorValue = analogRead(emg);
    sum += sensorValue;
    delay(5);
  }
  emg_avg = sum / 10;
  Blynk.virtualWrite(V4, gsr_average);

  Serial.println(gsr_average);
*/
void send_mail() {
  // Read humidity from the DHT sensor
  float h = dht.readHumidity();
  float airVelocity = .1;  // Modify as needed
  float meanRadiantTemperature = 25.0;  // Modify as needed

  float part1 = 0.303 * exp(-0.036 * metabolicRate);
  float part2 = 0.028 * metabolicRate;
  float part3 = (metabolicRate - clothingInsulation) - 3.05 * (5733 - 6.99 * metabolicRate - 0.00649 * h - meanRadiantTemperature);
  float pmv = (((part1 + part2) * part3)/1000)+2.5;

  // Calculate PPD
  float ppd = (100 - 95 * exp(-0.0335 * pow(pmv, 4) - 0.2179 * pow(pmv, 2)))-82;

  long sum = 0;
  for (int i = 0; i < 10; i++)
  {
    sensorValue = analogRead(GSR);
    sum += sensorValue;
    delay(5);
  }
  gsr_average = sum / 10;

  // Check if humidity exceeds the threshold (50%)
  if (h > 50) {
    // Trigger the emergency alert and send an email notification
    Blynk.logEvent("on_the_fan");
  }
   if ((pmv>0) &&(ppd<20)) 
  {
  Blynk.logEvent("thermal_comfort_level_");
  }
 if (( gsr_average>2) &&( gsr_average<20)) 
  {
  Blynk.logEvent("pain_meter_");
  }

}
void send_mail1() {
  float h = dht.readHumidity();
  // Read humidity from the DHT sensor
  float airVelocity = .1;  // Modify as needed
  float meanRadiantTemperature = 25.0;  // Modify as needed

  float part1 = 0.303 * exp(-0.036 * metabolicRate);
  float part2 = 0.028 * metabolicRate;
  float part3 = (metabolicRate - clothingInsulation) - 3.05 * (5733 - 6.99 * metabolicRate - 0.00649 * h - meanRadiantTemperature);
  float pmv = (((part1 + part2) * part3)/1000)+2.5;

  // Calculate PPD
  float ppd = ((100 - 95 * exp(-0.0335 * pow(pmv, 4) - 0.2179 * pow(pmv, 2)))-82);

  if ((pmv<0) &&(ppd<20)) 
  {
  Blynk.logEvent("thermal_comfort_level_");
  }

}
void send_mail2() {
  long sum = 0;
  for (int i = 0; i < 10; i++)
  {
    sensorValue = analogRead(GSR);
    sum += sensorValue;
    delay(5);
  }
  gsr_average = sum / 10;

 if (( gsr_average>2) &&( gsr_average<20)) 
  {
  Blynk.logEvent("pain_meter_");
  }

}




