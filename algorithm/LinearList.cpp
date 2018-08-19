#include "stdafx.h"
#include "LinearList.h"
#include <iostream>
template<typename T>
void ListUnion(LinkList<T>&La, LinkList<T>&Lb){
	auto compareFunc = [](LinkNode<T>*a, LinkNode<T>*b){
		if (a == nullptr || b == nullptr)
			return true;//为true就不会导致插入
		return a->value == b->value;
	};
	int LaLen = La.ListLength();
	int LbLen = Lb.ListLength();
	LinkNode<T> e;
	for (int i = 0; i < LbLen; i++){
		Lb.GetElem(i,&e);
		if (La.LocateElem(&e, compareFunc) == -1){
			La.ListInsert(LaLen++,&e);
		}
	}
}

template<typename T>
void ListPrint(LinkList<T>&L){
	LinkNode<T>* curNode = L.head;
	while (curNode){
		std::cout << curNode->value << " ";
		curNode = curNode->next;
	}
	std::cout<<std::endl;
}

template<typename T>
void ListInit(LinkList<T>&L,T elemArr[],int elemLen){
	LinkNode<T> node;
	for (int i = 0; i < elemLen; i++){
		node.value = elemArr[i];
		L.ListInsert(i, &node);
	}
}

template<typename T>
void ListPrint(SqList<T>&L){
	int size = L.ListLength();
	for (int i = 0; i < size;i++){
		std::cout << L[i] << " ";
	}
	std::cout << std::endl;
}

template<typename T>
void ListInit(SqList<T>&L, T elemArr[], int elemLen){
	for (int i = 0; i < elemLen; i++){
		L.ListInsert(i, &elemArr[i]);
	}
}

template<typename T>
void ListUnion(LinkList<T>&Lc,LinkList<T>&La,LinkList<T>&Lb){
	//低效算法,没有利用到给定数据已经排序的条件
	//ListLen(La)*ListLen(Lb)
	/*
	Lc = La;
	int LcLen = Lc.ListLength();
	int LbLen = Lb.ListLength();
	LinkNode<T> e;
	LinkNode<T> c;
	bool hasFind = false;
	for (int i = 0; i < LbLen; i++){
		Lb.GetElem(i, &e);
		hasFind = false;
		for (int j = 0; j < LcLen; j++){
			if (Lc.GetElem(j, &c)){
				if (c->value >= e->value){
					hasFind = true;
					Lc.ListInsert(j, &e);
					LcLen++;
					break;
				}
			}
		}
		if (!hasFind){
			Lc.ListInsert(-1, &e);
			LcLen++;
		}
	}
	*/
	//高效算法
	LinkNode<T>* a=La.GetHead();
	LinkNode<T>* b=Lb.GetHead();
	while (a&&b){
		if (a->value <= b->value){
			Lc.ListAppend(a);
			a = a->next;
		}
		else{
			Lc.ListAppend(b);
			b = b->next;
		}
	}
	while (a){
		Lc.ListAppend(a);
		a = a->next;
	}
	while (b){
		Lc.ListAppend(b);
		b = b->next;
	}
}

template<typename T>
void ListUnion(SqList<T>&Lc, SqList<T>&La, SqList<T>&Lb){
	//高效算法
	int LaLen = La.ListLength();
	int LbLen = Lb.ListLength();
	int ai = 0, bi = 0;
	while (ai < LaLen&&bi < LbLen){
		if (La[ai] <= Lb[bi]){
			Lc.ListAppend(&La[ai]);
			ai++;
		}
		else{
			Lc.ListAppend(&Lb[bi]);
			bi++;
		}
	}
	while (ai < LaLen){
		Lc.ListAppend(&La[ai]);
		ai++;
	}
	while (bi < LbLen){
		Lc.ListAppend(&Lb[bi]);
		bi++;
	}
}

