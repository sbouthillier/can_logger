#include <Can.h>
#include "ccp.h"

typedef struct 
{
    uint32_t    addr;
    uint8_t     length;
} odt_element_t;


CCPClass::CCPClass() : 
    _rxLength(0)
{
}

CCPClass::~CCPClass()
{
}

int CCPClass::init(uint32_t baudRate)
{
    CAN.setPins(10);

    if (!CAN.begin(baudRate))
    {
        return 0;
    }

    CAN.onReceive(_onCanReceive);

    return 1;
}

void CCPClass::close(void)
{
    CAN.end();
}

int CCPClass::send(void)
{
    Serial.print("Sending packet ... ");

    CAN.beginPacket(0x12);
    CAN.write('h');
    CAN.write('e');
    CAN.write('l');
    CAN.write('l');
    CAN.write('o');
    CAN.write('1');
    CAN.write('2');
    CAN.write('3');
    CAN.endPacket();

    return 1;
}

void CCPClass::_onCanReceive(int len)
{
    for (int idx = 0; idx < len; idx++)
    {
        _rxData[idx] = CAN.read();
    }

    if (this._onReceive)
    {
        _onReceive(_rxData, len);
    }
}

void CCPClass::onReceive(void(*callback)(uint8_t *, size_t))
{
    _onReceive = callback;
}

CCPClass CCP;
