/*************************************************/
/*           makew1gram.c                        */
/*  Shift_JIS 汉字编码文字的单词1-gram生成器     */
/*　从Shift_JIS记述的文件中仅提取全角            */
/*  数据并生成单词的1-gram                       */
/* 使用方法                                      */
/*C:\Users\odaka\ch2>makew1gram < text1.txt      */
/*************************************************/

/*和Visual Studio的互换性保证 */
#define _CRT_SECURE_NO_WARNINGS

/* Include头文件*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 符号常数的定义            */
#define TRUE 1 
#define FALSE 0
#define KANJI 0 /*字种是汉字*/
#define KATAKANA 1/*字种是片假名*/
#define KUTOUTEN 2/*字种是标点符号*/
#define SONOTA 3 /* 字种是上述之外*/

/* 函数原型的声明   */
int is2byte(int chr) ;/*判断是否是全角文字的第一个字节*/
int typep(int chr1,int chr2) ;/*字种的判定*/

/****************/
/* main()函数   */
/****************/
int main()
{
 int chr1,chr2 ;/*输入文字*/
 int now,last=-1 ;/*记忆字种*/

 /*读入数据后以一个文字一个文字的方式输出*/
 while((chr1=getchar())!=EOF){
  if(is2byte(chr1)==TRUE){
   chr2=getchar() ;
   now=typep(chr1,chr2) ;

   /*输出全角（2字节）*/
   if(now!=last){
    putchar('\n') ;/*切分1-gram*/
    last=now ;
   }
   putchar(chr1) ;
   putchar(chr2) ;
  }
 }

 return 0 ;
}

/*******************************/
/*   typep()函数               */
/*　字种的判定                 */
/*******************************/
int typep(int chr1,int chr2)
{
 char chr[3]="　" ;/*标点符号判定用*/

 chr[0]=chr1 ; chr[1]=chr2 ; /*文字的设定*/
 /*字种的判定*/
 if(chr1>=0x88)
  return KANJI ;/*汉字*/
 else if((chr1==0x83)&&(chr2>=0x40)&&(chr2<=0x96))  
  return KATAKANA ;/*片假名*/
 else if((strncmp(chr,"。",2) ==0) ||
         (strncmp(chr,"．",2) ==0) ||
         (strncmp(chr,"、",2) ==0) ||
         (strncmp(chr,"，",2) ==0))
  return KUTOUTEN ;/*标点符号*/
 return SONOTA ;/*其它*/
}

/*******************************/
/*  is2byte()函数              */
/*判断是否是全角文字的第一个字节*/
/*******************************/
int is2byte(int c)
{
 if(((c>0x80)&&(c<0xA0))||(c>0xDF)&&(c<0xF0))
  return TRUE ;/*2字节文字*/
 return FALSE ;/* 1字节文字*/
}