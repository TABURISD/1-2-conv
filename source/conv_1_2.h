#ifndef CONV_1_2_H_
#define CONV_1_2_H_

void encoder_init(); //����ǰ����
int encode(int input); //1bit���� 2bit���
void decoder_init(int initialstate);//����ǰ����
int decode(int input);//2bit���� 1bit���

#endif