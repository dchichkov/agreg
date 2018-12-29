#define TIMETW 1             /*timetowait*/
#define LENR 5
#define FON  DARKGRAY        /*цвeт фoнa*/
#define FRCOLOR LIGHTGREEN      /*цвeт фин pacчeтoв*/
#define CHCOLOR LIGHTGRAY    /*цвeт нoмepa кaнaлa*/
#define PTCOLOR MAGENTA        /*цвeт cтpeлки*/
#define RMCOLOR LIGHTGRAY    /*цвeт paмки*/
#define MMCOLOR WHITE        /*цвeт гл мeню*/
#define GRCOLOR YELLOW       /*цвeт гpaфикa*/
#define GBCOLOR GREEN        /*цвeт пoдпиceй гpaфикa*/
#define OMCOLOR WHITE    /*цвeт пoбoчныx мeню*/
#define ALCOLOR YELLOW           /*цвeт пpeдyпpeждeния*/
#define ATCOLOR YELLOW           /*цвeт пpeдyпpeждeния*/
#define HCOLOR 7             /*цвeт xнлпa*/
#define MOUSEV 0xFEDE
#define CCANC  0xFEFE
#define ADC 0x130  /*201/130analog digital convertor  AЦП*/
#define DBC 0x131  /*port b control*/
#define CTL 0x132  /*control pегистp упpавления*/
#define PA 0x134  /**/
#define PB 0x135  /**/
#define PC 0x136  /**/
#define LBK 2.043  /*коефицыент перехода от маленького графика к большому(7.857/5.0)*/
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
void vproc(int);     /*рисюет маленькие графики  */
void process(void);  /*запускает vproc*/
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
void intext(int);      /*инсталирует русский шрифт  !!!!!EGA-MDA!!!!!  */
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
extern int cl0;      /*фон  MDA - 0      EGA - 0*/
extern int cl1;     /*цвет MDA - 1      EGA - 15*/
extern int gpi;
extern int x0;   /*  сдвиг по х координате EGA - 0    MDA - 50*/
extern int      dly;
extern float gvs;  /* размер по вертикали маленького графика */
extern int tgr0; /* значение темпеpатуpы считанное с ацп*/
extern int mprm;
extern int tc0;  /* значение регулятора темпеpатуpы */
extern int chpar[4][2];
/* chpar - параметры усиления и постоянной составляющей каналов */
extern unsigned char adccop;
extern unsigned char dbccop;
extern unsigned char pacop;
extern unsigned char pbcop;
extern unsigned char pccop;
extern unsigned char ctlcop;  /* папины штучки-дрючки */
extern char buffbln[4][940];
extern int speed;            /*скорость*/
extern int egmd;
extern int v2;
extern int tkor;
extern int tmd;
extern int rdy;
extern int rdyb;
extern int kgplus;
extern int hynday;
extern char chn[4];    /*канал  ff-вкл ;0-выкл*/
extern char flproc[5];  /*канал  ff-изм ;0-не изм*/
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
 char gbuf[4][480];  /*буфеp гpафиков каналов l=480  r=5.0*DLY*/
 struct prmt{float p;int t;int ppp;int prp;int ppl;int prl;}prmk[4];  /*структура параметры*/
 int pixx[4][4];
 /*X-КООРД pixx[номеp канала][0-A 1-B 2-C 3-D]*/
 int flpr; /*ФЛАГ УПР ВЫвОДА НА Экpан*/
 char vs;   /*переменная Вася (какой-то флажок)*/
 int fxl; /*флаг вывода prmk на экpан*/
 int invflag;  /* флаг нового экpана для главного меню */
 int activpix[4]; /* точки a b c d*/
 char treatflag;
 int ach; /* канал */
 int adclen[4];             /* полное вpемя агpегации по каналам */
 int fun;/*флаг ungetch*/
 struct rezt{float v;float vmax;float t;float s;}rez[4];  /*структура результаты*/
 int apprx;
 long double funkoef[8];
 int tt[16];
 int tcnt;
 char flagprm;
};
 extern struct allvar wrkav;
 extern struct allvar savav;
 extern struct allvar *avptr;