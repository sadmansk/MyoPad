#include "myo/myo.hpp"

class Filter : public myo::DeviceListener {
public:
	Filter();
	void onUnpair(myo::Myo* myo, uint64_t timestamp);
	void onAccelerometerData(myo::Myo *myo, uint64_t timestamp, const myo::Vector3< float > &accel, const myo::Quaternion<float>& quat);
	bool onArm;
	void onOrientationData(myo::Myo* myo, uint64_t timestamp, const myo::Quaternion<float>& quat);
	myo::Arm whichArm;
	float quatX, quatY, quatZ, quatW, accelX, accelY, accelZ;
	float accelX_old, accelY_old, accelZ_old;
	myo::Pose currentPose;
};