/*********************************************************/
/*                      bp1.c                            */
/*           ���ڷ��򴫲����������ѧϰ                */
/* ʹ�÷���                                              */
/*  \Users\odaka\dl\ch4>bp1 < data.txt > result.txt      */
/*  ������ı仯����Ϊѧϰ���������ϵ����             */
/*********************************************************/

/*Visual Studio�Ļ����Ա�֤ */
#define _CRT_SECURE_NO_WARNINGS

/* Includeͷ�ļ�*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


/*���ų����Ķ���*/
#define INPUTNO 3  /*�������Ԫ��*/ 
#define HIDDENNO 3  /*�м����Ԫ��*/ 
#define ALPHA  10  /*ѧϰϵ��*/ 
#define SEED 65535    /*���������*/ 
#define MAXINPUTNO 100    /*ѧϰ���ݵ�������*/ 
#define BIGNUM 100    /*���ĳ�ʼֵ*/ 
#define LIMIT 0.001    /*��������ֵ*/ 

/*����ԭ������*/
double f(double u) ; /*���ݺ�����sigmoid������*/
void initwh(double wh[HIDDENNO][INPUTNO+1]) ;
                         /*�м��Ȩ�صĳ�ʼ��*/
void initwo(double wo[HIDDENNO+1]) ;/*�����Ȩ�صĳ�ʼ��*/
double drnd(void) ;/* ���������     */
void print(double wh[HIDDENNO][INPUTNO+1]
          ,double wo[HIDDENNO+1]) ; /*������*/
double forward(double wh[HIDDENNO][INPUTNO+1]
         ,double wo[HIDDENNO+1],double hi[]
         ,double e[INPUTNO+1]) ; /*ǰ�����*/
void olearn(double wo[HIDDENNO+1],double hi[]
         ,double e[INPUTNO+1],double o) ; /*�����Ȩ�صĵ���*/
int getdata(double e[][INPUTNO+1]) ; /*����ѧϰ����*/
void hlearn(double wh[HIDDENNO][INPUTNO+1]
         ,double wo[HIDDENNO+1],double hi[]
         ,double e[INPUTNO+1],double o) ; /*�м��Ȩ�صĵ���*/

/*******************/ 
/*    main()����   */ 
/*******************/ 
int main()
{
 double wh[HIDDENNO][INPUTNO+1] ;/*�м���Ȩ��*/
 double wo[HIDDENNO+1] ;/*������Ȩ��*/
 double e[MAXINPUTNO][INPUTNO+1] ;/*ѧϰ���ݼ�*/
 double hi[HIDDENNO+1] ;/*�м������*/
 double o ;/*���*/
 double err=BIGNUM ;/*��������*/
 int i,j ;/*ѭ������*/
 int n_of_e ;/*ѧϰ���ݵĸ���*/
 int count=0 ;/*ѭ�������ļ���*/

 /*������ĳ�ʼ��*/
 srand(SEED) ;

 /*Ȩ�صĳ�ʼ��*/
 initwh(wh) ;/*�м��Ȩ�صĳ�ʼ��*/
 initwo(wo) ;/*�����Ȩ�صĳ�ʼ��*/
 print(wh,wo) ; /*��������*/

 /*����ѧϰ����*/
 n_of_e=getdata(e) ;
 printf("ѧϰ���ݵĸ���:%d\n",n_of_e) ;

 /*ѧϰ*/
 while(err>LIMIT){
  err=0.0 ;
  for(j=0;j<n_of_e;++j){
   /*ǰ�����*/
   o=forward(wh,wo,hi,e[j]) ;
   /*�����Ȩ�صĵ���*/
   olearn(wo,hi,e[j],o) ;
   /*�м��Ȩ�صĵ���*/
   hlearn(wh,wo,hi,e[j],o) ;
   /*�����ۻ�*/
   err+=(o-e[j][INPUTNO])*(o-e[j][INPUTNO]) ;
  }
  ++count ;
  /*�������*/
  fprintf(stderr,"%d\t%lf\n",count,err) ;
 }/*ѧϰ����*/

 /*����Ȩ�ص����*/
 print(wh,wo) ; 

 /*����ѧϰ���ݵ����*/
 for(i=0;i<n_of_e;++i){
  printf("%d ",i) ;
  for(j=0;j<INPUTNO+1;++j)
   printf("%lf ",e[i][j]) ;
  o=forward(wh,wo,hi,e[i]) ;
  printf("%lf\n",o) ;
 }

 return 0 ;
}

/**********************/
/*  hlearn()����      */
/*  �м��Ȩ�ص�ѧϰ  */
/**********************/
void hlearn(double wh[HIDDENNO][INPUTNO+1]
    ,double wo[HIDDENNO+1]
    ,double hi[],double e[INPUTNO+1],double o)
{
 int i,j ;/*ѭ������*/
 double dj ;/*�����м���Ȩ�ؼ���*/

 for(j=0;j<HIDDENNO;++j){/*�м��ĸ���Ԫj��Ϊ����*/
  dj=hi[j]*(1-hi[j])*wo[j]*(e[INPUTNO]-o)*o*(1-o) ;
  for(i=0;i<INPUTNO;++i)/*�����i��Ȩ��*/
   wh[j][i]+=ALPHA*e[i]*dj ;
  wh[j][i]+=ALPHA*(-1.0)*dj ;/*��ֵ��ѧϰ*/
 }
}


/**********************/
/*  getdata()����     */
/*  ����ѧϰ����      */
/**********************/
int getdata(double e[][INPUTNO+1])
{
 int n_of_e=0 ;/*���ݼ��ĸ���*/
 int j=0 ;/*ѭ��������*/

 /*��������*/
 while(scanf("%lf",&e[n_of_e][j])!=EOF){
  ++ j ;
  if(j>INPUTNO){/*��һ������*/
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
    ,double hi[],double e[INPUTNO+1],double o)
{
 int i ;/*ѭ���Ŀ���*/
 double d ;/*����Ȩ�ؼ���*/

 d=(e[INPUTNO]-o)*o*(1-o) ;/*���ļ���*/
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
          ,double wo[HIDDENNO+1])
{
 int i,j ;/*ѭ���Ŀ���*/

 for(i=0;i<HIDDENNO;++i)
  for(j=0;j<INPUTNO+1;++j)
   printf("%lf ",wh[i][j]) ;
 printf("\n") ;
 for(i=0;i<HIDDENNO+1;++i)
  printf("%lf ",wo[i]) ;
 printf("\n") ;
} 

/**********************/
/*    initwh()����    */
/* �м��Ȩ�صĳ�ʼ�� */
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
/*�����Ȩ�صĳ�ʼ��  */
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
 rndno=rndno*2-1 ;/*����-1��1֮��������*/
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



