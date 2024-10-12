#include "pwm.h"

// pwm
#define PWM0 P33
#define PWM1 P55

static i16 g_timer_cnt = 0;
static u16 g_pwm0_busy = 0;
static u16 g_pwm1_busy = 0;

void update_pwm()
{
    if(g_timer_cnt++ == 5e3-125) {
        g_timer_cnt = -125;
        gpio_set(PWM0, Pin_High);
        gpio_set(PWM1, Pin_High);
    }

    if(g_timer_cnt == g_pwm0_busy)    gpio_set(PWM0, Pin_Low);
    if(g_timer_cnt == g_pwm1_busy)    gpio_set(PWM1, Pin_Low);
}

void set_pwm(u8 id, u16 val) // val为pwm高电平时间*4us, 周期为20ms
{
    if(id == 0)         g_pwm0_busy = val;
    else if(id == 1)    g_pwm1_busy = val;
}

void timer1_init(void)		//4微秒@24.000MHz
{
	AUXR |= 0x40;			//定时器时钟1T模式
	TMOD &= 0x0F;			//设置定时器模式
	TL1 = 0xA0;				//设置定时初始值
	TH1 = 0xFF;				//设置定时初始值
	TF1 = 0;				//清除TF1标志
	TR1 = 1;				//定时器1开始计时
	ET1 = 1;				//使能定时器1中断
}