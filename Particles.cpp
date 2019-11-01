/*
Glassy Dynamics Simulation Module: Particles
Created by Joe Raso, Mon Jun 10 16:31:28 MDT 2019
Copyright © 2019 Joe Raso, All rights reserved.
*/

#include "Particles.hpp"

#define fastround(x) (x>=0 ? static_cast<int>(x+0.5) : static_cast<int>(x-0.5))

/* Archetypal Particle Class ------------------------------------------------ */

void Particles::Initialize(){
    /* places the particle positions on a square lattice, each at the center of
    a unit cell. Does not initialize energies or forces (they are set to zero
    implicilty, but does randomize velocities and subtract off the cmv. */
    int xi, yi, zi, k, n; n=0;
    
    // Setting other parameters from Nside (number of particles along a side
    // of the box) and rho (number density).
    N = Nside*Nside*Nside;
    lengthscale = pow(rho, -1.0/3.0);
    sidelength = lengthscale*Nside;
    
    //std::cout << "Sidelength is " << sidelength << std::endl;
    //std::cout << "lengthscale is " << lengthscale << std::endl;
    //std::cout << "N is " << N << std::endl;
    //std::cout << "Nside is " << Nside << std::endl;
    
    // Setting up the trajectory matrices. Note the dimensionality is hard-
    // coded to 3.
    positions = Matrix(N,3);
    velocities = Matrix(N,3);
    forces = Matrix(N,3);
    r = positions.Data();
    v = velocities.Data();
    f = forces.Data();
    
    // Tracking the center-of-mass velocity
    double cmv[3];
    for(k=0;k<3;k++){cmv[k] = 0;}
    
    // initializing positions, velocities.
    for(zi=0;zi<Nside;zi++){
       //std::cout << "zi=" << zi << std::endl;
       //std::cout << "zcoord=" << lengthscale*(zi+0.5) << std::endl;
       for(yi=0;yi<Nside;yi++){
         for(xi=0;xi<Nside;xi++){
            r[n][0] = lengthscale*(xi+0.5);
            r[n][1] = lengthscale*(yi+0.5);
            r[n][2] = lengthscale*(zi+0.5);
            for(k=0;k<3;k++){
                v[n][k] = chaos::gaussian(0.0, 1.0);
                cmv[k] += v[n][k];
            }
            n++;
         }
       }
    }
    
    // Subtracting off the center-of-mass velocity, and calculating KE.
    kinetic_energy = 0;
    for(n=0;n<N;n++){
        for(k=0;k<3;k++){
            v[n][k] -= (cmv[k]/N);
            kinetic_energy += (24.0)*v[n][k]*v[n][k];
        }
    }
    return;
}

void Particles::SaveTrajectory(){
    /* Writes positions, velocities and forces to their respective trajectory
    files. */
    ofstream rtraj, vtraj, ftraj;
    
    rtraj.open("Data/rtraj.csv", std::ios::app);
    vtraj.open("Data/vtraj.csv", std::ios::app);
    ftraj.open("Data/ftraj.csv", std::ios::app);
    
    // File check-stops
    if(!rtraj.is_open()){
        cout << "Error opening position-trajectory file!" << endl;
        exit(1);
    }
    if(!vtraj.is_open()){
        cout << "Error opening velocity-trajectory file!" << endl;
        exit(1);
    }
    if(!ftraj.is_open()){
        cout << "Error opening force-trajectory file!" << endl;
        exit(1);
    }
    
    rtraj << positions; vtraj << velocities; ftraj << forces;
    rtraj.close(); vtraj.close(); ftraj.close();
    
}

void Particles::UpdateKinetic(){
    /* Updates the kinetic energy according to the current particle
    velocities */
    int i, k;
    kinetic_energy = 0;
    for(i=0;i<N;i++){ 
        for(k=0;k<3;k++){kinetic_energy += (24.0)*(v[i][k]*v[i][k]);}
    }
    return;
}

void Particles::Thermalize(double Temp){
    /* Thermostats the particle system to temperature T by rescaling the
    velocities of all the particles to be in line with the KE based on the
    ideal gas temperature. Not sure if this belongs here or in the integrator
    section.*/
    int i, k;

    // figuring out the factor needed to readjust the velocities.
    double KEnew = (0.5)*3*Temp*(N-1);
    double scale_factor = sqrt( KEnew / kinetic_energy );
    
    // Zeros KE
    kinetic_energy = 0;
    
    // rescaling all the velocities and re-tally kinetic energy
    for(i=0;i<N;i++){ 
        for(k=0;k<3;k++){
            v[i][k] *= scale_factor;
            kinetic_energy += (24.0)*(v[i][k]*v[i][k]);
        }
    }
    return;
}

/* The Free particle model -------------------------------------------------- */

void Free::UpdateForces(){
    int i, k;
    // Zero out the forces and potential energy
    for(i=0;i<N;i++){for(k=0;k<3;k++){f[i][k]=0;};};
    potential_energy = 0;
    return;
}

