#include "stdafx.h"
#include "Chapter1.h"
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <vector>
#include <algorithm>
#include <functional>
#include <iostream>
#include <regex>
#include <map>
#include <windows.h>
int reverseNum(int num){
	static char numStr[256];
	sprintf(numStr, "%d", num);
	for (int i = 0, j = strlen(numStr)-1; i < j; i++, j--){
		numStr[i] = numStr[j]^numStr[i];
		numStr[j] = numStr[i]^numStr[j];
		numStr[i] = numStr[i]^numStr[j];
	}
	return atoi(numStr);
}

void getChickenRabbitNum(int totalNum,int legsNum,int& chickenNum,int& rabbitNum){
	rabbitNum = (legsNum - totalNum * 2) / 2;
	chickenNum = totalNum - rabbitNum;
}

void getWholeSquare(){
	int num;
	double sq;
	printf("whole square has:");
	for (int i = 1; i < 9; i++){
		for (int j = 0; j < 9; j++){
			num = i * 1100 + j * 11;
			sq = sqrt(float(num));
			if (floor(sq + 0.5) == sq){
				printf("%d ", num);
			}
		}
	}
	printf("\n");
}

int get3Nadd1Times(unsigned int num){
	int times = 0;
	while (num != 1){
		times += 1;
		if (num % 2 == 0){
			num /= 2;
		}
		else{
			num = 3 * num + 1;
		}
	}
	return times;
}

int get2_3(unsigned int num){
	unsigned int i = 1;
	unsigned int j;
	unsigned int m = 0;
	unsigned int n = 0;
	//double b=clock()/CLOCKS_PER_SEC;
	while (i <= num){
		j = i;
		n = 1;
		while (j >= 1){
			n *= j;
			n %= 1000000;
			j--;
		}
		m += n;
		m %= 1000000;
		i++;
		if (i > 25)
			break;
	}
	//printf("get2_3 usetime is %lf\n", clock() / CLOCKS_PER_SEC - b);
	return m;
}

void getMaxFactorial(){
	int i = 1;
	unsigned int res = 1;
	unsigned int old = 1;
	while (res>=old){
		old = res;
		res *= i;
		i++;
	}
	printf("int max n! is %u,n is %d\n", old, i); //int max n! is 1932053504,n is 15
	i = 1;
	unsigned long long long_res = 1;
	unsigned long long long_old = 1;
	while (long_res >= long_old){
		long_old = long_res;
		long_res *= i;
		i++;
	}
	printf("long max n! is %llu,n is %d\n", long_old, i); //long max n! is 1719 6083 3550 3458 3040,n is 24
	//2的64次方 1844 6744 0737 0955 1616
}

void getMinMaxAvg(){
	freopen("getMinMaxAvg_input.txt", "r", stdin);
	freopen("getMinMaxAvg_output.txt", "w", stdout);
	int input = 0;
	if (!scanf("%d", &input))
		return;
	int num = 1;
	int min = input;
	int max = input;
	float sum = (float)input;
	while (scanf("%d",&input)==1){
		num++;
		if (min > input){
			min = input;
		}
		if (max < input){
			max = input;
		}
		sum += input;
	}
	printf("%d %d %f\n", min, max, sum/num);
}

int getDivisorNum(unsigned long long num){
	int n = 0;
	unsigned long long i = 1;
	unsigned long long ceilNum = (unsigned long long)floor(sqrt(double(num)));
	while (i <= ceilNum){
		if (num%i == 0)n+=2;
		i++;
	}
	return n;
}

int getNumLen(unsigned int num){
	int len = 0;
	while (num > 0){
		num /= 10;
		len++;
	}
	return len;
}

void getNarcissus(){
	for (int i = 100; i <= 999; i++){
		if (pow(float(i % 10), 3) + pow(float(i / 10 % 10), 3) + pow(float(i / 100), 3) == i){
			printf("%d ", i);
		}
	}
	printf("\n");
}

void getHanxin(){
	int _3, _5, _7;
	int n;
	int hasAnswer = 0;
	while (scanf("%d %d %d", &_3, &_5, &_7)){
		hasAnswer = 0;
		for (n = 10; n < 100; n++){
			if (n % 3 == _3&&n % 5 == _5&&n % 7 == _7){
				hasAnswer = 1;
				printf("%d\n", n);
			}
		}
		if (!hasAnswer){
			printf("No answer\n");
		}
	}
}

