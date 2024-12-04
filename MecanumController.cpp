#pragma region VEXcode Generated Robot Configuration
// Make sure all required headers are included.
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>


#include "vex.h"

using namespace vex;

// Brain should be defined by default
brain Brain;


// START V5 MACROS
#define waitUntil(condition)                                                   \
  do {                                                                         \
    wait(5, msec);                                                             \
  } while (!(condition))

#define repeat(iterations)                                                     \
  for (int iterator = 0; iterator < iterations; iterator++)
// END V5 MACROS


// Robot configuration code.
motor Motor11 = motor(PORT11, ratio18_1, false);

controller Controller1 = controller(primary);
motor leftMotorA = motor(PORT9, ratio18_1, false);
motor leftMotorB = motor(PORT10, ratio18_1, false);
motor_group LeftDriveSmart = motor_group(leftMotorA, leftMotorB);
motor rightMotorA = motor(PORT6, ratio18_1, true);
motor rightMotorB = motor(PORT7, ratio18_1, true);
motor_group RightDriveSmart = motor_group(rightMotorA, rightMotorB);
drivetrain Drivetrain = drivetrain(LeftDriveSmart, RightDriveSmart, 319.19, 295, 40, mm, 1);



// generating and setting random seed
void initializeRandomSeed(){
  int systemTime = Brain.Timer.systemHighResolution();
  double batteryCurrent = Brain.Battery.current();
  double batteryVoltage = Brain.Battery.voltage(voltageUnits::mV);

  // Combine these values into a single integer
  int seed = int(batteryVoltage + batteryCurrent * 100) + systemTime;

  // Set the seed
  srand(seed);
}



void vexcodeInit() {

  //Initializing random seed.
  initializeRandomSeed(); 
}


// Helper to make playing sounds from the V5 in VEXcode easier and
// keeps the code cleaner by making it clear what is happening.
void playVexcodeSound(const char *soundName) {
  printf("VEXPlaySound:%s\n", soundName);
  wait(5, msec);
}



// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

#pragma endregion VEXcode Generated Robot Configuration

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       {author}                                                  */
/*    Created:      {date}                                                    */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// Include the V5 Library
#include "vex.h"
  
// Allows for easier use of the VEX Library
using namespace vex;


class Dtrain
{
  private:
    int accelerationValue;
    int maxTorque;
    
    void Drive(int accelerationValueCon, int direction)
    {
        accelerationValue = accelerationValueCon;
        //0 = forward
        //1 = reverse
        //over 1 is invalid so dont let it happen

        leftMotorA.setVelocity(accelerationValue,percent);
        rightMotorA.setVelocity(accelerationValue,percent);

        leftMotorB.setVelocity(accelerationValue,percent);
        rightMotorB.setVelocity(accelerationValue,percent);

        if(direction == 0)
        {
          //forward
        }
        if(direction == 1)
        {
          //backward
        }
        else
        {
          //error
          return;
        }
         
          
        
        
    }

    Dtrain(int maxTorqueCon)
    {
      maxTorque = maxTorqueCon;

      leftMotorA.setMaxTorque(maxTorque,percent);
      rightMotorA.setMaxTorque(maxTorque,percent);
      
      leftMotorB.setMaxTorque(maxTorque,percent);
      rightMotorB.setMaxTorque(maxTorque,percent);
    }
    //Dtrain constructor initializes stuff for the drivetrain
};

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  // Begin project code
  //int accelerationValue;
 
  //  leftMotorA.setMaxTorque(100,percent);
  //  rightMotorA.setMaxTorque(100,percent);

  //  leftMotorB.setMaxTorque(100,percent);
  //  rightMotorB.setMaxTorque(100,percent);

  Dtrain dtrain(50);

  while(true)
  {
    dtrain.accelerationValue = Controller1.Axis3.position();
    // leftMotorA.setVelocity(accelerationValue,percent);
    // rightMotorA.setVelocity(accelerationValue,percent);

    // leftMotorB.setVelocity(accelerationValue,percent);
    // rightMotorB.setVelocity(accelerationValue,percent);
    //assigns axis3 position to int variable and sets that as the motor velocity
  
   if(dtrain.accelerationValue != 0)
  {
    leftMotorA.spin(forward);
    rightMotorA.spin(forward);

    leftMotorB.spin(forward);
    rightMotorB.spin(forward);
  }
  //if the controller axis isnt centered then rotate
  else {
    leftMotorA.stop();
    rightMotorA.stop();

    leftMotorB.stop();
    rightMotorB.stop();
    
  }
 
 
  
   wait(20,msec);
   //small delay 
 }


 



}
