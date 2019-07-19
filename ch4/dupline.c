/*********************************************/
/*           dupline.c                       */
/*  复制第2行之后的输入行                    */
/* 使用方法                                  */
/*C:\Users\odaka\ch4>dupline < text1.txt   */
/*********************************************/

/*和Visual Studio的互换性保证 */
#define _CRT_SECURE_NO_WARNINGS

/* 定义符号常数             */
#define MAXSIZE 4096 /*1行的最大长度*/ 

/*include头文件*/
#include <stdio.h>
#include <stdlib.h>

/****************/
/*  main()函数  */
/****************/
int main()
{
 char line[MAXSIZE] ;/*输入行*/

 /*读入最初行并原样输出*/
 fgets(line,MAXSIZE,stdin) ;
 printf("%s",line) ;

 /*复制第2行之后的行*/
 while(fgets(line,MAXSIZE,stdin)!=NULL){
  printf("%s",line) ;
  printf("%s",line) ;
 }

 return 0 ;
}