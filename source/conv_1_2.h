#ifndef CONV_1_2_H_
#define CONV_1_2_H_

void encoder_init(); //编码前调用
int encode(int input); //1bit输入 2bit输出
void decoder_init(int initialstate);//解码前调用
int decode(int input);//2bit输入 1bit输出

#endif