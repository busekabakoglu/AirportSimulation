#include <iostream>
#include <vector>
#include <fstream>
#include "Counter.h"
#include "Action.h"
#include "Passenger.h"
#include <sstream>
#include <queue>
using namespace std;
int main(int argc, char* argv[]) {
    // below reads the input file
    // in your next projects, you will implement that part as well
    if (argc != 3) {
        cout << "Run the code with the following command: ./project1 [input_file] [output_file]" << endl;
        return 1;
    }
    cout << "input file: " << argv[1] << endl;
    cout << "output file: " << argv[2] << endl;
    ifstream inputFile(argv[1]);
    int passenger;
    int lugCounter;
    int secCounter;
    inputFile>>passenger;
    inputFile>>lugCounter;
    inputFile>>secCounter;

    Action action(passenger, lugCounter, secCounter);
    Action action2(passenger, lugCounter, secCounter);
    Action action3(passenger, lugCounter, secCounter);
    Action action4(passenger, lugCounter, secCounter);
    Action action5(passenger, lugCounter, secCounter);
    Action action6(passenger, lugCounter, secCounter);
    Action action7(passenger, lugCounter, secCounter);
    Action action8(passenger, lugCounter, secCounter);


    vector<int> arrivals;
    int arrival;
    int flight;
    int luggage;
    int sec;
    char isvip;
    char istherel;
    vector<Passenger*> passs;
    for(int i = 0 ; i<passenger ; i++){
        inputFile>>arrival;
        arrivals.push_back(arrival);
        inputFile>>flight;
        inputFile>>luggage;
        inputFile>>sec;
        inputFile>>isvip;
        inputFile>>istherel;
        bool LCheck = false;
        bool VIPCheck = false;
        if(isvip=='V'){
            VIPCheck = true;
        }
        if(istherel=='L'){
            LCheck = true;
        }
        Passenger* tempPas = new Passenger(arrival,flight,
        luggage,sec,VIPCheck,LCheck);
        action.eventQ.push(new Event(arrival,'A',tempPas));
        action2.eventQ.push(new Event(arrival,'A',tempPas));
        action3.eventQ.push(new Event(arrival,'A',tempPas));
        action4.eventQ.push(new Event(arrival,'A',tempPas));
        action5.eventQ.push(new Event(arrival,'A',tempPas));
        action6.eventQ.push(new Event(arrival,'A',tempPas));
        action7.eventQ.push(new Event(arrival,'A',tempPas));
        action8.eventQ.push(new Event(arrival,'A',tempPas));

        passs.push_back(tempPas);
    }
    vector<int> miss ;
    ofstream myFile;
    myFile.open(argv[2]);
    int missedFlight=0;
    double a1=action.case1(passs,missedFlight);
    miss.push_back(missedFlight);
    double a2=action2.case2(passs,missedFlight);
    miss.push_back(missedFlight);
    double a3=action3.case3(passs,missedFlight);
    miss.push_back(missedFlight);
    double a4=action4.case4(passs,missedFlight);
    miss.push_back(missedFlight);
    double a5=action5.case5(passs,missedFlight);
    miss.push_back(missedFlight);
    double a6=action6.case6(passs,missedFlight);
    miss.push_back(missedFlight);
    double a7=action7.case7(passs,missedFlight);
    miss.push_back(missedFlight);
    double a8=action8.case8(passs,missedFlight);
    miss.push_back(missedFlight);

    myFile<<a1<<" "<<miss[0]<<endl;

    myFile<<a2<<" "<<miss[1]<<endl;

    myFile<<a3<<" "<<miss[2]<<endl;

    myFile<<a4<<" "<<miss[3]<<endl;

    myFile<<a5<<" "<<miss[4]<<endl;

    myFile<<a6<<" "<<miss[5]<<endl;

    myFile<<a7<<" "<<miss[6]<<endl;

    myFile<<a8<<" "<<miss[7]<<endl;




    return 0;
}