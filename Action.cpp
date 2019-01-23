#include "Action.h"
#include <iostream>


Action::Action(int passengerNum, int lugCounterNum, int secCounterNum) {
    this->passengerNum = passengerNum;
    this->currentTime = 0;
    for (int i = 0; i < lugCounterNum; i++) {
        lugCounter.push_back((new Counter));
    }
    for (int i = 0; i < secCounterNum; i++) {
        secCounter.push_back((new Counter));
    }
}
//case1 is no priority queue, no vip, no luggage considered
double Action::case1(vector<Passenger*>& passs,int& missedFlight){
    missedFlight=0;
    while(!eventQ.empty()){
        Event* temp = eventQ.top();
        eventQ.pop();

        if(temp->ALS=='S'){
            currentTime = temp->time;
            temp->pas->counter->isEmpty = true;
            if(!secWaitingQ.empty()){
                secWaitingQ.front()->counter = temp->pas->counter;
                secWaitingQ.front()->counter->isEmpty = false;
                eventQ.push(new Event(currentTime+secWaitingQ.front()->secTime,'S'
                        , secWaitingQ.front()));
                secWaitingQ.pop();

            }
            temp->pas->timeWaited = currentTime-temp->pas->arrival;
            if(temp->pas->flight < currentTime){
                missedFlight+=1;
            }

        }
        else if(temp->ALS=='L'){
            currentTime = temp->time;
            temp->pas->counter->isEmpty = true;
            Counter* tempCounter = temp->pas->counter;
            if(whichSCounterEmpty()!=-1){
                temp->pas->counter = secCounter[whichSCounterEmpty()];
                secCounter[whichSCounterEmpty()]->isEmpty=false;
                eventQ.push(new Event(currentTime+temp->pas->secTime,'S',temp->pas));

            }
            else{
                secWaitingQ.push(temp->pas);
            }
            if(!lugWaitingQ.empty()){
                lugWaitingQ.front()->counter = tempCounter;
                lugWaitingQ.front()->counter->isEmpty = false;
                eventQ.push(new Event(currentTime+lugWaitingQ.front()->luggingTime,'L'
                        ,lugWaitingQ.front()));
                lugWaitingQ.pop();
            }

        }
        else{
            currentTime = temp->time;
            if(lugWaitingQ.empty()){
                if(whichLCounterEmpty()!=-1) {
                    temp->pas->counter = lugCounter[whichLCounterEmpty()];
                    lugCounter[whichLCounterEmpty()]->isEmpty = false;
                    eventQ.push(new Event(currentTime+temp->pas->luggingTime,'L',temp->pas));
                }
                else{
                    lugWaitingQ.push(temp->pas);

                }
            }
            else{
                lugWaitingQ.push(temp->pas);
            }

        }

    }
    double sum = 0;
    for(int i =0 ; i<passs.size();i++){
        sum+= passs[i]->timeWaited;
    }
    return sum/(double)passs.size();
}
//case2 only priority queue is considered
double Action::case2(vector<Passenger*>& passs, int& missedFlight){
    missedFlight=0;

    priority_queue <Passenger*,vector<Passenger*>, Priority> lugwaitingPQ;
    priority_queue <Passenger*,vector<Passenger*>, Priority> secwaitingPQ;
    while(!eventQ.empty()){
        Event* temp = eventQ.top();
        eventQ.pop();

        if(temp->ALS=='S'){
            currentTime = temp->time;
            temp->pas->counter->isEmpty = true;
            if(!secwaitingPQ.empty()){
                secwaitingPQ.top()->counter = temp->pas->counter;
                secwaitingPQ.top()->counter->isEmpty = false;
                eventQ.push(new Event(currentTime+secwaitingPQ.top()->secTime,'S'
                        , secwaitingPQ.top()));
                secwaitingPQ.pop();

            }
            temp->pas->timeWaited = currentTime-temp->pas->arrival;
            if(temp->pas->flight < currentTime){
                missedFlight+=1;
            }
        }
        else if(temp->ALS=='L'){
            currentTime = temp->time;
            temp->pas->counter->isEmpty = true;
            Counter* tempCounter = temp->pas->counter;
            if(whichSCounterEmpty()!=-1){
                temp->pas->counter = secCounter[whichSCounterEmpty()];
                secCounter[whichSCounterEmpty()]->isEmpty=false;
                eventQ.push(new Event(currentTime+temp->pas->secTime,'S',temp->pas));

            }
            else{
                secwaitingPQ.push(temp->pas);
            }
            if(!lugwaitingPQ.empty()){
                lugwaitingPQ.top()->counter = tempCounter;
                lugwaitingPQ.top()->counter->isEmpty = false;
                eventQ.push(new Event(currentTime+lugwaitingPQ.top()->luggingTime,'L'
                        ,lugwaitingPQ.top()));
                lugwaitingPQ.pop();
            }

        }
        else{
            currentTime = temp->time;
            if(lugwaitingPQ.empty()){
                if(whichLCounterEmpty()!=-1) {
                    temp->pas->counter = lugCounter[whichLCounterEmpty()];
                    lugCounter[whichLCounterEmpty()]->isEmpty = false;
                    eventQ.push(new Event(currentTime+temp->pas->luggingTime,'L',temp->pas));
                }
                else{
                    lugwaitingPQ.push(temp->pas);

                }
            }
            else{
                lugwaitingPQ.push(temp->pas);
            }

        }

    }
    double sum = 0;
    for(int i =0 ; i<passs.size();i++){
        sum+= passs[i]->timeWaited;
    }
    return sum/(double)passs.size();

}
//only vip is considered
double Action::case3(vector<Passenger*>& passs, int& missedFlight){
    missedFlight=0;

    while(!eventQ.empty()){
        Event* temp = eventQ.top();
        eventQ.pop();

        if(temp->ALS=='S'){
            currentTime = temp->time;
            temp->pas->counter->isEmpty = true;
            if(!secWaitingQ.empty()){
                secWaitingQ.front()->counter = temp->pas->counter;
                secWaitingQ.front()->counter->isEmpty = false;
                eventQ.push(new Event(currentTime+secWaitingQ.front()->secTime,'S'
                        , secWaitingQ.front()));
                secWaitingQ.pop();

            }
            temp->pas->timeWaited = currentTime-temp->pas->arrival;
            if(temp->pas->flight < currentTime){
                missedFlight+=1;
            }
        }
        else if(temp->ALS=='L'){
            currentTime = temp->time;
            temp->pas->counter->isEmpty = true;
            Counter* tempCounter = temp->pas->counter;
            if(!lugWaitingQ.empty()){
                lugWaitingQ.front()->counter = tempCounter;
                lugWaitingQ.front()->counter->isEmpty = false;
                eventQ.push(new Event(currentTime+lugWaitingQ.front()->luggingTime,'L'
                        ,lugWaitingQ.front()));
                lugWaitingQ.pop();
            }
            if(temp->pas->isVIP){
                temp->pas->timeWaited = currentTime - temp->pas->arrival;
                if(temp->pas->flight < currentTime){
                    missedFlight+=1;
                }
            }
            else {
                if (whichSCounterEmpty() != -1) {
                    temp->pas->counter = secCounter[whichSCounterEmpty()];
                    secCounter[whichSCounterEmpty()]->isEmpty = false;
                    eventQ.push(new Event(currentTime + temp->pas->secTime, 'S', temp->pas));

                } else {
                    secWaitingQ.push(temp->pas);
                }
            }


        }
        else{
            currentTime = temp->time;
            if(lugWaitingQ.empty()){
                if(whichLCounterEmpty()!=-1) {
                    temp->pas->counter = lugCounter[whichLCounterEmpty()];
                    lugCounter[whichLCounterEmpty()]->isEmpty = false;
                    eventQ.push(new Event(currentTime+temp->pas->luggingTime,'L',temp->pas));
                }
                else{
                    lugWaitingQ.push(temp->pas);

                }
            }
            else{
                lugWaitingQ.push(temp->pas);
            }

        }

    }
    double sum = 0;
    for(int i =0 ; i<passs.size();i++){
        sum+= passs[i]->timeWaited;
    }
    return sum/(double)passs.size();
}
//priority queue and vip is considered, no luggage considered
double Action::case4(vector<Passenger*>& passs, int& missedFlight){
    priority_queue <Passenger*,vector<Passenger*>, Priority> lugwaitingPQ;
    priority_queue <Passenger*,vector<Passenger*>, Priority> secwaitingPQ;
    missedFlight=0;

    while(!eventQ.empty()){
        Event* temp = eventQ.top();
        eventQ.pop();

        if(temp->ALS=='S'){
            currentTime = temp->time;
            temp->pas->counter->isEmpty = true;
            if(!secwaitingPQ.empty()){
                secwaitingPQ.top()->counter = temp->pas->counter;
                secwaitingPQ.top()->counter->isEmpty = false;
                eventQ.push(new Event(currentTime+secwaitingPQ.top()->secTime,'S'
                        , secwaitingPQ.top()));
                secwaitingPQ.pop();

            }
            temp->pas->timeWaited = currentTime-temp->pas->arrival;
            if(temp->pas->flight < currentTime){
                missedFlight+=1;
            }
        }
        else if(temp->ALS=='L'){
            currentTime = temp->time;
            temp->pas->counter->isEmpty = true;
            Counter* tempCounter = temp->pas->counter;
            if(!lugwaitingPQ.empty()){
                lugwaitingPQ.top()->counter = tempCounter;
                lugwaitingPQ.top()->counter->isEmpty = false;
                eventQ.push(new Event(currentTime+lugwaitingPQ.top()->luggingTime,'L'
                        ,lugwaitingPQ.top()));
                lugwaitingPQ.pop();
            }
            if(temp->pas->isVIP){
                temp->pas->timeWaited = currentTime - temp->pas->arrival;
                if(temp->pas->flight < currentTime){
                    missedFlight+=1;
                }

            }
            else {
                if (whichSCounterEmpty() != -1) {
                    temp->pas->counter = secCounter[whichSCounterEmpty()];
                    secCounter[whichSCounterEmpty()]->isEmpty = false;
                    eventQ.push(new Event(currentTime + temp->pas->secTime, 'S', temp->pas));

                } else {
                    secwaitingPQ.push(temp->pas);
                }
            }


        }
        else{
            currentTime = temp->time;
            if(lugwaitingPQ.empty()){
                if(whichLCounterEmpty()!=-1) {
                    temp->pas->counter = lugCounter[whichLCounterEmpty()];
                    lugCounter[whichLCounterEmpty()]->isEmpty = false;
                    eventQ.push(new Event(currentTime+temp->pas->luggingTime,'L',temp->pas));
                }
                else{
                    lugwaitingPQ.push(temp->pas);

                }
            }
            else{
                lugwaitingPQ.push(temp->pas);
            }

        }

    }
    double sum = 0;
    for(int i =0 ; i<passs.size();i++){
        sum+= passs[i]->timeWaited;
    }
    return sum/(double)passs.size();

}
//case5 only online ticket is considered
double Action::case5(vector<Passenger*>& passs, int& missedFlight){
    missedFlight=0;

    while(!eventQ.empty()){
        Event* temp = eventQ.top();
        eventQ.pop();

        if(temp->ALS=='S'){
            currentTime = temp->time;
            temp->pas->counter->isEmpty = true;
            if(!secWaitingQ.empty()){
                secWaitingQ.front()->counter = temp->pas->counter;
                secWaitingQ.front()->counter->isEmpty = false;
                eventQ.push(new Event(currentTime+secWaitingQ.front()->secTime,'S'
                        , secWaitingQ.front()));
                secWaitingQ.pop();

            }
            temp->pas->timeWaited = currentTime-temp->pas->arrival;
            if(temp->pas->flight < currentTime){
                missedFlight+=1;
            }

        }
        else if(temp->ALS=='L'){
            currentTime = temp->time;
            if(temp->pas->isThereLug) {//luggage varsa
                temp->pas->counter->isEmpty = true;
                Counter *tempCounter = temp->pas->counter;
                if (whichSCounterEmpty() != -1) {
                    temp->pas->counter = secCounter[whichSCounterEmpty()];
                    secCounter[whichSCounterEmpty()]->isEmpty = false;
                    eventQ.push(new Event(currentTime + temp->pas->secTime, 'S', temp->pas));

                } else {
                    secWaitingQ.push(temp->pas);
                }
                if (!lugWaitingQ.empty()) {
                    lugWaitingQ.front()->counter = tempCounter;
                    lugWaitingQ.front()->counter->isEmpty = false;
                    eventQ.push(new Event(currentTime + lugWaitingQ.front()->luggingTime, 'L', lugWaitingQ.front()));
                    lugWaitingQ.pop();
                }
            }
            else{
                if (whichSCounterEmpty() != -1) {
                    temp->pas->counter = secCounter[whichSCounterEmpty()];
                    secCounter[whichSCounterEmpty()]->isEmpty = false;
                    eventQ.push(new Event(currentTime + temp->pas->secTime, 'S', temp->pas));

                } else {
                    secWaitingQ.push(temp->pas);
                }
            }

        }
        else{
            currentTime = temp->time;
            if(!temp->pas->isThereLug){
                eventQ.push(new Event(currentTime,'L',temp->pas));
            }
            else {
                if (lugWaitingQ.empty()) {
                    if (whichLCounterEmpty() != -1) {
                        temp->pas->counter = lugCounter[whichLCounterEmpty()];
                        lugCounter[whichLCounterEmpty()]->isEmpty = false;
                        eventQ.push(new Event(currentTime + temp->pas->luggingTime, 'L', temp->pas));
                    } else {
                        lugWaitingQ.push(temp->pas);

                    }
                } else {
                    lugWaitingQ.push(temp->pas);
                }
            }

        }

    }
    double sum = 0;
    for(int i =0 ; i<passs.size();i++){
        sum+= passs[i]->timeWaited;
    }
    return sum/(double)passs.size();
}
//case6 priority queue and online ticket considered, no vip
double Action::case6(vector<Passenger*>& passs, int& missedFlight){//priority queue and online ticket
    missedFlight=0;

    priority_queue <Passenger*,vector<Passenger*>, Priority> lugwaitingPQ;
    priority_queue <Passenger*,vector<Passenger*>, Priority> secwaitingPQ;
    while(!eventQ.empty()){
        Event* temp = eventQ.top();
        eventQ.pop();

        if(temp->ALS=='S'){
            currentTime = temp->time;
            temp->pas->counter->isEmpty = true;
            if(!secwaitingPQ.empty()){
                secwaitingPQ.top()->counter = temp->pas->counter;
                secwaitingPQ.top()->counter->isEmpty = false;
                eventQ.push(new Event(currentTime+secwaitingPQ.top()->secTime,'S'
                        , secwaitingPQ.top()));
                secwaitingPQ.pop();

            }
            temp->pas->timeWaited = currentTime-temp->pas->arrival;
            if(temp->pas->flight < currentTime){
                missedFlight+=1;
            }

        }
        else if(temp->ALS=='L'){
            currentTime = temp->time;
            if(temp->pas->isThereLug) {//luggage varsa
                temp->pas->counter->isEmpty = true;
                Counter *tempCounter = temp->pas->counter;
                if (whichSCounterEmpty() != -1) {
                    temp->pas->counter = secCounter[whichSCounterEmpty()];
                    secCounter[whichSCounterEmpty()]->isEmpty = false;
                    eventQ.push(new Event(currentTime + temp->pas->secTime, 'S', temp->pas));

                } else {
                    secwaitingPQ.push(temp->pas);
                }
                if (!lugwaitingPQ.empty()) {
                    lugwaitingPQ.top()->counter = tempCounter;
                    lugwaitingPQ.top()->counter->isEmpty = false;
                    eventQ.push(new Event(currentTime + lugwaitingPQ.top()->luggingTime, 'L', lugwaitingPQ.top()));
                    lugwaitingPQ.pop();
                }
            }
            else{
                if (whichSCounterEmpty() != -1) {
                    temp->pas->counter = secCounter[whichSCounterEmpty()];
                    secCounter[whichSCounterEmpty()]->isEmpty = false;
                    eventQ.push(new Event(currentTime + temp->pas->secTime, 'S', temp->pas));

                } else {
                    secwaitingPQ.push(temp->pas);
                }
            }

        }
        else{
            currentTime = temp->time;
            if(!temp->pas->isThereLug){
                eventQ.push(new Event(currentTime,'L',temp->pas));
            }
            else {
                if (lugwaitingPQ.empty()) {
                    if (whichLCounterEmpty() != -1) {
                        temp->pas->counter = lugCounter[whichLCounterEmpty()];
                        lugCounter[whichLCounterEmpty()]->isEmpty = false;
                        eventQ.push(new Event(currentTime + temp->pas->luggingTime, 'L', temp->pas));
                    } else {
                        lugwaitingPQ.push(temp->pas);

                    }
                } else {
                    lugwaitingPQ.push(temp->pas);
                }
            }

        }

    }
    double sum = 0;
    for(int i =0 ; i<passs.size();i++){
        sum+= passs[i]->timeWaited;
    }
    return sum/(double)passs.size();

}
//case7 online ticket and vip is considered, no priority q
double Action::case7(vector<Passenger*>& passs, int& missedFlight){
    missedFlight=0;

    while(!eventQ.empty()){
        Event* temp = eventQ.top();
        eventQ.pop();

        if(temp->ALS=='S'){
            currentTime = temp->time;
            temp->pas->counter->isEmpty = true;
            if(!secWaitingQ.empty()){
                secWaitingQ.front()->counter = temp->pas->counter;
                secWaitingQ.front()->counter->isEmpty = false;
                eventQ.push(new Event(currentTime+secWaitingQ.front()->secTime,'S'
                        , secWaitingQ.front()));
                secWaitingQ.pop();

            }
            temp->pas->timeWaited = currentTime-temp->pas->arrival;
            if(temp->pas->flight < currentTime){
                missedFlight+=1;
            }

        }
        else if(temp->ALS=='L'){
            currentTime = temp->time;
            if(temp->pas->isThereLug) {
                temp->pas->counter->isEmpty = true;
                Counter *tempCounter = temp->pas->counter;
                if (temp->pas->isVIP) {
                    temp->pas->timeWaited = currentTime - temp->pas->arrival; if(temp->pas->flight < currentTime){
                        missedFlight+=1;
                    }

                    if (!lugWaitingQ.empty()) {
                        lugWaitingQ.front()->counter = tempCounter;
                        lugWaitingQ.front()->counter->isEmpty = false;
                        eventQ.push(
                                new Event(currentTime + lugWaitingQ.front()->luggingTime, 'L', lugWaitingQ.front()));
                        lugWaitingQ.pop();
                    }
                }
                else {
                    if (whichSCounterEmpty() != -1) {
                        temp->pas->counter = secCounter[whichSCounterEmpty()];
                        secCounter[whichSCounterEmpty()]->isEmpty = false;
                        eventQ.push(new Event(currentTime + temp->pas->secTime, 'S', temp->pas));

                    } else {
                        secWaitingQ.push(temp->pas);
                    }

                    if (!lugWaitingQ.empty()) {
                        lugWaitingQ.front()->counter = tempCounter;
                        lugWaitingQ.front()->counter->isEmpty = false;
                        eventQ.push(
                                new Event(currentTime + lugWaitingQ.front()->luggingTime, 'L', lugWaitingQ.front()));
                        lugWaitingQ.pop();
                    }

                }
            }
            else {
                if (whichSCounterEmpty() != -1) {
                    if(!temp->pas->isVIP) {
                        temp->pas->counter = secCounter[whichSCounterEmpty()];
                        secCounter[whichSCounterEmpty()]->isEmpty = false;
                        eventQ.push(new Event(currentTime + temp->pas->secTime, 'S', temp->pas));
                    }

                } else {
                    secWaitingQ.push(temp->pas);
                }
            }


        }
        else{
            currentTime = temp->time;
            if(temp->pas->isVIP && !temp->pas->isThereLug){
                temp->pas->timeWaited = currentTime-temp->pas->arrival; if(temp->pas->flight < currentTime){
                    missedFlight+=1;
                }

            }
            else {
                if (!temp->pas->isThereLug) {
                    eventQ.push(new Event(currentTime, 'L', temp->pas));
                } else {
                    if (lugWaitingQ.empty()) {
                        if (whichLCounterEmpty() != -1) {
                            temp->pas->counter = lugCounter[whichLCounterEmpty()];
                            lugCounter[whichLCounterEmpty()]->isEmpty = false;
                            eventQ.push(new Event(currentTime + temp->pas->luggingTime, 'L', temp->pas));
                        } else {
                            lugWaitingQ.push(temp->pas);

                        }
                    } else {
                        lugWaitingQ.push(temp->pas);
                    }
                }
            }
        }

    }
    double sum = 0;
    for(int i =0 ; i<passs.size();i++){
        sum+= passs[i]->timeWaited;
    }
    return sum/(double)passs.size();
}
//case8 vip, online ticket and priority queue is considered
double Action::case8(vector<Passenger*>& passs, int& missedFlight){
    missedFlight=0;

    priority_queue <Passenger*,vector<Passenger*>, Priority> lugwaitingPQ;
    priority_queue <Passenger*,vector<Passenger*>, Priority> secwaitingPQ;
    while(!eventQ.empty()){
        Event* temp = eventQ.top();
        eventQ.pop();

        if(temp->ALS=='S'){
            currentTime = temp->time;
            temp->pas->counter->isEmpty = true;
            if(!secwaitingPQ.empty()){
                secwaitingPQ.top()->counter = temp->pas->counter;
                secwaitingPQ.top()->counter->isEmpty = false;
                eventQ.push(new Event(currentTime+secwaitingPQ.top()->secTime,'S'
                        , secwaitingPQ.top()));
                secwaitingPQ.pop();

            }
            temp->pas->timeWaited = currentTime-temp->pas->arrival;
            if(temp->pas->flight < currentTime){
                missedFlight+=1;
            }

        }
        else if(temp->ALS=='L'){
            currentTime = temp->time;
            if(temp->pas->isThereLug) {
                temp->pas->counter->isEmpty = true;
                Counter *tempCounter = temp->pas->counter;
                if (temp->pas->isVIP) {
                    temp->pas->timeWaited = currentTime - temp->pas->arrival;
                    if(temp->pas->flight < currentTime){
                        missedFlight+=1;
                    }

                    if (!lugwaitingPQ.empty()) {
                        lugwaitingPQ.top()->counter = tempCounter;
                        lugwaitingPQ.top()->counter->isEmpty = false;
                        eventQ.push(
                                new Event(currentTime + lugwaitingPQ.top()->luggingTime, 'L', lugwaitingPQ.top()));
                        lugwaitingPQ.pop();
                    }
                }
                else {
                    if (whichSCounterEmpty() != -1) {
                        temp->pas->counter = secCounter[whichSCounterEmpty()];
                        secCounter[whichSCounterEmpty()]->isEmpty = false;
                        eventQ.push(new Event(currentTime + temp->pas->secTime, 'S', temp->pas));

                    } else {
                        secwaitingPQ.push(temp->pas);
                    }

                    if (!lugwaitingPQ.empty()) {
                        lugwaitingPQ.top()->counter = tempCounter;
                        lugwaitingPQ.top()->counter->isEmpty = false;
                        eventQ.push(
                                new Event(currentTime + lugwaitingPQ.top()->luggingTime, 'L', lugwaitingPQ.top()));
                        lugwaitingPQ.pop();
                    }

                }
            }
            else {
                if (whichSCounterEmpty() != -1) {
                    if(!temp->pas->isVIP) {
                        temp->pas->counter = secCounter[whichSCounterEmpty()];
                        secCounter[whichSCounterEmpty()]->isEmpty = false;
                        eventQ.push(new Event(currentTime + temp->pas->secTime, 'S', temp->pas));
                    }

                } else {
                    secwaitingPQ.push(temp->pas);
                }
            }


        }
        else{
            currentTime = temp->time;
            if(temp->pas->isVIP && !temp->pas->isThereLug){
                temp->pas->timeWaited = currentTime-temp->pas->arrival;
                if(temp->pas->flight < currentTime){
                    missedFlight+=1;
                }

            }
            else {
                if (!temp->pas->isThereLug) {
                    eventQ.push(new Event(currentTime, 'L', temp->pas));
                } else {
                    if (lugwaitingPQ.empty()) {
                        if (whichLCounterEmpty() != -1) {
                            temp->pas->counter = lugCounter[whichLCounterEmpty()];
                            lugCounter[whichLCounterEmpty()]->isEmpty = false;
                            eventQ.push(new Event(currentTime + temp->pas->luggingTime, 'L', temp->pas));
                        } else {
                            lugwaitingPQ.push(temp->pas);

                        }
                    } else {
                        lugwaitingPQ.push(temp->pas);
                    }
                }
            }
        }

    }
    double sum = 0;
    for(int i =0 ; i<passs.size();i++){
        sum+= passs[i]->timeWaited;
    }
    return sum/(double)passs.size();
}
int Action:: whichLCounterEmpty(){
    for(int i = 0 ; i<lugCounter.size() ; i++){
        if(lugCounter[i]->isEmpty){
            return i;
        }
    }
    return -1;
}
int Action::whichSCounterEmpty(){
    for(int i = 0 ; i<secCounter.size() ; i++){
        if(secCounter[i]->isEmpty){
            return i;
        }
    }
    return -1;
}
