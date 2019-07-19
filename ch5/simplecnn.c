/*********************************************************/
/*               simplecnn.c                             */
/*      ���������Ļ����ṹ��ʾ                       */
/* ��ʾCNN�Ļ����ṹ������ʾ��Ǽܣ�                     */
/* ʹ�÷���                                              */
/*  \Users\odaka\dl\ch5>simplecnn < data1.txt            */
/*********************************************************/

/*Visual Studio�����Ա�֤ */
#define _CRT_SECURE_NO_WARNINGS

/* Includeͷ�ļ�*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*���ų����Ķ���*/
#define INPUTSIZE 11  /*������*/ 
#define FILTERSIZE 3 /*�˲����Ĵ�С*/
#define FILTERNO 2 /*�˲����ĸ���*/
#define POOLSIZE 3 /*�ػ��Ĵ�С*/
#define POOLOUTSIZE 3/*�ػ�����Ĵ�С*/
#define MAXINPUTNO 100    /*ѧϰ���ݵ�������*/ 
#define SEED 65535    /*�����������*/ 
#define LIMIT 0.001    /*��������ֵ*/ 
#define BIGNUM 100    /*���ĳ�ʼֵ*/ 
#define HIDDENNO 3  /*�м����Ԫ����*/ 
#define ALPHA  10  /*ѧϰϵ��*/ 

/*����ԭ�͵�����*/
void conv(double filter[FILTERSIZE][FILTERSIZE]
   ,double e[][INPUTSIZE]
   ,double convout[][INPUTSIZE]) ; /*�������*/
double calcconv(double filter[][FILTERSIZE]
               ,double e[][INPUTSIZE],int i,int j) ;
                               /*  �˲�����Ӧ��  */
void pool(double convout[][INPUTSIZE]
         ,double poolout[][POOLOUTSIZE]) ; 
             /*�ػ�����*/           
double maxpooling(double convout[][INPUTSIZE]
                 ,int i,int j) ;/* ���ֵ�ػ� */
int getdata(double e[][INPUTSIZE][INPUTSIZE],int r[]) ;/*��������*/ 
void showdata(double e[][INPUTSIZE][INPUTSIZE],int t[]
             ,int n_of_e) ;/*���ݱ�ʾ*/ 
void initfilter(double filter[FILTERNO][FILTERSIZE][FILTERSIZE]) ;
                /*�˲����ĳ�ʼ��*/
double drnd(void) ;/* �����������     */
double f(double u) ; /*���ݺ�����sigmoid������*/
void initwh(double wh[HIDDENNO][POOLOUTSIZE*POOLOUTSIZE*FILTERNO+1]) ;
                         /*�м��Ȩ�صĳ�ʼ��*/
void initwo(double wo[HIDDENNO+1]) ;/*�����Ȩ�صĳ�ʼ��*/
double forward(double wh[HIDDENNO][POOLOUTSIZE*POOLOUTSIZE*FILTERNO+1]
         ,double wo[HIDDENNO+1],double hi[]
         ,double e[POOLOUTSIZE*POOLOUTSIZE*FILTERNO+1]) ; /*ǰ�����*/
void olearn(double wo[HIDDENNO+1],double hi[]
         ,double e[POOLOUTSIZE*POOLOUTSIZE*FILTERNO+1],double o) ; /*�����Ȩ�صĵ���*/
void hlearn(double wh[HIDDENNO][POOLOUTSIZE*POOLOUTSIZE*FILTERNO+1]
         ,double wo[HIDDENNO+1],double hi[]
         ,double e[POOLOUTSIZE*POOLOUTSIZE*FILTERNO+1],double o) ; /*�м��Ȩ�صĵ���*/
double f(double u) ; /*���ݺ�����sigmoid������*/
void print(double wh[HIDDENNO][POOLOUTSIZE*POOLOUTSIZE*FILTERNO+1]
          ,double wo[HIDDENNO+1]) ; /*��������*/
          
