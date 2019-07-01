/*
Glassy Dynamics Simulation Module: Protocol
Created by Joe Raso, Fri Jun 14 15:07:05 MDT 2019
Copyright © 2019 Joe Raso, All rights reserved.
*/

#include "Protocol.hpp"

void Protocol::KobAndersonReplication(double Temp, double relax, Stopwatch* timer){
    /* Replication run of the 1995 Kob-Anderson paper. */
    
    std::cout <<"\n"<< "Replication of Kob-Anderson Glass" <<"\n"<< std::endl;
    std::cout << "Using Parameters:" << std::endl;
    std::cout << "Temperature = " << Temp << std::endl;
    std::cout << "RelaxationTime =  " << relax << std::endl;
    
    double rho = 1000 / (9.4*9.4*9.4);
    
    std::cout << "Density = " << rho << std::endl;
    std::cout << "Boxlength = 9.4" << std::endl;
    
    std::cout << "\n" << "Setting up System..." << std::endl;
    Glass System(rho, 5.0, 10);
    timer->StampComplete();
    
    std::cout << "\n" << "Setting up Simulation..." << std::endl;
    Verlet Simulation(&System, 0.01, 10);
    timer->StampComplete();
    
    
    std::cout << "\n" << "Equilibrating at T = 5.0" << std::endl;
     std::cout << "Running for t = 100" << std::endl;
    std::cout << "Recording every = " << Simulation.GetRecord() << std::endl;
    std::cout << "Thermostating every 50 timesteps" << std::endl;
    Simulation.Equilibrate(1000, 50);
    timer->StampComplete();
    
    std::cout << "\n" << "Equilibrating at T = " << Temp << std::endl;
    std::cout << "Running for t = " << relax << std::endl;
    std::cout << "Recording every = " << Simulation.GetRecord() << std::endl;
    std::cout << "Thermostating every 50 timesteps" << std::endl;
    System.setTemp(Temp);
    System.Thermalize();
    Simulation.Equilibrate(relax, 50);
    timer->StampComplete();
    
    std::cout << "\n" << "Begining Production Run" << std::endl;
    std::cout << "Running for t = " << relax << std::endl;
    if(Temp<1.0){
        Simulation.Setdt(0.02);
    }
    double dt = Simulation.Getdt();
    std::cout << "Timestep = " << dt << std::endl;
    int Npoints = 10000;
    std::cout << "Total Data Points = " << Npoints << std::endl;
    int Nrec = int( relax / (dt*Npoints) );
    Simulation.SetRecord(Nrec);
    std::cout << "Recording every = " << Simulation.GetRecord() << std::endl;
    Simulation.Run(relax);
    timer->StampComplete();
    
    return;
}

void Protocol::KobAndersonTest( double relax ,Stopwatch* timer){

    std::cout <<"\n"<< "Testing Kob-Anderson Glass" <<"\n"<< std::endl;
    std::cout << "Using Parameters:" << std::endl;
    //std::cout << "Temperature = " << Temp << std::endl;
    std::cout << "RelaxationTime =  " << relax << std::endl;
    
    double rho = 1000 / (9.4*9.4*9.4);
    
    std::cout << "Density = " << rho << std::endl;
    std::cout << "Boxlength = 9.4" << std::endl;
    
    std::cout << "\n" << "Setting up System..." << std::endl;
    Glass System(rho, 5.0, 10);
    timer->StampComplete();
    
    std::cout << "\n" << "Setting up Simulation..." << std::endl;
    Verlet Simulation(&System, 0.01, 1);
    timer->StampComplete();
    
    
    std::cout << "\n" << "Equilibrating at T = 5.0" << std::endl;
    std::cout << "Running for t = 100" << std::endl;
    std::cout << "Recording every = " << Simulation.GetRecord() << std::endl;
    std::cout << "Thermostating every 100 timesteps" << std::endl;
    Simulation.Equilibrate(relax, 100);
    timer->StampComplete();
 
    std::cout << "\n" << "Begining Production Run" << std::endl;
    std::cout << "Using Parameters:" << std::endl;

    double dt = Simulation.Getdt();
    std::cout << "Timestep = " << dt << std::endl;
    int Npoints = 10000;
    std::cout << "Total Data Points = " << Npoints << std::endl;
    int Nrec = int( relax / (dt*Npoints) );
    Simulation.SetRecord(Nrec);
    std::cout << "Recording every = " << Simulation.GetRecord() << std::endl;
    Simulation.Run(relax);
    timer->StampComplete();
    
    return;
}

void Protocol::LennardJonesTest(double Temp, double relax, Stopwatch* timer){

    std::cout <<"\n"<< "Testing Lennard-Jones Fluid" <<"\n"<< std::endl;
    std::cout << "Using Parameters:" << std::endl;
    std::cout << "Temperature = " << Temp << std::endl;
    std::cout << "RelaxationTime =  " << relax << std::endl;
    
    double rho = 1000 / (9.4*9.4*9.4);
    
    std::cout << "\n" << "Setting up System..." << std::endl;
    Fluid System(rho, Temp, 10);
    timer->StampComplete();
    
    std::cout << "\n" << "Setting up Simulation..." << std::endl;
    Verlet Simulation(&System, 0.01, 1);
    timer->StampComplete();
    
    std::cout << "\n" << "Equilibrating at T = " << Temp << std::endl;
    std::cout << "Thermostating every 100 timesteps" << std::endl;
    Simulation.Equilibrate(relax, 100);
    timer->StampComplete();
    
    std::cout << "\n" << "Begining Production Run" << std::endl;
    std::cout << "Using Parameters:" << std::endl;
    double dt = Simulation.Getdt();
    std::cout << "Timestep = " << dt << std::endl;
    int Npoints = 100;
    std::cout << "Total Data Points = " << Npoints << std::endl;
    int Nrec = int( relax / (dt*Npoints) );
    Simulation.SetRecord(Nrec);
    std::cout << "Recording every = " << Simulation.GetRecord() << std::endl;
    Simulation.Run(relax);
    timer->StampComplete();
    
    return;
}
