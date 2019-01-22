//
// Created by Buse Kabakoğlu on 28.10.2018.
//

#include <iostream>
#include "Event.h"
using namespace std;

Event::Event(int time, char action, Passenger* pas) {
    this->time = time;
    this->ALS = action;
    this->pas = pas;

}

