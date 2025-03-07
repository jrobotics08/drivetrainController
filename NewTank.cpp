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
controller Controller1 = controller(primary);
motor leftMotorA = motor(PORT1, ratio18_1, false);
motor leftMotorB = motor(PORT3, ratio18_1, false);
motor_group LeftDriveSmart = motor_group(leftMotorA, leftMotorB);
motor rightMotorA = motor(PORT2, ratio18_1, true);
motor rightMotorB = motor(PORT4, ratio18_1, true);
motor_group RightDriveSmart = motor_group(rightMotorA, rightMotorB);
drivetrain Drivetrain = drivetrain(LeftDriveSmart, RightDriveSmart, 319.19, 295, 40, mm, 1);

motor IntakeMotor = motor(PORT5, ratio18_1, false);

digital_out Solenoid = digital_out(Brain.ThreeWirePort.H);


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
/*    Author:       8114B                                                 */
/*    Created:     2/16/25                                                    */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// Include the V5 Library
#include "vex.h"
  
// Allows for easier use of the VEX Library
using namespace vex;
int accelerationValueRight;
int accelerationValueLeft;
int intakeValue;
bool pistonActive = false;

void ButtonPressX()
{
Solenoid.set(false);
}
void ButtonPressY()
{
Solenoid.set(true);
}
void ButtonPressA()
{
  intakeValue = 0;
  IntakeMotor.stop();
}
int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  // Begin project code
  leftMotorA.setMaxTorque(100,percent);
  leftMotorB.setMaxTorque(100,percent);
  rightMotorA.setMaxTorque(100,percent);
  rightMotorB.setMaxTorque(100,percent);


  while (true) {
    accelerationValueRight = Controller1.Axis2.position();
    accelerationValueLeft = Controller1.Axis3.position();

    if(accelerationValueRight == 0 && accelerationValueLeft == 0)
    {
      leftMotorA.stop();
      leftMotorB.stop();
      rightMotorA.stop();
      rightMotorB.stop();
    }
    else
    {
      leftMotorA.setVelocity(accelerationValueLeft,percent);
      leftMotorB.setVelocity(accelerationValueLeft,percent);

      rightMotorA.setVelocity(accelerationValueRight,percent);
      rightMotorB.setVelocity(accelerationValueRight,percent);

      leftMotorA.spin(forward);
      leftMotorB.spin(forward);

      rightMotorA.spin(forward);
      rightMotorB.spin(forward);
    }

    if(Controller1.ButtonUp.pressing())
    {
      if(intakeValue <= 95)
      {
        intakeValue = intakeValue + 5;
      }
      IntakeMotor.spin(forward);
    }

    if(Controller1.ButtonDown.pressing())
    {
      if(intakeValue >= -95)
      {
        intakeValue = intakeValue - 5;
      }

      IntakeMotor.spin(forward);
    }

    IntakeMotor.setVelocity(intakeValue,percent);
    

    Controller1.ButtonA.pressed(ButtonPressA);
    Controller1.ButtonX.pressed(ButtonPressX);
    Controller1.ButtonY.pressed(ButtonPressY);
    Brain.Screen.print("8114b");
    Brain.Screen.clear();
    wait(20,msec);
  }

  
}
