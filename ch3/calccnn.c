/*********************************************************/
/*                  calccnn.c　                          */
/*       利用cnn.c程序的学习结果计算CNN                  */
/* 使用方法                                              */
/*  \Users\odaka\ch3>calccnn < data.txt                  */
/*********************************************************/

/*和Visual Studio的互换性保证 */
#define _CRT_SECURE_NO_WARNINGS

/*include头文件*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*定义符号常数*/
#define VOCSIZE 12  /*1-of-N表示的词汇数（次数）*/ 
#define WORDLEN 7   /*1-of-N表示的单词词链长度*/
#define FILTERSIZE 3 /*滤波器的大小*/
#define POOLSIZE 3 /*池化的大小*/
#define FILTERNO 2 /*滤波器的个数*/

#define INPUTNO 48 /*输入层神经元数*/
/*由词汇数和单词词链长度确定（(12-2-2)*(7-2-2))*FILTERNO*/
#define HIDDENNO 2  /*中间层神经元数*/ 
#define ALPHA  10  /*学系系数*/ 
#define SEED 7    /*随机数种子*/ 
#define MAXINPUTNO 100    /*最大学习数据个数*/ 

/*函数原型的声明*/
void convpool(double s[WORDLEN][VOCSIZE],
	double mfilter[FILTERNO][FILTERSIZE][FILTERSIZE],
	double se[INPUTNO + 1]);/*卷积和池化*/
void conv(double filter[][FILTERSIZE]
	, double sentence[][VOCSIZE]
	, double convout[][VOCSIZE]); /*卷积计算*/
double calcconv(double filter[][FILTERSIZE]
	, double sentence[][VOCSIZE], int i, int j);
/*  应用滤波器  */
void convres(double convout[][VOCSIZE]);/*输出卷积结果*/
int getdata(double sentence[MAXINPUTNO][WORDLEN][VOCSIZE]);
/*读入数据*/
void poolres(double poolout[][VOCSIZE]);/*输出池化结果*/
void pool(double convout[][VOCSIZE]
	, double poolout[][VOCSIZE]);/*池化计算*/
double maxpooling(double convout[][VOCSIZE]
	, int i, int j);/* 最大值池化 */
double f(double u); /*传递函数（sigmoid函数）*/
void readwh(double wh[HIDDENNO][INPUTNO + 1]);
/*中间层权重的初始化*/
void readwo(double wo[HIDDENNO + 1]);/*输出层权重的初始化*/

void print(double wh[HIDDENNO][INPUTNO + 1]
	, double wo[HIDDENNO + 1]); /*输出结果*/
double forward(double wh[HIDDENNO][INPUTNO + 1]
	, double wo[HIDDENNO + 1], double hi[]
	, double e[INPUTNO + 1]); /*前向计算*/

