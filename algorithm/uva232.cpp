#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <array>
#define test_uva232

#ifdef test_uva232
int main_uva232(){
	freopen("uva232_input.txt", "r", stdin);
	freopen("uva232_output.txt", "w", stdout);
#else
int main(int argc, char** argv){
#endif
	char pGrid[101],strBuf[11];
	int pGirdIdx[100];
	std::vector<int> _bufVec;
	std::map<int, std::array<char,11>> _bufMap;

	int H, L,count=1,pidx,idx,gidx,bufIdx;
	while (true){
		std::cin >> H;
		if (H == 0){
			break;
		}
		std::cin >> L;
		if (count == 1)
			printf("puzzle #%d:\n",count);
		else
			printf("\npuzzle #%d:\n", count);
		count++;
		for (int h = 0; h < H; h++){
			std::cin >> pGrid+h*L;
		}
		pidx = 1;
		idx = 1;
		gidx = 0;
		bufIdx = 0;
		printf("Across\n");
		for (int i = 0; i < H; i++){
			for (int j = 0; j < L; j++){
				if (i == 0 || j==0){
					if (pGrid[gidx] != '*'){
						if (bufIdx == 0){
							pidx = idx;
						}
						strBuf[bufIdx] = pGrid[gidx];
						bufIdx++;
						pGirdIdx[gidx] = idx;
						idx++;
					}
					else if (bufIdx>0){
						strBuf[bufIdx] = '\0';
						printf("%3d.%s\n", pidx, strBuf);
						bufIdx = 0;
					}
				}
				else{
					if (pGrid[gidx] != '*'){
						if (bufIdx == 0){
							pidx = idx;
						}
						strBuf[bufIdx] = pGrid[gidx];
						bufIdx++;
						if (pGrid[i*L + j - 1] == '*' || pGrid[(i - 1)*L + j] == '*'){
							pGirdIdx[gidx] = idx;
							idx++;
						}
					}
					else if(bufIdx>0){
						strBuf[bufIdx] = '\0';
						printf("%3d.%s\n", pidx, strBuf);
						bufIdx = 0;
					}
				}
				gidx++;
			}
			if (bufIdx > 0){
				strBuf[bufIdx] = '\0';
				printf("%3d.%s\n", pidx, strBuf);
				bufIdx = 0;
			}
		}
		printf("Down\n");
		pidx = 1;
		idx = 1;
		gidx = 0;
		bufIdx = 0; 
		_bufMap.clear();
		_bufVec.clear();
		for (int j = 0; j < L; j++){
			for (int i = 0; i < H; i++){
				gidx = i*L + j;
				if (i==0 || j == 0){
					if (pGrid[gidx] != '*'){
						if (bufIdx == 0){
							pidx = pGirdIdx[gidx];
							_bufVec.push_back(pidx);
						}
						//pLBuf[bufIdx] = pGrid[gidx];
						_bufMap[pidx][bufIdx] = pGrid[gidx];
						bufIdx++;
					}
					else if (bufIdx>0){
						//pLBuf[bufIdx] = '\0';
						//printf("%3d.%s\n", pidx, pLBuf);
						_bufMap[pidx][bufIdx] = '\0';
						bufIdx = 0;
					}
				}
				else{
					if (pGrid[gidx] != '*'){
						if (bufIdx == 0){
							pidx = pGirdIdx[gidx];
							_bufVec.push_back(pidx);
						}
						//pLBuf[bufIdx] = pGrid[gidx];
						_bufMap[pidx][bufIdx] = pGrid[gidx];
						bufIdx++;
					}
					else if (bufIdx > 0){
						//pLBuf[bufIdx] = '\0';
						//printf("%3d.%s\n", pidx, pLBuf);
						_bufMap[pidx][bufIdx] = '\0';
						bufIdx = 0;
					}
				}
			}
			if (bufIdx > 0){
				//pLBuf[bufIdx] = '\0';
				//printf("%3d.%s\n", pidx, pLBuf);
				_bufMap[pidx][bufIdx] = '\0';
				bufIdx = 0; 
			}
		}
		std::sort(_bufVec.begin(), _bufVec.end(), [](int a,int b){
			return a < b;
		});
		for (auto it = _bufVec.begin(); it != _bufVec.end(); it++){
			printf("%3d.%s\n", *it, &_bufMap[*it][0]);
		}
	}
	return 0;
}