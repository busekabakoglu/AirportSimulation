//
// Created by Buse Kabakoğlu on 28.10.2018.
//

#ifndef SIMULATION_EVENT_H
#define SIMULATION_EVENT_H
#include "Passenger.h"
#include <iostream>
using namespace std;

class Event {
public:
    int time;
    char ALS;
    Passenger* pas;//eventi gerceklestiren passenger

    Event(int time, char action, Passenger* pas);
   /* Event(const Event& event);
    Event& operator=(const Event& event);
    Event(Event&& event);
    Event& operator=(Event&& event);
    */
};


#endif //SIMULATION_EVENT_H
