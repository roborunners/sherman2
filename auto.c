#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S4,     IRSeeker,       sensorHiTechnicIRSeeker1200)
#pragma config(Motor,  mtr_S1_C1_1,     ElevStage1,    tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C1_2,     ElevStage2,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     TreadLeft,     tmotorTetrix, openLoop, reversed, driveLeft)
#pragma config(Motor,  mtr_S1_C2_2,     TreadRight,    tmotorTetrix, openLoop, driveRight)
#pragma config(Servo,  srvo_S1_C3_1,    ScoopGate,     tServoStandard)

#include "constants.h"
#include "macros.h"
#include "config.h"

#include "JoystickDriver.c"

void setup() {
  return;
}

task main(){
  setup();
  startTask(displayDiagnostics);
  waitForStart();

  servo[ScoopGate] = SCOOPGATE_OPEN;
  delay(AUTO_SERVO);
  servo[ScoopGate] = SCOOPGATE_CLOSED;
  delay(AUTO_SERVO);

  motor[ElevStage1] = ELEVSTAGE1_SPEED;
  delay(AUTO_ELEVSTAGE1_INIT);
  motor[ElevStage1] = OFF;

  motor[TreadLeft]  = AUTO_TREAD_SPEED;
  motor[TreadRight] = AUTO_TREAD_SPEED;
  delay(AUTO_TREAD_TIME);
  motor[TreadLeft]  = OFF;
  motor[TreadRight] = OFF;

  motor[ElevStage1] = ELEVSTAGE1_SPEED;
  delay(AUTO_ELEVSTAGE1_SCORE);
  motor[ElevStage1] = OFF;
  motor[ElevStage2] = ELEVSTAGE2_SPEED;
  delay(AUTO_ELEVSTAGE2_SCORE);
  motor[ElevStage2] = OFF;

  servo[ScoopGate] = SCOOPGATE_OPEN;
  delay(AUTO_SERVO);
  motor[TreadRight] = LURCH_SPEED;
  motor[TreadLeft]  = LURCH_SPEED;
  delay(LURCH_TIME);
  motor[TreadRight] = OFF;
  motor[TreadLeft]  = OFF;
  delay(AUTO_SERVO);
  servo[ScoopGate] = SCOOPGATE_CLOSED;

  while (true) {};
}