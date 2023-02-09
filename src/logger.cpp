#include <Can.h>
#include "logger.h"

logger::logger(/* args */)
{
}

logger::~logger()
{
}

void logger::loggerOnReceive(int packetSize)
{
    while (CAN.available()) {
      Serial.print((char)CAN.read());
    }
}