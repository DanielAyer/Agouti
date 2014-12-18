/*
  Semi_Auto_Bot.h - Library for a semi-autonomous Arduino Uno controlled Hex-Bot.
  Created by Daniel Ian Ayer, 012172014.
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
	
	const static int pingPin = 10;  // Pin attached to the ping sensor.
	const static int left = 4;  // Left servo variable to store pin.;
	const static int right = 5; // Right servo variable to store pin.;
	const static int rotTime = 5000;  // Set time in milliseconds to perform continuous rotation.
	const static int critDist =30;	// Stop distance in cm.
	const static int leftZero = 90;  // Zero throttle write setting for left servo.  (Use zeroThrottle function to find this value for any given servo).
	const static int rightZero = 90;  // Zero throttle write setting for right servo. (Use zeroThrottle function to find this value for any given servo).
	
	// Declare ints to be modified later.
	int toThere; // Variable to hold bearing to object.
	int distance();  // Function to calculate distance to object.
    int zeroThrottle(Servo, int); // Function to return the write value to set the servo to zero rotation.
	int isLinear();  // Function to ascertain linear motion.
	int farthest(int);	 // This function measures the farthest distance recorded during the time interval set in rotTime.
	
private:
	
	
};

#endif
