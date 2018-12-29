#include <graphics.h>
#include <stdlib.h>
#include <dos.h>
#include <stdio.h>
#include <fcntl.h>
#include "agreg.h"

void wtemp(void)
{
 int a=0/*, mf=0*/;
 int m;
 char buff[20];
 m=mast;
 dam();
 rmkl();
 imnk(0);
 setviewport(200+x0,6*dly,440+x0,14*dly,1);
 clearviewport();
 setcolor(RMCOLOR);
 line(0,0,0,8*dly);
 line(240,0,240,8*dly);
 line(0,0,240,0);
 line(0,8*dly,240,8*dly);
 setcolor(LIGHTMAGENTA);
 outtextxy(0,dly*1,"      ‘ˆ‘’…Œ€ ‚›•Ž„ˆ’");
 outtextxy(0,dly*3,"        € €Ž—ˆ‰");
 outtextxy(0,dly*5,"       ’…Œ…€’“›‰");
 outtextxy(0,dly*7,"      P…†ˆŒ (’=37 £p ¤)");

 setviewport(x0+280, 0, x0+370, dly, 1);
 clearviewport();
 adcget();
 if(tcross[tgr0]>36.7)
			{
			 ctlcop=8;
			 outportb(CTL,ctlcop);
			}

 while(  ( (tcross[tgr0]<36.8)||(tcross[tgr0]>37.1) )   &&(a==0))
 {
	adcget();
	while(kbhit())  a=getch();
	eam();
	if(getme()) if(mse.btsr) a=1;
	dam();
  clearviewport();
	sprintf(buff,"  t=%2.1f",tcross[tgr0]);
	setcolor(LIGHTCYAN);
	if(tgr0<189) setcolor(BLUE);
	if(tgr0>216) setcolor(RED);
	if(tgr0<3) {setcolor(LIGHTBLUE);sprintf(buff,"   t<20");}
	if(tgr0>240) {setcolor(LIGHTRED);sprintf(buff,"   t>39");}
  outtext(buff);
	if(tcross[tgr0]<36.7) tc0=15;
	 else if(tcross[tgr0]<36.8) tc0=8;
				 else if(tcross[tgr0]<36.9) tc0=4;
							else tc0=0;
	if(tcross[tgr0]>37.0) culon(); else culoff();
	ctlcop=(ctlcop&0xf)|(tc0<<4);
	outportb(CTL,ctlcop);
	if(kgplus==1) ktermo(kadcget());
 } /*while temp*/
if(v2) {}
 else outportb(CTL,ctlcop);
setviewport(0,0,639+x0,dly*25-3,1);
culoff();
if(m) eam();
} /**/


char newtc(int t)
{
	char tc;
 if(tcross[t]<36.8) culoff();
 if(tcross[t]>36.8) culon();
	if(tcross[t]<36.6) {tc=15;  return tc; }
	if(tcross[t]<36.7) {tc=15;  return tc; }
	if(tcross[t]<36.8) {tc=8;   return tc;}
	if(tcross[t]<36.9) {tc=4;   return tc;}
	if(tcross[t]<37.0) {tc=2; }
								 else {tc=0;}
return tc;
}


char newtc1(int t)
{
	char tc;
 if(tcross[t]<37.0) culoff();
 if(tcross[t]>37.0) culon();
 if(tcross[t]<36.8) {tc=15;  return tc; }
 if(tcross[t]<36.9) {tc=15;  return tc; }
 if(tcross[t]<37.0) {tc=8;   return tc;}
 if(tcross[t]<37.1) {tc=4;   return tc;}
 if(tcross[t]<37.2) {tc=2; }
								 else {tc=0;}
 return tc;
}




int kadcget(void)   /*¯®ª § ­¨ï á €– â¥¬¯¥à âãàë ª®ã£ã«®¬¥âà */
{
 int a,ktgr;
 int i,j,l,k=4;
 unsigned int ii;
 int s[6];
 char ctlsav;
 aad(); ake(); delms(100);
 j=4; s[j]=0;
 ctlcop=ctlcop&0xf8; ctlsav=ctlcop;
	 ctlcop=ctlcop|j;
	 outportb(CTL,ctlcop);
	 delms(5);
   for(l=0;l<k;l++)
		{if(rdyb)
		 {ctlcop=ctlcop|0x8;outportb(CTL,ctlcop);inportb(ADC);
			i=0x8; ctlcop=ctlcop&(~i);outportb(CTL,ctlcop);
		 }
		 else
		 {i=0x8; ctlcop=ctlcop&(~i);outportb(CTL,ctlcop);ctlcop=ctlcop|0x8;
			outportb(CTL,ctlcop); if(!rdy) delms(1);
		 }
			s[j]=inportb(ADC) + s[j]; delms(1);
		}
		akd(); aae();
	 ctlcop=ctlcop&(~j);
 ctlcop=ctlsav|4|8;
 outportb(CTL,ctlcop);
 ktgr=(int) ((1.0*s[4])/(1.0*k));
		delms(100);
 return ktgr;
}/*kadcget*/


void ktermo(int kt)
{
 char ktc;
 if(tmd) kt=255-kt;
/* if(tkor)
 {if(tkor>0) if(tkor+kt<255) kt+=ktkor; else;
				else if(ktkor+kt>0) kt+=ktkor;
 }*/
 ktc=newtc(kt);
 ktc=ktc<<4;
 ktc=ktc & 0xf0;
 pccop=(pccop&0xf)|ktc;
 outportb(PC,pccop);
}/*termo*/

