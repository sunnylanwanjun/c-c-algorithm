#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <iostream>
#define test_uva455

#ifdef test_uva455
int main_uva455(){
	freopen("uva455_input.txt", "r", stdin);
	freopen("uva455_output.txt", "w", stdout);
#else
int main(int argc, char** argv){
#endif
	int column,matchlen,len;
	bool same;
	char buf[81];
	std::cin >> column;
	while (column>0){
		//std::cin.getline(buf,sizeof buf);//这个不把回车丢弃
		//gets(buf);//这个不把回车丢弃
		//scanf("%s", buf);//这个会把回车丢弃
		std::cin >> buf;//这个会把回车丢弃
		len = strlen(buf);
		for (matchlen = 1; matchlen <= len; matchlen++){
			same = true;
			if (len%matchlen != 0)
				continue;
			for (int j = matchlen; j < len; j++){
				if (buf[j] != buf[j%matchlen]){
					same = false;
					break;
				}
			}
			if (same)
				break;
		}
		if (column == 1){
			std::cout << matchlen << std::endl;
		}
		else{
			std::cout << matchlen << std::endl << std::endl;
		}
		column--;
	}
	return 0;
}