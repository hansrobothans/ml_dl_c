/*********************************************************/
/*                   conv.c                              */
/*　卷积处理                                             */
/*　读入1-of-N数据，实施卷积　                   　　　　*/
/* 使用方法                                              */
/*  \Users\odaka\ch3>conv  < data1.txt                   */
/*********************************************************/

/*和Visual Studio的互换性保证 */
#define _CRT_SECURE_NO_WARNINGS

/*Include头文件*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*符号常数的定义*/
#define VOCSIZE 12  /*1-of-N表示的词汇数（次数）*/ 
#define WORDLEN 5   /*1-of-N表示的单词词链长度*/
#define FILTERSIZE 3 /*滤波器的大小*/

/*函数原型的声明*/
void conv(double filter[][FILTERSIZE]
	, double sentence[][VOCSIZE]
	, double convout[][VOCSIZE]); /*卷积计算*/
double calcconv(double filter[][FILTERSIZE]
	, double sentence[][VOCSIZE], int i, int j);
/*  应用滤波器  */
void convres(double convout[][VOCSIZE]); /*输出卷积结果*/
void getdata(double sentence[][VOCSIZE]);/*读入数据*/

/*******************/
/*    main()函数   */
/*******************/
int main()
{
	double filter[FILTERSIZE][FILTERSIZE]
		//      ={{1,0,0},{0,1,0},{0,0,1}} ;/*顺接滤波*/
		= { { 1, 0, 0 }, { 1, 0, 0 }, { 1, 0, 0 } };/*连续滤波*/
	double sentence[WORDLEN][VOCSIZE];/*输入数据*/
	double convout[WORDLEN][VOCSIZE] = { 0 };/*卷积输出*/


	/*读入输入数据*/
	getdata(sentence);

	/*卷积计算*/
	conv(filter, sentence, convout);

	/*输出结果*/
	convres(convout);

	return 0;
}

/**********************/
/*  convres()函数     */
/* 输出卷积结果 */
/**********************/
void convres(double convout[][VOCSIZE])
{
	int i, j;/*循环控制*/
	int startpoint = FILTERSIZE / 2;/*输出范围的下限*/

	for (i = startpoint; i<WORDLEN - 1; ++i){
		for (j = startpoint; j<VOCSIZE - 1; ++j){
			printf("%.3lf ", convout[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

/**********************/
/*   getdata()函数     */
/*读入输入数据*/
/**********************/
void getdata(double e[][VOCSIZE])
{
	int i = 0, j = 0;/*循环控制用*/

	/*输入数据*/
	while (scanf("%lf", &e[i][j]) != EOF){
		++j;
		if (j >= VOCSIZE){/* 下一个数据*/
			j = 0;
			++i;
			if (i >= WORDLEN) break;/*输入结束*/
		}
	}
}

/**********************/
/*  conv()函数        */
/*  卷积计算    */
/**********************/
void conv(double filter[][FILTERSIZE]
	, double sentence[][VOCSIZE], double convout[][VOCSIZE])
{
	int i = 0, j = 0;/*循环控制用*/
	int startpoint = FILTERSIZE / 2;/*卷积范围的下限*/

	for (i = startpoint; i<WORDLEN - startpoint; ++i)
	for (j = startpoint; j<VOCSIZE - startpoint; ++j)
		convout[i][j] = calcconv(filter, sentence, i, j);
}

/**********************/
/*  calcconv()函数    */
/*   应用滤波器    */
/**********************/
double calcconv(double filter[][FILTERSIZE]
	, double sentence[][VOCSIZE], int i, int j)
{
	int m, n;/*循环控制用*/
	double sum = 0;/*和的值*/

	for (m = 0; m<FILTERSIZE; ++m)
	for (n = 0; n<FILTERSIZE; ++n)
		sum += sentence[i - FILTERSIZE / 2 + m][j - FILTERSIZE / 2 + n] * filter[m][n];

	return sum;
}