#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#define test_uva1225

#ifdef test_uva1225
int main_uva1225(){
	freopen("uva1225_input.txt", "r", stdin);
	freopen("uva1225_output.txt", "w", stdout);
#else
int main(int argc, char** argv){
#endif
	int column,limit,i,temp;
	int times[10];
	scanf("%d\n", &column);
	while (column > 0){
		scanf("%d\n", &limit);
		i = 1;
		memset(times,0,sizeof times);
		while (i <= limit){
			temp = i;
			do{
				times[temp%10]++;
				temp /= 10;
			} while (temp > 0);
			i++;
		}
		for (int j = 0; j < 9; j++){
			printf("%d ", times[j]);
		}
		printf("%d\n",times[9]);
		column--;
	}
	return 0;
}