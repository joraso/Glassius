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
    if(argc != 4){
        std::cout << "Error: wrong number of command line inputs!" << std::endl;
        return 1;
    }

    // Current command line arguments:
    double T = std::stod(argv[1]);
    double relax = std::stod(argv[2]);
    int JobID = std::stoi(argv[3]);

    // start the clock
    Stopwatch timer;
    timer.StampLaunch();
    
    // seed the random number generator
    chaos::seed(JobID);
    
    // running the protocol
    Protocol::KobAndersonReplication(T, relax, &timer);
    //Protocol::KobAndersonTest(100, &timer);
    //Protocol::LennardJonesTest(5.0 ,1000, &timer);

    // timestamping the end
    timer.EndStamp();
    
    return 0;
}
