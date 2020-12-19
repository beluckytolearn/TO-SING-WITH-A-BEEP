#ifndef __BEEP_H
#define __BEEP_H

#include "stm32f10x.h"
#include "sys.h"


void beep_init(void);
void beepon(void);
void beepoff(void);
void sound(u16 frq);
void music(void);

#endif
