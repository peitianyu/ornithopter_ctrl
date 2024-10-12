#ifndef __SERVO_CTRL_H__
#define __SERVO_CTRL_H__

#include "firmware/config.h"

struct ServoCtrl
{
    u16 pos;        // 中心位置
    u16 frequency;  // 频率
    u16 amplitude;  // 振幅
};

struct ServoInfo 
{
    u16 pos;
    i16 vel;
};

enum ServoCmd
{
    POWER_CMD,      // 扇动频率(油门)
    RUDDER_CMD,     // 改变两边的拍打频率(方向舵)
    PITCH_CMD,      // 改变拍打中心位置(俯仰)
    AILERON_CMD,    // 改变两边拍打中心位置(横滚)
    THROTTLE_CMD    // 扇动幅度(油门, 这部分应该设置为几个选择)
};

void servo_ctrl_cmd(u16* chs);

u16 get_pwm_val(u8 id);

#endif