#include <io.h>
#include <graphics.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys\stat.h>
#include "agreg.h"

void getfname(char *fdstr)
{
 int g,c;
 char sb[3]={0,95,0};
 char rd[80];
 char filn[30]="";
 c=0;
 setviewport(10+x0,dly*23,629+x0,dly*24-1,1);
 clearviewport();
 setviewport(0,0,639+x0,dly*25-3,1);
 setcolor(LIGHTRED);
 outtextxy(10+x0,dly*23,"Введите имя файла :");
 setcolor(YELLOW);
 outtextxy(162+x0,dly*23,"_");
 for(g=0;g!=13;g=getch())
        {
         if(( ((g>47)&&(g<58))||((g>64)&&(g<91))||((g>96)&&(g<123)) )&&(c<15))
                {
                 sb[0]=g;
                 setviewport(10+x0+(c+19)*8,dly*23,10+x0+(c+20)*8,dly*24-1,1);
                 clearviewport();
                 setviewport(0,0,639+x0,dly*25-3,1);
                 outtextxy(10+x0+(19+c)*8,dly*23,sb);
                 filn[c]=g;
                 c++;
                }
         if((g==8)&&(c>0))
                {
                 c--;
                 filn[c]=0;
                 setviewport(10+x0+(c+19)*8,dly*23,10+x0+(c+21)*8,dly*24-1,1);
                 clearviewport();
                 setviewport(0,0,639+x0,dly*25-3,1);
                 outtextxy(10+x0+(19+c)*8,dly*23,"_");
                }
        }
 getcwd(rd,80);
 sprintf(fdstr,"%s\\SAVBVAR\\%s.var",rd,filn);
 setviewport(10+x0,dly*23,629+x0,dly*24-1,1);
 clearviewport();
 setviewport(0,0,639+x0,dly*25-3,1);
}

void savfnvar(void)
{
 int fp;
 char fdstr[100];
 getfname(fdstr);
 fp=open(fdstr,O_CREAT|O_RDWR|O_BINARY,S_IWRITE|S_IREAD);
 write(fp,avptr,sizeof(*avptr));
 close(fp);
}


char loadfnvar(void)
{
 int fp;
 char fdstr[100];
 getfname(fdstr);
 fp=open(fdstr,O_RDONLY|O_BINARY,S_IWRITE|S_IREAD);
				if(fp==-1)
					{
            setviewport(10+x0,dly*23,629+x0,dly*24-1,1);
						clearviewport();
						setviewport(0,0,639+x0,dly*25-3,1);
						setcolor(LIGHTRED);
						outtextxy(10+x0,dly*23,"Не могу найти файл с таким именем.");
						sleep(1);
						return(27);
					}
 avptr=&savav;
 read(fp,avptr,sizeof(*avptr));
 close(fp);
 grmene(0);
 avptr=&wrkav;
 return(0);
}





void savbvar(void)
{
 int fp;
 fp=open("AGRVAR.BIN",O_CREAT|O_RDWR|O_BINARY,S_IWRITE|S_IREAD);
 write(fp,avptr,sizeof(*avptr));
 close(fp);
}


char loadbvar(void)
{
 int fp;
 fp=open("AGRVAR.BIN",O_RDONLY|O_BINARY,S_IWRITE|S_IREAD);
	if(fp==-1) return(27);
 avptr=&savav;
 read(fp,avptr,sizeof(*avptr));
 close(fp);
 grmene(0);
 avptr=&wrkav;
 return(0);
}
