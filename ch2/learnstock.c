/********************************************/
/*         learnstock.c                     */
/*  �����Ĺ���ѧϰ���������                */
/*            ģʽѧϰ��                    */
/*����100��ѧϰ����                         */
/*�������ʵ�10λ2����ģʽ��               */
/*ʹ�÷���                                    */
/*:\Users\odaka\dl\ch2>learnstock<ldata.txt */
/********************************************/

/*��Visual Studio�Ļ����Ա�֤ */
#define _CRT_SECURE_NO_WARNINGS

/*Includeͷ�ļ�*/
#include <stdio.h>
#include <stdlib.h>

/* ���ų����Ķ���             */
#define OK 1 
#define NG 0
#define SETSIZE 100 /*ѧϰ���ݼ��Ĵ�С*/
#define CNO 10 /*ѧϰ���ݵ�λ����10��*/
#define GENMAX  10000 /*���ɺ�ѡ��Ĵ���*/
#define SEED 32767 /*�������seed*/

/* ����ԭ������   */
void readdata(int data[SETSIZE][CNO],int teacher[SETSIZE]) ;
           /*����ѧϰ���ݼ�*/
int rand012() ;/*����0��1��2���������*/
int calcscore(int data[SETSIZE][CNO],int teacher[SETSIZE],
              int answer[CNO]) ;
           /*�����ѡ��ģʽ�ĵ÷֣�0��SETSIZE��*/


/****************/
/*  main()����  */
/****************/
int main()
{
 int i, j;
 int score = 0;/*�÷֣�0��SETSIZE��*/
 int answer[CNO];/*��ѡ��*/
 int data[SETSIZE][CNO];/*ѧϰ���ݼ�*/
 int teacher[SETSIZE];/*��ʦ����*/
 int bestscore = 0;/*�÷ֵ�����ֵ*/
 int bestanswer[CNO];/*���������е����Ž�*/

 srand(SEED);/*������ĳ�ʼ��*/

 /*����ѧϰ���ݼ�*/
 readdata(data,teacher) ;

 /*���ɺ�ѡ�Ⲣ���*/
 for (i = 0; i<GENMAX; ++i) {
  /*���ɺ�ѡ��*/
  for (j = 0; j<CNO; ++j) {
   answer[j] = rand012();
  }

  /*���*/
  score=calcscore(data,teacher,answer) ;

  /*���ŵ÷ֵĸ���*/
  if (score>bestscore) {/*����ǵ�ĿǰΪֹ������ֵ�����*/
   for (j = 0; j<CNO; ++j)
    bestanswer[j] = answer[j];
   bestscore = score;
   for (j = 0; j<CNO; ++j)
    printf("%1d ", bestanswer[j]);
   printf(":score=%d\n", bestscore);
  }
 }
 /*������Ž�*/
 printf("\n���Ž�\n");
 for (j = 0; j<CNO; ++j)
  printf("%1d ", bestanswer[j]);
 printf(":score=%d\n", bestscore);

 return 0;
}

/**********************************************/
/*            calcscore()����                 */
/*��ѡ��ģʽ�ĵ÷֣�0��SETSIZE���ļ���        */
/**********************************************/
int calcscore(int data[SETSIZE][CNO],int teacher[SETSIZE],
              int answer[CNO])
{
 int score = 0;/*�÷֣�0��SETSIZE��*/
 int point  ;/*��һ�µ�λ��(0��CNO)*/
 int i,j ;
 
for (i = 0; i<SETSIZE; ++i) {
  /*����һ�³̶�*/
  point = 0;
  for (j = 0; j<CNO; ++j) {
   if (answer[j] == 2) ++point;/*ͨ���*/
   else if (answer[j] == data[i][j]) ++point;/*��һ��*/
  }

  if ((point == CNO) && (teacher[i] == 1)) {
   ++score;
  }
  else if ((point != CNO) && (teacher[i] == 0)) {
   ++score;
  }
 }
 return score ;
}


/****************************/
/*     readdata()����       */
/*����ѧϰ���ݼ�            */
/****************************/
void readdata(int data[SETSIZE][CNO],int teacher[SETSIZE])
{
 int i,j ;
 
 for (i = 0; i<SETSIZE; ++i) {
  for (j = 0; j<CNO; ++j) {
   scanf("%d", &data[i][j]);
  }
  scanf("%d", &teacher[i]);
 }

}


/****************************/
/*     rand012()����        */
/*����0��1��2���������     */
/****************************/
int rand012()
{
 int rnd ;
 
 /*ȥ������������ֵ*/
 while((rnd=rand())==RAND_MAX) ;
 /*���������*/ 
 return (double)rnd/RAND_MAX*3 ;

}