/*******************/ 
/*    main()����   */ 
/*******************/ 
int main()
{
 double filter[FILTERNO][FILTERSIZE][FILTERSIZE] ;
                            /*�˲���*/
 double e[MAXINPUTNO][INPUTSIZE][INPUTSIZE] ;/*��������*/
 int t[MAXINPUTNO] ;/*��ʦ����*/
 double convout[INPUTSIZE][INPUTSIZE]={0} ;/*������*/
 double poolout[POOLOUTSIZE][POOLOUTSIZE] ;/*�������*/
 int i,j,m,n ;/*ѭ���Ŀ���*/
 int n_of_e ;/*ѧϰ���ݵĸ���*/
 double err=BIGNUM ;/*��������*/
 int count=0 ;/*ѭ�������ļ���*/
 double ef[POOLOUTSIZE*POOLOUTSIZE*FILTERNO+1] ;/*ȫ���Ӳ����������*/
 double o ;/*�������*/
 double hi[HIDDENNO+1] ;/*�м������*/
 double wh[HIDDENNO][POOLOUTSIZE*POOLOUTSIZE*FILTERNO+1] ;/*�м���Ȩ��*/
 double wo[HIDDENNO+1] ;/*������Ȩ��*/
 
 /*������ĳ�ʼ��*/
 srand(SEED) ;
 
 /*�˲����ĳ�ʼ��*/
 initfilter(filter) ;
 
 /*ȫ���Ӳ�Ȩ�صĳ�ʼ��*/
 initwh(wh) ;/*�м��Ȩ�صĳ�ʼ��*/
 initwo(wo) ;/*�����Ȩ�صĳ�ʼ��*/
 
 /*������������*/
 n_of_e=getdata(e,t) ;
 showdata(e,t,n_of_e) ;
 
  /*ѧϰ*/
 while(err>LIMIT){
  err=0.0 ;
  for(i=0;i<n_of_e;++i){/*ѧϰ���ݵ�ѭ��*/
   for(j=0;j<FILTERNO;++j){/*�˲�����ѭ��*/
    /*�������*/
    conv(filter[j],e[i],convout) ;
    /*�ػ�����*/
    pool(convout,poolout) ;
    /*���ػ�������Ƶ�ȫ���Ӳ������*/
    for(m=0;m<POOLOUTSIZE;++m)
     for(n=0;n<POOLOUTSIZE;++n)
      ef[j*POOLOUTSIZE*POOLOUTSIZE+POOLOUTSIZE*m+n]
           =poolout[m][n] ;
    ef[POOLOUTSIZE*POOLOUTSIZE*FILTERNO]=t[i] ;/*��ʦ����*/
   }
   /*ǰ�����*/
   o=forward(wh,wo,hi,ef) ;
   /*�����Ȩ�صĵ���*/
   olearn(wo,hi,ef,o) ;
   /*�м��Ȩ�صĵ���*/
   hlearn(wh,wo,hi,ef,o) ;
   /*�����ۻ�*/
   err+=(o-t[i])*(o-t[i]) ;
  }
  ++count ;
  /*�������*/
  fprintf(stderr,"%d\t%lf\n",count,err) ;
 }/*ѧϰ����*/
 
 printf("\n***Results***\n") ;
 /*����Ȩ�ص����*/
 printf("Weights\n") ;
 print(wh,wo) ; 

 /*����ڽ�ʦ���ݵ����*/
 printf("Network output\n") ;
 printf("#\tteacher\toutput\n") ;
 for(i=0;i<n_of_e;++i){
  printf("%d\t%d\t",i,t[i]) ;
  for(j=0;j<FILTERNO;++j){/*�˲�����ѭ��*/
    /*�������*/
    conv(filter[j],e[i],convout) ;
    /*�ػ�����*/
    pool(convout,poolout) ;
    /*���ػ�������Ƶ�ȫ���Ӳ������*/
    for(m=0;m<POOLOUTSIZE;++m)
     for(n=0;n<POOLOUTSIZE;++n)
      ef[j*POOLOUTSIZE*POOLOUTSIZE+POOLOUTSIZE*m+n]
           =poolout[m][n] ;
    ef[POOLOUTSIZE*POOLOUTSIZE*FILTERNO]=t[i] ;/*��ʦ����*/
   }
   o=forward(wh,wo,hi,ef) ;
  printf("%lf\n",o) ;
 }

 return 0 ;
}

/**********************/
/*   print()����      */
/*   ��������       */
/**********************/
void print(double wh[HIDDENNO][POOLOUTSIZE*POOLOUTSIZE*FILTERNO+1]
          ,double wo[HIDDENNO+1])
{
 int i,j ;/*ѭ���Ŀ���*/

 for(i=0;i<HIDDENNO;++i)
  for(j=0;j<POOLOUTSIZE*POOLOUTSIZE*FILTERNO+1;++j)
   printf("%lf ",wh[i][j]) ;
 printf("\n") ;
 for(i=0;i<HIDDENNO+1;++i)
  printf("%lf ",wo[i]) ;
 printf("\n") ;
} 

