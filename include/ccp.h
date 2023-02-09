#ifndef _ccp_h
#define _ccp_h

#include <Arduino.h>

#define CCP_BAUD_125 	        125E3		// CAN speed at 125 kbps
#define CCP_BAUD_250  	        250E3		// CAN speed at 250 kbps
#define CCP_BAUD_500            500E3		// CAN speed at 500 kbps

// Commands
#define CCP_CONNECT             0x01
#define CCP_GET_VERSION         0x1B
#define CCP_EXCHANGE_ID         0x17
#define CCP_GET_SEED            0x12
#define CCP_UNLOCK              0x13
#define CCP_SET_MTA             0x02
#define CCP_DOWNLOAD            0x03
#define CCP_DOWNLOAD_6          0x23
#define CCP_UPLOAD              0x04
#define CCP_SHORT_UP            0x0F
#define CCP_SELECT_CAL_PAGE     0x11
#define CCP_GET_DAQ_SIZE        0x14
#define CCP_SET_DAQ_PTR         0x15
#define CCP_WRITE_DAQ           0x16
#define CCP_START_STOP          0x06
#define CCP_DISCONNECT          0x07
#define CCP_START_STOP_ALL      0x08
#define CCP_SET_S_STATUS        0x0C
#define CCP_GET_S_STATUS        0x0D
#define CCP_BUILD_CHECKSUM      0x0E
#define CCP_CLEAT_MEMORY        0x10
#define CCP_PROGRAM             0x18
#define CCP_PROGRAM_6           0x22
#define CCP_MOVE                0x19
#define CCP_TEST                0x05
#define CCP_GET_ACTIVE_CAL_PAGE 0x09
#define CCP_DIAG_SERVICE        0x20
#define CCP_ACTION_SERVICE      0x21

// Error codes
#define CCP_ACK                 0x00

// Data Transmission Object (DTO)
#define CCP_DTO_CRM             0xFF
#define CCP_DTO_EV              0xFE

class CCPClass {

public:
    CCPClass();
    ~CCPClass();

    int init(uint32_t baudRate);
    void close();

    int send(void);
    void onReceive(void(*callback)(uint8_t *, size_t));

private:
    static void _onCanReceive(int);

protected:
    void (*_onReceive)(uint8_t *, size_t);
    size_t  _rxLength;
    uint8_t _rxData[8];
};

extern CCPClass CCP;

#endif
