#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <string>
#include <algorithm>

// The only file that needs to be included to use the Myo C++ SDK is myo.hpp.
#include <myo/myo.hpp>

// Filters the raw values passed in by the arm band
class Filter : public myo::DeviceListener {
public:
	Filter()
		: onArm(false), currentPose(), quatX(0), quatY(0), quatZ(0), quatW(0)
	{
	}

	////converts the quaternion value into a 3x3 euler rotation matrix
	//void quatToMatrix(const myo::Quaternion<float>& quat){
	//	double sqw = quat.w*quat.w;
	//	double sqx = quat.x*quat.x;
	//	double sqy = quat.y*quat.y;
	//	double sqz = quat.z*quat.z;
	//	float euler[3][3];

	//	// invs (inverse square length) is only required if quaternion is not already normalised
	//	double invs = 1 / (sqx + sqy + sqz + sqw);
	//	m[0][0] = (sqx - sqy - sqz + sqw)*invs; // since sqw + sqx + sqy + sqz =1/invs*invs
	//	m[1][1] = (-sqx + sqy - sqz + sqw)*invs;
	//	m[2][2] = (-sqx - sqy + sqz + sqw)*invs;

	//	double tmp1 = quat.x*quat.y;
	//	double tmp2 = quat.z*quat.w;
	//	m[1][0] = 2.0 * (tmp1 + tmp2)*invs;
	//	m[0][1] = 2.0 * (tmp1 - tmp2)*invs;

	//	tmp1 = q.x*q.z;
	//	tmp2 = q.y*q.w;
	//	m20 = 2.0 * (tmp1 - tmp2)*invs;
	//	m02 = 2.0 * (tmp1 + tmp2)*invs;
	//	tmp1 = q.y*q.z;
	//	tmp2 = q.x*q.w;
	//	m21 = 2.0 * (tmp1 + tmp2)*invs;
	//	m12 = 2.0 * (tmp1 - tmp2)*invs;
	//}
	// onUnpair() is called whenever the Myo is disconnected from Myo Connect by the user.
	void onUnpair(myo::Myo* myo, uint64_t timestamp)
	{
		onArm = false;
	}

	// onOrientationData() is called whenever the Myo device provides its current orientation, which is represented
	// as a unit quaternion.
	void onOrientationData(myo::Myo* myo, uint64_t timestamp, const myo::Quaternion<float>& quat)
	{
		quatX = quat.x(); //Return the x-component of this quaternion's vector
		quatY = quat.y(); //Return the y -component of this quaternion's vector
		quatZ = quat.z(); //Return the z-component of this quaternion's vector
		quatW = quat.w(); //Return the w-component (scalar) of this quaternion's vector
	}

	// onPose() is called whenever the Myo detects that the person wearing it has changed their pose, for example,
	// making a fist, or not making a fist anymore.
	void onPose(myo::Myo* myo, uint64_t timestamp, myo::Pose pose)
	{
		currentPose = pose;

	}

	void onAccelerometerData(myo::Myo *myo, uint64_t timestamp, const myo::Vector3< float > &accel){

		accelX = accel.x();
		accelY = accel.y();
		accelZ = accel.z();
	}

	// onArmRecognized() is called whenever Myo has recognized a Sync Gesture after someone has put it on their
	// arm. This lets Myo know which arm it's on and which way it's facing.
	void onArmRecognized(myo::Myo* myo, uint64_t timestamp, myo::Arm arm, myo::XDirection xDirection)
	{
		onArm = true;
		whichArm = arm;
	}

	// onArmLost() is called whenever Myo has detected that it was moved from a stable position on a person's arm after
	// it recognized the arm. Typically this happens when someone takes Myo off of their arm, but it can also happen
	// when Myo is moved around on the arm.
	void onArmLost(myo::Myo* myo, uint64_t timestamp)
	{
		onArm = false;
	}

	// There are other virtual functions in DeviceListener that we could override here, like onAccelerometerData().
	// For this example, the functions overridden above are sufficient.



	// We define this function to print the current values that were updated by the on...() functions above.
	void print()
	{
		// Clear the current line
		std::cout << '\r';

		// Print out the orientation. Orientation data is always available, even if no arm is currently recognized.
		std::cout << "QuatX: "<< '[' << quatX << ']' << 
					 "QuatY: "<< '[' << quatY <<']' <<
					 "QuatZ: "<< '[' << quatZ <<']' <<
					 "Quatw: " <<'[' << quatW << ']' << "accelX: " << '[' << accelX << ']' <<
					 "accelY: " << '[' << accelY << ']' <<
					 "accelZ: " << '[' << accelZ << ']';

		if (onArm) {
			// Print out the currently recognized pose and which arm Myo is being worn on.

			// Pose::toString() provides the human-readable name of a pose. We can also output a Pose directly to an
			// output stream (e.g. std::cout << currentPose;). In this case we want to get the pose name's length so
			// that we can fill the rest of the field with spaces below, so we obtain it as a string using toString().
			std::string poseString = currentPose.toString();

			std::cout << '[' << (whichArm == myo::armLeft ? "L" : "R") << ']'
				<< '[' << poseString << std::string(14 - poseString.size(), ' ') << ']';
		}
		else {
			// Print out a placeholder for the arm and pose when Myo doesn't currently know which arm it's on.
			std::cout << "[?]" << '[' << std::string(14, ' ') << ']';
		}

		std::cout << std::flush;
	}

	// These values are set by onArmRecognized() and onArmLost() above.
	bool onArm;
	myo::Arm whichArm;

	// These values are set by onOrientationData() and onPose() above.
	float quatX, quatY, quatZ, quatW, accelX, accelY, accelZ;
	myo::Pose currentPose;
};

