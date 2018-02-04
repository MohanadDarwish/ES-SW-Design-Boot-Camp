#ifndef _UTIL_H_
#define _UTIL_H_

#include "Main.h"

#define DELAY_100US     32
#define DELAY_56US      17

void Delay_US(U8 delay);
void Delay_MS(U16 delay);

//void Delay_100us(void);
//void Delay_56us(void);
void itoa(U8 number, U8* ret_num,U8 num_digits);
#endif // _UTIL_H_
