#include "myo/myo.hpp"

class Filter {
public:
	Filter();
	void onUnpair(myo::Myo* myo, uint64_t timestamp);
	void onAccelerometerData(myo::Myo *myo, uint64_t timestamp, const myo::Vector3< float > &accel);
	bool onArm;
	myo::Arm whichArm;
	float quatX, quatY, quatZ, quatW, accelX, accelY, accelZ;
	myo::Pose currentPose;
};