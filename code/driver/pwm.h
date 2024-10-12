#ifndef __PWM_H__
#define __PWM_H__

#include "firmware/config.h"
#include "driver/gpio.h" 

void set_pwm(u8 id, u16 val);
void timer1_init(void);
void update_pwm();

#endif // !__PWM_H__