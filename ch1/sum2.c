/******************************/
/*          sum2.c            */
/*       求和、求平方和       */
/* 由标准输入读取实数         */
/* 依次输出和及平方和         */
/* 由Ctrl+Z终止程序           */
/* 使用方法                   */
/* C:\Users\odaka\dl\ch1>sum2 */
/******************************/

/*和Visual Studio的互换性保证*/
#define _CRT_SECURE_NO_WARNINGS

/*Include头文件*/
#include <stdio.h>
#include <stdlib.h>

/* 符号常数的定义             */
#define BUFSIZE 256  /*输入缓存大小*/

/****************/
/*  main()函数  */
/****************/
int main()
{
 char linebuf[BUFSIZE] ;/*输入缓存*/
 double data ;/*输入数据*/
 double sum=0.0 ;/*和*/
 double sum2=0.0 ;/*平方和*/

 while(fgets(linebuf,BUFSIZE,stdin)!=NULL){
  /*在可以读取行时重复进行*/
  if(sscanf(linebuf,"%lf",&data)!=0){/*能够变换时*/
    sum+=data ;
    sum2+=data*data ;
    printf("%lf\t%lf\n",sum,sum2) ;
  }
 }

 return 0 ;
}
