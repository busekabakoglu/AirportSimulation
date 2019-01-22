//
// Created by Buse Kabakoğlu on 28.10.2018.
//

#ifndef SIMULATION_ACTION_H
#define SIMULATION_ACTION_H
#include <queue>
#include "Event.h"
#include "Counter.h"
#include "Passenger.h"
#include <iostream>
using namespace std;
class Priority{
public:
    bool operator()(const Passenger* pas1, const Passenger* pas2){
        if(pas1->flight == pas2->flight){
            return pas1->arrival > pas2->arrival;
        }
        return pas1->flight > pas2->flight;
    }
};

class isOrderedBefore{
public:

    bool operator()(const Event* event2,const Event* event1 ){//is event1 ordered before event2
        if(event1->time != event2->time){
            return event1->time < event2->time;
        }
        else if(event1->time==event2->time && event1->ALS!=event2->ALS){
            if(event1->ALS=='S' && (event2->ALS=='L'||event2->ALS=='A')) {
                return true;

            }
            else if(event2->ALS=='S' && (event1->ALS=='L'||event1->ALS=='A')){
                return false;
            }

            else if(event1->ALS=='L' && event2->ALS=='A'){
                return true;
            }
            else if(event2->ALS=='L' && event1->ALS=='A'){
                return false;
            }
            else if(event1->ALS=='A' && (event2->ALS=='S' || event2->ALS=='L')){
                return false;
            }

            else {
                return false;
            }
        }
        else {
            return event1->pas->arrival < event2->pas->arrival;
        }

    }
};
class Action {

public:
    priority_queue<Event*,vector<Event*>,isOrderedBefore> eventQ;
    vector<Counter*> lugCounter;
    vector<Counter*> secCounter;
    queue<Passenger*> lugWaitingQ;
    queue<Passenger*> secWaitingQ;
    int currentTime;
    int passengerNum;

    Action(int passengerNum, int lugCounterNum, int secCounterNum);
    double case1(vector<Passenger*>& passs, int& missedFlight);
    double case2(vector<Passenger*>& passs, int& missedFlight);
    double case3(vector<Passenger*>& passs, int& missedFlight);
    double case4(vector<Passenger*>& passs, int& missedFlight);
    double case5(vector<Passenger*>& passs, int& missedFlight);
    double case6(vector<Passenger*>& passs, int& missedFlight);
    double case7(vector<Passenger*>& passs, int& missedFlight);
    double case8(vector<Passenger*>& passs, int& missedFlight);
    int whichLCounterEmpty();
    int whichSCounterEmpty();
};


#endif //SIMULATION_ACTION_H