void getTriangleSharp(){
	int r = 0;
	int sn = 0;
	while (scanf("%d", &r)){
		for (int n = 1; n <= r; n++){
			for (int b = 1; b < n; b++){
				printf(" ");
			}
			sn = 1 + 2 * (r - n);
			for (int s = 1; s <= sn; s++){
				printf("#");
			}
			printf("\n");
		}
	}
}

void getStat(){
	int n;
	int m;
	int a;
	int t = 0;
	std::vector<int> aV;
	while (scanf("%d", &n)){
		for (int i = 1; i <= n; i++){
			scanf("%d", &a);
			aV.push_back(a);
		}
		scanf("%d", &m);
		t = 0;
		for (int i = 0; i < n; i++){
			if (aV[i] < m)
				t++;
		}
		printf("%d\n", t);
	}
}

void getHarmony(){
	int n = 0;
	double h = 0;
	while (scanf("%d", &n)){
		for (int i = 1; i <= n; i++){
			h += 1.0 / i;
		}
		printf("%.3lf\n", h);
	}
}

//求1-1/3+1/5-1/7...最后一个分数必须小于10^-6
void getApproximation(){
	double _pi4 = 0;
	int i = 1;
	int sign = 1;
	double _1_i = 1.0;
	double _10_6 = pow(10, -6);
	while (_1_i>=_10_6){
		_pi4 += _1_i*sign;
		i += 2;
		sign *= -1;
		_1_i = 1.0 / i;
	}
	printf("PI/4约为:%lf	3.141592653/4:%lf\n", _pi4, 3.141592653 / 4);
}

//输入两个数 n m，求得s=1/n^2+1/(n+1)^2+1/(n+2)^2+...+1/m^2，m<=10^6
void getSubSequence(){
	unsigned long long n, m;
	double sum;
	unsigned long long n2;
	unsigned long long _2n;
	while (scanf("%llu %llu", &n, &m)){
		sum = 0;
		n2 = n*n;
		_2n = 2 * n;
		for (unsigned long long i = n,j=0; i <= m; i++,j++){
			sum += 1.0/(n2+_2n*j+j*j);
		}
		printf("%.5lf\n", sum);
	}
}

//输入三数 a b c，求得a/b结果保留c位
void getDecimal(){
	int a, b, c;
	double res;
	char format[]="%%.%dlf\n";
	char buf[256];
	while (scanf("%d %d %d", &a, &b, &c)){
		res = (1.0*a) / b;
		sprintf(buf, format, c);
		printf(buf, res);
	}
}

//0123456789 三位数 组成 abc:def:ghi = 1 : 2 :3
//数字不能重用
void getPermutation(){
	unsigned int flag = 0x0000;
	unsigned int def = 0;
	unsigned int ghi = 0;
	for (int i = 123; i <= 321; i++){
		flag = (flag^flag);
		flag |= 0x01 << (i % 10);
		if (((flag >> i / 10 % 10) & 0x01) == 0x01){
			continue;
		}
		if (((flag >> i / 100 % 10) & 0x01) == 0x01){
			continue;
		}
		def = i * 2;
		if (((flag >> def  % 10) & 0x01) == 0x01){
			continue;
		}
		if (((flag >> def / 10 % 10) & 0x01) == 0x01){
			continue;
		}
		if (((flag >> def / 100 % 10) & 0x01) == 0x01){
			continue;
		}
		ghi = i * 3;
		if (((flag >> ghi % 10) & 0x01) == 0x01){
			continue;
		}
		if (((flag >> ghi / 10 % 10) & 0x01) == 0x01){
			continue;
		}
		if (((flag >> ghi / 100 % 10) & 0x01) == 0x01){
			continue;
		}
		printf("%d %d %d\n", i, def, ghi);
	}
}

//开灯问题
void getLightUp(){
	int k,n;
	static unsigned char light[1000];
	while (scanf("%d %d", &n, &k)){
		for (int i = 1; i <= k; i++){
			for (int j = 1; j <= n; j++){
				if (i == 1){
					light[j-1] = 0xff;
				}
				else if (j%i == 0){
					light[j-1] = ~light[j-1];
				}
			}
		}
		for (int i = 1; i <= n; i++){
			if (light[i - 1] == 0xff)
				printf("%d ", i);
		}
		printf("\n");
	}
}

