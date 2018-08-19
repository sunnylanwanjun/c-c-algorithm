#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <map>
#define test_uva1586

#ifdef test_uva1586
int main_uva1586(){
	freopen("uva1586_input.txt", "r", stdin);
	freopen("uva1586_output.txt", "w", stdout);
#else
int main(int argc, char** argv){
#endif
	std::map<int, double> eletb;
	eletb['C'] = 12.01;
	eletb['N'] = 14.01;
	eletb['O'] = 16.00;
	eletb['H'] = 1.008;
	int column,len,num;
	bool preEle;
	double sum,ele;
	char buf[81];
	scanf("%d\n", &column);
	while (column > 0){
		gets(buf);
		len = strlen(buf);
		preEle = false;
		sum = 0;
		for (int i = 0; i < len; ){
			if (buf[i]>'A'){
				if (preEle){
					sum += ele;
				}
				ele = eletb[buf[i]];
				preEle = true;
				i++;
			}
			else{
				sscanf(buf + i, "%d", &num);
				while (buf[i] < 'A')i++;
				sum += ele*num;
				preEle = false;
			}
		}
		if (preEle){
			sum += ele;
		}
		printf("%.3lf\n", sum);
		column--;
	}
	return 0;
}