/*
//18-二-1
bool ListDeleteSmall(SqList&L,ELemType& de){
	if(L.length==0){
		std::cout<<"error"<<std::endl;
		return false;
	}
	ElemType small = L.data[0];
	int smallIdx=0;
	for(int i=1;i<L.length;i++){
		if(L.data[i]<small){
			smallIdx=i;
			small=L.data[i];
		}
	}
	de=L.data[smallIdx];
	L.data[smallIdx] = L.data[L.length-1];
	L.length--;
	return true;
}

//18-二-2
void ListReverse(SqList&L){
	if(L.length<=1)
		return;
	ElemType temp;
	for(int i=0;i<L.length/2;i++){
		temp = L.data[i];
		L.data[i] = L.data[L.length-i-1];
		L.data[L.length-i-1] = temp;
	}
}

//18-二-3
void ListDelete(SqList&L,ElemType x){
	int move=0;
	for(int i=0;i<L.length;i++){
		if(L.data[i]==x){
			move++;
		}
		else{
			L.data[i-move]=L.data[i];
		}
	}
	L.length-=move;
}

//18-二-4
bool ListDeleteRange(SqList&L,ElemType s,ElemType t){
	if(s>=t||L.length==0){
		std::cout<<"error"<<std::endl;
		return false;
	}
	int i=0;
	int enterRange=false;
	int move=0;
	for(;i<L.length&&L.data[i]<s;i++);
	if(i>=L.length) return false;
	for(;i<L.length&&L.data[i]<=t;i++,move++);
	if(move<=0) return false;
	for(;i<L.length;i++){
		L.data[i-move]=L.data[i];
	}
	L.length-=move;
	return true;
}

//18-二-5
bool ListDeleteRange(SqList&L,ElemType s,ElemType t){
	if(s>=t||L.length==0){
		std::cout<<"error"<<std::endl;
		return false;
	}
	int move=0;
	for(int i=0;i<L.length;i++){
		if(L.data[i]>=s&&L.data[i]<=t){
			move++;
		}
		else{
			L.data[i-move]=L.data[i];
		}
	}
	L.length-=move;
	return true;
}

//18-二-6
void ListDeleteSame(SqList&L){
	if(L.length==0)
		return;
	ElemType same=L.data[0];
	int move=0;
	for(int i=1;i<L.length;i++){
		if(same==L.data[i]){
			move++;
		}else{
			same=L.data[i];
			L.data[i-move]=L.data[i];
		}
	}
	L.length-=move;
}

//18-二-7 这个已经在上面联系过

//18-二-8
void ListExchange(SqList&L,int m,int n){
	int ai,bi;
	ElemType temp;
	if(m>n){
		//0 1 2 a b
		//0 1 b a 2
		//0 a b 1 2
		//b a 0 1 2
		//长者作为进攻方，为偶数，则不会改变被进攻方的顺序，为奇数则会改变被进攻方的顺序，如上述序列
		ai=m-1;
		bi=m+n-1;
		while(ai>0){
			temp = L.data[ai];
			L.data[ai] = L.data[bi];
			L.data[bi] = temp;
			ai--;
			bi--;
		}
		//进攻方为奇数，置换完后，需要把被进攻方的顺序倒过来
		if(m%2!=0){
			for(int i=0;i<n/2;i++){
				temp = L.data[i];
				L.data[i] = L.data[n-i-1];
				L.data[n-i-1] = temp;
			}
		}
	}
	else{
		ai=0;
		bi=m;
		while(bi<m+n){
			temp = L.data[ai];
			L.data[ai] = L.data[bi];
			L.data[bi] = temp;
			ai++;
			bi++;
		}
		if(n%2!=0){
			for(int i=n;i<m/2;i++){
				temp = L.data[i];
				L.data[i] = L.data[m-i-1];
				L.data[m-i-1] = temp;
			}
		}
	}
}

//18-二-8 使用倒转法解题
typedef int ElemType;
void ListReverse(ElemType L[],int left,int right,int arrLen){
	if(left>=right||left>=arrLen||right>=arrLen)
		return;
	int mid=(left+right)/2;
	ElemType temp;
	for(int i=left;i<=mid;i++){
		temp = L[i];
		L[i] = L[arrLen-i-1];
		L[arrLen-i-1] = temp;
	}
}

void ListExchange(ElemType L[],int m,int n,int arrLen){
	ListReverse(L,0,arrLen-1,arrLen);
	ListReverse(L,0,n-1,arrLen);
	ListReverse(L,n,arrLen-1,arrLen);
}

//18-二-9
void ListFind(SqList&L,ElemType e){
	if(L.length==0)
		return;
	int up=0,down=L.length-1,mid=0;
	if(L.data[up]==e){
		e=L.data[up+1];
		L.data[up+1]=L.data[up];
		L.data[up]=e;
		return;
	}
	if(L.data[down]==e)
		return;
	while(up<down){
		mid = (down+up)/2;												//错误，写成(down-up)/2减号了，会死循环
		if(L.data[mid]==e&&mid<L.length-1){
			e=L.data[mid+1];
			L.data[mid+1]=L.data[mid];
			L.data[mid]=e;
			return;
		}else if(L.data[mid]<e){
			up=mid+1;													//错误，没有加1，在上界与下界邻近时，会造成死循环，如(3+2)/2=2,下一次下界仍然是2
		}else{
			down=mid-1;													//错误同上
		}
	}
	//没找到相同的元素
	int insertPos=mid;
	if(L.data[mid]<e){
		insertPos++;
	}
	//直接放在最后
	if(insertPos>=L.length){
		L.data[L.length]=e;
		L.length++;
		return;
	}
	//需要进行插入操作
	for(int i=L.length-1;i>=mid;i++){
		L.data[i+1]=L.data[i];
	}
	L.data[mid]=e;
	L.length++;
}

//18-二-10
void ListShift(SqList&L,int p){
	int ai,bi;
	int m=p;
	int n=L.length-m;
	ElemType temp;
	if(m>n){
		//0 1 2 a b
		//0 1 b a 2
		//0 a b 1 2
		//b a 0 1 2
		//长者作为进攻方，为偶数，则不会改变被进攻方的顺序，为奇数则会改变被进攻方的顺序，如上述序列
		ai=m-1;
		bi=m+n-1;
		while(ai>0){
			temp = L.data[ai];
			L.data[ai] = L.data[bi];
			L.data[bi] = temp;
			ai--;
			bi--;
		}
		//进攻方为奇数，置换完后，需要把被进攻方的顺序倒过来
		if(m%2!=0){
			for(int i=0;i<n/2;i++){
				temp = L.data[i];
				L.data[i] = L.data[n-i-1];
				L.data[n-i-1] = temp;
			}
		}
	}
	else{
		ai=0;
		bi=m;
		while(bi<m+n){
			temp = L.data[ai];
			L.data[ai] = L.data[bi];
			L.data[bi] = temp;
			ai++;
			bi++;
		}
		if(n%2!=0){
			for(int i=n;i<m/2;i++){
				temp = L.data[i];
				L.data[i] = L.data[m-i-1];
				L.data[m-i-1] = temp;
			}
		}
	}
}

//18-二-11
typedef int ElemType;
ElemType ListMiddle(ELemType S1[],ElemType S2[],int n){
	int left1=0,right1=n-1,left2=0,right2=n-1,mid1,mid2;
	while(left1<right1||left2<right2){
		mid1=(right1+left1)/2;
		mid2=(right2+left2)/2;
		if(S1[mid1]==S2[mid2]){
			return S1[mid1];
		}else if(S1[mid1]<S2[mid2]){
			if((right1+left1)%2==0){
				left1=mid1+1;
			}else{
				left1=mid1;
			}
			right2=mid2;
		}else if(S1[mid1]>S2[mid2]){
			right1=mid1;
			if((right2+left2)%2==0){
				left2=mid2+1;
			}else{
				left2=mid2;
			}
		}
	}
	return S1[left1]>S2[left2]?S2[left2]:S1[left1];
}

//18-二-12 n^2算法
typedef int ElemType;
int ListFindMain(ElemType L[],int arrLen){
	int mainNum;
	int times=0;
	for(int i=0;i<arrLen;i++){
		mainNum=L[i];
		times=1;
		for(int j=i+1;j<arrLen;j++){
			if(L[j]==mainNum){
				times++;
			}
		}
		if(times>L.length/2){
			return mainNum;
		}
	}
	return -1;
}

//18-二-12 n算法
int ListFindMain(ElemType L[],int arrLen){
	if(arrLen==0)
		return -1;
	int mainNum=L[0],count=1;
	for(int i=1;i<arrLen;i++){
		if(L[i]==mainNum){
			count++;
		}else{
			count--;
			if(count==0){
				mainNum=L[i];
				count=1;
			}
		}
	}
	if(count==0){
		count=0;
		for(int i=0;i<arrLen;i++){
			if(mainNum==L[i]){
				count++;
			}
		}
	}
	if(count>arrLen/2){
		return mainNum;
	}
	return -1;
}
*/

