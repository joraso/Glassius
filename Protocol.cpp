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
    Verlet Simulation(&System, 5, 0.01, 10);
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
    Simulation.SetTemp(Temp);
    System.Thermalize(Temp);
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

void Protocol::KobAndersonTest(double Temp, double relax, int record,
                               Stopwatch* timer){
    /* Set to mimick the tests run in LAMMPS */

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
    Verlet verlet(&System, 5.0, 0.005, record);
    verlet.SetEnergyFile("Data/Equilibration.csv");
    timer->StampComplete();
    
    std::cout << "\n" << "Mixing at T = 5.0" << std::endl;
    std::cout << "Running for t = 20" << std::endl;
    std::cout << "Timestep = " << verlet.Getdt() << std::endl;
    std::cout << "Steps = 4000" << std::endl;
    std::cout << "Recording every = " << verlet.GetRecord() << std::endl;
    std::cout << "Thermostating every 500 timesteps" << std::endl;
    verlet.Equilibrate(20, 500);
    timer->StampComplete();
 
    std::cout << "\n" << "Equilibrating at T = " << Temp << std::endl;
    std::cout << "Running for t = " << relax << std::endl;
    std::cout << "Timestep = " << verlet.Getdt() << std::endl;
    std::cout << "Steps = " << relax/verlet.Getdt() << std::endl;
    std::cout << "Recording every = " << verlet.GetRecord() << std::endl;
    std::cout << "Thermostating every 500 timesteps" << std::endl;
    verlet.SetTemp(0.5);
    System.Thermalize(0.5);
    verlet.Equilibrate(relax, 500);
    timer->StampComplete();
 
    std::cout << "\n" << "Begining Production Run" << std::endl;
    std::cout << "Running for t = " << 1.5*relax << std::endl;
    std::cout << "Timestep = " << verlet.Getdt() << std::endl;
    std::cout << "Steps = " << (1.5*relax)/verlet.Getdt() << std::endl;
    std::cout << "Recording every = " << verlet.GetRecord() << std::endl;
    verlet.SetTime(0);
    verlet.SetEnergyFile("Data/Energies.csv");
    verlet.RecordTrajectory(true);
    verlet.Run(1.5*relax);
    timer->StampComplete();
    
    return;
}

void Protocol::SzamelTest(double Temp, double relax, int record,
                               Stopwatch* timer){

    std::cout <<"\n"<< "Testing Szamel Brownian Glass" <<"\n"<< std::endl;
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
    Verlet verlet(&System, 5.0, 0.005, record);
    verlet.SetEnergyFile("Data/Equilibration.csv");
    timer->StampComplete();

    std::cout << "\n" << "Mixing at T = 5.0" << std::endl;
    std::cout << "Running for t = 20" << std::endl;
    std::cout << "Timestep = " << verlet.Getdt() << std::endl;
    std::cout << "Steps = 4000" << std::endl;
    std::cout << "Recording every = " << verlet.GetRecord() << std::endl;
    std::cout << "Thermostating every 500 timesteps" << std::endl;
    verlet.Equilibrate(20, 500);
    timer->StampComplete();

    Brownian brownian(&System, Temp, 1.0, 0.00005, record);
    brownian.SetEnergyFile("Data/Equilibration.csv");

    std::cout << "\n" << "Equilibrating at T = " << Temp << std::endl;
    std::cout << "Running for t = " << relax << std::endl;
    std::cout << "Timestep = " << brownian.Getdt() << std::endl;
    std::cout << "Steps = " << relax/brownian.Getdt() << std::endl;
    std::cout << "Recording every = " << brownian.GetRecord() << std::endl;
    brownian.Run(relax);
    timer->StampComplete();
 
    std::cout << "\n" << "Begining Production Run" << std::endl;
    std::cout << "Running for t = " << 1.5*relax << std::endl;
    std::cout << "Timestep = " << brownian.Getdt() << std::endl;
    std::cout << "Steps = " << (1.5*relax)/brownian.Getdt() << std::endl;
    std::cout << "Recording every = " << brownian.GetRecord() << std::endl;
    brownian.SetTime(0);
    brownian.SetEnergyFile("Data/Energies.csv");
    brownian.RecordTrajectory(true);
    brownian.Run(1.5*relax);
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
    Verlet Simulation(&System, Temp, 0.01, 1);
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

void Protocol::DiffusionTest(double Temp, double relax, Stopwatch* timer){

    std::cout <<"\n"<< "Diffusion Testing Brownian Integrator" <<"\n"<< std::endl;
    
    double rho = 1000 / (9.4*9.4*9.4);
    //double rho = 1;
    
    std::cout << "\n" << "Setting up System..." << std::endl;
    Free System(rho, Temp, 10);
    timer->StampComplete();
    
    std::cout << "\n" << "Setting up Simulation..." << std::endl;
    Brownian Simulation(&System, 1.0, 1.0, 0.00005, 1);
    timer->StampComplete();
    
    std::cout << "\n" << "Begining Production Run" << std::endl;
    std::cout << "Using Parameters:" << std::endl;
    double dt = Simulation.Getdt();
    std::cout << "Timestep = " << dt << std::endl;
    Simulation.Propigate();
    int Npoints = 100;
    std::cout << "Total Data Points = " << Npoints << std::endl;
    int Nrec = int( relax / (dt*Npoints) );
    Simulation.SetRecord(Nrec);
    std::cout << "Recording every = " << Simulation.GetRecord() << std::endl;
    Simulation.Run(relax);
    timer->StampComplete();
    
    return;
}
