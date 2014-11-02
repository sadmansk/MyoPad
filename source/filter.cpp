#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <string>
#include <algorithm>
#include "filter.h"
// The only file that needs to be included to use the Myo C++ SDK is myo.hpp.
#include <myo/myo.hpp>

	Filter::Filter()
		: onArm(false), currentPose(), quatX(0), quatY(0), quatZ(0), quatW(0)
	{
		accelX = 0.0;
		accelY = 0.0;
		accelZ = 0.0;
	}

	// onUnpair() is called whenever the Myo is disconnected from Myo Connect by the user.
	void Filter::onUnpair(myo::Myo* myo, uint64_t timestamp)
	{
		onArm = false;
	}

	// onOrientationData() is called whenever the Myo device provides its current orientation, which is represented
	// as a unit quaternion.
	void Filter::onOrientationData(myo::Myo* myo, uint64_t timestamp, const myo::Quaternion<float>& quat)
	{
		quatX = quat.x(); //Return the x-component of this quaternion's vector
		quatY = quat.y(); //Return the y -component of this quaternion's vector
		quatZ = quat.z(); //Return the z-component of this quaternion's vector
		quatW = quat.w(); //Return the w-component (scalar) of this quaternion's vector
	}

	void Filter::onAccelerometerData(myo::Myo *myo, uint64_t timestamp, const myo::Vector3< float > &accel){
		accelX_old = accelX;
		accelY_old = accelY;
		accelZ_old = accelZ;

		if (abs(accel.x() - accelX_old) > 0.01)
			accelX = accel.y();

		if (abs(accel.y() - accelY_old) > 0.01)
			accelY = accel.z() - 1;

		if (abs(accel.z() - accelZ_old) > 0.01)
			accelZ = accel.x();
	}
	
	// We define this function to print the current values that were updated by the on...() functions above.