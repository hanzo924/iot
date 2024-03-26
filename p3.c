void setup()
{
    pinMode(2, INPUT);
    input pinMode(10, OUTPUT);
}
void loop()
{
    int sensor_state = digitalRead(2);
    if (sensor_state == 1)
    {
        digitalWrite(10, HIGH);
    }
    else
    {
        digitalWrite(10, LOW);
    }
}
