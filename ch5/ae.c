/*********************************************************/
/*                      ae.c                             */
/*�Ա�����                                               */
/* ʹ�÷���                                              */
/*  \Users\odaka\dl\ch5>ae < data.txt                    */
/*������ı仯����Ϊѧϰ���������ϵ����               */
/*********************************************************/

/*Visual Studio�����Ա�֤ */
#define _CRT_SECURE_NO_WARNINGS

/* Includeͷ�ļ�*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


/*���ų����Ķ���*/
#define INPUTNO 9  /*��������Ԫ��*/ 
#define HIDDENNO 2  /*�м�����Ԫ��*/ 
#define OUTPUTNO 9  /*��������Ԫ��*/
#define ALPHA  10  /*ѧϰϵ��*/ 
#define SEED 65535    /*�����������*/ 
#define MAXINPUTNO 100    /*ѧϰ���ݵ�������*/ 
#define BIGNUM 100    /*���ĳ�ʼֵ*/ 
#define LIMIT 0.0001   /*��������ֵ*/ 

/*����ԭ������*/
double f(double u) ; /*���ݺ�����sigmoid������*/
void initwh(double wh[HIDDENNO][INPUTNO+1]) ;
                         /*�м��Ȩ�صĳ�ʼ��*/
void initwo(double wo[HIDDENNO+1]) ;/*�����Ȩ�صĳ�ʼ��*/
double drnd(void) ;/* �����������     */
void print(double wh[HIDDENNO][INPUTNO+1]
          ,double wo[OUTPUTNO][HIDDENNO+1]) ; /*��������*/
double forward(double wh[HIDDENNO][INPUTNO+1]
         ,double wo[HIDDENNO+1],double hi[]
         ,double e[]) ; /*ǰ�����*/
void olearn(double wo[HIDDENNO+1],double hi[]
         ,double e[],double o,int k) ; /*�����Ȩ�صĵ���*/
int getdata(double e[][INPUTNO+OUTPUTNO]) ; /*����ѧϰ����*/
void hlearn(double wh[HIDDENNO][INPUTNO+1]
         ,double wo[HIDDENNO+1],double hi[]
         ,double e[],double o,int k) ; /*�м��Ȩ�صĵ���*/

/*******************/ 
/*    main()����   */ 
/*******************/ 
int main()
{
 double wh[HIDDENNO][INPUTNO+1] ;/*�м���Ȩ��*/
 double wo[OUTPUTNO][HIDDENNO+1] ;/*������Ȩ��*/
 double e[MAXINPUTNO][INPUTNO+OUTPUTNO] ;/*ѧϰ���ݼ�*/
 double hi[HIDDENNO+1] ;/*�м������*/
 double o[OUTPUTNO] ;/*���*/
 double err=BIGNUM ;/*��������*/
 int i,j,k ;/*ѭ���Ŀ���*/
 int n_of_e ;/*ѧϰ���ݵĸ���*/
 int count=0 ;/*ѭ�������ļ���*/

 /*������ĳ�ʼ��*/
 srand(SEED) ;

 /*Ȩ�صĳ�ʼ��*/
 initwh(wh) ;/*�м��Ȩ�صĳ�ʼ��*/
 for(i=0;i<OUTPUTNO;++i)
  initwo(wo[i]) ; /*�����Ȩ�صĳ�ʼ��*/
 print(wh,wo) ; /*��������*/

 /*����ѧϰ����*/
 n_of_e=getdata(e) ;
 printf("ѧϰ���ݵĸ���:%d\n",n_of_e) ;

 /*ѧϰ*/
 while(err>LIMIT){
  /*�������������Ԫ*/
  for(k=0;k<OUTPUTNO;++k){
   err=0.0 ;
   for(j=0;j<n_of_e;++j){
    /*ǰ�����*/
    o[k]=forward(wh,wo[k],hi,e[j]) ;
    /*�����Ȩ�صĵ���*/
    olearn(wo[k],hi,e[j],o[k],k) ;
    /*�м��Ȩ�صĵ���*/
    hlearn(wh,wo[k],hi,e[j],o[k],k) ;
    /*�����ۻ�*/
    err+=(o[k]-e[j][INPUTNO+k])*(o[k]-e[j][INPUTNO+k]) ;
   }
   ++count ;
   /*�������*/
   fprintf(stderr,"%d\t%lf\n",count,err) ;
   /*����������Ԫ�Ķ�Ӧ���ֽ���*/
  }
 }/*ѧϰ����*/

 /*�������Ȩ��*/
 print(wh,wo) ; 

 /*�������ѧϰ���ݵļ�����*/
 for(i=0;i<n_of_e;++i){
  printf("%d ",i) ;
  for(j=0;j<INPUTNO+OUTPUTNO;++j)
   printf("%.3lf ",e[i][j]) ;
  printf("\t") ;
  for(j=0;j<OUTPUTNO;++j)
   printf("%.3lf ",forward(wh,wo[j],hi,e[i])) ;
  printf("\n") ;
 }

 return 0 ;
}

