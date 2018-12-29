#include <conio.h>
#include <dos.h>
#include <time.h>
#include <graphics.h>
#include <alloc.h>
#include <stdlib.h>
#include "agreg.h"


int goutpr(void)
{
int c,del;
 del=1000/180.0*delcl;
 for(c=0;c<500;c++)
	{
	 if(kbhit()) return getch();
	 if(getme()) {if(mse.btsr) return(CCANC);else return(MOUSEV);}
	 delms(2);
	}
for(c=0;(c<del)&&(!kbhit());c++)
 {
	adcget();
	delms(100);
	getch1(0x11);
	if(getme()) {if(mse.btsr) return(CCANC);else return(MOUSEV);}
 }
 if(c==del) return CCANC; else return(getch());
}

void adcpr(int kn,int rp)  /*  kn-kanal namber,rp-ppp:prp, */
{
int a[4]={0,0,0,0};
unsigned long tm=0;
unsigned long timer;
int k,c;
c=100;
if(kn<4)
 {

 if(chn[kn]==0) {if(rp)avptr->prmk[kn].prp=0;else avptr->prmk[kn].ppp=0; return;}
 for(k=0;k<10;k++)
	{
	 do
	 timer=time(NULL);
	 while(tm==timer);
	adcget();
  a[0]+=avptr->prmk[kn].p;
				avptr->prmk[kn].t=9-k;
		while(kbhit()) getch();
	getch1(0x11);
	timer=time(NULL);
	tm=timer;
	}

 if(rp)avptr->prmk[kn].prp=(int)(a[0]/10);
 else avptr->prmk[kn].ppp=(int)(a[0]/10);
 prmscr(kn);
 return;
 }

 for(k=0;k<10;k++)
	{
	 do
		timer=time(NULL);
	 while(tm==timer);
	adcget();
	for(kn=0;kn<4;kn++)
   {
		if(chn[kn]!=0)
     {
		 a[kn]+=avptr->prmk[kn].p;
		 avptr->prmk[kn].t=9-k;
			while(kbhit()) getch();
			getch1(0x11);
		 }
	 }
	timer=time(NULL);
	tm=timer;

	}
 for(c=0;c<4;c++)
   {
    if(chn[c]!=0)
     {
    if(rp) avptr->prmk[c].prp=(int)(a[c]/10);
    else  avptr->prmk[c].ppp=(int)(a[c]/10);
     prmscr(c);
     }
   }
} /*adcpr*/

int getprsel(int f)
 {
	int y;
	 if((mse.x<(x0+1+f*8))||(mse.x>(14*8+x0-1+f*8))) return(-1);
	 for(y=0;y<5;y++)
		if((mse.y>((y+14)*dly-5))&&(mse.y<((y+15)*dly-5))) return(y);
	 return(-1);
 }


