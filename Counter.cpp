//
// Created by Buse Kabakoglu on 28.10.2018.
//

#include "Counter.h"
Counter::Counter() {
    this->isEmpty = true;
    this->timeToBeFree = 0;

}
void Counter::updateCounter(int minute) {
    this->timeToBeFree = minute; //ne counter i olduguna bagli passenger ın lug ya da sec ini alicak
}