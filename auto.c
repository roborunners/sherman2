#pragma config(Hubs,   S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Sensor, S4,     IRSeeker,       sensorHiTechnicIRSeeker1200)
#pragma config(Motor,  mtr_S1_C1_1,     ElevStage1,    tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C1_2,     ElevStage2,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     TreadLeft,     tmotorTetrix, openLoop, reversed, driveLeft)
#pragma config(Motor,  mtr_S1_C2_2,     TreadRight,    tmotorTetrix, openLoop, driveRight)
#pragma config(Servo,  srvo_S1_C3_1,    ScoopGate,            tServoStandard)
#pragma config(Servo,  srvo_S1_C3_2,    TrailerHookLeft,      tServoStandard)
#pragma config(Servo,  srvo_S1_C3_3,    TrailerHookRight,     tServoStandard)
#pragma config(Servo,  srvo_S1_C3_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "constants.h"
#include "macros.h"
#include "config.h"

#include "JoystickDriver.c"

/* Initialize Robot */
void setup() {
  servo[ScoopGate]        = SCOOPGATE_CLOSED;
  servo[TrailerHookLeft]  = TRAILERHOOKLEFT_UP;
  servo[TrailerHookRight] = TRAILERHOOKRIGHT_UP;
}

/* Auto Program */
task main(){
  setup();
  startTask(displayDiagnostics);
  waitForStart();

  // Wave servo
  servo[ScoopGate]  = SCOOPGATE_OPEN;
  delay(AUTO_SERVO);
  servo[ScoopGate]  = SCOOPGATE_CLOSED;
  delay(AUTO_SERVO);

  // Lift elevator (to go down ramp)
  motor[ElevStage1] = ELEVSTAGE1_SPEED;
  delay(AUTO_ELEVSTAGE1_INIT);
  motor[ElevStage1] = OFF;

  // Drive forward to tube
  motor[TreadLeft]  = AUTO_TREAD_SPEED;
  motor[TreadRight] = AUTO_TREAD_SPEED;
  delay(AUTO_TREAD_TIME);
  motor[TreadLeft]  = OFF;
  motor[TreadRight] = OFF;

  // Raise elevator (stage 1)
  motor[ElevStage1] = ELEVSTAGE1_SPEED;
  delay(AUTO_ELEVSTAGE1_SCORE);
  motor[ElevStage1] = OFF;
  // Raise elevator (stage 2)
  motor[ElevStage2] = ELEVSTAGE2_SPEED;
  delay(AUTO_ELEVSTAGE2_SCORE);
  motor[ElevStage2] = OFF;

  // Open scoop
  servo[ScoopGate]  = SCOOPGATE_OPEN;
  delay(AUTO_SERVO);
  // Lurch forward
  motor[TreadRight] = LURCH_SPEED;
  motor[TreadLeft]  = LURCH_SPEED;
  delay(LURCH_TIME);
  motor[TreadRight] = OFF;
  motor[TreadLeft]  = OFF;
  delay(AUTO_SERVO);
  // Close scoop
  servo[ScoopGate]  = SCOOPGATE_CLOSED;

  // Stay running
  while (true) {};
}
