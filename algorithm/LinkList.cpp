#pragma warning(disable : 4786)
#include <iostream>
#include <queue>
#include <map>
#include <math.h>
#include <WINDOWS.H>
#include <time.h>
////////////////////////////////////////////////////
//链表
////////////////////////////////////////////////////
typedef int ListElemType;
struct ListNode{
	ListElemType data;
	ListNode* next;
};

//37 2 1/2
ListNode* DeleteElem(ListNode* pre,ListNode* cur,ListElemType e){
	if(cur==NULL)
		return NULL;
	if(cur->data==e){
		ListNode* next = cur->next;
		if(pre){
			pre->next = next;
		}
		delete cur;
		return DeleteElem(pre,next,e);
	}
	else{
		DeleteElem(cur,cur->next,e);
		return cur;
	}
}

//通过输入创建链表
ListNode* CreateList(bool hasHead=false){
	ListNode *head=NULL,*cur,*pre=NULL;
	if(hasHead){
		head = new ListNode;
		head->data = 0;
		head->next = NULL;
		pre = head;
	}
	ListElemType e;
	while(std::cin>>e){
		cur= new ListNode;
		if(pre)
			pre->next = cur;
		cur->data = e;
		cur->next = NULL;
		pre=cur;
		if(head==NULL)
			head=cur;
	}
	return head;
}

ListNode* CreateList(ListElemType arr[],int size){
	ListNode *head=NULL,*cur,*pre=NULL;
	int idx=0;
	while(idx<size){
		cur= new ListNode;
		if(pre)
			pre->next = cur;
		cur->data = arr[idx];
		cur->next = NULL;
		pre=cur;
		if(head==NULL)
			head=cur;
		idx++;
	}
	return head;
}

//获得链表尾节点
ListNode* GetTail(ListNode* node){
	while(node->next)node=node->next;
	return node;
}

//打印链表
void ShowList(ListNode* node,bool hasHead=false){
	if(node==NULL){
		std::cout<<"list is null"<<std::endl;
		return;
	}
	if(hasHead)
		node = node->next;
	while(node){
		std::cout<<node->data<<" ";
		node = node->next;
	}
	std::cout<<std::endl;
}

//37 2 5
ListNode* ReverseList(ListNode* node){
	ListNode *head=node,*pre=NULL,*cur=node->next,*next=NULL;
	while(cur){
		next = cur->next;
		cur->next = pre;
		pre = cur;
		cur = next;
	}
	head->next=pre;
	return head;
}

//37 2 3
void ReverseShowList(ListNode* node){
	ReverseList(node);
	ShowList(node,true);
	ReverseList(node);
}

//37 2 4 node 非头节点
ListNode* DeleteMinElem(ListNode* node){
	ListNode *cur=node->next,*pre=NULL,*minPre=NULL,*min=node,*head=node;
	while(cur){
		if(cur->data<min->data){
			minPre=pre;
			min=cur;
		}
		pre=cur;
		cur=cur->next;
	}
	if(min==head){
		head=min->next;
		delete min;
	}else{
		minPre->next = min->next;
		delete min;
	}
	return head;
}

//37 2 6 low非头节点
//冒泡排序 增序
void BubbleSort(ListNode* low,ListNode* high){
	if(low==NULL||high==NULL){
		return;
	}
	bool hasBubble=false;
	ListElemType e;
	ListNode *final=NULL,*j=NULL;
	while(final!=low){
		j=low;
		while(j->next!=final){
			if(j->data>j->next->data){
				e=j->data;
				j->data=j->next->data;
				j->next->data=e;
			}
			j=j->next;
		}
		final=j;
	}
}

//37 2 7 node为头节点
void DeleteRange(ListNode*node,ListElemType min,ListElemType max){
	/* 链表有序的情况下的删除
	while(node->next&&node->next->data<min)node=node->next;
	ListNode*delElem;
	while(node->next&&node->next->data<=max){
		delElem=node->next;
		node->next=node->next->next;
		delete delElem;
	}*/
	ListNode*delElem;
	while(node->next){
		if(node->next->data>=min&&node->next->data<=max){
			delElem=node->next;
			node->next=node->next->next;
			delete delElem;
		}else{
			node=node->next;
		}
	}
}

//获得链表长度
int ListLen(ListNode*node){
	if(node==NULL)return 0;
	int i=0;
	while(node){
		i++;
		node=node->next;
	}
	return i;
}

//32 2 8带头节点
ListNode* FindSameNode(ListNode*a,ListNode*b){
	int al=ListLen(a);
	int bl=ListLen(b);
	if(al>bl){
		int move=al-bl;
		while(move>0){
			move--;
			a=a->next;
		}
	}
	else{
		int move=bl-al;
		while(move>0){
			move--;
			b=b->next;
		}
	}
	while(a&&b&&a->next!=b->next){
		a=a->next;
		b=b->next;
	}
	return a?a->next:NULL;
}

//////////////////////////////////////////////
//顺序表
//////////////////////////////////////////////
typedef int ArrayElemType;
int default_sort_func(int& a,int& b){
	if(a>b)
		return 1;
	else if(a==b)
		return 0;
	else
		return -1;
}

#define SORT_PARAM int (sortFunc)(T&,T&)
#define SORT_FUNC sortFunc
#define BIG(a,b) (sortFunc(a,b)>0)
#define SMALL(a,b) (sortFunc(a,b)<0)
#define EBIG(a,b) (sortFunc(a,b)>=0)
#define ESMALL(a,b) (sortFunc(a,b)<=0)

//打印数组
void ShowArray(ArrayElemType array[],int len){
	for(int i=0;i<len;i++){
		std::cout<<array[i]<<" ";
	}
	std::cout<<std::endl;
}

template<typename T>
int ArrayDelete(T arr[],int size,int idx){
	if(idx<0||idx>=size)
		return size;
	if(idx==size-1)
		return size-1;
	memcpy(arr+idx,arr+idx+1,(size-1)*sizeof(T));
	return size-1;
}

//快排基准数归位，从小到大排序
template<typename T>
int Partition(T array[],int low,int high,SORT_PARAM){
	T pivot = array[low];
	while(low<high){
		while(low<high&&EBIG(array[high],pivot))high--;
		array[low]=array[high];
		while(low<high&&ESMALL(array[low],pivot))low++;
		array[high]=array[low];
	}
	array[low]=pivot;
	return low;	
}

//快排
template<typename T>
void QuickSort(T array[],int low,int high,SORT_PARAM){
	if(low>=high)
		return;
	int mid=Partition<T>(array,low,high,SORT_FUNC);
	QuickSort<T>(array,low,mid-1,SORT_FUNC);
	QuickSort<T>(array,mid+1,high,SORT_FUNC);
}
#define QuickSortInt(arr,low,high) QuickSort<int>(arr,low,high,default_sort_func)

//插入排序
void InsertSort(ArrayElemType array[],int arrlen){
	int i,j;
	ArrayElemType e;
	for(i=1;i<arrlen;i++){
		e=array[i];
		for(j=i;j>0&&e<array[j-1];j--){
			array[j]=array[j-1];
		}
		array[j]=e;
	}
}

//折半插入排序
void BinInsertSort(ArrayElemType array[],int arrlen){
	int i,j,left,right,mid;
	ArrayElemType e;
	for(i=1;i<arrlen;i++){
		e=array[i];
		left=0;
		right=i-1;
		//这个等号一定要有，否则left所在的值有可能是比e要小，当left与right相等时，说明这个数与e是最相近的，但不能确定是否小于e
		//所以需要再加一轮的比较才知道
		while(left<=right){
			mid=(left+right)/2;
			if(array[mid]<e)
				left=mid+1;
			else if(array[mid]>e)
				right=mid-1;
			else{
				left=mid;
				break;
			}
		}
		for(j=i;j>left;j--){
			array[j]=array[j-1];
		}
		array[left]=e;
	}
}

//折半查找 总是返回一个大于等于目标值的数的位置
int BinFind(ArrayElemType array[],int arrlen,ArrayElemType x){
	int left=0,right=arrlen-1,mid;
	while(left<=right){
		mid=(left+right)/2;
		if(array[mid]<x){
			left=mid+1;
		}else if(array[mid]>x){
			right=mid-1;
		}else{
			return mid;
		}
	}
	if(left<0||left>=arrlen)
		return -1;
	return left;
}

//希尔排序
void ShellSort(ArrayElemType array[],int arrlen){
	int i,j;
	ArrayElemType e;
	/* 根据概念的编写方法
	for(int gap=arrlen/2;gap>0;gap/=2){
		for(int gp=0;gp<gap;gp++){
			for(i=gap+gp;i<arrlen;i+=gap){
				e=array[i];
				for(j=i;j>0&&e<array[j-gap];j-=gap){
					array[j]=array[j-gap];
				}
				array[j]=e;
			}
		}
		ShowArray(array,arrlen);
	}*/
	//不一组排完后，再排下一组，而是不断的进行组切换，有点像多线程工作
	for(int gap=arrlen/2;gap>0;gap/=2){
		for(i=gap;i<arrlen;i++){
			e=array[i];
			for(j=i;j-gap>=0&&e<array[j-gap];j-=gap){
				array[j]=array[j-gap];
			}
			array[j]=e;
		}
		//ShowArray(array,arrlen);
	}
}

//顺序存储冒泡排序
void BubbleSort(ArrayElemType array[],int low,int high){
	if(low>=high)
		return;
	bool hasBubble=false;
	ArrayElemType e;
	for(int i=low;i<=high;i++){
		hasBubble=false;
		for(int j=high;j>i;j--){
			if(array[j]<array[j-1]){
				hasBubble=true;
				e=array[j];
				array[j]=array[j-1];
				array[j-1]=e;
			}
		}
		if(!hasBubble)
			return;
	}
	/*
	for(int i=low;i<high;i++){
		hasBubble=false;
		for(int j=low;j<high-i;j++){
			if(array[j]>array[j+1]){
				hasBubble=true;
				e=array[j];
				array[j]=array[j+1];
				array[j+1]=e;
			}
		}
		if(!hasBubble)
			return;
	}*/
}

//选择排序
void SelectSort(ArrayElemType arr[],int size){
	ArrayElemType minV=0,minP=0;
	for(int i=0;i<size;i++){
		minV=arr[i];
		minP=i;
		for(int j=i+1;j<size;j++){
			if(minV>arr[j]){
				minP=j;
				minV=arr[j];
			}
		}
		minV=arr[i];
		arr[i]=arr[minP];
		arr[minP]=minV;
	}
}

//归并排序
//a为前半部分，b为后半部分，合并的过程理解成排序的过程，c是辅助数组
void MergeArray(ArrayElemType a[],int sa,ArrayElemType b[],int sb,ArrayElemType c[]){
	int ia=0,ib=0,ic=0,i=0;
	while(ia<sa&&ib<sb){
		if(a[ia]<b[ib]){
			c[ic++]=a[ia++];
		}else{
			c[ic++]=b[ib++];
		}
	}
	while(ia<sa){
		c[ic++]=a[ia++];
	}
	while(ib<sb){
		c[ic++]=b[ib++];
	}
	while(i<ic){
		a[i]=c[i];
		i++;
	}
}

void MergeSortRecursion(ArrayElemType a[],int left,int right,ArrayElemType c[]){
	if(left==right)
		return;
	int mid=(left+right)/2;
	MergeSortRecursion(a,left,mid,c);
	MergeSortRecursion(a,mid+1,right,c);
	MergeArray(a+left,mid-left+1,a+mid+1,right-mid,c);
	//ShowArray(a+left,right-left+1);
}

void MergeSort(ArrayElemType a[],int size){
	int *c=new int[size];
	MergeSortRecursion(a,0,size-1,c);
	delete[] c;
}

//计数排序
void CountSort(ArrayElemType arr[],int size){
	int max=arr[0],min=arr[0],i=0;
	for(i=1;i<size;i++){
		if(max<arr[i]){
			max=arr[i];
		}
		if(min>arr[i]){
			min=arr[i];	
		}
	}
	if(min<0)return;
	int countSize=max+1;
	int *count = new int[countSize];
	ArrayElemType *sort = new ArrayElemType[size];
	memset(count,0,countSize*4);
	for(i=0;i<size;i++){
		count[arr[i]]++;
	}
	for(i=1;i<countSize;i++){
		count[i]+=count[i-1];
	}
	//从后往前，在计数排序中并不是必须的，但是基数排序中，必须这么做，
	//因为正是个位数的排序影响了十位数相同但个位数不同的排序
	for(i=size-1;i>=0;i--){
		int rank=count[arr[i]]--;
		sort[rank-1]=arr[i];
	}
	memcpy(arr,sort,size*sizeof(ArrayElemType));
	delete[] count;
	delete[] sort;
}

//基数排序
#define GetNumber(num,idx) (num/((int)pow(10,idx-1))%10)
void RadixSort(ArrayElemType arr[],int size,int digit){
	static int count[10];
	ArrayElemType *sort = new ArrayElemType[size];
	int i=0,digitVal=0,isAllZero=true;
	for(int idx=1;idx<=digit;idx++){
		memset(count,0,40);
		isAllZero=true;
		for(i=0;i<size;i++){
			digitVal=GetNumber(arr[i],idx);
			if(digitVal!=0){
				isAllZero=false;
			}
			count[digitVal]++;
		}
		if(isAllZero)
			break;
		for(i=1;i<10;i++){
			count[i]+=count[i-1];
		}
		for(i=size-1;i>=0;i--){
			int rank=count[GetNumber(arr[i],idx)]--;
			sort[rank-1]=arr[i];
		}
		memcpy(arr,sort,size*sizeof(ArrayElemType));
	}
	delete[] sort;
}

//////////////////////////////////////////////////
//二叉堆
//二叉堆具有有序序列取最小或最大数的方便与效率
//同时又具有无序序列插入数据的方便与效率
//所以称之为优先队列，就是优先取最小或最大的数据
//////////////////////////////////////////////////
typedef int HeapElemType;
#define HeapLeft(i) (2*i+1)
#define HeapRight(i) (2*i+2)
#define HeapParent(i) ((i-1)/2)

void PrintHeap(HeapElemType arr[],int size,char*perBlank,char*format){
	int depth=ceil(log(size+1)/log(2));
	int blankLen=strlen(perBlank);
	std::queue<int>queue;
	queue.push(0);
	int curH=1,curNum=1,curIdx=0,lastIdx=1,firstBlank=pow(2,depth-curH)-0.5,secondBlank=0,totalBlank=pow(2,depth)-1;
	for(int i=0;i<firstBlank;i++){
		std::cout<<perBlank;
	}
	int node;
	while(queue.size()!=0){
		node=queue.front();	
		if(node>=0)
			printf(format,arr[node]);
		else
			std::cout<<perBlank;
		for(int i=0;i<secondBlank;i++){
			std::cout<<perBlank;
		}
		curIdx++;
		queue.pop();
		if(node>=0){
			int left=HeapLeft(node),right=HeapRight(node);
			if(left<size)
				queue.push(left);
			else
				queue.push(-1);
			if(right<size)
				queue.push(right);
			else
				queue.push(-1);
		}else{
			queue.push(-1);
			queue.push(-1);
		}
		if(curIdx==lastIdx){
			curH++;
			if(curH>depth)
				break;
			curNum=pow(2,curH-1);
			lastIdx=curIdx+curNum;
			//计算起始空格
			firstBlank=pow(2,depth-curH)-0.5;
			if(curNum>1)
				secondBlank=(totalBlank-firstBlank*2-curNum)/(curNum-1);
			//打印起始空格
			std::cout<<std::endl;
			for(int i=0;i<firstBlank;i++){
				std::cout<<perBlank;
			}
		}
	}
	std::cout<<std::endl;
}

