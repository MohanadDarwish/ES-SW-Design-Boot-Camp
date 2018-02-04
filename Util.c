#include "Util.h"

void Delay_MS(U16 delay)
{
    //calculated the delay time using a timer
    U16 i,j;
    for(i=0;i<delay;i++)//when delay =5000 timer alarms after 5 sec
    {
        for(j=0;j<80;j++);//using the timer this inner loop takes 12.5 us per iteration
    }
}
void itoa(U8 number, U8* ret_num, U8 num_digits)
{
    U8 i = num_digits;
    U8 j=i-1;
    U8 calc = 100 - (U8)number;
    if( (calc > 100) || (calc == 0) )//100--->256
    {
      //hundreds exists
      ret_num[0]=0x31;
      //to remove the hundred
    }
    else
    {
      //no hundreds
      ret_num[0]=0x30;

    }
    while (i > 1)
    {
        j=i-1;
        ret_num[j] = (number % 10) + 0x30;
        number /= 10;
        i--;
    }

    ret_num[num_digits] = '\0';
}



void Delay_US(U8 delay)
{

//6cycles *iterations_num +3cycles +fn CALL 2cycles
//3us*delay+1.5us
    U8 i=0;
	for(i=0;i<delay;i++);
//	mov	r7,#0x05    ;1cycle
//
//00104$:
//	mov	ar6,r7      ;1cycle
//	dec	r6          ;1cycle
//	mov	a,r6        ;1cycle
//	mov	r7,a        ;1cycle
//	jnz	00104$      ;2cycle
//
//	ret             ;2cycle

}
//void Delay_100us(void)
//{
//	U8 i=0;
//	for(i=0;i<33;i++)//this for loop when compiled to assembly it took 6 cycles per iteration =3us
//    {
//		__asm
//		nop//1 instruction cycle 0.5 us
//		__endasm;
//    /*
//;test.c:5: for(i=0;i<33;i++){
//	mov	r7,#0x21
//00104$:
//;	test.c:8: __endasm;
//	nop
//	mov	a,r7
//	dec	a
//;	test.c:5: for(i=0;i<33;i++){
//	mov	r6,a
//	mov	r7,a
//	jnz	00104$
//	ret
//    */
//	}
//}
//void Delay_56us(void)
//{
//   	U8 i=0;
//	for(i=0;i<31;i++){
//		__asm
//		nop//1 instruction cycle 0.5 us
//		nop//1 instruction cycle 0.5 us
//		__endasm;
//	}
//	/* ;	test.c:5: for(i=0;i<31;i++){
//	mov	r7,#0x1F
//00104$:
//;	test.c:9: __endasm;
//	nop
//	nop
//	mov	ar6,r7
//	dec	r6
//;	test.c:5: for(i=0;i<31;i++){
//	mov	a,r6
//	mov	r7,a
//	jnz	00104$
//
//	ret*/
//}



//    //00000000000001 2's comp
//    //11111111111111 overflow/carry =1
//
//    // +127 > 2's comp is the binary representation of the -127
//    // 0111 1111 +127
//    // 1000 0001 -127
//
//    // 0000 0001 +1
//    // 1111 1111 -1
//
//    // 1000 0000 128
//
//    //byte 128 , 0 ,-127
//
//    // 0000 0001             = 1
//    // 1111 1111   -111 1111 = -1
//    // 0111 1111   +111 1111 = 127
//    // 1000 0000   `         = 128
//    // +0(00000000) -0(1000 0000) 127 ----> +0 ,-0 ,------>-127
//    // +0(00000000) 128/-0(1000 0000) 128 ----> 0 ,------>-127(1000 0001)  -127 , -126(1000 0010) , -125(1000 0011)= 1*2^7 - 1*2^1 + 1*2^0 = -125
//    // (0)0 000 0001 = 1
//    //  1 000 0000   = 128 128 - 0+ 0+ 0+ 0+ 0+ 0+ 0
//    // (-128)1 000 0001 = -127 128-1
//}
