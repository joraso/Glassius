/*

Molecular Dynamics Workshop
Joe Raso, Spring 2019
Copyright © 2019 Joe Raso.
All rights reserved.

*/

#include "chaos.hpp"

void chaos::seed(double s){
    /* Seeds the random number generator. */
    std::cout << "Seeding random number generation with: " << s << std::endl;
    //std::cout << "maximum random is: " << RAND_MAX << std::endl;
    std::srand(s);
    return;
}

double chaos::random(){
    /* Standard random [0,1] number generation */
    double r = double(std::rand()) / double(RAND_MAX);
    return r;
}

double chaos::gaussian(double mean, double std){
    /* Draws random numbers from a gaussian using the box-muller method */
    double r1 = chaos::random();
    double r2 = chaos::random();
    double z0 = sqrt(-2.0*log(r1))*cos(2.0*M_PI*r2);
    //double z1 = sqrt(-2.0*log(r1))*sin(2.0*M_PI*r2);
    return (z0 * std) + mean;
}

void chaos::test(int n){
    /* Draw random numbers and prints them to "chaostest.csv" */
    double r;
    
    // Opening the file
    std::ofstream chaosfile;
    chaosfile.open("Data/chaostest.csv");
    
    for(int i=0;i<n;i++){
        // change the function you want to test here:
        r = gaussian(3.0, 2);
        chaosfile << r << std::endl;
    }
    chaosfile.close();
    return;
}
