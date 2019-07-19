/*********************************************************/
/*                      ae.c                             */
/*自编码器                                               */
/* 使用方法                                              */
/*  \Users\odaka\dl\ch5>ae < data.txt                    */
/*输出误差的变化、作为学习结果的连接系数等               */
/*********************************************************/

/*Visual Studio互换性保证 */
#define _CRT_SECURE_NO_WARNINGS

/* Include头文件*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


/*符号常数的定义*/
#define INPUTNO 9  /*输入层的神经元数*/ 
#define HIDDENNO 2  /*中间层的神经元数*/ 
#define OUTPUTNO 9  /*输出层的神经元数*/
#define ALPHA  10  /*学习系数*/ 
#define SEED 65535    /*随机数的种子*/ 
#define MAXINPUTNO 100    /*学习数据的最大个数*/ 
#define BIGNUM 100    /*误差的初始值*/ 
#define LIMIT 0.0001   /*误差的上限值*/ 

/*函数原型声明*/
double f(double u) ; /*传递函数（sigmoid函数）*/
void initwh(double wh[HIDDENNO][INPUTNO+1]) ;
                         /*中间层权重的初始化*/
void initwo(double wo[HIDDENNO+1]) ;/*输出层权重的初始化*/
double drnd(void) ;/* 随机数的生成     */
void print(double wh[HIDDENNO][INPUTNO+1]
          ,double wo[OUTPUTNO][HIDDENNO+1]) ; /*结果的输出*/
double forward(double wh[HIDDENNO][INPUTNO+1]
         ,double wo[HIDDENNO+1],double hi[]
         ,double e[]) ; /*前向计算*/
void olearn(double wo[HIDDENNO+1],double hi[]
         ,double e[],double o,int k) ; /*输出层权重的调整*/
int getdata(double e[][INPUTNO+OUTPUTNO]) ; /*读入学习数据*/
void hlearn(double wh[HIDDENNO][INPUTNO+1]
         ,double wo[HIDDENNO+1],double hi[]
         ,double e[],double o,int k) ; /*中间层权重的调整*/

/*******************/ 
/*    main()函数   */ 
/*******************/ 
int main()
{
 double wh[HIDDENNO][INPUTNO+1] ;/*中间层的权重*/
 double wo[OUTPUTNO][HIDDENNO+1] ;/*输出层的权重*/
 double e[MAXINPUTNO][INPUTNO+OUTPUTNO] ;/*学习数据集*/
 double hi[HIDDENNO+1] ;/*中间层的输出*/
 double o[OUTPUTNO] ;/*输出*/
 double err=BIGNUM ;/*误差的评价*/
 int i,j,k ;/*循环的控制*/
 int n_of_e ;/*学习数据的个数*/
 int count=0 ;/*循环次数的计数*/

 /*随机数的初始化*/
 srand(SEED) ;

 /*权重的初始化*/
 initwh(wh) ;/*中间层权重的初始化*/
 for(i=0;i<OUTPUTNO;++i)
  initwo(wo[i]) ; /*输出层权重的初始化*/
 print(wh,wo) ; /*结果的输出*/

 /*读入学习数据*/
 n_of_e=getdata(e) ;
 printf("学习数据的个数:%d\n",n_of_e) ;

 /*学习*/
 while(err>LIMIT){
  /*对于与多个输出神经元*/
  for(k=0;k<OUTPUTNO;++k){
   err=0.0 ;
   for(j=0;j<n_of_e;++j){
    /*前向计算*/
    o[k]=forward(wh,wo[k],hi,e[j]) ;
    /*输出层权重的调整*/
    olearn(wo[k],hi,e[j],o[k],k) ;
    /*中间层权重的调整*/
    hlearn(wh,wo[k],hi,e[j],o[k],k) ;
    /*误差的累积*/
    err+=(o[k]-e[j][INPUTNO+k])*(o[k]-e[j][INPUTNO+k]) ;
   }
   ++count ;
   /*误差的输出*/
   fprintf(stderr,"%d\t%lf\n",count,err) ;
   /*多个输出层神经元的对应部分结束*/
  }
 }/*学习结束*/

 /*输出连接权重*/
 print(wh,wo) ; 

 /*输出对于学习数据的计算结果*/
 for(i=0;i<n_of_e;++i){
  printf("%d ",i) ;
  for(j=0;j<INPUTNO+OUTPUTNO;++j)
   printf("%.3lf ",e[i][j]) ;
  printf("\t") ;
  for(j=0;j<OUTPUTNO;++j)
   printf("%.3lf ",forward(wh,wo[j],hi,e[i])) ;
  printf("\n") ;
 }

 return 0 ;
}