template<typename T>
void MinHeapFloat(T arr[],int floatIdx,SORT_PARAM){
	int i=floatIdx;
	T value=arr[floatIdx];
	//插入值从底向上，不断的往上浮
	do{ 
		i=HeapParent(i);
		if(BIG(arr[i],value)){
			arr[floatIdx]=arr[i];
		}else{
			break;
		}
		floatIdx=i;
	}while(i>0);
	arr[floatIdx]=value;
}
#define MinHeapFloatInt(arr,size) MinHeapFloat<int>(arr,size,default_sort_func)

template<typename T>
void MinHeapSink(T arr[],int size,int sinkIdx,SORT_PARAM){
	T curVal=arr[sinkIdx];
	//从上往下 和是重的元素往下沉的过程
	//内层循环确保整颗树是合法堆，进行内层循环前，必须只是根树可能非法，其它子树必须合法，否则出错
	for(int j=HeapLeft(sinkIdx);j<size;j=HeapLeft(j)){
		if(j+1<size&&BIG(arr[j],arr[j+1]))
			j++;
		if(BIG(curVal,arr[j])){
			//为什么不用交换元素，与快排一样，想着一块石头不断的下沉，前面的空缺总会由后面的来填充
			arr[sinkIdx]=arr[j];
			sinkIdx=j;
		}else{
			break;
		}
	}
	arr[sinkIdx]=curVal;
}
#define MinHeapSinkInt(arr,size) MinHeapSink<int>(arr,size,default_sort_func)

template<typename T>
int MinHeapInsert(T arr[],int size,T value,SORT_PARAM){
	arr[size]=value;
	MinHeapFloat<T>(arr,size,SORT_FUNC);
	return size+1;
}
#define MinHeapInsertInt(arr,size,value) MinHeapInsert<int>(arr,size,value,default_sort_func)

template<typename T>
int MinHeapDelete(T arr[],int size,SORT_PARAM){
	T temp=arr[0];
	arr[0]=arr[size-1];
	arr[size-1]=temp;
	size--;
	MinHeapSink<T>(arr,size,0,SORT_FUNC);
	return size;
}
#define MinHeapDeleteInt(arr,size) MinHeapDelete<int>(arr,size,default_sort_func)

template<typename T>
void MinHeapSort(T arr[],int size,SORT_PARAM){
	while(size>1){
		size=MinHeapDelete<T>(arr,size,SORT_FUNC);
	}
}
#define MinHeapSortInt(arr,size) MinHeapSort<int>(arr,size,default_sort_func)

template<typename T>
void InitMinHeap(T arr[],int size,SORT_PARAM){
	int cur=0;
	//外层循环确保子树是合法堆 从下往上 
	for(int i=size/2-1;i>=0;i--){
		MinHeapSink<T>(arr,size,i,SORT_FUNC);
		//PrintHeap(arr,size,"  ","%02d");
	}
}
#define InitMinHeapInt(arr,size) InitMinHeap<int>(arr,size,default_sort_func)

template<typename T>
void RangeSort(T arr[],int totalSize,int rangeSize,SORT_PARAM){
	InitMinHeap<T>(arr,rangeSize,SORT_FUNC);
	//PrintHeap(arr,rangeSize,"  ","%02d");
	for(int i=totalSize-1;i>=rangeSize;i--){
		if(BIG(arr[i],arr[0])){
			T& temp=arr[0];
			arr[0]=arr[i];
			arr[i]=temp;
			MinHeapSink<T>(arr,rangeSize,SORT_FUNC);
			//PrintHeap(arr,rangeSize,"  ","%02d");
		}else{
			i--;
		}
	}
}

//////////////////////////////////////////////////
//分块查找
//////////////////////////////////////////////////
struct BlockSearch{
	enum BlockSearchState{
		SEARCH_ERROR=-2,
		SEARCH_FAILED=-1,
	};
	struct SearchIdx{
		ListNode* start;
		ListNode* end;
		int blockSize;
	};
	BlockSearch(ListElemType arr[],int size):searchTable(NULL),tableSize(0){
		head=CreateList(arr,size);
		elemSize=size;
		updateSearchIdx();
	}
	void insert(ListElemType elem){
		int i=idxSearch(elem);
		if(i==SEARCH_FAILED){
			ListNode* newEnd=new ListNode;
			newEnd->data=elem;
			newEnd->next=NULL;
			searchTable[tableSize-1].end->next=newEnd;
			searchTable[tableSize-1].end=newEnd;
			searchTable[tableSize-1].blockSize++;
			elemSize++;
		}
		else if(i==SEARCH_ERROR){
			head=new ListNode;
			head->data=elem;
			head->next=NULL;
			elemSize++;
			updateSearchIdx();
		}else{
			ListNode* newNode=new ListNode;
			newNode->data=elem;
			newNode->next=searchTable[i].start->next;
			searchTable[i].start->next=newNode;
			searchTable[i].blockSize++;
			elemSize++;
			ListElemType temp=searchTable[i].start->data;
			searchTable[i].start->data=newNode->data;
			newNode->data=temp;
			if(searchTable[i].end==searchTable[i].start){
				searchTable[i].end=newNode;
			}
		}
	}
	void remove(ListElemType elem){
		int i=idxSearch(elem);
		//没有适合的索引区间
		if(i==-1)return;
		//刚好等于索引表中的值
		if(searchTable[i].end->data==elem){
			ListNode *cur=searchTable[i].start,*biggest=cur,*preBiggest=NULL;
			//只含有一项，开头与结尾重合，导致索引项被删除，所以需要更新索引表
			if(cur==searchTable[i].end){
				if(cur==head){
					head=cur->next;
					delete cur;
				}
				else if(cur->next==NULL){
					ListNode* pre=head;
					while(pre->next!=cur){
						pre=pre->next;
					}
					pre->next=NULL;
					delete cur;
				}
				else{
					ListNode* deleteNode=cur->next;
					cur->data=cur->next->data;
					cur->next=cur->next->next;
					delete deleteNode;
				}
				
				elemSize--;
				updateSearchIdx();
				return;
			}
			//至少含有两项,开头与结尾
			if(i>0)preBiggest=searchTable[i-1].end;
			while(cur->next!=searchTable[i].end){
				if(biggest->data<cur->next->data){
					biggest=cur->next;
					preBiggest=cur;
				}
				cur=cur->next;
			}
			searchTable[i].end->data=biggest->data;
			if(preBiggest){
				preBiggest->next=biggest->next;
			}
			//如果开头结点正好是最大值的节点，那么就把最大值往后移一个节点
			if(biggest==searchTable[i].start){
				searchTable[i].start=biggest->next;
			}
			//删除的节点刚好是整个链表的头节点
			if(head==biggest){
				head=biggest->next;
			}
			searchTable[i].blockSize--;
			elemSize--;
			delete biggest;
		}else{
			ListNode* cur=searchTable[i].start;
			ListNode* end=searchTable[i].end;
			ListNode* pre=NULL;
			if(i>0)pre=searchTable[i-1].end;
			while(cur&&cur!=end->next&&cur->data!=elem){
				pre=cur;
				cur=cur->next;
			}
			//没找到要删除的点
			if(cur==NULL||cur->data!=elem)
				return;
			if(pre){
				pre->next=cur->next;
			}
			//如果开头结点正好是要删除的节点，那么就把最大值往后移一个节点
			if(cur==searchTable[i].start){
				searchTable[i].start=cur->next;
			}
			//删除的节点刚好是整个链表的头节点
			if(head==cur){
				head=cur->next;
			}
			searchTable[i].blockSize--;
			elemSize--;
			delete cur;
		}
	}
	int search(ListElemType elem){
		int i=idxSearch(elem);
		//没有适合的索引区间
		if(i==SEARCH_ERROR||i==SEARCH_FAILED)return SEARCH_FAILED;
		int idx=0;
		for(int j=0;j<i;j++){
			idx+=searchTable[j].blockSize;
		}
		//刚好等于索引表中的值
		if(searchTable[i].end->data==elem){
			idx+=searchTable[i].blockSize-1;
			return idx;
		}
		ListNode* cur=searchTable[i].start;
		ListNode* end=searchTable[i].end;
		while(cur&&cur!=end->next&&cur->data!=elem){
			cur=cur->next;
			idx++;
		}
		if(cur==NULL||cur->data!=elem)
			return SEARCH_FAILED;
		return idx;
	}
	void updateSearchIdx(){
		if(searchTable){
			delete[] searchTable;
			searchTable=NULL;
			tableSize=0;
		}
		if(head==NULL){
			return;
		}
		BubbleSort(head,GetTail(head));
		int blockSize=(int)sqrt(elemSize);
		tableSize=elemSize/blockSize;
		searchTable = new SearchIdx[tableSize];
		ListNode* cur=head;
		for(int i=0;i<tableSize;i++){
			SearchIdx& searchInfo=searchTable[i];
			searchInfo.start=searchInfo.end=cur;
			searchInfo.blockSize=blockSize;
			int j=1;
			while(j++<blockSize)searchInfo.end=searchInfo.end->next;
			cur=searchInfo.end->next;
		}
		//均分完后，仍然有下一个
		if(cur){
			int i=0;
			while(cur->next){
				cur=cur->next;
				i++;
			}
			searchTable[tableSize-1].blockSize=blockSize+i;
			searchTable[tableSize-1].end=cur;
		}
	}
	void showArray(){
		if(head==NULL){
			std::cout<<"block search is null"<<std::endl;
			return;
		}
		ShowList(head);
		std::cout<<"elemSize:"<<elemSize<<" tableSize:"<<tableSize<<std::endl;
		for(int i=0;i<tableSize;i++){
			std::cout<<"start:"<<searchTable[i].start->data<<" end:"<<searchTable[i].end->data<<std::endl;
		}
	}
	~BlockSearch(){
		delete[] searchTable;
		ListNode*next=NULL;
		while(head){
			next=head->next;
			delete head;
			head=next;
		}
		head=NULL;
	}
private:
	int idxSearch(ListElemType elem){
		if(tableSize==0){
			return SEARCH_ERROR;
		}
		int low=0;
		int high=tableSize-1;
		int mid;
		while(low<=high){
			mid=(low+high)/2;
			if(searchTable[mid].end->data==elem||
				(searchTable[mid].end->data>elem&&(mid==0||searchTable[mid-1].end->data<elem))
				){
				break;
			}
			else if(searchTable[mid].end->data<elem){
				low=mid+1;
			}
			else{
				high=mid-1;
			}
		}
		if(mid>=tableSize)
			return SEARCH_FAILED;
		return mid;
	}
	SearchIdx *searchTable;
	int elemSize;
	int tableSize;
	ListNode* head;
};

//////////////////////////////////////////////
//栈 顺序存储
//////////////////////////////////////////////
#define MaxSize 50
typedef int StackElemType;
struct Stack{
	StackElemType data[MaxSize];
	int top;
};

void InitStack(Stack* s){
	s->top=-1;
}

bool StackEmpty(Stack* s){
	return s->top==-1;
}

bool Push(Stack *s,StackElemType x){
	if(s->top==MaxSize-1)
		return false;
	s->top++;
	s->data[s->top]=x;
	return true;
}

bool Pop(Stack *s,StackElemType* x){
	if(s->top==-1)
		return false;
	*x=s->data[s->top];
	s->top--;
	return true;
}

bool GetTop(Stack *s,StackElemType *x){
	if(s->top==-1){
		return false;
	}
	*x=s->data[s->top];
	return true;
}

//////////////////////////////////////////////
//栈 链式存储
//////////////////////////////////////////////
struct LStack{
	ListNode* head;
};

bool InitStack(LStack* L){
	L->head=NULL;
	return true;
}

bool StackEmpty(LStack* L){
	return L->head==NULL;
}

bool Push(LStack *L,StackElemType x){
	ListNode* top=new ListNode;
	top->data=x;
	top->next=L->head;
	L->head=top;
	return true;
}

bool Pop(LStack *L,StackElemType* x){
	if(L->head==NULL)
		return false;
	*x=L->head->data;
	ListNode* head=L->head;
	L->head=L->head->next;
	delete head;
	return true;
}

bool GetTop(LStack *L,StackElemType *x){
	if(L->head==NULL)
		return false;
	*x=L->head->data;
	return true;
}

///////////////////////////////////////
//循环队列 顺序存储
///////////////////////////////////////
typedef int QueueElemType;
struct Queue{
	QueueElemType data[MaxSize];
	int front,rear;
};

void InitQueue(Queue* q){
	q->front=q->rear=0;
}

bool QueueEmpty(Queue* q){
	return q->front==q->rear;	
}

bool EnQueue(Queue* q,QueueElemType x){
	int next=(q->rear+1)%MaxSize;
	if(next==q->front)
		return false;
	q->data[q->rear]=x;
	q->rear=next;
	return true;
}

bool DeQueue(Queue* q,QueueElemType *x){
	if(q->front==q->rear)
		return false;
	*x=q->data[q->front];
	q->front=(q->front+1)%MaxSize;
	return true;
}

///////////////////////////////////////
//循环队列 链式存储
///////////////////////////////////////
struct LQueue{
	ListNode*front,*rear;
};

void InitQueue(LQueue* q){
	q->front=NULL;
	q->rear=NULL;
}

bool QueueEmpty(LQueue* q){
	return q->front==NULL;	
}

bool EnQueue(LQueue* q,QueueElemType x){
	ListNode* rear=new ListNode;
	rear->data = x;
	if(q->rear)
		q->rear->next = rear;
	q->rear=rear;
	if(!q->front)
		q->front = rear;
	return true;
}

bool DeQueue(LQueue* q,QueueElemType *x){
	if(q->front==NULL)
		return false;
	*x = q->front->data;
	ListNode* front=q->front;
	q->front=q->front->next;
	delete front;
	if(q->front==NULL)
		q->rear=NULL;
	return true;
}

////////////////////////////////////////////
//二叉树 106 5
#include <math.h>
typedef int TreeElemType;
struct BinTree{
	TreeElemType data[MaxSize];
};

//二叉链表
struct LBinTree{
	TreeElemType data;
	LBinTree *left,*right;
};

//线索二叉树
struct ThreadBinTree{
	TreeElemType data;
	ThreadBinTree *left,*right,*pre,*next;
};

//树的双亲表示法
struct PTNode{
	TreeElemType data;
	int parent;
};

struct PTree{
	PTNode nodes[MaxSize];
	int n;
};

