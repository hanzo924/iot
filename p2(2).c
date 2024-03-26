#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "DHT.h"
#define dhtpin 2
#define dhttype DHT11
DHT dht(dhtpin, dhttype);
Adafruit_SSD1306 myDisplay(128, 64, &Wire);
void setup()
{
    myDisplay.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    dht.begin();
}
void loop()
{
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();
    myDisplay.clearDisplay();
    myDisplay.setTextSize(1);
    myDisplay.setCursor(0, 0);
    myDisplay.setTextColor(WHITE);
    myDisplay.print("Temperature: ");
    myDisplay.print(temperature);
    myDisplay.println(" °C");
    myDisplay.print("Humidity: ");
    myDisplay.print(humidity);
    myDisplay.println(" %");
    myDisplay.display();
    delay(3000);
}
