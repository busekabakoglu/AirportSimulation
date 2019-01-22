//
// Created by Buse Kabakoğlu on 28.10.2018.
//

#ifndef SIMULATION_COUNTER_H
#define SIMULATION_COUNTER_H


class Counter {
public:
    int timeToBeFree;
    bool isEmpty;
    Counter();
    void updateCounter(int minute);
};


#endif //SIMULATION_COUNTER_H
