#include <DHT.h>
#include <WiFiEsp.h>
#include <SoftwareSerial.h>
#include <PubSubClient.h>
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
SoftwareSerial Serial1(6, 7);
char ssid[] = "______";
char pass[] = "________";
WiFiEspClient espClient;
PubSubClient client(espClient);
const char *mqtt_server = "mqtt3.thingspeak.com";
const char *publishTopic = "channels/_______/publish";
const char *subscribeTopicFor_Command_1 =
    "channels/________/subscribe/fields/field1";
const unsigned long postingInterval = 20L * 1000L;
unsigned long lastUploadedTime = 0;
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
void reconnect()
{
    while (!client.connected())
    {
        Serial.print("Attempting MQTT connection...");
        if (client.connect("____ID_____", "___username___",
                           "_____pass____"))
        {
            Serial.println("connected");
            client.subscribe(subscribeTopicFor_Command_1);
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
void callback(char *topic, byte *payload, unsigned int length)
{
    String incomingMessage = "";
    for (int i = 0; i < length; i++)
        incomingMessage += (char)payload[i];
    Serial.println("Message arrived [" + String(topic) + "] " +
                   incomingMessage);
}
void publishMessage(const char *topic, String payload,
                    boolean retained)
{
    if (client.publish(topic, payload.c_str(), retained))
    { Serial.println("Message published [" + String(topic) + "]: 
" + payload); } } 
void setup() 
{
            pinMode(LED_BUILTIN, OUTPUT);
            Serial.begin(115200);
            Serial1.begin(19200);
            dht.begin();
            setup_wifi();
            client.setServer(mqtt_server, 1883);
            client.setCallback(callback); }
void loop() 
{
            float temperature = dht.readTemperature();
            if (!client.connected())
            {
                reconnect();
            }
            client.loop();
            if (millis() - lastUploadedTime > postingInterval)
            {
                String dataText = String("field1=" +
                                         String(temperature) + "&status=MQTTPUBLISH");
                publishMessage(publishTopic, dataText, true);
                lastUploadedTime = millis();
            } }