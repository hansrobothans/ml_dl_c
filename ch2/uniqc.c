/*********************************************/
/*           uniqc.c                         */
/*  对重复行计数                             */
/*　删除重复行，表示重复次数                 */
/* 使用方法                                  */
/*C:\Users\odaka\ch2>uniqc < text.txt        */
/*********************************************/

/*和Visual Studio的互换性保证 */
#define _CRT_SECURE_NO_WARNINGS

/*include头文件*/
#include <stdio.h>
#include <stdlib.h>
#include<string.h>

/* 符号常数的定义             */
#define MAXLINE 65535 

/****************/
/*  main()函数  */
/****************/
int main()
{
 char newline[MAXLINE] ;/*输入行*/
 char oldline[MAXLINE] ;/*前一行*/
 int count=1 ;/*重复次数*/

 /*读入文本*/
 fgets(oldline,MAXLINE,stdin) ;
 while(fgets(newline,MAXLINE,stdin)!=NULL){
  if(strcmp(newline,oldline)==0) ++count ;/*相同的行*/
  else{/*不同的行*/
   printf("%d\t%s",count,oldline);
   count=1 ;
   strcpy(oldline,newline) ;
  }
 }
 printf("%d\t%s",count,oldline);

 return 0 ;
}