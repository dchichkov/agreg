#include <graphics.h>
#include <stdlib.h>
#include <dos.h>
#include <stdio.h>
#include <fcntl.h>
#include "agreg.h"

void instald(void)
{
 int a,c,k,prm2;
 char str[32];
 FILE *fp;
 outportb(0x133,0x90); /* �-���� �,�-�뢮� */
 fp=fopen("agreg.dat","rb");
 for(c=0;c<4;c++) for(k=0;k<2;k++) fscanf(fp,"%d%s",&(chpar[c][k]),str);
 fscanf(fp,"%d%s",&tkor,str);
 fscanf(fp,"%d%s",&tmd,str);
 fscanf(fp,"%d%s",&rdy,str);
 fscanf(fp,"%d%s",&rdyb,str);
 fscanf(fp,"%d%s",&egmd,str);
 fscanf(fp,"%d%s",&v2,str);
 fscanf(fp,"%d%s",&kgplus,str);
 fscanf(fp,"%d%s",&delcl,str);
 fscanf(fp,"%d%s",&hynday,str);
 fscanf(fp,"%d%s",&mprm,str);
 fclose(fp);
 if(v2)
 {ctlcop=0xf8|4;outportb(CTL,ctlcop);dbccop=0xc7; outportb(DBC,7); }
 else
 {ctlcop=0xf8|4;outportb(CTL,ctlcop);dbccop=(speed/100-3);
	dbccop=dbccop|0xc0;
	outportb(DBC,0xf); delms(2000); outportb(DBC,dbccop);
 }
 aae();
 if(kgplus==1)
 {outportb(0x137,0x90); /* �-���� �,�-�뢮� */
	outportb(pbcop,PB);
	outportb(pccop,PC);
 }
} /**/

void intext(int fl) /*�� ����ᠭ�� �⮩ �p�楤�p� ���� ����稫
               ������ ����p� ����*/
{
 struct adaress { char far *p; }temp;
 struct adaress far *addr=(struct adaress far *)124;
 if(fl>0) addr->p-=1024;
 if(fl==0) addr->p+=1024;
} /**/


void hardoff(void)
{
 if(v2) outportb(DBC,0xff); else outportb(DBC,0);
 outportb(CTL,4|8);
 outportb(PB,0);
 outportb(PC,0);
 aad(); akd(); culoff();
}
