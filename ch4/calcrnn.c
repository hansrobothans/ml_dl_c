/*********************************************************/
/*                   calcrnn.c　                         */
/*　                 循环神经网络                        */
/*　        学习完成后的神经网络的计算                   */
/* 使用方法                                              */
/*  \Users\odaka\ch4>calcrnn 2 < data.txt 　             */
/*　将开始单词的序号作为命令行的参数给出                 */
/*********************************************************/

/*和Visual Studio的互换性保证 */
#define _CRT_SECURE_NO_WARNINGS

/* include头文件*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*定义符号常数*/
#define INPUTNO 5  /*输入神经元数*/
#define HIDDENNO 5  /*中间层神经元数*/
#define OUTPUTNO 5  /*输出层神经元数*/
#define WORDLEN 50 /*单词词链长度*/

/*函数原型的声明*/
double f(double u) ; /*传递函数（sigmoid函数）*/
void print(double wh[HIDDENNO][INPUTNO+1+HIDDENNO]
          ,double wo[OUTPUTNO][HIDDENNO+1]) ; /*输出结果*/
double forward(double wh[HIDDENNO][INPUTNO+1+HIDDENNO]
         ,double wo[HIDDENNO+1],double hi[]
         ,double e[]) ; /*前向计算*/
void readwh(double wh[HIDDENNO][INPUTNO+1+HIDDENNO]) ;
                         /*读入中间层权重*/
void readwo(double wo[OUTPUTNO][HIDDENNO+1]) ;
                         /*读入输出层权重*/
void  putword(double inputdata[]) ;
       /*仅将单词部分用1-of-N表示*/

/*******************/
/*    main()函数   */
/*******************/
int main(int argc,char *argv[])
{
 double wh[HIDDENNO][INPUTNO+1+HIDDENNO] ;/*中间层权重*/
 double wo[OUTPUTNO][HIDDENNO+1] ;/*输出层权重*/
 double hi[HIDDENNO+1]={0} ;/*中间层的输出*/
 double o[OUTPUTNO] ;/*输出*/
 double inputdata[INPUTNO+HIDDENNO]={0} ;/*输入*/
 int i,j ;/*循环控制用*/
 int startno ; /*开始单词的序号*/

 /*指定开始单词*/
 if(argc<2){
  startno=0 ;/*没有指定时从序号0开始*/
 }
 else{
  startno=atoi(argv[1]) ;
  if((startno<0) || (startno>=INPUTNO)){
   /*指定开始单词错误*/
   fprintf(stderr,"開始単語の指定値(%d)が間違っています\n",startno) ;
   exit(1) ;
  }
 }   
 inputdata[startno]=1.0 ;

 /*读入权重*/
 readwh(wh) ;/*读入中间层权重*/
 readwo(wo) ;/*读入输出层权重*/

 /*文本生成*/
 for(i=0;i<WORDLEN;++i){
  /*表示输入数据*/
  /*有必要的话去掉下面三行的注释符*/
//  for(j=0;j<INPUTNO+HIDDENNO;++j)
//   printf("%.3lf ",inputdata[j]) ;
//  printf("\n") ;
  /*将单词部分用1-of-N表示*/
  putword(inputdata) ;
  /*前向计算*/
  for(j=0;j<OUTPUTNO;++j)
   o[j]=forward(wh,wo[j],hi,inputdata) ;
  /*将前一次的输出设定为输入*/
  for(j=0;j<HIDDENNO;++j)
    inputdata[j]=o[j] ;
  /*前一次中间层的输出追加到输入中*/
  for(j=0;j<HIDDENNO;++j)
    inputdata[INPUTNO+j]=hi[j] ;
 }

 return 0 ;
}

/********************************/
/*   putword()函数              */
/*将单词部分用1-of-N表示        */
/********************************/
void  putword(double inputdata[])
{
 int i ;/*循环控制用*/
 int maxindex=0 ;/*最大元素值的序号*/
 double max=inputdata[0] ;/*最大值*/

 /*调查最大的元素*/
 for(i=1;i<INPUTNO;++i)
  if(max<inputdata[i]){
   max=inputdata[i] ;
   maxindex=i ;
  }
 /*输出1-of-N表示的单词*/
 for(i=0;i<INPUTNO;++i){
  if(i==maxindex) printf("1 ") ;
  else printf("0 ") ;
 }
 printf("\n") ;

}

/**********************/
/*  forward()函数     */
/*  前向计算          */
/**********************/
double forward(double wh[HIDDENNO][INPUTNO+1+HIDDENNO]
 ,double wo[HIDDENNO+1],double hi[],double e[])
{
 int i,j ;/*最大値要素の添え字番号*/
 double u ;/*计算加权和*/
 double o ;/*输出的计算*/

 /*hi的计算*/
 for(i=0;i<HIDDENNO;++i){
  u=0 ;/*求得加权和*/
  for(j=0;j<INPUTNO+HIDDENNO;++j)
   u+=e[j]*wh[i][j] ;
  u-=wh[i][j] ;/*处理阈值*/
  hi[i]=f(u) ;
 }
 /*计算输出o*/
 o=0 ;
 for(i=0;i<HIDDENNO;++i)
  o+=hi[i]*wo[i] ;
 o-=wo[i] ;/*处理阈值*/
 
 return f(o) ;
}

/************************/
/*    readwh()函数      */
/*读入中间层权重        */
/************************/
void readwh(double wh[HIDDENNO][INPUTNO+1+HIDDENNO])
{
 int i,j ;/*循环控制用*/

  for(i=0;i<HIDDENNO;++i){
  for(j=0;j<INPUTNO+1+HIDDENNO;++j)
   scanf("%lf",&(wh[i][j])) ;
 }
}

/************************/
/*    readwo()函数      */
/*  读入输出层权重      */
/************************/
void readwo(double wo[OUTPUTNO][HIDDENNO+1])
{
 int i,j ;/*循环控制用*/

 for(i=0;i<OUTPUTNO;++i){
  for(j=0;j<HIDDENNO+1;++j)
   scanf("%lf",&(wo[i][j])) ;
 }
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