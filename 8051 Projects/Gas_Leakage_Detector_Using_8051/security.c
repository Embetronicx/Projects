#include<reg52.h>
#include"LCD.h"			   //rs=p3.7, en=p3.6
#include"GSM.h"

#define NUM "1234567890"    //Enter Your Mobile Number

sbit rd=P0^7;
sbit wr=P0^6;
sbit intr=P0^5;

sbit RELAY=P0^0;
sbit buzz=P0^1;


unsigned char h,g,temp,mydata,msgq;
unsigned int s,r;
void adc();

unsigned char adc_data=0;

void main()
{

	init_serial();
	LCD_initialise();
	RELAY=1;				 //relay on
	buzz=0;					 //buzz on
	comwrt(0x80);
	display("LOADING.");
	for(h=0;h<8;h++) {
		datawrt('.');
		for(s=0;s<30000;s++);
	}
	P2=0xFF;
	comwrt(0x80);
	display("GAS:000PPM R:OFF");
	buzz=0;
	for(r=0;r<=10000;r++);

	while(1) {
		adc();
		for(r=0;r<=20000;r++);			
	}
}


void adc()
{
wr=0;
rd=1;
wr=1;
while(intr==1);
rd=0;
adc_data = P2 ;

msgq = adc_data;

	comwrt(0x84);
	datawrt((msgq/100)+0x30);
	datawrt(((msgq/10)%10)+0x30);
	datawrt((msgq%10)+0x30);
	
	if(msgq > 80) {
		RELAY=0;			   //relay off
		buzz=0;				   //buzz on
		comwrt(0x8D);
		display("OFF");
		
				comwrt(0xC0);
				display("G:HIGH   V:CLOSE");
				for(s=0;s<60000;s++);
				comwrt(0xC0);
				display("SENDING MSG.....");
				
				sendSMS(NUM,"VOLVE CLOSED AND POWER DISCONNECTED DUE TO GAS LEAKAGE!");
				for(s=0;s<30000;s++);
				comwrt(0x80);
				display("GAS:");
				comwrt(0x8b);
				display("R:");
	} else {
		comwrt(0xC0);
		display("G:NORMAL V:OPEN ");
		RELAY=1;		 //relay on
		buzz=1;			 //buzz off
		comwrt(0x8D);
		display("ON ");	
	}
}