/* The Lennard-Jones Fluid -------------------------------------------------- */

void Fluid::UpdateForces(){
    /* Exicutes the forceloop for the simple Lennard-Jones fluid, updating the
    forces and potential energy. */
    int i, j, k;
    
    // Zero out the forces and potential energy
    for(i=0;i<N;i++){for(k=0;k<3;k++){f[i][k]=0;};};
    potential_energy = 0;
    
    // force-loop variables we need
    double rij[3], r2, r2inv, r6inv, fij;
    double Linv = 1.0 / sidelength;
    
    // The force loop (dun dun duuuuun)
    for(i=0;i<N;i++){
        for(j=i+1;j<N;j++){
            // calculating the radius
            r2 = 0;
            for(k=0;k<3;k++){
                rij[k] = r[i][k] - r[j][k];
                // imposing periodic boundary conditions
                rij[k] -= sidelength*fastround(rij[k]*Linv);
                r2 += rij[k]*rij[k];
            }
            r2inv = (1.0)/r2;
            r6inv = r2inv*r2inv*r2inv;
            // Updating the potential energy
            potential_energy += 4*r6inv*(r6inv-1);
            // Updating the forces
            fij = r6inv*r2inv*(r6inv-0.5);
            for(k=0;k<3;k++){
                f[i][k] += fij*rij[k];
                f[j][k] -= fij*rij[k];
            }
        }
    }
    return;
}

/* The Kob-Anderson Glass --------------------------------------------------- */

void Glass::UpdateForces(){
    /* Excicutes the forceloop for the Kob-Anderson glass mixture, updating the
    forces and potential energy. */
    int i, j, k;
    
    // Zero out the forces and potential energy
    for(i=0;i<N;i++){for(k=0;k<3;k++){f[i][k]=0;};};
    potential_energy = 0;
    
    // force-loop variables we need
    double rij[3], r2, r2inv, r6inv, fij;
    double Linv = 1.0 / sidelength;
    
    // factors for adjusting the forces and distances:
    double rABinv = (1.0/0.8);
    double rBBinv = (1.0/0.88);
    double fAB = 1.5*rABinv*rABinv;
    double fBB = 0.5*rBBinv*rABinv;
    
    // The force loop - AA interactions
    for(i=0;i<Na;i++){
        for(j=i+1;j<Na;j++){
            // calculating the radius
            r2 = 0;
            for(k=0;k<3;k++){
                rij[k] = r[i][k] - r[j][k];
                // imposing periodic boundary conditions
                rij[k] -= sidelength*fastround(rij[k]*Linv);
                r2 += rij[k]*rij[k];
            }
            r2inv = (1.0)/r2;
            r6inv = r2inv*r2inv*r2inv;
            // Updating the potential energy
            potential_energy += 4*r6inv*(r6inv-1);
            // Updating the forces
            fij = r6inv*r2inv*(r6inv-0.5);
            for(k=0;k<3;k++){
                f[i][k] += fij*rij[k];
                f[j][k] -= fij*rij[k];
            }
        }
        // AB interactions - sigma = 0.8, epsilon = 1.5
        for(j=Na;j<N;j++){
            r2 = 0;
            for(k=0;k<3;k++){
                rij[k] = (r[i][k] - r[j][k]);
                rij[k] -= sidelength*fastround(rij[k]*Linv);
                // effective radius adjusted by sigma
                rij[k] *= rABinv;
                r2 += rij[k]*rij[k];
            }
            r2inv = (1.0)/r2;
            r6inv = r2inv*r2inv*r2inv;
            // energy and forces adjusted by epsilon and force-factor
            potential_energy += (1.5)*4*r6inv*(r6inv-1);
            fij = fAB*r6inv*r2inv*(r6inv-0.5);
            for(k=0;k<3;k++){
                f[i][k] += fij*rij[k];
                f[j][k] -= fij*rij[k];
            }
        }
    }
    // BB interactions - sigma = 0.88, epsilon = 0.5
    for(i=Na;i<N;i++){
        for(j=i+1;j<N;j++){
            r2 = 0;
            for(k=0;k<3;k++){
                rij[k] = r[i][k] - r[j][k];
                rij[k] -= sidelength*fastround(rij[k]*Linv);
                // effective radius adjusted by sigma
                rij[k] *= rBBinv;
                r2 += rij[k]*rij[k];
            }
            r2inv = (1.0)/r2;
            r6inv = r2inv*r2inv*r2inv;
            // Update me!!
            potential_energy += (0.5)*4*r6inv*(r6inv-1);
            fij = fBB*r6inv*r2inv*(r6inv-0.5);
            for(k=0;k<3;k++){
                f[i][k] += fij*rij[k];
                f[j][k] -= fij*rij[k];
            }
        }
    }
    return;
}
