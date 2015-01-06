/*
Copyright (C) 2014 Sadman Kazi, Wojciech Swiderski, Serge Babayan, Shan Phylim

This file is part of MyoPad.

    MyoPad is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    MyoPad is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with MyoPad.  If not, see <http://www.gnu.org/licenses/>.
*/

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
	
	dim = dimIn;
	scale_a = scaleIn_a;
	scale_v = scaleIn_v;
	scale_s = scaleIn_s;
    
	accelp = (float*) malloc(dim * sizeof(float));
    accel = (float*) malloc(dim * sizeof(float));
    velop = (float*) malloc(dim * sizeof(float));
    velo = (float*) malloc(dim * sizeof(float));
    pos = (float*) malloc(dim * sizeof(float));
    
    reftimep = (int)clock();
    
    for (int i = 0; i < dim; i ++) {
        accelp[i] = 0.0f;
        accel[i] = accelp[i];
    }
    
    zeroAll();
    
    
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

float *Kinematic::update(float *accelIn){
	float *position = (float*)malloc(dim * sizeof(float));
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
