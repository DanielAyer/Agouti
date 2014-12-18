              
#include <Servo.h>  // Include basic Servo library.
#include <Semi_Auto_Bot.h>  // Include SAB library.
          
Semi_Auto_Bot SAB;  // Create instance of class Semi_Auto_Bot.
int servoThrottle[5] = {0,48,96,144,180};  // Left throttle of full reverse, half reverse, full stop, half forward, full forward.
int currDist = 0;  // Variable to hold current distance.
int farDist = 0;  // Variable to hold farthest distance.

void setup()
  { // initialize serial communication:
    Serial.begin(9600);  // Toss variable from header file here to allow for serial com to be set in the header only.  
    SAB.myServoLeft.attach(SAB.left);  // Attach left servo.
    SAB.myServoLeft.write(servoThrottle[2]);  // Stop left wheel.
    
    SAB.myServoRight.attach(SAB.right);  // Attach right servo.
    SAB.myServoRight.write(servoThrottle[2]);  // Stop left wheel.
  }
              
void loop()
{      
  currDist = SAB.distance();  // Get current distance.
  
  while(currDist > SAB.critDist)  //  While farther than critical distance from any object.  This loop will stop when too close to object.
    {
      
Serial.println("Begin code.");
Serial.println("Begin rotation.");

      // Begin rotation.
      SAB.myServoRight.write(servoThrottle[0]);  // Rotate full reverse right wheel.
      SAB.myServoLeft.write(servoThrottle[0]);  // Rotate full reverse left wheel.

Serial.println("Rotation begun.");
Serial.println("Get farthest point.");

      // Get farthest point.
      farDist = SAB.farthest(SAB.rotTime);  // Get farthest distance in a set amount of time.

Serial.print("farDist:  ");
Serial.println(farDist);

Serial.println("Got farthest point.");
Serial.println("Stop rotation.");

      // Stop moving.
      SAB.myServoRight.write(servoThrottle[2]);  // Stop right wheel.
      SAB.myServoLeft.write(servoThrottle[2]);  // Stop left wheel.

Serial.println("Stopped rotation.");
Serial.println("Delay 1 sec.");

      delay(1000);  // Pause for one second.

Serial.println("Delayed one sec.");
Serial.println("Turn to farthest dist.");

      // Turn to farthest measured distance.
      SAB.myServoRight.write(servoThrottle[1]);  // Half full reverse right wheel.
      SAB.myServoLeft.write(servoThrottle[1]);  // Half full reverse left wheel.

Serial.println("Turning to farthest dist.");

      while(currDist < farDist)  // While rotating to find current distance within variance eVar.
        {
          currDist = SAB.distance();  // Measure distance.
        }
        
Serial.println("Turned to farthest dist.");
Serial.println("Stopping.");

SAB.myServoRight.write(servoThrottle[2]);  // Half full reverse right wheel.
SAB.myServoLeft.write(servoThrottle[2]);  // Half full reverse left wheel.
      
Serial.println("Stopped.");

Serial.println("Delay one sec.");

      delay(1000); // Pause for one second.

Serial.println("Delayed one sec.");
Serial.println("Move forward.");

      // Put toThere() code here.
      SAB.myServoRight.write(servoThrottle[3]);  // Half full reverse right wheel.
      SAB.myServoLeft.write(servoThrottle[1]);  // Half full forward left wheel.

Serial.println("Moving forward.");
Serial.println("Hold to allow continuous motion.");
        
    while(currDist > SAB.critDist)  // Hold loop until bot reaches within 5cm of the critical distance.
      {
        Serial.println("currDist:    ");
        Serial.println(currDist);
        
        currDist = SAB.distance();  // Measure current distance.
      }
      
Serial.println("Remeasure distance.");

      currDist = SAB.distance();  // Remeasure distance.

Serial.println("Remeasured distance.  Begin loop again.");      
    }  
    
Serial.println("Too close.  Stop motion.");  

   SAB.myServoRight.write(servoThrottle[2]);  // Stop right wheel.
   SAB.myServoLeft.write(servoThrottle[2]);  // Stop left wheel.

Serial.println("Stopped motion.");
}
                
