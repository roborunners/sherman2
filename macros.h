#ifndef MACROS_H
#define MACROS_H

#define J1BUTTON(btn) (joystick.joy1_Buttons & (1 << (btn - 1))) != 0
#define J2BUTTON(btn) (joystick.joy2_Buttons & (1 << (btn - 1))) != 0
#define J1TOPHAT(th)  joystick.joy1_TopHat == th
#define J2TOPHAT(th)  joystick.joy2_TopHat == th

#endif // MACROS_H
