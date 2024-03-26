const int ledPin = 13;
void setup() 
{ 
pinMode(ledPin, OUTPUT); 
}
void loop()
{
digitalWrite(ledPin, HIGH); delay(1000);
digitalWrite(ledPin, LOW); delay(2000); 
}
1.2 IR sensor 
void setup()
{
Serial.begin(9600);
pinMode(2,INPUT);
pinMode(10,OUTPUT);
}
void loop()
{
int sensor_state=digitalRead(2);
if(sensor_state==1)
{
Serial.println("Motion Detected");
digitalWrite(10,HIGH); }
else
{
Serial.println("Motion Not Detected"); 
digitalWrite(10,LOW); } }
