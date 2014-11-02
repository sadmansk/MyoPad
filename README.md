Myo Pad
=======
####Current Version: 0.0.1
####Developed at EngHack 2014 in University of Waterloo

###What is the Myo Armband?

The Myo armband lets you use the electrical activity in your muscles to wirelessly control your computer, phone, and other favorite digital technologies. With the wave of your hand, it will transform how you interact with your digital world. For more information, check out their website at https://www.thalmic.com/en/myo/.

###What is the Myo Pad?

Myo Pad is a program that can be used to export drawings/writings on a surface wearing the Myo armband to graphical data on a computer.

###The Idea

We initially planned to draw objects on the GUI of the program by using integrals on the accelerometer data from the arm band to get the position vector and using the quaternion values on the position vector to get an accurate position of the fist. The program would then map that position onto the program's GUI and later could be exported onto a PDF file.

###The Problems

Our program was ready to work but then we found out that doing integration twice on the already noisy and inconsistent accelerometer values as well as applying the rotation on the ever changing coordinate system of the arm band. We tried using an independent coordinate system by applying a three dimensional rotation vector on the existing coordinate system but the discrepancies due to the gravity made the values very difficult if not impossible to work with. Hence we had to resolve to using the orientation data from the arm band since they provided a more accurate representation compared to the accelerometer data.

###The Solution

And so we did use the orientation data to position our marker on the GUI. But we also decided that we should add more features to the program using the gestures that the Myo library helps us import. Below is a tutorial that demonstrates how some of the gestures can be used to have the best experience with Myo Pad:


* <strong>Normal Gesture: </strong> Just pretending to hold a pen will return a rest value as the pose and this is used to draw points on the GUI.
* <strong>Fist Gesture: </strong> Can be used to erase already existing points/drawings/writings.
* <strong>Wave In and Out: </strong> The position of the cursor can be controlled by waving the hands in either of the directions. Using the waving in the right way gives a lot of control to the user.
* <strong>Spread Out Gesture: </strong> Spreading out your hands would tell the program that you are not drawing anything on the screen.

###Conclusion

Our completed project is not exactly the innovation we had hoped for when we started working on it. But the entire hackathon and researching was fun nonetheless. It was fun facing problems and finding ways to work around them. The dream we had could have been revolutionary, no one would need to buy expensive graphics tablets, or note taking tablets any more. Teachers would have an easier time sharing their notes with their student, in real time. Yes, in REAL TIME. But we still had a fun to work with end product once you get used to it. It would have been great if we had access to the Myo arm band for longer than just 24 hours. Maybe we would have found a way to apply the Kalman filter on the acceleration vector to get a more accurate position vector out of it. 

Last but not least, this project would not have been possible without all the great team members.

###Contributors

* Sadman Kazi
* Wojtek Swiderski
* Serge Babayan
* Shan Phylim
