/*********************************************/
/*           make1gram.c                     */
/*  Shift JIS 汉字编码文字的1-gram生成器     */
/*  从Shift_JIS记述的文件中仅提取            */
/*   全角数据并生成1-gram                    */
/* 使用方法                                  */
/*C:\Users\odaka\ch2>make1gram < text1.txt   */
/*********************************************/

/*和Visual Studio的互换性保证 */
#define _CRT_SECURE_NO_WARNINGS

/*include头文件*/
#include <stdio.h>
#include <stdlib.h>

/* 符号常数的定义             */
#define TRUE 1 
#define FALSE 0

/* 函数原型声明   */
int is2byte(int chr);/*判断是否是全角文字的第一个字节*/

/****************/
/*  main()函数  */
/****************/
int main()
{
	int chr;/*输入文字*/

	/*读入数据后以一个文字一个文字的方式输出*/
	while ((chr = getchar()) != EOF){
		if (is2byte(chr) == TRUE){/*如果是全角文字*/
			putchar(chr);
			/*输出全角文字的第2字节*/
			putchar(getchar());
			putchar('\n');/*1-gram的分割符*/
		}
	}

	return 0;
}

/***********************************/
/*  is2byte()函数                  */
/*判断是否是全角文字的第一个字节   */
/***********************************/
int is2byte(int c)
{
	if (((c >= 0x81) && (c <= 0x9F)) || (c >= 0xe0) && (c <= 0xef))
		return TRUE;/*2字节文字*/
	return FALSE;/*1字节文字*/
}