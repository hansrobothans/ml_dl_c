/*********************************************************/
/*                   cp.c                                */
/*             ����ͳػ�����                            */
/*����2ά���ݣ�ʵʩ����ͳػ�                            */
/* ʹ�÷���                                              */
/*  \Users\odaka\dl\ch5>cp < data1.txt                   */
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
#define POOLSIZE 3 /*�صĴ�С*/
#define POOLOUTSIZE 3/*�ػ������С*/
/*����ԭ������*/
void conv(double filter[][FILTERSIZE]
   ,double e[][INPUTSIZE]
   ,double convout[][INPUTSIZE]) ; /*�������*/
double calcconv(double filter[][FILTERSIZE]
               ,double e[][INPUTSIZE],int i,int j) ;
                               /*  Ӧ���˲���  */
void convres(double convout[][INPUTSIZE]) ;
              /*�����������*/
void pool(double convout[][INPUTSIZE]
         ,double poolout[][POOLOUTSIZE]) ; 
             /*�ػ�����*/           
double maxpooling(double convout[][INPUTSIZE]
                 ,int i,int j) ;/* ���ֵ�ػ� */
void poolres(double poolout[][POOLOUTSIZE]) ;/*��������*/
void getdata(double e[][INPUTSIZE]) ;/*��������*/ 
         
/*******************/ 
/*    main()����   */ 
/*******************/ 
int main()
{
 double filter[FILTERSIZE][FILTERSIZE]
//      ={{0,0,0},{1,1,1},{0,0,0}} ;/*�����˲���*/
        ={{0,1,0},{0,1,0},{0,1,0}} ;/*�����˲���*/
 double e[INPUTSIZE][INPUTSIZE] ;/*��������*/
 double convout[INPUTSIZE][INPUTSIZE]={0} ;/*������*/
 double poolout[POOLOUTSIZE][POOLOUTSIZE] ;/*�������*/
 int i,j ;/*ѭ������*/
 
 /*������������*/
 getdata(e) ;
 
 /*�������*/
 conv(filter,e,convout) ;
 convres(convout) ;
 
 /*�ػ�����*/
 pool(convout,poolout) ;
 /*��������*/
 poolres(poolout) ;
 
 return 0 ;
}

/**********************/
/*  poolres()����     */
/* ��������         */
/**********************/
void poolres(double poolout[][POOLOUTSIZE]) 
{
 int i,j ;/*ѭ���Ŀ���*/
 
 for(i=0;i<POOLOUTSIZE;++i){
  for(j=0;j<POOLOUTSIZE;++j){
   printf("%.3lf ",poolout[i][j]) ;
  }
  printf("\n") ;
 }
 printf("\n") ;	
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
 int m,n ;/*ѭ���Ŀ�����*/
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
/*  convres()����     */
/* �����������     */
/**********************/
void convres(double convout[][INPUTSIZE]) 
{
 int i,j ;/*ѭ���Ŀ���*/
 
 for(i=1;i<INPUTSIZE-1;++i){
  for(j=1;j<INPUTSIZE-1;++j){
   printf("%.3lf ",convout[i][j]) ;
  }
  printf("\n") ;
 }
 printf("\n") ;	
} 
              
/**********************/
/*  getdata()����     */
/*������������        */
/**********************/
void getdata(double e[][INPUTSIZE])
{
 int i=0,j=0 ;/*ѭ���Ŀ�����*/

 /*���ݵ�����*/
 while(scanf("%lf",&e[i][j])!=EOF){
  ++ j ;
  if(j>=INPUTSIZE){/*��һ������*/
   j=0 ;
   ++i ;
   if(i>=INPUTSIZE) break ;/*�������*/
  }
 }
}

/**********************/
/*  conv()����        */
/*  �������          */
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

