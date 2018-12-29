#include <io.h>
#include <fcntl.h>
#include <sys\stat.h>
#include <alloc.h>
#include <stdio.h>
main(int argc,char **argv)
{
 char *bufer;
 char m[]={13,10,0};
 char bff[100];
 int fp,d;
 long fl,c;
 if(argc<3)
	 {
		printf("\nftrans (filein) (\\f or \\b) [fileout]");
		printf("\n\\f text->pic");
		printf("\n\\b pic->text");
	 }
 fp=open(argv[1],O_RDWR|O_BINARY,S_IREAD|S_IWRITE);
 fl=filelength(fp)-2;
 bufer=malloc(fl);
 read(fp,bufer,fl);
 close(fp);
 if(argc>3) fp=open(argv[3],O_CREAT|O_WRONLY|O_BINARY,S_IREAD|S_IWRITE);
 else fp=open("orges.bln",O_CREAT|O_WRONLY|O_BINARY,S_IREAD|S_IWRITE);
 if(argv[2][1]==102)
	{
	 for(c=0;c<fl;c++)
	 if((bufer[c]!=13)&&(bufer[c]!=10)) write(fp,&bufer[c],1);
	}
 if(argv[2][1]==98)
	{
	 for(c=0;c<fl-80;c+=80)
	 {write(fp,&(bufer[c]),80);write(fp,m,2);}
	 write(fp,&(bufer[c]),fl-c);
	}
 close(fp);
}