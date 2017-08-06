void ser_init();
void tx(unsigned char send);
void tx_str(unsigned char *s);
unsigned char rx();

void sms(unsigned char *num1,unsigned char *msg);
void call(unsigned char *num2);
void gsm_delay();

unsigned int dell;

void sms(unsigned char *num1,unsigned char *msg)
{
tx_str("AT");
tx(0x0d);
gsm_delay();

tx_str("AT+CMGF=1");
tx(0x0d);
gsm_delay();

tx_str("AT+CMGS=");
tx('"');
while(*num1)
	tx(*num1++);
tx('"');
tx(0x0d);
gsm_delay();

while(*msg)
	tx(*msg++);
tx(0x1a);
gsm_delay();
}

void call(unsigned char *num2)
{
tx_str("AT");
tx(0x0d);
gsm_delay();

tx_str("AT+CMGF=1");
tx(0x0d);
gsm_delay();

tx_str("ATD");
while(*num2)
	tx(*num2++);
tx(';');
tx(0x0d);
for(dell=0;dell<=30;dell++)
	gsm_delay();

tx_str("ATH");
tx(0x0d);
gsm_delay();
}



void ser_init()
{
	SCON=0x50;
	TMOD|=0x20;
	TH1=0xFD;
	TL1=0xFD;
	TR1=1;
}

void tx(unsigned char send)
{
SBUF=send;
while(TI==0);
TI=0;
}

void tx_str(unsigned char *s)
{
while(*s)
tx(*s++);
}

unsigned char rx()
{
while(RI==0);
RI=0;
return SBUF;
}

void gsm_delay()
{
unsigned int gsm_del;
for(gsm_del=0;gsm_del<=50000;gsm_del++);
}




