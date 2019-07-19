/********************************************/
/*         qlearning.c                      */
/*   ǿ��ѧϰ��Qѧϰ�����������            */
/*   ѧϰ���̽���Թ�                       */
/*ʹ�÷���                                  */
/*:\Users\odaka\dl\ch2>qlearning            */
/********************************************/

/*��Visual Studio�Ļ����Ա�֤ */
#define _CRT_SECURE_NO_WARNINGS

/*Includeͷ�ļ�*/
#include <stdio.h>
#include <stdlib.h>

/* ���ų����Ķ���            */
#define GENMAX  1000 /*ѧϰ���ظ�����*/
#define NODENO  15  /*Qֵ�Ľڵ���*/
#define ALPHA 0.1/*ѧϰϵ��*/
#define GAMMA 0.9/*�ۿ���*/
#define EPSILON 0.3 /*ȷ���ж�ѡ��������*/
#define SEED 32767 /*�������seed*/

/* ����ԭ������   */
int rand100() ;/*����0��100���������*/
int rand01() ;/*����0��1���������*/
double rand1() ;/*����0��1��ʵ�����������*/
void printqvalue(int qvalue[NODENO]);/*���Qֵ*/
int selecta(int s,int qvalue[NODENO]);/*�ж�ѡ��*/
int updateq(int s,int qvalue[NODENO]);/*����Qֵ*/

/****************/
/*  main()����  */
/****************/
int main()
{
 int i;
 int s;/*״̬*/
 int t;/*ʱ��*/
 int qvalue[NODENO];/*Qֵ*/


 srand(SEED);/*������ĳ�ʼ��*/

 /*Qֵ�ĳ�ʼ��*/
 for(i=0;i<NODENO;++i)
  qvalue[i]=rand100() ;
 printqvalue(qvalue) ;


 /*ѧϰ������*/
 for(i=0;i<GENMAX;++i){
  s=0;/*�ж��ĳ�ʼ״̬*/
  for(t=0;t<3;++t){/*����ĩ��Ϊֹ�ظ�����*/
   /*�ж�ѡ��*/
   s=selecta(s,qvalue) ;
   
   /*Qֵ�ĸ���*/
   qvalue[s]=updateq(s,qvalue) ;
  }
  /*Qֵ�����*/
  printqvalue(qvalue) ;
 }
 return 0;
}

/****************************/
/*       updateq()����      */
/*       ����Qֵ            */
/****************************/
int updateq(int s,int qvalue[NODENO])
{
 int qv ;/*Ҫ���µ�Qֵ*/
 int qmax ;/*Qֵ�����ֵ*/
 
 /*��ĩ�˵�����*/
 if(s>6){
  if(s==14)/*���轱��*/
   qv=qvalue[s]+ALPHA*(1000-qvalue[s]) ;
  /*���轱�͵Ľڵ�Qֵ����*/
  /*�����ڵ��Qֵ׷��ʱ*/
  /*ȥ������2�е�ע��*/
//  else if(s==11)/*���轱��*/
//   qv=qvalue[s]+ALPHA*(500-qvalue[s]) ;
  else/*�޽���*/
   qv=qvalue[s] ;
 }
 /*��ĩ��֮��*/
 else{
  if((qvalue[2*s+1])>(qvalue[2*s+2])) 
   qmax=qvalue[2*s+1];
  else qmax=qvalue[2*s+2];
  qv=qvalue[s]+ALPHA*(GAMMA*qmax-qvalue[s]) ;
 }

 return qv ;
}

/****************************/
/*        selecta()����     */
/*        �ж�ѡ��          */
/****************************/
int selecta(int olds,int qvalue[NODENO])
{
 int s ;
 
 /*���ڦ�-greedy�������ж�ѡ��*/
 if(rand1()<EPSILON){
  /*����ж�*/
  if(rand01()==0) s=2*olds+1 ;
  else s=2*olds+2 ;
 }
 else{
  /*ѡ��Qֵ�����ֵ*/
  if((qvalue[2*olds+1])>(qvalue[2*olds+2])) 
   s=2*olds+1;
  else s=2*olds+2;
 }

 return s ;
}



/****************************/
/*    printqvalue()����     */
/*    ���Qֵ               */
/****************************/
void printqvalue(int qvalue[NODENO])
{
 int i ;
 
 for (i=1;i<NODENO;++i)
  printf("%d\t",qvalue[i]);

 printf("\n");

}

/****************************/
/*     rand1()����          */
/*����0��1��ʵ�����������  */
/****************************/
double rand1()
{
 /*������ļ���*/ 
 return (double)rand()/RAND_MAX ;

}

/****************************/
/*     rand01()����         */
/*����0��1���������        */
/****************************/
int rand01()
{
 int rnd ;
 
 /*ȥ������������ֵ*/
 while((rnd=rand())==RAND_MAX) ;
 /*������ļ���*/ 
 return (int)((double)rnd/RAND_MAX*2) ;

}

/****************************/
/*     rand100()����        */
/*����0��100���������      */
/****************************/
int rand100()
{
 int rnd ;
 
 /*ȥ������������ֵ*/
 while((rnd=rand())==RAND_MAX) ;
 /*������ļ���*/ 
 return (int)((double)rnd/RAND_MAX*101) ;

}

