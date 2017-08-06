#define lcd_data P2

sbit rs=P0^0;
sbit rw=P0^1;
sbit en=P0^2;

void lcd_init();
void cmd(unsigned char a);
void dat(unsigned char b);
void show(unsigned char *s);
void lcd_delay();

void lcd_init()
{
cmd(0x38);
cmd(0x0e);
cmd(0x06);
cmd(0x0c);
cmd(0x01);
cmd(0x80);
}

void cmd(unsigned char a)
{
lcd_data=a;
rs=0;
rw=0;
en=1;
lcd_delay();
en=0;
}

void dat(unsigned char b)
{
lcd_data=b;
rs=1;
rw=0;
en=1;
lcd_delay();
en=0;
}

void show(unsigned char *s)
{
while(*s)
{
dat(*s++);
}
}

void lcd_delay()
{
unsigned int lcd_delay;
for(lcd_delay=0;lcd_delay<=1000;lcd_delay++);
}