int pppset(void)
 {
	int n,c,y,m;
	char *buff;
	char bufer[15];
	 m=mast;
	 dam();
	 setviewport(336+x0,dly*5,528+x0,dly*8+6,1);
	 clearviewport();
	 setviewport(10+x0,dly*23,600+x0,dly*24-1,1);
	 clearviewport();
	 setviewport(0,0,639+x0,dly*25-3,1);
	 setcolor(HCOLOR);
	 outtextxy(10+x0,dly*23,"Enter - измерить ; - вверх ; - вниз ;Esc - выход");
	 setcolor(ATCOLOR);
	 outtextxy(336+x0,dly*5,"Залейте бедную плазму");
	 outtextxy(336+x0,dly*6,"в измерительные кюветы");
	 outtextxy(336+x0,dly*7,"  и нажмите ENTER");
	 buff=malloc(imagesize(16+x0,13*dly,144+x0,21*dly));
	 getimage(16+x0,13*dly,144+x0,21*dly,buff);
	 setcolor(RMCOLOR);
	 line(16+x0,dly*13,16+16*8+x0,dly*13);
	 line(16+16*8+x0,dly*13,16+16*8+x0,dly*19+1);
	 line(16+x0,dly*19+1,16+16*8+x0,dly*19+1);
	 line(16+x0,dly*13,16+x0,dly*19+1);
	 setcolor(OMCOLOR);
	 outtextxy(16+x0,dly*14,"  ИЗМЕРИТЬ ВСЕ");
	 for(n=0;n<4;n++)  /*374*/
		{
		 setviewport(32+x0,(15+n)*dly,128+x0,(16+n)*dly,1);
		 sprintf(bufer,"%d - %s",n+1,(avptr->prmk[n].ppp==0)?"НЕ ИЗМ.":"ИЗМЕРЕН");
		 outtext(bufer);
		}
	 setviewport(0,0,639+x0,dly*25-3,1);
	 y=0;
	 inblok(3,14+y,14);
	 eam();
	 for(c=0;c!=27;c=goutpr())
		{
		 switch(c)
			{
			 case 72 :inblok(3,14+y,14);if(y>0) y--;else y=4;inblok(3,14+y,14);break;
			 case 80 :inblok(3,14+y,14);if(y<4) y++;else y=0;inblok(3,14+y,14);break;
			 case MOUSEV:
									 if(getprsel(3)==-1) break;
									 inblok(3,14+y,14);
									 y=getprsel(3);
									 inblok(3,14+y,14);
									 if(mse.ev);else break;
			 case 13 :dam();
          setviewport(336+x0,dly*5,528+x0,dly*8+6,1);
          clearviewport();
          setviewport(0,0,639+x0,dly*25-3,1);
					setcolor(ALCOLOR);
					outtextxy(336+x0,dly*5,"Измерение");
          if(y==0) adcpr(4,0);
           else if(y!=0) adcpr(y-1,0);
          setviewport(0,0,639+x0,dly*25-3,1);
          inblok(3,14+y,14);
          for(n=0;n<4;n++)
           {
						setviewport(24+x0,(15+n)*dly,128+x0,(16+n)*dly,1);
						clearviewport();
						setviewport(30+x0,(15+n)*dly,118+x0,(16+n)*dly,1);
						sprintf(bufer,"%d - %s",n+1,(avptr->prmk[n].ppp==0)?"НЕ ИЗМ.":"ИЗМЕРЕН");
						setcolor(OMCOLOR);
						outtext(bufer);
					 }
					setviewport(336+x0,dly*5,528+x0,dly*8+6,1);
					clearviewport();
					setviewport(0,0,639+x0,dly*25-3,1);
					inblok(3,14+y,14);
					setviewport(0,0,639+x0,dly*25-3,1);
					putimage(16+x0,13*dly,buff,0);
					free(buff);
					setviewport(336+x0,dly*5,528+x0,dly*8+6,1);
					clearviewport();
					setviewport(0,0,639+x0,dly*25-6,1);
					if(m) eam();
					return 1;
			 case 0:break;
			 case CCANC:
					 dam();
           setviewport(0,0,639+x0,dly*25-3,1);
					 putimage(16+x0,13*dly,buff,0);
					 free(buff);
					 setviewport(336+x0,dly*5,528+x0,dly*8+6,1);
					 clearviewport();
					 setviewport(0,0,639+x0,dly*25-6,1);
					 if(m) eam();
					 return 0;
			}
		}
	 dam();
	 setviewport(0,0,639+x0,dly*25-3,1);
	 putimage(16+x0,13*dly,buff,0);
	 free(buff);
	 setviewport(336+x0,dly*5,528+x0,dly*8+6,1);
	 clearviewport();
	 setviewport(0,0,639+x0,dly*25-6,1);
	 if(m) eam();
	 return 0;
 } /*pppset*/



