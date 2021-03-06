#define TIMETW 1             /*timetowait*/
#define LENR 5
#define FON  DARKGRAY        /*�e� �o�a*/
#define FRCOLOR LIGHTGREEN      /*�e� 䨭 pac�e�o�*/
#define CHCOLOR LIGHTGRAY    /*�e� �o�epa �a�a�a*/
#define PTCOLOR MAGENTA        /*�e� c�pe���*/
#define RMCOLOR LIGHTGRAY    /*�e� pa���*/
#define MMCOLOR WHITE        /*�e� �� �e��*/
#define GRCOLOR YELLOW       /*�e� �pa䨪a*/
#define GBCOLOR GREEN        /*�e� �o���ce� �pa䨪a*/
#define OMCOLOR WHITE    /*�e� �o�o��x �e��*/
#define ALCOLOR YELLOW           /*�e� �pe�y�pe��e���*/
#define ATCOLOR YELLOW           /*�e� �pe�y�pe��e���*/
#define HCOLOR 7             /*�e� x���a*/
#define MOUSEV 0xFEDE
#define CCANC  0xFEFE
#define ADC 0x130  /*201/130analog digital convertor  A��*/
#define DBC 0x131  /*port b control*/
#define CTL 0x132  /*control p�����p �p�������*/
#define PA 0x134  /**/
#define PB 0x135  /**/
#define PC 0x136  /**/
#define LBK 2.043  /*�����륭� ���室� �� �����쪮�� ��䨪� � ����讬�(7.857/5.0)*/
#define BGL 5.785             /*big graf level lbk=7.857/5.0  bgl=8.143   bgl=5.785*/
#define DPIXCOEF 0.3
char loadfnvar(void);
void savfnvar(void);
void savbvar(void);
char loadbvar(void);

void aae(void);
void ake(void);
void aad(void);
void akd(void);
void culon(void);
void culoff(void);
void imnk(int);
void delms(int);
void vproc(int);     /*���� �����쪨� ��䨪�  */
void process(void);  /*����᪠�� vproc*/
void rmkl(void);
void saveskreen(int);
void help(void);
void blank(void);
void crdr(int,float);
void mainm(void);
void inblok(int,int,int);
void instald(void);
void palletini(int);
int mproc(int);
void mainh(int);
void chnset(void);
void speedset(void);
int pppset(void);
int prpset(void);
void adcpr(int,int);
void adcppp(void);
void intext(int);      /*���⠫���� ���᪨� ����  !!!!!EGA-MDA!!!!!  */
void adcget(void);
int kadcget(void);
void grmene(int);
void ifkb(void);
void prmscr(int);
void koefset(void);
void gbred(int);
void gredm(void);
void sproc(int);
int getch1(int);
int getch2(int);

void dam(void); /*DisAble Mouse*/
void eam(void); /*EnAble Mouse*/
int getme(void); /*1 kogda event*/
int mousecheck(void);
void mouseinit(void);
char newtc(int);
void termo(int);
void ktermo(int);
void blnclr(void);
extern void far MIX_ON(void);
extern void far MIX_OFF(void);
extern unsigned char DRB;
extern int delcl;
extern int cl0;      /*䮭  MDA - 0      EGA - 0*/
extern int cl1;     /*梥� MDA - 1      EGA - 15*/
extern int gpi;
extern int x0;   /*  ᤢ�� �� � ���न��� EGA - 0    MDA - 50*/
extern int      dly;
extern float gvs;  /* ࠧ��� �� ���⨪��� �����쪮�� ��䨪� */
extern int tgr0; /* ���祭�� ⥬��p���p� ��⠭��� � ��*/
extern int mprm;
extern int tc0;  /* ���祭�� ॣ���� ⥬��p���p� */
extern int chpar[4][2];
/* chpar - ��ࠬ���� �ᨫ���� � ����ﭭ�� ��⠢���饩 ������� */
extern unsigned char adccop;
extern unsigned char dbccop;
extern unsigned char pacop;
extern unsigned char pbcop;
extern unsigned char pccop;
extern unsigned char ctlcop;  /* ������ ���窨-���窨 */
extern char buffbln[4][940];
extern int speed;            /*᪮����*/
extern int egmd;
extern int v2;
extern int tkor;
extern int tmd;
extern int rdy;
extern int rdyb;
extern int kgplus;
extern int hynday;
extern char chn[4];    /*�����  ff-��� ;0-�몫*/
extern char flproc[5];  /*�����  ff-��� ;0-�� ���*/
extern float tcross[256];
extern unsigned char light[5];
extern unsigned int KD;
extern int mouse;
extern int mast;

struct msevent
 {
	int ev;
	int x,y;
	int bts;
	int btsr;
	int btsm;
 };

extern struct msevent mse;

struct allvar{
 float told;
 char gbuf[4][480];  /*���p �p�䨪�� ������� l=480  r=5.0*DLY*/
 struct prmt{float p;int t;int ppp;int prp;int ppl;int prl;}prmk[4];  /*������� ��ࠬ����*/
 int pixx[4][4];
 /*X-����� pixx[����p ������][0-A 1-B 2-C 3-D]*/
 int flpr; /*���� ��� ������ �� ��p��*/
 char vs;   /*��६����� ���� (�����-� 䫠���)*/
 int fxl; /*䫠� �뢮�� prmk �� ��p��*/
 int invflag;  /* 䫠� ������ ��p��� ��� �������� ���� */
 int activpix[4]; /* �窨 a b c d*/
 char treatflag;
 int ach; /* ����� */
 int adclen[4];             /* ������ �p��� ��p���樨 �� ������� */
 int fun;/*䫠� ungetch*/
 struct rezt{float v;float vmax;float t;float s;}rez[4];  /*������� १�����*/
 int apprx;
 long double funkoef[8];
 int tt[16];
 int tcnt;
 char flagprm;
};
 extern struct allvar wrkav;
 extern struct allvar savav;
 extern struct allvar *avptr;