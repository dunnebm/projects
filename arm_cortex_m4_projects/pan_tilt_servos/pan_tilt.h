#ifndef PAN_TILT_H
#define PAN_TILT_H

#define PT_POSITION_0_DEG 0
#define PT_POSITION_45_DEG 250
#define PT_POSITION_90_DEG 500
#define PT_POSITION_135_DEG 750
#define PT_POSITION_180_DEG 1000
#define PT_DEGREES_TO_REG_VAL(deg) (6*deg)

void pt_init();
void pt_movePanServo(int val);
void pt_moveTiltServo(int val);
void pt_setPanServo(int val);
void pt_setTiltServo(int val);

#endif