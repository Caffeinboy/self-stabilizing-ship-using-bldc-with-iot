#define BLYNK_TEMPLATE_ID "TMPL3Oz23dv6x"
#define BLYNK_TEMPLATE_NAME "Reaction Wheel"
#define BLYNK_AUTH_TOKEN "YOUR_BLYNK_TOKEN"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#include <Wire.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

#include <SoftwareSerial.h>
#include <VescUart.h>

// ---------------- WIFI ----------------
char ssid[] = "YOUR_WIFI_NAME";
char pass[] = "YOUR_WIFI_PASSWORD";

// ---------------- VESC ----------------
SoftwareSerial VescSerial(D5, D6); // RX,TX
VescUart vesc;

// ---------------- SENSOR ----------------
Adafruit_BNO055 bno = Adafruit_BNO055(55);

// ---------------- VARIABLES ----------------
float angle;
int rpm;

unsigned long lastBlynkUpdate = 0;

// ---------------- SETUP ----------------
void setup()
{
    Serial.begin(115200);

    // VESC UART
    VescSerial.begin(115200);
    vesc.setSerialPort(&VescSerial);

    // Blynk
    Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

    // BNO055
    if(!bno.begin())
    {
        Serial.println("BNO055 not detected");

        while(1);
    }

    delay(1000);

    bno.setExtCrystalUse(true);

    Serial.println("System Started");
}

// ---------------- LOOP ----------------
void loop()
{
    Blynk.run();

    imu::Vector<3> euler =
    bno.getVector(Adafruit_BNO055::VECTOR_EULER);

    // Roll Axis
    angle = euler.y();

    // ---------------- DEAD ZONE ----------------
    if(abs(angle) <= 3)
    {
        rpm = 0;
    }
    else
    {
        // Proportional RPM Control
        rpm = map(abs(angle),3,30,0,6000);

        // RPM Limit
        rpm = constrain(rpm,0,6000);

        // Direction Control
        if(angle > 0)
        {
            rpm = -rpm;
        }
    }

    // ---------------- SEND RPM TO VESC ----------------
    vesc.setRPM(rpm);

    // ---------------- BLYNK UPDATE ----------------
    if(millis() - lastBlynkUpdate > 100)
    {
        lastBlynkUpdate = millis();

        // Angle Graph
        Blynk.virtualWrite(V0, angle);

        // RPM Graph
        Blynk.virtualWrite(V1, rpm);
    }

    // ---------------- SERIAL DEBUG ----------------
    Serial.print("Angle: ");
    Serial.print(angle);

    Serial.print(" RPM: ");
    Serial.println(rpm);

    delay(20);
}
