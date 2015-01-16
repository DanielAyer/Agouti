/*
  Semi_Auto_Bot.h - Library for a semi-autonomous Arduino Uno controlled Hex-Bot.
  Created by Daniel Ian Ayer, 01122015.
  Released into the public domain. 
*/
#ifndef Semi_Auto_Bot_h
#define Semi_Auto_Bot_h

#include <Servo.h>  // Include the supplied Servo library.

class Semi_Auto_Bot
{
  public:
  
	// Declare items.
    Semi_Auto_Bot();  // Constructor of class Semi_Auto_Bot.
	~Semi_Auto_Bot();  // Destructor of class Semi_Auto_Bot.
	Servo myServoLeft;  // Allocating memory for Left servo.
	Servo myServoRight; // Allocating memory for Right servo.
	
	// Declare int constants to never be changed in program.
	
	const static int PING_PIN = 10;  // Pin attached to the ping sensor.
	const static int LEFT = 4;  // Left servo variable to store pin.;
	const static int RIGHT = 5; // Right servo variable to store pin.;
	const static int ROTATION_TIME = 5000;  // Set time in milliseconds to perform continuous rotation.
	const static int CRITICAL_DISTANCE =30;	// Stop distance in cm.
	const static int LEFT_SERVO_ZERO = 90;  // Zero throttle write setting for left servo.  (Use zeroThrottle function to find this value for any given servo).
	const static int RIGHT_SERVO_ZERO = 90;  // Zero throttle write setting for right servo. (Use zeroThrottle function to find this value for any given servo).
	
	// Declare ints to be modified later.
	int toThere; // Variable to hold bearing to object.
	double distance();  // Function to calculate distance to object.
		double duration; // Variable to hold distance measured in distance() routine.
	
	int zeroThrottle(Servo, int); // Function to return the write value to set the servo to zero rotation.
		double d1;  // Variable to hold first distance in zeroThrottle() routine.
		double d2;  // Variable to hold second distance in zeroThrottle() routine.
		double dDistance; // Variable to store delta distance calculation.
		
	int uLim; // Variable sets upper limit of throttle test.
	int isLinear();  // Function to ascertain linear motion.
		double derivatives[3]; // Array to hold distance first and second derivatives.  First position is first derivative.  Second position is another first derivative.  Last position is their difference thus the second derivative.  If second derivative is zero then linear motion.
		double distances[2]; // Variable to hold first distance.
	
	double farthest(int);	 // This function measures the farthest distance recorded during the time interval set in rotTime.
		double farthestDist;  // Variable to hold the farthest distance measured in farthest() routine.
		double currentDist;  // Variable to hold the current distance measured in farthest() routine.
		int t1;  // Variable to hold first time stamp for elapsed time comparison in farthest() routine. 
		int t2;  // Variable to hold second time stamp for elapsed time comparison in farthest() routine.
		int rTime;  // Variable to hold rotational time fed to farthest() routine.
	
	int i;  // Incremental counter integer.
	

private:
	
	
};

#endif