int prpset(void)
 {
	int n,c,y,m,x=120;
	char *buff;
	char bufer[15];
	 m=mast;
	 dam();
	 setviewport(336+x0,dly*5,528+x0,dly*8+6,1);
	 clearviewport();
	 setviewport(10+x0,dly*23,600+x0,dly*24-1,1);
	 clearviewport();
	 setviewport(0,0,639+x0,dly*25-3,1);
	 setcolor(HCOLOR);
	 outtextxy(10+x0,dly*23,"Enter - измерить ; - вверх ; - вниз ;Esc - выход");
	 setcolor(ATCOLOR);
	 outtextxy(336+x0,dly*5,"Залейте богатую плазму");
	 outtextxy(336+x0,dly*6,"в измерительные кюветы");
	 outtextxy(336+x0,dly*7,"  и нажмите ENTER");
	 buff=malloc(imagesize(16+x+x0,13*dly,144+x+x0,21*dly));
	 getimage(16+x+x0,13*dly,144+x+x0,21*dly,buff);
	 setcolor(RMCOLOR);
	 line(16+x+x0,dly*13,16+x+16*8+x0,dly*13);
	 line(16+x+16*8+x0,dly*13,16+x+16*8+x0,dly*19+1);
	 line(16+x+x0,dly*19+1,16+x+16*8+x0,dly*19+1);
	 line(16+x+x0,dly*13,16+x+x0,dly*19+1);
	 setcolor(OMCOLOR);
	 outtextxy(16+x+x0,dly*14,"  ИЗМЕРИТЬ ВСЕ");
	 for(n=0;n<4;n++)  /*374*/
		{
		 setviewport(32+x+x0,(15+n)*dly,128+x+x0,(16+n)*dly,1);
		 sprintf(bufer,"%d - %s",n+1,(avptr->prmk[n].prp==0)?"НЕ ИЗМ.":"ИЗМЕРЕН");
		 outtext(bufer);
		}
	 setviewport(0,0,639+x0,dly*25-3,1);
	 y=0;
	 inblok(18,14+y,14);
	 eam();
	 for(c=0;c!=27;c=goutpr())
		{
		 switch(c)
			{
			 case 72 :inblok(18,14+y,14);if(y>0) y--;else y=4;inblok(18,14+y,14);break;
			 case 80 :inblok(18,14+y,14);if(y<4) y++;else y=0;inblok(18,14+y,14);break;
			 case MOUSEV:
									 if(getprsel(18)==-1) break;
									 inblok(18,14+y,14);
									 y=getprsel(18);
									 inblok(18,14+y,14);
									 if(mse.ev);else break;
			 case 13 : dam();
          setviewport(336+x0,dly*5,528+x0,dly*8+6,1);
          clearviewport();
					setviewport(0,0,639+x0,dly*25-3,1);
					setcolor(ALCOLOR);
/*					outtextxy(336+x0,dly*5,"ИЗМЕРЕНИЕ ПОШЛО !");*/
					outtextxy(336+x0,dly*5,"Измepeниe");
          if(y==0) adcpr(4,1);
          else if(y!=0) adcpr(y-1,1);
          setviewport(0,0,639+x0,dly*25-3,1);
					inblok(18,14+y,14);
					setcolor(OMCOLOR);
          for(n=0;n<4;n++)
           {
						setviewport(24+x+x0,(15+n)*dly,128+x+x0,(16+n)*dly,1);
						clearviewport();
						setviewport(30+x+x0,(15+n)*dly,118+x+x0,(16+n)*dly,1);
						sprintf(bufer,"%d - %s",n+1,(avptr->prmk[n].prp==0)?"НЕ ИЗМ.":"ИЗМЕРЕН");
						outtext(bufer);
           }
					setviewport(336+x0,dly*5,528+x0,dly*8+6,1);
					clearviewport();
					setviewport(0,0,639+x0,dly*25-3,1);
					inblok(18,14+y,14);
					setviewport(0,0,639+x0,dly*25-3,1);
					putimage(16+x+x0,13*dly,buff,0);
					free(buff);
					setviewport(336+x0,dly*5,528+x0,dly*8+6,1);
					clearviewport();
					setviewport(0,0,639+x0,dly*25-3,1);
					if(m) eam();
					return 1;
			 case 0:break;
			 case CCANC:
								dam();
								setviewport(0,0,639+x0,dly*25-3,1);
								putimage(16+x+x0,13*dly,buff,0);
								free(buff);
								setviewport(336+x0,dly*5,528+x0,dly*8+6,1);
								clearviewport();
								setviewport(0,0,639+x0,dly*25-3,1);
								if(m) eam();
								return 0;
			}
		}
	 dam();
	 setviewport(0,0,639+x0,dly*25-3,1);
	 putimage(16+x+x0,13*dly,buff,0);
	 free(buff);
	 setviewport(336+x0,dly*5,528+x0,dly*8+6,1);
	 clearviewport();
	 setviewport(0,0,639+x0,dly*25-3,1);
	 if(m) eam();
	 return 0;
} /*prpset*/

