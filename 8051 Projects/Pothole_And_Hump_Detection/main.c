#include<reg51.h>
#include"ULTRASONIC.H"
#include"GSM.H"
#include"LCD.H"

#define NUMBER "0123456789"  //Your mobile number

#define delay for(i=0;i<=60000;i++)

sbit sw=P0^7;

unsigned int range=0,i,k;
unsigned char snumb[10],numb[10],temp;
unsigned char hump[]="Distance:   cm,        detected";

void main(void)
{
	ser_init();
	ultrasonic_init();
	lcd_init();
	show("Loading ");
	for(k=0;k<5;k++) {
		dat('.');
		delay;
	}
	sw=1;
	delay;
	while(1) {
		cmd(0x80);
		show("DISTANCE: ");
		range=ultrasonic();
		cmd(0x8a);
		dat((range/100)+48);
		dat(((range/10)%10)+48);
		dat((range%10)+48);
		show(" cm ");
			if(sw==0) {
				if(range<16) {
					cmd(0xc0);
					show("Hump Detected...");
					hump[9]=(range/100)+48;
					hump[10]=((range/10)%10)+48;
					hump[11]=(range%10)+48;
					hump[15]=' ';
					hump[16]=' ';
					hump[17]='H';
					hump[18]='U';
					hump[19]='M';
					hump[20]='P';
					hump[21]=' ';	
					cmd(0xc0);
					show("Sending message!");
					sms(NUMBER,hump);	
					cmd(0xc0);
					show("Message Sent!!!!");
					delay;
				} else if ((range>20) && (range<50)) {
				cmd(0xc0);
				show("Pothole Detected");
				hump[9]=(range/100)+48;
				hump[10]=((range/10)%10)+48;
				hump[11]=(range%10)+48;
				hump[15]='P';
				hump[16]='O';
				hump[17]='T';
				hump[18]='H';
				hump[19]='O';
				hump[20]='L';
				hump[21]='E';
				cmd(0xc0);
				show("Sending message!");
				sms(NUMBER,hump);
				cmd(0xc0);
				show("Message Sent!!!!");
				delay;
			} else {
				cmd(0xc0);
				show("<<Drive Safely>>"); 
			}
		} else {
			cmd(0xc0);
			show("~PLS SWITCH ON~ "); 
		}
	}
}
