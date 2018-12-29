#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <float.h>
#include <dos.h>



 long double  st(int  f, int s)
 {
  int aaa;
  long double  bbb=1.0;
  for(aaa=0; aaa<s; aaa++) bbb=bbb*(long double)(f);
  return(bbb);
 } /**/

 void mnk(int xo[],char yo[],int nn,int n,long double a[8][8],long double b[])
 {
 int o;         /* номер отсчета */
 int s;         /* номер строки */
 int c;         /* номер колонки */
  /* вычисления свободных членов */
  for(s=0;s<=n;s++) b[s]=0.0;
  for(s=0;s<=n;s++) for(o=0;o<nn;o++) b[s]=b[s]+st(xo[o],s)*(long double)(yo[o]);
  /* вычисление коеффицентов */
  for(s=0;s<=n;s++) for(c=0;c<=n;c++) a[s][c]=0.0;
  for(s=0;s<=n;s++)
   for(c=0;c<=n;c++)
    for(o=0;o<nn;o++)
     a[s][c]=a[s][c]+st(xo[o],s+c);
  s=0;
 } /*mnk*/


long double  ffabs(long double v)
{ if(v<0.0) v=v*-1.0; return(v); }


void mainelem(int k,int n,long double a[8][8],long double b[])
{
 int l;         /* ном ноибол по абс величине эл-та матрици в столбце к */
 int m;         /* тек ном эл-та с кот происх сравнение */
 int j;
 long double  f;
 m=k+1; l=k;
 lb6:if( ffabs(a[m][k]) > ffabs(a[l][k]) ) {l=m; goto lb7;}
 lb7:if(m<n) {m++; goto lb6;}
 lb8:if(l==k) goto lb10;
 j=k;
 lb9:f=a[k][j]; a[k][j]=a[l][j]; a[l][j]=f;
    if(j<n) {j++; goto lb9;}
 f=b[k]; b[k]=b[l]; b[l]=f;
 lb10:;
}/*mainelem*/

int gauss(long double a[8][8],long double b[],int n,long double x[])
{
 int i;         /* номер ур-нения из которого исключ неизвестное x[k] */
 int j;         /* номер столвца */
 int k;         /* номер неизвестного кот исключ из оставш n-k урнений */
 long double  cc;
 long double  ss;
 k=0;
 lb1:i=k+1;
    mainelem(k,n,a,b);
    if(a[k][k]==0.0) return(-1);
    lb2:cc=a[i][k]/a[k][k];
       a[i][k]=0.0; j=k+1;
       lb3:a[i][j]=a[i][j]-cc*a[k][j];
          if(j<n) {j++; goto lb3;}
       b[i]=b[i]-cc*b[k];
       if(i<n) {i++; goto lb2;}
    if(k<(n-1)) {k++; goto lb1;}
/* back */
 if(a[n][n]==0.0) return(-1);
 x[n]=b[n]/a[n][n];
 i=n-1;
 lb4:j=i+1; ss=0;
    lb5:ss=ss+a[i][j]*x[j];
       if(j<n) {j++; goto lb5;}
    if(a[i][i]==0.0) return(-1);
    x[i]=(b[i]-ss)/a[i][i];
    if(i>0) {i--; goto lb4;}
 return(0);
}/* gauss */


int nok( char  yo[],         /* функция  y-отсчет */
         int nn,             /* к-во отсчетов */
         int n,              /* порядок апроксимации */
         long double  x[]    /* искомые коеффициенты степенной функции */
       )
{
 int i;
 int xo[480];         /* аргумент */
 long double  a[8][8]; /* коеффиценты в системе ур-нений */
 long double  b[8];    /* свободные члены */

 for(i=0; i<480; i++) xo[i]=i;
 if(n>7) return(1);
 mnk(xo,yo,nn,n,a,b);
 if(gauss(a,b,n,x)) return(-1);
 return(0);

}/* nok */