//获得蛇型输出，如
/*
10  11  12  0
 9  16  13  1
 8	15	14  2
 7   6   5  4		 
*/
void getSnake(){
	int n;
	//上 下 左 右 'u' 'd' 'l' 'r'
	int j,r,c,d;
	static int snake[64];
	while (scanf("%d", &n)){
		j = 1;
		r = 1;
		c = n;
		d = 'd';
		memset(snake, 0, sizeof snake);
		while (j <= n*n){
			snake[(r-1)*n+c-1] = j;
			j++;
			switch (d){
			case 'd':
				if (r == n || snake[r*n + c - 1]!=0){
					d = 'l';
					c--;
				}
				else
					r++;
				break;
			case 'l':
				if (c == 1 || snake[(r - 1)*n + c - 2] != 0){
					d = 'u';
					r--;
				}
				else
					c--;
				break;
			case 'u':
				if (r == 1 || snake[(r - 2)*n + c - 1] != 0){
					d = 'r';
					c++;
				}
				else
					r--;
				break;
			case 'r':
				if (snake[(r - 1)*n + c] != 0){
					d = 'd';
					r++;
				}
				else
					c++;
				break;
			}	
		}
		d = n*n;
		for (int i = 1; i <= d; i++){
			printf("%2d ", snake[i - 1]);
			if (i%n == 0)
				printf("\n");
		}
	}
}

//乘法竖式的第一种实现
void getVerticalForm(){
	static char str[11];
	static char dict[10];
	int len,min3,max3,min2,max2,res,res0,res1,count;
	std::function<bool(int)> check = [](int number){
		int i = 1;
		int temp = number;
		bool flag = true;
		while (1){
			temp = number / i;
			if (temp == 0)
				break;
			if (dict[temp % 10] == 0){
				flag = false;
				break;
			}
			i *= 10;
		}
		return flag;
	};
	while (scanf("%s",str)){
		len = strlen(str);
		if (len == 1 && str[0] == '0'){
			printf("The number of solutions = 0\n");
			continue;
		}
		memset(dict,0,sizeof dict);
		std::sort(str, str+len, [](int _1,int _2){
			return _1<_2;
		});
		for (int i = 0; i < len; i++){
			str[i] -= '0';
			dict[str[i]] = 1;
		}
		if (str[0] != 0){
			min3 = str[0] * 100 + str[0] * 10 + str[0];
			min2 = str[0] * 10 + str[0];
		}
		else{
			min3 = str[1] * 100;
			min2 = str[1] * 10;
		}
		max3 = str[len - 1] * 100 + str[len - 1] * 10 + str[len - 1];
		max2 = str[len - 1] * 10 + str[len - 1];
		count = 0;
		for (int i=min3; i <= max3; i++){
			if (dict[i % 10] == 0 || dict[i / 10 % 10] == 0 || dict[i / 100] == 0)
				continue;
			for (int j=min2; j <= max2; j++){
				if (dict[j % 10] == 0 || dict[j / 10] == 0)
					continue;
				res0 = i*(j % 10);
				if (!check(res0))
					continue;
				res1 = i*(j / 10);
				if (!check(res1))
					continue;
				res = i*j;
				if (!check(res))
					continue;
				count++;
				printf("  %d\nX  %d\n----\n%5d\n%d\n----\n%d\n", i, j, res0, res1, res);
			}
		}
		printf("The number of solutions = %d\n", count);
	}
}

//乘法竖式的第二种实现
void getVerticalForm2(){
	static char str[11];
	static char buf[256];
	int len, res, res0, res1, count;
	bool flag;
	while (scanf("%s", str)){
		count = 0;
		for (int i = 100; i <= 999; i++){
			for (int j = 10; j <= 99; j++){
				res0 = i*(j%10);
				res1 = i*(j / 10);
				res = i*j;
				sprintf(buf, "%d%d%d%d%d", i, j, res0, res1, res);
				len = strlen(buf);
				flag = true;
				for (int k = 0; k < len; k++){
					if (strchr(str, buf[k]) == NULL)
						flag = false;
				}
				if (!flag)
					continue;
				count++;
				printf("  %d\nX  %d\n----\n%5d\n%d\n----\n%d\n", i, j, res0, res1, res);
			}
		}
		printf("The number of solutions = %d\n", count);
	}
}

