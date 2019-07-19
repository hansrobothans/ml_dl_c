/*********************************************************/
/*                   convpool.c                          */
/*卷积和池化处理                                         */
/*    读入1-of-N数据，实施卷积和池化                     */
/*使用方法                                               */
/*  \Users\odaka\ch3>convpool  < data1.txt               */
/*********************************************************/

/*和Visual Studio的互换性保证 */
#define _CRT_SECURE_NO_WARNINGS

/* include头文件*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*符号常数的定义*/
#define VOCSIZE 12  /*1-of-N表示的词汇数（次数）*/ 
#define WORDLEN 7   /*1-of-N表示的单词的词链长度*/
#define FILTERSIZE 3 /*滤波器大大小*/
#define POOLSIZE 3 /*池化大小*/

/*函数原型的声明*/
void conv(double filter[][FILTERSIZE]
	, double sentence[][VOCSIZE]
	, double convout[][VOCSIZE]); /*卷积计算*/
double calcconv(double filter[][FILTERSIZE]
	, double sentence[][VOCSIZE], int i, int j);
/* 应用滤波器  */
void convres(double convout[][VOCSIZE]);/*输出卷积结果*/
void getdata(double sentence[][VOCSIZE]);/*读入数据*/
void poolres(double poolout[][VOCSIZE]);/*输出池化结果*/
void pool(double convout[][VOCSIZE]
	, double poolout[][VOCSIZE]); /*池化计算*/
double maxpooling(double convout[][VOCSIZE]
	, int i, int j);/* 最大值池化 */

/*******************/
/*    main()函数   */
/*******************/
int main()
{
	double filter[FILTERSIZE][FILTERSIZE]
		= { { 1, 0, 0 }, { 0, 1, 0 }, { 0, 0, 1 } };/*顺接滤波器*/
	//      ={{1,0,0},{1,0,0},{1,0,0}} ;/*连续滤波器*/
	double sentence[WORDLEN][VOCSIZE];/*输入数据*/
	double convout[WORDLEN][VOCSIZE] = { 0 };/*卷积输出*/
	double poolout[WORDLEN][VOCSIZE] = { 0 };/*输出数据*/
	
	/*读入输入数据*/
	getdata(sentence);

	/*卷积计算*/
	conv(filter, sentence, convout);

	/*输出卷积计算的结果*/
	convres(convout);

	/*池化计算*/
	pool(convout, poolout);

	/*输出结果*/
	poolres(poolout);

	return 0;
}

/**********************/
/*  poolres()函数     */
/* 　输出结果         */
/**********************/
void poolres(double poolout[][VOCSIZE])
{
	int i, j;/*循环控制*/
	int startpoint = FILTERSIZE / 2 + POOLSIZE / 2; /*池化计算范围的下限*/

	for (i = startpoint; i<WORDLEN - startpoint; ++i){
		for (j = startpoint; j<VOCSIZE - startpoint; ++j)
			printf("%.3lf ", poolout[i][j]);
		printf("\n");
	}
	printf("\n");
}

/**********************/
/*  pool()函数        */
/*     池化计算       */
/**********************/
void pool(double convout[][VOCSIZE]
	, double poolout[][VOCSIZE])
{
	int i, j;/*循环控制*/
	int startpoint = FILTERSIZE / 2 + POOLSIZE / 2; /*池化计算范围的下限*/

	for (i = startpoint; i<WORDLEN - startpoint; ++i)
	for (j = startpoint; j<VOCSIZE - startpoint; ++j)
		poolout[i][j] = maxpooling(convout, i, j);
}

/**********************/
/* maxpooling()函数   */
/* 最大值池化   */
/**********************/
double maxpooling(double convout[][VOCSIZE]
	, int i, int j)
{
	int m, n;/*循环控制用*/
	double max;/*最大值*/

	max	= convout[i + POOLSIZE / 2][j + POOLSIZE / 2];
	for (m = i - POOLSIZE / 2; m <= i + POOLSIZE / 2; ++m)
	for (n = j - POOLSIZE / 2; n <= j + POOLSIZE / 2; ++n)
	if (max<convout[m][n]) max = convout[m][n];

	return max;
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
/*  getdata()函数     */
/*  读入输入数据      */
/**********************/
void getdata(double e[][VOCSIZE])
{
	int i = 0, j = 0;/*循环控制用*/

	/*输入数据*/
	while (scanf("%lf", &e[i][j]) != EOF){
		++j;
		if (j >= VOCSIZE){/*下一个数据*/
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
/*  calcconv.c()函数    */
/*  应用滤波器    */
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