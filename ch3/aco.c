/****************************************/
/*                aco.c                 */
/*  ��Ⱥ���Ż�����(aco)����             */
/*   ����acoѧϰ����ֵ                  */
/*ʹ�÷���                              */
/*\Users\odaka\dl\ch3>aco               */
/****************************************/


/*��Visual Studio�Ļ����Ա�֤ */
#define _CRT_SECURE_NO_WARNINGS

/*Includeͷ�ļ�*/
#include <stdio.h>
#include <stdlib.h>

/*   ���ų����Ķ���                 */
#define NOA 10 /*���ϵĸ�����*/
#define ILIMIT 50 /*ѭ������*/
#define Q 3 /*��Ϣ�ظ��µĳ���*/
#define RHO 0.8 /*�ӷ�����*/
#define STEP 10 /*·�̵Ĳ���*/
#define EPSILON 0.15 /*ȷ���ж�ѡ��������*/
#define SEED 32768 /*�������Seed*/


/*   ����ԭ������      */
void printp(double pheromone[2][STEP]) ;/*��ʾ*/
void printmstep(int mstep[NOA][STEP]) ;
                             /*��ʾ���ϵ��ж�*/
void walk(int cost[2][STEP]
          ,double pheromone[2][STEP]
          ,int mstep[NOA][STEP] ) ;/*ʹ���ϲ���*/
void update(int cost[2][STEP]
         ,double pheromone[2][STEP]
        ,int mstep[NOA][STEP] ) ;/*������Ϣ��*/
double rand1() ;/*����0��1ʵ�����������*/
int rand01() ;/*����0��1���������*/


/**********************/
/*     main()����     */
/**********************/
int main()
{
 int cost[2][STEP]={/*�����Ĵ��ۣ����룩*/
	 {1,1,1,1,1,1,1,1,1,1},
	 {5,5,5,5,5,5,5,5,5,5}};
 double pheromone[2][STEP]={0} ;/*��������Ϣ����*/
 int mstep[NOA][STEP] ;/*�����߹��Ĺ���*/
 int i;/*ѭ�������Ŀ���*/
 
 /*������ĳ�ʼ��*/
 srand(SEED) ;

 /*���Ż�������*/
 for(i=0;i<ILIMIT;++i){
  /*��Ϣ�ص�״̬�����*/
  printf("%d:\n",i) ;
  printp(pheromone) ;
  /*ʹ���ϲ���*/
  walk(cost,pheromone,mstep) ;
  /*������Ϣ��*/
  update(cost,pheromone,mstep) ;
 }
 /*��Ϣ��״̬�����*/
 printf("%d:\n",i) ;
 printp(pheromone) ;
 
 return 0 ;
}

/**************************/
/*    update()����        */
/*    ������Ϣ��          */
/**************************/
void update(int cost[2][STEP]
        ,double pheromone[2][STEP]
        ,int mstep[NOA][STEP] )
{
 int m ;/*���ϸ���ĺ���*/
 int lm ;/*���ϲ��еľ���*/
 int i,j ;
 double sum_lm=0 ;/*���ϲ��е��������*/
 
 /*��Ϣ�صĻӷ�*/
 for(i=0;i<2;++i)
  for(j=0;j<STEP;++j)
   pheromone[i][j]*=RHO ;

 /*���ϵĸ���*/
 for(m=0;m<NOA;++m){
  /*����m���ƶ�����lm�ļ���*/
  lm=0 ;
  for(i=0;i<STEP;++i)
   lm+=cost[mstep[m][i]][i] ;

  /*��Ϣ�صĸ���*/
  for(i=0;i<STEP;++i)
   pheromone[mstep[m][i]][i]+=Q*(1.0/lm) ;
  sum_lm+=lm ;
 }
 /*���ϲ��е�ƽ����������*/
 printf("%lf\n",sum_lm/NOA) ;
}

/**************************/
/*    walk()����          */
/*    ʹ���ϲ���          */
/**************************/
void walk(int cost[2][STEP]
,double pheromone[2][STEP],int mstep[NOA][STEP])
{
 int m ;/*���ϸ���ĺ���*/
 int s ;/*��������������λ��*/

 for(m=0;m<NOA;++m){
  for(s=0;s<STEP;++s){
   /*���ڦ�-greedy���ж�ѡ��*/
   if((rand1()<EPSILON)
    ||(abs(pheromone[0][s]-pheromone[1][s])<1e-9))
   {/*����ж�*/
    mstep[m][s]=rand01() ;
   }
   else{/*������Ϣ�ص�ѡ��*/
    if(pheromone[0][s]>pheromone[1][s]) 
      mstep[m][s]=0 ;
    else
      mstep[m][s]=1 ;
   }
 }
 }
 /*������ϵ��ж�*/
 printmstep(mstep) ;
}

/**************************/
/*  printmstep()����      */
/*   ��ʾ���ϵ��ж�       */
/**************************/
void printmstep(int mstep[NOA][STEP])
{
 int i,j ;

 printf("*mstep\n") ;
 for(i=0;i<NOA;++i){
  for(j=0;j<STEP;++j)
   printf("%d ",mstep[i][j]) ;
  printf("\n") ;
 }
}


/**************************/
/*    printp()����        */
/*   ��ʾ��Ϣ��           */
/**************************/
void printp(double pheromone[2][STEP]) 
{
 int i,j ;

 for(i=0;i<2;++i){
  for(j=0;j<STEP;++j)
   printf("%4.2lf ",pheromone[i][j]) ;
  printf("\n") ;
 }
}

/**************************/
/*    rand1()����         */
/*����0��1��ʵ�����������*/
/**************************/
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
 /*���������*/ 
 return (int)((double)rnd/RAND_MAX*2) ;

}
