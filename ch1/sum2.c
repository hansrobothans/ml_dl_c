/******************************/
/*          sum2.c            */
/*       ��͡���ƽ����       */
/* �ɱ�׼�����ȡʵ��         */
/* ��������ͼ�ƽ����         */
/* ��Ctrl+Z��ֹ����           */
/* ʹ�÷���                   */
/* C:\Users\odaka\dl\ch1>sum2 */
/******************************/

/*��Visual Studio�Ļ����Ա�֤*/
#define _CRT_SECURE_NO_WARNINGS

/*Includeͷ�ļ�*/
#include <stdio.h>
#include <stdlib.h>

/* ���ų����Ķ���             */
#define BUFSIZE 256  /*���뻺���С*/

/****************/
/*  main()����  */
/****************/
int main()
{
 char linebuf[BUFSIZE] ;/*���뻺��*/
 double data ;/*��������*/
 double sum=0.0 ;/*��*/
 double sum2=0.0 ;/*ƽ����*/

 while(fgets(linebuf,BUFSIZE,stdin)!=NULL){
  /*�ڿ��Զ�ȡ��ʱ�ظ�����*/
  if(sscanf(linebuf,"%lf",&data)!=0){/*�ܹ��任ʱ*/
    sum+=data ;
    sum2+=data*data ;
    printf("%lf\t%lf\n",sum,sum2) ;
  }
 }

 return 0 ;
}
