#include "WiFiEsp.h"
#include "ThingSpeak.h"
#include "DHT.h"
#define dhtpin 2
#define dhttype DHT11
DHT dht(dhtpin, dhttype);
char ssid[] = "_____";
char pass[] = "_______";
unsigned long myChannelNumber = ______;
const char *myWriteAPIKey = "__________";
WiFiEspClient client;
#include "SoftwareSerial.h"
SoftwareSerial Serial1(6, 7);
String myStatus = "";
void setup()
{
    Serial.begin(115200);
    dht.begin();
    Serial1.begin(19200);
    Serial.print("Searching for ESP8266...");
    WiFi.init(&Serial1);
    if (WiFi.status() != WL_CONNECTED)
    {
        Serial.print("Attempting to connect to SSID: ");
        Serial.println(ssid);
        while (WiFi.status() != WL_CONNECTED)
        {
            WiFi.begin(ssid, pass);
            Serial.print(".");
            delay(5000);
        }
        Serial.println("\nConnected.");
    }
    ThingSpeak.begin(client);
}
void loop()
{
    float t = dht.readTemperature();
    float h = dht.readHumidity();
    ThingSpeak.setField(1, t);
    ThingSpeak.setField(2, h);
    ThingSpeak.setStatus(myStatus);
    int x = ThingSpeak.writeFields(myChannelNumber,
                                   myWriteAPIKey);
    if (x == 200)
    {
        Serial.println("Channel update successful.");
    }
    else
    { Serial.println("Problem updating channel. HTTP error 
code " + String(x)); } 
delay(20000);
    }