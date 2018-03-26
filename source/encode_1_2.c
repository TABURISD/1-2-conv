#include "encode_1_2.h"

#define tracelen 32
#define NULL ((void*)0)

int t = 0;
int temp;
int encoder_buffer[7];
int encode_i;
const int s[64] = { 0, 32, 16, 48, 8, 40, 24, 56, 4, 36, 20, 52, 12, 44, 28, 60, 2, 34, 18, 50, 10, 42, 26, 58, 6, 38, 22, 54, 14, 46, 30, 62,
1, 33, 17, 49, 9, 41, 25, 57, 5, 37, 21, 53, 13, 45, 29, 61, 3, 35, 19, 51, 11, 43, 27, 59, 7, 39, 23, 55, 15, 47, 31, 63 };//六个寄存器，64个状态
struct sta                                  /*定义网格图中每一点为一个结构体,其元素包括*/
{
	int met;                                /*转移到此状态累计的度量值*/
	int value;                              /*输入符号 */
	struct sta *last;                       /*及指向前一个状态的指针*/
};
struct  sta state[64][33];                   //定义结构体sta类型的二维数组（网格图64个状态）
struct  sta *g;
int sym, sym1, sym2;


void encoder_1_2_init()
{
	for (int i = 0; i < 7; i++)
	{
		encoder_buffer[i] = 0;
	}
	encode_i = 1;
}

int encode_1_2(int input)
{
	int output;
	int a = 0;
	int b = 0;
	if (encode_i == 8)
	{
		encode_i = 1;
	}
	switch (encode_i)
	{
	case 1:
		encoder_buffer[0] = input;
		a = (encoder_buffer[0] + encoder_buffer[1] + encoder_buffer[2] + encoder_buffer[3] + encoder_buffer[6]) & 1;
		b = (encoder_buffer[0] + encoder_buffer[2] + encoder_buffer[3] + encoder_buffer[5] + encoder_buffer[6]) & 1;
		encode_i++;
		break;
	case 2:
		encoder_buffer[6] = input;
		a = (encoder_buffer[6] + encoder_buffer[0] + encoder_buffer[1] + encoder_buffer[2] + encoder_buffer[5]) & 1;
		b = (encoder_buffer[6] + encoder_buffer[1] + encoder_buffer[2] + encoder_buffer[4] + encoder_buffer[5]) & 1;
		encode_i++;
		break;
	case 3:
		encoder_buffer[5] = input;
		a = (encoder_buffer[5] + encoder_buffer[6] + encoder_buffer[0] + encoder_buffer[1] + encoder_buffer[4]) & 1;
		b = (encoder_buffer[5] + encoder_buffer[0] + encoder_buffer[1] + encoder_buffer[3] + encoder_buffer[4]) & 1;
		encode_i++;
		break;
	case 4:
		encoder_buffer[4] = input;
		a = (encoder_buffer[4] + encoder_buffer[5] + encoder_buffer[6] + encoder_buffer[0] + encoder_buffer[3]) & 1;
		b = (encoder_buffer[4] + encoder_buffer[6] + encoder_buffer[0] + encoder_buffer[2] + encoder_buffer[3]) & 1;
		encode_i++;
		break;
	case 5:
		encoder_buffer[3] = input;
		a = (encoder_buffer[3] + encoder_buffer[4] + encoder_buffer[5] + encoder_buffer[6] + encoder_buffer[2]) & 1;
		b = (encoder_buffer[3] + encoder_buffer[5] + encoder_buffer[6] + encoder_buffer[1] + encoder_buffer[2]) & 1;
		encode_i++;
		break;
	case 6:
		encoder_buffer[2] = input;
		a = (encoder_buffer[2] + encoder_buffer[3] + encoder_buffer[4] + encoder_buffer[5] + encoder_buffer[1]) & 1;
		b = (encoder_buffer[2] + encoder_buffer[4] + encoder_buffer[5] + encoder_buffer[0] + encoder_buffer[1]) & 1;
		encode_i++;
		break;
	case 7:
		encoder_buffer[1] = input;
		a = (encoder_buffer[1] + encoder_buffer[2] + encoder_buffer[3] + encoder_buffer[4] + encoder_buffer[0]) & 1;
		b = (encoder_buffer[1] + encoder_buffer[3] + encoder_buffer[4] + encoder_buffer[6] + encoder_buffer[0]) & 1;
		encode_i++;
		break;
	}
	output = (a << 1) | b;
	return output;
}

