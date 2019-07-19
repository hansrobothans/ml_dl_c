/*********************************************************/
/*                   neuron.c                            */
/* �����˹���Ԫ�ļ���                                  */
/* ģ������ʵ�Ȩ�غ���ֵ���˹���Ԫ                    */
/* ʹ�÷���                                              */
/*  \Users\odaka\dl\ch4>neuron                           */
/*********************************************************/

/*Visual Studio�Ļ����Ա�֤ */
#define _CRT_SECURE_NO_WARNINGS

/* Includeͷ�ļ� */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


/*���ų����Ķ���*/
#define INPUTNO 2  /*������*/ 
#define MAXINPUTNO 100    /*���ݵ�������*/ 

/*����ԭ�͵�����*/
double f(double u) ; /*���ݺ���*/
void initw(double w[INPUTNO+1]) ;
                         /*Ȩ�غ���ֵ�ĳ�ʼ��*/
double forward(double w[INPUTNO+1]
         ,double e[INPUTNO]) ; /*ǰ�����*/
int getdata(double e[][INPUTNO]) ;/*��������*/ 
         
/*******************/ 
/*    main()����   */ 
/*******************/ 
int main()
{
 double w[INPUTNO+1] ;/*Ȩ�غ���ֵ*/
 double e[MAXINPUTNO][INPUTNO] ;/*���ݼ�*/
 double o ;/*���*/
 int i,j ;/*ѭ���Ŀ���*/
 int n_of_e ;/*���ݵĸ���*/
 
 /*Ȩ�صĳ�ʼ��*/
 initw(w) ;

 /*������������*/
 n_of_e=getdata(e) ;
 printf("���ݵĸ���:%d\n",n_of_e) ;
 
 /*���������*/
 for(i=0;i<n_of_e;++i){
  printf("%d ",i) ;
  for(j=0;j<INPUTNO;++j)
   printf("%lf ",e[i][j]) ;
  o=forward(w,e[i]) ;
  printf("%lf\n",o) ;
 }

 return 0 ;
}

/**********************/
/*  getdata()����     */
/*����ѧϰ����        */
/**********************/
int getdata(double e[][INPUTNO])
{
 int n_of_e=0 ;/*���ݼ��ĸ���*/
 int j=0 ;/*ѭ���Ŀ�����*/

 /*���ݵ�����*/
 while(scanf("%lf",&e[n_of_e][j])!=EOF){
  ++ j ;
  if(j>=INPUTNO){/*��һ������*/
   j=0 ;
   ++n_of_e ;
  }
 }
 return n_of_e ;
}

/**********************/
/*  forward()����     */
/*  ǰ�����          */
/**********************/
double forward(double w[INPUTNO+1],double e[INPUTNO])
{
 int i ;/*ѭ���Ŀ���*/
 double u,o ;/*�м�ļ���ֵu�����ֵo*/

 /*���������*/
 u=0 ;
 for(i=0;i<INPUTNO;++i)
  u+=e[i]*w[i] ;
 u-=w[i] ;/*��ֵ�Ĵ���*/
 /*���ֵ�ļ���*/
 o=f(u) ;
 return o ;
} 

/**********************/
/*    initw()����     */
/*   Ȩ�صĳ�ʼ��     */
/**********************/
void initw(double w[INPUTNO+1])
{

 /*��Ȩ�ع̶�����*/
 w[0]=1 ;
 w[1]=1 ;
 w[2]=1.5 ;
// w[2]=0.5 ;

} 


/*******************/
/* f()����         */
/* ���ݺ���        */
/*******************/
double f(double u)
{
 /*���ݺ����ļ���*/
 if(u>=0) return 1.0 ;
 else return 0.0 ;
 
 /*sigmoid�����ļ���*/
// return 1.0/(1.0+exp(-u)) ;
}



