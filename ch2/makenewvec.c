/*************************************************/
/*           makenewvec.c                        */
/* 随机生成新文本（1-of-N表示）                  */
/* 使用方法                                      */
/*C:\Users\odaka\ch2>makenewvec  (参数）         */
/*     参数指定输入文件                          */
/* 第一参数  单词词汇数 n                        */
/* 第二参数  开始单词号码 s (0<=s<n)             */
/* 参数没有指定时指定为0                         */
/* 第三参数 输入文件（1-of-N表示）               */
/* 参数没有指定时指定为标准输入                  */
/*************************************************/

/*和Visual Studio的互换性保证 */
#define _CRT_SECURE_NO_WARNINGS

/*Include头文件*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 符号常数的定义            */
#define TRUE 1 
#define FALSE 0
#define N 1000/*词汇（单词）种类的上限*/
#define WN 5000/*单词个数的上限*/
#define WLIMIT 50/*输出单词数*/
#define LENGTH 64 /*文字列的长度的上限*/
#define SEED 65535    /*随机数的种子*/
#define ULIMIT 5 /* 随机搜索单词的上限次数*/

/* 函数原型的声明   */
int read1ofn(FILE *fpi,int n) ;
   /*读入基于1-of-N表示的单词序列*/
void putvec(int nextn,int n) ;
   /*输出基于1-of-N表示的单词*/
int searchs(int s,int n,int wn) ;
   /*搜寻对应于s的单词*/
int matchptn(int i,int s,int n) ;
  /*检查单词的一致性　              */
int rndn(int n) ;
  /*返回参数以下的整数随机数*/

/*外部变量*/
char ngram[WN][N] ;/*存放1-of-N表示的输入数据*/

/****************/
/*  main()函数  */
/****************/
int main(int argc,char *argv[])
{
 int n ;/*单词的种类数*/
 int wn ;/*输入单词的总数*/
 int s=0 ;/*开始单词序号*/
 FILE *fpi ;/*文件指针*/
 char inputfile[LENGTH] ;/*输入文件名*/
 int i,j ;/*循环控制*/
 int loopmax ;/*循环次数*/

 /*随机数的初始化*/
 srand(SEED) ;
 
 /*根据参数设定初值*/
 if(argc<2){
  /*参数不足*/
  fprintf(stderr,"使い方\n >makenewvec "
          "単語種類数n (開始単語番号s) (ファイル名)\n") ;
  exit(1);
 }
 fpi=stdin ;/*默认为标准输入*/
 n=atoi(argv[1]) ;/*设定词汇数*/
 if(argc>2) s=atoi(argv[2]) ;/*开始词汇序号*/
 if(argc>3){/*打开输入文件*/
  strncpy(inputfile,argv[3],LENGTH) ;/*输入文件*/
  if((fpi=fopen(inputfile,"r"))==NULL){
   /*文件打开失败*/
   fprintf(stderr,"%s:ファイルオープン失敗\n",inputfile) ;
   exit(1);
  }
 }
  
 fprintf(stderr,"単語数 %d,開始単語番号 %d\n",n,s) ;
 if((s>=n)||(s<0)){/*S不适当*/
   fprintf(stderr,"s=%d,sは1以上ｎ未満にしてください\n",s) ;
   exit(1);
 }
 /*读入基于1-of-N表示的单词序列*/
 wn= read1ofn(fpi,n) ;/*设定读入和输入单词总数wn*/

 /*生成单词词链（文本）*/
 putvec(s,n) ;/*起始符*/

 for(i=0;i<WLIMIT;++i){
  /*搜寻对应于s的单词*/
  loopmax=rndn(ULIMIT) ;/*最大重复次数ULIMIT*/
  for(j=0;j<loopmax;++j)/*重复随机次数*/
   s=searchs(s,n,wn) ;
  /*输出相邻的下一个单词*/
  ++ s ;
  if(s>=wn) s=0 ;/*回到最开始*/
  putvec(s,n) ;
 }

 return 0 ;
}

/**************************************/
/*   rndn()函数                       */
/*返回参数以下的整数随机数            */
/**************************************/
int rndn(int n)
{
 double rndno ;/*生成的随机数*/

 while((rndno=(double)rand()/RAND_MAX)==1.0) ;
 return rndno*n ;
}

/**************************************/
/*   searcha()函数                    */
/*  搜索s对应的单词                   */
/**************************************/
int searchs(int s,int n,int wn) 
{
 int i ;/*循环控制*/

 for(i=s+1;i<wn;++i)
  if(matchptn(i,s,n)==TRUE) return i ;
 for(i=0;i<=s;++i)
  if(matchptn(i,s,n)==TRUE) return i ;
 /*都不一致*/
 fprintf(stderr,"内部エラー　searchs()関数\n") ;
 exit(1) ;
}

/**************************************/
/*   matchptn()函数                   */
/*检查单词的一致性    　              */
/**************************************/
int matchptn(int i,int s,int n) 
{
 int result=TRUE ;
 int index ;

 for(index=0;index<n;++index)
  if(ngram[i][index]!=ngram[s][index])
   result=FALSE ;/*不一致*/
 return result ;
}

/**************************************/
/*  putvec()函数                      */
/*输出基于1-of-N表示的单词            */
/**************************************/
void putvec(int nextn,int n) 
{
 int j=0 ;/*循环控制*/

 for(j=0;j<n;++j)
  printf("%1d ",ngram[nextn][j]);
 printf("\n") ;

}

/****************************************/
/*   read1ofn()函数                     */
/*读入基于1-of-N表示的单词序列          */
/****************************************/
int read1ofn(FILE *fpi,int n) 
{
 int e ;/*输入向量元素的值*/
 int i=0,j=0 ;/*循环控制*/

 while((fscanf(fpi,"%d",&e)!=EOF)&&(i<WN)){
  ngram[i][j]=e ;
  ++j ;
  if(j>=n){
   j=0 ; ++i ;
  }
 } 
 return i ;
}