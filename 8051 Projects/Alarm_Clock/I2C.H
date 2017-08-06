unsigned char bdata EP_DATA;

sbit lsb=EP_DATA^0;
sbit msb=EP_DATA^7;

sbit SDA = 	P2^0;
sbit SCL = 	P2^1;


void i2c_start(void);
void i2c_stop(void);

void i2c_send (unsigned char);
void i2c_send_byte(unsigned char addr,unsigned char dataa);

unsigned char i2c_read(void);
unsigned char i2c_read_byte(unsigned char addr);


void i2c_start(void)
{
	SDA=1;
	SCL=1;
	SDA=0;
	SCL=0;
}


void i2c_send (unsigned char send)
{
	unsigned char i;
	EP_DATA=send;
	for(i=0;i<=7;i++)
	{
		SDA=msb;
		SCL=1;
		SCL=0;
		EP_DATA=EP_DATA<<1;
	}
	while(SDA!=0);
	SCL=1;
	SCL=0;
		
}

unsigned char i2c_read(void)
{
	unsigned char i;
	lsb=SDA;
	for(i=0;i<=7;i++)
	{
		EP_DATA=EP_DATA<<1;
		lsb=SDA;
		SCL=1;
		SCL=0;
	}
				
	if(EP_DATA==13)
	{
		SDA=1;
		SCL=1;
		SCL=0;
		SDA=0;
		i2c_stop();
		return(EP_DATA);
	}

	SDA=0;
	SCL=1;
	SCL=0;
	SDA=1;

	return(EP_DATA);
}

void i2c_stop(void)
{
	SDA=0;
	SCL=1;
	SDA=1;
	SCL=0;
}

void i2c_send_byte(unsigned char addr,unsigned char dataa)
{
i2c_start();
i2c_send(0xd0);
i2c_send(addr);
i2c_send(dataa);
i2c_stop();
}

unsigned char i2c_read_byte(unsigned char addr)
{
unsigned char rec;
i2c_start();
i2c_send(0xd0);
i2c_send(addr);
i2c_start();
i2c_send(0xd1);
rec=i2c_read();
i2c_stop();
return rec;
}

									   