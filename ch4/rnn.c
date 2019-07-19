/*********************************************************/
/*                   rnn.c　　                           */
/*　               循环神经网络                          */
/*　              基于反向传播学习                       */
/* 使用方法　                                            */
/*  \Users\odaka\ch4>rnn < data.txt 　                   */
/*　输出误差的变化过程及作为学习结果的连接系数等         */
/*********************************************************/

/*和Visual Studio的互换性保证 */
#define _CRT_SECURE_NO_WARNINGS

/* include头文件*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*定义符号常数*/
#define INPUTNO 5  /*输入的元素数*/
#define HIDDENNO 5  /*中间层神经元数*/
#define OUTPUTNO 5  /*输出层神经元数*/
#define ALPHA  10  /*学习系数*/
#define SEED 65535    /*随机数的种子*/
//#define SEED 7    /*随机数的种子（其他值）*/
#define MAXINPUTNO 100    /*学习数据的最大个数*/
#define BIGNUM 100    /*误差的初始值*/
#define LIMIT 0.01   /*误差的上限值*/

/*函数原型的声明*/
double f(double u) ; /*传递函数（sigmoid函数）*/
void initwh(double wh[HIDDENNO][INPUTNO+1+HIDDENNO]) ;
                         /*中间层权重的初始化*/
void initwo(double wo[HIDDENNO+1]) ;/*输出层权重的初始化*/
double drnd(void) ;/* 生成随机数     */
void print(double wh[HIDDENNO][INPUTNO+1+HIDDENNO]
          ,double wo[OUTPUTNO][HIDDENNO+1]) ; /*输出结果*/
double forward(double wh[HIDDENNO][INPUTNO+1+HIDDENNO]
         ,double wo[HIDDENNO+1],double hi[]
         ,double e[]) ; /*前向计算*/
void olearn(double wo[HIDDENNO+1],double hi[]
         ,double e[],double o,int k) ; /*输出层权重的调整*/
int getdata(double e[][INPUTNO+OUTPUTNO+HIDDENNO]) ; /*读入学习数据*/
void hlearn(double wh[HIDDENNO][INPUTNO+1+HIDDENNO]
         ,double wo[HIDDENNO+1],double hi[]
         ,double e[],double o,int k) ; /*中间层权重的调整*/

/*******************/
/*    main()函数   */
/*******************/
int main()
{
 double wh[HIDDENNO][INPUTNO+1+HIDDENNO] ;/*中间层权重*/
 double wo[OUTPUTNO][HIDDENNO+1] ;/*输出层权重*/
 double e[MAXINPUTNO][INPUTNO+OUTPUTNO+HIDDENNO] ;/*学习数据集*/
 double hi[HIDDENNO+1]={0} ;/*中间层的输出*/
 double o[OUTPUTNO] ;/*输出*/
 double err=BIGNUM ;/*误差评估*/
 int i,j,k ;/*循环控制用*/
 int n_of_e ;/*学习数据的个数*/
 int count=0 ;/*循环次数计数*/
 double errsum=BIGNUM ;/*误差的累计*/

 /*初始化随机数*/
 srand(SEED) ;

 /*初始化权重*/
 initwh(wh) ;/*初始化中间层权重*/
 for(i=0;i<OUTPUTNO;++i)
  initwo(wo[i]) ; /*初始化输出层权重*/

 /*读入学习数据*/
 n_of_e=getdata(e) ;
 fprintf(stderr,"学習データの個数:%d\n",n_of_e) ;

 /*学习*/
 while(errsum>LIMIT){
  /*对应多个输出层*/
  errsum=0 ;
  for(k=0;k<OUTPUTNO;++k){
   err=0.0 ;
   for(j=0;j<n_of_e;++j){
    /*将前一层中间层的输出追加到输入中*/
    for(i=0;i<HIDDENNO;++i)
      e[j][INPUTNO+i]=hi[i] ;
    /*前向计算*/
    o[k]=forward(wh,wo[k],hi,e[j]) ;
    /*输出层权重的调整*/
    olearn(wo[k],hi,e[j],o[k],k) ;
    /*中间层权重的调整*/
    hlearn(wh,wo[k],hi,e[j],o[k],k) ;
    /*误差的累积*/
    err+=(o[k]-e[j][INPUTNO+k+HIDDENNO])*(o[k]-e[j][INPUTNO+k+HIDDENNO]) ;
   }
   ++count ;
   /*误差的合计值*/
   errsum+=err ;
   /*对应多个输出层结束*/
  }
  /*输出误差*/
  fprintf(stderr,"%d\t%lf\n",count,errsum) ;  
 }/*学习结束*/

 /*输出连接权重*/
 print(wh,wo) ;

 /*输出学习数据的计算结果*/
 for(i=0;i<n_of_e;++i){
  fprintf(stderr,"%d:\n",i) ;
  for(j=0;j<INPUTNO+HIDDENNO;++j)
   fprintf(stderr,"%.3lf ",e[i][j]) ;
  fprintf(stderr,"\n") ;
  for(j=INPUTNO+HIDDENNO;j<INPUTNO+OUTPUTNO+HIDDENNO;++j)
   fprintf(stderr,"%.3lf ",e[i][j]) ;
  fprintf(stderr,"\n") ;
  for(j=0;j<OUTPUTNO;++j)
   fprintf(stderr,"%.3lf ",forward(wh,wo[j],hi,e[i])) ;
  /*将前一次中间层的输出追加到输入中*/
  if(i<n_of_e-1)
   for(j=0;j<HIDDENNO;++j)
    e[i+1][INPUTNO+j]=hi[j] ;
  fprintf(stderr,"\n") ;
 }

 return 0 ;
}

