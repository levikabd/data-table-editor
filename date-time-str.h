#include <iostream>
#include <ctime>
#include <string>

#define NULLDTIME "0000-00-00 00:00:00" 
#define NULLDATE  "0000-00-00"
#define NULLTIME  "00:00:00" 

std::string getNumDate(int inDate);

std::string getNumTime(int inTime);

struct tm* getTmTime();

std::string getNullTime();

std::string getNullDate();

std::string getNullDTime();

std::string getTime();

std::string getTimeHM();

std::string getDate();

std::string getDTime();

int outTime();