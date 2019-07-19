/*********************************************************/
/*                   nn.c                                */
/* �򵥲����������ļ���                              */
/* 1�����������ļ��㣨��ѧϰ��                         */
/* ʹ�÷���                                              */
/*  \Users\odaka\dl\ch4>nn <data.txt                     */
/*********************************************************/

/*Visual Studio�����Ա�֤ */
#define _CRT_SECURE_NO_WARNINGS

/* Includeͷ�ļ�*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


/*���ų����Ķ���*/
#define INPUTNO 2  /*��������Ԫ��*/ 
#define HIDDENNO 2  /*�м�����Ԫ��*/ 
#define MAXINPUTNO 100    /*���ݵ�������*/ 

/*����ԭ�͵�����*/
double f(double u) ; /*���ݺ���*/
void initwh(double wh[HIDDENNO][INPUTNO+1]) ;
                         /*�м��Ȩ�صĳ�ʼ��*/
void initwo(double wo[HIDDENNO+1]) ;/*�����Ȩ�صĳ�ʼ��*/
double forward(double wh[HIDDENNO][INPUTNO+1]
         ,double wo[HIDDENNO+1],double hi[]
         ,double e[INPUTNO]) ; /*ǰ�����*/
int getdata(double e[][INPUTNO]) ;/*��������*/ 
         
/*******************/ 
/*    main()����   */ 
/*******************/ 
int main()
{
 double wh[HIDDENNO][INPUTNO+1] ;/*�м���Ȩ��*/
 double wo[HIDDENNO+1] ;/*������Ȩ��*/
 double e[MAXINPUTNO][INPUTNO] ;/*���ݼ�*/
 double hi[HIDDENNO+1] ;/*�м������*/
 double o ;/*���*/
 int i,j ;/*ѭ���Ŀ���*/
 int n_of_e ;/*���ݸ���*/
 
 /*Ȩ�صĳ�ʼ��*/
 initwh(wh) ;
 initwo(wo) ;

 /*������������*/
 n_of_e=getdata(e) ;
 printf("���ݵĸ���:%d\n",n_of_e) ;
 
 /*���������*/
 for(i=0;i<n_of_e;++i){
  printf("%d ",i) ;
  for(j=0;j<INPUTNO;++j)
   printf("%lf ",e[i][j]) ;
  o=forward(wh,wo,hi,e[i]) ;
  printf("%lf\n",o) ;
 }

 return 0 ;
}

/**********************/
/*  getdata()����     */
/*    ����ѧϰ����    */
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
double forward(double wh[HIDDENNO][INPUTNO+1]
 ,double wo[HIDDENNO+1],double hi[],double e[INPUTNO])
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


//**********************/
/*    initwh()����     */
/*�м��Ȩ�صĳ�ʼ��   */
/**********************/
void initwh(double wh[HIDDENNO][INPUTNO+1])
{
 
 /*��Ȩ�ع̶�����*/
 wh[0][0]=-2 ;
 wh[0][1]=3 ;
 wh[0][2]=-1 ;
 wh[1][0]=-2 ;
 wh[1][1]=1 ;
 wh[1][2]=0.5 ;

} 

/**********************/
/*    initwo()����    */
/*�����Ȩ�صĳ�ʼ��  */
/**********************/
void initwo(double wo[HIDDENNO+1])
{
 /*��Ȩ�ع̶�����*/
 wo[0]=-60 ;
 wo[1]=94 ;
 wo[2]=-1 ;
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



