#include <io.h>
#include <conio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <dir.h>
#include <dos.h>
#include <process.h>
#include <sys\stat.h>
/*********************/



void main(void)
 {
	char *path;
	int f,i;
	char sc[100];
	char filename[200];
	long dat1,dat2;
	struct ffblk fff;
	struct date dait;
	path=getcwd(NULL,132);
	i=0;
	 do
		{
		 sprintf(filename,"%s\\DATA\\%d.dat",path,i);
		 f=findfirst(filename,&fff,FA_ARCH);
		 i++;
		}
	 while(f==0);
	if(i>500)
	 {
		i=0;
		do
		 {
			sprintf(filename,"%s\\DATA%d",path,i);
			f=findfirst(filename,&fff,FA_DIREC);
			i++;
		 }
		while(f==0);
		i--;
		sprintf(filename,"%s\\DATA",path);
		f=findfirst(filename,&fff,FA_DIREC);
		dat1=(((fff.ff_fdate&0xF800)>>9)+0x7BC)*1000+((fff.ff_fdate&0x1e0)>>5)*100+(fff.ff_fdate&0x1f);
		do
		 {
			printf("\nВведите дату\n");
			system("date");
			getdate(&dait);
			dat2=dait.da_year*1000+dait.da_mon*100+dait.da_day;
			if(dat2<=dat1) printf("\nВведенная вами дата более ранняя чем передидущяя!");
		 }while((dat2<dat1)||(dat2==dat1));
		sprintf(sc,"REN DATA DATA%d",i);
		system(sc);
		sprintf(sc,"mkdir DATA");
		system(sc);
		sprintf(sc,"REN DATA.GRF DATA%d.GRF",i);
		system(sc);
		sprintf(sc,"mkdir DATA.GRF");
		system(sc);
	 }
	free(path);
 }

