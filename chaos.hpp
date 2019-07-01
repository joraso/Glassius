/*

Molecular Dynamics Workshop
Joe Raso, Spring 2019
Copyright © 2019 Joe Raso.
All rights reserved.

These modules contain the random number generation functions. Currently
(6/4/19), these use the standard c++ library random functions, but are
designed to be easily swapped out and edited for superior random number
generation, if needed.

*/

#ifndef chaos_hpp
#define chaos_hpp

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>

namespace chaos {
    void seed(double);
    //Seeds the random number generator.
    double random(); 
    //Standard random [0,1] number generation
    double gaussian(double, double);
    //Draws random numbers from a gaussian with (mean, std)
    //using the box-muller method.
    void test(int);
    //Function for testing random number generations. prints "chaostest.csv"
    //to the Data folder.
};

#endif /*chaos_hpp*/
