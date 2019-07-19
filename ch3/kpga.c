/*****************************************************/
/*                  kpga.c�@�@                       */
/*          ����GA�ı��������������               */
/*          ����GA������������������Ž�             */
/* ʹ�÷���                                          */
/*\Users\odaka\dl\ch3>kpga < data.txt                */
/*****************************************************/

/*��Visual Studio�Ļ����Ա�֤ */
#define _CRT_SECURE_NO_WARNINGS

/* Includeͷ�ļ�*/
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/*���ų����Ķ���*/
#define MAXVALUE 100 /*�����ͼ�ֵ�����ֵ*/
#define N 30 /*�������*/
#define WEIGHTLIMIT (N*MAXVALUE/4) /*��������*/
#define POOLSIZE 30 /*Ⱦɫ�����*/
#define LASTG 50    /*��ֹ���*/
#define MRATE 0.01  /*ͻ��ĸ���*/
#define SEED 32767    /*�������seed*/
#define YES 1   /*yes��Ӧ������ֵ*/
#define NO 0    /*no��Ӧ������ֵ*/

/*����ԭ������*/
void initparcel();/*����ĳ�ʼ��*/
int evalfit(int gene[]) ; /*������Ӧ��*/
void mating(int pool[POOLSIZE][N]
            ,int ngpool[POOLSIZE*2][N]) ; /*����*/
void mutation(int ngpool[POOLSIZE*2][N]) ; /*ͻ��*/
void printp(int pool[POOLSIZE][N]) ; /*������*/
void initpool(int pool[POOLSIZE][N]) ;
                         /*���ɳ�ʼȾɫ�弯��*/
int rndn() ; /*����n֮�µ������   */
int notval(int v) ;/*��ֵ�ķ�ת*/
int selectp(int roulette[POOLSIZE],int totalfitness) ;
                    /*ѡ�񸸴�*/
void crossing(int m[],int p[],int c1[],int c2[]) ;
                /* �����ض�Ⱦɫ��Ľ��� */
void selectng(int ngpool[POOLSIZE*2][N]
              ,int pool[POOLSIZE][N]) ;/*ѡ����һ��*/

/*ȫ�ֱ������������ݣ�*/
 int parcel[N][2] ;/*����*/

/*******************/
/*    main()����   */
/*******************/
int main(int argc,char *argv[])
{
 int pool[POOLSIZE][N] ; /*Ⱦɫ�弯��*/
 int ngpool[POOLSIZE*2][N] ; /*��һ��Ⱦɫ�弯��*/
 int generation;/* ���ڵĴ��� */
 
 /*������ĳ�ʼ��*/
 srand(SEED) ;

 /*����ĳ�ʼ��*/
 initparcel() ;
 
 /*���ɳ�ʼȾɫ�弯��*/
 initpool(pool) ;
 
 /*ѭ��ֱ����ֹ�Ӵ�*/
 for(generation=0;generation<LASTG;++generation){
  printf("%d����\n",generation) ;
  mating(pool,ngpool) ;/*����*/
  mutation(ngpool) ;/*ͻ��*/
  selectng(ngpool,pool) ;/*ѡ����һ�Ӵ�*/
  printp(pool) ;/*������*/
 }

 return 0 ;
}

/****************************/
/*      initparcel()����    */
/*      ����ĳ�ʼ��        */
/****************************/
void initparcel()
{
 int i=0 ;
 while((i<N) && 
  (scanf("%d %d",&parcel[i][0],&parcel[i][1])
                 !=EOF)){
  ++i ;
 }
}

/************************/
/*   selectng()����     */
/*   ѡ����һ��         */
/************************/
void selectng(int ngpool[POOLSIZE*2][N]
              ,int pool[POOLSIZE][N]) 
{
 int i,j,c ;/* ѭ�����Ʋ��� */
 int totalfitness=0 ;/*��Ӧ�ȵ��ܼ�ֵ*/
 int roulette[POOLSIZE*2] ;/*�����Ӧ��*/
 int ball ;/* ��ѡ��λ�õ���ֵ��*/
 int acc=0 ;/*��Ӧ�ȵ��ۻ�ֵ*/
 
 /*ѭ������ѡ��*/
 for(i=0;i<POOLSIZE;++i){
  /* �������� */
  totalfitness=0 ;
  for(c=0;c<POOLSIZE*2;++c){
   roulette[c]=evalfit(ngpool[c]) ;
   /*������Ӧ�ȵ��ܼ�ֵ*/
   totalfitness+=roulette[c] ;
  }
  /*ѡ��һ��Ⱦɫ��*/
  ball=rndn(totalfitness) ;
  acc=0 ;
  for(c=0;c<POOLSIZE*2;++c){
   acc+=roulette[c] ;/*�ۻ�����ֵ*/
   if(acc>ball) break ;/*��Ӧ�Ļ���*/
  }

  /*Ⱦɫ��ĸ���*/
  for(j=0;j<N;++j){
   pool[i][j]=ngpool[c][j] ;
  }
 }
}

