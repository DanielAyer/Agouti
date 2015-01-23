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
	
	// Declare int constants to never be changed in program.
	
	const static int PING_PIN = 10;  // Pin attached to the ping sensor.
	const static int LEFT_SERVO = 4;  // Left servo variable to store pin.;
	const static int RIGHT_SERVO = 5; // Right servo variable to store pin.;
	const static int ROTATION_TIME = 2500;  // Set time in milliseconds to perform continuous rotation.
	const static int CRITICAL_DISTANCE =30;	// Stop distance in cm.
	const static int LEFT_SERVO_ZERO = 90;  // Zero throttle write setting for left servo.  (Use zeroThrottle function to find this value for any given servo).
	const static int RIGHT_SERVO_ZERO = 90;  // Zero throttle write setting for right servo. (Use zeroThrottle function to find this value for any given servo).
	
	// Declare variables to be modified later.
	double farthest(int);	 // This function measures the farthest distance recorded during the time interval set in rotTime.
	double distance();  // Function to calculate distance to object.
	int toThere; // Variable to hold bearing to object.	
	int zeroThrottle(Servo, int); // Function to return the write value to set the servo to zero rotation.		
	int isLinear();  // Function to ascertain linear motion.
		double derivatives[3]; // Array to hold distance first and second derivatives.  First position is first derivative.  Second position is another first derivative.  Last position is their difference thus the second derivative.  If second derivative is zero then linear motion.
		double distances[2]; // Variable to hold first distance.
	void turnServos(Servo, Servo, int);  // Turn the servos at same speed.
	void turnServos(Servo, Servo, int, int);  // Turn the servos at variable speeds.
	
private:
	
	
};

#endif
