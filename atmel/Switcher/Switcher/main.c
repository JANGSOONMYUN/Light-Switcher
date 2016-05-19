/*
 * Switcher.c
 *
 * Created: 2016-05-19 오전 9:34:18
 * Author : SOONMYUN
 */ 
#define F_CPU 8000000 // 사용하는 CPU 클럭을 설정한다. delay.h를 위해 필요
#include <util/delay.h>
#include <avr/io.h>

void timer_init(){
	DDRB=0x20;   // PB5 out
	TCCR1A=0x82; // FAST PWM
	TCCR1B=0x1A; // 8분주=1usec
	OCR1A=1500;  // 1500usec=0도		//인터럽트 발생위치
	ICR1=19999;  // 1usec*20000=20000usec=50Hz =20ms	//20ms로 인터럽트 발생
}

void control_motor(int angle){
	int i;
	if(angle<-90)angle=-90;
	if(angle> 90)angle= 90;
	i=(angle)*9 + 1500;
	OCR1A=i; //PB5
}

int main(void)
{
	unsigned char sw;
	PORTD = 0xff;
    DDRD = 0xf0;	// 0: input, 1: output, switch KEY1~4 : PD0~PD3
	 
	int i;
	DDRC=0xFF;
	timer_init();
	
    while (1) 
    {
		control_motor(-20); _delay_ms(1000);
		control_motor(  0); _delay_ms(1000);
		control_motor( 20); _delay_ms(1000);
		control_motor(  0); _delay_ms(1000);
	}
	
	
	
	// version 0.1
	
	return 0;
}

