#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#define test_uva1585

#ifdef test_uva1585
int main_uva1585(){
	freopen("uva1585_input.txt", "r", stdin);
	freopen("uva1585_output.txt", "w", stdout);
#else
int main(int argc,char** argv){
#endif
	int column,sum,score,len;
	static char token[81];
	scanf("%d\n", &column);
	while (column>0){
		gets(token);
		len = strlen(token);
		sum = 0;
		score = 0;
		for (int i = 0; i < len; i++){
			if (token[i] == 'O'){
				score += 1;
			}
			else{
				score = 0;
			}
			sum += score;
		}
		printf("%d\n", sum);
		column--;
	}
	return 0;
}