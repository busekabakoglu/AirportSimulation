
#include "Passenger.h"
#include <iostream>
Passenger::Passenger(int arrival, int flight,int lugging, int sec, bool isVIP, bool isThereLug) {
    this->arrival = arrival;
    this->flight = flight;
    this->luggingTime = lugging;
    this->secTime = sec;
    this->isVIP = isVIP;
    this->isThereLug = isThereLug;
    this->timeWaited = 0;
    this->counter = NULL;


}