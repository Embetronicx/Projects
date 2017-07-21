#include<reg51.h>
#include"GSM.h"
#include"LCD.h"

#define NUMBER1 "9876543210"   //Enter the mobile number
#define NUMBER2 "0123456789"
#define NUMBER3 "1111111111"

sbit vib = P3^2;
sbit buzzer = P0^0;

void main()
{
	unsigned int r;
	init_serial();
	LCD_initialise();
	comwrt(0x80);
	display("INITIALISING....");
	for(r=0;r<60000;r++);
	comwrt(0x80);
	display("GSM ACCIDENT DET");
	comwrt(0xC0);
	display(" VIBRATION: NO  ");
	buzzer=1;
	while(1) {
		if(vib==1) {
			buzzer=0;
			comwrt(0x80);
			display("VIBRATION DETECT");
			comwrt(0xC0);
			display(" VIBRATION: YES ");
			for(r=0;r<30000;r++);
			for(r=0;r<30000;r++);
			comwrt(0x80);
			display("SENDING MSG.....");
			sendSMS(NUMBER1,"ACCIDENT DETECTED NEAR DSPC MADAGADIPET PY-01-0229");
			sendSMS(NUMBER2,"ACCIDENT DETECTED NEAR DSPC MADAGADIPET PY-01-0229");
			sendSMS(NUMBER3,"ACCIDENT DETECTED NEAR DSPC MADAGADIPET PY-01-0229");
			comwrt(0xC0);
			display("    MSG SENT    ");
			for(r=0;r<30000;r++);
			for(r=0;r<30000;r++);
			for(r=0;r<30000;r++);
			comwrt(0x80);
			display("CALLING.........");
			call(NUMBER1);
			call(NUMBER2);
			call(NUMBER3);
		    comwrt(0x80);
			display("GSM ACCIDENT DET");
		
		}
		else
		{
			buzzer=1;
			comwrt(0xC0);
			display(" VIBRATION: NO  ");		
		}
			
	}
}