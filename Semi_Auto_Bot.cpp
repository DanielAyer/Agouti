/*
  Semi_Auto_Bot.cpp - Library for a semi-autonomous Arduino Uno controlled Hex-Bot.
 Created by Daniel Ian Ayer, 012172014.
 Released into the public domain. 
 */

#include <Arduino.h>  // Include the basic Arduino library.
#include <Semi_Auto_Bot.h>  // Include my own Semi_Auto_Bot library.
	
Semi_Auto_Bot::Semi_Auto_Bot()  // Constructor called when object is initialized.
{		
	Servo myServoLeft;  //  Declare left Servo.
	Servo myServoRight; // Declare right Servo.
}


Semi_Auto_Bot::~Semi_Auto_Bot()  // Destructor called when object is cleaned up.
{

}

int Semi_Auto_Bot::farthest(int rTime) // This function measures the farthest distance recorded during the time interval rTime in milliseconds.	
	{	
		int farthestDist = 0;  // Variable to hold farthest distance.
		int currentDist = 0;  // Variable to hold current distance.
 
		int t1 = millis();  // Get first time stamp.
		int t2 = millis();  // Get second time stamp.
		
      while (t2 - t1 < rTime)  // Rotate for rotTime milliseconds.
        {   currentDist = distance();  // Get current distance.
            
            if (farthestDist < currentDist) 
             {  // Current distance is farther than farthest distance recorded.
                farthestDist = currentDist;  // Store new farthest distance.
             } 
				
			t2 = millis(); // Refresh second time stamp.
        }
		
		return farthestDist;  // Toss back farthest recorded distance.
	
	}
	
int Semi_Auto_Bot::distance()  // Call this function to measure the distance to an object using the ping sensor.
{ // According to Arduino Cookbook ISBN:978-1-449-31387-6 the maximum range of this sensor is 3m and the min is 2cm.

  long duration;  // Declare the duration variable.

  pinMode(pingPin, OUTPUT);  // Sets the ping sensor to output to generate signal.
  digitalWrite(pingPin, LOW);  // Sets the voltage of the pin to zero.
  delayMicroseconds(2);  // Ensures completion of previous steps.
  digitalWrite(pingPin, HIGH);  // Sets the voltage of the pin to not zero and generates an outgoing pulse. (Depending on the board 3 volts to 5 volts).
  delayMicroseconds(5);  // Ensures a pulse duration of 5 microseconds.
  digitalWrite(pingPin, LOW);  //  Sets the voltage of the ping sensor to zero.

  pinMode(pingPin, INPUT);  // Sets the ping sensor to input to receive signal.
  duration = pulseIn(pingPin, HIGH);  // Waits for the ping sensor to respond to a signal and reports the elapsed time in microseconds.
 
return duration / 48;  // Return distance in cm.
 } 

int Semi_Auto_Bot::isLinear() // Determine if motion is linear or non-linear.  If non-linear indicates drift. Returns 0 for non-linear motion and 1 for linear motion.
	{ Serial.println("This is monitoring code from Semi_Auto_Bot::isLinear() in Semi_Auto_Bot.cpp.");
	Serial.println("The purpose of this code is to ascertain if bot is moving linearly or not.  A second derivative of zero for distance would indicate a constant rate of change of distance and therefore linear motion assuming an irregular surrounding.");
	int isLinear[3];  // Array to hold distance first and second derivatives.  First position is first derivative.  Second position is another first derivative.  Last position is their difference thus the second derivative.  If second derivative is zero then linear motion.
	int distances[2];  // Variable to hold first distance.
	int i = 0;  // Variable to hold array index.


      distances[i] = distance();  // Get first distance.
      delay(500);  // Delay half a second.
Serial.print("d1:  ");
Serial.println(distances[i]);
      distances[i+1] = distance();  // Get second distance.
      delay(500);  // Delay half a second.
Serial.print("d2:  ");
Serial.println(distances[i+1]);  
      isLinear[0] = distances[i+1] - distances[i];  // Get first delta distance.
Serial.print("isLinear[0]:  ");
Serial.println(isLinear[0]);  
      distances[i] = distance();  // Get third distance.
      delay(500);  // Delay half a second.
Serial.print("d3:  ");
Serial.println(distances[i]);
      distances[i+1] = distance();  // Get fourth distance.
      delay(500);  // Delay half a second.
Serial.print("d4:  ");
Serial.println(distances[i+1]);  
      isLinear[1] = distances[i+1] - distances[i];  // Get second delta distance.
Serial.print("isLinear[1]:  ");
Serial.println(isLinear[1]);  
      isLinear[2] = isLinear[1] - isLinear[0];  // Get second derivative of distance.
Serial.print("isLinear[2]:  ");
Serial.println(isLinear[2]);
	
	if (isLinear[2] == 0)
		{	// Linear motion.
			return 1;
		}
	else	
		{  // Non-linear motion.
			return 0;
		
		}
	}
	
int Semi_Auto_Bot::zeroThrottle(Servo myServo, int pZero)	
/* Find zero rotation.  Takes passed servo plus presumed zero write for throttle.  Use this to modify the throttle settings.
   This function is designed to be used on a rotating bot assuming an irregular surrounding.  
   This can be used on a stationary bot by holding an object in front of the sensor.  Modify the distance of the object to the sensor until the wheels 
   stop rotating.  When wheels are stopped hold the object stationary.  The function will return the write command sent to the stopped wheels.
*/
	{   int d1 = 0;  // First distance variable.
		int d2 = 0;  // Second instance variable.
        int dDistance = 0;  // Delta distance array.  First position is recent test.  Second position is increment test.  Third position is decrement test.
        int uLim = 100; // Variable sets upper limit of throttle test.
        int i = pZero; // Incrementing variable for throttle test.
             
        while (i <= uLim)
            {  //Test from presumed zero of 90 and increment to 135.  135 is presumed half forward.
			    myServo.write(i);  // Write possible zero rotation.

                d1 = distance();  // Get initial distance.

                delay(500);  // Delay half a second.
                                 
                d2 = distance();  // Get second distance.
                  
                dDistance = d2-d1;  // Calculate delta distance.

                if (dDistance == 0)  // If we think wheels aren't moving.
					{     
						delay(3000);  // Wait three seconds to ensure wheels are actually stopped.
					
						d1 = distance(); // Measure distance again.
					
						dDistance = d2-d1; // Recalculate delta distance.
					
							if (dDistance == 0)  // Wheels are actually stopped.
								{
									return i;  // Toss back the zero for the servo.
								}
					}                     
				else if (i == uLim) 
					{   // Increment test has failed.  No zero has been located between writes of 90 to 135.				
						i = pZero;  // Reset i to presumed zero.
					}
				i++;  // Increment write variable.	

            }
    } 