/* 回文数错误算法，不能通过反转来求，123456 123321 123456654321 78455478 这串数据反转后，为
87455487123456654321123321654321，结果为 123456，明显错误，反转的结果，使得 123456 xxxxxxx 654321 这种都可以匹配
void getPalindrome(){
	static char cstr[5001];
	static char rcstr[5001];
	int len,rlen,ci,ri,matchLen,matchci,matchtempci,realLen;
	bool flag;
	//while (gets(cstr)){
	sprintf(cstr, "%s", "123456 123321 123456654321 78455478");
		len = strlen(cstr);
		rlen = 0;
		matchLen = 0;
		matchci = 0;
		for (int i = 0; i < len; i++){
			if (cstr[i] == ' ' || cstr[i] == '.' || cstr[i] == ',' || cstr[i] == '\'' || cstr[i] == ':'){
				continue;
			}
			rcstr[rlen] = cstr[i];
			rlen++;
		}
		for (int i = 0, j = rlen - 1; i < j; i++, j--){
			rcstr[i] = rcstr[i] ^ rcstr[j];
			rcstr[j] = rcstr[i] ^ rcstr[j];
			rcstr[i] = rcstr[i] ^ rcstr[j];
		}
		for (int i = 0; i < rlen; i++){
			for (int j = i+2; j < rlen; j++){
				ci = 0;
				ri = i;
				flag = true;
				matchtempci = -1;
				while (true){
					if (cstr[ci] == rcstr[ri] || abs(cstr[ci]-rcstr[ri])==32){
						if (matchtempci == -1)
							matchtempci = ci;
						ci++;
						ri++;
					}
					else if (matchtempci != -1){
						if (cstr[ci] == ' ' || cstr[ci] == '.' || cstr[ci] == ',' || cstr[ci] == '\'' || cstr[ci] == ':'){
							ci++;
						}
						else{
							matchtempci = -1;
							ri = i;
						}
					}
					else{
						ci++;
					}
					if (ci >= len){
						if (ri <= j)
							flag = false;
						break;
					}
					if (ri > j)
						break;
				}
				if (flag&&matchLen<j - i + 1){
					matchLen = j - i + 1;
					matchci = matchtempci;
					realLen = ci - matchci;
				}
			}
		}
		if (matchLen>0){
			cstr[matchci + realLen] = '\0';
			printf("%s\n", cstr + matchci);
		}
	//}
}
*/

/* 通过确定起点和结尾，检测是否回文，这种可以解决问题，但效率太低了，当5000个都是相同时，需要等上好几秒。。。
void getPalindrome(){
	static char str[5001];
	int len, matchLen = 0, matchIdx = -1, realLen=0,maxRealLen=0;
	auto check = [](int b, int e){
		int count=0;
		for (int i = b, j = e; i <= j;){
			if (str[i] == ' ' || str[i] == '.' || str[i] == ',' || str[i] == '\'' || str[i] == ':'){
				i++;
				continue;
			}
			if (str[j] == ' ' || str[j] == '.' || str[j] == ',' || str[j] == '\'' || str[j] == ':'){
				j--;
				continue;
			}
			if (str[i] != str[j] && abs(str[i] - str[j])!=32){
				//printf("%c_%c\n", str[i], str[j]);
				return 0;
			}
			count++;
			i++;
			j--;
		}
		return count;
	};
	//while (gets(str)){
		//sprintf(str, "%s", "123456 123321 123456654321 78455478");//Confuciuss say:Madam,I'm Adam
	memset(str, 'a', 1000);
		len = strlen(str);
		for (int i = 0; i < len; i++){
			if (str[i] == ' ' || str[i] == '.' || str[i] == ',' || str[i] == '\'' || str[i] == ':'){
				continue;
			}
			for (int j = i+2; j<len; j++){
				if (str[j] == ' ' || str[j] == '.' || str[j] == ',' || str[j] == '\'' || str[j] == ':'){
					continue;
				}
				realLen = check(i, j);
				if (realLen > 1 && maxRealLen < realLen){	
					maxRealLen = realLen;
					matchIdx = i;
					matchLen = j - i + 1;
				}
			}
		}
		if (matchIdx!=-1){
			str[matchIdx + matchLen] = '\0';
			printf("%s", str + matchIdx);
		}
	//}
}*/

