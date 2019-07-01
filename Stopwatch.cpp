/*
Glassy Dynamics Simulation Module: Stopwatch
Created by Joe Raso, Fri Jun 14 16:38:37 MDT 2019
Copyright © 2019 Joe Raso, All rights reserved.
*/

#include "Stopwatch.hpp"

Stopwatch::Stopwatch(){
    tici = std::time(0);
    ticf = std::time(0);
    ticlast = std::time(0);
    return;
}

void Stopwatch::StampLaunch(){
    char* dt = std::ctime(&tici);
    std::cout << "Simulation launched: " << dt;
    return;   
}

void Stopwatch::StampComplete(){
    time_t lap = std::time(0);
    char* dt = std::ctime(&lap);
    std::cout << "Task completed: " << dt;
    double elapsed = std::difftime(lap, ticlast);
    std::cout << "Elapsed time: " << elapsed << " sec" << std::endl;
    ticlast = lap;
    return;
}

void Stopwatch::EndStamp(){
    ticf = std::time(0);
    char* dt = std::ctime(&ticf);
    std::cout << "Simulation finished: " << dt;
    double elapsed = std::difftime(ticf, tici);
    std::cout << "Total Elapsed time: " << elapsed << " sec" << std::endl;
    return;
}
