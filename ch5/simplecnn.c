/*********************************************************/
/*               simplecnn.c                             */
/*      卷积神经网络的基本结构演示                       */
/* 表示CNN的基本结构（仅表示其骨架）                     */
/* 使用方法                                              */
/*  \Users\odaka\dl\ch5>simplecnn < data1.txt            */
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
#define FILTERNO 2 /*滤波器的个数*/
#define POOLSIZE 3 /*池化的大小*/
#define POOLOUTSIZE 3/*池化输出的大小*/
#define MAXINPUTNO 100    /*学习数据的最大个数*/ 
#define SEED 65535    /*随机数的种子*/ 
#define LIMIT 0.001    /*误差的上限值*/ 
#define BIGNUM 100    /*误差的初始值*/ 
#define HIDDENNO 3  /*中间层神经元个数*/ 
#define ALPHA  10  /*学习系数*/ 

/*函数原型的声明*/
void conv(double filter[FILTERSIZE][FILTERSIZE]
   ,double e[][INPUTSIZE]
   ,double convout[][INPUTSIZE]) ; /*卷积计算*/
double calcconv(double filter[][FILTERSIZE]
               ,double e[][INPUTSIZE],int i,int j) ;
                               /*  滤波器的应用  */
void pool(double convout[][INPUTSIZE]
         ,double poolout[][POOLOUTSIZE]) ; 
             /*池化计算*/           
double maxpooling(double convout[][INPUTSIZE]
                 ,int i,int j) ;/* 最大值池化 */
int getdata(double e[][INPUTSIZE][INPUTSIZE],int r[]) ;/*读入数据*/ 
void showdata(double e[][INPUTSIZE][INPUTSIZE],int t[]
             ,int n_of_e) ;/*数据表示*/ 
void initfilter(double filter[FILTERNO][FILTERSIZE][FILTERSIZE]) ;
                /*滤波器的初始化*/
double drnd(void) ;/* 随机数的生成     */
double f(double u) ; /*传递函数（sigmoid函数）*/
void initwh(double wh[HIDDENNO][POOLOUTSIZE*POOLOUTSIZE*FILTERNO+1]) ;
                         /*中间层权重的初始化*/
void initwo(double wo[HIDDENNO+1]) ;/*输出层权重的初始化*/
double forward(double wh[HIDDENNO][POOLOUTSIZE*POOLOUTSIZE*FILTERNO+1]
         ,double wo[HIDDENNO+1],double hi[]
         ,double e[POOLOUTSIZE*POOLOUTSIZE*FILTERNO+1]) ; /*前向计算*/
void olearn(double wo[HIDDENNO+1],double hi[]
         ,double e[POOLOUTSIZE*POOLOUTSIZE*FILTERNO+1],double o) ; /*输出层权重的调整*/
void hlearn(double wh[HIDDENNO][POOLOUTSIZE*POOLOUTSIZE*FILTERNO+1]
         ,double wo[HIDDENNO+1],double hi[]
         ,double e[POOLOUTSIZE*POOLOUTSIZE*FILTERNO+1],double o) ; /*中间层权重的调整*/
double f(double u) ; /*传递函数（sigmoid函数）*/
void print(double wh[HIDDENNO][POOLOUTSIZE*POOLOUTSIZE*FILTERNO+1]
          ,double wo[HIDDENNO+1]) ; /*结果的输出*/
          
