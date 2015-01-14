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
  volatile bool disabled = false;
  volatile bool lurched = false;
  volatile int tread_sensitivity = 0;

  setup();
  startTask(displayDiagnostics);
  waitForStart();

  while (true) {
    getJoystickSettings(joystick);

    // Disable Button
    if        (J1BUTTON(BTN_BACK)) {
      disabled = true;
    // Enable Button
    } else if (J1BUTTON(BTN_START)) {
      disabled = false;
    }

    // If we're disabled, don't do anything.
    //if (disabled) continue;

    // Turn Button (Clockwise)
    if        (J1BUTTON(BTN_X)) {
      motor[TreadLeft]  = -TURN_SPEED;
      motor[TreadRight] = TURN_SPEED;
      delay(TURN_TIME);
      motor[TreadLeft]  = OFF;
      motor[TreadRight] = OFF;
    } else if (J1BUTTON(BTN_Y)) {
      motor[TreadLeft]  = TURN_SPEED;
      motor[TreadRight] = -TURN_SPEED;
      delay(TURN_TIME);
      motor[TreadLeft]  = OFF;
      motor[TreadRight] = OFF;
    // Lurch Button
    } else if (J1BUTTON(BTN_B)) {
      if (!lurched) {
        motor[TreadLeft]  = LURCH_SPEED;
        motor[TreadRight] = LURCH_SPEED;
        delay(LURCH_TIME);
        motor[TreadLeft]  = OFF;
        motor[TreadRight] = OFF;
        lurched = true;
      } else {
        lurched = false;
      }
    // Unused Button
    } else if (J1TOPHAT(BTN_A)) {
    // Elevator Stage 1 (Up)
    } else if (J1BUTTON(BTN_LB)) {
      motor[ElevStage1] = ELEVSTAGE1_SPEED;
    // Elevator Stage 1 (Down)
    } else if (J1BUTTON(BTN_LT)) {
      motor[ElevStage1] = -ELEVSTAGE1_SPEED;
    // Elevator Stage 2 (Up)
    } else if (J1BUTTON(BTN_RB)) {
      motor[ElevStage2] = ELEVSTAGE2_SPEED;
    // Elevator Stage 2 (Down)
    } else if (J1BUTTON(BTN_RT)) {
      motor[ElevStage2] = -ELEVSTAGE2_SPEED;
    // Defaults
    } else {
      motor[ElevStage1] = OFF;
      motor[ElevStage2] = OFF;
    }

    // Turbo Button
    if        (J1BUTTON(BTN_LS)) {
      tread_sensitivity = TREAD_SENSITIVITY_TURBO;
    // Precision Button
    } else if (J1BUTTON(BTN_RS)) {
      tread_sensitivity = TREAD_SENSITIVITY_PRECISE;
    } else {
      tread_sensitivity = TREAD_SENSITIVITY_NORMAL;
    }

    // Scoop Gate (Open)
    if        (J1TOPHAT(TH_U)) {
      servo[ScoopGate] = SCOOPGATE_OPEN;
    // Scoop Gate (Closed)
    } else if (J1TOPHAT(TH_B)) {
      servo[ScoopGate] = SCOOPGATE_CLOSED;
    }

    // Left Tread (Drive) Motor
    if (abs(joystick.joy1_y1) > TREAD_DEADZONE) {
      motor[TreadLeft] = joystick.joy1_y1 / tread_sensitivity;
    } else {
      motor[TreadLeft] = OFF;
    }

    // Right Tread (Drive) Motor
    if (abs(joystick.joy1_y2) > TREAD_DEADZONE) {
      motor[TreadRight] = joystick.joy1_y2 / tread_sensitivity;
    } else {
      motor[TreadRight] = OFF;
    }
  }
}