/*
Glassy Dynamics Simulation Module: main
Created by Joe Raso, Tue Jun 11 11:19:21 MDT 2019
Copyright © 2019 Joe Raso, All rights reserved.
*/

#include <iostream>
#include <string>
#include "chaos.hpp"
#include "Stopwatch.hpp"
#include "Protocol.hpp"

int main(int argc, const char * argv[]) {

    // Check:
    if(argc != 6){
        std::cout << "Error: wrong number of command line inputs!" << std::endl;
        return 1;
    }

    // Current command line arguments:
    int mode = std::stoi(argv[1]);
    double T = std::stod(argv[2]);
    double relax = std::stod(argv[3]);
    int record = std::stoi(argv[4]);
    int JobID = std::stoi(argv[5]);

    // start the clock
    Stopwatch timer;
    timer.StampLaunch();
    
    // seed the random number generator
    chaos::seed(JobID);
    
    // running the protocol
    
    if (mode==0) {Protocol::KobAndersonTest(T, relax, record, &timer);};
    if (mode==1) {Protocol::SzamelTest(T, relax, record, &timer);};
    //Protocol::LennardJonesTest(5.0 ,1000, &timer);
    //Protocol::DiffusionTest(T, relax, &timer);
    //Protocol::KobAndersonReplication(T, relax, &timer);
    
    // timestamping the end
    timer.EndStamp();
    
    return 0;
}
