#include <graphics.h>
#include <io.h>
#include <conio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <dir.h>
#include <dos.h>
#include <sys\stat.h>
#include "agreg.h"
/*********************/
void saveskreen(int);  /*0-save    1-load
void blank(void);
void blankdrow(void);
void blankdun(void);

/********************/
void saveskreen(int slf)
{
 char *slbufer;
 long hlong;
 int ymin,ymax;
 int c;
 int fp;
 int     grdr = HERCMONO;
 int     grmod = HERCMONOHI;
 if(egmd==1) {grdr=EGA;grmod=EGAHI;x0=0;cl1=15;}

 if(slf==0)
	{
	 fp=open("AGRSAVE.$$$",O_CREAT|O_WRONLY|O_BINARY,S_IWRITE|S_IREAD);
	 setviewport(0,0,639+x0,dly*25-3,0);
	}

 if(slf==1)
	{
	 fp=open("AGRSAVE.$$$",O_RDWR|O_BINARY,S_IREAD|S_IWRITE);
	 initgraph(&grdr, &grmod,"");
	 palletini(1);
	 setbkcolor(FON);
	}

 for(c=1;c<=25;c++)
	{
	 ymin=dly*(c-1);
	 ymax=dly*c;if(c==25) ymax=ymax-3;
	 hlong=imagesize(0,ymin,639+x0,ymax);
	 slbufer=malloc(hlong);
	 if(slf==0)
		{
		 getimage(0,ymin,639+x0,ymax,slbufer);
		 write(fp,slbufer,hlong);
		}
	 if(slf==1)
		{
		 read(fp,slbufer,hlong);
		 putimage(0,ymin,slbufer,0);
		}
	 free(slbufer);
	}
 close(fp);
 if(slf==1) unlink("AGRSAVE.$$$");
 if(slf==0) {closegraph();palletini(0);}
}

void curs(int a)
{
 union REGS r;
 r.h.ah=1;
 r.h.ch=a;
 r.h.cl=7;
 int86(0x10,&r,&r);
}



void blankdrow(void)
{
 char *buff,*buff1;
 int x,y,a;
 int fp;
 buff=malloc(4000);
 buff1=malloc(2000);
 fp=open("AGREG.PIK",O_RDWR|O_BINARY,S_IREAD|S_IWRITE);
 read(fp,buff1,2000);
 a=0;
 for(y=0;y<25;y++)
	for(x=0;x<80;x++)
	{
	 if(((x>1)&&(x<77))&&((y<24)&&(y>0)))
		{
		 buff[a*2]=buff1[a-80];
		 if(buff1[a-80]!=' ') buff[a*2+1]=0x17;else buff[a*2+1]=0x1b;
		}
	 else
		{
		 buff[a*2]=177;
		 buff[a*2+1]=0x0f;
		 if(x<2) buff[a*2+1]=0;
		}
	 if(((x==77)||(x==78))&&((y>1)&&(y<25))) buff[a*2+1]=0x7;
	 if((y==24)&&(x<77)&&(x>3)) buff[a*2+1]=0x7;
	 a++;
	}
 puttext(1,1,80,25,buff);
 free(buff1);
 free(buff);
 close(fp);
 curs(6);
 gotoxy(32,13+3);printf("%3.1f (%%)",avptr->rez[avptr->ach].s);
 gotoxy(32,14+3);printf("%3d (ᥪ)",(int)avptr->rez[avptr->ach].t);
 gotoxy(32,15+3);printf("%3.2f (%%/ᥪ)",avptr->rez[avptr->ach].v);
 gotoxy(32,16+3);printf("%3.2f (%%/ᥪ)",avptr->rez[avptr->ach].vmax);
}


void fname(char *filename,char *fdstr)
 {
	char *path;
	int f,i,d;
	struct ffblk fff;
	path=getcwd(NULL,132);
	i=0;
	 do
		{
		 sprintf(filename,"%s\\DATA\\%d.dat",path,i);
		 d=i;
		 f=findfirst(filename,&fff,FA_ARCH);
		 i++;
		}
	 while(f==0);
	sprintf(fdstr,"%s\\DATA.GRF\\%d.dat",path,d);
	free(path);
 }

