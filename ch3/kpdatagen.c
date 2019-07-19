/****************************************/
/*              kpdatagen.c             */
/*         背包问题的数据生成机         */
/* 随机生成行李的重量、价值             */
/*使用方法                              */
/*\Users\odaka\dl\ch3>kpdatagen>data.txt*/
/****************************************/


/*和Visual Studio的互换性保证 */
#define _CRT_SECURE_NO_WARNINGS

/*Include头文件*/
#include <stdio.h>
#include <stdlib.h>

/*   符号常数的定义                 */
#define MAXVALUE 100 /*重量和价值的最大值*/
#define N 30 /*行李个数*/
#define SEED 32768 /*随机数的seed*/

/*   函数原型声明      */
int randdata() ;
    /*返回MAXVALUE以下的整数的随机函数*/

/****************/
/*  main()函数  */
/****************/
int main()
{
 int i ;

 srand(SEED) ;
 for(i=0;i<N;++i)
  printf("%ld %ld\n",randdata(),randdata()) ;
 return 0 ;
}

/**********************************/
/*     randdata()函数             */
/*返回MAXVALUE以下的整数的随机函数*/
/**********************************/
int randdata()
{
 int rnd ;
 
 /*去除随机数的最大值*/
 while((rnd=rand())==RAND_MAX) ;
 /*随机数的计算*/ 
 return (int)((double)rnd/RAND_MAX*MAXVALUE+1) ;

}
