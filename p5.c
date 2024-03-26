#include <SoftwareSerial.h>
const int LED = 13;
const char turnON = '1';
const char turnOFF = '0';
SoftwareSerial EEBlue(11, 10);
void setup()
{
    Serial.begin(9600);
    pinMode(LED, OUTPUT);
    configure_HC05();
    EEBlue.begin(9600);
Serial.println("The bluetooth gates are open.\n Connect 
to HC-05 from any other bluetooth device with 1234 as 
pairing key!."); 
Serial.print("Now You can TURN ON LED by sending '1' 
and TURN OFF by '0'"); 
EEBlue.println("Now You can TURN ON LED by sending '1' 
and TURN OFF by '0'"); } 
void loop() 
{
        char message;
        if (EEBlue.available())
        {
            message = EEBlue.read();
            Serial.write(message);
            if (message == turnON)
            {
                digitalWrite(LED, HIGH);
                Serial.println(" :LED Turned ON");
                EEBlue.println(" :LED Turned ON");
                delay(500);
            }
            else if (message == turnOFF)
            {
                digitalWrite(LED, LOW);
                Serial.println(" :LED Turned OFF");
                EEBlue.println(" :LED Turned OFF");
                delay(500);
            }
        } } 
void configure_HC05()
{
        EEBlue.begin(38400);
        EEBlue.println("AT");
        delay(500);
        EEBlue.println("AT+NAME=USN000");
        delay(1000);
        EEBlue.println("AT+RESET");
        delay(1000); }