/*
 * main.c
 *
 *  Created on: Mar 20, 2023
 *      Author: Ahmed_Reda
 *
 */

/*
 * main.c
 *
 *  Created on: Mar 20, 2023
 *      Author: Ahmed_Reda
 */

#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
const unsigned char numbers[10]={0x3f ,
											0x06,
											0x5b,
											0x4f,
											0x66 ,
											0x6D,
											0x7D,
											0x07,
											0x7F,
											0x6F};



void run_as_counter(void)
{
	for(char i=0;i<10;i++)
	{


		for(char j=0;j<10;j ++)
			{
				PORTC=~(numbers[i]);
				_delay_ms(150);
				PORTC=(numbers[j]);
				_delay_ms(100);



			}
     }
}

int main(void)
{
   DDRC=0xff;

   while(1){
		run_as_counter();
	}
}


