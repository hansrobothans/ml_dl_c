/****************************************/
/*              kpdatagen.c             */
/*         ����������������ɻ�         */
/* ��������������������ֵ             */
/*ʹ�÷���                              */
/*\Users\odaka\dl\ch3>kpdatagen>data.txt*/
/****************************************/


/*��Visual Studio�Ļ����Ա�֤ */
#define _CRT_SECURE_NO_WARNINGS

/*Includeͷ�ļ�*/
#include <stdio.h>
#include <stdlib.h>

/*   ���ų����Ķ���                 */
#define MAXVALUE 100 /*�����ͼ�ֵ�����ֵ*/
#define N 30 /*�������*/
#define SEED 32768 /*�������seed*/

/*   ����ԭ������      */
int randdata() ;
    /*����MAXVALUE���µ��������������*/

/****************/
/*  main()����  */
/****************/
int main()
{
 int i ;

 srand(SEED) ;
 for(i=0;i<N;++i)
  printf("%ld %ld\n",randdata(),randdata()) ;
 return 0 ;
}

/**********************************/
/*     randdata()����             */
/*����MAXVALUE���µ��������������*/
/**********************************/
int randdata()
{
 int rnd ;
 
 /*ȥ������������ֵ*/
 while((rnd=rand())==RAND_MAX) ;
 /*������ļ���*/ 
 return (int)((double)rnd/RAND_MAX*MAXVALUE+1) ;

}
