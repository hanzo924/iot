#include "WiFiEsp.h"
#include "ThingSpeak.h"
char ssid[] = "_______";
char pass[] = "_________";
unsigned long counterChannelNumber = _______;
const char *myCounterReadAPIKey = "______________";
WiFiEspClient client;
#include "SoftwareSerial.h"
SoftwareSerial Serial1(6, 7);
void setup()
{
    Serial.begin(115200);
    Serial1.begin(19200);
    Serial.print("Searching for ESP8266...");
    WiFi.init(&Serial1);
    delay(5000);
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
        Serial.println("\nConnected");
    }
    ThingSpeak.begin(client);
}
void loop()
{
    int statusCode = 0;
    float temperature =
        ThingSpeak.readFloatField(counterChannelNumber, 1,
                                  myCounterReadAPIKey);
    delay(1000);
    float humidity =
        ThingSpeak.readFloatField(counterChannelNumber, 2,
                                  myCounterReadAPIKey);
    statusCode = ThingSpeak.getLastReadStatus();
    delay(2000);
    if (statusCode == 200)
    { Serial.println("Temperature: " + String(temperature)+" 
deg C"); 
Serial.println("Humidity: "+String(humidity)+" %");
    }
    else
    { Serial.println("Problem reading channel. HTTP error 
code " + String(statusCode));
    }
    delay(15000);
}
