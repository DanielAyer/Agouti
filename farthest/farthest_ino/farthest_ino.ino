              
#include <Servo.h>  // Include basic Servo library.
#include <Semi_Auto_Bot.h>  // Include SAB library.
          
Semi_Auto_Bot SAB;  // Create instance of class Semi_Auto_Bot.
int servoThrottle[5] = {0,48,96,144,180};  // Left throttle of full reverse, half reverse, full stop, half forward, full forward.
int stage = 0;  // Counter to denote which stage of the function is running.

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
  double currDist = SAB.distance();  // Variable to hold current distance.  Measure current distance.
  double farDist = 0;  // Variable to hold farthest distance.
  
  while(currDist > SAB.critDist)  //  While farther than critical distance from any object.  This loop will stop when too close to object.
    {

    switch (stage)  // Find farthest distance.
      {
        case 0:
          {
Serial.println("Begin code.");
Serial.println("Begin rotation.");
Serial.print("Stage=:  ");
Serial.println(stage);

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
        
        stage ++;  // Increment function stage counter.
            }
      
      case 1:  // Turn towards farthest distance measured.
          {
Serial.print("Stage=:  ");
Serial.println(stage);

          // Turn to farthest measured distance.
          SAB.myServoRight.write(servoThrottle[1]);  // Half full reverse right wheel.
          SAB.myServoLeft.write(servoThrottle[1]);  // Half full reverse left wheel.

Serial.println("Turning to farthest dist.");

          while(currDist < farDist - 1)  // While rotating to find current distance within 1cm.
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
            
            stage ++;  // Increment function stage counter.
          }
        
        case 2:  // Move forward.
            {
Serial.println("Move forward.");
Serial.print("Stage=:  ");
Serial.println(stage);
            // Put toThere() code here.
            SAB.myServoRight.write(servoThrottle[3]);  // Half full reverse right wheel.
            SAB.myServoLeft.write(servoThrottle[1]);  // Half full forward left wheel.

Serial.println("Moving forward.");      
Serial.println("Remeasure distance.");

        currDist = SAB.distance();  // Remeasure distance.      
            }
      }
    }

// While loop ends when bot is too close to object.    
Serial.println("Too close.  Stop motion.");  

   SAB.myServoRight.write(servoThrottle[2]);  // Stop right wheel.
   SAB.myServoLeft.write(servoThrottle[2]);  // Stop left wheel.

Serial.println("Stopped motion.");
Serial.println("Resetting function stage counter.");

stage = 0;  // Restting function stage counter.
}
                
