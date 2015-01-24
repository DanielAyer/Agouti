#include <Servo.h>  // Include basic Servo library.
#include <Semi_Auto_Bot.h>  // Include SAB library.
    
Semi_Auto_Bot SAB;  // Create instance of class Semi_Auto_Bot.
    
int servoThrottle[5] = {0,48,96,144,180};  // Left throttle of full reverse, half reverse, full stop, half forward, full forward.
int stage = 0;  // Counter to denote which stage of the function is running.
     
double currentDistance = SAB.distance();  // Variable to hold current distance.  Measure current distance.
double farthestDistance = 0;  // Variable to hold farthest distance.
       
Servo myServoLeft; // Declare new severo instance.
Servo myServoRight; // Declare new Servo instance.
    
void setup()
  { // initialize serial communication:
      Serial.begin(9600);  // Toss variable from header file here to allow for serial com to be set in the header only.    
        
      myServoLeft.attach(SAB.LEFT_SERVO);  // Attach left servo.
      myServoLeft.write(servoThrottle[2]);  // Stop left wheel.  
          
      myServoRight.attach(SAB.RIGHT_SERVO);  // Attach right servo.
      myServoRight.write(servoThrottle[2]);  // Stop left wheel.
    }
                  
void loop()
    {  
      currentDistance = SAB.distance();  // Variable to hold current distance.  Measure current distance.
      farthestDistance = 0;  // Variable to hold farthest distance.
      stage = 0;  // Counter to denote which stage of the function is running.     
      
      while(currentDistance > SAB.CRITICAL_DISTANCE)  //  While farther than critical distance from any object.  This loop will stop when too close to object.
        {
    
        switch (stage)  // Find farthest distance.
          {
            case 0:
              {
                // Begin rotation.
                SAB.turnServos(myServoRight, myServoLeft, servoThrottle[0]);  // Rotate bot full speed.
    
                // Get farthest point.
                farthestDistance = SAB.farthest(SAB.ROTATION_TIME);  // Get farthest distance in a set amount of time.
    
                // Stop moving.
                SAB.turnServos(myServoRight, myServoLeft, servoThrottle[2]);// Stop bot.
    
                delay(1000);  // Pause for one second.
     
                stage ++;  // Increment function stage counter.
                }
          
           case 1:  // Turn towards farthest distance measured.
              {
               // Turn to farthest measured distance.
               SAB.turnServos(myServoRight, myServoLeft, servoThrottle[0]);  // Rotate bot full speed.
    
               currentDistance = SAB.distance();  // Set current distance.
              
               while(currentDistance < farthestDistance)  // While rotating to find current distance within 1cm.
                {
                  currentDistance = SAB.distance();  // Measure distance.
                }
             
                SAB.turnServos(myServoRight, myServoLeft, servoThrottle[2]);  // Stop bot.
    
                delay(500);  // Delay half a second.
              
                stage ++;  // Increment function stage counter.
              }
            
            case 2:  // Move forward.
                {
               // Put toThere() code here.
                SAB.turnServos(myServoRight, myServoLeft, servoThrottle[3], servoThrottle[1]);  // Half full forward to each servo.
    
            currentDistance = SAB.distance();  // Remeasure distance.      
                }
          }
        }
    
    // While loop ends when bot is too close to object.    
    
       SAB.turnServos(myServoRight, myServoLeft, servoThrottle[2]); // Stop bot.
    }
                    
