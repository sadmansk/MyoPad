//
//  kinematics.h
//  interpreter
//
//  Created by Wojtek Swiderski on 2014-11-01.
//  Copyright (c) 2014 myohack. All rights reserved.
//

//#ifndef __interpreter__kinematics__
//#define __interpreter__kinematics__

// Kinematic class contains the acceleration, velocity and position data
// Integrates and filters acceleration input to give accurate velocity

class Kinematic {
    
private:
    // Values
    float *accelp, *accel, *velop, *velo, *pos;
    float scale_a, scale_v, scale_s;
    int reftime, reftimep, timeInt;
    int dim;
    
    // Private functions that should be run in a
    float integrate(float highBound, float lowBound, int timeInt); //
    void doubleIntegrate(void); //
    
public:
    Kinematic(int dimIn, float scaleIn_x, float scaleIn_a, float scaleIn_s); //
    
    // Functions to return desired values
    float *getPosition(float *position); //
    float *getVelocity(float *position); //
    float *getAcceleration(float *position); //
    
    // Functions to input values into the object
    void inputAccel(float *accelIn); //
    void changeThreshold(int newThres); //
    
    // Functions used to zero values
    void zeroPos(void); //
    void zeroVelo(void); //
    void zeroAll(void); //
    void zeroTime(void); //
    
    // Function that will return needed information in the data flow
    float *update(float *accelIn);
    
    // Print functions
    void printAll(void);
    
    // Frees memory
    void freeAll(void);
};

//#endif /* defined(__interpreter__kinematics__) */