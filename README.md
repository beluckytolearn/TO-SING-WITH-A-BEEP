# TO-SING-WITH-A-BEEP
## This is my first object.I want to sing a song with a beep.
The following are some experience on learning STM32. 
As we all know, the buzzer is a very common electronic component. We always use it to sound an alarm. Can I use a buzzer to sing a song? 
The buzzer can change the tone of the sound according to the frequency.
The corresponding frequency of specific notes is as follows.

|Number|Tone|Frequency|Number|Tone|Frequency|Number|Tone|Frequency
|-----|-----|-----|-----|-----|-----|-----|-----|-----|
|0|bass 1|262|7|midrange 1|523|14|treble 1|1045|
|1|bass 2|294|8|midrange 2|578|15|treble 2|1175|
|2|bass 3|330|9|midrange 3|659|16|treble 3|1318|
|3|bass 4|349|10|midrange 4|698|17|treble 4|1397|
|4|bass 5|392|11|midrange 5|784|18|treble 5|1568|
|5|bass 6|440|12|midrange 6|880|19|treble 6|1760|
|6|bass 7|494|13|midrange 7|988|20|treble 7|1976|

Then you need to know the beat of a piece of music.
The corresponding numbers of specific beats are as follows.
|Number|Beat|
|-----|-----|
|1|1/4|
|2|1/2|
|3|1|
|4|2|

The songs I chose are some parts of &laquo;animal world&raquo; and &laquo;see you again&raquo;.

`beep.c`
```
#include "stm32f10x.h"
#include "beep.h"
#include "sys.h"
#include "delay.h"
 
void beep_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_8;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	GPIO_ResetBits(GPIOB,GPIO_Pin_8);
	
}
 
void beepon(void)
{
	GPIO_SetBits(GPIOB,GPIO_Pin_8);
}
 
void beepoff(void)
{
	GPIO_ResetBits(GPIOB,GPIO_Pin_8);
}
 
void sound(u16 frq)
{
	u32 n;
	if(frq!=2000)
	{
		n=500000/((u32)frq);
		beepoff();
		delay_us(n);
		beepon();
		delay_us(n);
	}
	else
	{
		beepoff();
		delay_us(1000);
	}
	
}
 
void music(void)
{
	
	//          低1 低2 低3  低4 低5 低6 低7  中1 中2 中3 中4 中5 中6 中7  高1  高2  高3   高4  高5  高6  高7 不放声
	u16 tone[]={262,294,330,349,392,440,494,523,578,659,698,784,880,988,1046,1175,1318,1397,1568,1760,1976,2000};
	//           0   1   2   3   4   5   6   7   8   9   10  11  12  13  14    15   16   17   18   19   20  21	
		
	//歌曲《动物世界》简谱
	u8 playmusic[]={7,6,5,6,7,9,9,6,6,7,6,5,6,7,9,9,5,5,5,4,2,5,4,2,
									5,4,2,5,4,1,2,2,2,21,21,21,3,2,1,2,3,7,7,6,6,
									1,2,2,1,1,6,6,5,5,5,4,2,5,4,2,5,6,7,6,6,5,6,4,4,4,								
									7,6,5,6,7,9,9,6,6,7,6,5,6,7,9,9,5,5,5,4,2,5,4,2,
									5,4,2,5,4,9,10,10,9,9,9,21,21,21,8,8,8,8,8,9,10,9,6,8,7,6,
									7,7,7,5,9,4,12,12,12,5,7,9,12,12,11,12,11,8,9,11,8,7,7,7,5,
									11,12,11,12,11,8,9,9,9,5,7,9,12,12,11,12,11,8,9,11,8,7,7,5,5,5,5,
									9,8,7,6,6,6,6,5,7,9,12,12,11,12,11,8,9,11,8,7,7,7,5,12,12,12,
									14,13,12,11,11,11,11,11,11,21,12,11,9,12,11,9,12,11,11,8,7,6,7,6,4,
									5,11,9,8,8,8,8,9,8,7,5,5,5,5,
									21,21,21
									};
	//1是1/4拍 2是半拍，4是一拍，8是两拍	
	u8 time[]={2,2,2,2,2,2,4,4,4,2,2,2,2,2,2,4,4,4,2,2,2,2,2,2,
						 2,2,2,2,2,2,4,4,4,4,4,4,2,2,2,2,2,2,4,4,4,
						 2,2,2,2,2,2,4,4,4,2,2,2,2,2,2,4,4,4,4,4,2,2,4,4,4,
						 2,2,2,2,2,2,4,4,4,2,2,2,2,2,2,4,4,4,2,2,2,2,2,2,
						 2,2,2,2,2,1,1,2,2,4,4,4,4,4,2,2,2,2,2,2,4,4,4,4,4,4,
						 4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,2,2,4,4,4,
						 4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
						 4,4,2,2,4,4,4,4,4,4,4,4,4,4,4,4,4,4,2,2,4,4,4,4,4,4,
						 4,4,2,2,4,4,4,4,4,4,2,2,2,2,2,2,4,4,4,2,2,2,2,2,2,
						 4,4,2,2,4,4,4,4,4,2,2,4,4,4,						 
						 4,4,4
						};
 
	//歌曲《see you again》简谱
	//u8 playmusic[]={11,15,14,11,11,14,15,16,15,14,15,
	//								11,15,14,11,11,14,15,16,15,14,15,
	//								11,15,14,11,11,14,15,16,15,14,15,
	//								11,15,14,11,11,7,9,11,
	//								12,11,11,21,7,
	//								8,8,7,8,9,21,8,11,
	//								12,13,12,11,9,8,8,7,
	//								8,8,8,7,21,7,9,11,
	//								12,11,11,21,7,
	//								8,8,7,9,21,8,9,11,
	//								12,14,15,16,15,14,11,12,14,
	//								16,16,16,15,21,11,12,14,
	//								16,16,16,15,21,21,
	//								21,21,21
	//								};
	//1是1/4拍 2是半拍，4是一拍，8是两拍	
	//u8 time[]={2,2,2,2,2,1,1,1,1,1,1,
	//					 2,2,2,2,2,1,1,1,1,1,1,
	//					 2,2,2,2,2,1,1,1,1,1,1,
	//					 2,2,2,2,2,2,2,2,
	//					 4,2,2,4,4,
	//					 2,2,2,2,4,2,1,1,
	//					 2,2,2,2,2,2,2,2,
	//					 2,2,2,2,4,1,1,1,1,
	//					 8,2,2,2,2,
	//					 2,2,2,2,4,1,1,2,
	//					 2,2,2,2,2,2,1,1,2,
	//					 2,2,2,2,4,1,1,2,
	//					 2,2,2,2,4,4,
	//					 4,4,4
	//					 };
		
	u32 delaytime;
	u16 i,e;
		
	delaytime=10;
		
		for(i=0;i<(sizeof(playmusic)/sizeof(playmusic[0]));i++)
	{
		for(e=0;e<((u16)time[i])*tone[playmusic[i]]/delaytime;e++)
		{
			sound((u32)tone[playmusic[i]]);
		}		
	}
}
```
`beep.h`
```
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
```
`main.c`
```
#include "stm32f10x.h"
#include "beep.h"
#include "delay.h"
int main()
{
	delay_init(72);
	beep_init();	
	while(1)
	{
		music();
		delay_ms(1000);
	}
}
```
Finally, the MCU will be able to burn the program and We can hear the buzzer sing.  


##
