/*
Glassy Dynamics Simulation Module: Stopwatch
Created by Joe Raso, Fri Jun 14 16:38:37 MDT 2019
Copyright © 2019 Joe Raso, All rights reserved.

Rudementary clocking functions for the simulation.
*/

#ifndef Stopwatch_hpp
#define Stopwatch_hpp

#include <ctime>
#include <iostream>

class Stopwatch{
    public:
        Stopwatch();
        void StampLaunch();
        void StampComplete();
        void EndStamp();
    protected:
        time_t tici, ticf, ticlast;
};

#endif /*Stopwatch_hpp*/
