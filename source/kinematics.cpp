//
//  kinematics.cpp
//  interpreter
//
//  Created by Wojtek Swiderski on 2014-11-01.
//  Copyright (c) 2014 myohack. All rights reserved.
//

#include <iostream>
#include <time.h>
#include <stdlib.h>
#include "kinematics.h"

// -------- Start of private functions --------

// Uses trapezoids to measure the area under the float
float Kinematic::integrate(float highBound, float lowBound, int timeInt){
    float area;
    area = (lowBound + (highBound - lowBound) / 2.0) * (float) timeInt / 1000;
    return area;
}

// Calculates the velocity and position using integrate function
// Updates time variables
void Kinematic::doubleIntegrate(void){
    reftime = reftimep;
    reftimep = (int) clock();
    int timeInt = reftimep - reftime;
    for (int i = 0; i < dim; i++){
        velo[i] = velop[i];
        velop[i] = velop[i] + integrate(accelp[i], accel[i], timeInt);
        pos[i] = pos[i] + integrate(velop[i], velo[i], timeInt);
    }
}

// -------- End of private functions --------

// -------- Start of public functions --------

Kinematic::Kinematic(int dimIn, float scaleIn_a, float scaleIn_v, float scaleIn_s){ // dim = 3, float = 0.0
    
    accelp = (float*) malloc(dim * sizeof(float));
    accel = (float*) malloc(dim * sizeof(float));
    velop = (float*) malloc(dim * sizeof(float));
    velo = (float*) malloc(dim * sizeof(float));
    pos = (float*) malloc(dim * sizeof(float));
    
    reftimep = (int)clock();
    
    for (int i = 0; i < dim; i ++) {
        accelp[i] = 0.0;
        accel[i] = accelp[i];
    }
    
    zeroAll();
    
    dim = dimIn;
    scale_a = scaleIn_a;
    scale_v = scaleIn_v;
    scale_s = scaleIn_s;
}

float *Kinematic::getPosition(float *position){
    position = (float*) malloc(dim * sizeof(float));
    for (int i = 0; i < dim; i++){
        position[i] = scale_a * pos[i];
    }
    return position;
}

float *Kinematic::getVelocity(float *velocity){
    velocity = (float*) malloc(dim * sizeof(float));
    for (int i = 0; i < dim; i++){
        velocity[i] = scale_v * velo[i];
    }
    return velocity;
}

float *Kinematic::getAcceleration(float *acceleration){
    acceleration = (float*) malloc(dim * sizeof(float));
    for (int i = 0; i < dim; i++){
        acceleration[i] = scale_s * accel[i];
    }
    return acceleration;
}

void Kinematic::inputAccel(float *accelIn){
    for (int i = 0; i < dim; i++){
        accel[i] = accelp[i];
        accelp[i] = accelIn[i];
    }
    return;
}

void Kinematic::zeroPos(void){
    for (int i = 0; i < dim; i++) {
        pos[i] = 0.0;
    }
    return;
}

void Kinematic::zeroVelo(void){
    for (int i = 0; i < dim; i++) {
        velo[i] = 0.0;
        velop[i] = velo[i];
    }
    return;
}

void Kinematic::zeroAll(void){
    zeroPos();
    zeroVelo();
    return;
}

void Kinematic::zeroTime(void){
    reftimep = (int) clock();
}

float *Kinematic::update(float *accelIn, float *position){
    position = (float*) malloc(dim * sizeof(float));
    inputAccel(accelIn);
    doubleIntegrate();
    for (int i = 0; i < dim; i++) {
        position[i] = pos[i];
    }
    return position;
}

void Kinematic::printAll(void){
    for (int i = 0; i < dim; i++){
        std::cout << "accel: " << i << " = " << accel[i] << std::endl;
        std::cout << "accelp: " << i << " = " << accelp[i] << std::endl;
        std::cout << "velo: " << i << " = " << velo[i] << std::endl;
        std::cout << "velop: " << i << " = " << velop[i] << std::endl;
        std::cout << "pos: " << i << " = " << pos[i] << std::endl;
    }
}

void Kinematic::freeAll(void){
    free(accelp);
    free(accel);
    free(velop);
    free(velo);
    free(pos);
}

// -------- End of public functions --------