/**********************/
/*  hlearn()函数      */
/*  中间层权重的学习  */
/**********************/
void hlearn(double wh[HIDDENNO][INPUTNO+1]
    ,double wo[HIDDENNO+1]
    ,double hi[],double e[],double o,int k)
{
 int i,j ;/*循环的控制*/
 double dj ;/*用于中间层的权重计算*/

 for(j=0;j<HIDDENNO;++j){/*以中间层各神经元j为对象*/
  dj=hi[j]*(1-hi[j])*wo[j]*(e[INPUTNO+k]-o)*o*(1-o) ;
  for(i=0;i<INPUTNO;++i)/*处理第i个权重*/
   wh[j][i]+=ALPHA*e[i]*dj ;
  wh[j][i]+=ALPHA*(-1.0)*dj ;/*阈值的学习*/
 }
}


/**********************/
/*  getdata()函数     */
/*读入学习数据        */
/**********************/
int getdata(double e[][INPUTNO+OUTPUTNO])
{
 int n_of_e=0 ;/*数据集的个数*/
 int j=0 ;/*循环的控制用*/

 /*数据的输入*/
 while(scanf("%lf",&e[n_of_e][j])!=EOF){
  ++ j ;
  if(j>=INPUTNO+OUTPUTNO){/*下一个数据*/
   j=0 ;
   ++n_of_e ;
  }
 }

 return n_of_e ;
}

/**********************/
/*  olearn()函数      */
/*  输出层的权重学习  */
/**********************/
void olearn(double wo[HIDDENNO+1]
    ,double hi[],double e[INPUTNO+1],double o,int k)
{
 int i ;/*循环的控制*/
 double d ;/*用于权重计算*/

 d=(e[INPUTNO+k]-o)*o*(1-o) ;/*误差的计算*/
 for(i=0;i<HIDDENNO;++i){
  wo[i]+=ALPHA*hi[i]*d ;/*权重的学习*/
 }
 wo[i]+=ALPHA*(-1.0)*d ;/*阈值的学习*/
 
} 


/**********************/
/*  forward()函数     */
/*  前向计算          */
/**********************/
double forward(double wh[HIDDENNO][INPUTNO+1]
 ,double wo[HIDDENNO+1],double hi[],double e[INPUTNO+1])
{
 int i,j ;/*循环的控制*/
 double u ;/*加权和的计算*/
 double o ;/*输出的计算*/

 /*hi的计算*/
 for(i=0;i<HIDDENNO;++i){
  u=0 ;/*求取加权和*/
  for(j=0;j<INPUTNO;++j)
   u+=e[j]*wh[i][j] ; 
  u-=wh[i][j] ;/*阈值的处理*/
  hi[i]=f(u) ;
 }
 /*输出o的计算*/
 o=0 ;
 for(i=0;i<HIDDENNO;++i)
  o+=hi[i]*wo[i] ;
 o-=wo[i] ;/*阈值的处理*/
 
 return f(o) ;
} 

/**********************/
/*   print()函数      */
/*   结果的输出       */
/**********************/
void print(double wh[HIDDENNO][INPUTNO+1]
          ,double wo[OUTPUTNO][HIDDENNO+1])
{
 int i,j ;/*循环的控制*/

 for(i=0;i<HIDDENNO;++i){
  for(j=0;j<INPUTNO+1;++j)
   printf("%.3lf ",wh[i][j]) ;
  printf("\n") ;
 } 
 printf("\n") ;
 for(i=0;i<OUTPUTNO;++i){
  for(j=0;j<HIDDENNO+1;++j)
   printf("%.3lf ",wo[i][j]) ;
  printf("\n") ;
 }
 printf("\n") ;
} 

/**********************/
/*    initwh()函数    */
/*中间层权重的初始化  */
/**********************/
void initwh(double wh[HIDDENNO][INPUTNO+1])
{
 int i,j ;/*循环的控制*/

 /*基于随机数确定权重*/ 
 for(i=0;i<HIDDENNO;++i)
  for(j=0;j<INPUTNO+1;++j)
   wh[i][j]=drnd() ;
} 

/**********************/
/*    initwo()函数    */
/*输出层权重的初始化*/
/**********************/
void initwo(double wo[HIDDENNO+1])
{
 int i ;/*循环的控制*/

 /*基于随机数确定权重*/
 for(i=0;i<HIDDENNO+1;++i)
   wo[i]=drnd() ;
} 

/*******************/
/* drnd()函数      */
/* 生成随机数      */
/*******************/
double drnd(void)
{
 double rndno ;/*生成的随机数*/

 while((rndno=(double)rand()/RAND_MAX)==1.0) ;
 rndno=rndno*2-1 ;/*生成-1到1间的随机数*/
 return rndno; 
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



