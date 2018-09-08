#include "x86.h"
#include "iostream.h"

#if !defined ( __CMOS_H_ )
#define __CMOS_H_


#define CMOS_PORT 0x70
#define CMOS_DATA 0x71

#define RTC_SEC		0
#define RTC_MIN		2
#define RTC_HOUR	4
#define RTC_DAYMON	7
#define RTC_MONTH	8
#define RTC_YEAR	9
#define RTC_STATUS	11

typedef struct time time;
struct time
{
 unsigned int seconds;
 unsigned int minutes;
 unsigned int hours;
};

typedef struct date date;
struct date
{
 unsigned int day;
 unsigned int month;
 unsigned int year;
};


class CMOS
{
 private:
 public:
    void init();
    void initCMOS();			//initialize the cmos 
    void waitUntilClockChanging();	//wait until clock is changing
    unsigned int readRTC(unsigned int port, unsigned int value);    //use to read from CMOS   
    time* readSysTime();		//reads and formats the current time from cmos
    date* readSysDate();
    void showCurrentTime();		//displays the current time 
};

#endif