typedef int ElemType;
typedef struct LNode{
	ElemType data;
	LNode* next;
}ListNode,*PListNode;

//头插法 n
PListNode CreateList1(){
	PListNode head = new ListNode;
	head->next = nullptr;
	ElemType e;
	PListNode insert;
	while (std::cin >> e){
		insert = new ListNode;
		insert->data = e;
		insert->next = head->next;
		head->next = insert;
	}
	return head;
}

//尾插法 n
PListNode CreateList2(){
	PListNode head = new ListNode;
	PListNode preNode = head;
	head->next = nullptr;
	ElemType e;
	PListNode insert;
	while (std::cin >> e){		
		insert = new ListNode;
		insert->data = e;
		insert->next = nullptr;
		preNode->next = insert;
		preNode = insert;
	}
	return head;
}

PListNode GetElem(PListNode L, int i){
	L = L->next;
	int pos = 0;
	while (L&&pos++<i){
		L = L->next;
	}
	return L;
}

PListNode LocateElem(PListNode L,ElemType e){
	L = L->next;
	while (L&&L->data!=e){
		L = L->next;
	}
	return L;
}

PListNode ReverseList(PListNode L){
	PListNode preNode=nullptr,curNode=L->next,nextNode;
	while (curNode){
		nextNode = curNode->next;
		curNode->next = preNode;
		preNode = curNode;
		curNode = nextNode;
	}
	L->next = preNode;
	return L;
}

