#include <DHT.h>
#include <WiFiEsp.h>
#include <WiFiEspUdp>
#include "SoftwareSerial.h"
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
SoftwareSerial Serial1(6, 7);
char ssid[] = "______";
char pass[] = "_________";
WiFiEspUDP udp;
void setup()
{
    Serial.begin(115200);
    Serial1.begin(19200);
    WiFi.init(&Serial1);
    connectToWiFi();
    Serial.print("Arduino IP Address: ");
    Serial.println(WiFi.localIP());
    dht.begin();
    udp.begin(8888);
}
void loop()
{
    int packetSize = udp.parsePacket();
    if (packetSize)
    {
        char request[packetSize];
        udp.read(request, packetSize);
        request[packetSize] = '\0';
        if (strcmp(request, "GET_HUMIDITY") == 0)
        {
            float humidity = dht.readHumidity();
            char response[10];
            dtostrf(humidity, 4, 2, response);
            udp.beginPacket(udp.remoteIP(), udp.remotePort());
            udp.write(response, strlen(response));
            udp.endPacket();
        }
    }
}
void connectToWiFi()
{
    Serial.println("Connecting to WiFi");
    while (WiFi.status() != WL_CONNECTED)
    {
        if (WiFi.begin(ssid, pass) != WL_CONNECTED)
        {
            Serial.println("Failed to connect to WiFi. Retrying...");
            delay(5000);
        }
    }
    Serial.println("Connected to WiFi");
}

// Python program for UDP
// import socket UDP_IP = "______________"
// UDP_PORT = 8888
// MESSAGE = "GET_HUMIDITY" 
// sock = socket.socket(socket.AF_INET, 
// socket.SOCK_DGRAM) 
// sock.sendto(bytes(MESSAGE, "utf-8"), (UDP_IP, 
// UDP_PORT)) 
// data, addr = sock.recvfrom(1024) 
// print("Received humidity: {data.decode('utf-8')}") 
// sock.close()