/*******************/ 
/*    main()函数   */ 
/*******************/ 
int main()
{
 double filter[FILTERNO][FILTERSIZE][FILTERSIZE] ;
                            /*滤波器*/
 double e[MAXINPUTNO][INPUTSIZE][INPUTSIZE] ;/*输入数据*/
 int t[MAXINPUTNO] ;/*教师数据*/
 double convout[INPUTSIZE][INPUTSIZE]={0} ;/*卷积输出*/
 double poolout[POOLOUTSIZE][POOLOUTSIZE] ;/*输出数据*/
 int i,j,m,n ;/*循环的控制*/
 int n_of_e ;/*学习数据的个数*/
 double err=BIGNUM ;/*误差的评价*/
 int count=0 ;/*循环次数的计数*/
 double ef[POOLOUTSIZE*POOLOUTSIZE*FILTERNO+1] ;/*全连接层的输入数据*/
 double o ;/*最终输出*/
 double hi[HIDDENNO+1] ;/*中间层的输出*/
 double wh[HIDDENNO][POOLOUTSIZE*POOLOUTSIZE*FILTERNO+1] ;/*中间层的权重*/
 double wo[HIDDENNO+1] ;/*输出层的权重*/
 
 /*随机数的初始化*/
 srand(SEED) ;
 
 /*滤波器的初始化*/
 initfilter(filter) ;
 
 /*全连接层权重的初始化*/
 initwh(wh) ;/*中间层权重的初始化*/
 initwo(wo) ;/*输出层权重的初始化*/
 
 /*读入输入数据*/
 n_of_e=getdata(e,t) ;
 showdata(e,t,n_of_e) ;
 
  /*学习*/
 while(err>LIMIT){
  err=0.0 ;
  for(i=0;i<n_of_e;++i){/*学习数据的循环*/
   for(j=0;j<FILTERNO;++j){/*滤波器的循环*/
    /*卷积计算*/
    conv(filter[j],e[i],convout) ;
    /*池化计算*/
    pool(convout,poolout) ;
    /*将池化输出复制到全连接层的输入*/
    for(m=0;m<POOLOUTSIZE;++m)
     for(n=0;n<POOLOUTSIZE;++n)
      ef[j*POOLOUTSIZE*POOLOUTSIZE+POOLOUTSIZE*m+n]
           =poolout[m][n] ;
    ef[POOLOUTSIZE*POOLOUTSIZE*FILTERNO]=t[i] ;/*教师数据*/
   }
   /*前向计算*/
   o=forward(wh,wo,hi,ef) ;
   /*输出层权重的调整*/
   olearn(wo,hi,ef,o) ;
   /*中间层权重的调整*/
   hlearn(wh,wo,hi,ef,o) ;
   /*误差的累积*/
   err+=(o-t[i])*(o-t[i]) ;
  }
  ++count ;
  /*误差的输出*/
  fprintf(stderr,"%d\t%lf\n",count,err) ;
 }/*学习结束*/
 
 printf("\n***Results***\n") ;
 /*连接权重的输出*/
 printf("Weights\n") ;
 print(wh,wo) ; 

 /*相对于教师数据的输出*/
 printf("Network output\n") ;
 printf("#\tteacher\toutput\n") ;
 for(i=0;i<n_of_e;++i){
  printf("%d\t%d\t",i,t[i]) ;
  for(j=0;j<FILTERNO;++j){/*滤波器的循环*/
    /*卷积计算*/
    conv(filter[j],e[i],convout) ;
    /*池化计算*/
    pool(convout,poolout) ;
    /*将池化输出复制到全连接层的输入*/
    for(m=0;m<POOLOUTSIZE;++m)
     for(n=0;n<POOLOUTSIZE;++n)
      ef[j*POOLOUTSIZE*POOLOUTSIZE+POOLOUTSIZE*m+n]
           =poolout[m][n] ;
    ef[POOLOUTSIZE*POOLOUTSIZE*FILTERNO]=t[i] ;/*教师数据*/
   }
   o=forward(wh,wo,hi,ef) ;
  printf("%lf\n",o) ;
 }

 return 0 ;
}

/**********************/
/*   print()函数      */
/*   结果的输出       */
/**********************/
void print(double wh[HIDDENNO][POOLOUTSIZE*POOLOUTSIZE*FILTERNO+1]
          ,double wo[HIDDENNO+1])
{
 int i,j ;/*循环的控制*/

 for(i=0;i<HIDDENNO;++i)
  for(j=0;j<POOLOUTSIZE*POOLOUTSIZE*FILTERNO+1;++j)
   printf("%lf ",wh[i][j]) ;
 printf("\n") ;
 for(i=0;i<HIDDENNO+1;++i)
  printf("%lf ",wo[i]) ;
 printf("\n") ;
} 

/**********************/
/*  hlearn()函数      */
/*  中间层的权重学习  */
/**********************/
void hlearn(double wh[HIDDENNO][POOLOUTSIZE*POOLOUTSIZE*FILTERNO+1]
    ,double wo[HIDDENNO+1]
    ,double hi[],double e[POOLOUTSIZE*POOLOUTSIZE*FILTERNO+1],double o)
{
 int i,j ;/*循环的控制*/
 double dj ;/*用于中间层的权重计算*/

 for(j=0;j<HIDDENNO;++j){/*以中间层个神经元j为对象*/
  dj=hi[j]*(1-hi[j])*wo[j]*(e[POOLOUTSIZE*POOLOUTSIZE*FILTERNO]-o)*o*(1-o) ;
  for(i=0;i<POOLOUTSIZE*POOLOUTSIZE*FILTERNO;++i)/*处理第i个权重*/
   wh[j][i]+=ALPHA*e[i]*dj ;
  wh[j][i]+=ALPHA*(-1.0)*dj ;/*阈值的学习*/
 }
}

