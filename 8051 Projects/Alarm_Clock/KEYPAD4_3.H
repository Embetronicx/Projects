sbit r1=P0^0;
sbit r2=P0^1;
sbit r3=P0^2;
sbit r4=P0^3;
sbit c1=P0^4;
sbit c2=P0^5;
sbit c3=P0^6;

unsigned char keypad();
unsigned char key[4][3]={{'1','2','3'},{'4','5','6'},{'7','8','9'},{'*','0','#'}};

unsigned char keypad()
{
char row,col;
unsigned char a;

r1=r2=r3=r4=0;
c1=c2=c3=1;
while(c1&&c2&&c3);
	while(c1==0||c2==0||c3==0)
	{
	r1=0;r2=r3=r4=1;if(c1==0||c2==0||c3==0){row=0;break;}
	r2=0;r1=r3=r4=1;if(c1==0||c2==0||c3==0){row=1;break;}
	r3=0;r1=r2=r4=1;if(c1==0||c2==0||c3==0){row=2;break;}
	r4=0;r2=r3=r1=1;if(c1==0||c2==0||c3==0){row=3;break;}
	}
	if(c1==0&&c2!=0&&c3!=0)col=0;
	else if(c2==0&&c1!=0&&c3!=0)col=1;
	else if(c3==0&&c2!=0&&c1!=0)col=2;
	while(c1==0||c2==0||c3==0);

	a=key[row][col];
	return a;

}