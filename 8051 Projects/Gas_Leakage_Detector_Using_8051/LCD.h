

#define LCDDATA P1
#define DELAY for(i=0;i<1200;i++)


sbit RS = P3^7; 
//sbit RW = P3^6;
sbit EN = P3^6;	

void comwrt(unsigned char);
void datawrt(unsigned char);
void  LCD_initialise();
void display(unsigned char *str);


void LCD_initialise()
{
 
 unsigned int i,j;
 
 int com[5]={0x38,0x0C,0x01,0x06,0x80};
 for(j=0;j<=4;j++)
 {
 	comwrt(com[j]);
 	DELAY;
	}
 
 
 
}


void comwrt(unsigned char dat)
{
	unsigned int i;
	LCDDATA=dat;
	RS = 0; 
//	RW = 0;
	EN = 1;
	DELAY;
	EN = 0;
}

void datawrt(unsigned char dat)
{
	unsigned int i;
	LCDDATA=dat;
	RS = 1; 
//	RW = 0;
	EN = 1;
	DELAY;
	EN = 0;
}

void display(unsigned char *str)
{
	int i;
	for(;*str!=0;str++)
 {
 	datawrt(*str);
	DELAY;
	
	}
}