//回文数
void getPalindrome(){
	static char str[5001];
	static char astr[5001];
	static int posmap[5001];
	int len,alen,left,right,matchLen=0,matchLeft=0,matchRight=0;
	bool isOdd;
	//while (gets(str)){
		//sprintf(str, "%s", "Confuciuss say:Madam,I'm Adam");//Confuciuss say:Madam,I'm Adam//123456 123321 123456654321 78455478
		memset(str, 'a', 5000);
		len = strlen(str);
		alen = 0;
		for (int i = 0,j=0; i < len; i++){
			if (str[i] == ' ' || str[i] == '.' || str[i] == ',' || str[i] == '\'' || str[i] == ':')
				continue;
			posmap[j] = i;
			astr[j] = tolower(str[i]);
			alen++;
			j++;
		}
		for (int i = 0; i < alen; i++){
			//奇数
			left = i;
			right = i;
			isOdd = true;
		again:
			while (true){
				if (left < 0 || right >= alen){
					break;
				}
				if (astr[left] != astr[right]){
					break;
				}
				left--;
				right++;
			}
			left++;
			right--;
			if (matchLen < right - left + 1){
				matchLen = right - left + 1;
				matchLeft = left;
				matchRight = right;
			}
			if (!isOdd)
				goto next;
			//偶数
			left = i;
			right = i + 1;
			isOdd = false;
			goto again;
		next:
			;
		}
		if (matchLen>1){
			str[posmap[matchRight] + 1] = '\0';
			printf("%s\n", str + posmap[matchLeft]);
		}
	//}
}

//输出两个最相近的数
void getTwoNear(){
	int n[256];
	int size = 0;
	int m1, m2, m3, m4;
	while (scanf("%d",n+size)){
		size++;
	}
	m1 = n[0];
	m2 = n[1];
	m3 = abs(m1-m2);
	for (int i = 0; i < size; i++){
		for (int j = i+1; j < size; j++){
			m4 = abs(n[i] - n[j]);
			if (m4 < m3){
				m1 = n[i];
				m2 = n[j];
				m3 = m4;
			}
		}
	}
	printf("%d %d\n", m1, m2);
}

//获得第二大的数
void getSecondBig(){
	/*数组方式
	int n[256];
	int size = 0;
	int big, sbig;
	while (scanf("%d", n + size)){
		size++;
	}
	big = n[0];
	sbig = n[1];
	if (big < sbig){
		big = n[1];
		sbig = n[0];
	}
	for (int i = 2; i < size; i++){
		if (big < n[i]){
			sbig = big;
			big = n[i];
		}
		else if (sbig < n[i]){
			sbig = n[i];
		}
	}
	printf("big=%d sbig=%d\n", big, sbig);
	*/
	int big, sbig, temp;
	scanf("%d %d", &big,&sbig);
	if (big < sbig){
		sbig = big;
	}
	while (scanf("%d", &temp)){
		if (big < temp){
			sbig = big;
			big = temp;
		}
		else if (sbig < temp){
			sbig = temp;
		}
	}
	printf("big=%d sbig=%d\n", big, sbig);
}

//求方差
void getVariance(){
	int n[256];
	int sum=0, size=0;
	double avg = 0.0, variance=0.0;
	while (scanf("%d", n + size)){
		sum += n[size];
		size++;
	}
	avg = sum*1.0 / size;
	for (int i = 0; i < size; i++){
		variance += (n[i] - avg)*(n[i] - avg);
	}
	variance /= size;
	printf("%lf\n", variance);
}

//-2146697216 ~ 2146697215
//使用getchar实现
int getInt_by_getchar(int* pn){
	if (pn == nullptr)
		return 0;
	*pn = 0;
	char myint[256]="\0";
	int size=0;
	while (myint[size] = getchar()){
		//遇到文件尾
		if (myint[size] == -1)
			return 0;
		//结束读取
		if (myint[size] == '\t' || myint[size] == '\n' || myint[size] == ' '){
			myint[size] = '\0';
			break;
		}
		//读取失败，读取非法字符
		else if ((size>0 && (myint[size]<'0' || myint[size]>'9')) 
			  || (size == 0 && myint[0] != '-' && (myint[size]<'0' || myint[size]>'9'))){
			return 0;
		}
		
		size++;
		if (size >= 256)
			break;
		//长度达到最大
		/*if ((size == 11 && myint[0] == '-') || (size == 10 && myint[0] != '-')){
			myint[size] = '\0';
			break;
		}*/
	}
	//读取失败，只输了一个'-'号
	if (size == 1 && myint[0] == '-')
		return 0;
	if (size == 0)
		return 1;
	sscanf(myint, "%d", pn);
	return 1;
}

