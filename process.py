#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Jun 17 14:50:12 2019

@author: joe
"""

import datetime
import numpy as np

def getTaxis(npoints=100):
    en = np.loadtxt("Energies.csv", delimiter=",")
    return en[-npoints:,0] - en[-(npoints+1),0]

def CalculateFsk(N=1000, Na=800, L=9.4):
    
    # Tri's k-vectors:
    k1 = (2*np.pi/9.40001)*np.asarray([3,3,10])
    k2 = (2*np.pi/9.40001)*np.asarray([6,-9,1])
    k3 = (2*np.pi/9.40001)*np.asarray([9,-6,-1])
    
    # Loading the trajectory
    r = np.loadtxt("rtraj.csv", delimiter=",")
    time = int(r.shape[0]/N)
    taxis = getTaxis(npoints=time-1)
    shape = (time,N,3)
    traj = np.reshape(r, shape)
    del r
    
    # Buckets
    fsk = []; var = []; counts = []
    
    # Calculating Fsk
    for t in range(1,traj.shape[0]):
        rt = traj[t:,:,:]
        r0 = np.roll(traj, t, axis=0)[t:,:,:]
        dr = rt - r0
        dr -= L*np.round(dr/L)
        corr1 = np.average(np.cos(np.dot(dr, k1)), axis=0)
        corr2 = np.average(np.cos(np.dot(dr, k2)), axis=0)
        corr3 = np.average(np.cos(np.dot(dr, k3)), axis=0)
        corrolation = np.concatenate([corr1, corr2, corr3])
        var.append(np.var(corrolation))
        fsk.append(np.average(corrolation))
        counts.append(dr.shape[0])
    
    # Transcribing fsk to file
    fsobj = np.asarray([fsk, var, counts])
    fsobj = np.vstack((taxis, fsobj))
    fsobj = fsobj.transpose()
    np.savetxt("fsk.csv",fsobj, delimiter=",")


def CalculateGr(N=1000, Na=800, L=9.4, sample=100, res=100):
    
    # Loading the trajectory
    r = np.loadtxt("rtraj.csv", delimiter=",")
    time = int(r.shape[0]/N)
    shape = (time,N,3)
    traj = np.reshape(r, shape)
    del r

    # Setting up some things
    rho = Na/(L**3)
    raxis = np.linspace(0, L, num=res, endpoint=False)
    dr = raxis[1]-raxis[0]; raxis += dr/2
    Norm = 2*np.pi*rho*(Na-1)*(raxis**2)*dr
    Nr = int((Na**2 - Na)/2)
    G = []
    
    # Looping
    for t in range(0, traj.shape[0], sample):
        positions = traj[t,:,:]
        delta = np.zeros((Nr, 3)); k = 0
        for i in range(Na):
            for j in range(i+1, Na):
                delta[k,:] = positions[i,:] - positions[j,:]
                k += 1
        delta -= L*np.round(delta/L)
        radii = np.sqrt(np.sum(delta**2, axis=1))
        g, edge = np.histogram(radii,bins=res,range=(0, L))
        G.append(g)
    
    # Restructuring and saving
    G = np.asarray(G)
    counts = np.sum(G, axis=0)
    var = np.var(G/Norm, axis=0)
    G = np.average(G/Norm, axis=0)
    Gobj = np.vstack((raxis, G, var, counts))
    Gobj = Gobj.transpose()
    np.savetxt("gr.csv", Gobj, delimiter=",")
    
def CalculateMSD(N=1000, Na=800, L=9.4):
    
    # Loading the trajectory
    r = np.loadtxt("rtraj.csv", delimiter=",")
    time = int(r.shape[0]/N)
    taxis = getTaxis(npoints=time)
    taxis = taxis - taxis[0]
    shape = (time,N,3)
    traj = np.reshape(r, shape)
    del r
    
    # Buckets
    msd = []; var = []; counts = []
    
    # Looping
    for t in range(0,traj.shape[0]):
        rt = traj[t:,:,:]
        r0 = np.roll(traj, t, axis=0)[t:,:,:]
        dr = rt - r0
        dr -= L*np.round(dr/L)
        msd.append(np.average(np.sum(dr**2, axis=2)))
        var.append(np.var(np.sum(dr**2, axis=2)))
        counts.append(dr.shape[0])
        
    # Transcribing msd to file
    msdobj = np.asarray([msd, var, counts])
    msdobj = np.vstack((taxis, msdobj))
    msdobj = msdobj.transpose()
    np.savetxt("msd.csv",msdobj, delimiter=",")
    
def CalculateCvv(N=1000, Na=800, L=9.4):

    # Loading the trajectory
    v = np.loadtxt("vtraj.csv", delimiter=",")
    time = int(v.shape[0]/N)
    taxis = getTaxis(npoints=time)
    taxis = taxis - taxis[0]
    shape = (time,N,3)
    traj = np.reshape(v, shape)
    del v

    # Buckets
    cvv = []; var = []; counts = []
    
    # Looping
    for t in range(0,traj.shape[0]):
        vt = traj[t:,:,:]
        v0 = np.roll(traj, t, axis=0)[t:,:,:]
        vv = np.sum(vt*v0, axis=2)
        cvv.append(np.average(vv))
        var.append(np.var(vv))
        counts.append(vv.shape[0])
    
    # Transcribing msd to file
    cvvobj = np.asarray([cvv, var, counts])
    cvvobj = np.vstack((taxis, cvvobj))
    cvvobj = cvvobj.transpose()
    np.savetxt("cvv.csv", cvvobj, delimiter=",")

if __name__ == "__main__":
    
    dstart = datetime.datetime.now()
    print("Post-processing launched: {}".format(
            dstart.strftime("%a %b %d %H:%M:%S %Y")))
    
    print("\nCalculating Fsk...")
    tic = datetime.datetime.now()
    CalculateFsk()
    toc = datetime.datetime.now()
    print("Task completed: {}".format(
            toc.strftime("%a %b %d %H:%M:%S %Y")))
    elapsed = int((toc-tic).total_seconds())
    print("Elapsed time: {} sec".format(elapsed))
    
    print("\nCalculating g(r)...")
    tic = datetime.datetime.now()
    CalculateGr()
    toc = datetime.datetime.now()
    print("Task completed: {}".format(
            toc.strftime("%a %b %d %H:%M:%S %Y")))
    elapsed = int((toc-tic).total_seconds())
    print("Elapsed time: {} sec".format(elapsed))
    
    print("\nCalculating MSD...")
    tic = datetime.datetime.now()
    CalculateMSD()
    toc = datetime.datetime.now()
    print("Task completed: {}".format(
            toc.strftime("%a %b %d %H:%M:%S %Y")))
    elapsed = int((toc-tic).total_seconds())
    print("Elapsed time: {} sec".format(elapsed))
    
    print("\nCalculating Cvv...")
    tic = datetime.datetime.now()
    CalculateCvv()
    toc = datetime.datetime.now()
    print("Task completed: {}".format(
            toc.strftime("%a %b %d %H:%M:%S %Y")))
    elapsed = int((toc-tic).total_seconds())
    print("Elapsed time: {} sec".format(elapsed))
    
    dend = datetime.datetime.now()
    print("\nPost-processing finished: {}".format(
            dstart.strftime("%a %b %d %H:%M:%S %Y")))
    elapsed = int((dend-dstart).total_seconds())
    print("Total Elapsed time: {} sec".format(elapsed))
    
#    fs = np.loadtxt("fsk.csv", delimiter=",")
#    gr = np.loadtxt("gr.csv", delimiter=",")
#    msd = np.loadtxt("msd.csv", delimiter=",")
#    cvv = np.loadtxt("cvv.csv", delimiter=",")
#    
#    def display(thing):
#        plt.plot(thing[:,0],thing[:,1])
    