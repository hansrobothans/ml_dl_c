/*********************************************/
/*           make3gram.c                     */
/*  Shift_JIS 汉字编码文字的3-gram生成器     */
/*　    从Shift_JIS记述的文件中仅提取        */
/*      全角数据并生成3-gram                 */
/* 使用方法                                    */
/*C:\Users\odaka\ch2>make3gram <text1.txt    */
/*********************************************/

/*和Visual Studio的互换性保证 */
#define _CRT_SECURE_NO_WARNINGS

/*Include头文件*/
#include <stdio.h>
#include <stdlib.h>

/*  符号常数的定义             */
#define TRUE 1 
#define FALSE 0
#define N 6 /*n-gram的n的2倍*/

/* 函数原型的声明   */
int is2byte(int chr) ;/*判断是否是全角文字的第一个字节*/
void put3gram(int chr) ;/*输出3-gram*/
int invert(int flag) ;/*反转flag*/

/****************/
/*  main()函数  */
/****************/
int main()
{
 int chr ;/*输入文字*/

 /*读入数据后以一个文字一个文字的方式输出*/
 while((chr=getchar())!=EOF){
  if(is2byte(chr)==TRUE){
   /*根据put3gram()函数输出*/
   put3gram(chr) ;
   put3gram(getchar()) ;
  }
 }

 return 0 ;
}

/*******************************/
/*   invett()函数              */
/*　 反转flag                  */
/*******************************/
int invert(int flag)
{
 if(flag==FALSE)
  return TRUE ;
 return FALSE ;
}


/*******************************/
/*  put3gram()函数             */
/*  输出3-gram               */
/*******************************/
void put3gram(int c)
{
 static char queue[N]="　　　" ;/*用于输出的队列*/
 static int flag=FALSE ;/*关于输出的时间控制*/
 int i;/*循环控制*/

 /*向队列中添加数据*/
 for(i=0;i<N-1;++i)
  queue[i]=queue[i+1] ;
 queue[N-1]=c ;/*添加数据*/ 

 /*如果是2字节分割，就输出*/
 if(flag==TRUE){
  for(i=0;i<N;++i)
   putchar(queue[i]) ; 
  putchar('\n') ;
 }
 /*反转flag*/
 flag=invert(flag) ;
}


/*******************************/
/*   is2byte()函数              */
/*判断是否是全角文字的第一个字节*/
/*******************************/
int is2byte(int c)
{
 if(((c>0x80)&&(c<0xA0))||(c>0xDF)&&(c<0xF0))
  return TRUE ;/*2字节文字*/
 return FALSE ;/*1字节文字*/
}

