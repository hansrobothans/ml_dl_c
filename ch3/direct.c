/*************************************/
/*              direct.c             */
/*ͨ��ȫ����������ⱳ������         */
/*ʹ�÷���                             */
/*\Users\odaka\dl\ch3>direct<data.txt*/
/*************************************/


/*��Visual Studio�Ļ����Ա�֤ */
#define _CRT_SECURE_NO_WARNINGS

/*Includeͷ�ļ�*/
#include <stdio.h>
#include <stdlib.h>


/*  ���ų����Ķ���                 */
#define MAXVALUE 100 /*�����ͼ�ֵ�����ֵ*/
#define N 30 /*����ĸ���*/
#define WEIGHTLIMIT (N*MAXVALUE/10)
             /*��������*/
#define SEED 32768 /*�������seed*/

/*   ����ԭ�͵�����      */
void initparcel(int parcel [N][2]);/*����ĳ�ʼ��*/
void prints(int solution);/*�����ѡ��*/
int solve(int parcel [N][2]) ;/*���ص�����*/
int pow2n(int n);/*2������*/
int calcval(int parcel[N][2],int i);/*����ֵ�ļ���*/

/****************/
/*  main()����  */
/****************/
int main()
{
 int parcel[N][2] ;/*����*/
 int solution=0xfff ;/*��*/

 /*����ĳ�ʼ��*/
 initparcel(parcel) ;
 /*����������*/
 solution=solve(parcel) ;
 /*������*/
 prints(solution) ;
 return 0 ;
}

/****************************/
/*       solve()����        */
/*       ����������         */
/****************************/
int solve(int parcel [N][2])
{
 int i ;/*ѭ������*/
 int limit ;/*����������*/
 int maxvalue=0 ;/*����ֵ�����ֵ*/
 int value ;/*����ֵ*/
 int solution ;/*��ѡ��*/

 /*������Χ���趨*/
 limit=pow2n(N) ;
 /*�������*/
 for(i=0;i<limit;++i){
  /*��������ֵ*/
  value=calcval(parcel,i) ;
  /*���ֵ�ĸ���*/
  if(value>maxvalue){
   maxvalue=value ;
   solution=i ;
   printf("*** maxvalue %d\n",maxvalue) ;
  }
 }
 return solution ;
}

/****************************/
/*       calcval()����      */
/*       ��������ֵ         */
/****************************/
int calcval(int parcel[N][2],int i)
{
 int pos ;/*ָ������λ��*/
 int value=0 ;/*����ֵ*/
 int weight=0 ;/*����*/

 /*���������λ�����������������ֵ*/
 for(pos=0;pos<N;++pos){
  weight+=parcel[pos][0]*((i>>pos)&0x1) ;
  value+=parcel[pos][1]*((i>>pos)&0x1) ;
 }
 /*��������Ĵ���*/
 if(weight>=WEIGHTLIMIT) value=0 ;
 return value;
}

/****************************/
/*       pow2n()����        */
/*       2������            */
/****************************/
int pow2n(int n)
{
 int pow=1 ;
 for(;n>0;--n)
  pow*=2 ;
 return pow ;
}

/****************************/
/*       prints()����       */
/*      �����ѡ��          */
/****************************/
void prints(int solution)
{
 int i ;
 for(i=0;i<N;++i)
  printf("%1d ",(solution>>i)&0x1) ;
 printf("\n") ;
}

/****************************/
/*      initparcel()����    */
/*      ����ĳ�ʼ��        */
/****************************/
void initparcel(int parcel [N][2])
{
 int i=0 ;
 while((i<N) && 
  (scanf("%d %d",&parcel[i][0],&parcel[i][1])!=EOF)){
  ++i ;
 }
}
