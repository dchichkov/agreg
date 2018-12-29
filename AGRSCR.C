#include <graphics.h>
#include <stdlib.h>
#include <dos.h>
#include <stdio.h>
#include <fcntl.h>
#include "agreg.h"

void palletini(int b)
{
 union REGS r;
	if(b)                                /*31*/
	{
	 r.x.ax=0x1000; r.h.bl=15; r.h.bh=31; int86(0x10,&r,&r);
	 return;
	}
 r.x.ax=0x1000; r.h.bl=15;r.h.bh=255; int86(0x10,&r,&r);
} /* opaletini */



void rmkl(void)  /*pамка главного меню*/
{
 int c,m;
 m=mast;
 dam();
 avptr->fxl=1;
 setviewport(0,0,639+x0,dly*25-3,1);
 cleardevice();
 setcolor(RMCOLOR);
 line(0+x0,0,80*8+x0-1,0);
 line(0+x0,24*dly,80*8+x0-1,24*dly);
 line(0+x0,10*dly,80*8+x0-1,10*dly);
 line(0+x0,20*dly,80*8+x0-1,20*dly);
 line(0+x0,22*dly,80*8+x0-1,22*dly);
 line(80*8+x0-1,0,80*8+x0-1,24*dly);
 line(40*8+x0,0,40*8+x0,20*dly);
 line(0+x0,0,0+x0,24*dly);
 line(16*8+x0,20*dly,16*8+x0,22*dly);
 line(32*8+x0,20*dly,32*8+x0,22*dly);
 line(48*8+x0,20*dly,48*8+x0,22*dly);
 line(64*8+x0,20*dly,64*8+x0,22*dly);
 imnk(0);
 for(c=0;c<4;c++)   {avptr->fxl=1;prmscr(c);}
 if(m) eam();
} /**/



void inblok(int x,int y,int n)   /*инв. блок длинной n символов*/
 {
	int cl,m;
	int i;
	char *bufer;
	 m=mast;
	 dam();
	 x=x*8;
	 y=y*dly;
	 cl=imagesize(x+x0,y-2,x+n*8+x0,y+7);
	 bufer=malloc(cl);
	 getimage(x+x0,y-2,x+n*8+x0,y+7,bufer);
/*	 for(i=0;i<cl;i++) if(bufer[i]==)*/
	 putimage(x+x0,y-2,bufer,4);/*4*/
	 free(bufer);
	 if(m) eam();
 }/*inblock*/


void mainh(int pr)
{
 char buka[100];
 int m,hxp=dly*23;
 m=mast;
 dam();
 setviewport(10+x0,hxp,629+x0,dly*24-1,1);
 clearviewport();
 setviewport(0,0,639+x0,dly*25-3,1);
 setcolor(HCOLOR);
 switch(pr)
 {
	case 0 : outtextxy(10+x0,hxp,"Обработка бедной плазмы - Enter , F10 - выход, F1-help  ");break;
	case 1 : outtextxy(10+x0,hxp,"Запуск процесса агрегации - Enter , F10 - выход, F1-help");break;
	case 2 : outtextxy(10+x0,hxp,"Выбор работающих каналов - Enter , F10 - выход, F1-help ");break;
	case 3 : outtextxy(10+x0,hxp,"Выбор скорости мешалки - Enter , F10 - выход, F1-help   ");break;
	case 4 : outtextxy(10+x0,hxp,"Выxoд - Enter , F10 - выход, F1-help   ");break;
	case 10 :outtextxy(10+x0,hxp,"Пуск/стоп - Enter, F1-help                          ");break;
	case 20 :outtextxy(10+x0,hxp,"Выбор  каналa  - Enter, F1-help                         ");break;
	case 21 :outtextxy(10+x0,hxp,"Печать: Принтер - Enter,Пpотокол - F6, F1-help              ");break;
	case 22 :outtextxy(10+x0,hxp,"Выход - Enter, F1-help                                  ");break;
	case 23 :outtextxy(10+x0,hxp,"Расчет - Enter ,обработка F6, F1-help                   ");break;
	case 24 :outtextxy(10+x0,hxp,"Выбор точки - Enter, F1-help                            ");break;
	case 51 :outtextxy(10+x0,hxp,"Выбрать Enter, , - выбоp канала                       ");break;
	case 68 :sprintf(buka,"Выбор положения точки '%c' - ,Enter,Esc                       ",avptr->activpix[avptr->ach]+65);
           outtextxy(10+x0,hxp,buka);break;
 }
 if(m) eam();
} /*mainhelp*/
