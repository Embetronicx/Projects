code unsigned char SMS1[2] = "AT" ;
code unsigned char SMS2[9] = "AT+CMGF=1" ;
code unsigned char SMS3[8]= "AT+CMGS=" ; // send "
code unsigned char SMS4[3]= "ATD" ; // send "
code unsigned char SMS5[3]= "ATH" ; // send "


void sendSMS(unsigned char *num , unsigned char *msg);
void delay1(unsigned int tim);
void sendserial(unsigned char mydata1);
void call(unsigned char *num1);

unsigned char i;

void sendSMS(unsigned char *num , unsigned char *msg)
{	
	for (i=0;i<2;i++)
	sendserial(SMS1[i]);
	sendserial(0X0D);
	delay1(60);

	for (i=0;i<9;i++)
	sendserial(SMS2[i]);
	sendserial(0X0D);						
	delay1(60);
	
	for (i=0;i<8;i++)
	sendserial(SMS3[i]);
	sendserial(0x22);  // "
	
	for(;*num!=0;num++)
	sendserial(*num);
	sendserial(0x22);  // "
	sendserial(0X0D);
	delay1(60);
	
	for(;*msg!=0;msg++)
	sendserial(*msg);
	sendserial(0X1A);
	delay1(80);

}

void call(unsigned char *num1)
{
	for (i=0;i<2;i++)
	sendserial(SMS1[i]);
	sendserial(0X0D);
	delay1(60);

	for (i=0;i<9;i++)
	sendserial(SMS2[i]);
	sendserial(0X0D);						
	delay1(60);

	for (i=0;i<3;i++)
	sendserial(SMS4[i]);
	
	for(;*num1!=0;num1++)
	sendserial(*num1);
	sendserial(0x3b);
	sendserial(0X0D);
	delay1(80);
	delay1(600);

	for (i=0;i<3;i++)
	sendserial(SMS5[i]);
	delay1(80);
} 





void delay1(unsigned int tim)
{
	unsigned int h;
	for(h=0;h<=tim;h++) {
		TMOD=0X21;
		TH0=0x4B;
		TL0=0xFD;
		TR0=1;
		while(TF0==0);
		TF0=0;	
	}

	
}


void sendserial(unsigned char mydata1)
{
 
	TI=0; 
	SBUF= mydata1;
	while(TI==0);

  
}

void init_serial()
{
	SCON=0x50;
	TMOD=0x21;
	TH1=0xFD;
	TL1=0xFD;
	TR1=1;
}
