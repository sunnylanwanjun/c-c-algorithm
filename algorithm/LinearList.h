#ifndef __LINEARLIST_H
#define __LINEARLIST_H
#include <functional>
#include <assert.h>
template<typename Node>
struct List{
	typedef std::function<bool(Node*, Node*)> CompareFunc;
	virtual void ClearList() = 0;
	virtual bool GetElem(int i, Node* e) = 0;
	virtual int LocateElem(Node*e, CompareFunc compare) = 0;
	virtual bool ListInsert(int i, Node*e) = 0;
	virtual void ListAppend(Node*e) = 0;
	virtual void ListDelete(int i) = 0;
	virtual Node* PriorElem(Node*e) = 0;
	virtual int ListLength() = 0;
};

///////////////////////////////////////////////////////////////
//使用链表实现线性表
//链表结点
template<typename Elem>
struct LinkNode{
	Elem value;
	LinkNode *next;
};
//链表类
template<typename Elem>
struct LinkList :public List<LinkNode<Elem>>{
	LinkNode<Elem> *head, *tail;
	LinkList():head(nullptr),tail(nullptr){

	}
	LinkList(LinkList&L){
		int len = L.ListLength();
		LinkNode<Elem> node;
		for (int i = 0; i < len; i++){
			L.GetElem(i, node);
			ListInsert(i, node);
		}
	}
	LinkList& operator=(LinkList&L){
		int len = L.ListLength();
		LinkNode<Elem> node;
		for (int i = 0; i < len; i++){
			L.GetElem(i, node);
			ListInsert(i, node);
		}
		return *this;
	}
	~LinkList(){
		ClearList();
	}
	void ClearList(){
		LinkNode<Elem>* curNode = head;
		while (curNode){
			curNode = curNode->next;
			delete head;
			head = curNode;
		}
		head = tail = nullptr;
	}
	bool GetElem(int i, LinkNode<Elem>*e){
		int pos = 0;
		LinkNode<Elem>* curNode = head;
		while (pos++ != i&&curNode){
			curNode=curNode->next;
		}
		if (curNode == nullptr)
			return false;
		*e = *curNode;
		return true;
	}
	LinkNode<Elem>* GetHead(){
		return head;
	}
	int LocateElem(LinkNode<Elem>*e, CompareFunc  compare){
		LinkNode<Elem>* curNode = head;
		int pos = 0;
		while (curNode&&!compare(curNode, e)){
			curNode = curNode->next;
			pos++;
		}
		if (curNode == nullptr)
			return -1;
		return pos;
	}
	bool ListInsert(int i, LinkNode<Elem>*e){
		LinkNode<Elem>* curNode = head;
		LinkNode<Elem>* preNode = nullptr;
		if (i < 0){//向末尾添加结点
			curNode = nullptr;
		}
		int pos = 0;
		while (pos != i&&curNode){
			preNode = curNode;
			curNode = curNode->next;
			pos++;
		}
		//向链表末尾添加结点
		if (curNode == nullptr){
			preNode = tail;
		}
		LinkNode<Elem>* insertNode = new LinkNode<Elem>;
		*insertNode = *e;
		if (preNode){
			preNode->next = insertNode;
		}
		else{
			head = insertNode;
		}
		insertNode->next = curNode;
		if (insertNode->next == nullptr){
			tail = insertNode;
		}
		return true;
	}
	void ListDelete(int i){
		int pos = 0;
		LinkNode<Elem>* curNode = head;
		LinkNode<Elem>* preNode = nullptr;
		while (pos++ != i&&curNode){
			preNode = curNode;
			curNode = curNode->next;
		}
		if (curNode == nullptr){
			return;
		}
		if (curNode == head){
			head = curNode->next;	
		}
		if (curNode == tail){
			tail = preNode;
		}
		preNode->next = curNode->next;
		delete curNode;
	}
	LinkNode<Elem>* PriorElem(LinkNode<Elem>*e){
		LinkNode<Elem>* curNode = head;
		while (curNode&&curNode->next != e);
		return curNode;
	}
	void ListAppend(LinkNode<Elem>*e){
		LinkNode<Elem>* insertNode = new LinkNode<Elem>;
		*insertNode = *e;
		insertNode->next = nullptr;
		if (head == nullptr){
			head = insertNode;
		}
		if (tail){
			tail->next = insertNode;
		}
		tail = insertNode;
	}
	int ListLength(){
		int len = 0;
		LinkNode<Elem> *curNode = head;
		while (curNode){
			curNode = curNode->next;
			len++;
		}
		return len;
	}
};

///////////////////////////////////////////////////////////////
//使用顺序存储实现线性表
#define SqList_Malloc_Step 10
#define SqList_Malloc_Init 100
template<class Elem>
struct SqList :public List<Elem>{
	Elem* base;
	int size;
	int capacity;
	SqList() :size(0), capacity(SqList_Malloc_Init){
		base = new Elem[SqList_Malloc_Init];
		memset(base, 0, SqList_Malloc_Init*sizeof Elem);
	}
	~SqList(){
		delete[] base;
	}
	void ClearList(){
		size = 0;
	}
	bool GetElem(int i, Elem* e){
		if (i >= size)
			return false;
		*e = base[i];
		return true;
	}
	Elem GetElem(int i){
		return base[i];
	}
	Elem& operator[](int i){
		//越界访问
		if (i >= capacity)
			return base[size-1];
		return base[i];
	}
	int LocateElem(Elem*e, CompareFunc compare){
		for (int i = 0; i < size; i++){
			if (compare(&base[i], e)){
				return i;
			}
		}
		return -1;
	}
	void ListRelloc(){
		if (capacity - size < 1){
			capacity += SqList_Malloc_Step;
			Elem* newBase = new Elem[capacity];
			assert(newBase != nullptr);
			memcpy(newBase, base, size*sizeof Elem);
			delete[] base;
			base = newBase;
		}
	}
	bool ListInsert(int i, Elem*e){
		if (i<0 || i>size)
			return false;
		ListRelloc();
		if (i < size){
			memcpy(&base[i+1],&base[i],(size-i)*sizeof Elem);
		}
		base[i] = *e;
		size++;
		return true;
	}
	void ListAppend(Elem*e){
		ListRelloc();
		base[size++] = *e;
	}
	void ListDelete(int i){
		if (i == size - 1){
			size--;
			return;
		}
		//不能删除不存在的元素
		if (i<0 || i>=size)
			return;
		memcpy(&base[i], &base[i+1],(size-i-1)*sizeof Elem);
		size--;
	}
	Elem* PriorElem(Elem*e){
		return e - sizeof Elem;
	}
	int ListLength(){
		return size;
	}
};

void Chapter2();
#endif