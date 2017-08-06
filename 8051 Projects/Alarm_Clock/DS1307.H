unsigned char get_rtc(unsigned char ad);
void disp_time(unsigned char h,unsigned char m,unsigned char s);
void disp_date(unsigned char h,unsigned char m,unsigned char s);
void set_time(unsigned char h,unsigned char m,unsigned char s);
void set_date(unsigned char h,unsigned char m,unsigned char s);

void seT(void);
void al_set(void);

unsigned char ho=100,mi=100;

unsigned char get_rtc(unsigned char ad)
{
return (i2c_read_byte(ad));
}


void disp_time(unsigned char h,unsigned char m,unsigned char s)
{
cmd(0x88);
dat((h/16)+48);
dat((h%16)+48);
dat(':');
dat((m/16)+48);
dat((m%16)+48);
dat(':');
dat((s/16)+48);
dat((s%16)+48);
}

void disp_date(unsigned char h,unsigned char m,unsigned char s)
{
cmd(0xc0);
show("DATE  : ");
cmd(0xc8);
dat((h/16)+48);
dat((h%16)+48);
dat('/');
dat((m/16)+48);
dat((m%16)+48);
dat('/');
dat((s/16)+48);
dat((s%16)+48);
}

void set_time(unsigned char h,unsigned char m,unsigned char s)
{
unsigned char temp;
temp=(h/10)<<4;
h=temp|(h%10);
temp=(m/10)<<4;
m=temp|(m%10);
temp=(s/10)<<4;
s=temp|(s%10);
i2c_send_byte(0x00,s);
i2c_send_byte(0x01,m);
i2c_send_byte(0x02,h);
}

void set_date(unsigned char h,unsigned char m,unsigned char s)
{
unsigned char temp;
temp=(h/10)<<4;
h=temp|(h%10);
temp=(m/10)<<4;
m=temp|(m%10);
temp=(s/10)<<4;
s=temp|(s%10);
i2c_send_byte(0x06,s);
i2c_send_byte(0x05,m);
i2c_send_byte(0x04,h);
}

void seT()
{
unsigned char t1,t2,h,s,m;
		cmd(0x01);
		cmd(0x80);
		show("    SET TIME    ");
L1:		cmd(0xc0);
		show("HH:");
		t1=keypad();
		dat(t1);
		t1=(t1-0x30)*10;
		t2=keypad();
		dat(t2);
		t2=t2-0x30;
		h=t1+t2;
			if(h>23)
			{
			cmd(0xc3);
			show("  ");
			goto L1;
			}
		dat(' ');
L2:		cmd(0xc6);
		show("MM:");
		t1=keypad();
		dat(t1);
		t1=(t1-0x30)*10;
		t2=keypad();
		dat(t2);
		t2=t2-0x30;
		m=t1+t2;
		if(m>59)
			{
			cmd(0xc9);
			show("  ");
			goto L2;
			}
L3:		cmd(0xcb);
		show("SS:");
		t1=keypad();
		dat(t1);
		t1=(t1-0x30)*10;
		t2=keypad();
		dat(t2);
		t2=t2-0x30;
		s=t1+t2;
		if(s>59)
			{
			cmd(0xce);
			show("  ");
			goto L3;
			}
		set_time(h,m,s);
		
		cmd(0x01);
		cmd(0x80);
		show("    SET DATE    ");
L4:		cmd(0xc0);
		show("DD:");
		t1=keypad();
		dat(t1);
		t1=(t1-0x30)*10;
		t2=keypad();
		dat(t2);
		t2=t2-0x30;
		h=t1+t2;
			if(h>31)
			{
			cmd(0xc3);
			show("  ");
			goto L4;
			}
		dat(' ');
L5:		cmd(0xc6);
		show("MM:");
		t1=keypad();
		dat(t1);
		t1=(t1-0x30)*10;
		t2=keypad();
		dat(t2);
		t2=t2-0x30;
		m=t1+t2;
		if(m>12)
			{
			cmd(0xc9);
			show("  ");
			goto L5;
			}
		cmd(0xcb);
		show("YY:");
		t1=keypad();
		dat(t1);
		t1=(t1-0x30)*10;
		t2=keypad();
		dat(t2);
		t2=t2-0x30;
		s=t1+t2;
		set_date(h,m,s);  
		cmd(0x01);
}

void al_set()
{
unsigned char t1,t2;
		cmd(0x01);
		cmd(0x80);
		show("   SET  ALARM   ");
L4:		cmd(0xc0);
		show("HOUR: ");
		t1=keypad();
		dat(t1);
		t1=(t1-0x30)*10;
		t2=keypad();
		dat(t2);
		t2=t2-0x30;
		ho=t1+t2;
		if(ho>23)
			{
			cmd(0xc6);
			show("  ");
			goto L4;
			}
L5:		cmd(0xc9);
		show("MIN: ");
		t1=keypad();
		dat(t1);
		t1=(t1-0x30)*10;
		t2=keypad();
		dat(t2);
		t2=t2-0x30;
		mi=t1+t2;
		if(mi>59)
			{
			cmd(0xce);
			show("  ");
			goto L5;
			}
			t1=0;
		t1=(ho/10)<<4;
		ho=t1|(ho%10);
		t1=0;
		t1=(mi/10)<<4;
		mi=t1|(mi%10);
}

