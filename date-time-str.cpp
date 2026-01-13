#include <iostream>
#include <ctime>
#include <string>

#include "date-time-str.h"

// #define NULLDTIME "0000-00-00 00:00:00" 
// #define NULLDATE  "0000-00-00"
// #define NULLTIME  "00:00:00" 

std::string getNumDate(int inDate)
{
    if (inDate==0){return "01";};    
    if (inDate<10){return "0" + std::to_string(inDate);};
    return std::to_string(inDate);
};

std::string getNumTime(int inTime)
{
    if (inTime==0){return "00";};
    if (inTime<10){return "0" + std::to_string(inTime);};
    return std::to_string(inTime);
};

struct tm* getTmTime()
{
    time_t current_time = time(NULL);    
    struct tm *curTime = localtime(&current_time);
    return curTime;
};

std::string getNullTime()
{
    std::string nullTime="";
    nullTime = "00:00:00";
    // std::cout << "nullTime: " << nullTime << " (" <<  std::to_string(nullTime.length()) << "int)\n";

    return nullTime;    
};

std::string getNullDate()
{
    std::string nullDate="";
    nullDate = "0000-00-00";
    // std::cout << "nullDate: " << nullDate <<  " (" << std::to_string(nullDate.length()) << "int)\n";

    return nullDate;    
};

std::string getNullDTime()
{
    std::string nulldtime="";
    nulldtime = "0000-00-00 00:00:00";
    // std::cout << "nulldtime: " << nulldtime << " (" << std::to_string(nulldtime.length()) << "int)\n";

    return nulldtime;    
};

std::string getTime()
{
    struct tm *curTime=getTmTime();
    
    // '09:00:00'::TIME AS time_value, 
    std::string outTime="";
    outTime=
    getNumTime(curTime->tm_hour) + ":" +
    getNumTime(curTime->tm_min) + ":" +
    getNumTime(curTime->tm_sec);
    // std::cout << "outTime: " << outTime << " (" << std::to_string(outTime.length()) << "int)\n";

    return outTime;    
};

std::string getDate()
{
    struct tm *curTime=getTmTime();

    // SELECT '2024-01-01'::DATE AS date_value, 
    std::string outDate="";
    outDate= std::to_string(curTime->tm_year + 1900) + "-" + 
    getNumDate(curTime->tm_mon + 1) + "-"+ 
    getNumDate(curTime->tm_mday);
    // std::cout << "outDate: " << outDate << " (" << std::to_string(outDate.length()) << "int)\n";

    return outDate;    
};

std::string getDTime()
{
    struct tm *curTime=getTmTime();
    
    // '2024-01-01 09:00:00'::TIMESTAMP AS timestamp_value.  
    std::string outdtime="";
    outdtime= std::to_string(curTime->tm_year + 1900) + "-" + 
    getNumDate(curTime->tm_mon + 1) + "-"+ 
    getNumDate(curTime->tm_mday) + " " + 
    getNumTime(curTime->tm_hour) + ":" +
    getNumTime(curTime->tm_min) + ":" +
    getNumTime(curTime->tm_sec);
    // std::cout << "outdtime: " << outdtime << " (" << std::to_string(outdtime.length()) << "int)\n";

    return outdtime;    
};

int outTime()
{
    std::string oTime="";
    
    oTime=getDTime();
    std::cout << "DTime: " << oTime << " (" <<  std::to_string(oTime.length()) << "char)\n";

    oTime=getDate();
    std::cout << "Date: " << oTime << " (" <<  std::to_string(oTime.length()) << "char)\n";

    oTime=getTime();
    std::cout << "Time: " << oTime << " (" <<  std::to_string(oTime.length()) << "char)\n";

    oTime=getNullDTime();
    std::cout << "nullDTime: " << oTime << " (" <<  std::to_string(oTime.length()) << "char)\n";

    oTime=getNullDate();
    std::cout << "nullDate: " << oTime << " (" <<  std::to_string(oTime.length()) << "char)\n";

    oTime=getNullTime();
    std::cout << "nullTime: " << oTime << " (" <<  std::to_string(oTime.length()) << "char)\n";

    return 0;
};