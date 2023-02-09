#ifndef _logger_h
#define _logger_h

class logger
{
private:
    /* data */
public:
    logger(/* args */);
    ~logger();

    void loggerOnReceive(int packetSize);
};


#endif // !__logger_h