/**********************/
/*  hlearn()����      */
/*  �м���Ȩ��ѧϰ  */
/**********************/
void hlearn(double wh[HIDDENNO][POOLOUTSIZE*POOLOUTSIZE*FILTERNO+1]
    ,double wo[HIDDENNO+1]
    ,double hi[],double e[POOLOUTSIZE*POOLOUTSIZE*FILTERNO+1],double o)
{
 int i,j ;/*ѭ���Ŀ���*/
 double dj ;/*�����м���Ȩ�ؼ���*/

 for(j=0;j<HIDDENNO;++j){/*���м�����ԪjΪ����*/
  dj=hi[j]*(1-hi[j])*wo[j]*(e[POOLOUTSIZE*POOLOUTSIZE*FILTERNO]-o)*o*(1-o) ;
  for(i=0;i<POOLOUTSIZE*POOLOUTSIZE*FILTERNO;++i)/*�����i��Ȩ��*/
   wh[j][i]+=ALPHA*e[i]*dj ;
  wh[j][i]+=ALPHA*(-1.0)*dj ;/*��ֵ��ѧϰ*/
 }
}

/**********************/
/*  olearn()����      */
/*  ������Ȩ��ѧϰ  */
/**********************/
void olearn(double wo[HIDDENNO+1]
    ,double hi[],double e[POOLOUTSIZE*POOLOUTSIZE*FILTERNO+1],double o)
{
 int i ;/*ѭ���Ŀ���*/
 double d ;/*����Ȩ�ؼ���*/

 d=(e[POOLOUTSIZE*POOLOUTSIZE*FILTERNO]-o)*o*(1-o) ;/*���ļ���*/
 for(i=0;i<HIDDENNO;++i){
  wo[i]+=ALPHA*hi[i]*d ;/*Ȩ�ص�ѧϰ*/
 }
 wo[i]+=ALPHA*(-1.0)*d ;/*��ֵ��ѧϰ*/
 
} 

/**********************/
/*  forward()����     */
/*  ǰ�����          */
/**********************/
double forward(double wh[HIDDENNO][POOLOUTSIZE*POOLOUTSIZE*FILTERNO+1]
 ,double wo[HIDDENNO+1],double hi[],double e[POOLOUTSIZE*POOLOUTSIZE*FILTERNO+1])
{
 int i,j ;/*ѭ���Ŀ���*/
 double u ;/*��Ȩ�͵ļ���*/
 double o ;/*����ļ���*/

 /*hi�ļ���*/
 for(i=0;i<HIDDENNO;++i){
  u=0 ;/*��ȡ��Ȩ��*/
  for(j=0;j<POOLOUTSIZE*POOLOUTSIZE*FILTERNO;++j)
   u+=e[j]*wh[i][j] ; 
  u-=wh[i][j] ;/*��ֵ�Ĵ���*/
  hi[i]=f(u) ;
 }
 /*�������o*/
 o=0 ;
 for(i=0;i<HIDDENNO;++i)
  o+=hi[i]*wo[i] ;
 o-=wo[i] ;/*��ֵ�Ĵ���*/
 
 return f(o) ;
} 

/**********************/
/*    initwh()����    */
/*�м��Ȩ�صĳ�ʼ��  */
/**********************/
void initwh(double wh[][POOLOUTSIZE*POOLOUTSIZE*FILTERNO+1])
{
 int i,j ;/*ѭ���Ŀ���*/

 /*���������ȷ��Ȩ��*/ 
 for(i=0;i<HIDDENNO;++i)
  for(j=0;j<POOLOUTSIZE*POOLOUTSIZE*FILTERNO+1;++j)
   wh[i][j]=drnd() ;
} 

/**********************/
/*    initwo()����    */
/*�����Ȩ�صĳ�ʼ��  */
/**********************/
void initwo(double wo[])
{
 int i ;/*ѭ���Ŀ���*/

 /*���������ȷ��Ȩ��*/
 for(i=0;i<HIDDENNO+1;++i)
   wo[i]=drnd() ;
} 

/**********************/
/*  initfilter()����  */
/* �˲����ĳ�ʼ��     */
/**********************/
void initfilter(double filter[FILTERNO][FILTERSIZE][FILTERSIZE])
{
 int i,j,k ;/*ѭ���Ŀ���*/
 
 for(i=0;i<FILTERNO;++i)
  for(j=0;j<FILTERSIZE;++j)
   for(k=0;k<FILTERSIZE;++k)
    filter[i][j][k]=drnd() ;
} 

