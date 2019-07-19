/*************************************************/
/*           tow2gram.c                          */
/*  由makew1gram.c程序的输出                     */
/*  结果生成单词2-gram                           */
/* 使用方法                                      */
/*C:\Users\odaka\ch2>makew1gram<t.txt|tow2gram   */
/*************************************************/

/*和Visual Studio的互换性保证 */
#define _CRT_SECURE_NO_WARNINGS

/*Include头文件*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 符号常数的定义             */
#define N 256 /*单词1-gram的字节长*/


/****************/
/* main()函数  */
/****************/
int main()
{
 char w1[N]="",w2[N]="" ;/*输入的单词（1-gram）*/

 /*读入数据后输出单词2-gram*/
 while(scanf("%s",w2)!=EOF){
  printf("%s->%s\n",w1,w2) ;
  strncpy(w1,w2,N) ;/* 保存输入的单词*/
 }

 return 0 ;
}