/*******************/
/*    main()函数   */
/*******************/
int main()
{
	double mfilter[FILTERNO][FILTERSIZE][FILTERSIZE]
		= {
			{ { 1, 0, 0 }, { 0, 1, 0 }, { 0, 0, 1 } },
			{ { 1, 0, 0 }, { 1, 0, 0 }, { 1, 0, 0 } }
	};/*フィルタ群*/
	double sentence[MAXINPUTNO][WORDLEN][VOCSIZE];/*输入数据*/
	double convout[WORDLEN][VOCSIZE] = { 0 };/*输出卷积结果*/
	double poolout[WORDLEN][VOCSIZE] = { 0 };/*输出数据*/

	double wh[HIDDENNO][INPUTNO + 1];/*中间层权重*/
	double wo[HIDDENNO + 1];/*输出层权重*/
	double e[MAXINPUTNO][INPUTNO + 1];/*学习数据集*/
	double hi[HIDDENNO + 1];/*中间层权重*/
	double o;/*输出*/
	int i, j;/*循环控制用*/
	int n_of_e;/*学习数据的个数*/
	int count = 0;/*重复次数的计数*/

	/*读入权重*/
	readwh(wh);/*读入中间层权重*/
	readwo(wo);/*读入输出层权重*/
	print(wh, wo); /*输出结果*/

	/*读入测试数据*/
	n_of_e = getdata(sentence);
	printf("検査データの個数:%d\n", n_of_e);

	/*卷积和池化计算*/
	for (i = 0; i<n_of_e; ++i){
		convpool(sentence[i], mfilter, e[i]);
	}

	/*输出连接权重*/
	print(wh, wo);

	/*对于学习数据的计算输出*/
	for (i = 0; i<n_of_e; ++i){
		printf("%d\n", i);
		for (j = 0; j<INPUTNO; ++j)
			printf("%lf ", e[i][j]);
		printf("\n");
		o = forward(wh, wo, hi, e[i]);
		printf("%lf\n\n", o);
	}

	return 0;
}
/**********************/
/*  poolres()函数     */
/* 　输出结果         */
/**********************/
void poolres(double poolout[][VOCSIZE])
{
	int i, j;/*循环控制用*/
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
/* 池化计算           */
/**********************/
void pool(double convout[][VOCSIZE]
	, double poolout[][VOCSIZE])
{
	int i, j;/*循环控制用*/
	int startpoint = FILTERSIZE / 2 + POOLSIZE / 2; /*池化计算范围的下限*/

	for (i = startpoint; i<WORDLEN - startpoint; ++i)
	for (j = startpoint; j<VOCSIZE - startpoint; ++j)
		poolout[i][j] = maxpooling(convout, i, j);
}

/**********************/
/* maxpooling()函数   */
/* 最大值池化         */
/**********************/
double maxpooling(double convout[][VOCSIZE]
	, int i, int j)
{
	int m, n;/*循环控制用*/
	double max;/*最大值*/

	max = convout[i + POOLSIZE / 2][j + POOLSIZE / 2];
	for (m = i - POOLSIZE / 2; m <= i + POOLSIZE / 2; ++m)
	for (n = j - POOLSIZE / 2; n <= j + POOLSIZE / 2; ++n)
	if (max<convout[m][n]) max = convout[m][n];

	return max;
}


/**********************/
/*  convres()函数     */
/* 输出卷积结果       */
/**********************/
void convres(double convout[][VOCSIZE])
{
	int i, j;/*循环控制用*/
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
/*  conv()函数        */
/*  计算卷积          */
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
/*  应用滤波器        */
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

/************************/
/*  convpool()函数      */
/*  卷积和池化          */
/************************/
void convpool(double s[WORDLEN][VOCSIZE],
	double mfilter[FILTERNO][FILTERSIZE][FILTERSIZE],
	double se[INPUTNO + 1])
{
	int i, j, k;
	int startpoint = FILTERSIZE / 2 + POOLSIZE / 2; /*池化计算范围的下限*/
	/*用各滤波器进行卷积和池化*/
	for (i = 0; i<FILTERNO; ++i){
		double convout[WORDLEN][VOCSIZE] = { 0 };/*卷积输出*/
		double poolout[WORDLEN][VOCSIZE] = { 0 };/*输出数据*/
		/*计算卷积*/
		conv(mfilter[i], s, convout);

		/*输出卷积计算的结果*/
		convres(convout);

		/*池化计算*/
		pool(convout, poolout);

		/*输出结果*/
		poolres(poolout);

		/*卷积计算的结果作为全连接部的输入而代入*/
		for (j = startpoint; j<WORDLEN - startpoint; ++j){
			for (k = startpoint; k<VOCSIZE - startpoint; ++k)
				se[i*INPUTNO / FILTERNO + (j - startpoint)*(VOCSIZE - startpoint * 2) + (k - startpoint)]
				= poolout[j][k];
		}
	}
}

/**********************/
/*  getdata()函数     */
/*   读入学习数据     */
/**********************/
int getdata(double sentence[MAXINPUTNO][WORDLEN][VOCSIZE])
{
	int i = 0, j = 0, k = 0;/*循环控制用*/

	/*输入数据*/
	while (scanf("%lf", &sentence[i][j][k]) != EOF){
		++k;
		if (k >= VOCSIZE){/*下一个数据*/
			k = 0;
			++j;
			if (j >= WORDLEN){/*下一个数据集*/
				j = 0;
				++i;
			}
		}
		if (i>MAXINPUTNO) break;/*输入结束*/
	}
	return i;
}

/**********************/
/*  forward()函数     */
/*  前向计算      */
/**********************/
double forward(double wh[HIDDENNO][INPUTNO + 1]
	, double wo[HIDDENNO + 1], double hi[], double e[INPUTNO + 1])
{
	int i, j;/*循环控制用*/
	double u;/*计算加权和*/
	double o;/*计算输出*/

	/*hiの計算*/
	for (i = 0; i<HIDDENNO; ++i){
		u = 0;/*求得加权和*/
		for (j = 0; j<INPUTNO; ++j)
			u += e[j] * wh[i][j];
		u -= wh[i][j];/*处理阈值*/
		hi[i] = f(u);
	}
	/*计算输出o*/
	o = 0;
	for (i = 0; i<HIDDENNO; ++i)
		o += hi[i] * wo[i];
	o -= wo[i];/*处理阈值*/

	return f(o);
}

/**********************/
/*   print()函数      */
/*   输出结果         */
/**********************/
void print(double wh[HIDDENNO][INPUTNO + 1]
	, double wo[HIDDENNO + 1])
{
	int i, j;/*循环控制用*/

	for (i = 0; i<HIDDENNO; ++i)
	for (j = 0; j<INPUTNO + 1; ++j)
		printf("%lf ", wh[i][j]);
	printf("\n");
	for (i = 0; i<HIDDENNO + 1; ++i)
		printf("%lf ", wo[i]);
	printf("\n");
}

/************************/
/*    readwh()函数      */
/*    读入中间层权重    */
/************************/
void readwh(double wh[HIDDENNO][INPUTNO + 1])
{
	int i, j;/*循环控制用*/

	/*读入权重*/
	for (i = 0; i<HIDDENNO; ++i)
	for (j = 0; j<INPUTNO + 1; ++j)
		scanf("%lf", &(wh[i][j]));
}

/************************/
/*    readwo()函数      */
/*    读入输出层权重    */
/************************/
void readwo(double wo[HIDDENNO + 1])
{
	int i;/*循环控制用*/

	/*读入权重*/
	for (i = 0; i<HIDDENNO + 1; ++i)
		scanf("%lf", &(wo[i]));
}

/*******************/
/* f()函数         */
/* 传递函数        */
/*(sigmoid函数) */
/*******************/
double f(double u)
{
	return 1.0 / (1.0 + exp(-u));
}