void decoder_1_2_init(int initialstate)
{
	if (initialstate == 0)
	{
		for (int m = 0; m<64; m++)
		{


			sym = (((s[m] >> 5) & 1) << 1) | ((s[m] >> 5) & 1);
			state[m][0].met = ((sym & 1)) + ((sym >> 1) & 1);
			state[m][0].value = ((s[m] >> 5) & 1);
			state[m][0].last = NULL;
		}
	}
	else
	{
//		for (int m = 0; m<64; m++)
//		{
//
//			sym = ((((s[m] >> 5) + (initialstate >> 5) + (initialstate >> 4) + (initialstate >> 3) + initialstate) & 1) << 1) | ((s[m] >> 5) + (initialstate >> 4) + (initialstate >> 3) + (initialstate >> 1) + initialstate) & 1;
//			state[m][0].met = ((viterbiinput[0] + sym) & 1) + ((viterbiinput[0] >> 1) + (sym >> 1)) & 1;
//			state[m][0].value = ((s[m] >> 5) & 1);
//			state[m][0].last = NULL;
//		}
	}

	t = 0;
}

int decode_1_2(int input)
{

	int  p, r, u,k;
	int  a = 0;
	int output;

	if (temp<tracelen)
	//if (t<tracelen)
	{
		for (int q = 0; q<64; q++)
		{
			p = q / 2;
			sym1 = ((((s[q] >> 5) + (s[p] >> 5) + (s[p] >> 4) + (s[p] >> 3) + s[p]) << 1) & 2) | (((s[q] >> 5) + (s[p] >> 4) + (s[p] >> 3) + (s[p] >> 1) + s[p]) & 1);
			sym2 = ((((s[q] >> 5) + (s[p + 32] >> 5) + (s[p + 32] >> 4) + (s[p + 32] >> 3) + s[p + 32]) << 1) & 2) | (((s[q] >> 5) + (s[p + 32] >> 4) + (s[p + 32] >> 3) + (s[p + 32] >> 1) + s[p + 32]) & 1);
			int met1 = state[p][t - 1].met + ((input + sym1) & 1) + (((input >> 1) + (sym1 >> 1)) & 1);
			int met2 = state[p + 32][t - 1].met + ((input + sym2) & 1) + (((input >> 1) + (sym2 >> 1)) & 1);
			state[q][t].value = ((s[q] >> 5) & 1);
			if (met1>met2)  //保留累计汉明度量小的分支为幸存路径
			{
				state[q][t].met = met2;
				state[q][t].last = &state[p + 32][t - 1]; //第t个网段即从状态s[p + 32]到s[q], 即t - 1时刻对应的状态为s[p + 32]
			}
			else
			{
				state[q][t].met = met1;
				state[q][t].last = &state[p][t - 1];//第t个网段即从状态s[p]到s[q],即t-1时刻对应的状态为s[p]
			}
		}
		t++;
		temp++;
		return 0;
	}
	else{
		if (t == 0)
			k = tracelen;
		else
			k = t - 1;
			
		//k = t - 1;
		for (int q = 0; q < 64; q++)
		{
			p = q / 2;
			sym1 = ((((s[q] >> 5) + (s[p] >> 5) + (s[p] >> 4) + (s[p] >> 3) + s[p]) << 1) & 2) | (((s[q] >> 5) + (s[p] >> 4) + (s[p] >> 3) + (s[p] >> 1) + s[p]) & 1);
			sym2 = ((((s[q] >> 5) + (s[p + 32] >> 5) + (s[p + 32] >> 4) + (s[p + 32] >> 3) + s[p + 32]) << 1) & 2) | (((s[q] >> 5) + (s[p + 32] >> 4) + (s[p + 32] >> 3) + (s[p + 32] >> 1) + s[p + 32]) & 1);
			//int met1 = state[p][t - 1].met + ((input + sym1) & 1) + (((input >> 1) + (sym1 >> 1)) & 1);
			//int met2 = state[p + 32][t - 1].met + ((input + sym2) & 1) + (((input >> 1) + (sym2 >> 1)) & 1);
			int met1 = state[p][k].met + ((input + sym1) & 1) + (((input >> 1) + (sym1 >> 1)) & 1);
			int met2 = state[p + 32][k].met + ((input + sym2) & 1) + (((input >> 1) + (sym2 >> 1)) & 1);
			state[q][t].value = ((s[q] >> 5) & 1);
			if (met1 > met2)  //保留累计汉明度量小的分支为幸存路径
			{
				state[q][t].met = met2;
				//state[q][t].last = &state[p + 32][t - 1]
