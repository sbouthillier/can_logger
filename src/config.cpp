#include <SD.h>
#include <ArduinoJson.h>
#include "config.h"

const int SdChipSelect = 9;

static File configFile;

ConfigClass::ConfigClass() 
{
}

ConfigClass::~ConfigClass()
{
}

int ConfigClass::open(const char *filename)
{
    pinMode(SS, OUTPUT);

    if (!SD.begin(SdChipSelect)) 
    {
        return 0;
    }

    configFile = SD.open(filename, FILE_READ);

    if (!configFile) 
    {
        return 0;
    }

    return 1;
}

void ConfigClass::close() 
{
    configFile.close();
}

int ConfigClass::read()
{
    // Allocate the JSON document
    //
    // Inside the brackets, 200 is the capacity of the memory pool in bytes.
    // Don't forget to change this value to match your JSON document.
    // Use https://arduinojson.org/v6/assistant to compute the capacity.
    StaticJsonDocument<256> doc;

    DeserializationError error = deserializeJson(doc, configFile);


    // Test if parsing succeeded.
    if (error) {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.f_str());
        return 0;
    }

    for (JsonObject variable : doc["variables"].as<JsonArray>()) {

        // const char* variable_name = variable["name"];
        // uint32_t variable_value   = strtoul(variable["address"], 0 , 16);

        // Serial.print("name: ");
        // Serial.print(variable_name);
        // Serial.print(" address: ");
        // Serial.println(variable_value);
    }

    return 1;
}