/**********************/
/*  olearn()函数      */
/*  输出层的权重学习  */
/**********************/
void olearn(double wo[HIDDENNO+1]
    ,double hi[],double e[POOLOUTSIZE*POOLOUTSIZE*FILTERNO+1],double o)
{
 int i ;/*循环的控制*/
 double d ;/*用于权重计算*/

 d=(e[POOLOUTSIZE*POOLOUTSIZE*FILTERNO]-o)*o*(1-o) ;/*误差的计算*/
 for(i=0;i<HIDDENNO;++i){
  wo[i]+=ALPHA*hi[i]*d ;/*权重的学习*/
 }
 wo[i]+=ALPHA*(-1.0)*d ;/*阈值的学习*/
 
} 

/**********************/
/*  forward()函数     */
/*  前向计算          */
/**********************/
double forward(double wh[HIDDENNO][POOLOUTSIZE*POOLOUTSIZE*FILTERNO+1]
 ,double wo[HIDDENNO+1],double hi[],double e[POOLOUTSIZE*POOLOUTSIZE*FILTERNO+1])
{
 int i,j ;/*循环的控制*/
 double u ;/*加权和的计算*/
 double o ;/*输出的计算*/

 /*hi的计算*/
 for(i=0;i<HIDDENNO;++i){
  u=0 ;/*求取加权和*/
  for(j=0;j<POOLOUTSIZE*POOLOUTSIZE*FILTERNO;++j)
   u+=e[j]*wh[i][j] ; 
  u-=wh[i][j] ;/*阈值的处理*/
  hi[i]=f(u) ;
 }
 /*计算输出o*/
 o=0 ;
 for(i=0;i<HIDDENNO;++i)
  o+=hi[i]*wo[i] ;
 o-=wo[i] ;/*阈值的处理*/
 
 return f(o) ;
} 

/**********************/
/*    initwh()函数    */
/*中间层权重的初始化  */
/**********************/
void initwh(double wh[][POOLOUTSIZE*POOLOUTSIZE*FILTERNO+1])
{
 int i,j ;/*循环的控制*/

 /*基于随机数确定权重*/ 
 for(i=0;i<HIDDENNO;++i)
  for(j=0;j<POOLOUTSIZE*POOLOUTSIZE*FILTERNO+1;++j)
   wh[i][j]=drnd() ;
} 

/**********************/
/*    initwo()函数    */
/*输出层权重的初始化  */
/**********************/
void initwo(double wo[])
{
 int i ;/*循环的控制*/

 /*基于随机数确定权重*/
 for(i=0;i<HIDDENNO+1;++i)
   wo[i]=drnd() ;
} 

/**********************/
/*  initfilter()函数  */
/* 滤波器的初始化     */
/**********************/
void initfilter(double filter[FILTERNO][FILTERSIZE][FILTERSIZE])
{
 int i,j,k ;/*循环的控制*/
 
 for(i=0;i<FILTERNO;++i)
  for(j=0;j<FILTERSIZE;++j)
   for(k=0;k<FILTERSIZE;++k)
    filter[i][j][k]=drnd() ;
} 

/*******************/
/* drnd()函数      */
/* 随机数的生成    */
/*******************/
double drnd(void)
{
 double rndno ;/*生成的随机数*/

 while((rndno=(double)rand()/RAND_MAX)==1.0) ;
 rndno=rndno*2-1 ;/*生成从-1到1的随机数*/
 return rndno; 
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
 int m,n ;/*循环控制用*/
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
/* showdata()函数     */
/*输入数据的表示      */
/**********************/
void showdata(double e[][INPUTSIZE][INPUTSIZE],int t[],int n_of_e)
{
 int i=0,j=0,k=0 ;/*循环的控制用*/

 /*数据的表示*/
 for(i=0;i<n_of_e;++i){
  printf("N=%d category=%d\n",i,t[i]) ;
  for(j=0;j<INPUTSIZE;++j){
   for(k=0;k<INPUTSIZE;++k)
    printf("%.3lf ",e[i][j][k]) ;
   printf("\n") ;
  }
  printf("\n") ;
 }
}
             
/**********************/
/*  getdata()函数     */
/*读入输入数据        */
/**********************/
int getdata(double e[][INPUTSIZE][INPUTSIZE],int t[])
{
 int i=0,j=0,k=0 ;/*循环的控制用*/

 /*数据的输入*/
 while(scanf("%d",&t[i])!=EOF){/*读入教师数据*/
  /*读入图像数据*/
  while(scanf("%lf",&e[i][j][k])!=EOF){
   ++ k ;
   if(k>=INPUTSIZE){/*下一个数据*/
    k=0 ;
    ++j ;
    if(j>=INPUTSIZE) break ;/*输入结束*/
   }
  }
  j=0; k=0 ;
  ++i ; 
 }
 return i ;
}

/**********************/
/*  conv()函数        */
/*  卷积计算    */
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

/*******************/
/* f()函数         */
/* 传递函数        */
/*(sigmoid函数)    */
/*******************/
double f(double u)
{
 return 1.0/(1.0+exp(-u)) ;
}