/************************/
/*   selectp()����      */
/*    ������ѡ��        */
/************************/
int selectp(int roulette[POOLSIZE],int totalfitness)
{
 int i ;/* ѭ���Ŀ��Ʊ��� */
 int ball ;/* ��ѡ��λ�õ���ֵ��*/
 int acc=0 ;/*����ֵ���ۻ�ֵ*/

 ball=rndn(totalfitness) ;
 for(i=0;i<POOLSIZE;++i){
  acc+=roulette[i] ;/*����ֵ���ۻ�*/
  if(acc>ball) break ;/*��Ӧ�Ļ���*/
 }
 return i ;
}


/************************/
/*   mating()����       */
/*        ����          */
/************************/
void mating(int pool[POOLSIZE][N]
           ,int ngpool[POOLSIZE*2][N])
{
 int i ;/* ѭ���Ŀ��Ʊ��� */
 int totalfitness=0 ;/*����ֵ���ܼ�ֵ*/
 int roulette[POOLSIZE] ;/*�������ֵ*/
 int mama,papa ;/*�����Ļ���ĺ���*/

 /* �������� */
 for(i=0;i<POOLSIZE;++i){
  roulette[i]=evalfit(pool[i]) ;
  /* ��������ֵ���ܼ�ֵ*/
  totalfitness+=roulette[i] ;
 }

 /*ѡ��ͽ����ѭ��*/
 for(i=0;i<POOLSIZE;++i){
  do{/*������ѡ��*/
   mama=selectp(roulette,totalfitness) ;
   papa=selectp(roulette,totalfitness) ;
  }while(mama==papa) ;/*ɾ���ظ���*/

  /*�ض�2Ⱦɫ��Ľ���*/
  crossing(pool[mama],pool[papa]
            ,ngpool[i*2],ngpool[i*2+1])  ;  
 }
}


/************************/
/*  crossing()����      */
/* �ض�2Ⱦɫ��Ľ���    */
/************************/
void crossing(int m[],int p[],int c1[],int c2[])
{
 int j ;/* ѭ�����Ʊ��� */
 int cp ;/*����ĵ�*/

 /*ȷ�������*/
 cp =rndn(N) ;

 /*����ǰ�벿��*/
 for(j=0;j<cp;++j){
  c1[j]=m[j] ;
  c2[j]=p[j] ;
 }
 /*���ƺ�벿��*/
 for(;j<N;++j){
  c2[j]=m[j] ;
  c1[j]=p[j] ;
 }
}

/************************/
/*   evalfit()����      */
/*   ��������ֵ         */
/************************/
int evalfit(int g[])
{
 int pos ;/*ָ������λ��*/
 int value=0 ;/*����ֵ*/
 int weight=0 ;/*����*/

 /*�����������λ���������������ֵ*/
 for(pos=0;pos<N;++pos){
  weight+=parcel[pos][0]*g[pos] ;
  value+=parcel[pos][1]*g[pos] ;
 }
 /*��������Ĵ���*/
 if(weight>=WEIGHTLIMIT) value=0 ;
 return value;
 
}

/***********************/
/*   printp()����      */
/*   ������          */
/***********************/
void printp(int pool[POOLSIZE][N])
{
 int i,j ;/* ѭ���Ŀ��Ʊ��� */
 int fitness ;/* ����ֵ */
 double totalfitness=0 ;/* ����ֵ���ܼ�ֵ */
 int elite,bestfit=0 ;/*��Ӣ����Ĵ����ñ���*/

 for(i=0;i<POOLSIZE;++i){
  for(j=0;j<N;++j)
   printf("%1d",pool[i][j]) ;
  fitness=evalfit(pool[i]) ;
  printf("\t%d\n",fitness) ;
  if(fitness>bestfit){/*��Ӣ��*/
   bestfit=fitness ;
   elite=i ;
  }
  totalfitness+=fitness ;
 }
 /*�����Ӣ�������ֵ*/
 printf("%d\t%d \t",elite,bestfit) ;
 /*���ƽ������ֵ*/
 printf("%lf\n",totalfitness/POOLSIZE) ;
}


/***********************/
/*   initpool()����    */
/*   ���ɳ�ʼȾɫ�弯��*/
/***********************/
void initpool(int pool[POOLSIZE][N])
{
 int i,j ;/* ѭ�����Ʊ��� */

 for(i=0;i<POOLSIZE;++i)
  for(j=0;j<N;++j)
   pool[i][j]=rndn(2) ;
}


/************************/
/*     rndn()����       */
/*    n��������������� */
/************************/
int rndn(int l)
{
 int rndno ;/*���ɵ������*/

 while((rndno=((double)rand()/RAND_MAX)*l)==l) ;

 return rndno;
}

/***********************/
/*   mutation()����    */
/*   ͻ��              */
/***********************/
void mutation(int ngpool[POOLSIZE*2][N])
{
 int i,j ;/* ѭ���Ŀ��Ʊ��� */

 for(i=0;i<POOLSIZE*2;++i)
  for(j=0;j<N;++j)
   if((double)rndn(100)/100.0<=MRATE)
    /*��ת��ͻ��*/
    ngpool[i][j]=notval(ngpool[i][j]) ;

}

/************************/
/*   notval()����       */
/*   ��ֵ�ķ�ת         */
/************************/
int notval(int v)
{
 if(v==YES) return NO ;
 else return YES ;
}

