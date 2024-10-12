#include "servo_ctrl.h"

/*
蓝箭舵机基本参数:
	舵机频率: 20ms
	舵机角度: 0~180(0.5ms~2.5ms)(0~500)
	额定速度: 0.2s/60°
*/
static struct ServoCtrl g_servo_ctrl_left = {
    .amplitude = 125,                
    .frequency = 0,                 
    .pos = 250                      
};

static struct ServoCtrl g_servo_ctrl_right = {
    .amplitude = 125,                
    .frequency = 0,                 
    .pos = 250                      
};

static struct ServoInfo g_servo_left = {
    .pos = 250,
    .vel = 0
};

static struct ServoInfo g_servo_right = {
    .pos = 250,
    .vel = 0
};

static void power_ctrl(i16 val);
static u8 rudder_ctrl(i16 val);
static void pitch_ctrl(i16 val);
static u8 aileron_ctrl(i16 val);
static void throttle_ctrl(i16 val);
static void creat_pwm_ctrl(struct ServoInfo* servo, struct ServoCtrl* ctrl, u8 is_left);
static void servo_pwm_ctrl();
void servo_ctrl_cmd(u16* chs)
{
    pitch_ctrl(chs[1]);
    power_ctrl(chs[2]);
    throttle_ctrl(chs[4]);

    if(aileron_ctrl(chs[3]) && rudder_ctrl(chs[0]))
        g_servo_right.pos = g_servo_left.pos;

    servo_pwm_ctrl();
}

u16 get_pwm_val(u8 id)
{
    if(id == 0) return 500-g_servo_left.pos;
    else return g_servo_right.pos;
}

static void servo_pwm_ctrl()
{ 
    creat_pwm_ctrl(&g_servo_left, &g_servo_ctrl_left, TRUE);
    creat_pwm_ctrl(&g_servo_right, &g_servo_ctrl_right, FALSE); 
}

static void creat_pwm_ctrl(struct ServoInfo* servo, struct ServoCtrl* ctrl, u8 is_left)
{
    u16 max_pos = ctrl->pos + ctrl->amplitude;
    u16 min_pos = ctrl->pos - ctrl->amplitude;

    max_pos = (max_pos > 500) ? 500 : max_pos;
    min_pos = (min_pos < 0) ? 0 : min_pos;

    i16 vel = ctrl->frequency*ctrl->amplitude/100;

    servo->vel = (servo->vel > 0) ? vel : -vel;
    servo->pos += servo->vel;
    
    if(servo->pos >= max_pos) {
        servo->vel = -servo->vel;
        servo->pos = max_pos;
    } else if(servo->pos <= min_pos) {
        servo->vel = -servo->vel;
        servo->pos = min_pos;
    }
}

// ppm范围(80~2000)
static u8 rudder_ctrl(i16 val)              // 舵机偏航控制
{
    i16 freq = (val-1000)/125;
    g_servo_ctrl_left.frequency += freq;
    g_servo_ctrl_right.frequency -= freq;
    return (freq==0);
}

static void pitch_ctrl(i16 val)             // 舵机油门控制
{
    i16 pos = (val-1000)/10;
    g_servo_ctrl_left.pos = pos+250;
    g_servo_ctrl_right.pos = pos+250;
}

static void power_ctrl(i16 val)             // 舵机频率控制
{
    i16 freq = val/60;
    g_servo_ctrl_left.frequency = freq;
    g_servo_ctrl_right.frequency = freq;
}

static u8 aileron_ctrl(i16 val)             // 舵机横滚控制
{
    i16 pos = (val-1000)/20;
    g_servo_ctrl_left.pos += pos;
    g_servo_ctrl_right.pos -= pos;
    return (pos==0);
}

static void throttle_ctrl(i16 val)          // 舵机幅度控制
{
    i16 amplitude = (val-1000)/20+125;
    g_servo_ctrl_left.amplitude = amplitude;
    g_servo_ctrl_right.amplitude = amplitude;
}

