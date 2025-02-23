/*
Glassy Dynamics Simulation Module: Integration
Created by Joe Raso, Tue Jun 11 10:42:29 MDT 2019
Copyright © 2019 Joe Raso, All rights reserved.

This mudule contains the superclass for integrators, and all the integration
functions used to advance a particle system in time. Note that the integrator
object is passed a *pointer* to the particle system - this enables polymorphism,
allowing the type of particle system to be switched out.
*/

#ifndef Integration_hpp
#define Integration_hpp

#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include "Particles.hpp"
#include "chaos.hpp"

class Integrator {
    /* Base class for integration functions. */
    public:
        // Constructor
        Integrator(Particles* system, double Temp, double dt, int Nrecord):
            System(system), Temp(Temp), dt(dt), Nrecord(Nrecord), time(0),
            efilename("Data/Energies.csv"), recordtraj(false) {};
        // Accessors
        inline double Temperature() {return Temp;};
        inline void SetTemp(double T) {Temp = T;};
        inline double Time() {return time;};
        inline void SetTime(double t) {System->setTime(t);};
        inline double Getdt() {return dt;};
        inline void Setdt(double t) {dt = t;};
        inline int GetRecord() {return Nrecord;};
        inline void SetRecord(int n) {Nrecord = n;}
        // Switches & Filenames
        inline void SetEnergyFile(string name) {efilename = name;};
        inline void RecordTrajectory(bool rt) {recordtraj = rt;};
        // Inheritor calculations
        void Equilibrate(double t, int Nthermalize);
        void Run(double t);
        virtual void Initialize(){return;};
        virtual void Propigate(){return;};
    protected:
        Particles* System;
        // Parameters
        double Temp, dt, time;
        int Nrecord;
        // File names and Flags
        string efilename;
        bool recordtraj;
};

class Verlet: public Integrator {
    /* Derived class for the Velocity Verlet integrator */
    public:
        // Constructor
        Verlet(Particles* system, double Temp, double dt, int Nrecord):
            Integrator(system, Temp, dt, Nrecord){Initialize();};
        void Initialize();
        void Propigate();
    //protected:
};

class Brownian: public Integrator {
    /* Derived class for the Overdamped Brownian integrator */
    public:
        // Constructor
        Brownian(Particles* system, double Temp, double drag,
                 double dt, int Nrecord):
            Integrator(system, Temp, dt, Nrecord), drag(drag){Initialize();};
        void Initialize();
        void Propigate();
    protected:
        double drag, prefactor;
        Matrix randomforce, F0, X0;
        double** eta;
        double** f0;
        double** x0;
};

#endif /*Integration_hpp*/
