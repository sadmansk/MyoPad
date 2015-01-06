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

#include "myo/myo.hpp"

class Filter : public myo::DeviceListener {
public:
	Filter();
	void onUnpair(myo::Myo* myo, uint64_t timestamp);
	void onAccelerometerData(myo::Myo *myo, uint64_t timestamp, const myo::Vector3< float > &accel);
	bool onArm, check = true;
	void onOrientationData(myo::Myo* myo, uint64_t timestamp, const myo::Quaternion<float>& quat);
	myo::Arm whichArm;
	float quatX, quatY, quatZ, quatW, accelX, accelY, accelZ;
	float accelX_old, accelY_old, accelZ_old;
	float roll, pitch, yaw;
	myo::Pose currentPose;
	void onPose(myo::Myo* myo, uint64_t timestamp, myo::Pose pose);
};