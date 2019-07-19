/*********************************************************/
/*                   cp.c                                */
/*             卷积和池化处理                            */
/*读入2维数据，实施卷积和池化                            */
/* 使用方法                                              */
/*  \Users\odaka\dl\ch5>cp < data1.txt                   */
/*********************************************************/

/*Visual Studio互换性保证 */
#define _CRT_SECURE_NO_WARNINGS

/* Include头文件*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


/*符号常数的定义*/
#define INPUTSIZE 11  /*输入数*/ 
#define FILTERSIZE 3 /*滤波器的大小*/
#define POOLSIZE 3 /*池的大小*/
#define POOLOUTSIZE 3/*池化输出大小*/
/*函数原型声明*/
void conv(double filter[][FILTERSIZE]
   ,double e[][INPUTSIZE]
   ,double convout[][INPUTSIZE]) ; /*卷积计算*/
double calcconv(double filter[][FILTERSIZE]
               ,double e[][INPUTSIZE],int i,int j) ;
                               /*  应用滤波器  */
void convres(double convout[][INPUTSIZE]) ;
              /*卷积结果的输出*/
void pool(double convout[][INPUTSIZE]
         ,double poolout[][POOLOUTSIZE]) ; 
             /*池化计算*/           
double maxpooling(double convout[][INPUTSIZE]
                 ,int i,int j) ;/* 最大值池化 */
void poolres(double poolout[][POOLOUTSIZE]) ;/*结果的输出*/
void getdata(double e[][INPUTSIZE]) ;/*读入数据*/ 
         
/*******************/ 
/*    main()函数   */ 
/*******************/ 
int main()
{
 double filter[FILTERSIZE][FILTERSIZE]
//      ={{0,0,0},{1,1,1},{0,0,0}} ;/*横向滤波器*/
        ={{0,1,0},{0,1,0},{0,1,0}} ;/*纵向滤波器*/
 double e[INPUTSIZE][INPUTSIZE] ;/*输入数据*/
 double convout[INPUTSIZE][INPUTSIZE]={0} ;/*卷积输出*/
 double poolout[POOLOUTSIZE][POOLOUTSIZE] ;/*输出数据*/
 int i,j ;/*循环控制*/
 
 /*读入输入数据*/
 getdata(e) ;
 
 /*卷积计算*/
 conv(filter,e,convout) ;
 convres(convout) ;
 
 /*池化计算*/
 pool(convout,poolout) ;
 /*结果的输出*/
 poolres(poolout) ;
 
 return 0 ;
}

/**********************/
/*  poolres()函数     */
/* 结果的输出         */
/**********************/
void poolres(double poolout[][POOLOUTSIZE]) 
{
 int i,j ;/*循环的控制*/
 
 for(i=0;i<POOLOUTSIZE;++i){
  for(j=0;j<POOLOUTSIZE;++j){
   printf("%.3lf ",poolout[i][j]) ;
  }
  printf("\n") ;
 }
 printf("\n") ;	
} 
 
/**********************/
/*  pool()函数        */
/* 池化计算           */
/**********************/
void pool(double convout[][INPUTSIZE]
         ,double poolout[][POOLOUTSIZE]) 
{
 int i,j ;/*循环的控制*/

 for(i=0;i<POOLOUTSIZE;++i)
  for(j=0;j<POOLOUTSIZE;++j)
   poolout[i][j]=maxpooling(convout,i,j) ;
}
 
/**********************/
/* maxpooling()函数   */
/* 最大值池化         */
/**********************/
double maxpooling(double convout[][INPUTSIZE]
                 ,int i,int j)
{
 int m,n ;/*循环的控制用*/
 double max ;/*最大值*/
 int halfpool=POOLSIZE/2 ;/*池化大小的1/2*/
 
 max
 =convout[i*POOLOUTSIZE+1+halfpool][j*POOLOUTSIZE+1+halfpool];
 for(m=POOLOUTSIZE*i+1;m<=POOLOUTSIZE*i+1+(POOLSIZE-halfpool);++m)
  for(n=POOLOUTSIZE*j+1;n<=POOLOUTSIZE*j+1+(POOLSIZE-halfpool);++n)
   if(max<convout[m][n]) max=convout[m][n] ;

 return max ;
}


/**********************/
/*  convres()函数     */
/* 卷积结果的输出     */
/**********************/
void convres(double convout[][INPUTSIZE]) 
{
 int i,j ;/*循环的控制*/
 
 for(i=1;i<INPUTSIZE-1;++i){
  for(j=1;j<INPUTSIZE-1;++j){
   printf("%.3lf ",convout[i][j]) ;
  }
  printf("\n") ;
 }
 printf("\n") ;	
} 
              
/**********************/
/*  getdata()函数     */
/*读入数据数据        */
/**********************/
void getdata(double e[][INPUTSIZE])
{
 int i=0,j=0 ;/*循环的控制用*/

 /*数据的输入*/
 while(scanf("%lf",&e[i][j])!=EOF){
  ++ j ;
  if(j>=INPUTSIZE){/*下一个数据*/
   j=0 ;
   ++i ;
   if(i>=INPUTSIZE) break ;/*输入结束*/
  }
 }
}

/**********************/
/*  conv()函数        */
/*  卷积计算          */
/**********************/
void conv(double filter[][FILTERSIZE]
         ,double e[][INPUTSIZE],double convout[][INPUTSIZE])
{
 int i=0,j=0 ;/*循环的控制用*/
 int startpoint=FILTERSIZE/2 ;/*卷积范围的下限*/

 for(i=startpoint;i<INPUTSIZE-startpoint;++i)
  for(j=startpoint;j<INPUTSIZE-startpoint;++j)
   convout[i][j]=calcconv(filter,e,i,j) ;
}

/**********************/
/*  calcconv()函数    */
/*  滤波器的应用      */
/**********************/
double calcconv(double filter[][FILTERSIZE]
             ,double e[][INPUTSIZE],int i,int j)
{
 int m,n ;/*循环的控制用*/
 double sum=0 ;/*和的值*/
 
 for(m=0;m<FILTERSIZE;++m)
  for(n=0;n<FILTERSIZE;++n)
   sum+=e[i-FILTERSIZE/2+m][j-FILTERSIZE/2+n]*filter[m][n];
   
 return sum ;
}

