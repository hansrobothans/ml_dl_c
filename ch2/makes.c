/*************************************************/
/*           makes.c                             */
/* 由1-of-N表示生成文本          　　　　        */
/* 使用方法                                      */
/*C:\Users\odaka\ch2>makes  (参数）              */
/*参数指定了输入文件                             */
/*第一参数  存放单词词汇的文件                   */
/* 参数没有指定时的默认值是voc.txt文件           */
/* 第二参数  输入文件（1-of-N表示）              */
/* 参数没有指定时按标准输入                      */
/*************************************************/

/*和Visual Studio的互换性保证 */
#define _CRT_SECURE_NO_WARNINGS

/*Include头文件*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 符号常数的定义             */
#define TRUE 1 
#define FALSE 0
#define LENGTH 64 /*单词长度的上限*/
#define N 10000/*  单词种类的上限*/
#define VOCFILE "voc.txt"/*默认单词词汇文件*/

/****************/
/*  main()函数  */
/****************/
int main(int argc,char *argv[])
{
 char word[LENGTH*10] ;/*用于读入单词*/
 char dictionary[N][LENGTH] ;/*用于登录单词的词典*/
 int n=0 ;/*单词的种类数*/
 FILE *fpvoc,*fpi ;/*文件指针*/
 char inputfile[LENGTH] ;/*输入文件名*/
 char vocfile[LENGTH]=VOCFILE ;/*单词词汇文件名*/
 int e ;/*输入向量元素值*/
 int i ;/*循环控制*/

 /*输入文件名的设定*/
 fpi=stdin ;
 if(argc>=2) strncpy(vocfile,argv[1],LENGTH) ;
 if(argc>=3) strncpy(inputfile,argv[2],LENGTH) ;

 /*打开词汇文件*/
 if((fpvoc=fopen(vocfile,"r"))==NULL){
  /*打开文件失败*/
  fprintf(stderr,"%s:ファイルオープン失敗\n",vocfile) ;
  exit(1);
 }

 /*打开输入文件*/
 if((argc>=3)&&(fpi=fopen(inputfile,"r"))==NULL){
  /*打开文件失败*/
  fprintf(stderr,"%s:ファイルオープン失敗\n",inputfile) ;
  exit(1);
 }

 /*读入单词词汇数据并登录到词典*/
 while(fscanf(fpvoc,"%s",word)!=EOF){
  strncpy(dictionary[n],word,LENGTH) ;/*登录单词*/
  ++n ;/*计数单词个数*/
 }
 printf("単語数 %d\n",n) ;

 /* 输出文本*/
 i=0 ;
 while(fscanf(fpi,"%d",&e)!=EOF){
  if(e==1) printf("%s",dictionary[i]) ;
  ++i ;
  if(i>=n) i=0 ;
 }
 
 return 0 ;
}