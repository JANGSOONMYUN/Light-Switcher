/*
 * Switcher.c
 *
 * Created: 2016-05-19 오전 9:34:18
 * Author : SOONMYUN
 */ 
<<<<<<< HEAD
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

=======
#define F_CPU 8000000 // 사용하는 CPU 클럭을 설정한다. delay.h를 위해 필요
#include <util/delay.h>
>>>>>>> hardware
#include <avr/io.h>
#include <avr/signal.h>
#include <avr/interrupt.h>
#include <stdlib.h>

unsigned int baudrate = 25;	// 8MHz, double baudrate, 38400 bps
unsigned char temp;
int sw = 1;	// 1: on 0: off

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


void tx_char(unsigned char tx_data)
{
	//시리얼포트로 데이터 송신이 완료되고 송신버퍼가 준비되었는지 검사

	while((UCSR0A&0x20) == 0x00);

	UDR0 = tx_data; //시리얼 포트를 통하여 데이터 전송
}

void tx_string(unsigned char *str_data)
{
	while(*str_data != 0x00){ //문자열의 끝부분이 아니라면

		tx_char(*str_data); //시리얼포트로 한개의 문자를 송신한다.
		str_data++;
	}
}

char getswitch(){
	if((PINC & 0x02) == 0x00){	// 0000 0101 & 0000 0010 = 0x00
		if(sw == 1){
			sw = 0;
			return 'n';
		}
		else if(sw == 0){
			sw = 1;
			return 'f';
		}
	}
	return '1';
}

char getch(void)
{
	while(!(UCSR0A& 0X80)){
		return getswitch();
	}
	return UDR0;
}

void putch(char data)
{
	while(!(UCSR0A & 0x20));
	UDR0 = data;
}

int main(void)
{
<<<<<<< HEAD
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
=======
	unsigned char * cha = (char*)malloc(sizeof(char) * 5);
	int angle = 0;
	
	
	//PORTC = 0x0f;
    DDRC = 0xf0;	// 0: input, 1: output, switch KEY1~4 : PD0~PD3
	// PORTD0~2 : buttons(INPUT), PORTD4,5 : LED(OUTPUT) 
	// 0b00110000, 0x30;
	
	timer_init();
	usart_init();
	
	//cli();
	//sei();
	
    while (1) 
    {
		cha=getch();
		/*
		angle = atoi(cha);
		if((angle >= -100) && (angle <= 100))
			control_motor(angle);
		*/
		
		if(cha=='q'){
			control_motor(-40); _delay_ms(300);
		}
		if(cha=='w'){
			control_motor(-30); _delay_ms(300);
		}
		if(cha=='e'){
			control_motor(-20); _delay_ms(300);
		}
		if(cha=='r'){
			control_motor(-10); _delay_ms(300);
		}
		if(cha=='t'){
			control_motor(0); _delay_ms(300);
		}
		if(cha=='y'){
			control_motor(10); _delay_ms(300);
		}
		
		if(cha=='n'){
			PORTC = (PORTC & 0x0f) | 0x10;
			control_motor(-30); _delay_ms(300);
			
		}
		if(cha=='f'){
			PORTC = (PORTC & 0x0f) | 0x20;
			control_motor(10); _delay_ms(300);
		}
		
		
		
>>>>>>> hardware
		//if(cha == 'a')
		//break;
		//tx_string(str); //문자열을 송신하는 프로그램
	}
	
	
<<<<<<< HEAD
	// version 1.0
	
	return 0;
>>>>>>> parent of cf2c213... no message
=======
	// version 1.1
	
	return 0;
>>>>>>> hardware
}

