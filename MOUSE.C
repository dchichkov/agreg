#include <dos.h>
#include "agreg.h"

int mousecheck(void)
 {
	 union REGS r;
		if(egmd!=1) return(0);
		r.x.ax=0;
		int86(0x33,&r,&r);
		if(r.x.ax!=0xFFFF)	return(0);
		return(1);
 }

int getme(void)
 {
	union REGS r;
	static int x,y,bts,rt,btsr,btsm;
	 if(mouse&&mast)
		{
		 rt=0;
		 r.x.ax=3;
		 int86(0x33,&r,&r);
		 mse.x=r.x.cx;
		 mse.y=r.x.dx;
		 mse.bts=(r.x.bx)&1;
		 mse.btsm=((r.x.bx)&4)>>2;
		 mse.btsr=((r.x.bx)&2)>>1;
		 if(mse.bts>bts) {mse.ev=1;rt=1;}
		 if(mse.btsr>btsr) {mse.ev=0;rt=1;}
		 if(mse.btsm>btsm) {mse.ev=0;rt=1;}
		 if((x!=mse.x)||(y!=mse.y)) {mse.ev=0;rt=1;}
		 x=mse.x;y=mse.y;bts=mse.bts;btsr=mse.btsr;btsm=mse.btsm;
		 return(rt);
		}
	 return(0);
 }

void mouseinit(void)
 {
	 union REGS r;
		r.x.ax=1;
		int86(0x33,&r,&r);
		mouse=1;
		mast=1;
		getme();
 }

void dam(void)   /*disable mouse*/
 {
	union REGS r;
	 if(mouse&&mast)
		{
		 r.x.ax=2;
		 int86(0x33,&r,&r);
		 mast=0;
	 }
 }

void eam(void)   /*enable mouse*/
 {
	union REGS r;
	 if(mouse&&(!mast))
		{
		 r.x.ax=1;
		 int86(0x33,&r,&r);
		 mast=1;
	 }
 }
