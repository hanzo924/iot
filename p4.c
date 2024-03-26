#include <SoftwareSerial.h>
#include "DHT.h"
#define dhtpin 2
#define dhttype DHT11
SoftwareSerial EEBlue(11, 10);
0DHT dht(dhtpin, dhttype);
void setup()
{
    Serial.begin(9600);
    configure_HC05();
    EEBlue.begin(9600);
    Serial.println("The bluetooth gates are open.\n Connect 
    to HC-05 from any other bluetooth device with 0000 OR 
    1234 as pairing key!."); 
    dht.begin();
}
void loop()
{
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();
    Serial.print("Temperature: ");
    delay(100);
    Serial.print(temperature);
    delay(500);
    Serial.print(" °C, Humidity: ");
    delay(100);
    Serial.print(humidity);
    delay(500);
    Serial.println(" %");
    delay(100);
    EEBlue.print("Temperature: ");
    delay(100);
    EEBlue.print(temperature);
    delay(500);
    EEBlue.print(" degree C, Humidity: ");
    delay(100);
    EEBlue.print(humidity);
    delay(500);
    EEBlue.println(" %");
    delay(2000);
}
void configure_HC05()
{
    EEBlue.begin(38400);
    EEBlue.println("AT");
    delay(500);
    EEBlue.println("AT+NAME=USN000");
    delay(1000);
    EEBlue.println("AT+RESET");
    delay(1000);
}