void chnset(void)
 {
	int n,c,y,m,dx=8;
	char *buff;
	char bufer[15];
	 m=mast;
	 dam();
	 setviewport(10+x0,dly*23,600+x0,dly*24-1,1);
	 clearviewport();
	 setviewport(0,0,639+x0,dly*25-3,1);
	 setcolor(HCOLOR);
	 outtextxy(10+x0,dly*23,"Enter - вкл/выкл ; - вверх ; - вниз ;Esc - выход");
	 buff=malloc(imagesize(390-16*dx+x0,13*dly,518+x0-16*dx,21*dly));
	 getimage(390+x0-16*dx,13*dly,518+x0-16*dx,21*dly,buff);
	 setviewport(390+x0-16*dx,13*dly,518+x0-16*dx,20*dly-8,0);
	 clearviewport();
	 setviewport(0,0,639+x0,dly*25-3,1);
	 setcolor(RMCOLOR);
	 line(390+x0-16*dx,dly*13,390+16*8-16*dx+x0,dly*13);
	 line(390-16*dx+16*8+x0,dly*13,390-16*dx+16*8+x0,dly*19+1);
	 line(390-16*dx+x0,dly*19+1,390+16*8-16*dx+x0,dly*19+1);
	 line(390-16*dx+x0,dly*13,390+x0-16*dx,dly*19+1);
	 setcolor(OMCOLOR);
	 outtextxy(390+x0-16*dx,dly*14,"  ВКЛЮЧИТЬ ВСЕ");
	 for(n=0;n<4;n++)
		{
		 setviewport(406+x0-16*dx,(15+n)*dly,502+x0-16*dx,(16+n)*dly,1);
		 sprintf(bufer,"%d - %s",n+1,(chn[n]==0)?"ВЫКЛЮЧЕН":"ВКЛЮЧЕН");
		 outtext(bufer);
		}
	 setviewport(0,0,639+x0,dly*25-3,1);
	 y=0;
	 inblok(34,14+y,14);
	 eam();
	 for(c=0;c!=27;c=getch1(0))
		{
		 switch(c)
			{
			 case 72 :inblok(34,14+y,14);if(y>0) y--;else y=4;inblok(34,14+y,14);break;
			 case 80 :inblok(34,14+y,14);if(y<4) y++;else y=0;inblok(34,14+y,14);break;
			 case MOUSEV:
									 if(getprsel(34)==-1) break;
									 inblok(34,14+y,14);
									 y=getprsel(50);
									 inblok(34,14+y,14);
									 if(mse.ev);else break;
			 case 13 :dam();
          if(y==0) for(n=0;n<4;n++) chn[n]=0xff;
          else if(y!=0) chn[y-1]=~chn[y-1];
          setviewport(0,0,639+x0,dly*25-3,1);
					inblok(34,14+y,14);
					setcolor(OMCOLOR);
					for(n=0;n<4;n++)
           {
						setviewport(400+x0-16*dx,(15+n)*dly,512+x0-16*dx,(16+n)*dly,1);
						clearviewport();
						setviewport(406-16*dx+x0,(15+n)*dly,502+x0-16*dx,(16+n)*dly,1);
						sprintf(bufer,"%d - %s",n+1,(chn[n]==0)?"ВЫКЛЮЧЕН":"ВКЛЮЧЕН");
						outtext(bufer);
           }
					setviewport(0,0,639+x0,25*dly-3,1);
					inblok(34,14+y,14);
					eam();
					break;
			 case CCANC:
						 dam();
						 setviewport(0,0,639+x0,dly*25-3,1);
						 putimage(390+x0-16*dx,13*dly,buff,0);
						 free(buff);
						 avptr->fxl=1;
						 if(m) eam();
						 return;
			 case 0  :break;
			}
		}
	 dam();
	 setviewport(0,0,639+x0,dly*25-3,1);
	 putimage(390+x0-16*dx,13*dly,buff,0);
	 free(buff);
	 avptr->fxl=1;
	 if(m) eam();
	} /*chanel set*/
