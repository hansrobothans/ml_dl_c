/*************************************************/
/*           makevec.c                           */
/*           从单词1-gram生成1-of-N表示          */
/* 使用方法                                      */
/*C:\Users\odaka\ch2>makevec  (参数）            */
/*参数指定了输入输出文件                         */
/* 第一参数  输入文件（单词1-gram）              */
/* 参数没有指定时的默认值是w1gram.txt文件        */
/* 第二参数  存放单词词汇的文件                  */
/* 参数没有指定时的默认值是voc.txt文件           */
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
#define N 5000/*单词种类的上限*/
#define INPUTFILE "w1gram.txt"/* 默认输入文件*/
#define OUTPUTFILE "voc.txt"/*默认输出文件*/

/* 函数原型的声明   */
int isnew(char word[],
      char dictionary[][LENGTH],int n)  ;/*新建单词判别*/
void putvec(char word[],
      char dictionary[][LENGTH],int n)  ;/*1-of-N输出*/

/****************/
/* main()函数  */
/****************/
int main(int argc,char *argv[])
{
 char word[LENGTH*10] ;/*用于读入单词*/
 char dictionary[N][LENGTH] ;/*用于登录单词的词典*/
 int n=0 ;/*单词的种类数*/
 FILE *fpi,*fpo ;/*文件指针*/
 char inputfile[LENGTH]=INPUTFILE ;/*输入文件名*/
 char outputfile[LENGTH]=OUTPUTFILE ;/* 输出文件名*/

 /*输入文件名的设定*/
 if(argc>=2) strncpy(inputfile,argv[1],LENGTH) ;
 if(argc>=3) strncpy(outputfile,argv[2],LENGTH) ;

 /*打开输入文件*/
 if((fpi=fopen(inputfile,"r"))==NULL){
  /*打开文件失败*/
  fprintf(stderr,"%s:ファイルオープン失敗\n",inputfile) ;
  exit(1);
 }

 /*打开输出文件*/
 if((fpo=fopen(outputfile,"w"))==NULL){
  /*打开文件失败*/
  fprintf(stderr,"%s:ファイルオープン失敗\n",outputfile) ;
  exit(1);
 }
 /*读入数据并登录到词典*/
 while(fscanf(fpi,"%s",word)!=EOF){
  if(isnew(word,dictionary,n)==TRUE){/*如果是新单词*/
    strncpy(dictionary[n],word,LENGTH) ;/*登录单词*/
    ++n ;/*计数单词个数*/
  }
 }
 fprintf(stderr,"単語数 %d\n",n) ;
 rewind(fpi) ;/*向文件头回卷*/

 /*输出1-of-N表示*/
 while(fscanf(fpi,"%s",word)!=EOF){
  putvec(word,dictionary,n) ;/*输出*/
 }
 
 /*词汇文件的输出*/
 {
  int i ;
  for(i=0;i<n;++i) fprintf(fpo,"%s\n",dictionary[i]) ;
 }
 return 0 ;
}

/*******************************/
/*  putvec()函数               */
/* 输出1-of-N表示              */
/*******************************/
void putvec(char word[],
      char dictionary[][LENGTH],int n)  
{
 int i ;/*循环控制变量*/

 for(i=0;i<n;++i){
  if((strncmp(word,dictionary[i],LENGTH)==0)
       && (strlen(word)==strlen(dictionary[i]))) /*一致*/
   printf("1") ;
  else printf("0") ;
  printf(" ") ;
 }
 printf("\n") ;/*向量的区分*/
}

/*******************************/
/*  isnew()函数                */
/*是否是新单词的判定           */
/*******************************/
int isnew(char word[],
      char dictionary[][LENGTH],int n)  
{
 int i ;/*循环控制变量*/

 for(i=0;i<n;++i){
  if((strncmp(word,dictionary[i],LENGTH)==0)
       && (strlen(word)==strlen(dictionary[i]))) break ;/*已经登录*/
 }
 if(i<n) return FALSE ;
 
 return TRUE ;
}