/**********************/
/*  hlearn()函数      */
/*  中间层权重的学习  */
/**********************/
void hlearn(double wh[HIDDENNO][INPUTNO+1+HIDDENNO]
    ,double wo[HIDDENNO+1]
    ,double hi[],double e[],double o,int k)
{
 int i,j ;/*循环控制用*/
 double dj ;/*用于计算中间层权重*/

 for(j=0;j<HIDDENNO;++j){/*将中间层各神经元j作为对象*/
  dj=hi[j]*(1-hi[j])*wo[j]*(e[INPUTNO+k+HIDDENNO]-o)*o*(1-o) ;
  for(i=0;i<INPUTNO+HIDDENNO;++i)/*处理第i个权重*/
   wh[j][i]+=ALPHA*e[i]*dj ;
  wh[j][i]+=ALPHA*(-1.0)*dj ;/*学习阈值*/
 }
}

/**********************/
/*  getdata()函数     */
/*   读入学习数据     */
/**********************/
int getdata(double e[][INPUTNO+OUTPUTNO+HIDDENNO])
{
 int n_of_e=0 ;/*数据集的个数*/
 int j=0 ;/*循环控制用*/

 /*输入数据*/
 while(scanf("%lf",&e[n_of_e][j])!=EOF){
  ++ j ;
  if(j==INPUTNO) j+=HIDDENNO;/*跳过循环成分读*/
  if(j>=INPUTNO+OUTPUTNO+HIDDENNO){/*下一个数据*/
   j=0 ;
   ++n_of_e ;
   if(n_of_e>=MAXINPUTNO) break ;/*到达数据数的上限*/
  }
 }

 return n_of_e ;
}

/**********************/
/*  olearn()函数      */
/*  学习输出层权重    */
/**********************/
void olearn(double wo[HIDDENNO+1]
    ,double hi[],double e[],double o,int k)
{
 int i ;/*循环控制用*/
 double d ;/*用于计算权重*/

 d=(e[INPUTNO+k+HIDDENNO]-o)*o*(1-o) ;/*计算误差*/
 for(i=0;i<HIDDENNO;++i){
  wo[i]+=ALPHA*hi[i]*d ;/*学习权重*/
 }
 wo[i]+=ALPHA*(-1.0)*d ;/*学习阈值*/
}

/**********************/
/*  forward()函数     */
/*  前向计算          */
/**********************/
double forward(double wh[HIDDENNO][INPUTNO+1+HIDDENNO]
 ,double wo[HIDDENNO+1],double hi[],double e[])
{
 int i,j ;/*循环控制用*/
 double u ;/*计算加权和*/
 double o ;/*计算输出值*/

 /*hi的计算*/
 for(i=0;i<HIDDENNO;++i){
  u=0 ;/*求得加权和*/
  for(j=0;j<INPUTNO+HIDDENNO;++j)
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
/*   print()函数      */
/*   输出结果         */
/**********************/
void print(double wh[HIDDENNO][INPUTNO+1+HIDDENNO]
          ,double wo[OUTPUTNO][HIDDENNO+1])
{
 int i,j ;/*循环控制用*/

 for(i=0;i<HIDDENNO;++i){
  for(j=0;j<INPUTNO+1+HIDDENNO;++j)
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
/* 中间层权重的初始化 */
/**********************/
void initwh(double wh[HIDDENNO][INPUTNO+1+HIDDENNO])
{
 int i,j ;/*循环控制用*/

 /*根据随机数确定权重*/
 for(i=0;i<HIDDENNO;++i)
  for(j=0;j<INPUTNO+1+HIDDENNO;++j)
   wh[i][j]=drnd() ;
}

/**********************/
/*    initwo()函数    */
/* 输出层权重的初始化 */
/**********************/
void initwo(double wo[HIDDENNO+1])
{
 int i ;/*循环控制用*/

 /*根据随机数确定权重*/
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
 rndno=rndno*2-1 ;/*生成-1到1之间的随机数*/
 return rndno;
}

/*******************/
/* f()函数         */
/* 传递函数        */
/*（sigmoid函数）  */
/*******************/
double f(double u)
{
 return 1.0/(1.0+exp(-u)) ;
}