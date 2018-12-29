#include <graphics.h>
#include <stdlib.h>
#include <dos.h>
#include <stdio.h>
#include <fcntl.h>
#include "agreg.h"

char func(int  xx)
{
 int i; long double  yy,xxx;
 xxx=(long double)(xx);
 yy=avptr->funkoef[0];
 for(i=1; i<=avptr->apprx; i++) { yy = yy +avptr->funkoef[i]*xxx; xxx=xxx*xx; }
 if(yy>254.0) return(254);
 if(yy<1.0) return(0);
 return((unsigned char)(yy));
}/*func*/

void ss(void)
 {
	float f;
	 if(v2)
		{
		 f=speed/10;
		 KD=(unsigned int) (1193180.0/f);
		}
	 else
		{
		 dbccop=dbccop&0xf0;
		 dbccop=dbccop|(speed/100-3);
		 outportb(DBC,dbccop);
		}
 }


void speedset(void)     /*pаботает!?*/
{
 int a,c,m,dx=8;
 char bufer[15];
 char *buff;
 m=mast;
 dam();
 buff=malloc(imagesize(50*dx+x0,17*dly,62*dx+x0,dly*24));
 getimage(50*dx+x0,17*dly,62*dx+x0,24*dly,buff);
 setviewport(10+x0,dly*23,510+x0,dly*24-1,1);
 clearviewport();
 setviewport(0,0,639+x0,dly*25-3,1);
 setcolor(HCOLOR);
 outtextxy(10+x0,dly*23,"Enter - ввод ; - менньше ; - больше ;Esc - выход");
 setcolor(RMCOLOR);
 line(50*dx+x0,dly*17,50*dx+12*8+x0,dly*17);
 line(50*dx+12*8+x0,dly*17,50*dx+12*8+x0,dly*19);
 line(50*dx+x0,dly*19,50*dx+12*8+x0,dly*19);
 line(50*dx+x0,dly*17,50*dx+x0,dly*19);
 setviewport(54*dx+x0,dly*18,58*dx+x0,dly*19-1,0);
 eam();
 for(c=0;c!=27;c=getch1(0))
 {
  switch(c)
  {
	 case MOUSEV:if(mse.bts==1); else if(mse.btsm==1) {if(speed>500)  speed-=100;ss();break;}else break;
	 case 72:if(speed<1600) speed+=100;ss();break;
	 case 80:if(speed>500)  speed-=100;ss();break;
	 case CCANC:
   case 13:
				 dam();
				 setviewport(0,0,639+x0,dly*25-3,1);
				 putimage(50*dx+x0,17*dly,buff,0);
         free(buff);
				 if(m) eam();
				 return;
   case 0 :break;
	}
	dam();
  sprintf(bufer,"%4d",speed);
	clearviewport();
	setcolor(OMCOLOR);
	outtextxy(0,0,bufer);
	eam();
 }
 dam();
 setviewport(0,0,639+x0,dly*25-3,1);
 putimage(50*dx+x0,17*dly,buff,0);
 free(buff);
 if(m) eam();
} /*end speed_set */


void aae(void)
{
 int i=0x80;
 dbccop=dbccop&(~i); outportb(DBC,dbccop); /*разреш вход агрегометра*/
 DRB=dbccop;
}

void ake(void)
{
 int i=0x40;
 dbccop=dbccop&(~i); outportb(DBC,dbccop); /*разреш вход коугулометра*/
 DRB=dbccop;
}

void aad(void)
{
 dbccop=dbccop|0x80; outportb(DBC,dbccop); /*запрет вход агрегометра*/
  DRB=dbccop;
}

void akd(void)
{
 dbccop=dbccop|0x40; outportb(DBC,dbccop); /*запрет вход коугулометра*/
  DRB=dbccop;
}

void culon() /*включить куллер*/
{
 dbccop=dbccop|0x20; outportb(DBC,dbccop);
 DRB=dbccop;
}

void culoff()  /*выключить куллер*/
{
 int i;
 i=0x20; i=~i; dbccop=dbccop&i; outportb(DBC,dbccop);
 DRB=dbccop;
}