//使用gets实现
int getInt_by_gets(int* pn){
	if (pn == nullptr)
		return 0;
	*pn = 0;
	char myint[256] = "\0";
	int size = 0;
	gets(myint);
	size = strlen(myint);
	if (size == 0)
		return 0;
	if (myint[0] != '-' && (myint[0]<'0' || myint[0]>'9'))
		return 0;
	for (int i = 1; i<size; i++){
		//读取失败，读取非法字符
		if (myint[i]<'0' || myint[i]>'9'){
			return 0;
		}
	}
	sscanf(myint, "%d", pn);
	return 1;
}

//使用getchar来实现gets的功能
char* gets_by_getchar(char* s){
	if (s == nullptr)
		return nullptr;
	int si = 0;
	while (s[si] = getchar()){
		//只输入一个^Z时，getchar返回的结果是-1
		if (si == 0 && s[si] == -1)
			return s;
		//输入一串字符后，再加^Z，getchar返回的结果是26，神奇。。。。
		if (si > 0 && s[si] == 26){
			si = 0;
			continue;
		}
		if (s[si] == '\n'){
			s[si] = '\0';
			break;
		}
		si++;
	}
	return s;
}

//在字符串中查找字符
char* my_strchr(char* s,char c){
	while (s != '\0'){
		if (*s == c)
			return s;
		s++;
	}
	return 0;
}

//小写返回2，大写返回1，否则返回0
int my_isalpha(int c){
	if (c >= 'a'&&c <= 'z')
		return 2;
	else if (c >= 'A'&&c <= 'Z')
		return 1;
	else
		return 0;
}

//字符是否为数字
int my_isdigit(int c){
	if (c >= '0'&&c <= '9')
		return 1;
	else
		return 0;
}

//测试gets
void testGets(){
	char str[256];
	while (gets_by_getchar(str)){
		printf("%s\n",str);
	}
}

//测试getInt
void testGetInt(){
	int temp;
	while (getInt_by_gets(&temp)){
		printf("%d\n", temp);
	}
}

//获得1出现的次数
int get1num(char* s){
	int bt = clock();
	int count = 0;
	unsigned int len = strlen(s);
	for (unsigned int i = 0; i < len; i++){
		if (s[i] == '1'){
			count++;
		}
	}
	printf("time=%lf\n", (clock() - bt) * 1.0 / CLOCKS_PER_SEC);
	return count;
}

void chapter1(){
	printf("=================TEST PRINTF================\n");
	printf("%lf\n", 8.0 / 5.0);
	printf("%.1lf\n", 8.0 / 5.0);
	printf("%lf\n", 8 / 5);
	printf("%d\n", 8.0 / 5.0);
	printf("=================反转数字输出================\n");
	printf("reverse num is:%d\n",reverseNum(123456));
	printf("=================鸡兔同笼问题================\n");
	int rn, cn;
	getChickenRabbitNum(14, 32, cn, rn);
	printf("rabbit is %d,chicken is %d\n", rn,cn);
	getWholeSquare();
	printf("3n+1:%d\n",get3Nadd1Times(999999999));
	printf("1!+2!+3!+...+n!:%d(末6位)\n", get2_3(100));
	getMaxFactorial();
	//getMinMaxAvg();
	printf("divisor num is:%d\n",getDivisorNum(999999999999));
	printf("num len is:%d\n", getNumLen(999999999));
	getNarcissus();
	//getHanxin();
	//getTriangleSharp();
	//getStat();
	//getHarmony();
	//getApproximation();
	//getSubSequence();
	//getDecimal();
	//getPermutation();
	//getLightUp();
	//getSnake();
	//getVerticalForm();
	//getVerticalForm2();
	//getPalindrome();
	//getTwoNear();
	//getSecondBig();
	//getVariance();
	//testGetInt();
	//testGets();
	//printf("%s",my_strchr("123456789",'7'));
	//测试for循环中调用strlen的性能
	/*
	static char s[1000000];
	int i = 1,t = 0;
	while (t <= 1000000){
		memset(s, '1', t);
		s[t] = '\0';
		i+=1000;
		t = i * 5;
		printf("%d,%d\n", t, get1num(s));
	}*/
}