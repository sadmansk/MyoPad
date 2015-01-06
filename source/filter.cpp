/*
This file is part of Foobar.

    Foobar is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Foobar is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
*/

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
		
	}
	void Filter::onPose(myo::Myo* myo, uint64_t timestamp, myo::Pose pose)
	{
		currentPose = pose;
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
		using std::atan2;
		using std::asin;
		using std::sqrt;
		using std::cos;
		using std::sin;
		using std::max;
		using std::min;

		roll = -1 * atan2(2.0f * (quat.w() * quat.z() + quat.x() * quat.y()),
				1.0f - 2.0f * (quat.y() * quat.y() + quat.z() * quat.z()));
		pitch = -1 * atan2(2.0f * (quat.w() * quat.x() + quat.y() * quat.z()),
				1.0f - 2.0f * (quat.x() * quat.x() + quat.y() * quat.y()));
		yaw = -1 * asin(max(-1.0f, min(1.0f, 2.0f * (quat.w() * quat.y() - quat.z() * quat.x()))));
	}

	void Filter::onAccelerometerData(myo::Myo *myo, uint64_t timestamp, const myo::Vector3< float > &accel){
		accelX_old = accelX;
		accelY_old = accelY;
		accelZ_old = accelZ;

		using std::atan2;
		using std::asin;
		using std::sqrt;
		using std::cos;
		using std::sin;
		using std::max;
		using std::min;

		//shift the coordinate system in order to cancel out gravity in the right axis


		//roll = roll - roll_i;
		//pitch = pitch - pitch_i;
		//yaw = yaw - yaw_i;

		//accelX = -1 * accel.y();
		//accelY = -1 * accel.z();
		//accelZ = accel.x();

		// pitch = alpha
		// yaw = beta
		// roll = gamma

		//accelX *= cos(yaw) * cos(roll) + cos(yaw) * sin(roll) - sin(yaw);
		//accelY *= cos(roll) * sin(pitch) * sin(yaw) - cos(pitch) * sin(roll) + cos(pitch) * cos(roll) + sin(pitch) * sin(yaw) * sin(roll) + cos(yaw) * sin(pitch);
		//accelZ *= cos(pitch) * cos(roll) * sin(yaw) + sin(pitch) * sin(roll) - cos(roll) * sin(pitch) + cos(pitch) * sin(yaw) * sin(roll) + cos(pitch) * cos(yaw);

		if (fabs(accel.x() - accelX_old) > 0.01)
			accelX = accel.x();

		if (fabs(accel.y() - accelY_old) > 0.01)
			accelY = accel.y();

		if (fabs(accel.z() - accelZ_old) > 0.01)
			accelZ = accel.z() - 1;
	}
	
	// We define this function to print the current values that were updated by the on...() functions above.
