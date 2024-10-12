#include "ppm.h"


// ppm
u8 g_channel;
u16 g_cnt;
u16 g_ch[5] = {1000, 1000, 50, 1000, 1000};

void int0_init(void)
{
    TMOD |= 0x01;
    
    TH0 = 0;
    TL0 = 0;

    TR0 = 1;                                    //启动定时器
    IT0 = 1;
    EX0 = 1;
}

void update_ppm()
{
    TR0=0;
    g_cnt = TH0*256+TL0;
    if(g_cnt > 5000)    g_channel=0;
    else                g_channel++;

    i16 cnt = g_cnt-2080;
    switch(g_channel)
    {
        case 1: g_ch[0] = cnt < 0 ? 0 : cnt;    break;
        case 2: g_ch[1] = cnt < 0 ? 0 : cnt;    break;
        case 3: g_ch[2] = cnt < 0 ? 0 : cnt;    break;
        case 4: g_ch[3] = cnt < 0 ? 0 : cnt;    break;
        case 5: g_ch[4] = cnt < 0 ? 0 : cnt;    break;
        default :                               break;
    }

    TH0=0;
    TL0=0;
    TR0=1;
}

u16* get_ch()
{
    return g_ch;
}
