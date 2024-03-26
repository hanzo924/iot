#include <DHT.h>
#include <WiFiEsp.h>
#include "SoftwareSerial.h"
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
SoftwareSerial Serial1(6, 7);
char ssid[] = "______";
char pass[] = "________";
WiFiEspServer server(80);
void setup()
{
    Serial.begin(115200);
    Serial1.begin(19200);
    WiFi.init(&Serial1);
    connectToWiFi();
    Serial.print("Arduino IP Address: ");
    Serial.println(WiFi.localIP());
    dht.begin();
    server.begin();
}
void loop()
{
    WiFiEspClient client = server.available();
    if (client)
    {
        Serial.println("New client connected");
        String request = client.readStringUntil('\r');
        Serial.println(request);
        if (request.indexOf("GET_HUMIDITY") != -1)
        {
            float humidity = dht.readHumidity();
            char response[10];
            dtostrf(humidity, 4, 2, response);
            client.println(response);
        }
        client.stop();
        Serial.println("Client disconnected");
    }
}
void connectToWiFi()
{
    if (WiFi.status() != WL_CONNECTED)
    {
        Serial.println("Connecting to WiFi");
        while (WiFi.begin(ssid, pass) != WL_CONNECTED)
        {
            Serial.println("Failed to connect to WiFi. Retrying...");
            delay(5000);
        }
        Serial.println("Connected to WiFi");
    }
}

// Python program for TCP
// import socket TCP_IP = "________________" 
// TCP_PORT = 80 
// def send_tcp_request(request): 
//  with socket.socket(socket.AF_INET,
//  socket.SOCK_STREAM) as s: 
//  s.connect((TCP_IP, TCP_PORT))
//  s.sendall(request.encode()) 
//  response = s.recv(1024).decode() 
//  print("Received response:", response) 
// send_tcp_request("GET_HUMIDITY")