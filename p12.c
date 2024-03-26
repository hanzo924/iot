12 subscribe to mqtt broker for temp data
#include <WiFiEsp.h>
#include <SoftwareSerial.h>
#include <PubSubClient.h>
SoftwareSerial Serial1(6, 7);
char ssid[] = "______";
char pass[] = "_________";
WiFiEspClient espClient;
PubSubClient client(espClient);
const char *mqtt_server = "mqtt3.thingspeak.com";
const char *subscribeTopicFor_Field1 =
    "channels/_______/subscribe/fields/field1";
void setup_wifi()
{
    delay(10);
    Serial.print("\nConnecting to ");
    Serial.println(ssid);
    WiFi.init(&Serial1);
    int status = WiFi.begin(ssid, pass);
    while (status != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
        status = WiFi.begin(ssid, pass);
    }
    randomSeed(micros());
    Serial.println("\nWiFi connected\nIP address: ");
    Serial.println(WiFi.localIP());
}
void callback(char *topic, byte *payload, unsigned int length)
{
    String incomingMessage = "";
    for (int i = 0; i < length; i++)
        incomingMessage += (char)payload[i];
    Serial.println("Message arrived [" + String(topic) + "] " +
                   incomingMessage);
}
void reconnect()
{
    while (!client.connected())
    {
        Serial.print("Attempting MQTT connection...");
        if (client.connect("____ID____", "__username__",
                           "___pass___"))
        {
            Serial.println("connected");
            client.subscribe(subscribeTopicFor_Field1);
        }
        else
        {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            delay(5000);
        }
    }
}
void setup()
{
    Serial.begin(115200);
    Serial1.begin(19200);
    setup_wifi();
    client.setServer(mqtt_server, 1883);
    client.setCallback(callback);
}
void loop()
{
    if (!client.connected())
    {
        reconnect();
    }
    client.loop();
}