void ShowList(PListNode L){
	L = L->next;
	while (L){
		std::cout << L->data << " ";
		L = L->next;
	}
	std::cout << std::endl;
}

void Chapter2(){
	int ainit[] = { 3, 5, 8, 11 };
	int binit[] = { 2, 6, 8, 9, 11, 15, 20 };

	///////////////////////////////////////////////////////////
	//链表
	//LinkList<int> La;
	//LinkList<int> Lb;
	
	//ListInit<int>(La, ainit,sizeof ainit/sizeof(int));
	//ListInit<int>(Lb, binit, sizeof binit / sizeof(int));
	//ListPrint<int>(La);
	//ListPrint<int>(Lb);
	//ListUnion<int>(La, Lb);
	//ListPrint<int>(La);

	//LinkList<int> Lc;
	//La.ClearList();
	//Lb.ClearList();
	//ListInit<int>(La, ainit, sizeof ainit / sizeof(int));
	//ListInit<int>(Lb, binit, sizeof binit / sizeof(int));
	//ListUnion<int>(Lc, La, Lb);
	//ListPrint<int>(Lc);

	//ListInit<int>(La, ainit,sizeof ainit/sizeof(int));
	//ListPrint(La);
	//La.ListDelete(1);
	//ListPrint(La);

	//////////////////////////////////////////////////////////
	//顺序表
	//SqList<int> Ld,Le,Lf,Lg;
	//ListInit(Le, ainit, sizeof ainit / sizeof(int));
	//ListInit(Lf, binit, sizeof binit / sizeof(int));
	//ListUnion<int>(Ld, Le, Lf);
	//ListPrint<int>(Ld);

	//Ld.ClearList();
	//ListInit(Ld, ainit, sizeof ainit / sizeof(int));
	//ListPrint(Ld);
	//Ld.ListDelete(1);
	//ListPrint(Ld);

	PListNode  L = CreateList2();
	ShowList(L);
	ReverseList(L);
	ShowList(L);
	//std::cout << LocateElem(L, 3)->data << std::endl;
}