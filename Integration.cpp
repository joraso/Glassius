/*
Glassy Dynamics Simulation Module: Integration
Created by Joe Raso, Tue Jun 11 10:42:29 MDT 2019
Copyright © 2019 Joe Raso, All rights reserved.
*/

#include "Integration.hpp"

void Verlet::Propigate(){
    /* Advances the velocity Verlet calculation one step.*/
    int i,k;
    double dt2 = dt*dt;
    int n = System->Number();
    for(i=0;i<n;i++){
        for(k=0;k<3;k++){
            System->r[i][k] += System->v[i][k]*dt + 0.5*System->f[i][k]*dt2;
            System->v[i][k] += 0.5*System->f[i][k]*dt;
        }
    }
    System->UpdateForces();
    for(i=0;i<n;i++){
        for(k=0;k<3;k++){
            System->v[i][k] += 0.5*dt*System->f[i][k];
        }
    }
    System->UpdateKinetic();
    time += dt;
    return;
}

void Verlet::Equilibrate(double t, int Nthermalize){
    /* Advanced the integration for time=t, themostating the system every
    Nthermalize steps. Records into an energy file as it does. */
    
    // Cycling indeces
    int m, n; int steps = int(t/dt);
    int cycles = int(steps/Nrecord);
    int s = 0; // thermostat counter
    
    // Retrieving the system time
    time = System->Time();
    
    // Prepping output file
    std::ofstream energyfile;
    energyfile.open("Data/Energies.csv", std::ios::app);
    
    // File check-stop
    if(!energyfile.is_open()){
        cout << "Error opening energy file!" << endl;
        exit(1);
    }
    
    // Integrating
    for(m=0;m<cycles;m++){
        for(n=0;n<Nrecord;n++){
            Propigate(); s++;
            if(s%Nthermalize==0){System->Thermalize();}
        }
        energyfile << time << ", ";
        energyfile << System->KE() << ", ";
        energyfile << System->PE() << ", ";
        energyfile << System->TotalEnergy() << std::endl;
        //System->SaveTrajectory(); //Uncomment to print trajectory during equilibration.
    }
    
    // Closing the energy file
    energyfile.close();
    
    // Storing the system time
    System->setTime(time);
    
    return;
}

void Verlet::Run(double t){
    /* Advanced the integration for time=t. Records into an energy file AND a 
    trajectory file as it does. Does not themostate the system. */
    
    // Cycling indeces
    int m, n; int steps = int(t/dt);
    int cycles = int(steps/Nrecord);
    
    // Retrieving the system time
    time = System->Time();
    
    // Prepping output file
    std::ofstream energyfile;
    energyfile.open("Data/Energies.csv", std::ios::app);
    
    // File check-stop
    if(!energyfile.is_open()){
        cout << "Error opening energy file!" << endl;
        exit(1);
    }
    
    // Integrating
    for(m=0;m<cycles;m++){
        for(n=0;n<Nrecord;n++){Propigate();}
        energyfile << time << ", ";
        energyfile << System->KE() << ", ";
        energyfile << System->PE() << ", ";
        energyfile << System->TotalEnergy() << std::endl;
        System->SaveTrajectory();
    }
    
    // Closing the energy file
    energyfile.close();
    
    // Storing the system time
    System->setTime(time);
    
    return;
}


