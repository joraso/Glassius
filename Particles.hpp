/*
Glassy Dynamics Simulation Module: Particles
Created by Joe Raso, Mon Jun 10 16:31:28 MDT 2019
Copyright © 2019 Joe Raso, All rights reserved.

This module contains the "Particles" object, and it's derivative objects Fluid
and Glass. These object structures contain the static information of th system
including parameters such as it's density and energy. Importantly, calculation
of interparticle forces is carried out here, as it is a function of the system
under simulation.
*/

#ifndef Particles_hpp
#define Particles_hpp

#include <cmath>
#include <fstream>
#include <iostream>
#include "Matrix.hpp"
#include "chaos.hpp"

class Particles{
    /* Base class for systems of monatomic Lennard-Jones Particles */
    public:
        // Constructors
        Particles(double rho, double T, int Nside):
            rho(rho), T(T), Nside(Nside),
            time(0), kinetic_energy(0), potential_energy(0)
            {Initialize();};
        void Initialize();
        // Accessors
        double** r;
        double** v;
        double** f;
        inline Matrix Positions(){return positions;};
        inline Matrix Velocities(){return velocities;};
        inline Matrix Forces(){return forces;};
        inline double KE() {UpdateKinetic(); return kinetic_energy;};
        inline double PE() {return potential_energy;};
        inline double TotalEnergy() {return kinetic_energy + potential_energy;}
        inline double Length(){return sidelength;};
        inline double Number(){return N;};
        inline double Time(){return time;};
        inline void setTime(double t){time = t;};
        inline void setTemp(double temperature){T = temperature;}
        // Common Operations
        void UpdateKinetic();
        void Thermalize();
        // Integration calculations
        virtual void UpdateForces(){return;};
        // File Operations 
        void SaveTrajectory();
        //virtual void SelfScattering(){return;}; to be implemented later
    protected:
        Matrix positions, velocities, forces;
        int N, Nside;
        double lengthscale, sidelength, rho, T, time;
        double kinetic_energy, potential_energy;
};

class Fluid: public Particles {
    /* Derived class for simple Lennard-Jones fluid */
    public:
        Fluid(double rho, double T, double nside):
            Particles(rho, T, nside){UpdateForces(); Thermalize();};
        void UpdateForces();
    //protected:
};

class Glass: public Particles {
    /* Derived class for the Kob-Anderson glass mixture */
    public:
        Glass(double rho, double T, double nside):
            Particles(rho, T, nside){UpdateForces(); Thermalize();};
        void UpdateForces();
    protected:
        int Na = int(0.8*N);
        int Nb = N - Na;
};

#endif /*Particles_hpp*/
