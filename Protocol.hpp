/*
Glassy Dynamics Simulation Module: Protocol
Created by Joe Raso, Fri Jun 14 15:07:05 MDT 2019
Copyright © 2019 Joe Raso, All rights reserved.

This module constains the namespace "Protocol" which has functions that set up
the whol simulation according to certain regimes. These are the functions to be
invoked in main.cpp
*/

#ifndef Protocol_hpp
#define Protocol_hpp

#include <fstream>
#include <iostream>
#include "Stopwatch.hpp"
#include "Particles.hpp"
#include "Integration.hpp"


namespace Protocol {
    // Szamel Test
    void SzamelTest(double, double, Stopwatch*);
    // Diffusion testing for the ODB integrator.
    void DiffusionTest(double, double, Stopwatch*);
    // Replication of the Kob-Anderson paper 
    void KobAndersonReplication(double, double, Stopwatch*);
    // KA Testing: mixing, equilibration etc.
    void KobAndersonTest(double, Stopwatch*);
    // LJ Testing mixing equilibration etc.
    void LennardJonesTest(double, double, Stopwatch*);
}

#endif /*Protocol_hpp*/
