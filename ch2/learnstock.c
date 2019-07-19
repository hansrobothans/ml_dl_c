/********************************************/
/*         learnstock.c                     */
/*  单纯的归纳学习的例题程序                */
/*            模式学习器                    */
/*读入100个学习数据                         */
/*给出合适的10位2进制模式答案               */
/*使用方法                                    */
/*:\Users\odaka\dl\ch2>learnstock<ldata.txt */
/********************************************/

/*和Visual Studio的互换性保证 */
#define _CRT_SECURE_NO_WARNINGS

/*Include头文件*/
#include <stdio.h>
#include <stdlib.h>

/* 符号常数的定义             */
#define OK 1 
#define NG 0
#define SETSIZE 100 /*学习数据集的大小*/
#define CNO 10 /*学习数据的位数（10）*/
#define GENMAX  10000 /*生成候选解的次数*/
#define SEED 32767 /*随机数的seed*/

/* 函数原型声明   */
void readdata(int data[SETSIZE][CNO],int teacher[SETSIZE]) ;
           /*读入学习数据集*/
int rand012() ;/*返回0、1、2的随机函数*/
int calcscore(int data[SETSIZE][CNO],int teacher[SETSIZE],
              int answer[CNO]) ;
           /*计算候选解模式的得分（0～SETSIZE）*/


/****************/
/*  main()函数  */
/****************/
int main()
{
 int i, j;
 int score = 0;/*得分（0～SETSIZE）*/
 int answer[CNO];/*候选解*/
 int data[SETSIZE][CNO];/*学习数据集*/
 int teacher[SETSIZE];/*教师数据*/
 int bestscore = 0;/*得分的最优值*/
 int bestanswer[CNO];/*搜索过程中的最优解*/

 srand(SEED);/*随机数的初始化*/

 /*读入学习数据集*/
 readdata(data,teacher) ;

 /*生成候选解并检查*/
 for (i = 0; i<GENMAX; ++i) {
  /*生成候选解*/
  for (j = 0; j<CNO; ++j) {
   answer[j] = rand012();
  }

  /*检查*/
  score=calcscore(data,teacher,answer) ;

  /*最优得分的更新*/
  if (score>bestscore) {/*如果是到目前为止的最优值则更新*/
   for (j = 0; j<CNO; ++j)
    bestanswer[j] = answer[j];
   bestscore = score;
   for (j = 0; j<CNO; ++j)
    printf("%1d ", bestanswer[j]);
   printf(":score=%d\n", bestscore);
  }
 }
 /*输出最优解*/
 printf("\n最优解\n");
 for (j = 0; j<CNO; ++j)
  printf("%1d ", bestanswer[j]);
 printf(":score=%d\n", bestscore);

 return 0;
}

/**********************************************/
/*            calcscore()函数                 */
/*候选解模式的得分（0～SETSIZE）的计算        */
/**********************************************/
int calcscore(int data[SETSIZE][CNO],int teacher[SETSIZE],
              int answer[CNO])
{
 int score = 0;/*得分（0～SETSIZE）*/
 int point  ;/*相一致的位数(0～CNO)*/
 int i,j ;
 
for (i = 0; i<SETSIZE; ++i) {
  /*计算一致程度*/
  point = 0;
  for (j = 0; j<CNO; ++j) {
   if (answer[j] == 2) ++point;/*通配符*/
   else if (answer[j] == data[i][j]) ++point;/*相一致*/
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
/*     readdata()函数       */
/*读入学习数据集            */
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
/*     rand012()函数        */
/*返回0、1、2的随机函数     */
/****************************/
int rand012()
{
 int rnd ;
 
 /*去除随机数的最大值*/
 while((rnd=rand())==RAND_MAX) ;
 /*计算随机数*/ 
 return (double)rnd/RAND_MAX*3 ;

}