//孩子表示法
struct ChildLink{
	int idx;
	ChildLink* next;
};

struct CLNode{
	TreeElemType data;
	ChildLink* child;
};

struct CLTree{
	CLNode nodes[MaxSize];
	int n;
};

//孩子兄弟表示法
struct CSTree{
	TreeElemType data;
	CSTree *child,*brother;
};

//二叉树的线索化 采用栈
void InitThreadBinTree2(ThreadBinTree*node){
	ThreadBinTree* pre=NULL;
	static ThreadBinTree *stack[MaxSize];
	int top=-1;
	stack[++top]=node;
	while(top!=-1){
		while(true){
			if(stack[top]->left){
				stack[++top]=stack[top]->left;
			}else{
				break;
			}
		}
		while(top!=-1){
			node=stack[top--];
			node->next=NULL;
			if(pre)
				pre->next=node;
			node->pre=pre;
			pre=node;
			if(node->right){
				stack[++top]=node->right;
				break;
			}
		}
	}
}

//二叉树线索化 采用递归
void InitThreadBinTree(ThreadBinTree*node,ThreadBinTree **pre){
	if(!node)
		return;
	InitThreadBinTree(node->left,pre);
	node->pre=*pre;
	node->next=NULL;
	if(*pre)
		(*pre)->next=node;
	*pre=node;
	InitThreadBinTree(node->right,pre);
}

ThreadBinTree* FirstNode(ThreadBinTree* node){
	while(node->pre)node=node->pre;
	return node;
}

void ShowThreadTree(ThreadBinTree* node){
	while(node){
		std::cout<<node->data<<" ";
		node=node->next;
	}
	std::cout<<std::endl;
}

int findAncient(int i,int j){
	double _1_log2=1/log(2);
	int iLayer = ceil(log(i+1)*_1_log2);
	int jLayer = ceil(log(j+1)*_1_log2);
	while(jLayer>iLayer){
		j/=2;
		jLayer = ceil(log(j+1)*_1_log2);
	}
	while(jLayer<iLayer){
		i/=2;
		iLayer = ceil(log(i+1)*_1_log2);
	}
	while(i!=j){
		i/=2;
		j/=2;
	}
	return i;
}

//递归算法求二叉树深度，核心思想是比较左子树和右子树的高度
int TreeDepth(LBinTree*node){
	if(node==NULL)
		return 0;
	int leftH=TreeDepth(node->left);
	int rightH=TreeDepth(node->right);
	return leftH>rightH?leftH+1:rightH+1;
}

int TreeDepth2(LBinTree*node){
	if(node==NULL)
		return 0;
	std::queue<LBinTree*>queue;
	queue.push(node);
	int h=0;
	int last=1,first=0;
	while(queue.size()!=0){
		node=queue.front();
		queue.pop();
		if(node->left)
			queue.push(node->left);
		if(node->right)
			queue.push(node->right);
		first++;
		if(first==last){
			h++;
			last=first+queue.size();
		}
	}
	return h;
}

void PreOrder(LBinTree*node){
	if(node==NULL)
		return;
	std::cout<<node->data<<" ";
	PreOrder(node->left);
	PreOrder(node->right);
}

void MidOrder(LBinTree*node){
	if(node==NULL)
		return;
	MidOrder(node->left);
	std::cout<<node->data<<" ";
	MidOrder(node->right);	
}

void PostOrder(LBinTree*node){
	if(node==NULL)
		return;
	PostOrder(node->left);
	PostOrder(node->right);	
	std::cout<<node->data<<" ";
}

void LevelOrder(LBinTree*node){
	std::queue<LBinTree*> queue;
	queue.push(node);
	while(queue.size()!=0){
		node = queue.front();
		std::cout<<node->data<<" ";
		queue.pop();
		if(node->left)
			queue.push(node->left);
		if(node->right)
			queue.push(node->right);
	}
	std::cout<<std::endl;
}

void PreOrder2(LBinTree*node){
	if(node==NULL)
		return;
	static LBinTree *stack[MaxSize];	
	LBinTree *cur=NULL,*pre=NULL;
	int top=-1;
	stack[++top]=node;
	while(top!=-1){
		while(true){
			std::cout<<stack[top]->data<<" ";
			if(stack[top]->left)
				stack[++top]=stack[top]->left;
			else
				break;
		}
		while(top!=-1){
			node=stack[top--];
			if(node->right){
				stack[++top]=node->right;
				break;
			}
		}
	}
	/*
	while(top!=-1){
		cur=stack[top--];
		std::cout<<cur->data<<" ";
		if(cur->right){
			stack[++top]=cur->right;
		}
		if(cur->left){
			stack[++top]=cur->left;
		}
	}*/
}

void MidOrder2(LBinTree*node){
	if(node==NULL)
		return;
	static LBinTree *stack[MaxSize];	
	LBinTree *cur=NULL,*pre=NULL;
	int top=-1;
	stack[++top]=node;
	while(top!=-1){
		while(true){
			if(stack[top]->left)
				stack[++top]=stack[top]->left;
			else
				break;
		}
		while(top!=-1){
			node=stack[top--];
			std::cout<<node->data<<" ";
			if(node->right){
				stack[++top]=node->right;
				break;
			}
		}
	}
}

void PostOrder2(LBinTree*node){
	if(node==NULL)
		return;
	static LBinTree *stack[MaxSize];	
	LBinTree *cur=NULL,*pre=NULL;
	int top=-1;
	stack[++top]=node;
	while(top!=-1){
		while(true){
			if(stack[top]->left)
				stack[++top]=stack[top]->left;
			else
				break;
		}
		node=NULL;
		while(top!=-1){
			//第二个判断避免死循环，由于此时根节点并没有打印，还保存在栈中，
			//于是右节点遍历打印完后，会去回到根节点，而此时，如果根节点再次遍历右节点，就会造成死循环
			if(stack[top]->right&&stack[top]->right!=node){
				stack[++top]=stack[top]->right;
				break;
			}
			else{
				node=stack[top--];
				std::cout<<node->data<<" ";
			}
		}
	}
}

enum TraverseTreeType{
	PRE,
	MID,
	POST
};

template<typename T>
T* PreInitBinTree(TreeElemType arr[],int size,int& idx){
	if(idx>=size||arr[idx]==0){
		idx++;
		return NULL;
	}
	T* node = new T;
	node->data=arr[idx++];
	node->left = PreInitBinTree<T>(arr,size,idx);
	node->right = PreInitBinTree<T>(arr,size,idx);
	return node;
}

template<typename T>
T* MidInitBinTree(TreeElemType arr[],int size,int& idx){
	if(idx>=size||arr[idx]==0){
		idx++;
		return NULL;
	}
	T* node = new T;
	node->left = PreInitBinTree<T>(arr,size,idx);
	node->data=arr[idx++];
	node->right = PreInitBinTree<T>(arr,size,idx);
	return node;
}

template<typename T>
T* PostInitBinTree(TreeElemType arr[],int size,int& idx){
	if(idx>=size||arr[idx]==0){
		idx++;
		return NULL;
	}	
	T* node = new T;
	node->left = PreInitBinTree<T>(arr,size,idx);
	node->right = PreInitBinTree<T>(arr,size,idx);
	node->data=arr[idx++];
	return node;
}

template<typename T>
T* InitBinTree(TreeElemType arr[],int size,int initType){
	int idx=0;
	switch(initType){
	case PRE:
		return PreInitBinTree<T>(arr,size,idx);
	break;
	case MID:
		return MidInitBinTree<T>(arr,size,idx);
	break;
	case POST:
		return PostInitBinTree<T>(arr,size,idx);
	break;
	};
	return NULL;
}

void ShowTree(LBinTree* root,int traverseType){
	switch(traverseType){
	case PRE:
		PreOrder(root);
		break;
	case MID:
		MidOrder(root);
		break;
	case POST:
		PostOrder(root);
		break;
	};
	std::cout<<std::endl;
}

void ShowTree2(LBinTree* root,int traverseType){
	switch(traverseType){
	case PRE:
		PreOrder2(root);
		break;
	case MID:
		MidOrder2(root);
		break;
	case POST:
		PostOrder2(root);
		break;
	};
	std::cout<<std::endl;
}

///////////////////////////////////////////////////////
//二叉排序树
///////////////////////////////////////////////////////

LBinTree* BST_Search(LBinTree*node,TreeElemType value){
	while(node&&node->data!=value){
		if(node->data<value){
			node=node->right;
		}else{
			node=node->left;
		}	
	}
	return node;
}

bool BST_Insert(LBinTree*node,TreeElemType value){
	LBinTree* insert=new LBinTree;
	insert->data=value;
	insert->left=insert->right=NULL;
	while(true){
		if(node->data<value){
			if(node->right==NULL){
				node->right=insert;
				return true;
			}
			else{
				node=node->right;
			}
		}else if(node->data>value){
			if(node->left==NULL){
				node->left=insert;
				return true;
			}else{
				node=node->left;	
			}
		}else{
			return false;
		}
	}
}

LBinTree* BST_Create(TreeElemType arr[],int size){
	LBinTree* root=new LBinTree;
	root->data=arr[0];
	root->left=root->right=NULL;
	for(int i=0;i<size;i++){
		BST_Insert(root,arr[i]);
	}
	return root;
}

LBinTree* BST_Delete(LBinTree*node,TreeElemType value){
	LBinTree *parent=NULL,*root=node;
	while(node&&node->data!=value){
		parent=node;
		if(node->data<value){
			node=node->right;
		}else{
			node=node->left;
		}	
	}
	if(node==NULL)
		return root;
	if(node->left&&node->right==NULL){
		if(parent){
			if(parent->left==node){
				parent->left=node->left;
			}else{
				parent->right=node->left;
			}
		}else{
			root=node->left;
		}
	}else if(node->left==NULL&&node->right){
		if(parent){
			if(parent->left==node){
				parent->left=node->right;
			}else{
				parent->right=node->right;
			}
		}else{
			root=node->left;
		}
	}else if(node->left&&node->right){
		LBinTree *next=node->right,*next_parent=node;
		while(next->left){
			next_parent=next;
			next=next->left;
		}
		//只有当待作删节点的右节点不是叶子节点的时候，才需要作以下修改
		if(next!=node->right){
			next_parent->left=next->right;
			next->right=node->right;
		}
		next->left=node->left;

		if(parent){
			if(parent->left==node){
				parent->left=next;
			}else{
				parent->right=next;
			}
		}else{
			root=next;
		}

	}else{
		if(parent){
			if(parent->left==node){
				parent->left=NULL;
			}else{
				parent->right=NULL;
			}
		}else{
			root=NULL;
		}
	}
	delete node;
	return root;
}

LBinTree* BST_Delete2(LBinTree*node,TreeElemType value){
	if(node==NULL)return node;
	if(node->data<value){
		node->right=BST_Delete2(node->right,value);
		return node;
	}
	else if(node->data>value){
		node->left=BST_Delete2(node->left,value);
		return node;
	}
	else{
		LBinTree* newNode=NULL;
		if(node->left&&node->right==NULL){
			newNode=node->left;
		}else if(node->left==NULL&&node->right){
			newNode=node->right;
		}else if(node->left&&node->right){
			LBinTree *next=node->right,*next_parent=node;
			while(next->left){
				next_parent=next;
				next=next->left;
			}
			//只有当待作删节点的右节点不是叶子节点的时候，才需要作以下修改
			if(next!=node->right){
				next_parent->left=next->right;
				next->right=node->right;
			}
			next->left=node->left;
			newNode=next;
		}
		delete node;
		return newNode;
	}
}

void PrintTree(LBinTree* node,char*perBlank,char*format){
	int depth=TreeDepth2(node);
	int blankLen=strlen(perBlank);
	std::queue<LBinTree*>queue;
	queue.push(node);
	int curH=1,curNum=1,curIdx=0,lastIdx=1,firstBlank=pow(2,depth-curH)-0.5,secondBlank=0,totalBlank=pow(2,depth)-1;
	for(int i=0;i<firstBlank;i++){
		std::cout<<perBlank;
	}
	while(queue.size()!=0){
		node=queue.front();	
		if(node)
			printf(format,node->data);
		else
			std::cout<<perBlank;
		for(int i=0;i<secondBlank;i++){
			std::cout<<perBlank;
		}
		curIdx++;
		queue.pop();
		if(node){
			queue.push(node->left);
			queue.push(node->right);
		}else{
			queue.push(NULL);
			queue.push(NULL);
		}
		if(curIdx==lastIdx){
			curH++;
			if(curH>depth)
				break;
			curNum=pow(2,curH-1);
			lastIdx=curIdx+curNum;
			//计算起始空格
			firstBlank=pow(2,depth-curH)-0.5;
			if(curNum>1)
				secondBlank=(totalBlank-firstBlank*2-curNum)/(curNum-1);
			//打印起始空格
			std::cout<<std::endl;
			for(int i=0;i<firstBlank;i++){
				std::cout<<perBlank;
			}
		}
	}
	std::cout<<std::endl;
}

/////////////////////////////////////////////
//平衡二叉树
/////////////////////////////////////////////

int AVL_Factor(LBinTree* node){
	if(node==NULL)
		return 0;
	int leftH=TreeDepth2(node->left);
	int rightH=TreeDepth2(node->right);
	return leftH-rightH;
}

LBinTree* LL(LBinTree* node){
	LBinTree *newRoot=node,*oldRoot=node;
	//右旋
	newRoot=oldRoot->left;
	oldRoot->left=newRoot->right;
	newRoot->right=oldRoot;
	return newRoot;
}

LBinTree* LR(LBinTree* node){
	LBinTree *newRoot=node,*oldRoot=node,*newChildRoot=NULL,*oldChildRoot=NULL;
	//先左旋左子树
	oldChildRoot=oldRoot->left;
	newChildRoot=oldChildRoot->right;
	oldChildRoot->right=newChildRoot->left;
	newChildRoot->left=oldChildRoot;
	
	//再右旋整颗树
	oldRoot->left=newChildRoot;
	newRoot=oldRoot->left;
	oldRoot->left=newRoot->right;
	newRoot->right=oldRoot;
	return newRoot;		
}

LBinTree* RR(LBinTree* node){
	LBinTree *newRoot=node,*oldRoot=node;
	//左旋
	newRoot=oldRoot->right;
	oldRoot->right=newRoot->left;
	newRoot->left=oldRoot;
	return newRoot;
}

LBinTree* RL(LBinTree* node){
	LBinTree *newRoot=node,*oldRoot=node,*newChildRoot=NULL,*oldChildRoot=NULL;
	//先右旋右子树
	oldChildRoot=oldRoot->right;
	newChildRoot=oldChildRoot->left;
	oldChildRoot->left=newChildRoot->right;
	newChildRoot->right=oldChildRoot;
	
	//再左旋整颗树
	oldRoot->right=newChildRoot;
	newRoot=oldRoot->right;
	oldRoot->right=newRoot->left;
	newRoot->left=oldRoot;
	return newRoot;
}

