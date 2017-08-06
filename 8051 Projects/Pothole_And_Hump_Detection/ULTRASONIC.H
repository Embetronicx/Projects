#include<intrins.h>

sfr16 DPTR=0x82;

sbit trig=P3^5;
sbit echo=P3^2;

void ultrasonic_init(void);
void send_pulse(void) ;
unsigned char ultrasonic();

void ultrasonic_init(void)
{
	TMOD|=0x09;
	TH0=TL0=0;
	TR0=1;
}

void send_pulse(void) 
{
TH0=0x00;TL0=0x00; 
 trig=1;
 _nop_();_nop_();_nop_();_nop_();_nop_();
 _nop_();_nop_();_nop_();_nop_();_nop_();
 trig=0;
}

unsigned char ultrasonic()
{
unsigned char get;
send_pulse();
while(!echo);
while(echo);
DPH=TH0;
DPL=TL0;
TH0=TL0=0xff;
if(DPTR<35000)
	get=DPTR/59;
else
	get=0;
return get;
}