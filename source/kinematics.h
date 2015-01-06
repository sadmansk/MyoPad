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