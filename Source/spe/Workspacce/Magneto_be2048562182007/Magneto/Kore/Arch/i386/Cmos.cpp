#include "cmos.h"

#if !defined ( __CMOS_CPP_ )
#define __CMOS_CPP_

void CMOS::init()
{
 cout<<endl<<"Initializing CMOS";
 initCMOS();
 cout<<"\t\tDONE";
}

void CMOS::initCMOS()
{
 outportb(CMOS_PORT, RTC_STATUS);
 outportb(CMOS_DATA, (inportb(CMOS_DATA) & ~6) | 2);
}

void CMOS::waitUntilClockChanging()
{
 outportb(CMOS_PORT, 10);
 while(inportb(CMOS_DATA) & 128)/* nothing */;
}

unsigned int CMOS::readRTC(unsigned int port, unsigned int val)
{
 unsigned int high_digit, low_digit;
 outportb(port,val);

 high_digit=low_digit=inportb(port+1);

 /* convert from BCD to binary */
 high_digit >>= 4;
 high_digit &= 0x0F;
 low_digit &=0x0F;

 return 10 * high_digit + low_digit;
}

time* CMOS::readSysTime()
{
 time* localTime; 
 unsigned int hr;				/* for 24 to 12 hours conversion */

 waitUntilClockChanging();
	
 localTime->seconds=readRTC(CMOS_PORT, RTC_SEC);
 localTime->minutes=readRTC(CMOS_PORT, RTC_MIN);
 localTime->hours=readRTC(CMOS_PORT, RTC_HOUR);

 /* convert from 24 hours to 12 hours */
 hr=localTime->hours;
	
 if(hr>12)
    hr -= 12;

 localTime->hours=hr;

 return localTime;
}

date* CMOS::readSysDate()
{
 date* date_;
	
 waitUntilClockChanging();
 date_->year=readRTC(CMOS_PORT,RTC_YEAR);
 date_->month=readRTC(CMOS_PORT,RTC_MONTH);
 date_->day=readRTC(CMOS_PORT,RTC_DAYMON);
 date_->year += 2000;
 return date_;
}

#endif