LBinTree* AVL_Rotate(LBinTree* node,TreeElemType value){
	/*
	右旋，左子树的左子树高度减1，右子树的右子树高度加1，左子树的右子树转移到右子树的左子树
	左旋，右子树的右子树高度减1，左子树的左子树高度加1，右子树的左子树转移到左子树的右子树
	所以
	在左子树的左子树中插入节点，只需做右旋即可，
	在右子树的右子树中插入节点，只需做左旋即可
	但
	在左子树的右子树中插入节点，需要先把左子树先转化为一颗平衡树，
	*/
	if(!node)return node;
	int nodeFactor=AVL_Factor(node);
	if(nodeFactor==-2){
		if(node->right){
			int nodeRightFactor=AVL_Factor(node->right);
			if(nodeRightFactor<0){
				//左旋
				return RR(node);
			}else if(nodeRightFactor>0){
				//先右旋右子树 再左旋整颗树
				return RL(node);
			}
		}
	}
	else if(nodeFactor==2){
		if(node->left){
			int nodeLeftFactor=AVL_Factor(node->left);
			if(nodeLeftFactor<0){
				//先左旋左子树 再右旋整颗树
				return LR(node);
			}else if(nodeLeftFactor>0){
				//右旋
				return LL(node);
			}
		}
	}
	
	return node;
}

LBinTree* AVL_Insert(LBinTree* node,TreeElemType value){
	if(node==NULL){
		node=new LBinTree;
		node->data=value;
		node->left=NULL;
		node->right=NULL;
		return node;
	}else{
		if(node->data<value){
			node->right=AVL_Insert(node->right,value);
			if(abs(AVL_Factor(node))==2){
				if(node->right->data<value){
					//左旋
					return RR(node);
				}else if(node->right->data>value){
					//先右旋右子树 再左旋整颗树
					return RL(node);
				}
			}
		}else if(node->data>value){
			node->left=AVL_Insert(node->left,value);
			if(abs(AVL_Factor(node))==2){
				if(node->left->data<value){
					//先左旋左子树 再右旋整颗树
					return LR(node);
				}else if(node->left->data>value){
					//右旋
					return LL(node);
				}
			}
		}
	}
	return node;
}

LBinTree* AVL_Delete(LBinTree* node,TreeElemType value){
	if(node==NULL)return node;
	if(node->data<value){
		node->right=AVL_Delete(node->right,value);
	}
	else if(node->data>value){
		node->left=AVL_Delete(node->left,value);
	}
	else{
		LBinTree* newNode=NULL;
		if(node->left&&node->right==NULL){
			newNode=node->left;
		}else if(node->left==NULL&&node->right){
			newNode=node->right;
		}else if(node->left&&node->right){
			LBinTree *next=node->right,*next_parent=node;
			while(next->left){
				next_parent=next;
				next=next->left;
			}
			//只有当待作删节点的右节点不是叶子节点的时候，才需要作以下修改
			if(next!=node->right){
				next_parent->left=next->right;
				next->right=node->right;
			}
			next->left=node->left;
			newNode=next;
		}
		delete node;
		return newNode;
	}

	if(node->right)
		node->right=AVL_Rotate(node->right,value);
	if(node->left)
		node->left=AVL_Rotate(node->left,value);
	node=AVL_Rotate(node,value);
	return node;
}

///////////////////////////////////////////////////////
//B树
//////////////////////////////////////////////////////
#define BTree_M 4
struct BTreeNode{
	int keyNum;
	int key[BTree_M];//第一个用来存放关键字的个数
	BTreeNode *ptr[BTree_M];
};

int BTree_Search(BTreeNode* node,BTreeNode*&findNode){
	return 0;
}

void PrintBTree(BTreeNode* node){

}

/////////////////////////////////////////////////////
//字符串转化为整数
/////////////////////////////////////////////////////
int StrToInt(char* str){
	if(str==NULL){
		return 0;
	}
	int flag=1;
	if(*str=='-'){
		flag=-1;
		str++;
	}
	int res=0;
	while(*str!=0){
		if(*str<'0'||*str>'9')
			return 0;
		res=res*10+*str-'0';
		++str;
	}
	//溢出
	if(res<0)
		return 0;
	return res*flag;
}

//获取链表倒数第idx个节点 0 0 0 0
ListNode* GetTailNode(ListNode* node,int idx){
	if(node==NULL||idx<0)
		return NULL;
	ListNode *before=node,*behind=node;
	int i=1;
	while(behind&&i<idx){
		behind=behind->next;
		i++;
	}
	if(behind==NULL)
		return NULL;
	while(behind->next){
		behind=behind->next;
		before=before->next;
	}
	return before;
}

///////////////////////////////////////////////
//哈希表
///////////////////////////////////////////////
typedef int HashElemType;
typedef char* HashName;
#define HashSize 40
struct HashMap{
	struct HashNode{
		HashNode *next;
		HashElemType value;
		HashName name;
	};
	HashMap(){
		ZeroMemory(arr,sizeof arr);
	}
	~HashMap(){
		for(int i=0;i<HashSize;i++){
			delete arr[i];
		}
	}
	int hashValue(HashName name){
		int value=0;
		while(*name++!=0){
			value=*name+31*value;
		}
		return value%HashSize;
	}
	HashElemType& operator[](HashName name){
		int idx=hashValue(name);
		HashNode *begin=arr[idx],*cur=begin;
		for(;cur!=NULL&&strcmp(cur->name,name)!=0;cur=cur->next);
		if(cur==NULL){
			cur=new HashNode;
			cur->name=name;
			cur->next=begin;
			cur->value=0;
			arr[idx]=cur;
		}
		return cur->value;
	}
	HashNode *arr[HashSize];
};

//////////////////////////////////////////////
//字符串模式匹配
//////////////////////////////////////////////
int MatchString(char* mainStr,char* subStr){
	if(mainStr==NULL||subStr==NULL)
		return 0;
	/* 双for写法
	int mainIdx=0,subIdx=0,mainLen=strlen(mainStr),subLen=strlen(subStr);
	for(;mainIdx<mainLen;mainIdx++){
		subIdx=0;
		for(int i=mainIdx;subIdx<subLen&&i<mainLen;i++,subIdx++){
			if(mainStr[i]!=subStr[subIdx])
				break;
		}
		if(subIdx==subLen)
			return mainIdx;
	}
	return 0;
	*/
	//单while写法
	int ml=strlen(mainStr),sl=strlen(subStr),i=0,j=0;
	int loopTimes=0;
	while(i<ml&&j<sl){
		loopTimes++;
		if(mainStr[i]==subStr[j]){
			i++;j++;
		}else{
			i=i-j+1;j=0;
		}
	}
	std::cout<<"loopTimes="<<loopTimes<<std::endl;
	if(j==sl)
		return i-j;
	else
		return 0;
}

//KMP算法，构建跳转表
int* BuildKMPJump(char* pattern){
	int len=strlen(pattern);
	int *jump = new int[len];
	int i,j,k,g;
	int nextTimes=0;
	//i表示当前不匹配的位置
	for(i=0;i<len;i++){
		//j从第1个开始寻找能匹配子串的点
		/*比如
		abcabx
		此时的最终结果应为3
		*/
		for(j=1;j<i;j++){
			for(k=0,g=j;g<i;g++,k++){
				nextTimes++;
				if(pattern[k]!=pattern[g])
					break;
			}
			//如果g和i相等了，说明g前面的元素与k所指向的元素都相等了
			//这时，如果g的下一位置和k的下一位置也相同，这里的j是不满足条件的
			/*
			比如
			abcabx
			此时j=3，g==5,且如果[5]==[2]，说明j是不符合的，因为我们已经知道x的位置
			不符合条件，所以如果[2]的位置也是c，就说明，如果跳转到j现在的位置，最终也会
			匹配失败。
			*/
			if(g==i&&pattern[g]!=pattern[k])
				break;
		}
		//j==i，则说明没有找到可以匹配的子串，i前面的子串都是不自覆盖的
		if(j==i){
			//如果i位置上的元素与开头相同，那么这个位置是可以跳过的，否则如果下次跳转到i
			//也最终会失败
			//jump 中存储的数值是模式串当前指针的调整值，0表示模式串的开头位置挪至目标串的当前指针位置
			//-1表示模式串的的开头位置，比当前目标串的批针位置还要往前一格，也就是说，这种情况需要往后移动目标串指针
			//其它数值与0的含义相似，就是调整模式串的位置至目标串的当前指针位置
			if(pattern[0]==pattern[j]){
				jump[i]=-1;
			}else{
				jump[i]=0;
			}
		}else{
			jump[i]=i-j;
		}
	}
	std::cout<<"nextTimes="<<nextTimes<<std::endl;
	return jump;
}

int* BuildKMPJump2(char* pattern){
	int len=strlen(pattern);
	int *jump = new int[len];
	jump[0]=-1;
	int cur=1,pre=0;
	int nextTimes=0;
	//这个循环找匹配数
	/*
	如abcdabce
	会生成 -1 -1 -1 -1 4 4 4 -1
	-1表可以包含有序列，4表示，从下标为4开始的序列是被包含的序列，如后面的abc与开头的abc一样
	*/
	for(cur=1;cur<len;cur++){
		nextTimes++;
		if(jump[cur-1]==-1){
			if(pattern[0]==pattern[cur]){
				jump[cur]=cur;
			}else{
				jump[cur]=-1;
			}
		}else{
			pre=cur-jump[cur-1];
			if(pattern[pre]==pattern[cur]){
				jump[cur]=jump[cur-1];
			}else{
				jump[cur]=-1;
			}
		}
	}
	jump[0]=-1;
	int prei=0;
	//有了包含关系，就可以计算模式串的调整值了
	for(int i=len-1;i>0;i--){
		nextTimes++;
		//-1表示当前位置的模式串没有包含任何子串
		if(jump[i]==-1){
			//如果前一个位置也没有包含任何子串，说明需要把模式串的开头位置调整到目标串当前指针的位置
			/*
			abcdx  目标串
			abcde  模式串
			调整完后，变成
			abcdx
			    abcde
			*/
			if(jump[i-1]==-1){
				jump[i]=0;
			/*
			abcdx  目标串
			ababe  模式串
			调整完后，变成
			ababx
			  aba
			*/
			}else{
				jump[i]=i-jump[i-1];
			}
		}else{
			/*
			abdabcabdabx  目标串
			abdabcabdabc  模式串
			调整完后，变成
			abdabcabdabx
			         abdabcabdabc
			*/
			prei=i-jump[i];
			while(prei>=0&&jump[prei]!=-1){
				prei=prei-jump[prei];
			}
			if(prei-1>=0){
				if(jump[prei-1]==-1){
					jump[i]=0;
				}else{
					jump[i]=prei-jump[prei-1];//prei-1-jump[prei-1]+1
				}
			}else{
				jump[i]=-1;
			}
		}
	}
	std::cout<<"nextTimes="<<nextTimes<<std::endl;
	return jump;
}

int MatchString2(char* mainStr,char* subStr){
	int ml=strlen(mainStr),sl=strlen(subStr),i=0,j=0;
	int *jump=BuildKMPJump2(subStr);
	int *jump2=BuildKMPJump(subStr);
	//for(int k=0;k<sl;k++){
	//	std::cout<<jump[k]<<" "<<jump2[k]<<std::endl;
	//}
	int loopTimes=0;
	while(i<ml&&j<sl){
		loopTimes++;
		if(mainStr[i]==subStr[j]){
			i++;j++;
		}else{
			if(jump[j]==-1){
				i++;
				j=0;
			}else{
				j=jump[j];
			}
		}
	}
	std::cout<<"loopTimes="<<loopTimes<<std::endl;
	if(j==sl)
		return i-j;
	else
		return 0;
	delete[] jump;
	return 0;
}

void BuildNext(const char* pattern, size_t length, unsigned int* next)  
{  
    unsigned int i, t;  
	
    i = 1;  
    t = 0;  
    next[1] = 0;  
	
	int nextTimes=0;
    while(i < length + 1)  
    {  
        while(t > 0 && pattern[i - 1] != pattern[t - 1])  
        {  
			nextTimes++;
            t = next[t];  
        }  
		
        ++t;  
        ++i;  
		
        if(pattern[i - 1] == pattern[t - 1])  
        {  
            next[i] = next[t];  
        }  
        else  
        {  
            next[i] = t;  
        }  
    }  
	
    //pattern末尾的结束符控制，用于寻找目标字符串中的所有匹配结果用  
    while(t > 0 && pattern[i - 1] != pattern[t - 1])  
    {  
		nextTimes++;
        t = next[t];  
    }  
	
    ++t;  
    ++i;  
	
    next[i] = t;  
	std::cout<<"nextTimes="<<nextTimes<<std::endl;
}  

unsigned int KMP(const char* text, const char* pattern, unsigned int* matches)  
{  
	size_t text_length=strlen(text),pattern_length=strlen(pattern);
    unsigned int i, j, n;  
    unsigned int* next = new unsigned int[pattern_length + 2];  
	
    BuildNext(pattern, pattern_length, next);  
	
    i = 0;  
    j = 1;  
    n = 0;  
	
	int loopTimes=0;
    while(pattern_length + 1 - j <= text_length - i)  
    {  
		loopTimes++;
        if(text[i] == pattern[j - 1])  
        {  
            ++i;  
            ++j;  
			
            //发现匹配结果，将匹配子串的位置，加入结果  
            if(j == pattern_length + 1)  
            {  
                matches[n++] = i - pattern_length;  
                j = next[j];  
            }  
        }  
        else  
        {  
            j = next[j];  
			
            if(j == 0)  
            {  
                ++i;  
                ++j;  
            }  
        }  
    }  
	std::cout<<"loopTimes="<<loopTimes<<std::endl;
	//delete[] next;
    //返回发现的匹配数  
    return n;  
}