/**********************/
/*  hlearn()����      */
/*  �м��Ȩ�ص�ѧϰ  */
/**********************/
void hlearn(double wh[HIDDENNO][INPUTNO+1]
    ,double wo[HIDDENNO+1]
    ,double hi[],double e[],double o,int k)
{
 int i,j ;/*ѭ���Ŀ���*/
 double dj ;/*�����м���Ȩ�ؼ���*/

 for(j=0;j<HIDDENNO;++j){/*���м�����ԪjΪ����*/
  dj=hi[j]*(1-hi[j])*wo[j]*(e[INPUTNO+k]-o)*o*(1-o) ;
  for(i=0;i<INPUTNO;++i)/*�����i��Ȩ��*/
   wh[j][i]+=ALPHA*e[i]*dj ;
  wh[j][i]+=ALPHA*(-1.0)*dj ;/*��ֵ��ѧϰ*/
 }
}


/**********************/
/*  getdata()����     */
/*����ѧϰ����        */
/**********************/
int getdata(double e[][INPUTNO+OUTPUTNO])
{
 int n_of_e=0 ;/*���ݼ��ĸ���*/
 int j=0 ;/*ѭ���Ŀ�����*/

 /*���ݵ�����*/
 while(scanf("%lf",&e[n_of_e][j])!=EOF){
  ++ j ;
  if(j>=INPUTNO+OUTPUTNO){/*��һ������*/
   j=0 ;
   ++n_of_e ;
  }
 }

 return n_of_e ;
}

/**********************/
/*  olearn()����      */
/*  ������Ȩ��ѧϰ  */
/**********************/
void olearn(double wo[HIDDENNO+1]
    ,double hi[],double e[INPUTNO+1],double o,int k)
{
 int i ;/*ѭ���Ŀ���*/
 double d ;/*����Ȩ�ؼ���*/

 d=(e[INPUTNO+k]-o)*o*(1-o) ;/*���ļ���*/
 for(i=0;i<HIDDENNO;++i){
  wo[i]+=ALPHA*hi[i]*d ;/*Ȩ�ص�ѧϰ*/
 }
 wo[i]+=ALPHA*(-1.0)*d ;/*��ֵ��ѧϰ*/
 
} 


/**********************/
/*  forward()����     */
/*  ǰ�����          */
/**********************/
double forward(double wh[HIDDENNO][INPUTNO+1]
 ,double wo[HIDDENNO+1],double hi[],double e[INPUTNO+1])
{
 int i,j ;/*ѭ���Ŀ���*/
 double u ;/*��Ȩ�͵ļ���*/
 double o ;/*����ļ���*/

 /*hi�ļ���*/
 for(i=0;i<HIDDENNO;++i){
  u=0 ;/*��ȡ��Ȩ��*/
  for(j=0;j<INPUTNO;++j)
   u+=e[j]*wh[i][j] ; 
  u-=wh[i][j] ;/*��ֵ�Ĵ���*/
  hi[i]=f(u) ;
 }
 /*���o�ļ���*/
 o=0 ;
 for(i=0;i<HIDDENNO;++i)
  o+=hi[i]*wo[i] ;
 o-=wo[i] ;/*��ֵ�Ĵ���*/
 
 return f(o) ;
} 

/**********************/
/*   print()����      */
/*   ��������       */
/**********************/
void print(double wh[HIDDENNO][INPUTNO+1]
          ,double wo[OUTPUTNO][HIDDENNO+1])
{
 int i,j ;/*ѭ���Ŀ���*/

 for(i=0;i<HIDDENNO;++i){
  for(j=0;j<INPUTNO+1;++j)
   printf("%.3lf ",wh[i][j]) ;
  printf("\n") ;
 } 
 printf("\n") ;
 for(i=0;i<OUTPUTNO;++i){
  for(j=0;j<HIDDENNO+1;++j)
   printf("%.3lf ",wo[i][j]) ;
  printf("\n") ;
 }
 printf("\n") ;
} 

/**********************/
/*    initwh()����    */
/*�м��Ȩ�صĳ�ʼ��  */
/**********************/
void initwh(double wh[HIDDENNO][INPUTNO+1])
{
 int i,j ;/*ѭ���Ŀ���*/

 /*���������ȷ��Ȩ��*/ 
 for(i=0;i<HIDDENNO;++i)
  for(j=0;j<INPUTNO+1;++j)
   wh[i][j]=drnd() ;
} 

/**********************/
/*    initwo()����    */
/*�����Ȩ�صĳ�ʼ��*/
/**********************/
void initwo(double wo[HIDDENNO+1])
{
 int i ;/*ѭ���Ŀ���*/

 /*���������ȷ��Ȩ��*/
 for(i=0;i<HIDDENNO+1;++i)
   wo[i]=drnd() ;
} 

/*******************/
/* drnd()����      */
/* ���������      */
/*******************/
double drnd(void)
{
 double rndno ;/*���ɵ������*/

 while((rndno=(double)rand()/RAND_MAX)==1.0) ;
 rndno=rndno*2-1 ;/*����-1��1��������*/
 return rndno; 
}

/*******************/
/* f()����         */
/* ���ݺ���        */
/*(sigmoid����)    */
/*******************/
double f(double u)
{
 return 1.0/(1.0+exp(-u)) ;
}



