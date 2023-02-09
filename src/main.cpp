#include <Arduino.h>
#include <SD.h>
#include <ArduinoJson.h>
#include <Can.h>
#include "ccp.h"
#include "config.h"


/* Define Joystick connection pins */
#define UP     A1
#define DOWN   A3
#define LEFT   A2
#define RIGHT  A5
#define CLICK  A4

const int SdChipSelect = 9;

// set up variables using the SD utility library functions:
// Sd2Card card;
// SdVolume volume;
// SdFile root;

void onReceive(uint8_t * data, size_t packetSize);

void setup() {
    // Open serial communications
    Serial.begin(115200);

    //Initialize analog pins as inputs
    pinMode(UP,INPUT);
    pinMode(DOWN,INPUT);
    pinMode(LEFT,INPUT);
    pinMode(RIGHT,INPUT);
    pinMode(CLICK,INPUT);
    
    //Pull analog pins high to enable reading of joystick movements
    digitalWrite(UP, HIGH);
    digitalWrite(DOWN, HIGH);
    digitalWrite(LEFT, HIGH);
    digitalWrite(RIGHT, HIGH);
    digitalWrite(CLICK, HIGH);

    Serial.println(F("\nInitializing SD card... "));

    if (!CONFIG.open("config.cfg"))
    {
        Serial.println(F("error opening config file"));
    }

    if (!CONFIG.read())
    {
        Serial.println(F("error reading config file"));
    }

    CONFIG.close();

    Serial.println(F("Initializing CAN..."));

    if (!CCP.init(CCP_BAUD_500)) 
    {
        Serial.println(F("Can't init CAN"));
    }

    // register the receive callback
    CCP.onReceive(onReceive);

    CAN.loopback();
}


void loop() {
    if (digitalRead(CLICK) == 0) 
    {
        CCP.send();
    }      

    delay(100);
}

void onReceive(uint8_t * data, size_t packetSize)
{   
    for (int idx = 0; idx < packetSize; idx++)
    {
        Serial.print((char)data[idx]);
    }

    Serial.println(" ");
}