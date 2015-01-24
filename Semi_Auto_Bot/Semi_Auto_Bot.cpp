/*
  Semi_Auto_Bot.cpp - Library for a semi-autonomous Arduino Uno controlled Hex-Bot.
 Created by Daniel Ian Ayer, 01222015.
 Released into the public domain. 
 */

#include <Arduino.h>  // Include the basic Arduino library.
#include <Semi_Auto_Bot.h>  // Include my own Semi_Auto_Bot library.
	
Semi_Auto_Bot::Semi_Auto_Bot()  // Constructor called when object is initialized.
{		

}


Semi_Auto_Bot::~Semi_Auto_Bot()  // Destructor called when object is cleaned up.
{

}

double Semi_Auto_Bot::farthest(int rTime) // This function measures the farthest distance recorded during the time interval rTime in milliseconds.	
	{	
		double farthestDistance = 0;  // Variable to hold farthest distance.
		double currentDistance = 0;  // Variable to hold current distance.
 
		int t1 = 0;  // Set initial time to zero.
		int t2 = 0;  // Set second time to zero.
		int currentTimeElapsed = 0;	// Variable used to hold elapsed time.
		
		t1 = millis();  // Get first time stamp.
		
      while (currentTimeElapsed < rTime)  // Rotate for rotTime milliseconds.
        {   currentDistance = distance();  // Get current distance.
            
			t2 = millis(); // Refresh second time stamp.
			currentTimeElapsed = t2 - t1;  // Calculate current elapsed time.
			
            if (farthestDistance < currentDistance) 
             {  // Current distance is farther than farthest distance recorded.
                farthestDistance = currentDistance;  // Store new farthest distance.
             } 
        }
		
		return farthestDistance;  // Toss back farthest recorded distance.
	}
	
double Semi_Auto_Bot::distance()  // Call this function to measure the distance to an object using the ping sensor.
{ // According to Arduino Cookbook ISBN:978-1-449-31387-6 the maximum range of this sensor is 3m and the min is 2cm.

  double duration = 0;  // Set duration to zero every time routine runs.

  pinMode(PING_PIN, OUTPUT);  // Sets the ping sensor to output to generate signal.
  digitalWrite(PING_PIN, LOW);  // Sets the voltage of the pin to zero.
  delayMicroseconds(2);  // Ensures completion of previous steps.
  digitalWrite(PING_PIN, HIGH);  // Sets the voltage of the pin to not zero and generates an outgoing pulse. (Depending on the board 3 volts to 5 volts).
  delayMicroseconds(5);  // Ensures a pulse duration of 5 microseconds.
  digitalWrite(PING_PIN, LOW);  //  Sets the voltage of the ping sensor to zero.

  pinMode(PING_PIN, INPUT);  // Sets the ping sensor to input to receive signal.
  duration = pulseIn(PING_PIN, HIGH);  // Waits for the ping sensor to respond to a signal and reports the elapsed time in microseconds.

 duration = duration / 48;  // Convert duration to centimeters.

return duration;	// Return distance in cm.
 } 

int Semi_Auto_Bot::isLinear() // Determine if motion is linear or non-linear.  If non-linear indicates drift. Returns 0 for non-linear motion and 1 for linear motion.
	{ 	/* We assume constant speed.  With constant speed the time variable is allowed to be omitted.  If speed is fluctuating this function is 
inappropriate.
	     Assuming an irregular surroundings, if speed is constant then the acceleration should be zero.  If acceleration is not zero then the bot 
is deviating from a
		 linear trajectory. */
		 
	  distances[0] = distance();  // Get first distance.

      distances[1] = distance();  // Get second distance.

      derivatives[0] = distances[1] - distances[0];  // Get first delta distance.

      distances[0] = distance();  // Get third distance.

      distances[1] = distance();  // Get fourth distance.
 
      derivatives[1] = distances[1] - distances[0];  // Get second delta distance.

      derivatives[2] = derivatives[1] - derivatives[0];  // Get second derivative of distance.

	
	if (derivatives[2] == 0)
		{	// Linear motion.
			return 1;
		}
	else	
		{  // Non-linear motion.
			return 0;
		
		}
	}
	
int Semi_Auto_Bot::zeroThrottle(Servo myServo, int presumedZero)	
/* Find zero rotation.  Takes passed servo plus presumed zero write for throttle.  Use this to modify the throttle settings.
   This function is designed to be used on a rotating bot assuming an irregular surrounding.  
   This can be used on a stationary bot by holding an object in front of the sensor.  Modify the distance of the object to the sensor until the 
wheels 
   stop rotating.  When wheels are stopped hold the object stationary.  The function will return the write command sent to the stopped wheels.
*/
	{   int i = presumedZero; // Incrementing variable for throttle test.
		int upperLimit = 135; // Variable sets upper limit of throttle test.
		double distance1 = 0;  // Set initial distance to zero.
		double distance2 = 0; // Set second distance to zero.
        double dDistance = 0;  // Set delta distance to zero.
		
        while (i <= upperLimit)
            {  //Test from presumed zero of 90 and increment to 135.  135 is presumed half forward.
			    myServo.write(i);  // Write possible zero rotation.

                distance1 = distance();  // Get initial distance.

                delay(500);  // Delay half a second.
                                 
                distance2 = distance();  // Get second distance.
                  
                dDistance = distance2-distance1;  // Calculate delta distance.

                if (dDistance == 0)  // If we think wheels aren't moving.
					{     
						delay(3000);  // Wait three seconds to ensure wheels are actually stopped.
					
						distance1 = distance(); // Measure distance again.
					
						dDistance = distance2-distance1; // Recalculate delta distance.
					
							if (dDistance == 0)  // Wheels are actually stopped.
								{
									return i;  // Toss back the zero for the servo.
								}
					}                     
				else if (i == upperLimit) 
					{   // Increment test has failed.  No zero has been located between writes of 90 to 135.				
						i = presumedZero;  // Reset i to presumed zero.
					}
				i++;  // Increment write variable.	

            }
	}
	
void Semi_Auto_Bot::turnServos(Servo myServoRight, Servo myServoLeft, int sentThrottleSignal)
	{  // Send sentThrottleSignal to both servos.
		myServoRight.write(sentThrottleSignal);  // Rotate right servo.
        myServoLeft.write(sentThrottleSignal);  // Rotate left servo.
	}
	
void Semi_Auto_Bot::turnServos(Servo myServoRight, Servo myServoLeft, int sentThrottleSignalRight, int sentThrottleSignalLeft)
	{  // Send unique throttle signals to each servo.
		myServoRight.write(sentThrottleSignalRight);  // Rotate right servo.
        myServoLeft.write(sentThrottleSignalLeft);  // Rotate left servo.
	}





