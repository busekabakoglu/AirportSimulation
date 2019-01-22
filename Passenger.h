//
// Created by Buse Kabakoğlu on 28.10.2018.
//

#ifndef SIMULATION_PASSENGER_H
#define SIMULATION_PASSENGER_H
#include "Counter.h"

class Passenger {
public:
    int arrival;
    int flight;
    int luggingTime;
    int secTime;
    bool isVIP;
    bool isThereLug;
    int timeWaited;
    Counter* counter;

    Passenger(int arrival, int flight,int lugging,int sec, bool isVIP, bool isThereLug);
};


#endif //SIMULATION_PASSENGER_H
