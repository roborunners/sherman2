#ifndef MACROS_H
#define MACROS_H

#define J1BUTTON(btn) (joystick.joy1_Buttons & (1 << (btn - 1))) != 0
#define J1TOPHAT(th)  joystick.joy1_TopHat == th

#endif // MACROS_H