void blnclr()
 {
	int i,s;
  for(s=0;s<4;s++)
	 {
		for(i=0;i<940;i++) buffbln[s][i]=32;
		for(i=0;i<20;i++) {buffbln[s][47*i+45]=13;buffbln[s][47*i+46]=10;}
	 }
 }/*blnclr*/

void bln1clr()
 {
	int i;
	 for(i=0;i<940;i++) buffbln[avptr->ach][i]=32;
	 for(i=0;i<20;i++) {buffbln[avptr->ach][47*i+45]=13;buffbln[avptr->ach][47*i+46]=10;}
 }/*blnclr*/




void blankdun(void)
{
 int i,sm,x,y,fp,s;
 char filename[256];
 char fdstr[256];
 x=0;y=0;
 bln1clr();
 sprintf((buffbln[avptr->ach]+13*47),"%3.1f (%%)",avptr->rez[avptr->ach].s);
 sprintf((buffbln[avptr->ach]+14*47),"%3d (ᥪ)",(int)avptr->rez[avptr->ach].t);
 sprintf((buffbln[avptr->ach]+15*47),"%3.2f (%%/ᥪ)",avptr->rez[avptr->ach].v);
 sprintf((buffbln[avptr->ach]+16*47),"%3.2f (%%/ᥪ)",avptr->rez[avptr->ach].vmax);
 while(kbhit()) getch();
 for(sm=0;sm!=27;sm=getch1(0))
	{
	 switch(sm)
		{
		 case 13 : x=0;
		 case 80 : if(y>19) break;y++;break;/*Down*/
		 case 72 : if(y<1) break;y--; break;/*Up*/
		 case 75 : if(x<1) break;x--; break;/*Left*/
		 case 77 : if(x>43) break;x++;break;/*Right*/
		 case 71 : x=0; break;/*Home*/
		 case 79 : x=44;break;/*End*/
		 case 73 : y=0; break;/*PgUp*/
		 case 81 : y=20;break;/*PgDn*/
		 case 83 : for(s=x;s<44;s++)
								{
								 gotoxy(s+32,y+3);
								 if(s!=44) printf("%c",buffbln[avptr->ach][s+1+y*47]);
								 buffbln[avptr->ach][s+y*47]=buffbln[avptr->ach][s+1+y*47];
								 gotoxy(s+33,y+3); printf(" ");
								 buffbln[avptr->ach][s+1+y*47]=32;
								}
							 gotoxy(x+32,y+3);break;
		 case 8 :  if(x>0) x--;else break;
							 for(s=x;s<44;s++)
								{
								 gotoxy(s+32,y+3);
								 if(s!=44) printf("%c",buffbln[avptr->ach][s+1+y*47]);
								 buffbln[avptr->ach][s+y*47]=buffbln[avptr->ach][s+1+y*47];
								 gotoxy(s+33,y+3); printf(" ");
								 buffbln[avptr->ach][s+1+y*47]=32;
								}
							 gotoxy(x+32,y+3);break;
		 default :
							 if((sm<32)||(sm>255)||(x>44)) break;
							 if((sm>0x60)&&(sm<0x7B)) sm=sm-0x20;
							 if((sm>0x9F)&&(sm<0xB0)) sm=sm-0x20;
							 if((sm>0xDF)&&(sm<0xF0)) sm=sm-0x50;
							 printf("%c",sm);
							 buffbln[avptr->ach][x+47*y]=sm;
							 if(x<44) x++;
		}
	 gotoxy(x+32,y+3);
	}
 fname(filename,fdstr);
 fp=open(filename,O_CREAT|O_WRONLY|O_BINARY,S_IWRITE|S_IREAD);
 if(fp==-1) {closegraph();printf("file %s not open",filename);exit(0);}
 write(fp,buffbln[avptr->ach],940);
 close(fp);
 fp=open(fdstr,O_CREAT|O_WRONLY|O_BINARY,S_IWRITE|S_IREAD);
 write(fp,avptr,sizeof(*avptr));
 close(fp);
}


void blank(void)
{
 gpi=0;
 saveskreen(0);
 blankdrow();
 blankdun();
 saveskreen(1);
 gpi=1;
}