struct MyTick{
	MyTick(){
		QueryPerformanceFrequency(&m_liPerfFreq);
	}
	~MyTick(){
		
	}
	void start(){
		QueryPerformanceCounter(&m_liPerfStart);
	}
	long stop(){
		QueryPerformanceCounter(&liPerfNow);
		interval=( ((liPerfNow.QuadPart - m_liPerfStart.QuadPart) * 1000)/m_liPerfFreq.QuadPart);
		return interval;
	}
	void show(){
		std::cout<<interval<<std::endl;
	}
	long interval;
	LARGE_INTEGER m_liPerfFreq;
	LARGE_INTEGER m_liPerfStart;
	LARGE_INTEGER liPerfNow;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//图
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//深度优先打印排列
void dfs_arrange(int step,int num,int book[],int box[]){
	if(step==num+1){
		for(int i=1;i<=num;i++){
			std::cout<<box[i-1]<<" ";
		}
		std::cout<<std::endl;
	}
	else{
		for(int i=1;i<=num;i++){
			if(book[i-1]==0){
				box[step-1]=i;
				book[i-1]=1;
				dfs_arrange(step+1,num,book,box);
				book[i-1]=0;
			}
		}
	}
}

//深度优先打印等式
void dfs_equal(int step,int num,int book[],int box[]){
	if(step==num+1){
		if(box[0]*100+box[1]*10+box[2]+box[3]*100+box[4]*10+box[5]==box[6]*100+box[7]*10+box[8]){
			for(int i=1;i<=num;i++){
				std::cout<<box[i-1];
				if(i==3)std::cout<<"+";
				if(i==6)std::cout<<"=";
			}
			std::cout<<std::endl;
		}
	}
	else{
		for(int i=1;i<=num;i++){
			if(book[i-1]==0){
				box[step-1]=i;
				book[i-1]=1;
				dfs_equal(step+1,num,book,box);
				book[i-1]=0;
			}
		}
	}
}

//==========================================================
//迷宫算法
//==========================================================
struct LinkPoint{
	int x,y;
	LinkPoint* pre;
};
struct Point{
	int x,y;
};
//深度优先找出口
struct MazeDfs{	
	MazeDfs(int*mazeArr,int h,int w,int oy,int ox){
		this->w=w;
		this->h=h;
		this->ox=ox;
		this->oy=oy;
		this->minStep=w*h;
		book = new int*[h];
		maze = new int*[h];
		for(int i=0;i<h;i++){
			book[i]=new int[w];
			maze[i]=new int[w];
			memcpy(maze[i],mazeArr+i*w,w*4);
			memset(book[i],0,w*4);
		}
	}
	~MazeDfs(){
		for(int i=0;i<h;i++){
			delete[] book[i];
			delete[] maze[i];
		}
		delete[] book;
		delete[] maze;
	}
	void dfs_maze(int y,int x,int step){
		if(x<=0||y<=0||x>w||y>h||book[y-1][x-1]==1||maze[y-1][x-1]==0)
			return;
		Point p;
		p.x=x;p.y=y;
		record.push_back(p);
		book[y-1][x-1]=1;
		if(x==ox&&y==oy){
			if(step<=minStep){
				minStep=step;
				result=record;
			}
			book[y-1][x-1]=0;
			record.pop_back();
			return;
		}
		//右
		dfs_maze(y,x+1,step+1);
		//下
		dfs_maze(y+1,x,step+1);
		//左
		dfs_maze(y,x-1,step+1);
		//下
		dfs_maze(y-1,x,step+1);
		book[y-1][x-1]=0;
		record.pop_back();
		return;
	}
	void showPath(){
		int size=result.size();
		for(int i=0;i<size;i++){
			std::cout<<"("<<result[i].y<<","<<result[i].x<<")";
		}
		std::cout<<std::endl;
	}
	std::vector<Point>record;
	std::vector<Point>result;
	int **book;
	int **maze;
	int w,h;
	int ox,oy;
	int minStep;
};

//广度优先查找出口
struct MazeBfs{
	MazeBfs(int*mazeArr,int h,int w,int oy,int ox){
		this->w=w;
		this->h=h;
		this->ox=ox;
		this->oy=oy;
		book = new int*[h];
		maze = new int*[h];
		for(int i=0;i<h;i++){
			book[i]=new int[w];
			maze[i]=new int[w];
			memcpy(maze[i],mazeArr+i*w,w*4);
			memset(book[i],0,w*4);
		}
	}
	~MazeBfs(){
		for(int i=0;i<h;i++){
			delete[] book[i];
			delete[] maze[i];
		}
		delete[] book;
		delete[] maze;
	}
	void bfs_maze(int y,int x){
		static int dir[4][2]={{0,1},{1,0},{0,-1},{-1,0}};//{y,x}
		LinkPoint *p = new LinkPoint;
		int tempx,tempy;
		p->x=x;p->y=y;
		p->pre=NULL;
		pathQueue.push_back(p);
		book[y-1][x-1]=1;
		int searchIdx=0;
		while(searchIdx<pathQueue.size()){
			p = pathQueue[searchIdx];
			searchIdx++;
			if(p==NULL)
				return;
			for(int i=0;i<4;i++){
				tempy=p->y+dir[i][0];
				tempx=p->x+dir[i][1];
				if(tempx>0&&tempy>0&&tempx<=w&&tempy<=h&&book[tempy-1][tempx-1]!=1&&maze[tempy-1][tempx-1]!=0){
					LinkPoint* newP = new LinkPoint;
					newP->x=tempx;newP->y=tempy;newP->pre=p;
					pathQueue.push_back(newP);	
					book[tempy-1][tempx-1]=1;
					if(newP->x==ox&&newP->y==oy)
						return;
				}
			}
		}
		return;
	}
	void showPath(){
		LinkPoint* p=pathQueue[pathQueue.size()-1];
		minStep=1;
		while(p){
			minStep++;
			std::cout<<"("<<p->y<<","<<p->x<<")";
			p=p->pre;
		}
		std::cout<<std::endl;
		while(pathQueue.size()>0){
			delete pathQueue[pathQueue.size()-1];
			pathQueue.pop_back();
		}
	}
	std::vector<LinkPoint*>pathQueue;
	int **book;
	int **maze;
	int w,h;
	int ox,oy;
	int minStep;
};

//广度优先计算面积
struct IslandBfs{
	IslandBfs(int*mazeArr,int h,int w){
		this->w=w;
		this->h=h;
		book = new int*[h];
		maze = new int*[h];
		for(int i=0;i<h;i++){
			book[i]=new int[w];
			maze[i]=new int[w];
			memcpy(maze[i],mazeArr+i*w,w*4);
			memset(book[i],0,w*4);
		}
	}
	~IslandBfs(){
		for(int i=0;i<h;i++){
			delete[] book[i];
			delete[] maze[i];
		}
		delete[] book;
		delete[] maze;
	}
	void bfs_all(){
		for(int i=1;i<=w;i++){
			for(int j=1;j<=h;j++){
				bfs_island(j,i);
			}
		}
	}
	void bfs_island(int y,int x){
		static int dir[4][2]={{0,1},{1,0},{0,-1},{-1,0}};//{y,x}
		int tempx=x,tempy=y;
		if(!(tempx>0&&tempy>0&&tempx<=w&&tempy<=h&&book[tempy-1][tempx-1]!=1&&maze[tempy-1][tempx-1]!=0)){
			return;
		}
		Point p,newP;
		p.x=tempx;p.y=tempy;
		pathVec.push_back(p);
		book[y-1][x-1]=1;
		int searchIdx=0;
		while(searchIdx<pathVec.size()){
			p = pathVec[searchIdx];
			searchIdx++;
			for(int i=0;i<4;i++){
				tempy=p.y+dir[i][0];
				tempx=p.x+dir[i][1];
				if(tempx>0&&tempy>0&&tempx<=w&&tempy<=h&&book[tempy-1][tempx-1]!=1&&maze[tempy-1][tempx-1]!=0){
					newP.x=tempx;newP.y=tempy;
					pathVec.push_back(newP);	
					book[tempy-1][tempx-1]=1;
				}
			}
		}
		return;
	}
	void showArea(){
		for(int i=0;i<w;i++){
			for(int j=0;j<h;j++){
				std::cout<<book[i][j]<<" ";
			}
			std::cout<<std::endl;
		}
		std::cout<<pathVec.size()<<std::endl;
	}
	std::vector<Point>pathVec;
	int **book;
	int **maze;
	int w,h;
};

//深度优先计算面积
struct IslandDfs{
	IslandDfs(int*mazeArr,int h,int w){
		this->w=w;
		this->h=h;
		this->ox=ox;
		this->oy=oy;
		area=0;
		book = new int*[h];
		maze = new int*[h];
		for(int i=0;i<h;i++){
			book[i]=new int[w];
			maze[i]=new int[w];
			memcpy(maze[i],mazeArr+i*w,w*4);
			memset(book[i],0,w*4);
		}
	}
	~IslandDfs(){
		for(int i=0;i<h;i++){
			delete[] book[i];
			delete[] maze[i];
		}
		delete[] book;
		delete[] maze;
	}
	void dfs_all(){
		for(int i=1;i<=w;i++){
			for(int j=1;j<=h;j++){
				dfs_island(j,i);
			}
		}
	}
	void dfs_island(int y,int x){
		if(x<=0||y<=0||x>w||y>h||book[y-1][x-1]==1||maze[y-1][x-1]==0)
			return;
		area++;
		book[y-1][x-1]=1;
		//右
		dfs_island(y,x+1);
		//下
		dfs_island(y+1,x);
		//左
		dfs_island(y,x-1);
		//下
		dfs_island(y-1,x);
		return;
	}
	void showArea(){
		for(int i=0;i<w;i++){
			for(int j=0;j<h;j++){
				std::cout<<book[i][j]<<" ";
			}
			std::cout<<std::endl;
		}
		std::cout<<area<<std::endl;
	}
	int **book;
	int **maze;
	int w,h;
	int ox,oy;
	int area;
};

//连接管道，有点像超电压
struct PipeDfs{
	enum PipeType{
		Wan_1=1,
		Wan_2=2,
		Wan_3=3,
		Wan_4=4,
		/*
		41
		32
		*/
		Zhi_H=5,
		Zhi_V=6,
	};
	enum PrePipeDir{
		Pipe_Left,
		Pipe_Right,
		Pipe_Up,
		Pipe_Down,
	};
	PipeDfs(int*mazeArr,int h,int w,int oy,int ox){
		this->w=w;
		this->h=h;
		this->ox=ox;
		this->oy=oy;
		book = new int*[h];
		maze = new int*[h];
		for(int i=0;i<h;i++){
			book[i]=new int[w];
			maze[i]=new int[w];
			memcpy(maze[i],mazeArr+i*w,w*4);
			memset(book[i],0,w*4);
		}
	}
	~PipeDfs(){
		for(int i=0;i<h;i++){
			delete[] book[i];
			delete[] maze[i];
		}
		delete[] book;
		delete[] maze;
	}
	bool canTrans(int p1,int p2){
		if(p1>=Wan_1&&p1<=Wan_4&&p2>=Wan_1&&p2<=Wan_4){
			return true;
		}
		if(p1>=Zhi_H&&p1<=Zhi_V&&p2>=Zhi_H&&p2<=Zhi_V){
			return true;
		}
		return false;
	}
	//preDir 现在方块处于前一方块的方位
	//nextDir 下一方块处于当前方块的方位
	int getPipeTypeByDir(int preDir,int nextDir){
		if(preDir==Pipe_Right){
			if(nextDir==Pipe_Up){
				return Wan_4;
			}else if(nextDir==Pipe_Right){
				return Zhi_H;
			}else if(nextDir==Pipe_Down){
				return Wan_3;
			}
		}else if(preDir==Pipe_Left){
			if(nextDir==Pipe_Up){
				return Wan_1;
			}else if(nextDir==Pipe_Down){
				return Wan_2;
			}else if(nextDir==Pipe_Left){
				return Zhi_H;
			}
		}else if(preDir==Pipe_Up){
			if(nextDir==Pipe_Up){
				return Zhi_V;
			}else if(nextDir==Pipe_Right){
				return Wan_2;
			}else if(nextDir==Pipe_Left){
				return Wan_3;
			}
		}else if(preDir==Pipe_Down){
			if(nextDir==Pipe_Down){
				return Zhi_V;
			}else if(nextDir==Pipe_Right){
				return Wan_1;
			}else if(nextDir==Pipe_Left){
				return Wan_4;
			}
		}
		return -1;
	}
	//返回是否完成搜索
	bool dfs_maze(int y,int x,int prey,int prex,int prePipeType,int preDir){
		if(x==ox&&y==oy){
			result=record;
			return true;
		}
		if(x<=0||y<=0||x>w||y>h||book[y-1][x-1]==1){
			return false;
		}
		Point p;
		p.x=x;p.y=y;
		record.push_back(p);
		book[y-1][x-1]=1;
		//右
		int transPipeType=getPipeTypeByDir(preDir,Pipe_Right);
		int curPipeType=maze[y-1][x-1];
		bool canBeTrans=canTrans(transPipeType,curPipeType);
		if(canBeTrans&&dfs_maze(y,x+1,y,x,transPipeType,Pipe_Right))
			return true;
		//下
		transPipeType=getPipeTypeByDir(preDir,Pipe_Down);
		canBeTrans=canTrans(transPipeType,curPipeType);
		if(canBeTrans&&dfs_maze(y+1,x,y,x,transPipeType,Pipe_Down))
			return true;
		//左
		transPipeType=getPipeTypeByDir(preDir,Pipe_Left);
		canBeTrans=canTrans(transPipeType,curPipeType);
		if(canBeTrans&&dfs_maze(y,x-1,y,x,transPipeType,Pipe_Left))
			return true;
		//上
		transPipeType=getPipeTypeByDir(preDir,Pipe_Up);
		canBeTrans=canTrans(transPipeType,curPipeType);
		if(canBeTrans&&dfs_maze(y-1,x,y,x,transPipeType,Pipe_Up))
			return true;
		book[y-1][x-1]=0;
		record.pop_back();
		return false;
	}
	void showPath(){
		int size=result.size();
		for(int i=0;i<size;i++){
			std::cout<<"("<<result[i].y<<","<<result[i].x<<")";
		}
		std::cout<<std::endl;
	}
	std::vector<Point>record;
	std::vector<Point>result;
	int **book;
	int **maze;
	int w,h;
	int ox,oy;
};

//深度优先遍历图
#define INIF 9999999
struct GraphDfs{
	GraphDfs(int*mazeArr,int h,int w){
		this->w=w;
		this->h=h;
		book = new int[h];
		memset(book,0,h*4);
		maze = new int*[h];
		for(int i=0;i<h;i++){
			maze[i]=new int[w];
			memcpy(maze[i],mazeArr+i*w,w*4);
		}
	}
	~GraphDfs(){
		for(int i=0;i<h;i++){
			delete[] maze[i];
		}
		delete[] maze;
		delete[] book;
	}
	void dfs(int idx){
		result.push_back(idx);
		book[idx-1]=1;
		for(int i=1;i<=h;i++){
			if(idx!=i&&book[i-1]==0&&maze[idx-1][i-1]==1){
				dfs(i);
			}
		}
	}
	void clear(){
		result.clear();
	}
	void showPath(){
		for(int i=0;i<result.size();i++){
			std::cout<<result[i]<<" ";
		}
		std::cout<<std::endl;
	}
	std::vector<int>result;
	int *book;
	int **maze;
	int w,h;
};

//广度优先遍历图
struct GraphBfs{
	GraphBfs(int*mazeArr,int h,int w){
		this->w=w;
		this->h=h;
		book = new int[h];
		memset(book,0,h*4);
		maze = new int*[h];
		for(int i=0;i<h;i++){
			maze[i]=new int[w];
			memcpy(maze[i],mazeArr+i*w,w*4);
		}
	}
	~GraphBfs(){
		for(int i=0;i<h;i++){
			delete[] maze[i];
		}
		delete[] maze;
		delete[] book;
	}
	void bfs(int idx){
		queue.push(idx);
		book[idx-1]=1;
		while(queue.size()>0){
			idx=queue.front();
			result.push_back(idx);
			queue.pop();
			for(int i=1;i<=h;i++){
				if(idx!=i&&book[i-1]==0&&maze[idx-1][i-1]==1){
					book[i-1]=1;
					queue.push(i);
				}
			}
		}
	}
	void showPath(){
		for(int i=0;i<result.size();i++){
			std::cout<<result[i]<<" ";
		}
		std::cout<<std::endl;
	}
	std::queue<int>queue;
	std::vector<int>result;
	int *book;
	int **maze;
	int w,h;
};

//深度优先查找从城市A到B的最短路径
struct CityDfs{
	CityDfs(int*mazeArr,int h,int w,int oidx){
		this->w=w;
		this->h=h;
		this->minStep=INIF;
		this->oidx=oidx;
		book = new int[h];
		memset(book,0,h*4);
		maze = new int*[h];
		for(int i=0;i<h;i++){
			maze[i]=new int[w];
			memcpy(maze[i],mazeArr+i*w,w*4);
		}
	}
	~CityDfs(){
		for(int i=0;i<h;i++){
			delete[] maze[i];
		}
		delete[] maze;
		delete[] book;
	}
	void dfs(int idx,int step){
		record.push_back(idx);
		book[idx-1]=1;
		if(idx==oidx){
			if(step<=minStep){
				result=record;
				minStep=step;
			}
			book[idx-1]=0;
			record.pop_back();
			return;
		}
		for(int i=1;i<=h;i++){
			if(idx!=i&&book[i-1]==0&&maze[idx-1][i-1]!=0&&maze[idx-1][i-1]!=INIF){
				dfs(i,step+maze[idx-1][i-1]);
			}
		}
		book[idx-1]=0;
		record.pop_back();
	}
	void showPath(){
		for(int i=0;i<result.size();i++){
			std::cout<<result[i]<<" ";
		}
		std::cout<<std::endl<<minStep<<std::endl;
	}
	std::vector<int>record;
	std::vector<int>result;
	int *book;
	int **maze;
	int w,h,minStep,oidx;
};

//深度优先查找航班换乘次数最少的路线
struct FlightDfs{
	FlightDfs(int*mazeArr,int h,int w,int oidx){
		this->w=w;
		this->h=h;
		this->minStep=INIF;
		this->oidx=oidx;
		book = new int[h];
		memset(book,0,h*4);
		maze = new int*[h];
		for(int i=0;i<h;i++){
			maze[i]=new int[w];
			memcpy(maze[i],mazeArr+i*w,w*4);
		}
	}
	~FlightDfs(){
		for(int i=0;i<h;i++){
			delete[] maze[i];
		}
		delete[] maze;
		delete[] book;
	}
	void dfs(int idx,int step){
		record.push_back(idx);
		book[idx-1]=1;
		if(idx==oidx){
			if(step<=minStep){
				result=record;
				minStep=step;
			}
			book[idx-1]=0;
			record.pop_back();
			return;
		}
		for(int i=1;i<=h;i++){
			if(idx!=i&&book[i-1]==0&&maze[idx-1][i-1]!=0&&maze[idx-1][i-1]!=INIF){
				dfs(i,step+1);
			}
		}
		book[idx-1]=0;
		record.pop_back();
	}
	void showPath(){
		for(int i=0;i<result.size();i++){
			std::cout<<result[i]<<" ";
		}
		std::cout<<std::endl<<result.size()<<std::endl;
	}
	std::vector<int>record;
	std::vector<int>result;
	int *book;
	int **maze;
	int w,h,minStep,oidx;
};

//广度优先查找航班换乘次数最少的路线
struct GraphLinkNode{
	int idx;
	GraphLinkNode* pre;
};
struct FlightBfs{
	FlightBfs(int*mazeArr,int h,int w,int oidx){
		this->w=w;
		this->h=h;
		this->oidx=oidx;
		book = new int[h];
		memset(book,0,h*4);
		maze = new int*[h];
		for(int i=0;i<h;i++){
			maze[i]=new int[w];
			memcpy(maze[i],mazeArr+i*w,w*4);
		}
	}
	~FlightBfs(){
		for(int i=0;i<h;i++){
			delete[] maze[i];
		}
		delete[] maze;
		delete[] book;
	}
	void bfs(int idx){
		while(pathQueue.size()>0){
			delete pathQueue[pathQueue.size()-1];
			pathQueue.pop_back();
		}

		int searchIdx=0;
		GraphLinkNode*pre=NULL;
		GraphLinkNode*node=new GraphLinkNode;
		node->idx=1;
		node->pre=pre;
		pathQueue.push_back(node);
		book[idx-1]=1;
		while(searchIdx<pathQueue.size()){
			pre=pathQueue[searchIdx];
			searchIdx++;
			idx=pre->idx;
			for(int i=1;i<=h;i++){
				if(idx!=i&&book[i-1]==0&&maze[idx-1][i-1]!=0&&maze[idx-1][i-1]!=INIF){
					book[i-1]=1;
					node=new GraphLinkNode;
					node->idx=i;
					node->pre=pre;
					pathQueue.push_back(node);
					if(i==oidx)
						return;
				}
			}
		}
	}
	void showPath(){
		GraphLinkNode* p=pathQueue[pathQueue.size()-1];
		minStep=1;
		while(p){
			minStep++;
			std::cout<<p->idx<<" ";
			p=p->pre;
		}
		std::cout<<std::endl<<minStep<<std::endl;
	}
	std::vector<GraphLinkNode*>pathQueue;
	int *book;
	int **maze;
	int w,h,oidx,minStep;
};

///////////////////////////////////////////////////
//动态规划
///////////////////////////////////////////////////
//稀疏矩阵的压缩存储
//上下三角矩阵
template<typename T>
struct MatrixTri{
	MatrixTri(int matrixSize,bool isUpTri):upTri(isUpTri),matSize(matrixSize){
		 size = matrixSize*(1+matrixSize)/2;
		 arr = new T[size];
		 memset(arr,0,sizeof(T)*size);
	}
	~MatrixTri(){
		delete[] arr;
	}
	void init(T* matrix,int matrixSize){
		int idx=0;
		if(upTri){
			for(int i=1;i<=matrixSize;i++){
				for(int j=1;j<=matrixSize-i+1;j++){
					arr[idx++]=*(matrix+(i-1)*matrixSize+j-1);
				}
			}
		}else{
			for(int i=1;i<=matrixSize;i++){
				for(int j=1;j<=i;j++){
					arr[idx++]=*(matrix+(i-1)*matrixSize+j-1);
				}
			}
		}
	}
	//从1开始计
	T& Get(int H,int L){
		int idx;
		if(upTri){
			if(H<=L){
				idx=(H-1)*(2*matSize-H+2)/2+L-H;
			}else{
				idx=matSize*(1+matSize)/2-1;
			}
		}else{
			if(H>=L){
				idx=H*(H-1)/2+L-1;
			}else{
				idx=matSize*(1+matSize)/2-1;
			}
		}
		return arr[idx];
	}
	T* arr;
	int size;
	int matSize;
	bool upTri;
};

//数字三角形，求和最大的路径
struct NumTriangle{
	struct PathNode{
		int value;
		int nextH,nextL;
	};
	//result需要预留多一行，值为0，为了能够累加
	NumTriangle(int*mazeArr,int h,int w):maze(h,false),result(h+1,false){
		this->w=w;
		this->h=h;
		maze.init(mazeArr,h);
	}
	~NumTriangle(){
	}
	void dp(){
		for(int i=h;i>=1;i--){
			for(int j=1;j<i+1;j++){
				int left=maze.Get(i,j)+result.Get(i+1,j).value;
				int right=maze.Get(i,j)+result.Get(i+1,j+1).value;
				if(left>right){
					result.Get(i,j).value=left;
					result.Get(i,j).nextH=i+1;
					result.Get(i,j).nextL=j;
				}else{
					result.Get(i,j).value=right;
					result.Get(i,j).nextH=i+1;
					result.Get(i,j).nextL=j+1;
				}
			}
		}
	}
	void showPath(){
		int H=1,L=1,newH=0,newL=0;
		printf("(%d,%d) ",H,L);
		while(true){
			newH=result.Get(H,L).nextH;
			newL=result.Get(H,L).nextL;
			if(0==result.Get(newH,newL).nextH&&0==result.Get(newH,newL).nextL)
				break;
			printf("(%d,%d) ",newH,newL);
			H=newH;
			L=newL;
		}
	}
	MatrixTri<PathNode> result;
	MatrixTri<int> maze;
	int w,h;
};

//任意两点最短路径
struct Floyd{
	struct LinkFloyd{
		int mp,value;
		LinkFloyd():mp(0),value(0){

		}
	};
	Floyd(int*mazeArr,int h,int w){
		this->w=w;
		this->h=h;
		result = new LinkFloyd*[h];
		for(int i=0;i<h;i++){
			result[i]=new LinkFloyd[w];
			for(int j=0;j<w;j++){
				result[i][j].value=*(mazeArr+i*w+j);
			}
		}
	}
	~Floyd(){
		for(int i=0;i<h;i++){
			delete[] result[i];
		}
		delete[] result;
	}
	void floyd(){
		//动态规划思想，如果子问题最优，那么整体最优
		//如果i到j的距离大于i到k再到j，那么就选择i->k->j作为i到j的路径
		//这个是子问题，父问题也可这么解决，遍历完所有的点后，所有的点就找到最优解了
		//每次加入一个点，使得原路径变短，没有先后顺序
		for(int i=1;i<=h;i++){
			for(int j=1;j<=h;j++){
				for(int k=1;k<=h;k++){
					if(result[j-1][k-1].value>result[j-1][i-1].value+result[i-1][k-1].value){
						result[j-1][k-1].value=result[j-1][i-1].value+result[i-1][k-1].value;
						result[j-1][k-1].mp=i;
					}
				}
			}
			//showPath();
		}
	}
	void showPath(){
		for(int i=1;i<=h;i++){
			for(int j=1;j<=h;j++){
				printf("从%d到%d 总长%d 路径: %d ",i,j,result[i-1][j-1].value,i);
				printPath(i,j);
				printf("\n");
			}
		}
		printf("============================\n");
	}
	void printPath(int bp,int ep){
		LinkFloyd&node=result[bp-1][ep-1];
		if(node.mp!=0){
			printPath(bp,node.mp);
			printPath(node.mp,ep);
		}else{
			printf("%d ",ep);
		}
	}
	LinkFloyd **result;
	int w,h;
};

//从结果出发，最近的点，就是最终结果序列的一部分，如 124356
//第一次会发现1到2是最近的，此时12是不可能再短的了，于是12是绝对有可能成为最终序列的
//一部分，使用它去修改其它各点的路径，使得路径不断的接近最终结果，完成一次修正之后，
//对还未确定的点，重复上述的动作。
//Dijkstra和floyd都是采用不断逼近最终结果的方式进行算法的演算
//前者通过寻找不可分割点逼近结果，后者通过插入点来逼近结果
struct OpenNode{
	int ep,value;
};

int __cdecl CompareOpenNode(OpenNode&o1,OpenNode&o2){
	if(o1.value>o2.value)
		return 1;
	else if(o1.value==o2.value)
		return 0;
	return -1;
}

struct Dijkstra{
	struct LinkDijkstra{
		int mp,value;
		LinkDijkstra():mp(0),value(0){
			
		}
	};	
	Dijkstra(int*mazeArr,int h,int w):open(NULL){
		this->w=w;
		this->h=h;
		result = new LinkDijkstra*[h];
		for(int i=0;i<h;i++){
			result[i]=new LinkDijkstra[w];
			for(int j=0;j<w;j++){
				result[i][j].value=*(mazeArr+i*w+j);
			}
		}
	}
	~Dijkstra(){
		for(int i=0;i<h;i++){
			delete[] result[i];
		}
		delete[] result;
	}
	void dijkstra(int bidx){
		OpenNode minNode;
		this->bidx=bidx;
		int i=0,openSize=h-1,openIdx=0;
		delete[] open;
		open = new OpenNode[h-1];
		for(i=1;i<=h;i++){
			if(i!=bidx){
				minNode.ep=i;
				minNode.value=result[bidx-1][i-1].value;
				open[openIdx++]=minNode;
			}
		}
		InitMinHeap<OpenNode>(open,openSize,CompareOpenNode);
		while(openSize>0){
			/*使用顺序查找最近点
			openIdx=0;
			minNode=open[openIdx];
			for(i=1;i<openSize;i++){
				if(minNode.value>open[i].value){
					minNode=open[i];
					openIdx=i;
				}
			}
			openSize=ArrayDelete<OpenNode>(open,openSize,openIdx);
			*/
			openSize=MinHeapDelete<OpenNode>(open,openSize,CompareOpenNode);
			minNode=open[openSize];
			for(i=0;i<openSize;i++){
				if(open[i].value>minNode.value+result[minNode.ep-1][open[i].ep-1].value){
					result[bidx-1][open[i].ep-1].mp=minNode.ep;
					result[bidx-1][open[i].ep-1].value=open[i].value=minNode.value+result[minNode.ep-1][open[i].ep-1].value;
					MinHeapFloat<OpenNode>(open,i,CompareOpenNode);
				}
			}
		}
	}
	void showPath(){
		int i=bidx;
		//for(int i=1;i<=h;i++){
			for(int j=1;j<=h;j++){
				printf("从%d到%d 总长%d 路径: %d ",i,j,result[i-1][j-1].value,i);
				printPath(i,j);
				printf("\n");
			}
		//}
		printf("============================\n");
	}
	void printPath(int bp,int ep){
		LinkDijkstra&node=result[bp-1][ep-1];
		if(node.mp!=0){
			printPath(bp,node.mp);
			printPath(node.mp,ep);
		}else{
			printf("%d ",ep);
		}
	}
	LinkDijkstra **result;
	OpenNode* open;
	int w,h,bidx;
};

///////////////////////////////////////////////////////////////
//带负权边单源最短路径
//理论:起点到其它点的最短路径，最多包含n-1个顶点
//所以只需要不断的根据提供的信息，循环n-1次，即可求出所有的最短路径,
//因为每循环一次，至少可提供一个最短路径
///////////////////////////////////////////////////////////////
struct BellmanFord{
	struct LinkBellmanFord{
		int mp,value;
		LinkBellmanFord():mp(0),value(INIF){
			
		}
	};
	struct Edge{
		int p1,p2,value;
	};
	BellmanFord(int* edgeArr,int edgeSize,int vn):
	vexn(vn),result(NULL){
		this->edgeArr=(Edge*)edgeArr;
		this->edgeSize=edgeSize;
	}
	~BellmanFord(){
		delete[] result;
	}
	void bellmanFord(int bidx){
		delete[] result;
		this->bidx=bidx;
		result = new LinkBellmanFord[vexn];
		result[0].value=0;

		for(int i=1;i<vexn;i++){
			bool hasChange=false;
			for(int j=0;j<edgeSize;j++){
				Edge& edge=edgeArr[j];
				if(result[edge.p2-1].value>result[edge.p1-1].value+edge.value){
					result[edge.p2-1].value=result[edge.p1-1].value+edge.value;
					//只有路径信息是非起点向终点时，才需插入中间节点,如起点是1，这个信息是1到5的，那么直接更新
					//路径长度就可以了
					if(edge.p1!=bidx)
						result[edge.p2-1].mp=edge.p1;
					hasChange=true;
				}
			}
			if(!hasChange)
				break;
		}
	}
	void showPath(){
		int i=bidx;
		//for(int i=1;i<=h;i++){
		for(int j=1;j<=vexn;j++){
			printf("从%d到%d 总长%d 路径: %d ",i,j,result[j-1].value,i);
			printPath(j);
			printf("\n");
		}
		//}
		printf("============================\n");
	}
	void printPath(int ep){
		LinkBellmanFord&node=result[ep-1];
		if(node.mp!=0){
			printPath(node.mp);
		}
		printf("%d ",ep);
	}
	LinkBellmanFord *result;
	Edge* edgeArr;
	int edgeSize,vexn,bidx;
};

////////////////////////////////////////////////////////////
//使用队列优化带负权边单源最短路径
//没有优化的BellmanFord算法，每次都会遍历所有的信息，这个过程
//包含已经形成最终最短路径的顶点，这无疑是浪费cpu的，而前面一轮
//变化的点，也就是有改变最短路径的点，必将会成为下一轮最短路径
//经过的点，所以只需遍历前一轮变更的点所连接的其它点即可，如此
//可减少许多不必要的遍历
////////////////////////////////////////////////////////////
struct BellmanFordQueue{
	struct LinkBellmanFord{
		int mp,value;
		LinkBellmanFord():mp(0),value(INIF){
			
		}
	};
	struct Edge{
		int endP,value;
	};
	typedef std::vector<Edge> EndInfo;
	typedef std::map<int,EndInfo> EdgeInfo;
	BellmanFordQueue(int* edgeArr,int edgeSize,int vn):
	vexn(vn){
		Edge edge;
		for(int i=0;i<edgeSize;i++){
			EndInfo& endInfo=data[*(edgeArr+i*3+0)];
			edge.endP=*(edgeArr+i*3+1);
			edge.value=*(edgeArr+i*3+2);
			endInfo.push_back(edge);
		}
		book = new int[vexn];
		memset(book,0,vexn*sizeof(int));
		
	}
	~BellmanFordQueue(){
		delete[] result;
		delete[] book;
	}
	void bellmanFord(int bidx){
		delete[] result;
		result = new LinkBellmanFord[vexn];
		result[0].value=0;

		this->bidx=bidx;
		checkQueue.push(bidx);
		while(checkQueue.size()>0){
			int p1=checkQueue.front();
			checkQueue.pop();
			book[p1-1]=0;
			EndInfo& endInfo=data[p1];
			for(int i=0;i<endInfo.size();i++){
				int p2=endInfo[i].endP;
				if(result[p2-1].value>result[p1-1].value+endInfo[i].value){
					if(book[p2-1]==0){
						checkQueue.push(p2);
						book[p2-1]=1;
					}
					result[p2-1].value=result[p1-1].value+endInfo[i].value;
					//只有路径信息是非起点向终点时，才需插入中间节点,如起点是1，这个信息是1到5的，那么直接更新
					//路径长度就可以了
					if(p1!=bidx)
						result[p2-1].mp=p1;
				}
			}
		}
	}
	void showPath(){
		int i=bidx;
		//for(int i=1;i<=h;i++){
		for(int j=1;j<=vexn;j++){
			printf("从%d到%d 总长%d 路径: %d ",i,j,result[j-1].value,i);
			printPath(j);
			printf("\n");
		}
		//}
		printf("============================\n");
	}
	void printPath(int ep){
		LinkBellmanFord&node=result[ep-1];
		if(node.mp!=0){
			printPath(node.mp);
			//这里为何不用递归prithPath(node.ep)
			//首先result是一维数组，算法运行过程中，从头到尾中是优化了起点到终点的路径，没有优化
			//任何中途路径，比如2到5等，所以不像floyd和dijkstra算法，这两个算法在运行过程会去修改其它的
			//中途路径，所以至于159这样的路径要拆开两部分来打印，1到5和5到9中间都有可能插入其它点，dijkstra算法
			//其实如果只运行一次，也没有这个必要，因为它和bellmanford一样，都是单源最短路径，不会去改其它的点
			//但如果算法不只是计算一个起点，比如算完1到其它点，再算2到其它点，再算3到其它点，而结果会保留到result二维数组
			//里面，从而间接行成了floyd算法的效果，其实dijkstra运行n次，其结果floyd的算法结果肯定是一样的。
		}
		printf("%d ",ep);
	}
	LinkBellmanFord *result;
	int *book;
	std::queue<int> checkQueue;
	EdgeInfo data;
	int vexn,bidx;
};

/////////////////////////////////////////////////////////////////////////////////////////////
//并查集
//查找图中森林一共有几颗子树
//并查即合并，查找，通过递归实现
/////////////////////////////////////////////////////////////////////////////////////////////
struct MergeSearch{
	MergeSearch(int (*data)[2],int dataLen,int nodeSize):partnerInfo(data),infoSize(dataLen){
		this->nodeSize=nodeSize;
		node = new int[nodeSize+1];
		for(int i=0;i<=nodeSize;i++){
			node[i]=i;
		}
	}
	~MergeSearch(){
		delete[] node;
	}
	void handleInfo(){
		for(int i=0;i<infoSize;i++){
			int ancient=getAncient(partnerInfo[i][0]);
			int child=partnerInfo[i][1];
			changeAncient(child,ancient);
		}
	}
	void showPartner(){
		std::cout<<"并查集:";
		ShowArray(node,nodeSize+1);
		int partner=0;
		int cur=0;
		for(int i=1;i<=nodeSize;i++){
			if(cur!=node[i]){
				cur=node[i];
				partner++;
			}
		}
		std::cout<<"同伙:"<<partner<<std::endl;
	}
private:
	int getAncient(int idx){
		if(node[idx]==idx)
			return idx;
		node[idx]=getAncient(node[idx]);
		return node[idx];
	}
	void changeAncient(int idx,int ancient){
		int oldAncient=node[idx];
		if(oldAncient==ancient)
			return;
		node[idx]=ancient;
		changeAncient(oldAncient,ancient);
	}
	int (*partnerInfo)[2];
	int infoSize;
	int *node;
	int nodeSize;
};

/////////////////////////////////////////////////////////////////////////////////////////////
//最小生成树
//通过总长度最小的边连接所有的点
//总是应该从最短的边开始筛选，所以开始时需要小从到大排序所有的边，往后遍历边时，如果两点已经连通
//则忽略该边，而判断两点是否连通，使用并查集算法即可解决
/////////////////////////////////////////////////////////////////////////////////////////////
struct MinTreeEdgeInfo{
	int p1,p2,value;
};

int MinTreeSortFunc(MinTreeEdgeInfo& e1,MinTreeEdgeInfo& e2){
	if(e1.value>e2.value)
		return 1;
	else if(e1.value==e2.value)
		return 0;
	else
		return -1;
}

struct MinTree{	
	MinTree(int (*data)[3],int dataLen,int nodeSize):partnerInfo((MinTreeEdgeInfo*)data),infoSize(dataLen){
		QuickSort<MinTreeEdgeInfo>(partnerInfo,0,dataLen-1,MinTreeSortFunc);
		this->nodeSize=nodeSize;
		node = new int[nodeSize+1];
		for(int i=0;i<=nodeSize;i++){
			node[i]=i;
			//std::cout<<partnerInfo[i].value<<" ";
		}
		//std::cout<<std::endl;
	}
	~MinTree(){
		delete[] node;
	}
	void handleInfo(){
		for(int i=0;i<infoSize;i++){
			int ancient1=getAncient(partnerInfo[i].p1);
			int ancient2=getAncient(partnerInfo[i].p2);
			//判断是否连通
			if(ancient1!=ancient2){
				result.push_back(partnerInfo[i]);
				changeAncient(partnerInfo[i].p2,ancient1);
			}
		}
	}
	void showTree(){
		std::cout<<"并查集:";
		ShowArray(node,nodeSize+1);
		int partner=0;
		int cur=0;
		for(int i=1;i<=nodeSize;i++){
			if(cur!=node[i]){
				cur=node[i];
				partner++;
			}
		}
		std::cout<<"森林:"<<partner<<std::endl<<"边:";
		int totalDis=0;
		for(int j=0;j<result.size();j++){
			printf("(%d,%d,%d) ",result[j].p1,result[j].p2,result[j].value);
			totalDis+=result[j].value;
		}
		printf("\n总长:%d\n",totalDis);
	}
private:
	int getAncient(int idx){
		if(node[idx]==idx)
			return idx;
		node[idx]=getAncient(node[idx]);
		return node[idx];
	}
	void changeAncient(int idx,int ancient){
		int oldAncient=node[idx];
		if(oldAncient==ancient)
			return;
		node[idx]=ancient;
		changeAncient(oldAncient,ancient);
	}
	MinTreeEdgeInfo *partnerInfo;
	int infoSize;
	int *node;
	int nodeSize;
	std::vector<MinTreeEdgeInfo> result;
};

//稀疏矩阵
struct SparseMat{
	//symmetric 是否对称矩阵
	SparseMat(int (*data)[3],int len,int vexn,bool symmetric=true){
		this->vexn=vexn;
		for(int i=0;i<len;i++){
			maze[data[i][0]*vexn+data[i][1]]=data[i][2];
			if(symmetric)
				maze[data[i][1]*vexn+data[i][0]]=data[i][2];
		}
	}
	~SparseMat(){

	}
	int Get(int H,int L){
		if(H==L)
			return 0;
		int key=H*vexn+L;
		return maze[key]==0?INIF:maze[key];
	}
	std::map<int,int> maze;
	int vexn;
};

//////////////////////////////////////////////////////////////////
//Prim算法最小生成树
//上面的最小生成树算法是从边出发，通过并查集实现，这里，通过点出发
//因为最终的结果肯定包含所有的点，不断选取离生成树最近的点，从而
//不断完善生成树的构造
//////////////////////////////////////////////////////////////////
struct PrimEdgeInfo{
	int bp;
	int ep;
	int value;
};
int CompareEdgeInfo(PrimEdgeInfo&e1,PrimEdgeInfo&e2){
	if(e1.value>e2.value)
		return 1;
	else if(e1.value==e2.value)
		return 0;
	else 
		return -1;
}
struct Prim{
	Prim(int (*data)[3],int dataLen,int vexn):mat(data,dataLen,vexn),vexn(vexn){
		book = new int[vexn+1];
		memset(book,0,(vexn+1)*sizeof(int));
		disSize=vexn-1;//只需存储2~N与1的距离
		disArr = new PrimEdgeInfo[disSize];
		for(int p=2,idx=0;idx<disSize;p++,idx++){
			disArr[idx].bp=1;
			disArr[idx].ep=p;
			disArr[idx].value=mat.Get(1,p);
		}
		InitMinHeap<PrimEdgeInfo>(disArr,disSize,CompareEdgeInfo);
	}
	~Prim(){
		delete[] book;
		delete[] disArr;
	}
	void handleInfo(){
		int minDis=INIF,minPoint=1,i;
		while(true){
			////////////////////////////////////////////////////////////////////////
			/*使用顺序查找法，查法最近点
		for(int j=2;j<=vexn;j++){
			//生成树,寻找一个离树最近的点，加入树中，这个点必须不属于树
			//否则就没有加入的必要了
			minDis=INIF;
			minPoint=0;
			for(i=0;i<vexn-1;i++){
				if(book[disArr[i].ep]==0&&disArr[i].value<minDis){
					minDis=disArr[i].value;
					minPoint=disArr[i].ep;
				}
			}
			book[minPoint]=1;
			//最后一个点已经加入树中，所以不需要再刷新距离了，已经没有剩余的点未加入了
			if(j==vexn)break;
			*/
			////////////////////////////////////////////////////////////////////////

			//使用堆排序法查找最近点
			disSize=MinHeapDelete<PrimEdgeInfo>(disArr,disSize,CompareEdgeInfo);
			minPoint=disArr[disSize].ep;
			book[minPoint]=1;
			if(disSize==0)
				break;
			//由于新加入了点，所以可以重新计算未加入点离树的距离
			//其实就是计算其它点与新加入点的距离是否比原来的要短
			//同样，已经在树中的点，不需要计算
			for(i=0;i<disSize;i++){
				int dis=mat.Get(minPoint,disArr[i].ep);
				if(book[disArr[i].ep]==0&&dis<disArr[i].value){
					disArr[i].value=dis;
					disArr[i].bp=minPoint;
					MinHeapFloat<PrimEdgeInfo>(disArr,i,CompareEdgeInfo);
				}
			}
		}
	}
	void showTree(){
		int totalDis=0;
		//第1个点不用打印了，因为是自己到自己的距离
		for(int j=0;j<vexn-1;j++){
			printf("(%d,%d,%d) ",disArr[j].bp,disArr[j].ep,disArr[j].value);
			totalDis+=disArr[j].value;
		}
		printf("\n总长:%d\n",totalDis);
	}
private:
	PrimEdgeInfo *disArr;
	int disSize;
	int vexn;
	int *book;
	SparseMat mat;
};

int main(){

	//ListNode* head = CreateList(true);
	//ShowList(head,true);
	//DeleteRange(head,5,8);
	//ShowList(head,true);
	//ListNode* tail = GetTail(head);
	//BubbleSort(head->next,tail);
	//ShowList(head,true);
	//head = DeleteElem(NULL,head,5);
	//head->next = DeleteElem(head,head->next,5);
	//ShowList(head,true);
	//ReverseShowList(head);
	//ShowList(head,true);
	//head->next = DeleteMinElem(head->next);
	//ShowList(head,true);
	
	//ArrayElemType array[]={6,4,6,7,7,6,5,4,23,2,21,4,6,7,87,100,9809,0};
	//ArrayElemType array[]={9,8,7,6,5,4,3,2,1,0};
	//int arrSize=sizeof(array)/sizeof(ArrayElemType);
	//ElemType array[]={49,38,65,97,26,13,27,49,55,4};//{10,9,5,7,6,5,4,3,2,1,0};
	//ShellSort(array,sizeof(array)/sizeof(ArrayElemType));
	//SelectSort(array,sizeof(array)/sizeof(ArrayElemType));
	//PrintHeap(array,arrSize,"  ","%02d");
	//InitMinHeapInt(array,arrSize);
	//PrintHeap(array,arrSize,"  ","%02d");
	//arrSize=MinHeapDeleteInt(array,arrSize);
	//PrintHeap(array,arrSize,"  ","%02d");
	//arrSize=MinHeapInsertInt(array,arrSize,-1);
	//PrintHeap(array,arrSize,"  ","%02d");
	//MinHeapSortInt(array,arrSize);
	//PrintHeap(array,arrSize,"  ","%02d");
	//BinInsertSort(array,sizeof(array)/sizeof(ElemType));
	//ShowArray(array,sizeof(array)/sizeof(ElemType));
	//int pos=BinFind(array,sizeof(array)/sizeof(ElemType),5.5);
	//std::cout<<pos<<" "<<array[pos]<<std::endl;
	//QuickSortInt(array,0,sizeof array/sizeof(int));
	//BubbleSort(array,0,sizeof array/sizeof(int)-1);
	//ShowArray(array,sizeof array/sizeof(int));
	//std::cout<<findAncient(11,4)<<std::endl;
	//MergeSort(array,arrSize);
	//ShowArray(array,arrSize);
	//CountSort(array,arrSize);
	//RadixSort(array,arrSize,4);
	//ShowArray(array,arrSize);

	//TreeElemType treeArr[] = {'A','B',0,'C',0,0,'D','E',0,0,'F','G',0,'H',0,0,'I',0,0,};
	//TreeElemType treeArr[] = {6,2,1,0,0,4,3,0,0,0,8,0,0};
	//TreeElemType treeArr[] = {53,17,9,0,0,45,23,0,0,0,78,65,0,0,94,81,79,0,80,0,0,88,0,0,0};
	//TreeElemType treeArr[] = {20,10,5,3,0,0,0,15,0,17,0,0,30,0,35,0,0};
	//TreeElemType treeArr[] = {8,6,4,0,0,7,0,0,11,0,0};
	//TreeElemType treeArr[] = {8,6,0,0,10,9,0,0,12,0,0};
	//TreeElemType treeArr[] = {9,6,4,0,0,7,0,0,11,0,0};
	//TreeElemType treeArr[] = {6,4,0,0,12,10,0,0,14,0,0};
	//ThreadBinTree* root=InitBinTree<ThreadBinTree>(treeArr,sizeof treeArr/sizeof(TreeElemType),PRE);
	//ThreadBinTree* pre=NULL;
	//InitThreadBinTree(root,&pre);
	//ShowThreadTree(FirstNode(root));
	
	//LBinTree* root=InitBinTree<LBinTree>(treeArr,sizeof treeArr/sizeof(TreeElemType),PRE);
	//LBinTree* compare_root=InitBinTree<LBinTree>(treeArr,sizeof treeArr/sizeof(TreeElemType),PRE);
	//LBinTree* root=BST_Create(treeArr,sizeof treeArr/sizeof(TreeElemType));
	//std::cout<<TreeDepth(root)<<std::endl;
	//std::cout<<TreeDepth2(root)<<std::endl;
	//ShowTree(root,PRE);
	//ShowTree(root,MID);
	//BST_Insert(compare_root,4);//14);//2);
	//BST_Insert(compare_root,2);
	//PrintTree(compare_root,"  ","%02d");

	//root=AVL_Insert(root,4);//14);//2);
	//PrintTree(root,"  ","%02d");

	//AVL_Delete(compare_root,4);
	//AVL_Delete(compare_root,4);
	//PrintTree(compare_root,"  ","%02d");
	//LBinTree* find=BST_Search(root,4);
	//if(find)
	//	std::cout<<find->data<<std::endl;
	//BST_Insert(root,5);
	//ShowTree(root,MID);
	//BST_Delete2(root,NULL,45);
	//BST_Delete(root,78);
	//ShowTree(root,MID);
	//ShowTree(root,POST);
	//ShowTree2(root,PRE);
	//ShowTree2(root,MID);
	//ShowTree2(root,POST);
	//LevelOrder(root);

	//ListElemType treeArr[] = {20,10,5,3,50,6,100,15,40,17,8,31,30,97,35,65,77};
	//BlockSearch blockSearch(treeArr,sizeof treeArr/sizeof(ArrayElemType));
	//blockSearch.showArray();
	/*
	blockSearch.showArray();
	blockSearch.remove(5);
	blockSearch.showArray();
	blockSearch.remove(8);
	blockSearch.showArray();
	blockSearch.remove(3);
	blockSearch.showArray();
	blockSearch.remove(6);
	blockSearch.showArray();
	blockSearch.remove(100);
	blockSearch.showArray();
	blockSearch.remove(65);
	blockSearch.showArray();
	blockSearch.insert(3);
	blockSearch.showArray();
	std::cout<<blockSearch.search(65)<<std::endl;
	*/
	/*
	for(int i=0;i<sizeof treeArr/sizeof(ArrayElemType);i++){
		blockSearch.remove(treeArr[i]);
		blockSearch.showArray();
	}
	std::cout<<"delete finish"<<std::endl;*/
	//std::cout<<0x7fffffff<<std::endl;
	//std::cout<<StrToInt("-2147483648")<<std::endl;
	/*
	HashMap mymap;
	mymap["a1"]=1;
	mymap["a2"]=2;
	mymap["a3"]=3;
	mymap["a1"]=4;
	std::cout<<mymap["a1"]<<" ";
	std::cout<<mymap["a2"]<<" ";
	std::cout<<mymap["a3"]<<std::endl;
	std::cout<<MatchString("lanwanjun","un")<<std::endl;
	*/
	//std::cout<<MatchString("babcbabcabcaabcabcabcacabc","abcabcacab")<<std::endl;
	//std::cout<<MatchString2("babcbabcabcaabcabcabcacabc","abcabcacab")<<std::endl;
	//unsigned int *matches = new unsigned int[10];
	//std::cout<<KMP("babcbabcabcaabcabcabcacabc","abcabcacab",matches)<<std::endl;
	
	/*
	ArrayElemType randArr[50000],testArr[50000];
	int randSize=10000;
	bool showResult=false;
	MyTick tick;
	srand(clock());
	for(;randSize<=50000;randSize+=5000){
		std::cout<<"==============数据规模:"<<randSize<<"=============="<<std::endl;
		for(int i=0;i<randSize;i++){
			randArr[i]=rand();
		}
		
		memcpy(testArr,randArr,randSize*4);
		tick.start();
		CountSort(testArr,randSize);
		std::cout<<"CountSort ";
		tick.stop();
		tick.show();
		if(showResult)ShowArray(testArr,randSize);

		memcpy(testArr,randArr,randSize*4);
		tick.start();
		QuickSortInt(testArr,0,randSize-1);
		std::cout<<"QuickSort ";
		tick.stop();
		tick.show();
		if(showResult)ShowArray(testArr,randSize);

		memcpy(testArr,randArr,randSize*4);
		tick.start();
		InitMinHeapInt(testArr,randSize);
		MinHeapSortInt(testArr,randSize);
		std::cout<<"MinHeapSort ";
		tick.stop();
		tick.show();
		if(showResult)ShowArray(testArr,randSize);

		memcpy(testArr,randArr,randSize*4);
		tick.start();
		MergeSort(testArr,randSize);
		std::cout<<"MergeSort ";
		tick.stop();
		tick.show();
		if(showResult)ShowArray(testArr,randSize);

		memcpy(testArr,randArr,randSize*4);
		tick.start();
		ShellSort(testArr,randSize);
		std::cout<<"ShellSort ";
		tick.stop();
		tick.show();
		if(showResult)ShowArray(testArr,randSize);

		memcpy(testArr,randArr,randSize*4);
		tick.start();
		RadixSort(testArr,randSize,5);
		std::cout<<"RadixSort ";
		tick.stop();
		tick.show();
		if(showResult)ShowArray(testArr,randSize);

		memcpy(testArr,randArr,randSize*4);
		tick.start();
		BinInsertSort(testArr,randSize);
		std::cout<<"BinInsertSort ";
		tick.stop();
		tick.show();
		if(showResult)ShowArray(testArr,randSize);

		memcpy(testArr,randArr,randSize*4);
		tick.start();
		InsertSort(testArr,randSize);
		std::cout<<"InsertSort ";
		tick.stop();
		tick.show();
		if(showResult)ShowArray(testArr,randSize);

		memcpy(testArr,randArr,randSize*4);
		tick.start();
		SelectSort(testArr,randSize);
		std::cout<<"SelectSort ";
		tick.stop();
		tick.show();
		if(showResult)ShowArray(testArr,randSize);

		memcpy(testArr,randArr,randSize*4);
		tick.start();
		BubbleSort(testArr,0,randSize-1);
		std::cout<<"BubbleSort ";
		tick.stop();
		tick.show();
		if(showResult)ShowArray(testArr,randSize);
	}*/
	/*
	int book[4]={0};
	int box[4]={0};
	dfs_arrange(1,4,book,box);*/
	/*
	int book[9]={0};
	int box[9]={0};
	dfs_equal(1,9,book,box);*/
	/*
	int maze[6][11]={
	{0,0,0,0,0,0,0,0,0,0,0},
	{2,1,1,1,1,0,1,1,1,1,0},
	{0,0,0,0,1,0,1,0,0,1,0},
	{0,0,0,0,1,0,1,0,0,1,0},
	{0,0,0,0,1,1,1,0,0,1,0},
	{0,0,0,0,0,0,0,0,0,3,0}
	};
	MazeDfs dfsMaze((int*)maze,6,11,6,10);
	dfsMaze.dfs_maze(2,1,1);
	dfsMaze.showPath();
	MazeBfs bfsMaze((int*)maze,6,11,6,10);
	bfsMaze.bfs_maze(2,1);
	bfsMaze.showPath();*/
	/*
	int island[10][10]={
	{1,2,1,0,0,0,0,0,2,3},
	{3,0,2,0,1,2,1,0,1,2},
	{4,0,1,0,1,2,3,2,0,1},
	{3,2,0,0,0,1,2,4,0,0},
	{0,0,0,0,0,0,1,5,3,0},
	{0,1,2,1,0,1,5,4,3,0},
	{0,1,2,3,1,3,6,2,1,0},
	{0,0,3,4,8,9,7,5,0,0},
	{0,0,0,3,7,8,6,0,1,2},
	{0,0,0,0,0,0,0,0,1,0},
	};
	*/
	/*
#define islandW 100 
#define islandH 100
	srand(clock());
	int island[islandW][islandH];
	for(int i=0;i<islandW;i++){
		for(int j=0;j<islandH;j++){
			island[i][j]=rand()>16384?1:0;
		}
	}
	MyTick tick;
	IslandBfs bfsIsland((int*)island,islandW,islandH);
	//bfsIsland.bfs_island(6,8);
	tick.start();
	bfsIsland.bfs_all();
	bfsIsland.showArea();
	tick.stop();
	tick.show();
	IslandDfs dfsIsland((int*)island,islandW,islandH);
	//dfsIsland.dfs_island(6,8);
	tick.start();
	dfsIsland.dfs_all();
	dfsIsland.showArea();
	tick.stop();
	tick.show();
	*/
	/*
	int maze[5][4]={
		{5,3,5,3},
		{1,5,3,0},
		{2,3,5,1},
		{6,1,1,5},
		{1,5,5,4},
	};
	PipeDfs pipeDfs((int*)maze,5,4,5,5);
	pipeDfs.dfs_maze(1,1,0,0,PipeDfs::Zhi_H,PipeDfs::Pipe_Right);
	pipeDfs.showPath();
	*/
	/*int maze[5][5]={
		{0,1,1,INIF,1},
		{1,0,INIF,1,INIF},
		{1,INIF,0,INIF,1},
		{INIF,1,INIF,0,INIF},
		{1,INIF,1,INIF,0},
	};
	GraphDfs graphDfs((int*)maze,5,5);
	graphDfs.dfs(1);
	graphDfs.showPath();
	GraphBfs graphBfs((int*)maze,5,5);
	graphBfs.bfs(1);
	graphBfs.showPath();
	*/
	/*
	int maze[5][5]={
		{0,2,INIF,INIF,10},
		{INIF,0,3,INIF,7},
		{4,INIF,0,4,INIF},
		{INIF,INIF,INIF,0,5},
		{INIF,INIF,3,INIF,0},
	};
	CityDfs cityDfs((int*)maze,5,5,5);
	cityDfs.dfs(1,0);
	cityDfs.showPath();
	FlightDfs flightDfs((int*)maze,5,5,5);
	flightDfs.dfs(1,0);
	flightDfs.showPath();
	FlightBfs flightBfs((int*)maze,5,5,5);
	flightBfs.bfs(1);
	flightBfs.showPath();*/
	/*
	int maze[4][4]={
		{1,0,0,0},
		{3,2,0,0},
		{4,10,1,0},
		{4,3,2,20},
	};
	NumTriangle nt((int*)maze,4,4);
	nt.dp();
	nt.showPath();
	*/
	/*
	int maze[4][4]={
	{0,2,6,4},
	{INIF,0,3,INIF},
	{7,INIF,0,1},
	{5,INIF,12,0},
	};
	int maze[6][6]={
	{0,1,12,INIF,INIF,INIF},
	{INIF,0,9,3,INIF,INIF},
	{INIF,INIF,0,INIF,5,INIF},
	{INIF,INIF,4,0,13,15},
	{INIF,INIF,INIF,INIF,0,4},
	{INIF,INIF,INIF,INIF,INIF,0}
	};
	*/
	/*
	int maze[5][5]={
		{0,-3,INIF,INIF,5},
		{INIF,0,2,INIF,INIF},
		{INIF,INIF,0,3,INIF},
		{INIF,INIF,INIF,0,2},
		{INIF,INIF,INIF,INIF,0},
	};
	Floyd floyd((int*)maze,6,6);
	floyd.floyd();
	floyd.showPath();
	Dijkstra dijkstra((int*)maze,6,6);
	dijkstra.dijkstra(1);
	dijkstra.showPath();
	*/
	/*
	int edge[5][3]={
		{2,3,2},
		{1,2,-3},
		{1,5,5},
		{4,5,2},
		{3,4,3},
	};*/
	/*
	int edge[7][3]={
	{1,2,2},
	{1,5,10},
	{2,3,3},
	{2,5,7},
	{3,4,4},
	{4,5,5},
	{5,3,6},
	};
	BellmanFord bellmanFord((int*)edge,7,5);
	bellmanFord.bellmanFord(1);
	bellmanFord.showPath();*/
	//BellmanFordQueue bellmanFordQueue((int*)edge,7,5);
	//bellmanFordQueue.bellmanFord(1);
	//bellmanFordQueue.showPath();
	
	/*
	HeapElemType testArr[]={1,2,3,4,5,6,7,8,9};
	RangeSort(testArr,sizeof(testArr)/sizeof(HeapElemType),5);
	ShowArray(testArr,sizeof(testArr)/sizeof(HeapElemType));
	*/
	/*
	int partner[9][2]={
		{1,2},
		{3,4},
		{5,2},
		{4,6},
		{2,6},
		{8,7},
		{9,7},
		{1,6},
		{2,4},
	};
	MergeSearch mergeSearch(partner,9,10);
	mergeSearch.handleInfo();
	mergeSearch.showPartner();
	*/
	int partner[9][3]={
		{1,2,1},
		{1,3,2},
		{4,6,3},
		{5,6,4},
		{2,3,6},
		{4,5,7},
		{3,4,9},
		{2,4,11},
		{3,5,13},
	};
	MinTree minTree(partner,9,6);
	minTree.handleInfo();
	minTree.showTree();
	Prim primTree(partner,9,6);
	primTree.handleInfo();
	primTree.showTree();
	system("Pause");
	return 0;
}