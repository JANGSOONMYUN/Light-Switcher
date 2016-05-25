/*
 * Switcher.c
 *
 * Created: 2016-05-19 오전 9:34:18
 * Author : SOONMYUN
 */ 
<<<<<<< HEAD
=======
#define F_CPU 8000000 // 사용하는 CPU 클럭을 설정한다. delay.h를 위해 필요
#include <util/delay.h>
#include <avr/io.h>
#include <avr/signal.h>
#include <avr/interrupt.h>

unsigned int baudrate = 25;	// 8MHz, double baudrate, 38400 bps
unsigned char temp;

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

void usart_init(){
	DDRE = 0xFE; //시리얼통신을 위해 PE0핀은 RXD0로서 입력으로 설정하고, PE1 핀은 TXD0로서 출력으로 설정

	UBRR0H = baudrate>>8; // 보레이트 설정 38400 bps

	UBRR0L = baudrate;

	UCSR0A = 0x02; // 비동기 모드, 더블 보레이트
	// 0000 0010 U2Xn(Double the USARTn Transmission Speed)
	//			클록의 분주비를 16에서 8로 낮추어 전송속도 2배 높이는 기능

	UCSR0B = 0x18; // 0x98 rx interrupt enable, 8 data, tx 0xD8, tx_empty 0xF8

	UCSR0C = 0x06; // no parity, 1 stop, 8 data

	temp = UDR0; // dummy read
}

>>>>>>> parent of cf2c213... no message

#include <avr/io.h>


int main(void)
{
<<<<<<< HEAD
    /* Replace with your application code */
    while (1) 
    {
    }
=======
	unsigned char cha=0;
	
	PORTD = 0x00;
    DDRD = 0xf0;	// 0: input, 1: output, switch KEY1~4 : PD0~PD3
	// PORTD0~2 : buttons(INPUT), PORTD4,5 : LED(OUTPUT) 
	// 0b00110000, 0x30;
	
	timer_init();
	usart_init();
	
	//cli();
	//sei();
	
    while (1) 
    {
		cha=getch();
		if(cha=='a'){
			control_motor(-20); _delay_ms(1000);
		}
		if(cha=='b'){
			control_motor(  0); _delay_ms(1000);
		}
		if(cha=='c'){
			control_motor(  20); _delay_ms(1000);
		}
		//if(cha == 'a')
		//break;
		//tx_string(str); //문자열을 송신하는 프로그램
	}
	
	
	// version 1.0
	
	return 0;
>>>>>>> parent of cf2c213... no message
}

