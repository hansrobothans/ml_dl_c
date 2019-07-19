/*********************************************/
/*           sortn.c                         */
/*  根据行头的数值按顺序排列                 */
/* 使用方法                                  */
/*C:\Users\odaka\ch2>sortn < text.txt        */
/*********************************************/

/*和Visual Studio的互换性保证 */
#define _CRT_SECURE_NO_WARNINGS

/*include头文件*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 符号常数的定义             */
#define LINESIZE 256 /*　一行字节数的上限 */
#define MAX 65536*3 /* 行数的上限 */ 

/* 函数原型的声明   */
int cmpdata(const char *a,const char *b) ; /*比较函数*/

/* 外部变量　*/
char lines[MAX][LINESIZE] ; /*处理对象文本*/

/****************/
/*  main()函数  */
/****************/
int main()
{
 char buffer[LINESIZE] ;/*读入缓存*/
 int pos=0 ;/*读入行数的计数*/
 int i ;
 
 /*读入文本*/
 while(fgets(buffer,LINESIZE,stdin)!=NULL){
   strcpy(lines[pos],buffer) ;
   if((++pos)>=MAX){ 
    fprintf(stderr,
      "ファイルサイズの上限を超えました\n") ;
    exit(1);
   }
  }
 /*按序排列*/
 qsort(lines,pos,LINESIZE,
   (int (*)(const void *,const void *))cmpdata) ;
 /*出力*/
 for(i=0;i<pos;++i)
  printf("%s",lines[i]) ;
  
 return 0;
}

/*******************************/
/*  cmpdata()函数              */
/*　比较函数                   */
/*******************************/
int cmpdata(const char *a,const char *b)
{
 int inta,intb ;

 inta=atoi(a) ;
 intb=atoi(b) ;
 if(inta>intb) return -1;/*第一参数大*/
 else if(inta<intb) return 1 ;/*第二参数大*/

 return 0 ;/*其他*/
}