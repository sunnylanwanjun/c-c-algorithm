#ifndef __ARRAYTABLE_H
#define __ARRAYTABLE_H
#define MAX_ARRAY_DIM 8
template<class Elem>
struct ArrayTable{
	Elem *base;
	int   dim;
	int  *bounds; //存放维度
	int  *constants;//存放维度乘积
	/*
	设j1 => 第1维
	j2 => 第2维
	j3 => 第3维
	...
	b1 => 第1维数据个数
	b2 => 第2维数据个数
	...
	在二维的情况下，
	0 1 2  3
	4 5 6  7
	8 9 10 11
	也可表示为
	{[0,1,2,3],[4,5,6,7],[8,9,10,11]}
	根据假设有
	b1 = 3 
	b2 = 4
	用公式表示
	Addr(j1,j2) = Addr(0,0) + (j1*b2+j2)*L,其中L表示单个元素所占空间
	Addr表示j1行j2列所在的地址
	在三维的情况下，
	{[(1,2,3),(4,5,6)],[(7,8,9),(1,2,3)],[(7,8,9),(1,2,3)],[(7,8,9),(1,2,3)]}
	b1 = 4
	b2 = 2
	b3 = 3
	Addr(j1,j2,j3) = Addr(0,0,0) + (j1*b2*b3 + j2*b3 + j3)*L
	推广到n维，则有
	Addr(j1,j2,...,jn) = Addr(0,0,...,0) + 
	[ (j1*b2*b3*...*bn) +
	  (j2*b3*b4*...*bn) +
	  ...
	  ...
	  ...
	  (jn-1*bn) +
	  jn
	]*L
	*/
	ArrayTable(int dim,...){
		assert(dim <= MAX_ARRAY_DIM);
		bounds = new int[dim];
		va_list va;
		va_start(va,dim);
		int totalSize = 1;
		for (int i = 0; i < dim; i++){
			bounds[i] = va_arg(va, int);
			totalSize *= bounds[i];
		}
		va_end(va);
		constants = new int[totalSize];
		constants[totalSize - 1] = 1;
		for (int i = totalSize-2; i >= 0; i--){
			constants[i] *= constants[i+1];
		}
	}
	~ArrayTable(){
		delete[] base;
		delete[] bounds;
		delete[] constants;
	}
	int Locate(va_list va){
		int pos = 1;
		int offset = 0;
		for (int i = 0; i < dim; i++){
			pos = va_arg(va, int);
			offset += constants[i] * pos;
		}
		va_end(va);
		return offset;
	}
	void Value(Elem* e,...){
		va_list va;
		va_start(va,e);
		*e = base[Locate(va)];
	}
	void Assign(Elem* e, ...){
		va_list va;
		va_start(va, e);
		base[Locate(va)] = *e;
	}

};

//n阶对称矩阵的下标对应关系推导
/*
矩阵下标
11 12 13 14
21 22 23 24
31 32 33 34
41 42 43 44

其中
21 12
13 31
。。。
。。。
对称位置上的值相同

接下来是数组下标
0
1 2
3 4 5
6 7 8 9
接下来由矩阵下标，推出数组下标
观察可知所在行数确定了该行有多少个数字
如第3行，有3 4 5
那么有0+1+2+3=6，也就是说可以推出每一行的最后一个数，由最后一个数减去行数就可以得到行首的数字，总结式子如下
(1+i)*i/2-i,由行首加下列数就可以知道矩阵与一维数组下标的关系，如下：
(1+i)*i/2-i+j-1 = (i-1)/2+j-1 这是下三角的公式
对于上三角，由对称关系可知
(j-1)/2+i-1,总结如下,设k为数组下标
当i>=j时，有k=(i-1)/2+j-1
当i<j时，有k=(j-1)/2+i-1
*/
//稀疏矩阵与对称矩阵不同，稀疏矩阵是没有规律了，我们使用三元组进行压缩存储
template<class Elem>
struct Triple{
	int i, j;
	Elem e;
};
#define TSMAXSIZE 12500
template<class Elem>
struct TSMatrix{
	Triple data[TSMAXSIZE+1];
	int mu, nu, tu;
};
#endif