/*******************/
/* drnd()����      */
/* �����������    */
/*******************/
double drnd(void)
{
 double rndno ;/*���ɵ������*/

 while((rndno=(double)rand()/RAND_MAX)==1.0) ;
 rndno=rndno*2-1 ;/*���ɴ�-1��1�������*/
 return rndno; 
}

/**********************/
/*  pool()����        */
/* �ػ�����           */
/**********************/
void pool(double convout[][INPUTSIZE]
         ,double poolout[][POOLOUTSIZE]) 
{
 int i,j ;/*ѭ���Ŀ���*/

 for(i=0;i<POOLOUTSIZE;++i)
  for(j=0;j<POOLOUTSIZE;++j)
   poolout[i][j]=maxpooling(convout,i,j) ;
}
 
/**********************/
/* maxpooling()����   */
/* ���ֵ�ػ�         */
/**********************/
double maxpooling(double convout[][INPUTSIZE]
                 ,int i,int j)
{
 int m,n ;/*ѭ��������*/
 double max ;/*���ֵ*/
 int halfpool=POOLSIZE/2 ;/*�ػ���С��1/2*/
 
 max
 =convout[i*POOLOUTSIZE+1+halfpool][j*POOLOUTSIZE+1+halfpool];
 for(m=POOLOUTSIZE*i+1;m<=POOLOUTSIZE*i+1+(POOLSIZE-halfpool);++m)
  for(n=POOLOUTSIZE*j+1;n<=POOLOUTSIZE*j+1+(POOLSIZE-halfpool);++n)
   if(max<convout[m][n]) max=convout[m][n] ;

 return max ;
}
               
/**********************/
/* showdata()����     */
/*�������ݵı�ʾ      */
/**********************/
void showdata(double e[][INPUTSIZE][INPUTSIZE],int t[],int n_of_e)
{
 int i=0,j=0,k=0 ;/*ѭ���Ŀ�����*/

 /*���ݵı�ʾ*/
 for(i=0;i<n_of_e;++i){
  printf("N=%d category=%d\n",i,t[i]) ;
  for(j=0;j<INPUTSIZE;++j){
   for(k=0;k<INPUTSIZE;++k)
    printf("%.3lf ",e[i][j][k]) ;
   printf("\n") ;
  }
  printf("\n") ;
 }
}
             
/**********************/
/*  getdata()����     */
/*������������        */
/**********************/
int getdata(double e[][INPUTSIZE][INPUTSIZE],int t[])
{
 int i=0,j=0,k=0 ;/*ѭ���Ŀ�����*/

 /*���ݵ�����*/
 while(scanf("%d",&t[i])!=EOF){/*�����ʦ����*/
  /*����ͼ������*/
  while(scanf("%lf",&e[i][j][k])!=EOF){
   ++ k ;
   if(k>=INPUTSIZE){/*��һ������*/
    k=0 ;
    ++j ;
    if(j>=INPUTSIZE) break ;/*�������*/
   }
  }
  j=0; k=0 ;
  ++i ; 
 }
 return i ;
}

/**********************/
/*  conv()����        */
/*  �������    */
/**********************/
void conv(double filter[][FILTERSIZE]
         ,double e[][INPUTSIZE],double convout[][INPUTSIZE])
{
 int i=0,j=0 ;/*ѭ���Ŀ�����*/
 int startpoint=FILTERSIZE/2 ;/*�����Χ������*/

 for(i=startpoint;i<INPUTSIZE-startpoint;++i)
  for(j=startpoint;j<INPUTSIZE-startpoint;++j)
   convout[i][j]=calcconv(filter,e,i,j) ;
}

/**********************/
/*  calcconv()����    */
/*  �˲�����Ӧ��      */
/**********************/
double calcconv(double filter[][FILTERSIZE]
             ,double e[][INPUTSIZE],int i,int j)
{
 int m,n ;/*ѭ���Ŀ�����*/
 double sum=0 ;/*�͵�ֵ*/
 
 for(m=0;m<FILTERSIZE;++m)
  for(n=0;n<FILTERSIZE;++n)
   sum+=e[i-FILTERSIZE/2+m][j-FILTERSIZE/2+n]*filter[m][n];
   
 return sum ;
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

