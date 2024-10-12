#include "driver/delay.h"
#include "driver/gpio.h" 
#include "driver/pwm.h" 
#include "driver/ppm.h"
#include "core/servo_ctrl.h"

void main()
{
    gpio_init(3, 2, GPIO_PullUp); // GPIO_PullUp
    gpio_init(3, 3, GPIO_OUT_PP); // PWM0
    gpio_init(5, 5, GPIO_OUT_PP); // PWM1
    
    timer1_init();
    int0_init();
    EA = 1;
    
    // 初始化pwm
    set_pwm(0, get_pwm_val(0));
    set_pwm(1, get_pwm_val(1));
    
    while(1) {
        delay_ms(1);
        servo_ctrl_cmd(get_ch());
        set_pwm(0, get_pwm_val(0));
        set_pwm(1, get_pwm_val(1));
    }
}



INTERRUPT(timer_irq, 3)
{
    update_pwm();
}


INTERRUPT(int0_irq, 0)
{
    update_ppm();
}