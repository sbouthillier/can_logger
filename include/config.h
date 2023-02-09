#ifndef _config_h
#define _config_h

#include <Arduino.h>

class ConfigClass {

public:
    ConfigClass();
    ~ConfigClass();

    int open(const char *filename);
    void close();
    int read();
};

extern ConfigClass CONFIG;

#endif