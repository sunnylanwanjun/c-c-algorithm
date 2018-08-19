#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <iostream>
#define test_uva227

#ifdef test_uva227
int main_uva227(){
	freopen("uva227_input.txt", "r", stdin);
	freopen("uva227_output.txt", "w", stdout);
#else
int main(int argc, char** argv){
#endif
	char grid[26];
	char step[256],sl;
	int H, L,OH,OL,oidx,idx,num=1;
	char s;
	while (true){
		for (int i = 0; i < 25; i+=5){
			gets(grid + i);
			if (grid[0] == 'Z'&&grid[1] == '\0')
				return 0;
		}
		if (num==1)
			printf("Puzzle #%d:\n", num);
		else
			printf("\nPuzzle #%d:\n", num);
		num++;
		L = H = -1;
		for (int i = 0; i < 25; i++){
			if (grid[i] == ' '){
				H = i / 5;
				L = i % 5;
			}
		}
		step[0] = '\0';
		for (int i = 0;;){
			i=strlen(step);
			gets(step+i);
			if (step[strlen(step) - 1] == '0')
				break;
		}
		sl = strlen(step);
		for (int i = 0; i < sl; i++){
			s = step[i];
			OH = H;
			OL = L;
			switch (s){
			case 'A'://上
				H -= 1;
				if (H < 0)
					goto pFailed;
				break;
			case 'B'://下
				H += 1;
				if (H > 4)
					goto pFailed;
				break;
			case 'L'://左
				L -= 1;
				if (L < 0)
					goto pFailed;
				break;
			case 'R'://右
				L += 1;
				if (L > 4)
					goto pFailed;
				break;
			case '0'://结束
				goto pGrid;
				break;
			default:
				goto pFailed;
				break;
			}
			oidx = OH * 5 + OL;
			idx = H * 5 + L;
			grid[oidx] = grid[idx];
			grid[idx] = ' ';
		}
	pGrid:
		for (int i = 0; i < 25; i++){
			printf("%c", grid[i]);
			if ((i+1) % 5 == 0)
				printf("\n");
			else
				printf(" ");
		}
		continue;
	pFailed:
		printf("This puzzle has no final configuration.\n");
	}
	return 0;
}