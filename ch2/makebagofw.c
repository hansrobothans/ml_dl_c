/*************************************************/
/*           makebagofw.c                        */
/* 生成bag-of-words表示                          */
/* 使用方法                                      */
/*C:\Users\odaka\ch2>makebagofw  (参数）         */
/* 第一参数 单词词汇数n                          */
/* 第二参数  输入文件（1-of-N表示）              */
/* 参数没有指定时指定标准输入                    */
/*************************************************/

/*和Visual Studio的互换性保证 */
#define _CRT_SECURE_NO_WARNINGS

/*Include头文件*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 符号常数的定义           */
#define TRUE 1 
#define FALSE 0
#define N 1000/*词汇（单词）种类的上限*/
#define LENGTH 64 /*文件名长度的上限*/

/****************/
/*  main()函数  */
/****************/
int main(int argc,char *argv[])
{
 int n ;/*单词的种类数*/
 FILE *fpi ;/*文件指针*/
 char inputfile[LENGTH] ;/*输入文件名*/
 int e ;/*向量元素的值*/
 int i=0 ;/*循环控制*/
 int bagofwords[N]={0} ;/*bag-of-words表示*/

 /*由参数而设定初值*/
 if(argc<2){
  /*参数个数不足*/
  fprintf(stderr,"使い方\n >makenewvec "
          "単語種類数n  (ファイル名)\n") ;
  exit(1);
 }
 fpi=stdin ;/*默认是标准输入*/
 n=atoi(argv[1]) ;/*设置词汇数*/
 if(argc>2){/*打开输入文件*/
  strncpy(inputfile,argv[2],LENGTH) ;/*输入文件*/
  if((fpi=fopen(inputfile,"r"))==NULL){
   /*打开文件失败*/
   fprintf(stderr,"%s:ファイルオープン失敗\n",inputfile) ;
   exit(1);
  }
 }
  
 /*读入基于1-of-N表示的单词序列*/
 while(fscanf(fpi,"%d",&e)!=EOF){
  bagofwords[i]+=e ;
  ++i ;
  if(i>=n) i=0 ;
 }

 /*输出bag-of-words表示*/
 for(i=0;i<n;++i)
  printf("%d ", bagofwords[i]);
 printf("\n") ;

 return 0 ;
}