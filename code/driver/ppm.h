#ifndef __PPM_H__
#define __PPM_H__

#include "firmware/config.h"

void int0_init(void);
u16* get_ch();
void update_ppm();

#endif // !__PPM_H__